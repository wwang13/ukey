// ListFile.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Dongle_API.h"

int _tmain(int argc, _TCHAR* argv[])
{
	DWORD dwRet = 0;
	int nCount = 0;
	char AdminPin[32] = "FFFFFFFFFFFFFFFF"/*"6A4B33FFBE1B9CC3"*/;
	int KeyLen = 32;
	int nRemainCount = 255;

	DONGLE_HANDLE hDongle = NULL;

	dwRet = Dongle_Enum(NULL, &nCount);
	printf("Enum %d Dongle ARM. \n", nCount);

	dwRet = Dongle_Open(&hDongle, 0);
	printf("Open Dongle ARM. Return : 0x%08X . \n", dwRet);

	Dongle_VerifyPIN(hDongle, FLAG_ADMINPIN, AdminPin, &nRemainCount);

	printf("Please select file style you want to Query :\n");
	printf("DATA_FILE = 1\n");
	printf("EXE_FILE = 2\n");
	printf("RSA_PRIKEY_FILE = 3\n");
	printf("KEY_FILE = 4\n");
	printf("ECCSM2_PRIKEY_FILE = 5\n");
	printf("Your Input:  ");

	int type = 0;
	scanf_s("%d", &type);
	int dataLen = 0;
	int count = 0;
	EXE_FILE_LIST exe_list[64] = { 0 };
	DATA_FILE_LIST data_file_list[32] = { 0 };
	PRIKEY_FILE_LIST RSA_prikey_list[8] = { 0 };
	PRIKEY_FILE_LIST ECCSM2_prikey_list[16] = { 0 };
	KEY_FILE_LIST keyFile_list[32] = { 0 };

	printf("------------------------------------\n");

	switch (type)
	{
	case 1:
		dataLen = 48 * sizeof(DATA_FILE_LIST);
		dwRet = Dongle_ListFile(hDongle, FILE_DATA, (void*)data_file_list, &dataLen);
		count = dataLen / sizeof(DATA_FILE_LIST);

		if (dwRet == 0xF000000F)
			printf("No file \n");
		else
		{
			printf("This is %d Data File\n", count);
			for (int i = 0; i < count; i++)
			{
				printf("File  %d  ID is 0x%04X, Size is %d\n", i + 1, data_file_list[i].m_FILEID, data_file_list[i].m_attr.m_Size);
			}
		}
		break;
	case 2:
		dataLen = 64 * sizeof(EXE_FILE_LIST);
		dwRet = Dongle_ListFile(hDongle, FILE_EXE, (void*)exe_list, &dataLen);
		count = dataLen / sizeof(EXE_FILE_LIST);

		if (dwRet == 0xF000000F)
			printf("No file \n");
		else
		{
			printf("This is %d EXE File\n", count);
			for (int i = 0; i < count; i++)
			{
				printf("File  %d  ID is 0x%04X, file length is %d\n", i + 1, exe_list[i].m_FILEID, exe_list[i].m_attr.m_Len);
			}
		}
		break;
	case 3:
		dataLen = 8 * sizeof(PRIKEY_FILE_LIST);
		dwRet = Dongle_ListFile(hDongle, FILE_PRIKEY_RSA, (void*)RSA_prikey_list, &dataLen);
		count = dataLen / sizeof(PRIKEY_FILE_LIST);
		if (dwRet == 0xF000000F)
			printf("No file \n");
		else
		{
			printf("This is %d RSA File\n", count);
			for (int i = 0; i < count; i++)
			{
				printf("File  %d  ID is 0x%04X, Size is %d\n", i + 1, RSA_prikey_list[i].m_FILEID, RSA_prikey_list[i].m_attr.m_Size);
			}
		}
		break;
	case 4:
		dataLen = 32 * sizeof(KEY_FILE_LIST);
		dwRet = Dongle_ListFile(hDongle, FILE_KEY, (void*)keyFile_list, &dataLen);
		count = dataLen / sizeof(KEY_FILE_LIST);

		if (dwRet == 0xF000000F)
			printf("No file \n");
		else
		{
			printf("This is %d 3DES/SM4 File\n", count);
			for (int i = 0; i < count; i++)
			{
				printf("File  %d  ID is 0x%04X, Size is %d\n", i + 1, keyFile_list[i].m_FILEID, keyFile_list[i].m_attr.m_Size);
			}
		}
		break;
	case 5:
		dataLen = 16 * sizeof(PRIKEY_FILE_LIST);
		dwRet = Dongle_ListFile(hDongle, FILE_PRIKEY_ECCSM2, (void*)ECCSM2_prikey_list, &dataLen);
		count = dataLen / sizeof(PRIKEY_FILE_LIST);
		if (dwRet == 0xF000000F)
			printf("No file \n");
		else
		{
			printf("This is %d ECCSM2 File\n", count);
			for (int i = 0; i < count; i++)
			{
				printf("File  %d  ID is 0x%04X, Size is %d\n", i + 1, ECCSM2_prikey_list[i].m_FILEID, ECCSM2_prikey_list[i].m_attr.m_Size);
			}
		}
		break;
	default:
		break;
	}
	printf("------------------------------------\n");
	dwRet = Dongle_Close(hDongle);
	printf("Close Dongle ARM. Return: 0x%08X\n", dwRet);

	return 0;
}


