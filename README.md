# 4x3-keypad-lock-system
A lock system that uses a 4x3 keypad matrix, and a double lock mechanic.

This project is a simple one. To use this you can download the source code and upload to your arduino. The schematic is there as well.
You can use a 4x4 or a bigger keypad of course, but you have to change some things in the code to make it work. 

You have to define the master key and the password first. If you fail to write the right password three times, then you have to reset the
system with the master key, because both of the lock will be activated until you write the master key. After you write the master key
everything goes back to normal.
