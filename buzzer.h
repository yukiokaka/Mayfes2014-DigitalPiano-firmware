#ifndef _BUZZER_H_
#define _BUZZER_H_

#define ON 1
#define OFF 0

#define C 0
#define Cs 1
#define D 2
#define Ds 3
#define E 4
#define F 5
#define Fs 6
#define G 7
#define Gs 8
#define A 9
#define As 10
#define B 11
#define HC 12

#define PLAY 13
#define REC 14

#define freq_C 262
#define freq_Cs 277
#define freq_D 294
#define freq_Ds 311
#define freq_E 330
#define freq_F 349
#define freq_Fs 370
#define freq_G 392
#define freq_Gs 415
#define freq_A 440
#define freq_As 466
#define freq_B 494
#define freq_HC 523
#define freq_HA 880

void pwm_init (void);
void set_palse_width (const uint32_t new_palse_width);
void set_pwm_period (const uint32_t new_pwm_period);
void set_sound_scale(const uint8_t new_scale);
void limit_sound(void);
void buzzer_on (void);
void buzzer_off (void);
void update_buzzer_status (void);

#endif
