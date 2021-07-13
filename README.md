# LCD-8bit-custom-char

<p align="justify">The 16x2 LCD module works by displaying ASCII characters when their corresponding 8-bit ASCII code is sent to it. The pixels on the LCD display that should be 
switched on to display each ASCII character are stored within the microcontroller unit of the display. When the ASCII code is sent to the microcontroller, the pixels corresponding
to the ASCII character will be lit.</p>

<p align="justify">Other than the pre-defined ASCII characters, the microcontroller unit of the LCD display can also store upto 8 user-defined custom characters on its CG-RAM and 
display them on the module. In order to store the custom characters, first a command must be sent to the microcontroller pointing to the CG-RAM address that the character should 
be stored at. There are 8 memory addresses from 0x40 to 0x48. Next, the custom character should be sent to the microcontroller unit to be stored.</p>
