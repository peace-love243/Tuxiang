#pragma once
#include "ImageDib.h"
class ColorSpace :public ImageDib
{
public:
	int m_nBitCountOut;
	unsigned char * m_pImgDataOut;
	LPRGBQUAD m_lpColorTableOut;
	int m_imgWidthOut;
	int m_imgHeightOut;
	int m_nColorTableLengthOut;
public:
	ColorSpace();
	ColorSpace(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData);
	~ColorSpace();
	CSize GetDimensions();                            //以像素为单位返回输出图像的宽和高
	void RGBR();                                       //提取红色分量
	void RGBG();                                        //提取绿色分量
	void RGBB();                                        //提取蓝色分量
	void RGB2YCBCR1();                                   //RGB颜色空间转换为YCBCR颜色空间
	void RGB2Y();                                        //提取Y分量
	void RGB2CB();                                       //提取CB分量
	void RGB2CR();                                       //提取CR分量
	void RGB2YCBCRJIAQUAN();                              //Y、CB、CR分量加权处理
	void RGB2LAB1();                                       //RGB颜色空间转换为LAB颜色空间
	void RGB2L();                                          //提取L分量
	void RGB2A();                                           //提取A分量
	void RGB2B();                                          //提取B分量
	void RGB2LABJQ();                                       //L、A、B分量加权处理
	void RGB2HSI();                                         //RGB颜色空间转换为HSI颜色空间
	void RGB2CMYK();                                        // RGB颜色空间转换为HSI颜色空间
};

