/** "https://maxpromer.github.io/LCD-Character-Creator/" to generate custom characters */

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#define LCD_DDR		DDRB						///< DDR of LCD display pins.
#define CTRL_DDR	DDRD						///< DDR of LCD control pins.
#define LCD_PORT	PORTB						///< Port of LCD display pins.
#define CTRL_PORT	PORTD						///< Port of LCD control pins.
#define RS 		PD0						///< Pin for LCD Register Select terminal.
#define EN  		PD1						///< Pin for LCD Enable terminal.

void LCD_DISPLAY_INIT(void);
void LCD_SEND_COMMAND(unsigned char command);
void LCD_SEND_CHARACTER(unsigned char character);
void LCD_SEND_STRING(char *string);
void LCD_CREATE_CHARACTER(uint8_t position,unsigned char *character);

int main(void){
	LCD_DISPLAY_INIT();
	
	unsigned char character1[8] = {0x04,0x04,0x0E,0x1F,0x15,0x04,0x04,0x0E};
	unsigned char character2[8] = {0x04,0x1F,0x11,0x11,0x1F,0x1F,0x1F,0x1F};
	unsigned char character3[8] = {0x04,0x0E,0x0E,0x0E,0x1F,0x00,0x04,0x00};
	unsigned char character4[8] = {0x01,0x03,0x07,0x1F,0x1F,0x07,0x03,0x01};
	unsigned char character5[8] = {0x01,0x03,0x05,0x09,0x09,0x0B,0x1B,0x18};
	unsigned char character6[8] = {0x0A,0x0A,0x1F,0x11,0x11,0x0E,0x04,0x04};
	unsigned char character7[8] = {0x00,0x00,0x1F,0x1B,0x15,0x11,0x1F,0x00};
	unsigned char character8[8] = {0x00,0x1F,0x11,0x0A,0x04,0x04,0x04,0x06};		///< Custom LCD characters (Only 8 can be stored in the 64 byte CG-RAM at one time).
	
	LCD_CREATE_CHARACTER(0,character1);  				///< Build character1 and store at position 0 (CG-RAM address 0x40).
	LCD_CREATE_CHARACTER(1,character2);  				///< Build character2 and store at position 1 (CG-RAM address 0x48).
	LCD_CREATE_CHARACTER(2,character3);  				///< Build character3 and store at position 2 (CG-RAM address 0x50).
	LCD_CREATE_CHARACTER(3,character4);  				///< Build character4 and store at position 3 (CG-RAM address 0x58).
	LCD_CREATE_CHARACTER(4,character5);  				///< Build character5 and store at position 4 (CG-RAM address 0x60).
	LCD_CREATE_CHARACTER(5,character6);  				///< Build character6 and store at position 5 (CG-RAM address 0x68).
	LCD_CREATE_CHARACTER(6,character7);  				///< Build character7 and store at position 6 (CG-RAM address 0x70).
	LCD_CREATE_CHARACTER(7,character8);  				///< Build character8 and store at position 7 (CG-RAM address 0x78).
	
	LCD_SEND_COMMAND(0x80);						///< Send cursor to the beginning of first line.
	LCD_SEND_STRING("Custom characters");
	LCD_SEND_COMMAND(0xC0);						///< Send cursor to the beginning of second line.
	
	for(uint8_t i=0;i<8;i++){
		LCD_SEND_CHARACTER(i);					///< Send a numerical character corresponding to the stored custom character.
	 	LCD_SEND_CHARACTER(32);					///< Send an ASCII space character.
	}
}

/*!
 *	@brief Initialize LCD in 8-bit mode.
 */

void LCD_DISPLAY_INIT(void){
	LCD_DDR = 0xFF;
    	CTRL_DDR = 0xFF;
	
	LCD_SEND_COMMAND(0x01);						///< Clear LCD screen.
    	LCD_SEND_COMMAND(0x3C);						///< 2 line, 5x8 matrix of characters in 8-bit mode.
	LCD_SEND_COMMAND(0x06);						///< Auto-increment cursor.
    	LCD_SEND_COMMAND(0x0E);						///< Turn display and cursor on.
    	_delay_us(2);
}

/*!
 *	@brief Send a command to the LCD display.
 *	@param Command to be sent (unsigned char).
 */

void LCD_SEND_COMMAND(unsigned char command){
    	LCD_PORT = command;
    
	CTRL_PORT &= ~(1<<RS);						///< Set RS pin low to enter command mode.
    	CTRL_PORT |= (1<<EN);
    	_delay_ms(5);
    	CTRL_PORT &= ~(1<<EN);						///< Create a momentary pulse at EN pin to send the data to the LCD.
	
	_delay_ms(2);
}

/*!
 *	@brief Send a single character to the LCD display.
 *	@param Character to be sent (unsigned char).
 */

void LCD_SEND_CHARACTER(unsigned char character){
    	LCD_PORT = character;
    
	CTRL_PORT |= (1<<RS);						///< Set RS pin high to enter character mode.
	CTRL_PORT |= (1<<EN);
    	_delay_ms(5);
    	CTRL_PORT &= ~(1<<EN);						///< Create a momentary pulse at EN pin to send the data to the LCD.

	_delay_ms(2);
}

/*!
 *	@brief Send a string of characters to the LCD display.
 *	@param String to be sent (char).
 */

void LCD_SEND_STRING(char *string){
	for(uint8_t i=0;string[i]!=0;i++){	
		LCD_SEND_CHARACTER(string[i]);
		_delay_ms(2);
	}
}

/*!
 *	@brief Create a custom character and store it in the CG-RAM.
 *	@param Position to store in CG-RAM (uint8_t) and pixel data of character to be created (unsigned char).
 */

void LCD_CREATE_CHARACTER(uint8_t position,unsigned char *character){
	LCD_SEND_COMMAND(0x40 + (position*8));				///< Send command to point to CG-RAM address corresponding to relevant position.
	for(uint8_t i=0;i<8;i++){
		LCD_SEND_CHARACTER(character[i]);			///< Send the custom character pixel data.
	}
}
