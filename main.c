#include "LPC11xx.h"		/* LPC11xx register definitions */
#include "flash_nvol.h"
#include "myinit.h"
#include "uart.h"
#include "xprintf.h"
#include "buzzer.h"
#include "gpio.h"
#include "rec.h"
#include "main.h"

#define _BV(x) (1 << (x))


/*---------------------------------------------------------*/
/* User Provided Timer Function for FatFs module           */
/*---------------------------------------------------------*/



static unsigned char rec_ptr = 0;
static unsigned char rec_length = 0;
static unsigned char play_ptr = 0;
static short melody_list[REC_LIMIT+1];
static int Mode = NORMAL_MODE;
static int i = 0;
static int limit_count = 0;
static int standby_count = 0;

/* 20Hz Timer ISR */
void SysTick_Handler (void)
{
    uint16_t scale, switch_st;

    SysTick->CTRL;

    i++;
    update_switch_status();
    switch_st = get_switch_status();

    if (Mode == NORMAL_MODE) {
        for (scale = C; scale <= HC; scale++) {
            if (switch_st & (1 << scale)) {
                set_sound_scale(scale);
                buzzer_on();
            }
        }
        if ((switch_st & 0x1FFF) == 0) {
            buzzer_off();
        }
        if(switch_st & (1 << PLAY)) {
            Mode = PLAY_MODE;
        }
        if(switch_st & (1 << REC)) {
            standby_count = 0;
            Mode = STANDBY_MODE;
        }
    }

    else if (Mode == PLAY_MODE) {
        if (play_ptr >= rec_length) {
            Mode = NORMAL_MODE;
            play_ptr = 0;
        } else {
            switch_st = melody_list[play_ptr++];
            for (scale = C; scale <= HC; scale++) {
                if (switch_st & (1 << scale)) {
                    set_sound_scale(scale);
                    buzzer_on();
                }
            }
            if ((switch_st & 0x1FFF) == 0) {
                buzzer_off();
            }
        }
    }

    else if (Mode ==STANDBY_MODE) {
        for (scale = C; scale <= HC; scale++) {
            if (switch_st & (1 << scale)) {
                set_sound_scale(scale);
                buzzer_on();
            }
        }
        if ((switch_st & 0x1FFF) == 0) {
            buzzer_off();
        }

        if (switch_st & (1 << REC)) {
            standby_count++;
        } else {
            standby_count = 0;
            Mode = NORMAL_MODE;
        }

        if (standby_count >= 10) {
            limit_sound();
            buzzer_on();
        }
        if (standby_count >= 12) {
            standby_count = 0;
            Mode = REC_MODE;
        }
    }

    else if (Mode == REC_MODE) {
        for (scale = C; scale <= HC; scale++) {
            if (switch_st & (1 << scale)) {
                set_sound_scale(scale);
                buzzer_on();
            }
        }
        if ((switch_st & 0x1FFF) == 0) {
            buzzer_off();
        }
        melody_list[rec_ptr++] = (switch_st & 0x1FFF);
        if ((switch_st & (1 << REC)) == 0 || (rec_ptr >= REC_LIMIT)) {
            Mode = LIMIT_MODE;
        }
    }

    else if (Mode == LIMIT_MODE) {
        if (limit_count < 2 || (limit_count > 3 && limit_count <= 10)) {
            limit_sound();
            buzzer_on();
        } else {
            buzzer_off();
        }
        limit_count++;
        if (limit_count == 20) {
            rec_length = rec_ptr;
            set_rec_length(&rec_length, 0);
            LPC_TMR32B1->TCR |= (1 << 1);
            LPC_TMR32B1->TCR &= ~(1 << 0);
            for(rec_ptr = 0; rec_ptr < rec_length; rec_ptr++) {
                set_rec_data(melody_list + rec_ptr, rec_ptr + 1);
            }
        }
        if(limit_count >= 21) {
            limit_sound();
            buzzer_on();
        }
        if (limit_count >= 25) {
            buzzer_off();
            limit_count = rec_ptr = 0;
            Mode = NORMAL_MODE;
        }
    }

    update_buzzer_status();
    xprintf("sw   : %4x  ",switch_st);
    xprintf("mode : %d  ",Mode);
    xprintf("limit_count : %d  ",limit_count);
    xprintf("rec_length : %d  ",rec_length);
    xprintf("play : %d  ",play_ptr);
    xprintf("rec  : %d\n", rec_ptr);

}


int main (void)
{
    uint8_t scale;
    MySystemInit();
    NVOL_Init();

    ioinit();
    uart_init(38400);
    xdev_in(uart_getc);
    xdev_out(uart_putc);
    pwm_init();
    get_rec_data(&rec_length, melody_list);
    /* Enable SysTick timer in interval of 50ms */
    SysTick->LOAD = AHB_CLOCK * 50 / 1000 - 1;
    SysTick->CTRL = 0x07;

    xprintf("test\n");

    while (1) {
        /* do nothing */
    }


    return 0;
}


