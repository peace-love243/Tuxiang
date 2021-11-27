#pragma once
#include "ImageDib.h"
class WaveTrans :public ImageDib
{
public:
	int m_nBitCountOut;
	unsigned char * m_pImgDataOut;
	LPRGBQUAD m_pColorTableOut;
	int m_nColorTableLengthOut;
	double* pCoeff;
	int m_imgWidthOut; 
	int m_imgHeightOut;
	int m_nScale;                      //分解尺度	
public:
	WaveTrans();
	WaveTrans(CSize size, int nBitCount,LPRGBQUAD pColorTable, unsigned char *pImgData);
	virtual ~WaveTrans();
public:
	void InputImageData(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData);
	CSize GetDimensions();
protected:
	void MatrixRegionCopy(unsigned char *matrixRegion, int heightRegion, int widthRegion,
		unsigned char *matrixDest, int heightDest, int widthDest);                    //矩阵区域复制
	void MatrixSub(unsigned char *matrixA, unsigned char *matrixB, int height, int width, unsigned char *result);  //矩阵相减
	void MatrixSampleRow(unsigned char *matrixInput, unsigned char *matrixOutputOdd,
		unsigned char *matrixOutputEven, int heightOutput, int widthOutput, int widthInput);            //行采样
	void MatrixSampleLine(unsigned char *matrixInput, unsigned char *matrixOutputOdd,
		unsigned char *matrixOutputEven, int heightOutput, int widthOutput, int widthInput);           //列采样
public:
	
	void WavlDecmposeTrans(unsigned char *inputData, int inputHeight, int inputWidth, int lineByte, 
		                 int scale, unsigned char *outputData);                                       //一次小波分解
	void BasicWaveletTrans(int scale);                                                                   //小波变换
protected:
	void MatrixPlus(unsigned char *matrixA, unsigned char *matrixB, int height, int width, unsigned char *result);   //矩阵相加
	void MatrixInsertRow(unsigned char *matrixInputOdd, unsigned char *matrixInputEven,
		unsigned char *matrixOutput, int heightInput, int widthInput, int widthOutput);                              //行插点
	void MatrixInsertLine(unsigned char *matrixInputOdd, unsigned char *matrixInputEven,
		unsigned char *matrixOutput, int heightInput, int widthInput, int widthOutput);                               //列插点
public:
	void WavlRebuildTrans(unsigned char *inputData, int inputHeight, int inputWidth, int lineByte, 
		              int scale, unsigned char *outputData);                                                      //一次小波重构
	void BasicWaveletReverse();                                                                                    //小波重构
};

