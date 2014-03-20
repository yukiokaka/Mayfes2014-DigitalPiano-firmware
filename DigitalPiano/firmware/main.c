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
static volatile uint32_t switch_st = 0;
static volatile uint32_t palse_width = 1000;
static volatile uint32_t rec_ptr = 0;
static uint32_t rec_length = 0;
static volatile uint32_t play_ptr = 0;
static volatile uint32_t melody_list[REC_LIMIT]; 
static volatile int Mode = NORMAL_MODE;

void SysTick_Handler (void)
{
    static uint32_t scale = 0;
    SysTick->CTRL;

    i++;
    if ((i % 10) == 0) {
        update_switch_status();
        switch_st = get_switch_status();
        update_buzzer_status();
        xprintf("sw   : %x  ",switch_st);
        xprintf("mode : %d  ",Mode);
        xprintf("rec  : %d\n", rec_ptr);
        /* todo:録音限界の処理 */
        if (Mode == REC_MODE) {
            melody_list[rec_ptr++] = (switch_st & 0x1FFF);
            if (rec_ptr == REC_LIMIT) Mode = NORMAL_MODE;
        }
        if ((Mode != REC_MODE) && (rec_ptr != 0)) {
            rec_length = rec_ptr;
            rec_ptr = 0;
        }
        if (Mode == PLAY_MODE) {
            if (play_ptr >= rec_length) {
                Mode = NORMAL_MODE;
                play_ptr = 0;
            } else {
                switch_st = melody_list[play_ptr++];
            }
        }
        
    }
}


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

    xprintf("test\n");
    
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
        /* xprintf("sw : %x\n", get_switch_status()); */

        /* test3 */
            if (switch_st & (1 << C)) {
                set_sound_scale(C);
                buzzer_on();
            }
            if (switch_st & (1 << Cs)) {
                set_sound_scale(Cs);
                buzzer_on();
            }
            if (switch_st & (1 << D)) {
                set_sound_scale(D);
                buzzer_on();
            }
            if (switch_st & (1 << Ds)) {
                set_sound_scale(Ds);
                buzzer_on();
            }
            if (switch_st & (1 << E)) {
                set_sound_scale(E);
                buzzer_on();
            }
            if (switch_st & (1 << F)) {
                set_sound_scale(F);
                buzzer_on();
            }
            if (switch_st & (1 << Fs)) {
                set_sound_scale(Fs);
                buzzer_on();
            }
            if (switch_st & (1 << G)) {
                set_sound_scale(G);
                buzzer_on();
            }
            if (switch_st & (1 << Gs)) {
                set_sound_scale(Gs);
                buzzer_on();
            }
            if (switch_st & (1 << A)) {
                set_sound_scale(A);
                buzzer_on();
            }
            if (switch_st & (1 << As)) {
                set_sound_scale(As);
                buzzer_on();
            }
            if (switch_st & (1 << B)) {
                set_sound_scale(B);
                buzzer_on();
            }
            if (switch_st & (1 << HC)) {
                set_sound_scale(HC);
                buzzer_on();
            }

            if (switch_st == 0) {
                buzzer_off();
            }
            if(switch_st & (1 << PLAY)) {
                Mode = PLAY_MODE;
            }
            
            if(switch_st & (1 << REC)) {
                Mode = REC_MODE;
            } else if (Mode != PLAY_MODE) { /* 再生中は戻さないように */
                Mode = NORMAL_MODE;
            }
 

  
  
    }
            
            
    return 0;
}


