#include <ArduinoBLE.h>

#include "HX711.h"

#define DOUT 2
#define CLK 3

HX711 scale;

float calibration_factor = 14778;

BLEService scaleService("181D");

// Bluetooth® Low Energy Battery Level Characteristic
BLEFloatCharacteristic scaleWeightChar("2A9D", // standard 16-bit characteristic UUID
                                       BLERead | BLENotify);

BLEUnsignedIntCharacteristic scaleMessageChar("2A9E",
                                              BLERead | BLEWrite);

float oldScaleValue = 0;
long timeStart = 0;

void setup()
{
  // Serial.begin(9600);
  // while (!Serial);

  /* Scale Setup */
  // Serial.println("Setting up scale");
  scale.begin(DOUT, CLK);
  scale.set_scale(calibration_factor);
  scale.tare();

  /* BLE setup */
  if (!BLE.begin())
  {
    // Serial.println("starting BLE failed!");
    while (1);
  }

  BLE.setLocalName("BlockPuller");
  BLE.setDeviceName("BlockPuller");
  BLE.setAdvertisedService(scaleService);
  scaleService.addCharacteristic(scaleWeightChar);
  scaleService.addCharacteristic(scaleMessageChar);
  BLE.addService(scaleService);
  scaleWeightChar.writeValue(oldScaleValue);

  BLE.advertise();

  // Serial.println("Bluetooth® device active, waiting for connections...");
}

void loop()
{
  BLEDevice central = BLE.central();

  if (central)
  {
    // Serial.print("Connected to central: ");
    // Serial.println(central.address());

    commWithCentral(central);

    // Serial.print("Disconnected from central: ");
    // Serial.println(central.address());
  }
}

void commWithCentral(BLEDevice central)
{
  while (central.connected())
  {
    readCentralMessages();
    long timePassed = millis();
    if (timePassed - timeStart >= 100)
    {
      timeStart = timePassed;
      updateScaleValue();
    }
  }
}

void updateScaleValue()
{
  // Serial.println("Reading scale...");
  float scaleValue = scale.get_units();
  // Serial.println(scaleValue);

  if (trunc(10. * scaleValue) != trunc(10. * oldScaleValue))
  {
    // Serial.print("Reading: ");
    // Serial.println(scaleValue);
    scaleWeightChar.writeValue(scaleValue);
    oldScaleValue = scaleValue;
  }
}

void readCentralMessages()
{
  if (scaleMessageChar.written())
  {
    // Serial.print("Value received from central: ");
    int value = scaleMessageChar.value();
    // Serial.println(value);

    if (value == 1)
    {
      scale.tare();
      // Serial.print("Scale Tared");
    }
    else if (value == 2)
    {
      scale.calibrate_scale(20);
      // Serial.print("Calibration factor: ");
      // Serial.println(scale.get_scale());
    }
  }
}
