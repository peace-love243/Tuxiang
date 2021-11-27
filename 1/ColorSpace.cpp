#include "stdafx.h"
#include "ColorSpace.h"
#define MIN(x,y) ((x)<(y)?(x):(y))

ColorSpace::ColorSpace()
{
	m_nBitCountOut = 0;
	m_pImgDataOut = NULL;
	m_lpColorTableOut = NULL;
	m_imgWidthOut = 0;
	m_imgHeightOut = 0;
	m_nColorTableLengthOut = 0;
}
ColorSpace::ColorSpace(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData) :
	ImageDib(size, nBitCount, lpColorTable, pImgData)
{
	m_pImgDataOut = NULL;//输出图像位图数据指针为空
	m_lpColorTableOut = NULL;//输出图像颜色表指针为空
	m_nColorTableLengthOut = 0;//输出图像颜色表长度为0
	m_nBitCountOut = 0;//输出图像每像素位数为0
	m_imgWidthOut = 0;//输出图像的宽为0
	m_imgHeightOut = 0;//输出图像的高为0
}
ColorSpace::~ColorSpace()
{
	if (m_pImgDataOut != NULL)//释放输出图像位图数据缓冲区
	{
		delete[]m_pImgDataOut;
		m_pImgDataOut = NULL;
	}
	if (m_lpColorTableOut != NULL)//释放输出图像颜色表
	{
		delete[]m_lpColorTableOut;
		m_lpColorTableOut = NULL;
	}
}
CSize ColorSpace::GetDimensions()
{
	if (m_pImgDataOut == NULL)
		return CSize(0, 0);
	return CSize(m_imgWidthOut, m_imgHeightOut);
}
void ColorSpace::RGBR()
{
	if (m_nBitCount == 8)
		return;
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
	m_nBitCountOut = 8;
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);
	if (m_nColorTableLengthOut != 0)
	{
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		for (int i = 0; i < m_nColorTableLengthOut; i++)
		{
			m_lpColorTableOut[i].rgbBlue = i;
			m_lpColorTableOut[i].rgbGreen = i;
			m_lpColorTableOut[i].rgbRed = i;
			m_lpColorTableOut[i].rgbReserved = 0;
		}
	}
	int pixelByteIn = 3;
	int lineByteIn = (m_imgWidth*pixelByteIn + 3) / 4 * 4;
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;
	int lineByteOut = (m_imgWidth*m_nBitCountOut / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeight];
	int i, j;
	for (i = 0; i < m_imgHeight; i++)
	{
		for (j = 0; j < m_imgWidth; j++)
			*(m_pImgDataOut + i*lineByteOut + j) = *(m_pImgData + i*lineByteIn + j*pixelByteIn + 0);           //提取红色分量
	}
}
void ColorSpace::RGBG()
{
	if (m_nBitCount == 8)
		return;
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
	m_nBitCountOut = 8;
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);
	if (m_nColorTableLengthOut != 0)
	{
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		for (int i = 0; i < m_nColorTableLengthOut; i++)
		{
			m_lpColorTableOut[i].rgbBlue = i;
			m_lpColorTableOut[i].rgbGreen = i;
			m_lpColorTableOut[i].rgbRed = i;
			m_lpColorTableOut[i].rgbReserved = 0;
		}
	}
	int pixelByteIn = 3;
	int lineByteIn = (m_imgWidth*pixelByteIn + 3) / 4 * 4;
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;
	int lineByteOut = (m_imgWidth*m_nBitCountOut / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeight];
	int i, j;
	for (i = 0; i < m_imgHeight; i++)
	{
		for (j = 0; j < m_imgWidth; j++)
			*(m_pImgDataOut + i*lineByteOut + j) = *(m_pImgData + i*lineByteIn + j*pixelByteIn + 1);   //提取绿色分量
	}
}
void ColorSpace::RGBB()
{
	if (m_nBitCount == 8)
		return;
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
	m_nBitCountOut = 8;
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);
	if (m_nColorTableLengthOut != 0)
	{
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		for (int i = 0; i < m_nColorTableLengthOut; i++)
		{
			m_lpColorTableOut[i].rgbBlue = i;
			m_lpColorTableOut[i].rgbGreen = i;
			m_lpColorTableOut[i].rgbRed = i;
			m_lpColorTableOut[i].rgbReserved = 0;
		}
	}
	int pixelByteIn = 3;
	int lineByteIn = (m_imgWidth*pixelByteIn + 3) / 4 * 4;
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;
	int lineByteOut = (m_imgWidth*m_nBitCountOut / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeight];
	int i, j;
	for (i = 0; i < m_imgHeight; i++)
	{
		for (j = 0; j < m_imgWidth; j++)
			*(m_pImgDataOut + i*lineByteOut + j) = *(m_pImgData + i*lineByteIn + j*pixelByteIn + 2);    //提取蓝色分量
	}
}
void ColorSpace::RGB2YCBCR1()
{
	BYTE Y, CB, CR;
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
	m_nBitCountOut = m_nBitCount;
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);
	if (m_nColorTableLengthOut != 0)
	{
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut, m_lpColorTable, sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;
	int lineByteOut = (m_imgWidth*m_nBitCountOut / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeight];
	int i, j, k;
	int pixelByte = m_nBitCountOut / 8;
	for (i = 0; i < m_imgHeight; i++)
	{
		for (j = 0; j < m_imgWidth; j++)
		{
			Y = 0.257**(m_pImgData + i*lineByteOut + j*pixelByte + 0) + 0.504**(m_pImgData + i*lineByteOut + j*pixelByte + 1) + 0.098**(m_pImgData + i*lineByteOut + j*pixelByte + 2) + 16;
			CB = -0.148**(m_pImgData + i*lineByteOut + j*pixelByte + 0) - 0.219**(m_pImgData + i*lineByteOut + j*pixelByte + 1) + 0.439**(m_pImgData + i*lineByteOut + j*pixelByte + 2) + 128;
			CR = 0.439**(m_pImgData + i*lineByteOut + j*pixelByte + 0) - 0.368**(m_pImgData + i*lineByteOut + j*pixelByte + 1) - 0.071**(m_pImgData + i*lineByteOut + j*pixelByte + 2) + 128;
			*(m_pImgDataOut + i*lineByteOut + j*pixelByte + 0) = Y;
			*(m_pImgDataOut + i*lineByteOut + j*pixelByte + 1) = CB;
			*(m_pImgDataOut + i*lineByteOut + j*pixelByte + 2) = CR;
		}
	}
}
void ColorSpace::RGB2Y()
{
	BYTE Y, CB, CR;
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
	m_nBitCountOut = m_nBitCount;
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);
	if (m_nColorTableLengthOut != 0)
	{
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut, m_lpColorTable, sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;
	int lineByteOut = (m_imgWidth*m_nBitCountOut / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeight];
	int i, j, k;
	int pixelByte = m_nBitCountOut / 8;
	for (i = 0; i < m_imgHeight; i++)
	{
		for (j = 0; j < m_imgWidth; j++)
		{
			Y = 0.257**(m_pImgData + i*lineByteOut + j*pixelByte + 0) + 0.504**(m_pImgData + i*lineByteOut + j*pixelByte + 1) + 0.098**(m_pImgData + i*lineByteOut + j*pixelByte + 2) + 16;
			CB = -0.148**(m_pImgData + i*lineByteOut + j*pixelByte + 0) - 0.219**(m_pImgData + i*lineByteOut + j*pixelByte + 1) + 0.439**(m_pImgData + i*lineByteOut + j*pixelByte + 2) + 128;
			CR = 0.439**(m_pImgData + i*lineByteOut + j*pixelByte + 0) - 0.368**(m_pImgData + i*lineByteOut + j*pixelByte + 1) - 0.071**(m_pImgData + i*lineByteOut + j*pixelByte + 2) + 128;
			for (k = 0; k < pixelByte; k++)
				*(m_pImgDataOut + i*lineByteOut + j*pixelByte + k) = Y;
		}
	}
}
void ColorSpace::RGB2CB()
{
	BYTE Y, CB, CR;
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
	m_nBitCountOut = m_nBitCount;
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);
	if (m_nColorTableLengthOut != 0)
	{
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut, m_lpColorTable, sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;
	int lineByteOut = (m_imgWidth*m_nBitCountOut / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeight];
	int i, j, k;
	int pixelByte = m_nBitCountOut / 8;
	for (i = 0; i < m_imgHeight; i++)
	{
		for (j = 0; j < m_imgWidth; j++)
		{
			Y = 0.257**(m_pImgData + i*lineByteOut + j*pixelByte + 0) + 0.504**(m_pImgData + i*lineByteOut + j*pixelByte + 1) + 0.098**(m_pImgData + i*lineByteOut + j*pixelByte + 2) + 16;
			CB = -0.148**(m_pImgData + i*lineByteOut + j*pixelByte + 0) - 0.219**(m_pImgData + i*lineByteOut + j*pixelByte + 1) + 0.439**(m_pImgData + i*lineByteOut + j*pixelByte + 2) + 128;
			CR = 0.439**(m_pImgData + i*lineByteOut + j*pixelByte + 0) - 0.368**(m_pImgData + i*lineByteOut + j*pixelByte + 1) - 0.071**(m_pImgData + i*lineByteOut + j*pixelByte + 2) + 128;
			for (k = 0; k < pixelByte; k++)
				*(m_pImgDataOut + i*lineByteOut + j*pixelByte + k) = CB;
		}
	}
}
void ColorSpace::RGB2CR()
{
	BYTE Y, CB, CR;
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
	m_nBitCountOut = m_nBitCount;
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);
	if (m_nColorTableLengthOut != 0)
	{
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut, m_lpColorTable, sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;
	int lineByteOut = (m_imgWidth*m_nBitCountOut / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeight];
	int i, j, k;
	int pixelByte = m_nBitCountOut / 8;
	for (i = 0; i < m_imgHeight; i++)
	{
		for (j = 0; j < m_imgWidth; j++)
		{
			Y = 0.257**(m_pImgData + i*lineByteOut + j*pixelByte + 0) + 0.504**(m_pImgData + i*lineByteOut + j*pixelByte + 1) + 0.098**(m_pImgData + i*lineByteOut + j*pixelByte + 2) + 16;
			CB = -0.148**(m_pImgData + i*lineByteOut + j*pixelByte + 0) - 0.219**(m_pImgData + i*lineByteOut + j*pixelByte + 1) + 0.439**(m_pImgData + i*lineByteOut + j*pixelByte + 2) + 128;
			CR = 0.439**(m_pImgData + i*lineByteOut + j*pixelByte + 0) - 0.368**(m_pImgData + i*lineByteOut + j*pixelByte + 1) - 0.071**(m_pImgData + i*lineByteOut + j*pixelByte + 2) + 128;
			for (k = 0; k < pixelByte; k++)
				*(m_pImgDataOut + i*lineByteOut + j*pixelByte + k) = CR;
		}
	}
}
void ColorSpace::RGB2YCBCRJIAQUAN()
{
	BYTE Y, CB, CR;
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
	m_nBitCountOut = m_nBitCount;
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);
	if (m_nColorTableLengthOut != 0)
	{
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut, m_lpColorTable, sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;
	int lineByteOut = (m_imgWidth*m_nBitCountOut / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeight];
	int i, j, k;
	int pixelByte = m_nBitCountOut / 8;
	for (i = 0; i < m_imgHeight; i++)
	{
		for (j = 0; j < m_imgWidth; j++)
		{
			Y = 0.257**(m_pImgData + i*lineByteOut + j*pixelByte + 0) + 0.504**(m_pImgData + i*lineByteOut + j*pixelByte + 1) + 0.098**(m_pImgData + i*lineByteOut + j*pixelByte + 2) + 16;
			CB = -0.148**(m_pImgData + i*lineByteOut + j*pixelByte + 0) - 0.219**(m_pImgData + i*lineByteOut + j*pixelByte + 1) + 0.439**(m_pImgData + i*lineByteOut + j*pixelByte + 2) + 128;
			CR = 0.439**(m_pImgData + i*lineByteOut + j*pixelByte + 0) - 0.368**(m_pImgData + i*lineByteOut + j*pixelByte + 1) - 0.071**(m_pImgData + i*lineByteOut + j*pixelByte + 2) + 128;
			for (k = 0; k < pixelByte; k++)
				*(m_pImgDataOut + i*lineByteOut + j*pixelByte + k) = 0.05*Y + 0.85*CB + 0.10*CR;
		}
	}
}
void ColorSpace::RGB2LAB1()
{
	BYTE L, A, B;
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
	m_nBitCountOut = m_nBitCount;
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);
	if (m_nColorTableLengthOut != 0)
	{
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut, m_lpColorTable, sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;
	int lineByteOut = (m_imgWidth*m_nBitCountOut / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeight];
	int i, j, k;
	int pixelByte = m_nBitCountOut / 8;
	for (i = 0; i < m_imgHeight; i++)
	{
		for (j = 0; j < m_imgWidth; j++)
		{
			L = 0.2126007**(m_pImgData + i*lineByteOut + j*pixelByte + 0) + 0.7151947**(m_pImgData + i*lineByteOut + j*pixelByte + 1) + 0.0722046**(m_pImgData + i*lineByteOut + j*pixelByte + 2);
			A = 0.3258962**(m_pImgData + i*lineByteOut + j*pixelByte + 0) - 0.4992596**(m_pImgData + i*lineByteOut + j*pixelByte + 1) + 0.1733409**(m_pImgData + i*lineByteOut + j*pixelByte + 2) + 128;
			B = 0.1218128**(m_pImgData + i*lineByteOut + j*pixelByte + 0) + 0.3785610**(m_pImgData + i*lineByteOut + j*pixelByte + 1) - 0.5003738**(m_pImgData + i*lineByteOut + j*pixelByte + 2) + 128;
			*(m_pImgDataOut + i*lineByteOut + j*pixelByte + 0) = L;
			*(m_pImgDataOut + i*lineByteOut + j*pixelByte + 1) = A;
			*(m_pImgDataOut + i*lineByteOut + j*pixelByte + 2) = B;
		}
	}
}
void ColorSpace::RGB2L()
{
	BYTE L, A, B;
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
	m_nBitCountOut = m_nBitCount;
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);
	if (m_nColorTableLengthOut != 0)
	{
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut, m_lpColorTable, sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;
	int lineByteOut = (m_imgWidth*m_nBitCountOut / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeight];
	int i, j, k;
	int pixelByte = m_nBitCountOut / 8;
	for (i = 0; i < m_imgHeight; i++)
	{
		for (j = 0; j < m_imgWidth; j++)
		{
			L = 0.2126007**(m_pImgData + i*lineByteOut + j*pixelByte + 0) + 0.7151947**(m_pImgData + i*lineByteOut + j*pixelByte + 1) + 0.0722046**(m_pImgData + i*lineByteOut + j*pixelByte + 2);
			A = 0.3258962**(m_pImgData + i*lineByteOut + j*pixelByte + 0) - 0.4992596**(m_pImgData + i*lineByteOut + j*pixelByte + 1) + 0.1733409**(m_pImgData + i*lineByteOut + j*pixelByte + 2) + 128;
			B = 0.1218128**(m_pImgData + i*lineByteOut + j*pixelByte + 0) + 0.3785610**(m_pImgData + i*lineByteOut + j*pixelByte + 1) - 0.5003738**(m_pImgData + i*lineByteOut + j*pixelByte + 2) + 128;
			for (k = 0; k < pixelByte; k++)
				*(m_pImgDataOut + i*lineByteOut + j*pixelByte + k) = L;
		}
	}
}
void ColorSpace::RGB2A()
{
	BYTE L, A, B;
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
	m_nBitCountOut = m_nBitCount;
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);
	if (m_nColorTableLengthOut != 0)
	{
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut, m_lpColorTable, sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;
	int lineByteOut = (m_imgWidth*m_nBitCountOut / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeight];
	int i, j, k;
	int pixelByte = m_nBitCountOut / 8;
	for (i = 0; i < m_imgHeight; i++)
	{
		for (j = 0; j < m_imgWidth; j++)
		{
			L = 0.2126007**(m_pImgData + i*lineByteOut + j*pixelByte + 0) + 0.7151947**(m_pImgData + i*lineByteOut + j*pixelByte + 1) + 0.0722046**(m_pImgData + i*lineByteOut + j*pixelByte + 2);
			A = 0.3258962**(m_pImgData + i*lineByteOut + j*pixelByte + 0) - 0.4992596**(m_pImgData + i*lineByteOut + j*pixelByte + 1) + 0.1733409**(m_pImgData + i*lineByteOut + j*pixelByte + 2) + 128;
			B = 0.1218128**(m_pImgData + i*lineByteOut + j*pixelByte + 0) + 0.3785610**(m_pImgData + i*lineByteOut + j*pixelByte + 1) - 0.5003738**(m_pImgData + i*lineByteOut + j*pixelByte + 2) + 128;
			for (k = 0; k < pixelByte; k++)
				*(m_pImgDataOut + i*lineByteOut + j*pixelByte + k) = A;
		}
	}
}
void ColorSpace::RGB2B()
{
	BYTE L, A, B;
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
	m_nBitCountOut = m_nBitCount;
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);
	if (m_nColorTableLengthOut != 0)
	{
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut, m_lpColorTable, sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;
	int lineByteOut = (m_imgWidth*m_nBitCountOut / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeight];
	int i, j, k;
	int pixelByte = m_nBitCountOut / 8;
	for (i = 0; i < m_imgHeight; i++)
	{
		for (j = 0; j < m_imgWidth; j++)
		{
			L = 0.2126007**(m_pImgData + i*lineByteOut + j*pixelByte + 0) + 0.7151947**(m_pImgData + i*lineByteOut + j*pixelByte + 1) + 0.0722046**(m_pImgData + i*lineByteOut + j*pixelByte + 2);
			A = 0.3258962**(m_pImgData + i*lineByteOut + j*pixelByte + 0) - 0.4992596**(m_pImgData + i*lineByteOut + j*pixelByte + 1) + 0.1733409**(m_pImgData + i*lineByteOut + j*pixelByte + 2) + 128;
			B = 0.1218128**(m_pImgData + i*lineByteOut + j*pixelByte + 0) + 0.3785610**(m_pImgData + i*lineByteOut + j*pixelByte + 1) - 0.5003738**(m_pImgData + i*lineByteOut + j*pixelByte + 2) + 128;
			for (k = 0; k < pixelByte; k++)
				*(m_pImgDataOut + i*lineByteOut + j*pixelByte + k) = B;
		}
	}
}
void ColorSpace::RGB2LABJQ()
{
	BYTE L, A, B;
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
	m_nBitCountOut = m_nBitCount;
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);
	if (m_nColorTableLengthOut != 0)
	{
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut, m_lpColorTable, sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;
	int lineByteOut = (m_imgWidth*m_nBitCountOut / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeight];
	int i, j, k;
	int pixelByte = m_nBitCountOut / 8;
	for (i = 0; i < m_imgHeight; i++)
	{
		for (j = 0; j < m_imgWidth; j++)
		{
			L = 0.2126007**(m_pImgData + i*lineByteOut + j*pixelByte + 0) + 0.7151947**(m_pImgData + i*lineByteOut + j*pixelByte + 1) + 0.0722046**(m_pImgData + i*lineByteOut + j*pixelByte + 2);
			A = 0.3258962**(m_pImgData + i*lineByteOut + j*pixelByte + 0) - 0.4992596**(m_pImgData + i*lineByteOut + j*pixelByte + 1) + 0.1733409**(m_pImgData + i*lineByteOut + j*pixelByte + 2) + 128;
			B = 0.1218128**(m_pImgData + i*lineByteOut + j*pixelByte + 0) + 0.3785610**(m_pImgData + i*lineByteOut + j*pixelByte + 1) - 0.5003738**(m_pImgData + i*lineByteOut + j*pixelByte + 2) + 128;
			for (k = 0; k < pixelByte; k++)
				*(m_pImgDataOut + i*lineByteOut + j*pixelByte + k) = 0.2*L + 0.5*A + 0.3*B;
		}
	}
}
void ColorSpace::RGB2CMYK()
{
	int C, M, Y;
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
	m_nBitCountOut = m_nBitCount;
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);
	if (m_nColorTableLengthOut != 0)
	{
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut, m_lpColorTable, sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;
	int lineByteOut = (m_imgWidth*m_nBitCountOut / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeight];
	int i, j, k;
	int pixelByte = m_nBitCountOut / 8;
	for (i = 0; i < m_imgHeight; i++)
	{
		for (j = 0; j < m_imgWidth; j++)
		{
			C = 1 - *(m_pImgData + i*lineByteOut + j*pixelByte + 0) / 255;
			M = 1 - *(m_pImgData + i*lineByteOut + j*pixelByte + 1) / 255;
			Y = 1 - *(m_pImgData + i*lineByteOut + j*pixelByte + 2) / 255;
			*(m_pImgDataOut + i*lineByteOut + j*pixelByte + 0) = C * 255;
			*(m_pImgDataOut + i*lineByteOut + j*pixelByte + 1) = M * 255;
			*(m_pImgDataOut + i*lineByteOut + j*pixelByte + 2) = Y * 255;
		}
	}
}
void ColorSpace::RGB2HSI()
{
	int h = 0, s = 0, i = 0, H, S, I;
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
	m_nBitCountOut = m_nBitCount;
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);
	if (m_nColorTableLengthOut != 0)
	{
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut, m_lpColorTable, sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;
	int lineByteOut = (m_imgWidth*m_nBitCountOut / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeight];
	int l, j, k;
	int pixelByte = m_nBitCountOut / 8;
	for (l = 0; l < m_imgHeight; l++)
	{
		for (j = 0; j < m_imgWidth; j++)
		{
			h = *(m_pImgData + i*lineByteOut + j*pixelByte + 0) / 255;
			s = *(m_pImgData + i*lineByteOut + j*pixelByte + 1) / 255;
			i = *(m_pImgData + i*lineByteOut + j*pixelByte + 2) / 255;
			H = acos(0.5*((h - s) + (h - i)) / sqrt(double((h - s)*(h - s) + (h - i)*(s - i))));
			I = (h + s + i) / 3.0;
			S = I - 3.0 *MIN(h, MIN(s, i)) / (h + s + i);
			*(m_pImgDataOut + l*lineByteOut + j*pixelByte + 0) = H * 255;
			*(m_pImgDataOut + l*lineByteOut + j*pixelByte + 1) = S * 255;
			*(m_pImgDataOut + l*lineByteOut + j*pixelByte + 2) = I * 255;
		}
	}
}
