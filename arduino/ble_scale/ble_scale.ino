#include <ArduinoBLE.h>
#include <EEPROM.h>

#include "HX711.h"

#define DOUT 6
#define CLK 5

HX711 scale;

int calibration_addr = 0;
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
  Serial.begin(9600);
  while (!Serial)
    ;

  int read_calibration = EEPROM.read(calibration_addr);
  Serial.print("Read value from EEPROM: ");
  Serial.println(read_calibration);

  /* Scale Setup */
  scale.begin(DOUT, CLK);
  scale.set_scale(calibration_factor);
  scale.tare();

  /* BLE setup */
  if (!BLE.begin())
  {
    Serial.println("starting BLE failed!");
    while (1)
      ;
  }

  BLE.setLocalName("BlockPuller");
  BLE.setAdvertisedService(scaleService);
  scaleService.addCharacteristic(scaleWeightChar);
  scaleService.addCharacteristic(scaleMessageChar);
  BLE.addService(scaleService);
  scaleWeightChar.writeValue(oldScaleValue);

  BLE.advertise();

  Serial.println("Bluetooth® device active, waiting for connections...");
}

void loop()
{
  BLEDevice central = BLE.central();

  if (central)
  {
    Serial.print("Connected to central: ");
    Serial.println(central.address());

    commWithCentral(central);

    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
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
  float scaleValue = scale.get_units();

  if (trunc(10. * scaleValue) != trunc(10. * oldScaleValue))
  {
    Serial.print("Reading: ");
    Serial.println(scaleValue);
    scaleWeightChar.writeValue(scaleValue);
    oldScaleValue = scaleValue;
  }
}

void readCentralMessages()
{
  if (scaleMessageChar.written())
  {
    Serial.print("Value received from central: ");
    int value = scaleMessageChar.value();
    Serial.println(value);

    if (value == 1)
    {
      scale.tare();
      Serial.print("Scale Tared");
    }
    else if (value == 2)
    {
      scale.calibrate_scale(20);
      Serial.print("Calibration factor: ");
      Serial.println(scale.get_scale());
    }
  }
}
