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
	int m_nScale;                      //�ֽ�߶�	
public:
	WaveTrans();
	WaveTrans(CSize size, int nBitCount,LPRGBQUAD pColorTable, unsigned char *pImgData);
	virtual ~WaveTrans();
public:
	void InputImageData(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData);
	CSize GetDimensions();
protected:
	void MatrixRegionCopy(unsigned char *matrixRegion, int heightRegion, int widthRegion,
		unsigned char *matrixDest, int heightDest, int widthDest);                    //����������
	void MatrixSub(unsigned char *matrixA, unsigned char *matrixB, int height, int width, unsigned char *result);  //�������
	void MatrixSampleRow(unsigned char *matrixInput, unsigned char *matrixOutputOdd,
		unsigned char *matrixOutputEven, int heightOutput, int widthOutput, int widthInput);            //�в���
	void MatrixSampleLine(unsigned char *matrixInput, unsigned char *matrixOutputOdd,
		unsigned char *matrixOutputEven, int heightOutput, int widthOutput, int widthInput);           //�в���
public:
	
	void WavlDecmposeTrans(unsigned char *inputData, int inputHeight, int inputWidth, int lineByte, 
		                 int scale, unsigned char *outputData);                                       //һ��С���ֽ�
	void BasicWaveletTrans(int scale);                                                                   //С���任
protected:
	void MatrixPlus(unsigned char *matrixA, unsigned char *matrixB, int height, int width, unsigned char *result);   //�������
	void MatrixInsertRow(unsigned char *matrixInputOdd, unsigned char *matrixInputEven,
		unsigned char *matrixOutput, int heightInput, int widthInput, int widthOutput);                              //�в��
	void MatrixInsertLine(unsigned char *matrixInputOdd, unsigned char *matrixInputEven,
		unsigned char *matrixOutput, int heightInput, int widthInput, int widthOutput);                               //�в��
public:
	void WavlRebuildTrans(unsigned char *inputData, int inputHeight, int inputWidth, int lineByte, 
		              int scale, unsigned char *outputData);                                                      //һ��С���ع�
	void BasicWaveletReverse();                                                                                    //С���ع�
};

