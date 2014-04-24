#ifndef _MAIN_H_
#define _MAIN_H_

#define NORMAL_MODE 0 /* 通常モード */
#define REC_MODE 1 /* 録音モード */
#define PLAY_MODE 2 /* 再生モード */
#define LIMIT_MODE 3 /* 録音限界(通常操作は禁止しておく) */
#define STANDBY_MODE 4 /* 録音準備 */

#define REC_LIMIT 98

int main (void);
void SysTick_Handler (void);

#endif
