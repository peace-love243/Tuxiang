// MedianSmoothDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "1.h"
#include "MedianSmoothDlg.h"
#include "afxdialogex.h"


// MedianSmoothDlg 对话框

IMPLEMENT_DYNAMIC(MedianSmoothDlg, CDialog)

MedianSmoothDlg::MedianSmoothDlg(CWnd* pParent /*=NULL*/)
	: CDialog(MedianSmoothDlg::IDD, pParent)
{
	TempH=3;
	TempW=3;
	TempCX=1;
	TempCY=1;
	EnableAutomation();
	m_RadioValue = 0;
}

MedianSmoothDlg::~MedianSmoothDlg()
{
}

void MedianSmoothDlg::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialog::OnFinalRelease();
}

void MedianSmoothDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MedianSmoothDlg)
	DDX_Radio(pDX, IDC_RADIO1, m_RadioValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MedianSmoothDlg, CDialog)
	ON_BN_CLICKED(IDC_RADIO2, &MedianSmoothDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO1, &MedianSmoothDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO3, &MedianSmoothDlg::OnBnClickedRadio3)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(MedianSmoothDlg, CDialog)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_IMedianSmoothDlg 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {5CDA38A4-E75F-4F61-AD07-70134B800ADB}
static const IID IID_IMedianSmoothDlg =
{ 0x5CDA38A4, 0xE75F, 0x4F61, { 0xAD, 0x7, 0x70, 0x13, 0x4B, 0x80, 0xA, 0xDB } };

BEGIN_INTERFACE_MAP(MedianSmoothDlg, CDialog)
	INTERFACE_PART(MedianSmoothDlg, IID_IMedianSmoothDlg, Dispatch)
END_INTERFACE_MAP()


// MedianSmoothDlg 消息处理程序


void MedianSmoothDlg::OnBnClickedRadio2()
{
	m_RadioValue=1;
	TempH=5;
	TempW=5;
	TempCX=2;
	TempCY=2;
	UpdateData(false);
}

void MedianSmoothDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	UpdateData(true);
	CDialog::OnOK();
}


BOOL MedianSmoothDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	UpdateData(false);
	return TRUE;    // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void MedianSmoothDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_RadioValue = 0;
	TempH=3;
	TempW=3;
	TempCX=1;
	TempCY=1;
	UpdateData(false);
}

void MedianSmoothDlg::OnBnClickedRadio3()
{
	m_RadioValue=2;
	TempH=7;
	TempW=7;
	TempCX=3;
	TempCY=3;
    UpdateData(false);
}
