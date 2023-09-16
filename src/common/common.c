#include "common.h"



void read_line(char* str,FILE *in)
{
    char *result;

    result = fgets(str,MAX_LINE_SIZE,in);
    if ((result == NULL) && !feof (in)) fprintf(stderr,"Error occurred while reading from file\n");
}


void log_printf(const char *fmt, ...)
{
    va_list args;
    va_start(args,fmt);//���������ݲ��� fmt �ĵ�ַ����ȡ fmt ��������ĵ�ַ���������� args ָ������С�
    vprintf(fmt,args);//��ӡ��������ı���б�ֱ�Ӵ��ݸ� vprintf ������ʵ�ִ�ӡ���ܡ�
    va_end(args);//�ͷţ��ͷ� args ָ�룬
}



