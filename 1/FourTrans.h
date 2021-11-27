#pragma once
#include "ImageDib.h"
#define PI 3.1415926
struct ComplexNumber                 //�������ͽṹ��
{
	float imag;                      // imaginary�鲿
	float real;                      //ʵ��
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
	ComplexNumber *m_pFFTBuf;                //����Ҷ�任������
	bool m_isExpanded;                         //ͼ���Ƿ���չ�ı�־����
public:
	FourTrans();
	FourTrans(CSize size, int nBitCount, LPRGBQUAD lpColorTable,unsigned char *pImgData);
	virtual ~FourTrans();
	CSize GetDimensions();
	void InputImgData(CSize size, int nBitCount, LPRGBQUAD lpColorTable,unsigned char *pImgData);
	void Fourier();                                                                           //ͼ����Ҷ�任
	void RevFourier();                                                                        //����Ҷ���任
	void ImageFFt1D(ComplexNumber *arrayBuf, int n);                                          //һά���ٸ���Ҷ���任
	void ImageRevFFt1D(ComplexNumber *arrayBuf, int n);                                       //һά���ٸ���Ҷ���任
	void ImageFFt2D(unsigned char* imgBuf, int width, int height, unsigned char *imgBufOut);  //��ά���ٸ���Ҷ�任
	void ImageRevFFt2D(unsigned char* imgBufOut, int width, int height);                      //��ά���ٸ���Ҷ�任
};

