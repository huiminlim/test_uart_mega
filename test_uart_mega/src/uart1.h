/*
    uart1.h

    Created: 17/1/2021 3:36:22 PM
    Author: user
*/

#include <avr/io.h>
#include <string.h>
#include <avr/sfr_defs.h>			// For loop_until_bit_is_set()
#include <avr/interrupt.h>

#define FF_CPU					16000000UL
#define BAUD					9600
#define BRC						((FF_CPU/16/BAUD) - 1)

void uart1_init(void);
void uart1_tx_char(char c);
void uart1_tx_string(char str[]);

#define RX_BUFFER_SIZE 128

#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))


char uart1_rx_char(void);
char uart1_peek_char(void);
void uart1_rx_string(char[], int);
