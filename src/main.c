#include "main.h"

#define     HBT_VERSION     "V1.0.0"


static hbt_cmd_st hbt_cmd_table[] = 
{
    {"--help",        hbt_help_function,            hbt_help},
    {"--version",     hbt_version_function,         hbt_version_help},
    {"--hex2bin",     hbt_hex2bin_function,         hbt_hex2bin_help},
};



int main(int argc, char *argv[])
{
    hbt_cmd_st *cmd = NULL;

    if (argc == 1)
    {
        hbt_help_function(0,NULL);
        return 0;
    }

    cmd = get_hbt_cmd(argv[1]);
    if(NULL != cmd)
    {
        printf("Execute command [%s]\r\n",cmd->name);
        cmd->hbt_function(argc-2,&argv[2]);
    }else
    {
        printf("Invalid command [%s]\r\n",argv[1]);
        hbt_help_function(0,NULL);
    }

    return 0;
}





hbt_cmd_st * get_hbt_cmd(unsigned char * name)
{
    hbt_cmd_st *p = NULL;

    for (size_t i = 0; i < sizeof(hbt_cmd_table)/sizeof(hbt_cmd_st); i++)
    {
        if ((strstr(hbt_cmd_table[i].name,name) != NULL))
        {
            p = &hbt_cmd_table[i];
            break;
        }
    }
    return p;
}


cmd_st * get_cmd(cmd_st *cmd_table,unsigned int size, unsigned char * name)
{
    cmd_st *p = NULL;

    for (size_t i = 0; i < size; i++)
    {
        if ((strstr(cmd_table[i].cmd,name) != NULL))
        {
            p = &cmd_table[i];
            break;
        }
    }
    return p;
}

void cmd_help(cmd_st *cmd_table,unsigned int size)
{
    for (size_t i = 0; i < size; i++)
    {
        printf("        %s  %s\r\n",cmd_table[i].cmd,cmd_table[i].help);
    }
}


void hbt_help(void)
{
    printf("        help\r\n");
}

void hbt_help_function(int argc, char *argv[])
{
    for (size_t i = 0; i < sizeof(hbt_cmd_table)/sizeof(hbt_cmd_st); i++)
    {
        printf("    %s\r\n",hbt_cmd_table[i].name);
        hbt_cmd_table[i].hbt_cmd_help();
    }
}

void hbt_version_help(void)
{
    printf("        hbt version %s\r\n",HBT_VERSION);
}

void hbt_version_function(int argc, char *argv[])
{
    hbt_version_help();
}
