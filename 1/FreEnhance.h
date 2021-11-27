#pragma once
#include "ImageDib.h"
#include "FourTrans.h"
class FreEnhance :public ImageDib
{
public:
	int m_nBitCountOut;
	unsigned char * m_pImgDataOut;
	LPRGBQUAD m_lpColorTableOut;
	int m_imgWidthOut;
	int m_imgHeightOut;
	int m_nColorTableLengthOut;
public:
	FourTrans FFtTrans;
public:
	FreEnhance();
	FreEnhance(CSize size, int nBitCount, LPRGBQUAD lpColorTable,unsigned char *pImgData);
	virtual ~FreEnhance();
	CSize GetDimensions();
	void InputImageData(CSize size, int nBitCount, LPRGBQUAD lpColorTable,unsigned char *pImgData);	//输入原图像数据
	void IdealLowPassFilter(int nWidth, int nHeight, int nRadius);                                  //理想低通滤波
	void ButterLowPassFilter(int nWidth, int nHeight, int nRadius);	                                //巴特沃斯低通滤波
	void IdealHighPassFilter(int nWidth, int nHeight, int nRadius);	                                //理想高通滤波
	void ButterHighPassFilter(int nWidth, int nHeight, int nRadius);                                //巴特沃斯高通滤波
};

