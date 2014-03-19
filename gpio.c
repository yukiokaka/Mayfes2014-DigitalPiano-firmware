#include "LPC11xx.h"		/* LPC11xx register definitions */
#include "system_LPC11xx.h"
#include "gpio.h"

#define _BV(x) (1 << (x))

/*
   スイッチの状態を保存しておく変数
   スイッチが押されていると0、押されていないと1
   10ms周期で更新
*/
static volatile uint32_t switch_status = 0;

void update_switch_status (void)
{
    switch_status = 
        (((LPC_GPIO0->MASKED_ACCESS[1 << 2]>>2  & 0x1) <<  0)| /* C */
        ((LPC_GPIO0->MASKED_ACCESS[1 <<  3]>>3  & 0x1) <<  1) | /* C# */
        ((LPC_GPIO0->MASKED_ACCESS[1 <<  4]>>4  & 0x1) <<  2) | /* D */
        ((LPC_GPIO0->MASKED_ACCESS[1 <<  7]>>7  & 0x1) <<  3) | /* D# */
        ((LPC_GPIO0->MASKED_ACCESS[1 << 11]>>11  & 0x1) <<  4) | /* E */
        ((LPC_GPIO0->MASKED_ACCESS[1 << 10]>>10  & 0x1) <<  5) | /* F */
        ((LPC_GPIO0->MASKED_ACCESS[1 <<  9]>>9  & 0x1) <<  6) | /* F# */
        ((LPC_GPIO0->MASKED_ACCESS[1 <<  8]>>8  & 0x1) <<  7) | /* G */
        ((LPC_GPIO0->MASKED_ACCESS[1 <<  5]>>5  & 0x1) <<  8) | /* G# */
        ((LPC_GPIO0->MASKED_ACCESS[1 <<  6]>>6  & 0x1) <<  9) | /* A */
        ((LPC_GPIO1->MASKED_ACCESS[1 <<  0]>>0  & 0x1) << 10) | /* A# */
        ((LPC_GPIO1->MASKED_ACCESS[1 <<  4]>>4  & 0x1) << 11) | /* B */
        ((LPC_GPIO1->MASKED_ACCESS[1 <<  5]>>5  & 0x1) << 12) | /* C^ */
        ((LPC_GPIO1->MASKED_ACCESS[1 <<  8]>>8  & 0x1) << 13) | /* PLAY */
         ((LPC_GPIO1->MASKED_ACCESS[1 <<  9]>>9& 0x1) << 14)) ; /* REC */
}

uint32_t get_switch_status (void) 
{
    return (~switch_status & 0x7FFF);
}
