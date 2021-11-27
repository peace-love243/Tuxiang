// MedianSmoothDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "1.h"
#include "MedianSmoothDlg.h"
#include "afxdialogex.h"


// MedianSmoothDlg �Ի���

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
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

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

// ע��: ������� IID_IMedianSmoothDlg ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {5CDA38A4-E75F-4F61-AD07-70134B800ADB}
static const IID IID_IMedianSmoothDlg =
{ 0x5CDA38A4, 0xE75F, 0x4F61, { 0xAD, 0x7, 0x70, 0x13, 0x4B, 0x80, 0xA, 0xDB } };

BEGIN_INTERFACE_MAP(MedianSmoothDlg, CDialog)
	INTERFACE_PART(MedianSmoothDlg, IID_IMedianSmoothDlg, Dispatch)
END_INTERFACE_MAP()


// MedianSmoothDlg ��Ϣ�������


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
	// TODO: �ڴ����ר�ô����/����û���
	UpdateData(true);
	CDialog::OnOK();
}


BOOL MedianSmoothDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	UpdateData(false);
	return TRUE;    // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void MedianSmoothDlg::OnBnClickedRadio1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
