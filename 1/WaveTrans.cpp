#include "stdafx.h"
#include "WaveTrans.h"
#include "math.h"
WaveTrans::WaveTrans()
{
	m_nColorTableLengthOut = 0;
	m_nScale = 0;
	m_nBitCountOut = 0;
	m_pImgDataOut = NULL;
	m_pColorTableOut = NULL;
	pCoeff = NULL;
}
WaveTrans::WaveTrans(CSize size, int nBitCount, LPRGBQUAD pColorTable,unsigned char *pImgData)
{
	m_nBitCountOut = m_nBitCount;
	m_pColorTableOut = m_lpColorTable;
	int lineByte = (m_imgWidth*m_nBitCount / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByte*m_imgHeight];
	for (int i = 0; i < m_imgWidth; i++)
		for (int j = 0; j < m_imgHeight; j++)
			m_pImgDataOut[j * lineByte + i] = pImgData[j * lineByte + i];
	pCoeff = NULL;
}
WaveTrans::~WaveTrans()
{
	if (m_pImgDataOut != NULL)
	{
		delete[]m_pImgDataOut;
		m_pImgDataOut = NULL;
	}
	if (pCoeff != NULL)
	{
		delete[] pCoeff;
		pCoeff = NULL;
	}
}
void WaveTrans::InputImageData(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData)
{
	ReplaceDib(size, nBitCount, lpColorTable, pImgData);
	if (m_pImgDataOut != NULL) 
	{
		delete[]m_pImgDataOut;
		m_pImgDataOut = NULL;
	}
	m_nBitCountOut = m_nBitCount;
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);
	m_pColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
	memcpy(m_pColorTableOut, m_lpColorTable, sizeof(RGBQUAD)*m_nColorTableLengthOut);
}
CSize WaveTrans::GetDimensions()
{
	return CSize(m_imgWidthOut, m_imgHeightOut);
}
void WaveTrans::BasicWaveletTrans(int scale = 1) //对图像数据进行给定尺度的小波分解
{
	if (scale < 1 || scale>5)
	{
		return;
	}
	if (m_pImgDataOut != NULL)
	{
		delete[] m_pImgDataOut;
		m_pImgDataOut = NULL;
	}
	m_imgHeightOut = m_imgHeight;
	m_imgWidthOut = m_imgWidth;
	m_nScale = scale;
	int lineByte = (m_imgWidth*m_nBitCount / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByte*m_imgHeight];
	WavlDecmposeTrans(m_pImgData, m_imgHeight, m_imgWidth, lineByte, scale, m_pImgDataOut);
}
void WaveTrans::WavlDecmposeTrans(unsigned char *inputData, int inputHeight, int inputWidth, int lineByte, int scale, unsigned char *outputData)
{                      //进行小波分解
	unsigned char *buff = new unsigned char[lineByte*m_imgHeight];
	int imageHeight = inputHeight;
	int imageWidth = inputWidth;
	unsigned char *temp1 = new unsigned char[imageWidth * (int)(imageHeight / 2)];
	unsigned char *temp2 = new unsigned char[imageWidth * (int)(imageHeight / 2)];
	MatrixSampleRow(inputData, temp1, temp2, (imageHeight / 2), imageWidth, lineByte);               //对图像矩阵进行行采样
	MatrixSub(temp1, temp2, (imageHeight / 2), imageWidth, temp1);                                      //行差分，得到高频与低频数据
	unsigned char *temp00 = new unsigned char[(imageWidth / 2) * (imageHeight / 2)];
	unsigned char *temp01 = new unsigned char[(imageWidth / 2) * (imageHeight / 2)];
	MatrixSampleLine(temp2, temp01, temp00, (imageHeight / 2), (imageWidth / 2), imageWidth);                 //对低频数据进行列采样
	MatrixSub(temp01, temp00, (imageHeight / 2), (imageWidth / 2), temp01);                                  //列差分得到LL和LH
	unsigned char *temp10 = new unsigned char[(imageWidth / 2) * (imageHeight / 2)];
	unsigned char *temp11 = new unsigned char[(imageWidth / 2) * (imageHeight / 2)];
	MatrixSampleLine(temp1, temp11, temp10, (imageHeight / 2), (imageWidth / 2), imageWidth);               //对高频数据进行列采样
	MatrixSub(temp11, temp10, (imageHeight / 2), (imageWidth / 2), temp11);                                //列差分，得到HL和HH
	MatrixRegionCopy(temp01, (imageHeight / 2), (imageWidth / 2),
		buff + lineByte*(int)(imageHeight / 2) + (int)(imageWidth / 2), imageHeight, lineByte);
	MatrixRegionCopy(temp10, (imageHeight / 2), (imageWidth / 2), buff, imageHeight, lineByte);
	MatrixRegionCopy(temp11, (imageHeight / 2), (imageWidth / 2), buff + (int)(imageWidth / 2), imageHeight, lineByte);
	delete[] temp1;                                                                                             //释放空间
	delete[] temp2;
	delete[] temp01;
	delete[] temp10;
	delete[] temp11;
	scale--;
	if (scale > 0)//继续对LL进行递归分解
	{
		WavlDecmposeTrans(temp00, imageHeight / 2, imageWidth / 2, imageWidth / 2, scale, temp00);
	}
	MatrixRegionCopy(temp00, (imageHeight / 2), (imageWidth / 2), buff + lineByte*(int)(imageHeight / 2),
		imageHeight, lineByte);
	delete[] temp00;
	memcpy(outputData, buff, lineByte * inputHeight);
	delete[] buff;
}
void WaveTrans::MatrixSampleRow(unsigned char *matrixInput, unsigned char *matrixOutputOdd, 
	              unsigned char *matrixOutputEven, int heightOutput, int widthOutput, int widthInput)
{                       //对输入矩阵进行行抽点采样
	int h, w;
	for (h = 0; h<heightOutput; h++)
	{
		for (w = 0; w<widthOutput; w++)
		{
			matrixOutputEven[h * widthOutput + w] = matrixInput[h * 2 * widthInput + w];
			matrixOutputOdd[h * widthOutput + w] = matrixInput[(h * 2 + 1) * widthInput + w];
		}
	}
}
void WaveTrans::MatrixSub(unsigned char *matrixA, unsigned char *matrixB, int height, int width, unsigned char *result)   //将输入的两个矩阵A和B求差
{
	unsigned char temp;
	int h, w;
	for (h = 0; h<height; h++)
	{
		for (w = 0; w<width; w++)
		{
			temp = matrixA[h * width + w] - matrixB[h * width + w] + 128;
			result[h * width + w] = temp;
		}
	}
}
void WaveTrans::MatrixSampleLine(unsigned char *matrixInput, unsigned char *matrixOutputOdd,
	unsigned char *matrixOutputEven, int heightOutput, int widthOutput, int widthInput)//对输入矩阵进行列抽点采样
{
	int h, w;
	for (h = 0; h<heightOutput; h++)
	{
		for (w = 0; w<widthOutput; w++)
		{
			matrixOutputEven[h * widthOutput + w] = matrixInput[h * widthInput + w * 2];
			matrixOutputOdd[h * widthOutput + w] = matrixInput[h * widthInput + w * 2 + 1];
		}
	}
}
void WaveTrans::MatrixPlus(unsigned char *matrixA, unsigned char *matrixB, int height, int width, unsigned char *result)  //将输入的两个矩阵A和B求和
{
	unsigned char temp;
	int h, w;
	for (h = 0; h<height; h++)
	{
		for (w = 0; w<width; w++)
		{
			temp = matrixA[h * width + w] + matrixB[h * width + w] - 128;
			result[h * width + w] = temp;
		}
	}
}
void WaveTrans::MatrixRegionCopy(unsigned char *matrixRegion, int heightRegion, int widthRegion,
	unsigned char *matrixDest, int heightDest, int widthDest)
{
	int heightMin = heightRegion>heightDest ? heightDest : heightRegion;	//计算区域高度和宽度
	int widthMin = widthRegion>widthDest ? widthDest : widthRegion;
	int h, w;
	for (h = 0; h<heightMin; h++)
	{
		for (w = 0; w<widthMin; w++)
		{
			matrixDest[h * widthDest + w] = matrixRegion[h * widthRegion + w];
		}
	}
}
void WaveTrans::BasicWaveletReverse()         // 对相应小波分解系数进行小波重构
{
	if (m_nScale <= 0)
	{
		return;
	}
	if (m_pImgDataOut == NULL)
	{
		return;
	}
	m_imgHeightOut = m_imgHeight;
	m_imgWidthOut = m_imgWidth;
	int lineByte = (m_imgWidth*m_nBitCount / 8 + 3) / 4 * 4;
	this->WavlRebuildTrans(m_pImgDataOut, m_imgHeight, m_imgWidth, lineByte, m_nScale, m_pImgDataOut);
}
void WaveTrans::WavlRebuildTrans(unsigned char *inputData, int inputHeight,
	         int inputWidth, int lineByte, int scale, unsigned char *outputData)             //进行一遍小波重构
{
	unsigned char *buff = new unsigned char[lineByte*m_imgHeight];
	int imageHeight = inputHeight;
	int imageWidth = inputWidth;
	unsigned char *temp10 = new unsigned char[(imageWidth / 2) * (imageHeight / 2)];
	unsigned char *temp11 = new unsigned char[(imageWidth / 2) * (imageHeight / 2)];
	this->MatrixRegionCopy(inputData, imageHeight, lineByte, temp10, (imageHeight / 2), (imageWidth / 2));
	this->MatrixRegionCopy(inputData + (int)(imageWidth / 2), imageHeight, lineByte, temp11, (imageHeight / 2), (imageWidth / 2));
	this->MatrixPlus(temp11, temp10, (imageHeight / 2), (imageWidth / 2), temp11);
	unsigned char *temp1 = new unsigned char[imageWidth * (int)(imageHeight / 2)];
	this->MatrixInsertLine(temp11, temp10, temp1, (imageHeight / 2), (imageWidth / 2), imageWidth);
	unsigned char *temp00 = new unsigned char[(imageWidth / 2) * (imageHeight / 2)];
	unsigned char *temp01 = new unsigned char[(imageWidth / 2) * (imageHeight / 2)];
	this->MatrixRegionCopy(inputData + lineByte*(int)(imageHeight / 2), imageHeight, lineByte, 
		temp00, (imageHeight / 2), (imageWidth / 2));
	this->MatrixRegionCopy(inputData + lineByte*(int)(imageHeight / 2) + (int)(imageWidth / 2),
		imageHeight, lineByte, temp01, (imageHeight / 2), (imageWidth / 2));
	scale--;
	if (scale > 0)
	{
		this->WavlRebuildTrans(temp00, imageHeight / 2, imageWidth / 2, imageWidth / 2, scale, temp00);
	}
	this->MatrixPlus(temp01, temp00, (imageHeight / 2), (imageWidth / 2), temp01);
	unsigned char *temp2 = new unsigned char[imageWidth * (int)(imageHeight / 2)];
	this->MatrixInsertLine(temp01, temp00, temp2, (imageHeight / 2), (imageWidth / 2), imageWidth);
	this->MatrixPlus(temp1, temp2, (imageHeight / 2), imageWidth, temp1);
	this->MatrixInsertRow(temp1, temp2, buff, (imageHeight / 2), imageWidth, lineByte);
	delete[] temp1;
	delete[] temp2;
	delete[] temp01;
	delete[] temp10;
	delete[] temp11;
	delete[] temp00;
	memcpy(outputData, buff, lineByte * inputHeight);
	delete[] buff;
}
void WaveTrans::MatrixInsertLine(unsigned char *matrixInputOdd, unsigned char *matrixInputEven,
	unsigned char *matrixOutput, int heightInput, int widthInput, int widthOutput)                   //对输入矩阵进行列插点采样
{
	int h, w;
	for (h = 0; h<heightInput; h++)
	{
		for (w = 0; w<widthOutput; w++)
		{
			if (w % 2 == 0)
				matrixOutput[h * widthOutput + w] = matrixInputEven[h * widthInput + w / 2];
			else
				matrixOutput[h * widthOutput + w] = matrixInputOdd[h * widthInput + w / 2];
		}
	}
}
void WaveTrans::MatrixInsertRow(unsigned char *matrixInputOdd, unsigned char *matrixInputEven,
	unsigned char *matrixOutput, int heightInput, int widthInput, int widthOutput)                    //对输入矩阵进行行插点采样
{
	int h, w;
	for (h = 0; h<heightInput * 2; h++)
	{
		for (w = 0; w<widthInput; w++)
		{
			if (h % 2 == 0)
			{
				matrixOutput[h * widthOutput + w] = matrixInputEven[(int)(h / 2) * widthInput + w];
			}
			else
			{
				matrixOutput[h * widthOutput + w] = matrixInputOdd[(int)(h / 2) * widthInput + w];
			}
		}
	}
}