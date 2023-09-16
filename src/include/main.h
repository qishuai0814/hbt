#ifndef __HBT_MAIN_H
#define __HBT_MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hex2bin.h"




typedef struct _st_hbt_cmd
{
    unsigned char * name;
    void (*hbt_function)(int argc, char *argv[]);
    void (*hbt_cmd_help)(void);
}hbt_cmd_st;


typedef struct _st_cmd
{
    unsigned char *cmd;
    unsigned char has_argv;     // 0: no argv   1: one argv
    void (*cmd_function)(char *argv);
    unsigned char *help;
}cmd_st;


hbt_cmd_st * get_hbt_cmd(unsigned char * name);
cmd_st * get_cmd(cmd_st *cmd_table,unsigned int size, unsigned char * name);
void cmd_help(cmd_st *cmd_table,unsigned int size);


void hbt_help_function(int argc, char *argv[]);
void hbt_version_function(int argc, char *argv[]);


void hbt_help(void);
void hbt_version_help(void);




#endif