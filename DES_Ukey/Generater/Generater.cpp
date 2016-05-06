// Generater.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Dongle_API.h"

int _tmain(int argc, _TCHAR* argv[])
{
	DWORD dwRet = 0;
	int nCount = 0;
	char AdminPin[32] = "6A4B33FFBE1B9CC3";
	int KeyLen = 32;
	int nRemainCount = 255;

	DONGLE_HANDLE hDongle = NULL;
	KEY_FILE_ATTR DESkey;
	WORD KeyID = 0x1122;

	DESkey.m_Size = 16;
	DESkey.m_Lic.m_Priv_Enc = 2;

	dwRet = Dongle_Enum(NULL, &nCount);
	printf("Enum %d Dongle ARM. \n", nCount);

	dwRet = Dongle_Open(&hDongle, 0);
	printf("Open Dongle ARM. Return : 0x%08X . \n", dwRet);

	Dongle_VerifyPIN(hDongle, FLAG_ADMINPIN, AdminPin, &nRemainCount);
//	while (1)
	//{
	//	printf("Please Input Admin PIN:");
	//	scanf_s("%s", AdminPin, KeyLen);
	//	dwRet = Dongle_VerifyPIN(hDongle, FLAG_ADMINPIN, AdminPin, &nRemainCount);
	//	if (dwRet != DONGLE_SUCCESS)
	//	{
	//		printf("Verify Admin PIN. failure Return: 0x%08X\n", dwRet);
	//	}
	//	else
	//	{
	//		printf("Verify Admin PIN. OK Return: 0x%08X\n", dwRet);
	//		break;
	//	}
	//}
	//EXE_FILE_LIST list;
	char strList[200] = { 0 };
	int Leng = 200;
	dwRet = Dongle_ListFile(hDongle, FILE_EXE, strList, &Leng);
	EXE_FILE_LIST* list = NULL;
	list = (EXE_FILE_LIST*)strList;
	printf("%d  0x%08X   %d\n", dwRet,list->m_FILEID, list->m_attr.m_Len);

	BYTE key[16] = { 0 };
	dwRet = Dongle_GenRandom(hDongle, 16, key);

	dwRet = Dongle_CreateFile(hDongle, FILE_KEY, KeyID, (void*)&DESkey);
	printf("Create RSA private key file. Return: 0x%08X\n", dwRet);
	if (DONGLE_SUCCESS != dwRet)
	{
		printf("RSA pri_key file is existing!\n");
	}

	dwRet = Dongle_WriteFile(hDongle, FILE_KEY, KeyID, 0, key, 16);
	printf("Write 3DES/SM4 key file. Return: 0x%08X\n", dwRet);

	dwRet = Dongle_Close(hDongle);
	printf("Close Dongle ARM. Return: 0x%08X\n", dwRet);

	return 0;
}

