#include "hex.h"

#define HEX_TYPE_DATA_RECORD            0   // Data Record//数据记录
#define HEX_TYPE_END_OF_FILE_RECORD     1   // End of File Record//文件结束记录
#define HEX_TYPE_EXT_SEGMENT_ADDRESS    2   // Extended Segment Address Record//扩展段地址记录
#define HEX_TYPE_START_SEGMENT_ADDRESS  3   // Start Segment Address Record//开始段地址记录
#define HEX_TYPE_EXT_LINEAR_ADDRESS     4   // Extended Linear Address Record//扩展线性地址记录
#define HEX_TYPE_START_LINEAR_ADDRESS   5   // Start Linear Address Record//开始线性地址记录


void init_hex_buffer(hex_file_st *hex)
{
    for (size_t i = 0; i < HEX_FILE_BOLCK_SIZE; i++)
    {
        if (hex->block[i].blk_vaild == 1)
        {
            memset(hex->block[i].data,0,(hex->block[i].length/FILE_BLOCK_SIZE+1)*FILE_BLOCK_SIZE);
            free(hex->block[i].data);
        }
    }
    memset((void *)hex,0,sizeof(hex_file_st));
}


void read_hex_to_buffer(hex_file_st *hex,FILE *fp)
{
    unsigned char raw_data[MAX_LINE_SIZE] = {0};
    hex_st hex_line;
    unsigned char tmpbuf[MAX_LINE_SIZE] = {0};
    unsigned char ch = 0;
    unsigned int cur_block = 0;
    unsigned int extended_segment_address = 0;  // 02
    unsigned int start_segment_address = 0;
    unsigned int extended_linear_address = 0;     // 04 


    init_hex_buffer(hex);

    while(fgets (raw_data, MAX_LINE_SIZE, fp) != NULL)
    {
        sscanf (raw_data, "%c%2x%4x%2x%s",&hex_line.tag,&hex_line.length,&hex_line.address,&hex_line.type,tmpbuf);

        if (hex_line.tag = ':')
        {
            switch (hex_line.type)
            {
            case HEX_TYPE_DATA_RECORD: /* Data record */
            {
                if (hex_line.length == 0)
                {
                    LOG("");
                    break;
                }

                // check address
                if (hex_line.address != hex->block[cur_block].start_address + hex->block[cur_block].length)
                {
                    if (hex->block[cur_block].blk_vaild == 1)
                    {
                        cur_block++;
                    }
                    hex->block[cur_block].start_address = extended_linear_address + extended_segment_address + hex_line.address;
                    hex->block[cur_block].blk_vaild = 1;
                    hex->block[cur_block].length = 0;
                }

                // check chk
                unsigned int chk = 0;
                for (size_t i = 0; i < hex_line.length + 5; i++)
                {
                    sscanf (raw_data + 1 + i * 2, "%2x",&ch);
                    chk += ch;
                }
                if ((chk % 100) != 0)
                {
                    LOG("chk error");
                    return;
                }
                
                // check buffer
                if ((hex->block[cur_block].length == 0) || (hex->block[cur_block].data == NULL))
                {
                    hex->block[cur_block].data = malloc(FILE_BLOCK_SIZE);
                    if (hex->block[cur_block].data == NULL)
                    {
                        LOG("malloc error");
                        return;
                    }
                }
                else if ((hex->block[cur_block].length % FILE_BLOCK_SIZE + hex_line.length) > FILE_BLOCK_SIZE)
                {
                    unsigned char *p = hex->block[cur_block].data;
                    unsigned int realloc_length = ((hex->block[cur_block].length -1 ) / FILE_BLOCK_SIZE + 2) * FILE_BLOCK_SIZE;

                    hex->block[cur_block].data = realloc(p, realloc_length);
                    if (hex->block[cur_block].data == NULL)
                    {
                        LOG("realloc error");
                        return;
                    }
                }
                else
                {
                }

                // copy hex data to buffer
                for (size_t i = 0; i < hex_line.length; i++)
                {
                    sscanf (tmpbuf + i * 2, "%2x",&ch);
                    hex->block[cur_block].data[hex->block[cur_block].length++] = ch;
                }
            }
                break;
            case HEX_TYPE_END_OF_FILE_RECORD:
            {
                for (size_t i = 0; i < HEX_FILE_BOLCK_SIZE; i++)
                {
                    if (hex->block[cur_block].blk_vaild == 1)
                    {
                        hex->size += hex->block[cur_block].length;

                        printf("block %2d: start %08x  length %d\r\n",cur_block,hex->block[cur_block].start_address,hex->block[cur_block].length);

                    }
                }
                
                LOG("hex file parse end");
            }
            break;

            case HEX_TYPE_EXT_SEGMENT_ADDRESS:
            {
                if (hex_line.length != 2)
                {
                    LOG("");
                    break;
                }

                // cal address
                unsigned int start_address = 0;
                sscanf (tmpbuf, "%2x",&ch);
                start_address = ch << 12;
                sscanf (tmpbuf + 2, "%2x",&ch);
                start_address |= ch << 4;

                extended_segment_address = start_address;

                if (hex->block[cur_block].blk_vaild == 1)
                {
                    cur_block++;
                }
                hex->block[cur_block].start_address = extended_linear_address + extended_segment_address;
                hex->block[cur_block].blk_vaild = 1;
                hex->block[cur_block].length = 0;
            }
            break;

            case HEX_TYPE_START_SEGMENT_ADDRESS:
            {

            }
            break;

            case HEX_TYPE_EXT_LINEAR_ADDRESS:
            {
                if (hex_line.length != 2)
                {
                    LOG("");
                    break;
                }

                // cal address
                unsigned int start_address = 0;
                sscanf (tmpbuf, "%2x",&ch);
                start_address = ch << 24;
                sscanf (tmpbuf + 2, "%2x",&ch);
                start_address |= ch << 16;

                extended_linear_address = start_address;

                if (hex->block[cur_block].blk_vaild == 1)
                {
                    cur_block++;
                }
                hex->block[cur_block].start_address = extended_linear_address + extended_segment_address;
                hex->block[cur_block].blk_vaild = 1;
                hex->block[cur_block].length = 0;
            }
            break;

            case HEX_TYPE_START_LINEAR_ADDRESS:
            {

            }
            break;
            
            default:
            {

            }
                break;
            }
        }
        
    }

}

