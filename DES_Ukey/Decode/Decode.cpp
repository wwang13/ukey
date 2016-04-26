// Decode.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Dongle_API.h"

int _tmain(int argc, _TCHAR* argv[])
{
	int nCount = 0;
	DWORD dwRet = 0;
	DONGLE_HANDLE hDongle = NULL;

	dwRet = Dongle_Enum(NULL, &nCount);
	printf("Enum %d Dongle ARM. \n", nCount);

	dwRet = Dongle_Open(&hDongle, 0);
	printf("Open Dongle ARM. Return : 0x%08X . \n", dwRet);

	char strInput[512] = { 0 };
	BYTE strOutput[512] = { 0 };
	printf("Please Input no more than (512 - 5) word:\n");
	scanf_s("%s", strInput, 512);
	dwRet = Dongle_TDES(hDongle, 0x1122, FLAG_ENCODE, (BYTE*)strInput, strOutput, 512);
	printf("3DES encode. Return: 0x%08X\n", dwRet);

	dwRet = Dongle_RunExeFile(hDongle, 0x4321, strOutput, 512, NULL);

	BYTE strOut[512] = { 0 };
	dwRet = Dongle_TDES(hDongle, 0x1122, FLAG_DECODE, strOutput, strOut, 512);
	printf("3DES decode. Return: 0x%08X\n", dwRet);
	printf("%s\n", strOut);

	dwRet = Dongle_Close(hDongle);
	printf("Close Dongle ARM. Return: 0x%08X\n", dwRet);
	return 0;
}

