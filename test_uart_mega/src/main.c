#include <asf.h>
#include <delay.h>
#include <uart1.h>

int main (void) {
    board_init();

    uart1_init();

    while (1) {
        //uart1_tx_char('8');
        uart1_tx_string("hello");
        delay_ms(1000);
    }

}
