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

    rx_buffer[rx_write_pos] = UDR1;
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

/*


    void myloop(void) {

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

*/