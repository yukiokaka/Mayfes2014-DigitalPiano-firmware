#ifndef _REC_H_
#define _REC_H_

uint8_t get_rec_data(unsigned char* rec_length, short melody_list[]);
int set_rec_data(short* display_data, int row);
int set_rec_length(unsigned char *rec_length, int row);
#endif
