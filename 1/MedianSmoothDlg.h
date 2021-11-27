#pragma once


// MedianSmoothDlg 对话框

class MedianSmoothDlg : public CDialog
{
	DECLARE_DYNAMIC(MedianSmoothDlg)

public:

	int TempH,TempW,TempCX,TempCY;
	MedianSmoothDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MedianSmoothDlg();

	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_DLG_MedianSmooth };
	int m_RadioValue;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	afx_msg void OnBnClickedRadio2();	
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio3();
};
