// NeiAverSmoothDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "1.h"
#include "NeiAverSmoothDlg.h"
#include "afxdialogex.h"


// NeiAverSmoothDlg 对话框

IMPLEMENT_DYNAMIC(NeiAverSmoothDlg, CDialog)

NeiAverSmoothDlg::NeiAverSmoothDlg(CWnd* pParent /*=NULL*/)
	: CDialog(NeiAverSmoothDlg::IDD, pParent)
{
	m_radiovalue=0;
	TempH=3;
	TempW=3;
	TempCX=1;
	TempCY=1;
	fCoef=(float)(1.0/9.0);
	EnableAutomation();

	m_radiovalue = 0;
}

NeiAverSmoothDlg::~NeiAverSmoothDlg()
{
}

void NeiAverSmoothDlg::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialog::OnFinalRelease();
}

void NeiAverSmoothDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(NeiAverSmoothDlg)
	DDX_Radio(pDX, IDC_RADIO1, m_radiovalue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(NeiAverSmoothDlg, CDialog)
	ON_BN_CLICKED(IDC_RADIO4, &NeiAverSmoothDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO1, &NeiAverSmoothDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO3, &NeiAverSmoothDlg::OnBnClickedRadio3)
	//ON_COMMAND(IDC_RADIO2, &NeiAverSmoothDlg::OnRadio2)
	ON_BN_CLICKED(IDC_RADIO2, &NeiAverSmoothDlg::OnBnClickedRadio2)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(NeiAverSmoothDlg, CDialog)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_INeiAverSmoothDlg 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {7BB9DB8A-7A24-4695-B626-9DEF0F3AA60C}
static const IID IID_INeiAverSmoothDlg =
{ 0x7BB9DB8A, 0x7A24, 0x4695, { 0xB6, 0x26, 0x9D, 0xEF, 0xF, 0x3A, 0xA6, 0xC } };

BEGIN_INTERFACE_MAP(NeiAverSmoothDlg, CDialog)
	INTERFACE_PART(NeiAverSmoothDlg, IID_INeiAverSmoothDlg, Dispatch)
END_INTERFACE_MAP()


// NeiAverSmoothDlg 消息处理程序


void NeiAverSmoothDlg::OnBnClickedRadio4()
{
	m_radiovalue=3;
	TempH=5;
	TempW=5;
	TempCX=2;
	TempCY=2;
	fCoef=(float)(1.0/48.0);
	
	UpdateData(false);
}


void NeiAverSmoothDlg::OnBnClickedRadio1()
{
	m_radiovalue=0;
	TempH=3;
	TempW=3;
	TempCX=1;
	TempCY=1;
	fCoef=(float)(1.0/9.0);

	UpdateData(false);
}


void NeiAverSmoothDlg::OnBnClickedRadio3()
{
	m_radiovalue=2;
	TempH=7;
	TempW=7;
	TempCX=3;
	TempCY=3;
	fCoef=(float)(1.0/81.0);

	UpdateData(false);
}


//void NeiAverSmoothDlg::OnRadio2()
//{
//	m_radiovalue=1;
//	TempH=5;
//	TempW=5;
//	TempCX=2;
//	TempCY=2;
//	fCoef=(float)(1.0/25.0);
//
//	UpdateData(false);
//
//}


void NeiAverSmoothDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	UpdateData(true);

	CDialog::OnOK();
}


BOOL NeiAverSmoothDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	UpdateData(false);
  
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void NeiAverSmoothDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_radiovalue=1;
	TempH=5;
	TempW=5;
	TempCX=2;
	TempCY=2;
	fCoef=(float)(1.0/25.0);

	UpdateData(false);
}
