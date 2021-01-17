#include <asf.h>
#include <delay.h>
#include <uart1.h>
#include <uart.h>

int main (void) {
    board_init();

    // Baud rate = 57600
    uart_init();

    // Baud rate = 9600
    uart1_init();

    while (1) {
        int done = 0;
        char cmd [100] = "";

        int ptr = 0;
        char c = 'c';

        // c is not LF
        while (c != 10) {
            int c = getchar();

            if (c == 10) {
                break;
            }

            cmd[ptr++] = c;
            //printf("char is %d\r\n", c);
        }

        cmd[ptr] = '\0';
        done = 1;

        //printf("string is %s\r\n", cmd);

        if (done != 0) {
            //printf("%s\r\n", cmd);
            //uart1_tx_char('8');
            uart1_tx_string(cmd);
            delay_ms(10);
            done = 0;
        }
    }
}
