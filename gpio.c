#include "LPC11xx.h"		/* LPC11xx register definitions */
#include "system_LPC11xx.h"
#include "gpio.h"
#include "buzzer.h"

#define _BV(x) (1 << (x))

/*
   スイッチの状態を保存しておく変数
   スイッチが押されていると0、押されていないと1
   10ms周期で更新
*/
static volatile uint16_t switch_status = 0;

void update_switch_status (void)
{
    switch_status = 
        (((LPC_GPIO0->MASKED_ACCESS[1 << 2]>>2  & 0x1) <<  C)| /* C */
         ((LPC_GPIO0->MASKED_ACCESS[1 <<  3]>>3  & 0x1) <<  Cs) | /* C# */
         ((LPC_GPIO0->MASKED_ACCESS[1 <<  4]>>4  & 0x1) <<  D) | /* D */
         ((LPC_GPIO0->MASKED_ACCESS[1 <<  7]>>7  & 0x1) <<  Ds) | /* D# */
         ((LPC_GPIO0->MASKED_ACCESS[1 << 11]>>11  & 0x1) <<  E) | /* E */
         ((LPC_GPIO0->MASKED_ACCESS[1 << 10]>>10  & 0x1) <<  F) | /* F */
         ((LPC_GPIO0->MASKED_ACCESS[1 <<  9]>>9  & 0x1) <<  Fs) | /* F# */
         ((LPC_GPIO0->MASKED_ACCESS[1 <<  8]>>8  & 0x1) <<  G) | /* G */
         ((LPC_GPIO0->MASKED_ACCESS[1 <<  5]>>5  & 0x1) <<  Gs) | /* G# */
         ((LPC_GPIO0->MASKED_ACCESS[1 <<  6]>>6  & 0x1) <<  A) | /* A */
         ((LPC_GPIO1->MASKED_ACCESS[1 <<  0]>>0  & 0x1) << As) | /* A# */
         ((LPC_GPIO1->MASKED_ACCESS[1 <<  4]>>4  & 0x1) << B) | /* B */
         ((LPC_GPIO1->MASKED_ACCESS[1 <<  5]>>5  & 0x1) << HC) | /* C^ */
         ((LPC_GPIO1->MASKED_ACCESS[1 <<  8]>>8  & 0x1) << PLAY) | /* PLAY */
         ((LPC_GPIO1->MASKED_ACCESS[1 <<  9]>>9& 0x1) << REC)) ; /* REC */
}

uint16_t get_switch_status (void) 
{
    return (~switch_status & 0x7FFF);
}
