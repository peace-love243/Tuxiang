#pragma once


// NeiAverSmoothDlg 对话框

class NeiAverSmoothDlg : public CDialog
{
	DECLARE_DYNAMIC(NeiAverSmoothDlg)
public:
    int TempH, TempW, TempCX, TempCY;
    float fCoef;
public:
	NeiAverSmoothDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~NeiAverSmoothDlg();

	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_DLG_NeiborSmooth };
	int m_radiovalue;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
