// PubK_Encode.cpp : 定义控制台应用程序的入口点。
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
	printf("Open Dongle ARM. Return : 0x%08X \n", dwRet);

	RSA_PUBLIC_KEY  rsaPub;

	FILE* fp = NULL;
	fopen_s(&fp, "1111.Rsapub", "rb");
	fseek(fp, 0, SEEK_END);
	int file_size;
	file_size = ftell(fp);;
	fseek(fp, 0, SEEK_SET);
	fread(&rsaPub, 1, file_size, fp);
	fclose(fp);
	fp = NULL;

	char strInput[128] = { 0 };
	char strOutPut[128] = { 0 };
	int nInDataLen = 117;
	int nOutDataLen = 128;

	printf("Please enter no more than 113 string:");
	scanf_s("%s", &strInput, nInDataLen);

	dwRet = Dongle_RsaPub(hDongle, FLAG_ENCODE, &rsaPub, (BYTE*)strInput, nInDataLen, (BYTE*)strOutPut, &nOutDataLen);
	printf("RSA public key encode. Return: 0x%08X\n", dwRet);

	dwRet = Dongle_RunExeFile(hDongle, 0x1234, (BYTE*)strOutPut, nOutDataLen, NULL);
	printf("0x%08X\n", dwRet);

	char str[128] = { 0 };
	int datalen = 117;
	dwRet = Dongle_RsaPub(hDongle, FLAG_DECODE, &rsaPub, (BYTE*)strOutPut, nOutDataLen, (BYTE*)str, &datalen);
	printf("0x%08X\n", dwRet);
	printf("%s\n", str);

	dwRet = Dongle_Close(hDongle);
	printf("Close Dongle ARM. Return: 0x%08X\n", dwRet);

	return 0;
}

