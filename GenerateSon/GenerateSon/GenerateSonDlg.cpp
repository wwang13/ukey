
// GenerateSonDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GenerateSon.h"
#include "GenerateSonDlg.h"
#include "afxdialogex.h"
#include "StoreapiDLL.h"
#include "iostream"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
	
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGenerateSonDlg 对话框



CGenerateSonDlg::CGenerateSonDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGenerateSonDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGenerateSonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGenerateSonDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BtGenerateSon, &CGenerateSonDlg::OnGenerateSon)
	ON_BN_CLICKED(IDC_BtOpenFile, &CGenerateSonDlg::OnOpenUpdatafile)
	ON_BN_CLICKED(IDC_BtDownloadCD, &CGenerateSonDlg::OnOpenISOFile)
END_MESSAGE_MAP()


// CGenerateSonDlg 消息处理程序

BOOL CGenerateSonDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGenerateSonDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGenerateSonDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGenerateSonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGenerateSonDlg::OnOpenUpdatafile()
{
	// TODO:  在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE, NULL,
		NULL,
		OFN_FILEMUSTEXIST | OFN_SHAREAWARE | OFN_PATHMUSTEXIST,
		TEXT("(*.RyArmUdp)|*.RyArmUdp|所有文件(*.*)|*.*|"),
		NULL);
	if (dlg.DoModal() == IDOK)
	{
		UpdataFilePath = dlg.GetPathName();
		SetDlgItemText(IDC_Edit_UpdataFile, UpdataFilePath);
	}
}


void CGenerateSonDlg::OnOpenISOFile()
{
	// TODO:  在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE, NULL,
		NULL,
		OFN_FILEMUSTEXIST | OFN_SHAREAWARE | OFN_PATHMUSTEXIST,
		TEXT("(*.iso)|*.iso|所有文件(*.*)|*.*|"),
		NULL);
	if (dlg.DoModal() == IDOK)
	{
		ISOFilePath = dlg.GetPathName();
		SetDlgItemText(IDC_Edit_ISOFile, ISOFilePath);
	}
}


void CGenerateSonDlg::OnGenerateSon()
{
	// TODO:  在此添加控件通知处理程序代码
	SetDlgItemText(IDC_LabUpdata, _T("  "));
	SetDlgItemText(IDC_LabDownload, _T("  "));
	Sleep(300);
	if (InitSon())
	{
		SetDlgItemText(IDC_LabUpdata, _T("Updata Son clok success"));
	}
	else
	{
		SetDlgItemText(IDC_LabUpdata, _T("Updata Son clok Failure"));
	}
	if (GenerateCD())
	{
		SetDlgItemText(IDC_LabDownload, _T("Download ISO file finish"));
	}
	else
	{
		SetDlgItemText(IDC_LabDownload, _T("Download ISO file Failure"));
	}
}


BOOL CGenerateSonDlg::InitSon()
{
	DWORD dwRet = 1;
	int nCount = 0;
	char AdminPin[32] = "FFFFFFFFFFFFFFFF";
	int nRemainCount = 255;

	DONGLE_HANDLE hDongle = NULL;
	DONGLE_HANDLE m_hDongle = NULL;
	
	memset(Dongle_info, 0, 32 * sizeof(DONGLE_INFO));
	dwRet = Dongle_Enum(Dongle_info, &nCount);
//	printf("Enum %d Dongle ARM. \n", nCount);

	BYTE Request[32] = { 0 };
	BYTE InitData[1024] = { 0 };
	int InitDataLeng = 1024;

	for (int i = 0; i < nCount; i++)
	{
		if (Dongle_info[i].m_IsMother == 0x01)
		{
			dwRet = Dongle_Open(&m_hDongle, i);
		}
	}

	for (int j = 0; j < nCount; j++)
	{
		if (Dongle_info[j].m_PID == 0xFFFFFFFF && Dongle_info[j].m_IsMother != 0x01)
		{
			dwRet = Dongle_Open(&hDongle, j);
			dwRet = Dongle_VerifyPIN(hDongle, FLAG_ADMINPIN, AdminPin, &nRemainCount);
			dwRet = Dongle_RequestInit(hDongle, Request);
			dwRet = Dongle_GetInitDataFromMother(m_hDongle, Request, InitData, &InitDataLeng);
			dwRet = Dongle_InitSon(hDongle, InitData, InitDataLeng);
		}
	}
	dwRet = Dongle_Close(m_hDongle);	
	if (dwRet != 0)
		return FALSE;
	else
	{
		if (!DownloadPackage(hDongle, nCount))
			return FALSE;
	}
	return TRUE;
}


BOOL CGenerateSonDlg::DownloadPackage(DONGLE_HANDLE hDongle, int nCount)
{
	DWORD dwRet = 1;

	for (int k = 0; k < nCount; k++)
	{
		if (Dongle_info[k].m_IsMother != 0x01 && Dongle_info[k].m_PID == 0xFFFFFFFF)
		{
			dwRet = Dongle_Open(&hDongle, k);

			char strUpdata[20480] = { 0 };

			std::string strPath = CStringA(UpdataFilePath);
			const char* filePath = strPath.c_str();
			FILE* fp = NULL;
			fopen_s(&fp, filePath, "rb");
			fseek(fp, 0, SEEK_END);
			int file_size;
			file_size = ftell(fp);;
			fseek(fp, 0, SEEK_SET);
			fread(&strUpdata, 1, file_size, fp);
			fclose(fp);
			fp = NULL;

			int size = strlen(strUpdata);
			dwRet = Dongle_Update(hDongle, (BYTE*)strUpdata, file_size);
			Dongle_Close(hDongle);	
		}
	}
	if (dwRet != 0)
		return FALSE;
	else
		return TRUE;
}


BOOL CGenerateSonDlg::GenerateCD()
{
	char cPartLetters[48] = { 0 };

	int nTotalCnt = ST_GetDiskLetter(cPartLetters);
	if (nTotalCnt == ST_ERR_PARAMENTS)
	{
		AfxMessageBox(_T("parameter error!"));
		
	}
	if (nTotalCnt <= 0)
	{
		AfxMessageBox(_T("no equipment!"));
	}

	std::string strPath = CStringA(ISOFilePath);
	const char* filePath = strPath.c_str();
	CHAR szFilePath[MAX_PATH] = { 0 };
	memcpy(szFilePath, filePath, strlen(filePath));
	int ret = 0;
	int tmp = 0;
	for (int i = 0; i < nTotalCnt; i++)
	{
		g_PartLetters[0] = cPartLetters[tmp];
		ret = ST_DownladTOCDROM(szFilePath, g_PartLetters[0], this);
		tmp += 3;
	}
	if (ret != 2)
		return FALSE;
	else
		return TRUE;
}


