# Block Puller

A small arduino project, I wanted to replicate a [tindeq progessor](https://tindeq.com/product/progressor/). This tool, in addition to something like a tension block, is a great method for finger strength training with a compact package. Finger training is a vital part of training for rock climbing, and the block puller allows for high precision, as well as the ability to train anywhere anytime.

If you're curious what it looks like to use one of these, [here](https://www.youtube.com/watch?v=RMn2DxFDHQI) is a great video of the tindeq progessor in action.


## Circuit Diagram
Essentially, the block puller is a force plate hooked up to a strain guage, which then transmits data via an Arduino through Bluetooth Low Energy (BLE) to a mobile phone or computer. There is a quick sketch below, with components left to right being:
- 600 mAh LiPo batter
- Power switch on the positive wire between the battery and Seeed Xiao
- [Seeed Xiao](https://www.google.com/search?q=seeed+xiao+ble&rlz=1C5GCCM_en&oq=seeed+xiao+ble&gs_lcrp=EgZjaHJvbWUqCQgAEEUYOxiABDIJCAAQRRg7GIAEMgcIARAAGIAEMgcIAhAAGIAEMgcIAxAAGIAEMgcIBBAAGIAEMgYIBRBFGDwyBggGEEUYPDIGCAcQRRg8qAIAsAIA&sourceid=chrome&ie=UTF-8), running Arduino
- HX711
- A force plate with a strain guage on it

<img width="1215" alt="Screenshot 2024-05-16 at 2 03 26 PM" src="https://github.com/mitchbr/BlockPullApp/assets/40349575/5c0b5749-48f7-4530-82c0-d43e52420f72">



## Pictures

Some more pictures of what I've built. I forgot to take pictures along the way, but I am building a second now and plan to add more pictures as this one is completed. The construction uses 9 layers of 1/8th inch solid wood. Each layer is cut to it's required shape prior to glueing, this way I can fit cavities inside for the circuits, battery, and switches/charging port. Finally, the layers are glued together into two halves, so I can sandwich the force plate between the two layers. The two halves are then held together with bolts.

<img width="628" alt="Screenshot 2024-05-16 at 2 09 13 PM" src="https://github.com/mitchbr/BlockPullApp/assets/40349575/e6b10ae2-9bc1-4138-b595-15a54bc28012">

<img width="666" alt="Screenshot 2024-05-16 at 2 09 32 PM" src="https://github.com/mitchbr/BlockPullApp/assets/40349575/45d4be27-b318-4dd8-b46f-328c3b9a0385">

<img width="398" alt="Screenshot 2024-05-16 at 2 09 47 PM" src="https://github.com/mitchbr/BlockPullApp/assets/40349575/12085bd1-895c-4692-8bcd-5e02efa6aab7">
