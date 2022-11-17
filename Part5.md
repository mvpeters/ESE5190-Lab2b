Below is a picture of the I2C traffic running my firefly code I captured during last weeks lab session.

![IMG_4650](https://user-images.githubusercontent.com/114199773/200013572-4647bef7-30e9-4a7d-95d0-b919855ae731.jpg)


Looking at the image and the datasheet, the clock can be seen on the bottom in green while the transmitted packet can be seen on top in yellow. When the clock ticks from high to low it signals the start of a data packet. Everytime the clock then goes from low to high it transmitts 1 bit. If the bit is a 1 the yellow waveform is high, if the bit is 0 the yellow waveform is low. In the middle of the packet there is a breif pause where it acknowledges. The top waveform is different depending on the series of 1's and 0's being sent in the packet.
