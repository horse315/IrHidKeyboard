# IrHidKeyboard
IR remote control for my Car PC. Emulates keyboard and mouse USB HID Combo device.

## Hardware

- Digispark USB board or other attiny85 controller
- Any 38kHz IR receiver
- 10 kOhm resistor

### Arduino prototype scheme
![Arduino prototype scheme](https://raw.githubusercontent.com/horse315/IrHidKeyboard/master/ir_remote.png)

## Software

- Arduino IDE 1.6 with Digispark boards support
- Adafruit HID Combo libraries (also included in src/libraries): https://github.com/adafruit/Adafruit-Trinket-USB

## Description
Device emulates pressing keyboard media and other keys and key combinations. IR receiver data output is connected to PIN_2 (INT_0) of Digispark board. Also you can add hardware resistance key support. 

### Story
The idea was to make a small device compatible with all possible DIY Car PC systems (commonly Windows or Android/Linux). I tried Arduino HID Keyboard firmware on my Arduino UNO and Digikeyboard library on Digispark with standard IR Decode libraries, but media keys (play/pause, next, previous track) did not work in Windows for both. So I found these great Adafruit HID libraries that solve problem with media keys, but with them and IR libraries compilled sketch was too big for Digispark board. IR libraries provided with Digispark and Arduino have big overhead of different protocols implemetation, while most remotes in DIY kits from ebay use only NEC IR  protocol. So I wrote this slim implementation that uses about 4200 bytes! Also you can connect wheel media keys to controller - 1800 bytes left.
