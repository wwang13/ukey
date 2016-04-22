// pro_RSAKey.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdio.h"
#include "Dongle_API.h"

int _tmain(int argc, _TCHAR* argv[])
{
	DWORD dwRet = 0;
	int nCount = 0;
	int i = 0;
	char AdminPin[32] = { 0 };
	int KeyLen = 32;
	int nRemainCount = 255;

	DONGLE_HANDLE hDongle = NULL;
	RSA_PUBLIC_KEY  rsaPub;
	RSA_PRIVATE_KEY rsaPri;
	PRIKEY_FILE_ATTR priAttr;
	WORD wPriID = 0x1111;

	printf("Please Input AdminPin:");
	scanf_s("%s", &AdminPin, KeyLen);

	dwRet = Dongle_Enum(NULL, &nCount);
	printf("Enum %d Dongle ARM. \n", nCount);

	dwRet = Dongle_Open(&hDongle, 0);
	printf("Open Dongle ARM. Return : 0x%08X . \n", dwRet);

	dwRet = Dongle_VerifyPIN(hDongle, FLAG_ADMINPIN, AdminPin, &nRemainCount);
	if (dwRet != DONGLE_SUCCESS)
	{
		printf("Verify Admin PIN. failure Return: 0x%08X\n", dwRet);
		return 0;
	}
		
	priAttr.m_Size = 1024;
	priAttr.m_Type = FILE_PRIKEY_RSA;
	priAttr.m_Lic.m_Count = 0xFFFFFFFF;
	priAttr.m_Lic.m_IsDecOnRAM = FALSE;
	priAttr.m_Lic.m_IsReset = FALSE;
	priAttr.m_Lic.m_Priv = 2;

	dwRet = Dongle_CreateFile(hDongle, FILE_PRIKEY_RSA, wPriID, (void*)&priAttr);
	printf("Create RSA private key file. Return: 0x%08X\n", dwRet);
	if (DONGLE_SUCCESS != dwRet)
	{
		printf("RSA pri_key file is existing!\n");
	}

	dwRet = Dongle_RsaGenPubPriKey(hDongle, wPriID, &rsaPub, &rsaPri);
	printf("Gen RSA Public key and private key. Return: 0x%08X\n", dwRet);
	if (DONGLE_SUCCESS != dwRet)
	{
		printf("RSA pri_key and pub_key is existing!\n");
	}

	FILE* fp = NULL;
	fopen_s(&fp, "D://code//ukey//PublicKey//1111.Rsapub", "wb");
	fwrite(&rsaPub, 1, sizeof(RSA_PUBLIC_KEY), fp);
	fclose(fp);
	fp = NULL;

	dwRet = Dongle_Close(hDongle);
	printf("Close Dongle ARM. Return: 0x%08X\n", dwRet);


	return 0;
}

