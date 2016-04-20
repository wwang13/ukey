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
	printf("Open Dongle ARM. Return : 0x%08X . \n", dwRet);

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

	char strInput[128];
	char strOutPut[128];
	int nInDataLen = 128 - 11;
	int nOutDataLen = 128;

	printf("Please enter no more than 128 string:");
	scanf_s("%s", &strInput, nInDataLen);

	dwRet = Dongle_RsaPub(hDongle, FLAG_ENCODE, &rsaPub, (BYTE*)strInput, nInDataLen, (BYTE*)strOutPut, &nOutDataLen);
	printf("RSA public key encode. Return: 0x%08X\n", dwRet);

	char str[32] = "1234";
	dwRet = Dongle_WriteShareMemory(hDongle, (BYTE*)str, 32);
	printf("write to share Memory.  Retrun: 0x%08X\n", dwRet);


	BYTE pData[32];
	dwRet = Dongle_ReadShareMemory(hDongle, pData);
	printf("%s\n", pData);


	FILE* wfp = NULL;
	fopen_s(&wfp, "D://code//PubK_Encode//PriKfile_Decode//output.txt", "wb");
	fwrite(&strOutPut, 1, 128, wfp);
	fclose(wfp);
	
	char NewInput[128];
	char NewOutput[128];
	fopen_s(&wfp, "D://code//PubK_Encode//PubK_Encode//output.txt", "rb");
	fread(&NewInput, 1, 128, wfp);
	fclose(wfp);
	wfp = NULL;

	nInDataLen = 128;
	nOutDataLen = (128 - 11);
	dwRet = Dongle_RsaPub(hDongle, FLAG_DECODE, &rsaPub, (BYTE*)NewInput, nInDataLen, (BYTE*)NewOutput, &nOutDataLen);
	printf("RSA public key decode. Return: 0x%08X\n", dwRet);
	printf("the return new data is: %s\n", NewOutput);

	dwRet = Dongle_Close(hDongle);
	printf("Close Dongle ARM. Return: 0x%08X\n", dwRet);

	return 0;
}

