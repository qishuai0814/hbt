#ifndef __HBT_HEX2BIN_H
#define __HBT_HEX2BIN_H

#include "main.h"



#define HEX2BIN_CHK_OPT_OUT 0x00000001
#define HEX2BIN_CHK_OPT_IN  0x00000002

#define HEX2BIN_CHK_OPT_ALL  (HEX2BIN_CHK_OPT_OUT|HEX2BIN_CHK_OPT_IN)












void hbt_hex2bin_function(int argc, char *argv[]);
void hbt_hex2bin_help(void);


void hex2bin_help_function(char *argv,void *private);
void hex2bin_outpot_function(char *argv,void *private);
void hex2bin_in_function(char *argv,void *private);
void hex2bin_start_function(char *argv,void *private);
void hex2bin_end_function(char *argv,void *private);
void hex2bin_length_function(char *argv,void *private);





#endif
