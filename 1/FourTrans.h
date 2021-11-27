#pragma once
#include "ImageDib.h"
#define PI 3.1415926
struct ComplexNumber                 //复数类型结构体
{
	float imag;                      // imaginary虚部
	float real;                      //实部
};
class FourTrans : public ImageDib
{
public:
	int m_nBitCountOut;
	unsigned char * m_pImgDataOut;
	LPRGBQUAD m_lpColorTableOut;
	int m_imgWidthOut;
	int m_imgHeightOut;
	int m_nColorTableLengthOut;
	unsigned char *m_pImgExpandBuf;
	ComplexNumber *m_pFFTBuf;                //傅立叶变换缓冲区
	bool m_isExpanded;                         //图像是否被扩展的标志变量
public:
	FourTrans();
	FourTrans(CSize size, int nBitCount, LPRGBQUAD lpColorTable,unsigned char *pImgData);
	virtual ~FourTrans();
	CSize GetDimensions();
	void InputImgData(CSize size, int nBitCount, LPRGBQUAD lpColorTable,unsigned char *pImgData);
	void Fourier();                                                                           //图像傅立叶变换
	void RevFourier();                                                                        //傅立叶反变换
	void ImageFFt1D(ComplexNumber *arrayBuf, int n);                                          //一维快速傅立叶正变换
	void ImageRevFFt1D(ComplexNumber *arrayBuf, int n);                                       //一维快速傅立叶反变换
	void ImageFFt2D(unsigned char* imgBuf, int width, int height, unsigned char *imgBufOut);  //二维快速傅立叶变换
	void ImageRevFFt2D(unsigned char* imgBufOut, int width, int height);                      //二维快速傅立叶变换
};

