/*
    uart1.c

    Created: 17/1/2021 3:36:15 PM
    Author: user
*/
#include <uart1.h>
#include <uart.h>

char rx_buffer[RX_BUFFER_SIZE];

uint8_t rx_read_pos = 0;
uint8_t rx_write_pos = 0;

int hello = 100;

int flag_string_done = 0;

void uart1_init(void) {
    UBRR1H = (BRC >> 8);
    UBRR1L = BRC;

    UCSR1B = (1 << TXEN1) | (1 << RXEN1) | (1 << RXCIE1);

    UCSR1C = (1 << UCSZ00) | (1 << UCSZ11);
}

void uart1_tx_char(char c) {
    loop_until_bit_is_set(UCSR1A, UDRE1);
    UDR1 = c;
}

void uart1_tx_string(char str[]) {
    for (int i = 0; i < strlen(str); i++) {
        uart1_tx_char(str[i]);
    }

    uart1_tx_char('\r');
    uart1_tx_char('\n');
}

ISR(USART1_RX_vect) {
    //printf("isr\r\n");

    char c = UDR1;

    //printf("%c\r\n", c);

    // LF read
    if (c == 10) {
        flag_string_done = 1;
        //printf("done\r\n");
    }

    rx_buffer[rx_write_pos] = c;
    rx_write_pos++;

    // Buffer may overflow
    if (rx_write_pos >= RX_BUFFER_SIZE) {
        rx_write_pos = 0;
    }


}

char uart1_peek_char(void) {
    char ret = '\0';

    if (rx_read_pos != rx_write_pos) {
        ret = rx_buffer[rx_read_pos];
    }

    return ret;
}

char uart1_rx_char(void) {
    char ret = '\0';

    if (rx_read_pos != rx_write_pos) {
        ret = rx_buffer[rx_read_pos++];

        if (rx_read_pos >= RX_BUFFER_SIZE) {
            rx_read_pos = 0;
        }
    }

    return ret;
}

const char *uart1_rx_string(void) {
    char str [20] ;
    int str_pos = 0;

    static char buf[32];


    while (flag_string_done) {
        char c = uart1_rx_char();

        if (c != 0) {
            //printf("Char is %d\r\n", c);
        }

        // NOT CR
        if (c != 13 && c != '\r' && c != 0) {
            str[str_pos++] = c;
        }
        else if (c == 13 || c == '\r') {
            str[str_pos] = '\0';
            char test = uart1_rx_char(); // Read the LF

            if (test == 10) {
                //printf("LF is read\r\n");
            }

            //printf("String is %s\r\n\r\n", str);

            flag_string_done = 0;

            str_pos = 0;


            sprintf(buf, "%s", str);
            return buf;
        }
        else if (c == 10) {
            // ignore
        }
    }

    return "random";
}


const char *debug(void) {
    return "hello";
}
