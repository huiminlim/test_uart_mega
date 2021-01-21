#include <asf.h>
#include <delay.h>
#include <uart1.h>
#include <uart.h>
#include <avr/interrupt.h>

int flag_string_done = 0;


int main (void) {
    char str [20] ;
    int str_pos = 0;

    board_init();

    // Baud rate = 57600
    uart_init();

    // Baud rate = 9600
    uart1_init();
    sei(); // Turn on external interrupts

    while (1) {
        char c = uart1_rx_char();

        if (c != 0) {
            printf("Char is %d\r\n", c);
        }

        // NOT CR
        if (c != 13 && c != 0) {
            str[str_pos++] = c;
        }
        else if (c == 13) {
            str[str_pos] = '\0';
            char test = uart1_rx_char(); // Read the LF

            if (test == 10) {
                printf("LF is read\r\n");
            }

            printf("String is %s\r\n\r\n", str);
            str_pos = 0;
            flag_string_done = 1;
        }
        else if (c == 10) {
            // ignore
        }
    }
}


/*


        if (c == '1') {
	        printf("hello\r\n");
        }
        else if (c != 0) {
	        printf("%d\r\n", c);
        }
*/