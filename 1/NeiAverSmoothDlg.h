#pragma once


// NeiAverSmoothDlg �Ի���

class NeiAverSmoothDlg : public CDialog
{
	DECLARE_DYNAMIC(NeiAverSmoothDlg)
public:
    int TempH, TempW, TempCX, TempCY;
    float fCoef;
public:
	NeiAverSmoothDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~NeiAverSmoothDlg();

	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_DLG_NeiborSmooth };
	int m_radiovalue;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio2();
//	afx_msg void OnRadio2();
	
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	
};
