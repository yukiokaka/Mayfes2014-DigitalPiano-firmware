#ifndef _MAIN_H_
#define _MAIN_H_

#define NORMAL_MODE 0 /* 通常モード */
#define REC_MODE 1 /* 録音モード */
#define PLAY_MODE 2 /* 再生モード */
#define LIMIT_MODE 3 /* 録音限界(通常操作は禁止しておく) */

#define REC_LIMIT 99

int main (void);
void SysTick_Handler (void);

#endif
