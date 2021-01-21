#include <asf.h>
#include <delay.h>
#include <uart1.h>
#include <uart.h>
#include <avr/interrupt.h>

extern int hello;
extern int flag_string_done;

int main (void) {


    board_init();

    // Baud rate = 57600
    uart_init();

    // Baud rate = 9600
    uart1_init();
    sei(); // Turn on external interrupts

    while (1) {
        uart1_rx_string();

        //delay_ms(600);
    }
}
