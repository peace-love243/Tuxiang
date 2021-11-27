#include "stdafx.h"
#ifndef SHARED_HANDLERS
#include "1.h"
#endif
#include "1Doc.h"
#include "1View.h"
#include "MainFrm.h"
#include "GrayChange.h"
#include "ColorSpace.h"
#include "ImageEnhan.h"
#include "FreEnhance.h"
#include "FourTrans.h"
#include "WaveTrans.h"
#include "MedianSmoothDlg.h"
#include "NeiAverSmoothDlg.h"
#include "Morphology.h"
#include "ImgSegment.h"
FourTrans fftTrans;
WaveTrans wavltTrans;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
IMPLEMENT_DYNCREATE(CMy1View, CView)
BEGIN_MESSAGE_MAP(CMy1View, CView)// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMy1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_Close, &CMy1View::OnClose)
	ON_COMMAND(ID_Dilation, &CMy1View::OnDilation)
	ON_COMMAND(ID_Erosion, &CMy1View::OnErosion)
	ON_COMMAND(ID_OPEN, &CMy1View::OnOpen)
	ON_COMMAND(ID_Thinning, &CMy1View::OnThinning)
	ON_COMMAND(ID_AdaptiveThreshold, &CMy1View::OnAdaptivethreshold)
	ON_COMMAND(ID_EdgeTrace, &CMy1View::OnEdgetrace)
	ON_COMMAND(ID_Prewitt, &CMy1View::OnPrewitt)
	ON_COMMAND(ID_Robert, &CMy1View::OnRobert)
	ON_COMMAND(ID_RegionGrow, &CMy1View::OnRegiongrow)
	ON_COMMAND(ID_Sobel, &CMy1View::OnSobel)
	ON_COMMAND(ID_AdThreshSeg, &CMy1View::OnAdthreshseg)
	ON_COMMAND(ID_OTUS, &CMy1View::OnOtus)
	ON_COMMAND(ID_MAX_GRAY, &CMy1View::OnMaxGray)
	ON_COMMAND(ID_JUNZHI_GRAY, &CMy1View::OnJunzhiGray)
	ON_COMMAND(ID_JIAQUAN_GRAY, &CMy1View::OnJiaquanGray)
	ON_COMMAND(ID_YCBCR, &CMy1View::OnYcbcr)
	ON_COMMAND(ID_YCBCR2CB, &CMy1View::OnYcbcr2cb)
	ON_COMMAND(ID_YCBCR2CR, &CMy1View::OnYcbcr2cr)
	ON_COMMAND(ID_YCBCR2Y, &CMy1View::OnYcbcr2y)
	ON_COMMAND(ID_YCBCRJQ, &CMy1View::OnYcbcrjq)
	ON_COMMAND(ID_LAB1, &CMy1View::OnLab1)
	ON_COMMAND(ID_LAB2A, &CMy1View::OnLab2a)
	ON_COMMAND(ID_LAB2B, &CMy1View::OnLab2b)
	ON_COMMAND(ID_LABJQ, &CMy1View::OnLabjq)
	ON_COMMAND(ID_LAB2L, &CMy1View::OnLab2l)
	ON_COMMAND(ID_RGBR, &CMy1View::OnRgbr)
	ON_COMMAND(ID_RGBG, &CMy1View::OnRgbg)
	ON_COMMAND(ID_RGBB, &CMy1View::OnRgbb)
	ON_COMMAND(ID_NEWOTSU, &CMy1View::OnNewotsu)
	ON_COMMAND(ID_COLORREV, &CMy1View::OnColorrev)
	ON_COMMAND(ID_BINARYIMAGE, &CMy1View::OnBinaryimage)
	ON_COMMAND(ID_AREAS, &CMy1View::OnAreas)
	ON_COMMAND(ID_BUTTERHIGHPASS, &CMy1View::OnButterhighpass)
	ON_COMMAND(ID_BUTTERLOWPASS, &CMy1View::OnButterlowpass)
	ON_COMMAND(ID_HARRWAVE, &CMy1View::OnHarrwave)
	ON_COMMAND(ID_HARRWAVE_REVERSE, &CMy1View::OnHarrwaveReverse)
	ON_COMMAND(ID_QUICKFFT, &CMy1View::OnQuickfft)
	ON_COMMAND(ID_QUICKFFt_Reverse, &CMy1View::OnQuickfftReverse)
	ON_COMMAND(ID_IDEALHIGHPASS, &CMy1View::OnIdealhighpass)
	ON_COMMAND(ID_IDEALLOWPASS, &CMy1View::OnIdeallowpass)
	ON_COMMAND(ID_CMYK, &CMy1View::OnCmyk)
	ON_COMMAND(ID_HSI, &CMy1View::OnHsi)
	ON_COMMAND(ID_Laplacian, &CMy1View::OnLaplacian)
	ON_COMMAND(ID_ChooseMaskSmooth, &CMy1View::OnChoosemasksmooth)
	ON_COMMAND(ID_GaussNoise, &CMy1View::OnGaussnoise)
	ON_COMMAND(ID_GradeSharp, &CMy1View::OnGradesharp)
	ON_COMMAND(ID_LaplaceSharp, &CMy1View::OnLaplacesharp)
	ON_COMMAND(ID_MedianSmooth, &CMy1View::OnMediansmooth)
	ON_COMMAND(ID_NeiAveSmooth, &CMy1View::OnNeiavesmooth)
	ON_COMMAND(ID_PepperSaltNoise, &CMy1View::OnPeppersaltnoise)
END_MESSAGE_MAP()
CMy1View::CMy1View()
{
	
}
CMy1View::~CMy1View()
{

}
BOOL CMy1View::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}
void CMy1View::OnDraw(CDC*  pDC)
{
	CMy1Doc* pDoc = GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	CSize sizeFileDib=pDib->GetDimensions();
	pDib->Draw(pDC,CPoint(0,0),sizeFileDib);
}
void CMy1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}
BOOL CMy1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}
void CMy1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	
}
void CMy1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	
}
void CMy1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}
void CMy1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}
#ifdef _DEBUG
void CMy1View::AssertValid() const
{
	CView::AssertValid();
}
void CMy1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CMy1Doc* CMy1View::GetDocument() const 
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy1Doc)));
	return (CMy1Doc*)m_pDocument;
}
#endif 
void CMy1View::OnClose()
{
	CMy1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	if(pDib->m_nBitCount!=8)
	{
		::MessageBox(0,"只处理灰度图像",MB_OK,0);
		return ;
	}
	int i, j;
	CSize size=pDib->GetDimensions();
	int lineByte=(size.cx+3)/4*4;
	int flag=1;
	for(i=0;i<size.cy;i++)
	{
		for(j=0; j<size.cx;j++)
		{
			if(*(pDib->m_pImgData+i*lineByte+j)!=0&&*(pDib->m_pImgData+i*lineByte+j)!=255)
			{
				flag=0;
				break;
			}
		}
	}
	if(!flag)
	{
		::MessageBox(0,"需要输入二值图像",MB_OK,0);
		return ;
	}
	Morphology morTrans(pDib->GetDimensions(),pDib->m_nBitCount,pDib->m_lpColorTable, pDib->m_pImgData);
	morTrans.m_InitTemp[1]=1;                 
	morTrans.m_InitTemp[3]=1;
	morTrans.m_InitTemp[4]=1;
	morTrans.m_InitTemp[5]=1;
	morTrans.m_InitTemp[7]=1;
	if(morTrans.m_TempBuf)
	{
		delete []morTrans.m_TempBuf;
		morTrans.m_TempBuf=NULL;
	}
	morTrans.m_TempBuf=new int[morTrans.TempW*morTrans.TempH];
	int i0, j0;
	for(i0=0;i0<morTrans.TempH;i0++)
	{
		for(j0=0;j0<morTrans.TempW;j0++)
		{
			morTrans.m_TempBuf[i0*morTrans.TempW+j0]=morTrans.m_InitTemp[i0*morTrans.TempW+j0];
		}
	}
	morTrans.Close();
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView=(CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(morTrans.GetDimensions(),morTrans.m_nBitCountOut,morTrans.m_lpColorTable, morTrans.m_pImgDataOut);
	pView->OnInitialUpdate();		
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();
}
void CMy1View::OnDilation()
{
	CMy1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	if(pDib->m_nBitCount!=8)
	{
		::MessageBox(0,"只处理灰度图像",MB_OK,0);
		return ;
	}
	int i, j;
	CSize size=pDib->GetDimensions();
	int lineByte=(size.cx+3)/4*4;
	int flag=1;
	for(i=0;i<size.cy;i++)
		for(j=0; j<size.cx;j++)
			if(*(pDib->m_pImgData+i*lineByte+j)!=0&&*(pDib->m_pImgData+i*lineByte+j)!=255)
			{
				flag=0;
				break;
			}
	if(!flag)
	{
		::MessageBox(0,"需要输入二值图像",MB_OK,0);
		return ;
	}
	Morphology morTrans(pDib->GetDimensions(),pDib->m_nBitCount,pDib->m_lpColorTable, pDib->m_pImgData);
	morTrans.m_InitTemp[1]=1;               
	morTrans.m_InitTemp[3]=1;
	morTrans.m_InitTemp[4]=1;
	morTrans.m_InitTemp[5]=1;
	morTrans.m_InitTemp[7]=1;
	if(morTrans.m_TempBuf)
	{
		delete []morTrans.m_TempBuf;
		morTrans.m_TempBuf=NULL;
	}
	morTrans.m_TempBuf=new int[morTrans.TempW*morTrans.TempH];
	int i0, j0;
	for(i0=0;i0<morTrans.TempH;i0++)
		for(j0=0;j0<morTrans.TempW;j0++)
			morTrans.m_TempBuf[i0*morTrans.TempW+j0]=morTrans.m_InitTemp[i0*morTrans.TempW+j0];
	morTrans.ImgDilation(morTrans.m_pImgData,morTrans.m_pImgDataOut,morTrans.m_imgWidth,morTrans.m_imgHeight, morTrans.m_TempBuf, morTrans.TempW, morTrans.TempH);
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView=(CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(morTrans.GetDimensions(),morTrans.m_nBitCountOut,morTrans.m_lpColorTable, morTrans.m_pImgDataOut);
	pView->OnInitialUpdate();		
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();	
}
void CMy1View::OnErosion()
{
	CMy1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	if(pDib->m_nBitCount!=8)
	{
		::MessageBox(0,"只处理灰度图像",MB_OK,0);
		return ;
	}
	int i, j;
	CSize size=pDib->GetDimensions();
	int lineByte=(size.cx+3)/4*4;
	int flag=1;
	for(i=0;i<size.cy;i++)
	{
		for(j=0; j<size.cx;j++)
		{
			if(*(pDib->m_pImgData+i*lineByte+j)!=0&&*(pDib->m_pImgData+i*lineByte+j)!=255)
			{
				flag=0;
				break;
			}
		}
	}
	if(!flag)
	{
		::MessageBox(0,"需要输入二值图像",MB_OK,0);
		return ;
	}
	Morphology morTrans(pDib->GetDimensions(),pDib->m_nBitCount,pDib->m_lpColorTable, pDib->m_pImgData);
	morTrans.m_InitTemp[1]=1;
	morTrans.m_InitTemp[3]=1;
	morTrans.m_InitTemp[4]=1;
	morTrans.m_InitTemp[5]=1;
	morTrans.m_InitTemp[7]=1;
	if(morTrans.m_TempBuf)
	{
		delete []morTrans.m_TempBuf;
		morTrans.m_TempBuf=NULL;
	}
	morTrans.m_TempBuf=new int[morTrans.TempW*morTrans.TempH];
	int i0, j0;
	for(i0=0;i0<morTrans.TempH;i0++)
		for(j0=0;j0<morTrans.TempW;j0++)
			morTrans.m_TempBuf[i0*morTrans.TempW+j0]=morTrans.m_InitTemp[i0*morTrans.TempW+j0];

	morTrans.ImgErosion(morTrans.m_pImgData,morTrans.m_pImgDataOut,morTrans.m_imgWidth,morTrans.m_imgHeight,
		                     morTrans.m_TempBuf, morTrans.TempW, morTrans.TempH);
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView=(CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(morTrans.GetDimensions(),morTrans.m_nBitCountOut,morTrans.m_lpColorTable, morTrans.m_pImgDataOut);
	pView->OnInitialUpdate();		
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();
}
void CMy1View::OnOpen()
{
	CMy1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	if(pDib->m_nBitCount!=8)
	{
		::MessageBox(0,"只处理灰度图像",MB_OK,0);
		return ;
	}
	int i, j;
	CSize size=pDib->GetDimensions();
	int lineByte=(size.cx+3)/4*4;
	int flag=1;
	for(i=0;i<size.cy;i++)
	{
		for(j=0; j<size.cx;j++)
		{
			if(*(pDib->m_pImgData+i*lineByte+j)!=0&&*(pDib->m_pImgData+i*lineByte+j)!=255)
			{
				flag=0;
				break;
			}
		}
	}
	if(!flag)
	{
		::MessageBox(0,"需要输入二值图像",MB_OK,0);
		return ;
	}
	Morphology morTrans(pDib->GetDimensions(),pDib->m_nBitCount,pDib->m_lpColorTable, pDib->m_pImgData);
	morTrans.m_InitTemp[1]=1;
	morTrans.m_InitTemp[3]=1;
	morTrans.m_InitTemp[4]=1;
	morTrans.m_InitTemp[5]=1;
	morTrans.m_InitTemp[7]=1;
	if (morTrans.m_TempBuf) 
	{
		delete[]morTrans.m_TempBuf;
		morTrans.m_TempBuf = NULL;
	}
	morTrans.m_TempBuf=new int[morTrans.TempW*morTrans.TempH];
	int i0, j0;
	for(i0=0;i0<morTrans.TempH;i0++)
		for(j0=0;j0<morTrans.TempW;j0++)
			morTrans.m_TempBuf[i0*morTrans.TempW+j0]=morTrans.m_InitTemp[i0*morTrans.TempW+j0];
	morTrans.Open();
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView=(CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(morTrans.GetDimensions(),morTrans.m_nBitCountOut,morTrans.m_lpColorTable, morTrans.m_pImgDataOut);
	pView->OnInitialUpdate();		
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();
}
void CMy1View::OnThinning()
{
	CMy1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	if(pDib->m_nBitCount!=8)
	{
		::MessageBox(0,"只处理灰度图像",MB_OK,0);
		return ;
	}
	int i, j;
	CSize size=pDib->GetDimensions();
	int lineByte=(size.cx+3)/4*4;
	int flag=1;
	for(i=0;i<size.cy;i++)
	{
		for(j=0; j<size.cx;j++)
		{                    
			if(*(pDib->m_pImgData+i*lineByte+j)!=0&&*(pDib->m_pImgData+i*lineByte+j)!=255)
			{
				flag=0;
				break;
			}
		}
	}
	if(!flag)                                              
	{
		::MessageBox(0,"需要输入二值图像",MB_OK,0);
		return ;
	}
	Morphology morTrans(pDib->GetDimensions(),pDib->m_nBitCount,pDib->m_lpColorTable, pDib->m_pImgData);
    morTrans.ImgThinning();
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView=(CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(morTrans.GetDimensions(),morTrans.m_nBitCountOut,morTrans.m_lpColorTable, morTrans.m_pImgDataOut);
	pView->OnInitialUpdate();		
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();
}
void CMy1View::OnAdaptivethreshold()
{
	CMy1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	if(pDib->m_nBitCount!=8)
	{
		::MessageBox(0,"只处理灰度",MB_OK,0);
		return ;
	}
	ImgSegment segment(pDib->GetDimensions(),pDib->m_nBitCount,pDib->m_lpColorTable, pDib->m_pImgData);
	segment.AdaptThreshSeg(pDib->m_pImgData);
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView=(CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(segment.GetDimensions(),segment.m_nBitCountOut,segment.m_lpColorTableOut, segment.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);	
	Invalidate();
}
void CMy1View::OnEdgetrace()
{
	CMy1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	if(pDib->m_nBitCount!=8)
	{
		::MessageBox(0,"只处理灰度",MB_OK,0);
		return ;
	}
	int i, j;                                                    
	CSize size=pDib->GetDimensions();
	int lineByte=(size.cx+3)/4*4;
	int flag=1;
	for (i = 0; i < size.cy; i++) 
	{
		for (j = 0; j < size.cx; j++) 
		{
			if (*(pDib->m_pImgData + i*lineByte + j) != 0&& *(pDib->m_pImgData + i*lineByte + j) != 255)
			{
				flag = 0;
				break;
			}
		}
	}
	if(!flag)                            
	{
		::MessageBox(0,"需要输入二值图像",MB_OK,0);
		return ;
	}
	ImgSegment segment(pDib->GetDimensions(),pDib->m_nBitCount,pDib->m_lpColorTable, pDib->m_pImgData);
	segment.EdgeTrace();
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView=(CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(segment.GetDimensions(),segment.m_nBitCountOut,segment.m_lpColorTableOut, segment.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);	
	Invalidate();
}
void CMy1View::OnPrewitt()
{
	CMy1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	if(pDib->m_nBitCount!=8&&pDib->m_nBitCount!=24)
	{
		::MessageBox(0,"只处理灰度和彩色图像",MB_OK,0);
		return ;
	}
	ImgSegment segment(pDib->GetDimensions(),pDib->m_nBitCount,pDib->m_lpColorTable, pDib->m_pImgData);
	segment.Prewitt();
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView=(CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(segment.GetDimensions(),segment.m_nBitCountOut,segment.m_lpColorTableOut, segment.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);	
	Invalidate();	
}
void CMy1View::OnRobert()
{
	CMy1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	if(pDib->m_nBitCount!=8&&pDib->m_nBitCount!=24)
	{
		::MessageBox(0,"只处理灰度和彩色图像",MB_OK,0);
		return ;
	}
	ImgSegment segment(pDib->GetDimensions(),pDib->m_nBitCount,pDib->m_lpColorTable, pDib->m_pImgData);
	segment.Roberts();
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView=(CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(segment.GetDimensions(),segment.m_nBitCountOut,segment.m_lpColorTableOut, segment.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);	
	Invalidate();
}
void CMy1View::OnRegiongrow()
{
	CMy1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	if (pDib->m_nBitCount != 8) 
	{
		::MessageBox(0, "只处理灰度图像", MB_OK, 0);
		return;
	}
	ImgSegment segment(pDib->GetDimensions(),pDib->m_nBitCount,pDib->m_lpColorTable, pDib->m_pImgData);
	CPoint Pos(segment.m_imgWidth/2,segment.m_imgHeight/2);               
	int nThresh=3;                             
	segment.RegionGrow(Pos,nThresh);
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView=(CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(segment.GetDimensions(),segment.m_nBitCountOut,segment.m_lpColorTableOut, segment.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();
}
void CMy1View::OnSobel()
{
	CMy1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	if(pDib->m_nBitCount!=8&&pDib->m_nBitCount!=24)
	{
		::MessageBox(0,"只处理灰度和彩色图像",MB_OK,0);
		return ;
	}
	ImgSegment segment(pDib->GetDimensions(),pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	segment.Sobel();
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView=(CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(segment.GetDimensions(),segment.m_nBitCountOut,segment.m_lpColorTableOut, segment.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);	
	Invalidate();	
}
void CMy1View::OnLaplacian()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->m_dib;
	if (pDib->m_nBitCount != 8 && pDib->m_nBitCount != 24)
	{
		::MessageBox(0, "只处理灰度和彩色图像", MB_OK, 0);
		return;
	}
	ImgSegment segment(pDib->GetDimensions(), pDib->m_nBitCount,pDib->m_lpColorTable, pDib->m_pImgData);
	segment.Laplacian();
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->m_dib;
	dibNew->ReplaceDib(segment.GetDimensions(), segment.m_nBitCountOut, segment.m_lpColorTableOut, segment.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();
}
void CMy1View::OnAdthreshseg()
{
	CMy1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	if(pDib->m_nBitCount!=8)
	{
		::MessageBox(0,"只处理灰度",MB_OK,0);
		return ;
	}
	ImgSegment segment(pDib->GetDimensions(),pDib->m_nBitCount,pDib->m_lpColorTable, pDib->m_pImgData);
	segment.AdThreshSeg(pDib->m_pImgData);
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView=(CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(segment.GetDimensions(),segment.m_nBitCountOut,segment.m_lpColorTableOut, segment.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);	
	Invalidate();
}
void CMy1View::OnOtus()
{
	CMy1Doc *pDoc=GetDocument();
	ImageDib *pDib=pDoc->m_dib;
	if(pDib->m_nBitCount!=8)
	{
		::MessageBox(0,"只处理灰度",MB_OK,0);
		return ;
	}
	ImgSegment segment(pDib->GetDimensions(),pDib->m_nBitCount,pDib->m_lpColorTable, pDib->m_pImgData);
	segment.OtsuThreshold();                  
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView=(CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew=pView->GetDocument();
	ImageDib *dibNew=pDocNew->m_dib;
	dibNew->ReplaceDib(segment.GetDimensions(),segment.m_nBitCountOut,segment.m_lpColorTableOut, segment.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);	
	Invalidate();
}
void CMy1View::OnNewotsu()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->m_dib;
	if (pDib->m_nBitCount != 8) 
	{
		::MessageBox(0, "只处理灰度", MB_OK, 0);
		return;
	}
	ImgSegment segment(pDib->GetDimensions(), pDib->m_nBitCount,pDib->m_lpColorTable, pDib->m_pImgData);
	segment.NewOtsu();                   
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->m_dib;
	dibNew->ReplaceDib(segment.GetDimensions(), segment.m_nBitCountOut, segment.m_lpColorTableOut, segment.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();
}
void CMy1View::OnMaxGray()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->GetPDib();
	GrayChange graychange(pDib->GetDimensions(), pDib->m_nBitCount, pDib->m_lpColorTable, pDib->m_pImgData);
	graychange.ColorToGrayMax();
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->GetPDib();
	dibNew->ReplaceDib(graychange.GetDimensions(), graychange.m_nBitCountOut, graychange.m_lpColorTableOut, graychange.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
}
void CMy1View::OnJunzhiGray()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->GetPDib();
	GrayChange graychange(pDib->GetDimensions(), pDib->m_nBitCount, pDib->m_lpColorTable, pDib->m_pImgData);
	graychange.ColorToGrayAverage();
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->GetPDib();
	dibNew->ReplaceDib(graychange.GetDimensions(), graychange.m_nBitCountOut, graychange.m_lpColorTableOut, graychange.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
}
void CMy1View::OnJiaquanGray()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->GetPDib();
	GrayChange graychange(pDib->GetDimensions(), pDib->m_nBitCount, pDib->m_lpColorTable, pDib->m_pImgData);
	graychange.ColorToGrayJiaoQuan();
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->GetPDib();
	dibNew->ReplaceDib(graychange.GetDimensions(), graychange.m_nBitCountOut, graychange.m_lpColorTableOut, graychange.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
}
void CMy1View::OnYcbcr()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->GetPDib();
	ColorSpace colorspace(pDib->GetDimensions(), pDib->m_nBitCount, pDib->m_lpColorTable, pDib->m_pImgData);
	colorspace.RGB2YCBCR1();
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->GetPDib();
	dibNew->ReplaceDib(colorspace.GetDimensions(), colorspace.m_nBitCountOut, colorspace.m_lpColorTableOut, colorspace.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
}
void CMy1View::OnYcbcr2cb()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->GetPDib();
	ColorSpace colorspace(pDib->GetDimensions(), pDib->m_nBitCount, pDib->m_lpColorTable, pDib->m_pImgData);
	colorspace.RGB2CB();
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->GetPDib();
	dibNew->ReplaceDib(colorspace.GetDimensions(), colorspace.m_nBitCountOut, colorspace.m_lpColorTableOut, colorspace.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
}
void CMy1View::OnYcbcr2cr()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->GetPDib();
	ColorSpace colorspace(pDib->GetDimensions(), pDib->m_nBitCount, pDib->m_lpColorTable, pDib->m_pImgData);
	colorspace.RGB2CR();
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->GetPDib();
	dibNew->ReplaceDib(colorspace.GetDimensions(), colorspace.m_nBitCountOut, colorspace.m_lpColorTableOut, colorspace.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
}
void CMy1View::OnYcbcr2y()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->GetPDib();
	ColorSpace colorspace(pDib->GetDimensions(), pDib->m_nBitCount, pDib->m_lpColorTable, pDib->m_pImgData);
	colorspace.RGB2Y();
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->GetPDib();
	dibNew->ReplaceDib(colorspace.GetDimensions(), colorspace.m_nBitCountOut, colorspace.m_lpColorTableOut, colorspace.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
}
void CMy1View::OnYcbcrjq()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->GetPDib();
	ColorSpace colorspace(pDib->GetDimensions(), pDib->m_nBitCount, pDib->m_lpColorTable, pDib->m_pImgData);
	colorspace.RGB2YCBCRJIAQUAN();
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->GetPDib();
	dibNew->ReplaceDib(colorspace.GetDimensions(), colorspace.m_nBitCountOut, colorspace.m_lpColorTableOut, colorspace.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
}
void CMy1View::OnLab1()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->GetPDib();
	ColorSpace colorspace(pDib->GetDimensions(), pDib->m_nBitCount, pDib->m_lpColorTable, pDib->m_pImgData);
	colorspace.RGB2LAB1();
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->GetPDib();
	dibNew->ReplaceDib(colorspace.GetDimensions(), colorspace.m_nBitCountOut, colorspace.m_lpColorTableOut, colorspace.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
}
void CMy1View::OnLab2a()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->GetPDib();
	ColorSpace colorspace(pDib->GetDimensions(), pDib->m_nBitCount, pDib->m_lpColorTable, pDib->m_pImgData);
	colorspace.RGB2A();
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->GetPDib();
	dibNew->ReplaceDib(colorspace.GetDimensions(), colorspace.m_nBitCountOut, colorspace.m_lpColorTableOut, colorspace.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
}
void CMy1View::OnLab2b()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->GetPDib();
	ColorSpace colorspace(pDib->GetDimensions(), pDib->m_nBitCount, pDib->m_lpColorTable, pDib->m_pImgData);
	colorspace.RGB2B();
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->GetPDib();
	dibNew->ReplaceDib(colorspace.GetDimensions(), colorspace.m_nBitCountOut, colorspace.m_lpColorTableOut, colorspace.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
}
void CMy1View::OnLabjq()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->GetPDib();
	ColorSpace colorspace(pDib->GetDimensions(), pDib->m_nBitCount, pDib->m_lpColorTable, pDib->m_pImgData);
	colorspace.RGB2LABJQ();
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->GetPDib();
	dibNew->ReplaceDib(colorspace.GetDimensions(), colorspace.m_nBitCountOut, colorspace.m_lpColorTableOut, colorspace.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
}
void CMy1View::OnLab2l()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->GetPDib();
	ColorSpace colorspace(pDib->GetDimensions(), pDib->m_nBitCount, pDib->m_lpColorTable, pDib->m_pImgData);
	colorspace.RGB2L();
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->GetPDib();
	dibNew->ReplaceDib(colorspace.GetDimensions(), colorspace.m_nBitCountOut, colorspace.m_lpColorTableOut, colorspace.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
}
void CMy1View::OnRgbr()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->GetPDib();
	ColorSpace  colorspace(pDib->GetDimensions(), pDib->m_nBitCount, pDib->m_lpColorTable, pDib->m_pImgData);
	colorspace.RGBR();
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->GetPDib();
	dibNew->ReplaceDib(colorspace.GetDimensions(), colorspace.m_nBitCountOut, colorspace.m_lpColorTableOut, colorspace.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
}
void CMy1View::OnRgbg()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->GetPDib();
	ColorSpace colorspace(pDib->GetDimensions(), pDib->m_nBitCount, pDib->m_lpColorTable, pDib->m_pImgData);
	colorspace.RGBG();
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->GetPDib();
	dibNew->ReplaceDib(colorspace.GetDimensions(), colorspace.m_nBitCountOut, colorspace.m_lpColorTableOut, colorspace.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
}
void CMy1View::OnRgbb()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->GetPDib();
	ColorSpace colorspace(pDib->GetDimensions(), pDib->m_nBitCount, pDib->m_lpColorTable, pDib->m_pImgData);
	colorspace.RGBB();
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->GetPDib();
	dibNew->ReplaceDib(colorspace.GetDimensions(), colorspace.m_nBitCountOut, colorspace.m_lpColorTableOut, colorspace.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
}
void CMy1View::OnCmyk()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->m_dib;
	if (pDib->m_nBitCount != 24 && pDib->m_nBitCount != 8) 
	{
		::MessageBox(0, "只处理彩色和灰度图像", MB_OK, 0);
		return;
	}
	ColorSpace colorspace(pDib->GetDimensions(), pDib->m_nBitCount, pDib->m_lpColorTable, pDib->m_pImgData);
	colorspace.RGB2CMYK();
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->m_dib;
	dibNew->ReplaceDib(colorspace.GetDimensions(), colorspace.m_nBitCountOut, colorspace.m_lpColorTableOut, colorspace.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();
}
void CMy1View::OnHsi()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->m_dib;
	if (pDib->m_nBitCount != 24 && pDib->m_nBitCount != 8)
	{
		::MessageBox(0, "只处理彩色和灰度图像", MB_OK, 0);
		return;
	}
	ColorSpace colorspace(pDib->GetDimensions(), pDib->m_nBitCount, pDib->m_lpColorTable, pDib->m_pImgData);
	colorspace.RGB2HSI();
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->m_dib;
	dibNew->ReplaceDib(colorspace.GetDimensions(), colorspace.m_nBitCountOut, colorspace.m_lpColorTableOut, colorspace.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();
}
void CMy1View::OnColorrev()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->m_dib;
	if (pDib->m_nBitCount != 24 && pDib->m_nBitCount != 8)
	{
		::MessageBox(0, "只处理彩色和灰度图像", MB_OK, 0);
		return;
	}
	GrayChange graychange(pDib->GetDimensions(), pDib->m_nBitCount, pDib->m_lpColorTable, pDib->m_pImgData);
	graychange.ColorRev();
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->m_dib;
	dibNew->ReplaceDib(graychange.GetDimensions(), graychange.m_nBitCountOut, graychange.m_lpColorTableOut, graychange.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
}
void CMy1View::OnBinaryimage()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->m_dib;
	if (pDib->m_nBitCount != 24 && pDib->m_nBitCount != 8)
	{
		::MessageBox(0, "只处理彩色和灰度图像", MB_OK, 0);
		return;
	}
	GrayChange graychange(pDib->GetDimensions(), pDib->m_nBitCount, pDib->m_lpColorTable, pDib->m_pImgData);
	graychange.Binary(120);
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->m_dib;
	dibNew->ReplaceDib(graychange.GetDimensions(), graychange.m_nBitCountOut, graychange.m_lpColorTableOut, graychange.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
}
void CMy1View::OnAreas()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->m_dib;
	if (pDib->m_nBitCount != 24 && pDib->m_nBitCount != 8) 
	{
		::MessageBox(0, "只处理彩色和灰度图像", MB_OK, 0);
		return;
	}
	Morphology morphology(pDib->GetDimensions(), pDib->m_nBitCount, pDib->m_lpColorTable, pDib->m_pImgData);

	morphology.Areas();
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->m_dib;
	dibNew->ReplaceDib(morphology.GetDimensions(), morphology.m_nBitCountOut, morphology.m_lpColorTableOut, morphology.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
}
void CMy1View::OnButterhighpass()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->m_dib;
	if (pDib->m_nBitCount != 8) 
	{
		::MessageBox(0, "只处理灰度图像", MB_OK, 0);
		return;
	}
	int isValidateFlag = 1;
	int width = pDib->GetDimensions().cx;
	int height = pDib->GetDimensions().cy;
	int i = 1;
	while (i<width)
		i = i * 2;
	if (i != width)
		isValidateFlag = 0;
	i = 1;
	while (i<height)
		i = i * 2;
	if (i != height)
		isValidateFlag = 0;
	if (isValidateFlag == 0) 
	{
		::MessageBox(0, "输入图像的宽和高应为2的幂次方", MB_OK, 0);
		return;
	}
	FreEnhance imgfreq;
	imgfreq.InputImageData(pDib->GetDimensions(), pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	imgfreq.ButterHighPassFilter(pDib->m_imgWidth, pDib->m_imgHeight, pDib->m_imgHeight / 16);   
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->m_dib;
	dibNew->ReplaceDib(imgfreq.GetDimensions(), imgfreq.m_nBitCountOut,imgfreq.m_lpColorTable, imgfreq.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();
}
void CMy1View::OnButterlowpass()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->m_dib;
	if (pDib->m_nBitCount != 8)
	{
		::MessageBox(0, "只处理灰度图像", MB_OK, 0);
		return;
	}
	int isValidateFlag = 1;
	int width = pDib->GetDimensions().cx;
	int height = pDib->GetDimensions().cy;
	int i = 1;
	while (i<width)
		i = i * 2;
	if (i != width)
		isValidateFlag = 0;
	i = 1;
	while (i<height)
		i = i * 2;
	if (i != height)
		isValidateFlag = 0;
	if (isValidateFlag == 0) 
	{
		::MessageBox(0, "输入图像的宽和高应为2的幂次方", MB_OK, 0);
		return;
	}
	FreEnhance imgfreq;
	imgfreq.InputImageData(pDib->GetDimensions(), pDib->m_nBitCount,pDib->m_lpColorTable, pDib->m_pImgData);
	imgfreq.ButterLowPassFilter(pDib->m_imgWidth, pDib->m_imgHeight, pDib->m_imgHeight / 16);
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->m_dib;
	dibNew->ReplaceDib(imgfreq.GetDimensions(), imgfreq.m_nBitCountOut,imgfreq.m_lpColorTable, imgfreq.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();
}
void CMy1View::OnHarrwave()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->m_dib;
	if (pDib->m_nBitCount != 8) 
	{
		::MessageBox(0, "只处理灰度图像", MB_OK, 0);
		return;
	}
	wavltTrans.InputImageData(pDib->GetDimensions(), pDib->m_nBitCount,pDib->m_lpColorTable, pDib->m_pImgData);
	wavltTrans.BasicWaveletTrans(2);
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->m_dib;
	dibNew->ReplaceDib(wavltTrans.GetDimensions(), wavltTrans.m_nBitCountOut, wavltTrans.m_pColorTableOut, wavltTrans.m_pImgDataOut);
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();
}
void CMy1View::OnHarrwaveReverse()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->m_dib;
	if (pDib->m_nBitCount != 8)
	{
		::MessageBox(0, "只处理灰度图像", MB_OK, 0);
		return;
	}
	wavltTrans.BasicWaveletReverse();
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->m_dib;
	dibNew->ReplaceDib(wavltTrans.GetDimensions(), wavltTrans.m_nBitCountOut, wavltTrans.m_pColorTableOut, wavltTrans.m_pImgDataOut);
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();
}
void CMy1View::OnQuickfft()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->m_dib;
	if (pDib->m_nBitCount != 8)
	{
		::MessageBox(0, "只处理灰度图像", MB_OK, 0);
		return;
	}
	int isValidateFlag = 1;                     
	int width = pDib->GetDimensions().cx;
	int height = pDib->GetDimensions().cy;
	int i = 1;
	while (i<width)
		i = i * 2;
	if (i != width)                        
		isValidateFlag = 0;
	i = 1;
	while (i<height)
		i = i * 2;
	if (i != height)                         
		isValidateFlag = 0;
	if (isValidateFlag == 0) 
	{
		::MessageBox(0, "输入图像的宽和高应为2的幂次方", MB_OK, 0);
		return;
	}
	fftTrans.InputImgData(pDib->GetDimensions(), pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	fftTrans.Fourier();
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->m_dib;
	dibNew->ReplaceDib(fftTrans.GetDimensions(), fftTrans.m_nBitCountOut,fftTrans.m_lpColorTable, fftTrans.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();
}
void CMy1View::OnQuickfftReverse()
{
	fftTrans.RevFourier();
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->m_dib;
	dibNew->ReplaceDib(fftTrans.GetDimensions(), fftTrans.m_nBitCountOut,fftTrans.m_lpColorTable, fftTrans.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();
}
void CMy1View::OnIdealhighpass()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->m_dib;
	if (pDib->m_nBitCount != 8) 
	{
		::MessageBox(0, "只处理灰度图像", MB_OK, 0);
		return;
	}
	int isValidateFlag = 1;
	int width = pDib->GetDimensions().cx;
	int height = pDib->GetDimensions().cy;
	int i = 1;
	while (i<width)
		i = i * 2;
	if (i != width)
		isValidateFlag = 0;
	i = 1;
	while (i<height)
		i = i * 2;
	if (i != height)
		isValidateFlag = 0;
	if (isValidateFlag == 0) 
	{
		::MessageBox(0, "输入图像的宽和高应为2的幂次方", MB_OK, 0);
		return;
	}
	FreEnhance imgfreq;
	imgfreq.InputImageData(pDib->GetDimensions(), pDib->m_nBitCount,
		pDib->m_lpColorTable, pDib->m_pImgData);
	imgfreq.IdealHighPassFilter(pDib->m_imgWidth, pDib->m_imgHeight, pDib->m_imgHeight / 16);
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->m_dib;
	dibNew->ReplaceDib(imgfreq.GetDimensions(), imgfreq.m_nBitCountOut,imgfreq.m_lpColorTable, imgfreq.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();
}
void CMy1View::OnIdeallowpass()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->m_dib;
	if (pDib->m_nBitCount != 8)
	{
		::MessageBox(0, "只处理灰度图像", MB_OK, 0);
		return;
	}
	int isValidateFlag = 1;
	int width = pDib->GetDimensions().cx;
	int height = pDib->GetDimensions().cy;
	int i = 1;
	while (i<width)
		i = i * 2;
	if (i != width)
		isValidateFlag = 0;
	i = 1;
	while (i<height)
		i = i * 2;
	if (i != height)
		isValidateFlag = 0;
	if (isValidateFlag == 0) 
	{
		::MessageBox(0, "输入图像的宽和高应为2的幂次方", MB_OK, 0);
		return;
	};
	FreEnhance imgfreq;
	imgfreq.InputImageData(pDib->GetDimensions(), pDib->m_nBitCount,pDib->m_lpColorTable, pDib->m_pImgData);
	imgfreq.IdealLowPassFilter(pDib->m_imgWidth, pDib->m_imgHeight, pDib->m_imgHeight / 16);
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->m_dib;
	dibNew->ReplaceDib(imgfreq.GetDimensions(), imgfreq.m_nBitCountOut,imgfreq.m_lpColorTable, imgfreq.m_pImgDataOut);
	pView->OnInitialUpdate();
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();
}
void CMy1View::OnChoosemasksmooth()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->m_dib;
	if (pDib->m_nBitCount != 8) 
	{
		::MessageBox(0, "只处理灰度图像", MB_OK, 0);
		return;
	}
	ImageEnhan imgSmooth(pDib->GetDimensions(), pDib->m_nBitCount,pDib->m_lpColorTable, pDib->m_pImgData);
	imgSmooth.ChooseMaskSmooth();
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->m_dib;
	dibNew->ReplaceDib(imgSmooth.GetDimensions(), imgSmooth.m_nBitCountOut, imgSmooth.m_lpColorTable, imgSmooth.m_pImgDataOut);
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
}
void CMy1View::OnGaussnoise()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->m_dib;
	if (pDib->m_nBitCount != 8) 
	{
		::MessageBox(0, "只处理灰度图像", MB_OK, 0);
		return;
	}
	ImageEnhan imgnoise(pDib->GetDimensions(), pDib->m_nBitCount, pDib->m_lpColorTable, pDib->m_pImgData);
	imgnoise.AddGaussNoise();
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->m_dib;
	dibNew->ReplaceDib(imgnoise.GetDimensions(), imgnoise.m_nBitCountOut, imgnoise.m_lpColorTable, imgnoise.m_pImgDataOut);
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();
}
void CMy1View::OnGradesharp()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->m_dib;
	if (pDib->m_nBitCount != 8) 
	{
		::MessageBox(0, "只处理灰度图像", MB_OK, 0);
		return;
	}
	ImageEnhan imgsharp(pDib->GetDimensions(), pDib->m_nBitCount,pDib->m_lpColorTable, pDib->m_pImgData);
	int nThresh = 30;
	imgsharp.GradeSharp(nThresh);
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->m_dib;
	dibNew->ReplaceDib(imgsharp.GetDimensions(), imgsharp.m_nBitCountOut, imgsharp.m_lpColorTable, imgsharp.m_pImgDataOut);
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();
}
void CMy1View::OnLaplacesharp()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->m_dib;
	if (pDib->m_nBitCount != 8) 
	{
		::MessageBox(0, "只处理灰度图像", MB_OK, 0);
		return;
	}
	ImageEnhan imgsharp(pDib->GetDimensions(), pDib->m_nBitCount,pDib->m_lpColorTable, pDib->m_pImgData);
	int TempH, TempW, TempCX, TempCY;
	float fCoef;
	float Temp[9];
	Temp[0] = -1.0;
	Temp[1] = -1.0;
	Temp[2] = -1.0;
	Temp[3] = -1.0;
	Temp[4] = 9.0;
	Temp[5] = -1.0;
	Temp[6] = -1.0;
	Temp[7] = -1.0;
	Temp[8] = -1.0;
	TempH = 3;
	TempW = 3;
	TempCX = 1;
	TempCY = 1;
	fCoef = 1.0;
	imgsharp.LapTemplate(TempH, TempW, TempCX, TempCY, Temp, fCoef);
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->m_dib;
	dibNew->ReplaceDib(imgsharp.GetDimensions(), imgsharp.m_nBitCountOut, imgsharp.m_lpColorTable, imgsharp.m_pImgDataOut);
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();
}
void CMy1View::OnMediansmooth()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->m_dib;
	if (pDib->m_nBitCount != 8)
	{
		::MessageBox(0, "只处理灰度图像", MB_OK, 0);
		return;
	}
	MedianSmoothDlg dlgparam;
	if (dlgparam.DoModal() == TRUE) 
	{
		ImageEnhan imgsmooth(pDib->GetDimensions(), pDib->m_nBitCount,pDib->m_lpColorTable, pDib->m_pImgData);
		imgsmooth.MedianSmooth(dlgparam.TempH, dlgparam.TempW, dlgparam.TempCX, dlgparam.TempCY);
		CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
		pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
		CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
		CMy1Doc* pDocNew = pView->GetDocument();
		ImageDib *dibNew = pDocNew->m_dib;
		dibNew->ReplaceDib(imgsmooth.GetDimensions(), imgsmooth.m_nBitCountOut, imgsmooth.m_lpColorTable, imgsmooth.m_pImgDataOut);
		pDocNew->SetModifiedFlag(TRUE);
		pDocNew->UpdateAllViews(pView);
		Invalidate();
	}
}
void CMy1View::OnNeiavesmooth()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->m_dib;
	if (pDib->m_nBitCount != 8) 
	{
		::MessageBox(0, "只处理灰度图像", MB_OK, 0);
		return;
	}
	ImageEnhan imgsmooth(pDib->GetDimensions(), pDib->m_nBitCount,pDib->m_lpColorTable, pDib->m_pImgData);
	NeiAverSmoothDlg dlgparam;
	if (dlgparam.DoModal() == IDOK) 
	{
		if (dlgparam.m_radiovalue == 0 || dlgparam.m_radiovalue == 1 || dlgparam.m_radiovalue == 2) 
		{
			float Temp1[81];
			int i;
			for (i = 0; i < 81; i++)
			{
				Temp1[i] = 1.0;
			}
			imgsmooth.NeiAveTemplate(dlgparam.TempH, dlgparam.TempW, dlgparam.TempCX,dlgparam.TempCY, Temp1, dlgparam.fCoef);
		}
		else if (dlgparam.m_radiovalue = 3) 
		{
			float Temp[25];
			Temp[0] = 0.0;
			Temp[1] = 1.0;
			Temp[2] = 2.0;
			Temp[3] = 1.0;
			Temp[4] = 0.0;
			Temp[5] = 1.0;
			Temp[6] = 2.0;
			Temp[7] = 4.0;
			Temp[8] = 2.0;
			Temp[9] = 1.0;
			Temp[10] = 2.0;
			Temp[11] = 4.0;
			Temp[12] = 8.0;
			Temp[13] = 4.0;
			Temp[14] = 2.0;
			Temp[15] = 1.0;
			Temp[16] = 2.0;
			Temp[17] = 4.0;
			Temp[18] = 2.0;
			Temp[19] = 1.0;
			Temp[20] = 0.0;
			Temp[21] = 1.0;
			Temp[22] = 2.0;
			Temp[23] = 1.0;
			Temp[24] = 0.0;
			imgsmooth.NeiAveTemplate(dlgparam.TempH, dlgparam.TempW, dlgparam.TempCX,
				dlgparam.TempCY, Temp, dlgparam.fCoef);
		}
		else
			return;
		CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
		pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
		CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
		CMy1Doc* pDocNew = pView->GetDocument();
		ImageDib *dibNew = pDocNew->m_dib;
		dibNew->ReplaceDib(imgsmooth.GetDimensions(), imgsmooth.m_nBitCountOut, imgsmooth.m_lpColorTable, imgsmooth.m_pImgDataOut);
		pDocNew->SetModifiedFlag(TRUE);
		pDocNew->UpdateAllViews(pView);
		Invalidate();
	}
}
void CMy1View::OnPeppersaltnoise()
{
	CMy1Doc *pDoc = GetDocument();
	ImageDib *pDib = pDoc->m_dib;
	if (pDib->m_nBitCount != 8) 
	{
		::MessageBox(0, "只处理灰度图像", MB_OK, 0);
		return;
	}
	ImageEnhan imgnoise(pDib->GetDimensions(), pDib->m_nBitCount, pDib->m_lpColorTable, pDib->m_pImgData);
	imgnoise.AddPepperSaltNoise();
	CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);
	CMy1View* pView = (CMy1View*)pFrame->MDIGetActive()->GetActiveView();
	CMy1Doc* pDocNew = pView->GetDocument();
	ImageDib *dibNew = pDocNew->m_dib;
	dibNew->ReplaceDib(imgnoise.GetDimensions(), imgnoise.m_nBitCountOut, imgnoise.m_lpColorTable, imgnoise.m_pImgDataOut);
	pDocNew->SetModifiedFlag(TRUE);
	pDocNew->UpdateAllViews(pView);
	Invalidate();
}
