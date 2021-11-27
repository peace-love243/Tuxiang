#include "StdAfx.h"
#include "ImageDib.h"
ImageDib::ImageDib(void)
{
	m_lpDib = NULL;					//初始化m_lpDib为空。
	m_lpColorTable = NULL;			//颜色表指针为空
	m_pImgData = NULL;  				//图像数据指针为空
	m_lpBmpInfoHead = NULL;			//图像信息头指针为空
	m_hPalette = NULL;				//调色板为空
}
ImageDib::~ImageDib(void)
{
	if(m_lpDib != NULL) //释放m_lpDib所指向的内存缓冲区
		delete [] m_lpDib; 
	if(m_hPalette != NULL)//如果有调色板，释放调色板缓冲区
		::DeleteObject(m_hPalette);
}
ImageDib::ImageDib(CSize size, int nBitCount, LPRGBQUAD lpColorTable,unsigned char *pImgData)
{
	if(pImgData==NULL)
	{//如果没有位图数据传入，我们认为是空的DIB，此时不分配DIB内存
		m_lpDib=NULL;
		m_lpColorTable=NULL;
		m_pImgData=NULL;  // 图像数据
		m_lpBmpInfoHead=NULL; //  图像信息头
		m_hPalette = NULL;
	}
	else
	{
		m_imgWidth=size.cx;//图像的宽、高、每像素位数等成员变量赋值
		m_imgHeight=size.cy;
		m_nBitCount=nBitCount;
		m_nColorTableLength=ComputeColorTabalLength(nBitCount);//根据每像素位数，计算颜色表长度
		int lineByte=(m_imgWidth*nBitCount/8+3)/4*4;//每行像素所占字节数，必须扩展成4的倍数
		int imgBufSize=m_imgHeight*lineByte;//位图数据缓冲区的大小
		m_lpDib=new BYTE [sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * m_nColorTableLength+imgBufSize];
		m_lpBmpInfoHead = (LPBITMAPINFOHEADER) m_lpDib;//填写BITMAPINFOHEADER结构
		m_lpBmpInfoHead->biSize = sizeof(BITMAPINFOHEADER);
		m_lpBmpInfoHead->biWidth = m_imgWidth;
		m_lpBmpInfoHead->biHeight = m_imgHeight;
		m_lpBmpInfoHead->biPlanes = 1;
		m_lpBmpInfoHead->biBitCount = m_nBitCount;
		m_lpBmpInfoHead->biCompression = BI_RGB;
		m_lpBmpInfoHead->biSizeImage = 0;
		m_lpBmpInfoHead->biXPelsPerMeter = 0;
		m_lpBmpInfoHead->biYPelsPerMeter = 0;
		m_lpBmpInfoHead->biClrUsed = m_nColorTableLength;
		m_lpBmpInfoHead->biClrImportant = m_nColorTableLength;
		m_hPalette = NULL;//调色板句柄初始化为空，有颜色表时，MakePalette()函数要生成新的调色板
		if(m_nColorTableLength!=0)//如果有颜色表，则将颜色表拷贝进DIB的颜色表位置
		{  
			m_lpColorTable=(LPRGBQUAD)(m_lpDib+sizeof(BITMAPINFOHEADER));//m_lpColorTable指向DIB颜色表的起始位置
			memcpy(m_lpColorTable,lpColorTable,sizeof(RGBQUAD) * m_nColorTableLength);//颜色表拷贝
			MakePalette();	//创建逻辑调色板
		}
		m_pImgData = (LPBYTE)m_lpDib+sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD) * m_nColorTableLength;//m_pImgData指向DIB位图数据起始位置
		memcpy(m_pImgData,pImgData,imgBufSize);//拷贝图像数据进DIB位图数据区
	}	
}
BOOL ImageDib::Read(LPCTSTR lpszPathName)
{
	CFile file;//读模式打开图像文件
	if (!file.Open(lpszPathName, CFile::modeRead | CFile::shareDenyWrite))
		return FALSE;
	BITMAPFILEHEADER bmfh;
	
	int nCount=file.Read((LPVOID) &bmfh, sizeof(BITMAPFILEHEADER));//读取BITMAPFILEHEADER结构到变量bmfh中
	if(m_lpDib!=NULL)	
		delete []m_lpDib;
	m_lpDib=new BYTE[file.GetLength() -sizeof(BITMAPFILEHEADER)];
	file.Read(m_lpDib, file.GetLength() -sizeof(BITMAPFILEHEADER));
	m_lpBmpInfoHead = (LPBITMAPINFOHEADER)m_lpDib;
	m_imgWidth=m_lpBmpInfoHead->biWidth;
	m_imgHeight=m_lpBmpInfoHead->biHeight;
	m_nBitCount=m_lpBmpInfoHead->biBitCount; 
	m_nColorTableLength=ComputeColorTabalLength(m_lpBmpInfoHead->biBitCount);
	m_hPalette = NULL;
	if(m_nColorTableLength!=0)
	{
		m_lpColorTable=(LPRGBQUAD)(m_lpDib+sizeof(BITMAPINFOHEADER));
	    MakePalette();
	}
	m_pImgData = (LPBYTE)m_lpDib+sizeof(BITMAPINFOHEADER) +sizeof(RGBQUAD) * m_nColorTableLength;
	return TRUE;
}
BOOL ImageDib::Write(LPCTSTR lpszPathName)
{
	CFile file;
	if (!file.Open(lpszPathName, CFile::modeCreate | CFile::modeReadWrite | CFile::shareExclusive))
		return FALSE;
	BITMAPFILEHEADER bmfh;
	bmfh.bfType = 0x4d42; 
	bmfh.bfSize = 0;
	bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +sizeof(RGBQUAD) * m_nColorTableLength;	
	try {
		file.Write((LPVOID) &bmfh, sizeof(BITMAPFILEHEADER));
		file.Write(m_lpBmpInfoHead,  sizeof(BITMAPINFOHEADER));
		if(m_nColorTableLength!=0)
			file.Write(m_lpColorTable, sizeof(RGBQUAD) * m_nColorTableLength);
		int imgBufSize=(m_imgWidth*m_nBitCount/8+3)/4*4*m_imgHeight;
		file.Write(m_pImgData, imgBufSize);
	}
	catch(CException* pe) 
	{
		pe->Delete();
		AfxMessageBox(_T("write error"));
		return FALSE;
	}
	return TRUE;
}
void ImageDib::MakePalette()
{
	if(m_nColorTableLength == 0) 
		return;
	if(m_hPalette != NULL) 
		::DeleteObject(m_hPalette);
	LPLOGPALETTE pLogPal = (LPLOGPALETTE) new char[2 * sizeof(WORD) +m_nColorTableLength * sizeof(PALETTEENTRY)];
	pLogPal->palVersion = 0x300;
	pLogPal->palNumEntries = m_nColorTableLength;
	LPRGBQUAD m_lpDibQuad = (LPRGBQUAD) m_lpColorTable;
	for(int i = 0; i < m_nColorTableLength; i++) 
	{
		pLogPal->palPalEntry[i].peRed = m_lpDibQuad->rgbRed;
		pLogPal->palPalEntry[i].peGreen = m_lpDibQuad->rgbGreen;
		pLogPal->palPalEntry[i].peBlue = m_lpDibQuad->rgbBlue;
		pLogPal->palPalEntry[i].peFlags = 0;
		m_lpDibQuad++;
	}
	m_hPalette = ::CreatePalette(pLogPal);
	delete pLogPal;
}
int ImageDib::ComputeColorTabalLength(int nBitCount)
{
	int colorTableLength = 0;
	switch (nBitCount)
	{
	case 1:
		colorTableLength = 2;
		break;
	case 4:
		colorTableLength = 16;
		break;
	case 8:
		colorTableLength = 256;
		break;
	case 16:
	case 24:
	case 32:
		colorTableLength = 0;
		break;
	default:
		ASSERT(FALSE);
	}
	ASSERT((colorTableLength >= 0) && (colorTableLength <= 256));
	return colorTableLength;
}
BOOL ImageDib::Draw(CDC* pDC, CPoint origin, CSize size)
{
	HPALETTE hOldPal=NULL;				//旧的调色板句柄
	if(m_lpDib == NULL)
		return FALSE;			//如果DIB为空，则返回0
	if(m_hPalette != NULL)      //如果DIB有调色板
	{
		hOldPal=::SelectPalette(pDC->GetSafeHdc(), m_hPalette, TRUE);
		pDC->RealizePalette();			
	}
	pDC->SetStretchBltMode(COLORONCOLOR);  
	::StretchDIBits(pDC->GetSafeHdc(), origin.x, origin.y, size.cx, size.cy,
		0, 0, m_lpBmpInfoHead->biWidth, m_lpBmpInfoHead->biHeight,m_pImgData,
		 (LPBITMAPINFO) m_lpBmpInfoHead, DIB_RGB_COLORS, SRCCOPY);
	if(hOldPal!=NULL)						//恢复旧的调色板
		::SelectPalette(pDC->GetSafeHdc(), hOldPal, TRUE);
	return TRUE;
}
CSize ImageDib::GetDimensions()
{
	if(m_lpDib == NULL) 
		return CSize(0, 0);
	return CSize(m_imgWidth, m_imgHeight);
}
void ImageDib::ReplaceDib(CSize size,int nBitCount,LPRGBQUAD lpColorTable,unsigned char *pImgData)
{ 
	Empty();
	m_imgWidth=size.cx;
	m_imgHeight=size.cy;
	m_nBitCount=nBitCount;
	m_nColorTableLength=ComputeColorTabalLength(nBitCount);
	int lineByte=(m_imgWidth*nBitCount/8+3)/4*4;
	int imgBufSize=m_imgHeight*lineByte;
	m_lpDib=new BYTE [sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * m_nColorTableLength+imgBufSize];
	m_lpBmpInfoHead = (LPBITMAPINFOHEADER) m_lpDib;
	m_lpBmpInfoHead->biSize = sizeof(BITMAPINFOHEADER);
	m_lpBmpInfoHead->biWidth = m_imgWidth;
	m_lpBmpInfoHead->biHeight = m_imgHeight;
	m_lpBmpInfoHead->biPlanes = 1;
	m_lpBmpInfoHead->biBitCount = m_nBitCount;
	m_lpBmpInfoHead->biCompression = BI_RGB;
	m_lpBmpInfoHead->biSizeImage = 0;
	m_lpBmpInfoHead->biXPelsPerMeter = 0;
	m_lpBmpInfoHead->biYPelsPerMeter = 0;
	m_lpBmpInfoHead->biClrUsed = m_nColorTableLength;
	m_lpBmpInfoHead->biClrImportant = m_nColorTableLength;
	m_hPalette = NULL;
	if(m_nColorTableLength!=0)
	{
		m_lpColorTable=(LPRGBQUAD)(m_lpDib+sizeof(BITMAPINFOHEADER));
		memcpy(m_lpColorTable,lpColorTable,sizeof(RGBQUAD) * m_nColorTableLength);
		MakePalette();
	}
	m_pImgData = (LPBYTE)m_lpDib+sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD) * m_nColorTableLength;
	memcpy(m_pImgData,pImgData,imgBufSize);
}
void ImageDib::Empty()
{
	if (m_lpDib != NULL)
	{
		delete[] m_lpDib;
		m_lpDib = NULL;
		m_lpColorTable = NULL;
		m_pImgData = NULL;
		m_lpBmpInfoHead = NULL;
	}
	if(m_hPalette != NULL)
	{
		::DeleteObject(m_hPalette);
		m_hPalette = NULL;
	}
}
