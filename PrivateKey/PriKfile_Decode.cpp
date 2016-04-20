// PriKfile_Decode.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Dongle_API.h"


int _tmain(int argc, _TCHAR* argv[])
{
	DWORD dwRet = 0;
	int nCount = 0;
	DONGLE_HANDLE hDongle = NULL;

	dwRet = Dongle_Enum(NULL, &nCount);
	printf("Enum %d Dongle ARM. \n", nCount);

	dwRet = Dongle_Open(&hDongle, 0);
	printf("Open Dongle ARM. Return : 0x%08X . \n", dwRet);

	int nInDataLen = 128;
	int nOutDataLen = (128 - 11);
	char Input[128];
	char Output[128];

	FILE* fp = NULL;
	fopen_s(&fp, "output.txt", "rb");
	fread(&Input, 1, 128, fp);
	fclose(fp);
	fp = NULL;

	dwRet = Dongle_RsaPri(hDongle, 0x1111, FLAG_DECODE, (BYTE*)Input, nInDataLen, (BYTE*)Output, &nOutDataLen);
	printf("RSA private key decode. Return: 0x%08X\n", dwRet);

	printf("%s\n", Output);

	char NewOutput[128];

	nInDataLen = (128 - 11);
	nOutDataLen = 128;
	strcat_s(Output, 128, "0000");
	
	dwRet = Dongle_RsaPri(hDongle, 0x1111, FLAG_ENCODE, (BYTE*)Output, nInDataLen, (BYTE*)NewOutput, &nOutDataLen);
	printf("RSA private key encode. Return: 0x%08X\n", dwRet);

	FILE* wfp = NULL;
	fopen_s(&wfp, "D://code//PubK_Encode//PubK_Encode//output.txt", "wb");
	fwrite(&NewOutput, 1, 128, wfp);
	fclose(wfp);
	wfp = NULL;

	dwRet = Dongle_Close(hDongle);
	printf("Close Dongle ARM. Return: 0x%08X\n", dwRet);

	return 0;
}

