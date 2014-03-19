#include "LPC11xx.h"		/* LPC11xx register definitions */
#include "flash_nvol.h"
#include "myinit.h"
#include "uart.h"
#include "xprintf.h"
#include "buzzer.h"
#include "gpio.h"
#include "main.h"

#define _BV(x) (1 << (x))


/*---------------------------------------------------------*/
/* User Provided Timer Function for FatFs module           */
/*---------------------------------------------------------*/


/* 1kHz Timer ISR */
static int i = 0;

void SysTick_Handler (void)
{
    static scale = 0;
    SysTick->CTRL;

    i++;
    update_switch_status();
    if (i % 100 == 0) {
        update_pwm_status();
    }
}

static int Mode = NOMMAL_MODE;

int main (void)
{
    char c;

    MySystemInit();
    NVOL_Init();

    ioinit();
    uart_init(38400);
    xdev_in(uart_getc);
    xdev_out(uart_putc);
    pwm_init();

    /* Enable SysTick timer in interval of 1ms */
    SysTick->LOAD = AHB_CLOCK /1000 - 1;
    SysTick->CTRL = 0x07;
    
    while (1) {
        /* やること */
        /*     モードは3つ */
        /*     -通常モード */
        /*     -録音モード */
        /*     -再生モード */

        /* test1 */
        /* buzzer_on(); */
        /* if (c = uart_getc()){ */
        /*         uart_putc(c); */
        /*         if (c >= '0' && c <= '9') set_sound_scale(c-'0'); */
        /*         if (c >= 'a' && c <= 'c') set_sound_scale(c-'a'+10); */
    /* } */

        /* test2 */
 
            xprintf("sw : %x\n", get_switch_status());
    }
            
            
    return 0;
}


