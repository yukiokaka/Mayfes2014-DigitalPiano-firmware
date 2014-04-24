#include "LPC11xx.h"		/* LPC11xx register definitions */
#include "system_LPC11xx.h"
#include "buzzer.h"
#include "flash_nvol.h"
#include "xprintf.h"

#define NVOL_VAR_DEVINDEX 0

uint8_t get_rec_data(unsigned char* rec_length, short melody_list[])
{
    /* 初回使用時にflashからロードする。 */
    unsigned char data;
    int i;
    if(NVOL_GetVariable(NVOL_VAR_DEVINDEX, (UNSIGNED8*)rec_length, 1) == FALSE) {
        *rec_length = 0;
    }
    xprintf("length%d\n",*rec_length);
    for(i = 0;i < *rec_length; i++) {
        /* flashからロード */
        if(NVOL_GetVariable(NVOL_VAR_DEVINDEX + i + 1, (UNSIGNED8*)&data, 1) == FALSE) {
            /* 読み取り失敗。 */
            xprintf("get miss %d\n", i);
        }
        else {
            melody_list[i] = (1 << (data - 1));
        }
    }
    xprintf("get finish %d\n", *rec_length);
    return 0;
}

int set_rec_data(short *rec_data, int row)
{
    xprintf("set\n");
    int i;
    unsigned char compress_data;
    if ((*rec_data) == 0) {
        compress_data = 0;
    }   else {
        for (i = C; i <= HC; i++) {
            if ((*rec_data) & (1 << i)) {
                compress_data = (i + 1);
            }
        }
    }
    if(NVOL_SetVariable(NVOL_VAR_DEVINDEX+row, (UNSIGNED8*)&compress_data, 1) == FALSE) {
        /* fail */
        xprintf("set miss %d\n", row);
        return 0;
    }
    /* suceed */
    return 1;
}

int set_rec_length(unsigned char *rec_length, int row)
{
    xprintf("set\n");
    if(NVOL_SetVariable(NVOL_VAR_DEVINDEX+row, (UNSIGNED8*)rec_length, 1) == FALSE) {
        /* fail */
        xprintf("set miss %d\n", row);
        return 0;
    }
    unsigned char tmp;
    NVOL_GetVariable(NVOL_VAR_DEVINDEX, (UNSIGNED8*)&tmp, 1);
    xprintf("set success %d -> %d\n", *rec_length,tmp);
    /* suceed */
    return 1;
}
