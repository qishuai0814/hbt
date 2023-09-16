#ifndef __HBT_HEX_H
#define __HBT_HEX_H

#include "main.h"

#define HEX_FILE_BOLCK_SIZE 100

#define FILE_NAME_SIZE 1024

#define MAX_LINE_SIZE 1024

#define FILE_BLOCK_SIZE 1024



typedef struct _st_block
{
    unsigned int start_address; // 物理地址
    unsigned int length;
    unsigned char blk_vaild;    // 0: unused  1: used
    unsigned char *data;    // malloc
}block_st;

typedef struct _st_hex
{
    char tag;   // :
    unsigned char length;    // 当前行 有效数据的长度
    unsigned int address;    // 当前行 起始地址
    unsigned char type;    // 当前行 数据类型
    unsigned char chk;    // 当前行 校验和
}hex_st;


typedef struct _st_hex_file
{
    block_st block[HEX_FILE_BOLCK_SIZE];
    unsigned char file_name[FILE_NAME_SIZE];
    unsigned int size;
}hex_file_st;




void init_hex_buffer(hex_file_st *hex);




#endif

