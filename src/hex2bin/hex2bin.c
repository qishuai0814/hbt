
#include "hex2bin.h"


static cmd_st hex2bin_cmd_table[] = 
{
    {"-help",           0,  hex2bin_help_function,              "hex2bin help"},
    {"-output",         1,  hex2bin_outpot_function,            "out <filename.hex>"},
    {"-in",             1,  hex2bin_in_function,                "in <filename.hex>"},
    {"-start",          1,  hex2bin_start_function,             "start <start address>"},
    {"-end",            1,  hex2bin_end_function,               "start <end address>"},
    {"-length",         1,  hex2bin_length_function,            "length <length of bin file>"},
};



static FILE     *in_file,             /* input files */
                *out_file;            /* output files */


static unsigned char *in_file_name[1024];
static unsigned char *out_file_name[1024];



void hbt_hex2bin_function(int argc, char *argv[])
{
    cmd_st *cmd = NULL;
    unsigned int index = 0;

    if (argc == 0)
    {
        hbt_hex2bin_help();
        return ;
    }

    // tets ---------------------------
    for (size_t i = 0; i < argc; i++)
    {
        printf("argv[%d] %s :\r\n",i,argv[i]);
    }
    // tets ---------------------------


    while (argc > index)
    {
        cmd = get_cmd(hex2bin_cmd_table,sizeof(hex2bin_cmd_table)/sizeof(cmd_st),argv[index]);
        if(NULL != cmd)
        {
            printf("hex2bin execute command [%s]\r\n",cmd->cmd);
            cmd->cmd_function(argv[index + 1]);

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
    

    // open hex file
    while ((in_file = fopen(in_file_name,"r")) == NULL)
    {
    	if (Batch_Mode)
    	{
			fprintf (stderr,"Input file %s cannot be opened.\n", Flnm);
    		exit(1);
    	}
    	else
    	{
			fprintf (stderr,"Input file %s cannot be opened. Enter new filename: ",Flnm);
			if (Flnm[strlen(Flnm) - 1] == '\n') Flnm[strlen(Flnm) - 1] = '\0';
    	}
    }


}

void hbt_hex2bin_help(void)
{
    cmd_help(hex2bin_cmd_table,sizeof(hex2bin_cmd_table)/sizeof(cmd_st));
}


void hex2bin_help_function(char *argv)
{
    cmd_help(hex2bin_cmd_table,sizeof(hex2bin_cmd_table)/sizeof(cmd_st));
}

void hex2bin_outpot_function(char *argv)
{
    memset(out_file_name, '\0', sizeof(out_file_name));
    strcpy(out_file_name,argv); 
}


void hex2bin_in_function(char *argv)
{
    memset(in_file_name, '\0', sizeof(in_file_name));
    strcpy(in_file_name,argv); 
}


void hex2bin_start_function(char *argv)
{

    printf("hex2bin_start_function \r\n");
    
}


void hex2bin_end_function(char *argv)
{

    printf("hex2bin_end_function \r\n");
    
}


void hex2bin_length_function(char *argv)
{

    printf("hex2bin_length_function \r\n");
    
}


