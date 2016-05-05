
// GenerateSonDlg.h : 头文件
//

#pragma once
#include "Dongle_API.h"


// CGenerateSonDlg 对话框
class CGenerateSonDlg : public CDialogEx
{
// 构造
public:
	CGenerateSonDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GENERATESON_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString UpdataFilePath;
	CString ISOFilePath;

	afx_msg void OnGenerateSon();

	DONGLE_INFO Dongle_info[32];

	BOOL InitSon();
	BOOL DownloadPackage(DONGLE_HANDLE hDongle, int nCount);
	BOOL GenerateCD();

	afx_msg void OnOpenUpdatafile();
	afx_msg void OnOpenISOFile();
};
