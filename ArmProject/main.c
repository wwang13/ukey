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
	WORD Len = 32;
	BYTE strOutput[32] = {0};

	
	wErrCode = rsa_pri(0x1111, InOutBuf, dataLen, strOutput,&Len, MODE_DECODE);
	
	wErrCode = rsa_pri(0x1111, strOutput, Len, InOutBuf, &dataLen, MODE_ENCODE);

	return wErrCode;
}
