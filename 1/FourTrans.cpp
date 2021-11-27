#include "stdafx.h"
#include "1.h"
#include "FourTrans.h"
#include "math.h"
FourTrans::FourTrans()
{
	m_pImgDataOut = NULL;
	m_lpColorTableOut = NULL;
	m_nColorTableLengthOut = 0;
	m_nBitCountOut = 0;	
	m_imgWidthOut = 0;
	m_imgHeightOut = 0;	
	m_pFFTBuf = NULL;
}
FourTrans::~FourTrans()
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
	if (m_pFFTBuf != NULL) 
	{
		delete m_pFFTBuf;
		m_pFFTBuf = NULL;
	}
}
FourTrans::FourTrans(CSize size, int nBitCount,LPRGBQUAD lpColorTable, unsigned char *pImgData) :
	ImageDib(size, nBitCount, lpColorTable, pImgData)
{
	m_nBitCountOut = m_nBitCount;
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);
	m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
	memcpy(m_lpColorTableOut, m_lpColorTable, sizeof(RGBQUAD)*m_nColorTableLengthOut);
	m_pImgDataOut = NULL;
	m_pFFTBuf = NULL;
}
void FourTrans::InputImgData(CSize size, int nBitCount,LPRGBQUAD lpColorTable, unsigned char *pImgData)
{
	ReplaceDib(size, nBitCount, lpColorTable, pImgData);
	if (m_pImgDataOut != NULL) 
	{
		delete[]m_pImgDataOut;
		m_pImgDataOut = NULL;
	}
	if (m_pFFTBuf != NULL)
	{
		delete m_pFFTBuf;
		m_pFFTBuf = NULL;
	}
	m_nBitCountOut = m_nBitCount;
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);
	m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
	memcpy(m_lpColorTableOut, m_lpColorTable, sizeof(RGBQUAD)*m_nColorTableLengthOut);
}
CSize FourTrans::GetDimensions()                           
{
	return CSize(m_imgWidthOut, m_imgHeightOut);
}
void FourTrans::Fourier()                  //������ͼ����п��ٸ���Ҷ�任
{
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;
	m_pImgDataOut = new unsigned char[m_imgWidthOut*m_imgHeightOut];
	memset(m_pImgDataOut, 0, m_imgWidthOut*m_imgHeightOut);
	m_pFFTBuf = new ComplexNumber[m_imgWidthOut*m_imgHeightOut];
	memset(m_pFFTBuf, 0, sizeof(ComplexNumber)*m_imgWidthOut*m_imgHeightOut);
	ImageFFt2D(m_pImgData, m_imgWidthOut, m_imgHeightOut, m_pImgDataOut);             //����ͼ�����ݽ��ж�ά����Ҷ�任
}
void FourTrans::RevFourier()                                     //����ͼ��Ŀ��ٸ���Ҷ���任
{
	ImageRevFFt2D(m_pImgDataOut, m_imgWidthOut, m_imgHeightOut);
}
void FourTrans::ImageFFt1D(ComplexNumber *arrayBuf, int n)               //�Ը����ṹ������arrayBuf����һά���ٸ���Ҷ�任
{
	int i, k, r;
	ComplexNumber *buf1 = new ComplexNumber[n];
	memcpy(buf1, arrayBuf, sizeof(ComplexNumber)*n);            //��arrayBuf������buf1
	ComplexNumber *buf2 = new ComplexNumber[n];
	int t1, t2;
	for (r = 1; pow(2, r)<n; r++) 
	{
		t1 = pow(2, r);
		t2 = pow(2, r - 1);
		for (k = 0; k<t1; k++) 
		{
			for (i = 0; i<n / t1; i++)
			{
				buf2[k*n / t1 + i].real = buf1[k / 2 * n / t2 + i * 2 + k % 2].real;
				buf2[k*n / t1 + i].imag = buf1[k / 2 * n / t2 + i * 2 + k % 2].imag;
			}
		}
		memcpy(buf1, buf2, sizeof(ComplexNumber)*n);
	}
	float c, s;                                    //buf1�ǵ�r�������룬buf2��ŵ�r�������
	for (r = 1; pow(2, r) <= n; r++)
	{
		t1 = pow(2, r);
		for (k = 0; k<n / t1; k++) 
		{
			for (i = t1 / 2; i<t1; i++) 
			{
				c = cos(-2 * PI*(i - t1 / 2) / t1);                     //��Ȩ����
				s = sin(-2 * PI*(i - t1 / 2) / t1);
				buf1[k*t1 + i].real = buf2[k*t1 + i].real*c - buf2[k*t1 + i].imag*s;
				buf1[k*t1 + i].imag = buf2[k*t1 + i].imag*c + buf2[k*t1 + i].real*s;
			}
		}
		for (k = 0; k<n / t1; k++) 
		{
			for (i = 0; i<t1 / 2; i++)
			{
				buf2[k*t1 + i].real = buf1[k*t1 + i].real + buf1[k*t1 + i + t1 / 2].real;
				buf2[k*t1 + i].imag = buf1[k*t1 + i].imag + buf1[k*t1 + i + t1 / 2].imag;
			}
			for (i = t1 / 2; i<t1; i++) 
			{
				buf2[k*t1 + i].real = buf1[k*t1 + i - t1 / 2].real - buf1[k*t1 + i].real;
				buf2[k*t1 + i].imag = buf1[k*t1 + i - t1 / 2].imag - buf1[k*t1 + i].imag;
			}
		}
		memcpy(buf1, buf2, sizeof(ComplexNumber)*n);
	}
	memcpy(arrayBuf, buf2, sizeof(ComplexNumber)*n);
	delete[]buf2;
	delete[]buf1;
}
void FourTrans::ImageFFt2D(unsigned char* imgBuf, int width, int height,unsigned char *imgBufOut)//ͼ�����ݶ�ά���ٸ���Ҷ�任
{
	int i, j, u, v;
	for (i = 0; i<width*height; i++)                                   //ͼ�����ݱ�ɸ������ʹ���m_pFFTBuf
	{
		m_pFFTBuf[i].real = imgBuf[i];
		m_pFFTBuf[i].imag = 0;
	}
	ComplexNumber *array = new ComplexNumber[height];
	for (u = 0; u<width; u++)                                        //������һά���ٸ���Ҷ�任
	{
		for (v = 0; v<height; v++) 
		{
			array[v].real = m_pFFTBuf[v*width + u].real;
			array[v].imag = m_pFFTBuf[v*width + u].imag;
		}
		ImageFFt1D(array, height);
		for (v = 0; v<height; v++) 
		{
			m_pFFTBuf[v*width + u].real = array[v].real;
			m_pFFTBuf[v*width + u].imag = array[v].imag;
		}
	}
	delete[]array;
	for (v = 0; v<height; v++)                   //�ٺ���һά���ٸ���Ҷ�任
		ImageFFt1D(m_pFFTBuf + v*width, width);
	float t;
	int i0, j0;
	for (i = 0; i<height; i++)
	{
		for (j = 0; j<width; j++) 
		{
			if (i<height / 2)
				i0 = i + height / 2;
			else
				i0 = i - height / 2;
			if (j<width / 2)
				j0 = j + width / 2;
			else
				j0 = j - width / 2;
			t = sqrt(m_pFFTBuf[i0*width + j0].real*m_pFFTBuf[i0*width + j0].real
				+ m_pFFTBuf[i0*width + j0].imag*m_pFFTBuf[i0*width + j0].imag);
			t = t / 500;
			if (t>255)
				imgBufOut[i*width + j] = 255;
			else
				imgBufOut[i*width + j] = t;
		}
	}
}
void FourTrans::ImageRevFFt2D(unsigned char* imgBufOut, int width, int height)//�Ը���Ҷ�任������m_pFFTBuf���
{                                                                            //����,��������һά���ٸ���Ҷ���任
	if (!m_pFFTBuf)
		return;
	int i, u, v;
	ComplexNumber *array = new ComplexNumber[height];                           //��������Ҷ���任
	for (u = 0; u<width; u++) 
	{
		for (v = 0; v<height; v++) 
		{
			array[v].real = m_pFFTBuf[v*width + u].real;
			array[v].imag = m_pFFTBuf[v*width + u].imag;
		}
		ImageRevFFt1D(array, height);
		for (v = 0; v<height; v++) 
		{
			m_pFFTBuf[v*width + u].real = array[v].real;
			m_pFFTBuf[v*width + u].imag = array[v].imag;
		}
	}
	delete[]array;
	for (v = 0; v<height; v++)                                                       //�ٺ�����Ҷ���任 
		ImageRevFFt1D(m_pFFTBuf + v*width, width);
	float t;
	for (i = 0; i<width*height; i++) 
	{
		t = sqrt(m_pFFTBuf[i].real*m_pFFTBuf[i].real+ m_pFFTBuf[i].imag*m_pFFTBuf[i].imag);
		if (t>255)
			imgBufOut[i] = 255;
		else imgBufOut[i] = t;
	}
}
void FourTrans::ImageRevFFt1D(ComplexNumber *arrayBuf, int n)              //�Ը����ṹ������arrayBuf����һά���ٸ���Ҷ���任
{
	int i;
	for (i = 0; i<n; i++)                  //������arrayBuf����
		arrayBuf[i].imag = -arrayBuf[i].imag;
	ImageFFt1D(arrayBuf, n);                //һά���ٸ���Ҷ�任
	for (i = 0; i<n; i++)                 //ʱ���������������N
	{
		arrayBuf[i].real = arrayBuf[i].real / n;
		arrayBuf[i].imag = -arrayBuf[i].imag / n;
	}
}