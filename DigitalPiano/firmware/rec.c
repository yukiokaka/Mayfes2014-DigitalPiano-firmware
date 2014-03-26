#include "LPC11xx.h"		/* LPC11xx register definitions */
#include "system_LPC11xx.h"
#include "buzzer.h"
#include "flash_nvol.h"

#define NVOL_VAR_DEVINDEX 0

uint8_t get_rec_data(short* rec_length, short melody_list[])
{
    /* 初回使用時にflashからロードする。 */
    short data;
    int i;
    if(NVOL_GetVariable(NVOL_VAR_DEVINDEX, (UNSIGNED8*)rec_length, 2) == FALSE) {
        *rec_length = 0;
    }
    
    for(i = 0;i < *rec_length; i++) {
        /* flashからロード */
        if(NVOL_GetVariable(NVOL_VAR_DEVINDEX + i + 1, (UNSIGNED8*)&data, 2) == FALSE) {
            /* 読み取り失敗。 */
        }
        else {
            melody_list[i] = data;
        }
    }

    return 0;
}

int set_rec_data(short *display_data, int size, int row)
{

    if(NVOL_SetVariable(NVOL_VAR_DEVINDEX+row, (UNSIGNED8*)display_data, size) == FALSE) {
        /* fail */
        return 0;
    }
    /* suceed */
    return 1;
}
