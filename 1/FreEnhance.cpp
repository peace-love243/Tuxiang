#include "stdafx.h"
#include "FreEnhance.h"
#include "1.h"
#include "math.h"
#include <direct.h>
FreEnhance::FreEnhance()
{
	m_pImgDataOut = NULL;
	m_lpColorTableOut = NULL;
	m_nColorTableLengthOut = 0;
	m_nBitCountOut = 0;	
	m_imgWidthOut = 0;
	m_imgHeightOut = 0;	
}
FreEnhance::FreEnhance(CSize size, int nBitCount,LPRGBQUAD lpColorTable, unsigned char *pImgData) :
	        ImageDib(size, nBitCount, lpColorTable, pImgData)
{
	m_nBitCountOut = m_nBitCount;
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);
	m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
	memcpy(m_lpColorTableOut, m_lpColorTable, sizeof(RGBQUAD)*m_nColorTableLengthOut);
	m_pImgDataOut = NULL;
}
FreEnhance::~FreEnhance()
{
	if (m_pImgDataOut != NULL)
	{
		delete[]m_pImgDataOut;
		m_pImgDataOut = NULL;
	}
	if (m_lpColorTableOut != NULL) 
	{
		delete[]m_lpColorTableOut;
		m_lpColorTableOut = NULL;
	}
}
void FreEnhance::InputImageData(CSize size, int nBitCount,LPRGBQUAD lpColorTable, unsigned char *pImgData)
{	        //调用基类成员函数ReplaceDib创建输入图像的DIB结构，并清理缓冲区，初始化输出图像的颜色表，为图像快速傅立叶变换做准
	ReplaceDib(size, nBitCount, lpColorTable, pImgData);
	if (m_pImgDataOut != NULL) 
	{
		delete[]m_pImgDataOut;
		m_pImgDataOut = NULL;
	}
	m_nBitCountOut = m_nBitCount;
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);
	m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
	memcpy(m_lpColorTableOut, m_lpColorTable, sizeof(RGBQUAD)*m_nColorTableLengthOut);
}
CSize FreEnhance::GetDimensions()
{
	return CSize(m_imgWidthOut, m_imgHeightOut);
}
void FreEnhance::IdealLowPassFilter(int nWidth, int nHeight, int nRadius)
{
	int y;
	int x;
	double dTmpOne;
	double dTmpTwo;
	int nTransWidth;                  // 傅立叶变换的宽度和高度（2的整数次幂）
	int nTransHeight;
	dTmpOne = log(nWidth) / log(2);
	dTmpTwo = ceil(dTmpOne);
	dTmpTwo = pow(2, dTmpTwo);
	nTransWidth = (int)dTmpTwo;
	dTmpOne = log(nHeight) / log(2);
	dTmpTwo = ceil(dTmpOne);
	dTmpTwo = pow(2, dTmpTwo);
	nTransHeight = (int)dTmpTwo;
	if (nRadius>nTransWidth - 1 || nRadius>nTransHeight - 1)// 低通滤波的半径不能超过频域的最大半径
	{
		return;
	}
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;
	m_pImgDataOut = new unsigned char[m_imgWidthOut*m_imgHeightOut];
	memset(m_pImgDataOut, 0, m_imgWidthOut*m_imgHeightOut);
	FFtTrans.m_pFFTBuf = new ComplexNumber[m_imgWidthOut*m_imgHeightOut];
	memset(FFtTrans.m_pFFTBuf, 0, sizeof(ComplexNumber)*m_imgWidthOut*m_imgHeightOut);
	FFtTrans.ImageFFt2D(m_pImgData, m_imgWidthOut, m_imgHeightOut, m_pImgDataOut);
	for (y = nRadius; y<nTransHeight; y++)
	{
		for (x = nRadius; x<nTransWidth; x++)
		{
			FFtTrans.m_pFFTBuf[y*nTransWidth + x].real = 0;
			FFtTrans.m_pFFTBuf[y*nTransWidth + x].imag = 0;
		}
	}
	FFtTrans.ImageRevFFt2D(m_pImgDataOut, nWidth, nHeight);
}
void FreEnhance::ButterLowPassFilter(int nWidth, int nHeight, int nRadius)
{
	int y;
	int x;
	double dTmpOne;
	double dTmpTwo;
	double H;
	int nTransWidth;
	int nTransHeight;
	dTmpOne = log(nWidth) / log(2);
	dTmpTwo = ceil(dTmpOne);
	dTmpTwo = pow(2, dTmpTwo);
	nTransWidth = (int)dTmpTwo;
	dTmpOne = log(nHeight) / log(2);
	dTmpTwo = ceil(dTmpOne);
	dTmpTwo = pow(2, dTmpTwo);
	nTransHeight = (int)dTmpTwo;
	if (nRadius>nTransWidth - 1 || nRadius>nTransHeight - 1)
	{
		return;
	}
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;
	m_pImgDataOut = new unsigned char[m_imgWidthOut*m_imgHeightOut];
	memset(m_pImgDataOut, 0, m_imgWidthOut*m_imgHeightOut);
	FFtTrans.m_pFFTBuf = new ComplexNumber[m_imgWidthOut*m_imgHeightOut];
	memset(FFtTrans.m_pFFTBuf, 0, sizeof(ComplexNumber)*m_imgWidthOut*m_imgHeightOut);
	FFtTrans.ImageFFt2D(m_pImgData, m_imgWidthOut, m_imgHeightOut, m_pImgDataOut);       //输入图像数据进行二维傅立叶变换
	for (y = 0; y<nTransHeight; y++)               // 下面开始实施ButterWorth低通滤波
	{
		for (x = 0; x<nTransWidth; x++)
		{
			H = (double)(y*y + x*x);
			H = H / (nRadius * nRadius);
			H = 1 / (1 + H);
			FFtTrans.m_pFFTBuf[y*nTransWidth + x].real = (FFtTrans.m_pFFTBuf[y*nTransWidth + x].real)*H;
			FFtTrans.m_pFFTBuf[y*nTransWidth + x].imag = (FFtTrans.m_pFFTBuf[y*nTransWidth + x].imag)*H;
		}
	}
	FFtTrans.ImageRevFFt2D(m_pImgDataOut, nWidth, nHeight);               // 经过低通滤波的图象进行反变换
}
void FreEnhance::IdealHighPassFilter(int nWidth, int nHeight, int nRadius)
{
	int y;
	int x;
	double dTmpOne;
	double dTmpTwo;
	double dReal;               // 傅立叶变换的实部和虚部
	double dImag;
	unsigned char unchValue;	// 图象象素值
	int nTransWidth;
	int nTransHeight;
	dTmpOne = log(nWidth) / log(2);
	dTmpTwo = ceil(dTmpOne);
	dTmpTwo = pow(2, dTmpTwo);
	nTransWidth = (int)dTmpTwo;
	dTmpOne = log(nHeight) / log(2);
	dTmpTwo = ceil(dTmpOne);
	dTmpTwo = pow(2, dTmpTwo);
	nTransHeight = (int)dTmpTwo;
	if (nRadius>nTransWidth - 1 || nRadius>nTransHeight - 1)
	{
		return;
	}
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;
	m_pImgDataOut = new unsigned char[m_imgWidthOut*m_imgHeightOut];
	memset(m_pImgDataOut, 0, m_imgWidthOut*m_imgHeightOut);
	FFtTrans.m_pFFTBuf = new ComplexNumber[m_imgWidthOut*m_imgHeightOut];
	memset(FFtTrans.m_pFFTBuf, 0, sizeof(ComplexNumber)*m_imgWidthOut*m_imgHeightOut);
	FFtTrans.ImageFFt2D(m_pImgData, m_imgWidthOut, m_imgHeightOut, m_pImgDataOut);
	for (y = 0; y<nRadius; y++)                                               // 理想高通滤波
	{
		for (x = 0; x<nRadius; x++)
		{
			FFtTrans.m_pFFTBuf[y*nTransWidth + x].real = 0;
			FFtTrans.m_pFFTBuf[y*nTransWidth + x].imag = 0;
		}
	}
	FFtTrans.ImageRevFFt2D(m_pImgDataOut, nWidth, nHeight);
	for (y = 0; y<nHeight; y++)
	{
		for (x = 0; x<nWidth; x++)
		{
			dReal = FFtTrans.m_pFFTBuf[y*nTransWidth + x].real;
			dImag = FFtTrans.m_pFFTBuf[y*nTransWidth + x].imag;
			unchValue = (unsigned char)max(0, min(255, sqrt(dReal*dReal + dImag*dImag) + 100));
			m_pImgDataOut[y*nWidth + x] = unchValue;
		}
	}
}
void FreEnhance::ButterHighPassFilter(int nWidth, int nHeight, int nRadius)
{
	int y;
	int x;
	double dTmpOne;
	double dTmpTwo;
	double H;
	double dReal;
	double dImag;
	unsigned char unchValue;	
	int nTransWidth;
	int nTransHeight;
	dTmpOne = log(nWidth) / log(2);
	dTmpTwo = ceil(dTmpOne);
	dTmpTwo = pow(2, dTmpTwo);
	nTransWidth = (int)dTmpTwo;
	dTmpOne = log(nHeight) / log(2);
	dTmpTwo = ceil(dTmpOne);
	dTmpTwo = pow(2, dTmpTwo);
	nTransHeight = (int)dTmpTwo;
	if (nRadius>nTransWidth - 1 || nRadius>nTransHeight - 1)
	{
		return;
	}
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;
	m_pImgDataOut = new unsigned char[m_imgWidthOut*m_imgHeightOut];
	memset(m_pImgDataOut, 0, m_imgWidthOut*m_imgHeightOut);
	FFtTrans.m_pFFTBuf = new ComplexNumber[m_imgWidthOut*m_imgHeightOut];
	memset(FFtTrans.m_pFFTBuf, 0, sizeof(ComplexNumber)*m_imgWidthOut*m_imgHeightOut);
	FFtTrans.ImageFFt2D(m_pImgData, m_imgWidthOut, m_imgHeightOut, m_pImgDataOut);
	for (y = 0; y<nTransHeight; y++)                                      //ButterWorth低通滤波
	{
		for (x = 0; x<nTransWidth; x++)
		{
			H = (double)(y*y + x*x);
			H = (nRadius * nRadius) / H;
			H = 1 / (1 + H);
			FFtTrans.m_pFFTBuf[y*nTransWidth + x].real = (FFtTrans.m_pFFTBuf[y*nTransWidth + x].real)*H;
			FFtTrans.m_pFFTBuf[y*nTransWidth + x].imag = (FFtTrans.m_pFFTBuf[y*nTransWidth + x].imag)*H;
		}
	}
	FFtTrans.ImageRevFFt2D(m_pImgDataOut, nWidth, nHeight);
	for (y = 0; y<nHeight; y++)
	{
		for (x = 0; x<nWidth; x++)
		{
			dReal = FFtTrans.m_pFFTBuf[y*nTransWidth + x].real;
			dImag = FFtTrans.m_pFFTBuf[y*nTransWidth + x].imag;
			unchValue = (unsigned char)max(0, min(255, sqrt(dReal*dReal + dImag*dImag) + 100));
			m_pImgDataOut[y*nWidth + x] = unchValue;
		}
	}
}
