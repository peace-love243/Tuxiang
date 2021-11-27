
// 1View.h : CMy1View 类的接口
//

#pragma once
#include "ImageDib.h"
class CMy1View : public CView
{
protected: // 仅从序列化创建
	CMy1View();
	DECLARE_DYNCREATE(CMy1View)
// 特性
public:
	CMy1Doc* GetDocument() const;
// 操作
public:
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
// 实现
public:
	virtual ~CMy1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:
// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnDilation();
	afx_msg void OnErosion();
	afx_msg void OnOpen();
	afx_msg void OnThinning();
	afx_msg void OnAdaptivethreshold();
	afx_msg void OnAdthreshseg();
	afx_msg void OnEdgetrace();
	afx_msg void OnPrewitt();
	afx_msg void OnRobert();
	afx_msg void OnRegiongrow();
	afx_msg void OnSobel();
	afx_msg void OnOtus();
	afx_msg void OnMaxGray();
	afx_msg void OnJunzhiGray();
	afx_msg void OnJiaquanGray();
	afx_msg void OnYcbcr();
	afx_msg void OnYcbcr2cb();
	afx_msg void OnYcbcr2cr();
	afx_msg void OnYcbcr2y();
	afx_msg void OnYcbcrjq();
	afx_msg void OnLab1();
	afx_msg void OnLab2a();
	afx_msg void OnLab2b();
	afx_msg void OnLabjq();
	afx_msg void OnLab2l();
	afx_msg void OnRgbr();
	afx_msg void OnRgbg();
	afx_msg void OnRgbb();
	afx_msg void OnNewotsu();
	afx_msg void OnColorrev();
	afx_msg void OnBinaryimage();
	afx_msg void OnAreas();
	afx_msg void OnButterhighpass();
	afx_msg void OnButterlowpass();
	afx_msg void OnHarrwave();
	afx_msg void OnHarrwaveReverse();
	afx_msg void OnQuickfft();
	afx_msg void OnQuickfftReverse();
	afx_msg void OnIdealhighpass();
	afx_msg void OnIdeallowpass();
	afx_msg void OnCmyk();
	afx_msg void OnHsi();
	afx_msg void OnLaplacian();
	afx_msg void OnChoosemasksmooth();
	afx_msg void OnGaussnoise();
	afx_msg void OnGradesharp();
//	afx_msg void OnGradesmooth();
	afx_msg void OnLaplacesharp();
	afx_msg void OnMediansmooth();
	afx_msg void OnNeiavesmooth();
	afx_msg void OnPeppersaltnoise();
};
#ifndef _DEBUG  // 1View.cpp 中的调试版本
inline CMy1Doc* CMy1View::GetDocument() const
   { return reinterpret_cast<CMy1Doc*>(m_pDocument); }
#endif

