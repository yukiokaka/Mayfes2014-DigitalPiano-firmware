#include "LPC11xx.h"		/* LPC11xx register definitions */
#include "system_LPC11xx.h"
#include "buzzer.h"
#include "xprintf.h"

static volatile uint32_t prescale_value = 0; 
static volatile uint32_t pwm_period = 27272;
static volatile uint32_t palse_width = 27272/2; 
static volatile uint8_t buzzer_status = OFF;

static const int16_t scale_freq[] = {freq_C,
                                     freq_Cs,
                                     freq_D,
                                     freq_Ds,
                                     freq_E,
                                     freq_F,
                                     freq_Fs,
                                     freq_G,
                                     freq_Gs,
                                     freq_A,
                                     freq_As,
                                     freq_B,
                                     freq_HC,
                                     freq_HA
};

void pwm_init (void)
{

    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 10);

    LPC_TMR32B1->PR = prescale_value;
    LPC_TMR32B1->PWMC = (1 << 0);
    LPC_TMR32B1->MR0 = palse_width;
    LPC_TMR32B1->MR1 = pwm_period;
    LPC_TMR32B1->MCR = (1 << 4);

    /* LPC_TMR32B1->TCR = (1 << 0); */
}

void set_palse_width (const uint32_t new_palse_width)
{
    if (new_palse_width >= pwm_period) palse_width = pwm_period;
    else palse_width = new_palse_width;
}

void set_pwm_period (const uint32_t new_pwm_period)
{
    if (pwm_period >= 0xFFFFFFFF) pwm_period = 0xFFFFFFFF;
    else pwm_period = new_pwm_period;
}

void set_sound_scale(const uint8_t new_scale)
{
    uint32_t new_pwm_period, new_palse_width; 
    if (new_scale > 13) return;

    new_pwm_period = (12000000 / scale_freq[new_scale]);
    new_palse_width = (new_pwm_period / 2);
    /* xprintf("scale_frec = %d\n",scale_freq[new_scale]); */
    set_palse_width(new_palse_width);
    set_pwm_period(new_pwm_period);
}

void limit_sound(void)
{
    set_sound_scale(13);
}

void buzzer_on (void)
{
    buzzer_status = ON;
}

void buzzer_off (void)
{
    buzzer_status = OFF;
}

void update_buzzer_status (void)
{
    /* LPC_TMR32B1->PR = prescale_value; */
    while (LPC_TMR32B1->TC >= pwm_period);
    LPC_TMR32B1->MR1 = pwm_period;
    LPC_TMR32B1->MR0 = palse_width;
    if(buzzer_status) {
        LPC_TMR32B1->TCR |= (1 << 0); 
        /* LPC_TMR32B1->TCR |= (1 << 1);  */
        LPC_TMR32B1->TCR &= ~(1 << 1);
    } else {
        LPC_TMR32B1->TCR |= (1 << 1);
        LPC_TMR32B1->TCR &= ~(1 << 0); 
    }
    xprintf("st = %d PWM period = %d  ", buzzer_status == ON,pwm_period);
    pwm_init();
}
