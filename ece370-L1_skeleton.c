
/*
This code will cause a TekBot connected to the AVR board to
move forward and when it touches an obstacle, it will reverse
and turn away from the obstacle and resume forward motion.

PORT MAP
Port B, Pin 7 -> Output -> Left Motor Direction
Port B, Pin 6 -> Output -> Left Motor Enable
Port B, Pin 5 -> Output -> Right Motor Enable
Port B, Pin 4 -> Output -> Right Motor Direction
Port D, Pin 5 -> Input -> Left Whisker
Port D, Pin 4 -> Input -> Right Whisker
*/

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

int main(void)
{
      DDRB = 0b11110000;  // configure Port B pins for output
      PORTB = 0b11110000; // set initial value for Port B outputs
                          // (initially, disable both motors)

      DDRD = 0b00000000;  // configure Port D pins for input
      PORTD = 0b11111111; // set initial value for Port D inputs
                          // (enable pull-up resistors for whiskers)

      while (1) // loop forever
      {
            // Your code goes here
            uint8_t mpr = PIND & 0b00110000; // read and extract only 4-5th bits

            // reverse and turn left when:
            // - the right whisker is hit
            // - both whiskers are hit
            if (mpr == 0b00100000 || mpr == 0b00000000)
            {
                  // reverse
                  PORTB = 0b00000000; // back up
                  _delay_ms(1000);    // wait for 1 second
                  // turn left
                  PORTB = 0b00010000; // left motor backward, right motor forward
                  _delay_ms(1000);    // wait for 1 second
            }
            else if (mpr == 0b00010000)
            {
                  // reverse
                  PORTB = 0b00000000; // back up
                  _delay_ms(1000);    // wait for 1 second
                  // turn right
                  PORTB = 0b10000000; // right motor backward, left motor forward
                  _delay_ms(1000);    // wait for 1 second
            }
            else
            {
                  // move forward
                  PORTB = 0b10010000; // enable both motors to move forward
            }
      }
}
