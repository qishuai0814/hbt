
#include "hex2bin.h"


static unsigned int check_option = 0;


static cmd_st hex2bin_cmd_table[] = 
{
    {"-help",           0,  hex2bin_help_function,              "hex2bin help"},
    {"-output",         1,  hex2bin_outpot_function,            "out <filename.hex>,This option is mandatory"},
    {"-input",          1,  hex2bin_in_function,                "in <filename.hex>,This option is mandatory"},
    {"-start",          1,  hex2bin_start_function,             "start <start address>"},
    {"-end",            1,  hex2bin_end_function,               "start <end address>"},
    {"-length",         1,  hex2bin_length_function,            "length <length of bin file>"},
};




void hbt_hex2bin_function(int argc, char *argv[])
{
    cmd_st *cmd = NULL;
    unsigned int index = 0;
    static FILE     *in_file,             /* input files */
                *out_file;            /* output files */
    
    hex_file_st hex = {0};
    unsigned char *out_file_name[1024];

    init_hex_buffer(&hex);

    if (argc == 0)
    {
        hbt_hex2bin_help();
        return ;
    }

    // tets ---------------------------
    for (size_t i = 0; i < argc; i++)
    {
        printf("argv[%d] %s\r\n",i,argv[i]);
    }
    // tets ---------------------------

    check_option = 0;
    while (argc > index)
    {
        cmd = get_cmd(hex2bin_cmd_table,sizeof(hex2bin_cmd_table)/sizeof(cmd_st),argv[index]);
        if(NULL != cmd)
        {
            printf("hex2bin execute command [%s]\r\n",cmd->cmd);
            cmd->cmd_function(argv[index + 1],(void *)&hex);

            if (cmd->has_argv)
            {
                index++;
            }
        }else
        {
            printf("hex2bin invalid command [%s]\r\n",argv[index]);
            hbt_hex2bin_help();
            break;
        }

        index++;
    }
    
    // check argv
    if ((check_option & HEX2BIN_CHK_OPT_ALL) != HEX2BIN_CHK_OPT_ALL)
    {
        printf("hex2bin missing parameter\r\n");
        return ;
    }

    LOG("%s",hex.file_name);
    // open
    in_file = fopen((const char *)hex.file_name,"r");
    if (in_file == NULL)
    {
        printf("--input: can't open file [%s]\r\n",hex.file_name);
        return ;
    }

    LOG("%s",out_file_name);
    // open
    out_file = fopen((const char *)out_file_name,"r");
    if (out_file == NULL)
    {
        fclose(in_file);

        printf("--output: can't open file [%s]\r\n",out_file_name);
        return ;
    }



    
    fclose(in_file);
    fclose(out_file);
    
    init_hex_buffer(&hex);

}

void hbt_hex2bin_help(void)
{
    cmd_help(hex2bin_cmd_table,sizeof(hex2bin_cmd_table)/sizeof(cmd_st));
}


void hex2bin_help_function(char *argv,void *private)
{
    cmd_help(hex2bin_cmd_table,sizeof(hex2bin_cmd_table)/sizeof(cmd_st));
}

void hex2bin_outpot_function(char *argv,void *private)
{
    // memset(out_file_name, '\0', sizeof(out_file_name));
    // strcpy((char *)out_file_name,argv); 
    check_option |= HEX2BIN_CHK_OPT_OUT;
    LOG("");
}


void hex2bin_in_function(char *argv,void *private)
{
    hex_file_st *hex = (hex_file_st *)private;

    memset(hex->file_name, '\0', FILE_NAME_SIZE);
    strcpy((char *)hex->file_name,argv); 

    check_option |= HEX2BIN_CHK_OPT_IN;
    LOG("");
}


void hex2bin_start_function(char *argv,void *private)
{

    printf("hex2bin_start_function \r\n");
    
}


void hex2bin_end_function(char *argv,void *private)
{

    printf("hex2bin_end_function \r\n");
    
}


void hex2bin_length_function(char *argv,void *private)
{

    printf("hex2bin_length_function \r\n");
    
}






