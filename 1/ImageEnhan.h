#pragma once
#include "ImageDib.h"
class ImageEnhan :
	public ImageDib
{
public:
	int m_nBitCountOut;
	unsigned char * m_pImgDataOut;
	LPRGBQUAD m_lpColorTableOut;
	int m_nColorTableLengthOut;
public:
	ImageEnhan();
	ImageEnhan(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData);
	virtual ~ImageEnhan();
	void AddPepperSaltNoise();
	void AddGaussNoise();
	void NeiAveTemplate(int TempH, int TempW, int TempCX, int TempCY, float *fpTempArray, float fCoef);
	BYTE FindMedianValue(unsigned char* lpbArray, int iArrayLen);
	void MedianSmooth(int iFilterH, int iFilterW, int iFilterCX, int iFilterCY);
	void LapTemplate(int TempH, int TempW, int TempCX, int TempCY, float *fpTempArray, float fCoef);
	void GradeSharp(int Thresh);
	void ChooseMaskSmooth();
};

