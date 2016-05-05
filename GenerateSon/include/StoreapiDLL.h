/*********************************************************************************************
Module StoreAPIDLL.h
*********************************************************************************************/
#ifndef _STOREAPIDLL_H_
#define _STOREAPIDLL_H_
#ifndef STOREAPIDLL_EXPORTS
#define STOREAPIDLL_API __declspec(dllimport)
#else
#define STOREAPIDLL_API __declspec(dllexport)
#endif

/*********************************************************************************************
Define error code
*********************************************************************************************/
#define ST_ERR_PARAMENTS					-1	//参数错误
#define ST_ERR_FAILED						-2	//操作失败
#define ST_ERR_SUCCESS						1	//成功
#define ST_ERR_FILE_OPEN_FAILED				15	//文件无法打开
#define ST_ERR_MODE_NOT_SUPPORT				16	//不支持的模式
#define ST_ERR_OPENDISK_FAIL				17	//无法打开磁盘
#define ST_ERR_HIDDENSIZE_OVER				18	//隐藏区容量太大

#define WM_READ_SUCCESS						WM_USER+601
#define WM_READ_FAIL						WM_USER+602
#define WM_WRITE_SUCCESS					WM_USER+603
#define WM_WRITE_FAIL						WM_USER+604
#define WM_DELETE_SUCCESS					WM_USER+605
#define WM_DELETE_FAIL						WM_USER+606
#define WM_WRITECD_SUCCESS					WM_USER+607
#define WM_WRITECD_FAIL						WM_USER+608
#define WM_OPENHANDLE_FAIL					WM_USER+609
#define WM_PROGRESS							WM_USER+610
#define WM_REMOVALREFRESHOK					WM_USER+611
/*********************************************************************************************
Include
*********************************************************************************************/
#include <stdio.h>
#include <Afxwin.h>
/*********************************************************************************************
Global variables declare
*********************************************************************************************/
CHAR g_PartLetters[3]={0};
/*********************************************************************************************
Function declare
*********************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////////////////
//int ST_GetDiskLetter
//说明:获取插入当前PC端的各个分区的盘符
//参数：CHAR* PartLetters,返回获取到的分区,分区盘符以分号区分,同一个分号区间内的是
//参数：同一个硬件上的分区,如“H;IJ”，表示H和IJ属于两个不同的硬件
//返回值：-1表示参数错误，其他代表找到的可移动分区个数
STOREAPIDLL_API int __stdcall ST_GetDiskLetter(CHAR*PartLetters);

//////////////////////////////////////////////////////////////////////////////////////////////
//int __stdcall ST_GetDiskCurrentState
//说明:获取插入指定硬件的分区模式和各个分区的容量
//参数：DWORD *dwTotalSize 硬件总容量,DWORD *dwPubSize U盘容量, DWORD *dwSecSize密码区容量
//参数：DWORD *dwCdromSize CDROM容量,DWORD *dwHiddenSize 隐藏区容量,
//参数：CHAR cDiskLetter 指定的硬件盘符
//返回值：-1表示参数错误，其他代表分区模式
STOREAPIDLL_API int __stdcall ST_GetDiskCurrentState	(DWORD *dwTotalSize,DWORD *dwPubSize,
					DWORD *dwCdromSize,DWORD *dwSecSize,DWORD *dwHiddenSize ,CHAR cDiskLetter);
//////////////////////////////////////////////////////////////////////////////////////////////
//int __stdcall ST_SetDiskCurrentState
//说明:按照指定模式，指定分区容量重新分区
//参数：DWORD dwPubSize U盘容量, DWORD dwSecSize密码区容量,DWORD dwCdromSize CDROM容量,DWORD dwHiddenSize 隐藏区容量,
//参数：int nCurrentMode 指定的分区模式,CHAR cDiskLetter 指定的硬件盘符;HWND pWnd=NULL，
//参数：指定窗口句柄，接收分区的结果消息，可以为NULL（不建议为null，否则不知道何时分区完成）
//返回值：1表示成功，其他见错误码
STOREAPIDLL_API int __stdcall ST_SetDiskCurrentState(DWORD dwPubSize , DWORD dwCdromSize,
			DWORD dwSecSize,DWORD dwHiddenSize, int nCurrentMode,CHAR cDiskLetter,HWND pWnd=NULL);
//////////////////////////////////////////////////////////////////////////////////////////////
//BOOL __stdcall ST_WriteHidderArea
//说明:向隐藏区写入数据
//参数：CHAR cDiskLetter 指定的硬件盘符;DWORD dwOffsetLun,写数据的起始扇区；
//参数：DWORD dwLunCounts需要写入的扇区数;BYTE *Buf,带写入数据
//返回值：1表示成功，0表示失败
STOREAPIDLL_API BOOL __stdcall ST_WriteHidderArea(CHAR cDiskLetter,DWORD dwOffsetLun,
																DWORD dwLunCounts,BYTE *Buf);
//////////////////////////////////////////////////////////////////////////////////////////////
//BOOL __stdcall ST_ReadHidderArea
//说明:读取隐藏区数据
//参数：CHAR cDiskLetter 指定的硬件盘符;DWORD dwOffsetLun,读取数据的起始扇区；
//参数：DWORD dwLunCounts需要读取的扇区数;BYTE *Buf,接收数据的缓冲区
//返回值：1表示成功，0表示失败
STOREAPIDLL_API BOOL __stdcall ST_ReadHidderArea(CHAR cDiskLetter,DWORD dwOffsetLun,
													 DWORD dwLunCounts,BYTE *Buf);
//////////////////////////////////////////////////////////////////////////////////////////////
//int __stdcall ST_DownladTOCDROM
//说明:想CDROM区载入ISO文件
//参数：CHAR *FilePathName,ISO文件的镜像;CHAR cDiskLetter 指定的硬件盘符;CWnd* pWnd = NULL，
//参数：指定窗口类，接收ISO的结果消息，可以为NULL（不建议为null，否则不知道何时载入ISO完成）
//返回值：1表示成功，其他见错误码
STOREAPIDLL_API int __stdcall ST_DownladTOCDROM(CHAR *FilePathName, CHAR cDiskLetter,
																			CWnd* pWnd = NULL);
//////////////////////////////////////////////////////////////////////////////////////////////
//BOOL __stdcall ST_GetSerialNumber
//说明:获取硬件序列号
//参数：CHAR cDiskLetter 指定的硬件盘符;CHAR *cSN,接收数据的缓冲区
//返回值：1表示成功，0表示失败
STOREAPIDLL_API BOOL __stdcall ST_GetSerialNumber(CHAR cDiskLetter,CHAR *cSN);
//////////////////////////////////////////////////////////////////////////////////////////////
//BOOL __stdcall ST_GetPidAndVid
//说明:获取硬件VID和PID
//参数：CHAR cDiskLetter 指定的硬件盘符;WORD *wVID,VID;WORD *wPID,PID
//返回值：1表示成功，0表示失败
STOREAPIDLL_API BOOL __stdcall ST_GetPidAndVid(CHAR cDiskLetter,WORD *wVID , WORD *wPID);
#endif