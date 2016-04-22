#include "math.h"
#include "string.h"
#include "stdlib.h"
#include "absacc.h"
#include "ftrx.h"

/************************************************
*全局变量:  本程序中使用的变量,不支持定义时初始化,需在主函数中初始化.
************************************************/
//输入输出缓冲区
extern unsigned char InOutBuf[0x400];
//扩展缓冲区
extern unsigned char ExtendBuf[0x400];


/************************************************
*主函数:  程序入口. 
************************************************/
int main(void)
{	

	WORD wErrCode = 0;
	
	WORD dataLen = 128;
	WORD Len = 117;
	BYTE strOutput[117] = {0};
	BYTE strOInput[117] = {0};
	char temp[117] = {0};
	char* strTemp1 = (char*)malloc(117);
	char* strTemp2 = strTemp1;
	char* tag = "0000";
	int i = 0;
	int size = 0;
	wErrCode = rsa_pri(0x1111, InOutBuf, dataLen, strOutput,&Len, MODE_DECODE);
	
	while (strOutput[i++] != 0)
	{
		size++;
	}
	memcpy(temp, strOutput, size);
	for(i = 0; i < size + 4;i++)
	{
		if(i < size)
		{
			*strTemp1++ = temp[i];
		}
		else{
			*strTemp1++ = *tag++;
		}
	}
	
	memcpy(strOInput, strTemp2,size + 4);
	
	wErrCode = rsa_pri(0x1111, strOInput, Len, InOutBuf, &dataLen, MODE_ENCODE);

	return wErrCode;
}
