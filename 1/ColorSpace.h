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
	CSize GetDimensions();                            //������Ϊ��λ�������ͼ��Ŀ�͸�
	void RGBR();                                       //��ȡ��ɫ����
	void RGBG();                                        //��ȡ��ɫ����
	void RGBB();                                        //��ȡ��ɫ����
	void RGB2YCBCR1();                                   //RGB��ɫ�ռ�ת��ΪYCBCR��ɫ�ռ�
	void RGB2Y();                                        //��ȡY����
	void RGB2CB();                                       //��ȡCB����
	void RGB2CR();                                       //��ȡCR����
	void RGB2YCBCRJIAQUAN();                              //Y��CB��CR������Ȩ����
	void RGB2LAB1();                                       //RGB��ɫ�ռ�ת��ΪLAB��ɫ�ռ�
	void RGB2L();                                          //��ȡL����
	void RGB2A();                                           //��ȡA����
	void RGB2B();                                          //��ȡB����
	void RGB2LABJQ();                                       //L��A��B������Ȩ����
	void RGB2HSI();                                         //RGB��ɫ�ռ�ת��ΪHSI��ɫ�ռ�
	void RGB2CMYK();                                        // RGB��ɫ�ռ�ת��ΪHSI��ɫ�ռ�
};

