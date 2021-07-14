# LCD-8bit-custom-char

<p align="justify">The 16x2 LCD module works by displaying ASCII characters when their corresponding 8-bit ASCII code is sent to it. The pixels on the LCD display that should be 
switched on to display each ASCII character are stored within the microcontroller unit of the display. When the ASCII code is sent to the microcontroller, the pixels corresponding
to the ASCII character will be lit.</p>

<p align="justify">Besides the pre-defined ASCII characters, the microcontroller unit of the LCD display can also store upto 8 user-defined custom characters on its CG-RAM (Character Graphics RAM) and display them on the screen. In order to store the custom characters, first a command must be sent to the microcontroller unit pointing to the CG-RAM address that the character should be stored at. There are 8 memory locations of 8 bits to store custom characters, starting from address 0x40 to 0x78, with each location being indexed from 0 to 7. When a custom character stored in the CG-RAM has to be displayed, it can be accessed by sending the index of the memory location it is stored at as a character to the LCD module (by setting RS to HIGH).</p>

<p align="justify">Since each character displayed on the 16x2 LCD display module is composed of a grid of 7x5 or 8x5 pixels (depending on the display), the custom character information is represented and stored in an array of hexadecimal values, each representing a row of the pixel grid. Once the memory location the character should be stored at has been sent, each hexadecimal value of the character array will be transferred one after the other. In this way, the custom characters can be stored on the LCD module to be accessed and displayed later.</p>

<p align="justify">For more information on using the LCD module in 8-bit mode, visit my LCD-8bit-mode repo <a href="https://github.com/asitha-navaratne/LCD-8bit-mode">here</a>.</p>
