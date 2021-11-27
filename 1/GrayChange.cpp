#include "stdafx.h"
#include "GrayChange.h"
#define MAX(x,y) ((x)>(y)?(x):(y)) 

GrayChange::GrayChange()
{
	m_pImgDataOut = NULL;//���ͼ��λͼ����ָ��Ϊ��
	m_lpColorTableOut = NULL;//���ͼ����ɫ��ָ��Ϊ��
	m_nColorTableLengthOut = 0;//���ͼ����ɫ����Ϊ0
	m_nBitCountOut = 0;//���ͼ��ÿ����λ��Ϊ0	
	m_imgWidthOut = 0;//���ͼ��Ŀ�Ϊ0
	m_imgHeightOut = 0;//���ͼ��ĸ�Ϊ0
}
GrayChange::GrayChange(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData) :
	ImageDib(size, nBitCount, lpColorTable, pImgData)
{
	m_pImgDataOut = NULL;//���ͼ��λͼ����ָ��Ϊ��
	m_lpColorTableOut = NULL;//���ͼ����ɫ��ָ��Ϊ��
	m_nColorTableLengthOut = 0;//���ͼ����ɫ����Ϊ0
	m_nBitCountOut = 0;//���ͼ��ÿ����λ��Ϊ0
	m_imgWidthOut = 0;//���ͼ��Ŀ�Ϊ0
	m_imgHeightOut = 0;//���ͼ��ĸ�Ϊ0
}
GrayChange::~GrayChange()
{
	if (m_pImgDataOut != NULL)//�ͷ����ͼ��λͼ���ݻ�����
	{
		delete[]m_pImgDataOut;
		m_pImgDataOut = NULL;
	}
	if (m_lpColorTableOut != NULL)//�ͷ����ͼ����ɫ��
	{
		delete[]m_lpColorTableOut;
		m_lpColorTableOut = NULL;
	}
}
CSize GrayChange::GetDimensions()
{
	if (m_pImgDataOut == NULL)
		return CSize(0, 0);
	return CSize(m_imgWidthOut, m_imgHeightOut);
}
void GrayChange::ColorToGrayJiaoQuan()//��ֵ��
{
	if (m_nBitCount == 8)//���Ҷ�ͼ��,�򷵻�
		return;
	if (m_pImgDataOut != NULL) 
	{ //�ͷžɵ����ͼ�����ݼ���ɫ������
		delete[]m_pImgDataOut;
		m_pImgDataOut = NULL;
	}
	if (m_lpColorTableOut != NULL) 
	{
		delete[]m_lpColorTableOut;
		m_lpColorTableOut = NULL;
	}
	m_nBitCountOut = 8;//��ֵ����,ÿ����λ��Ϊ8����
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);
	if (m_nColorTableLengthOut != 0)
	{//������ɫ������,���ɻҶ�ͼ�����ɫ��
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		for (int i = 0; i<m_nColorTableLengthOut; i++)
		{
			m_lpColorTableOut[i].rgbBlue = i;
			m_lpColorTableOut[i].rgbGreen = i;
			m_lpColorTableOut[i].rgbRed = i;
			m_lpColorTableOut[i].rgbReserved = 0;
		}
	}
	int pixelByteIn = 3;
	int lineByteIn = (m_imgWidth*pixelByteIn + 3) / 4 * 4;
	m_imgWidthOut = m_imgWidth;//���ͼ��Ŀ��,������ͼ�����
	m_imgHeightOut = m_imgHeight;
	int lineByteOut = (m_imgWidth*m_nBitCountOut / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeight];//�������ͼ��λͼ���ݻ�����
	int i, j;
	for (i = 0; i<m_imgHeight; i++)
	{
		for (j = 0; j<m_imgWidth; j++)//��Ȩ��
			*(m_pImgDataOut + i*lineByteOut + j) = 0.11**(m_pImgData + i*lineByteIn + j*pixelByteIn + 0)    
			+ 0.59**(m_pImgData + i*lineByteIn + j*pixelByteIn + 1)+ 0.30**(m_pImgData + i*lineByteIn + j*pixelByteIn + 2) + 0.5;
	}

}
void GrayChange::ColorToGrayAverage()
{
	if (m_nBitCount == 8)
		return;
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
	m_nBitCountOut = 8;
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);
	if (m_nColorTableLengthOut != 0)
	{
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		for (int i = 0; i<m_nColorTableLengthOut; i++)
		{
			m_lpColorTableOut[i].rgbBlue = i;
			m_lpColorTableOut[i].rgbGreen = i;
			m_lpColorTableOut[i].rgbRed = i;
			m_lpColorTableOut[i].rgbReserved = 0;
		}
	}
	int pixelByteIn = 3;
	int lineByteIn = (m_imgWidth*pixelByteIn + 3) / 4 * 4;
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;
	int lineByteOut = (m_imgWidth*m_nBitCountOut / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeight];
	int i, j;
	for (i = 0; i<m_imgHeight; i++)
	{
		for (j = 0; j<m_imgWidth; j++)//��ֵ��

		*(m_pImgDataOut+i*lineByteOut+j)=(*(m_pImgData+i*lineByteIn+j*pixelByteIn+0)+*(m_pImgData+i*lineByteIn+j*pixelByteIn+1)+*(m_pImgData+i*lineByteIn+j*pixelByteIn+2))/3;
	}
}
void GrayChange::ColorToGrayMax()
{
	if (m_nBitCount == 8)
		return;
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
	m_nBitCountOut = 8;
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);
	if (m_nColorTableLengthOut != 0)
	{
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		for (int i = 0; i<m_nColorTableLengthOut; i++)
		{
			m_lpColorTableOut[i].rgbBlue = i;
			m_lpColorTableOut[i].rgbGreen = i;
			m_lpColorTableOut[i].rgbRed = i;
			m_lpColorTableOut[i].rgbReserved = 0;
		}
	}
	int pixelByteIn = 3;
	int lineByteIn = (m_imgWidth*pixelByteIn + 3) / 4 * 4;
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;
	int lineByteOut = (m_imgWidth*m_nBitCountOut / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeight];
	int i, j;
	for (i = 0; i<m_imgHeight; i++)
	{
		for (j = 0; j < m_imgWidth; j++)
		{
			BYTE A, B, C,D;
			A = *(m_pImgData + i*lineByteIn + j*pixelByteIn + 0) / 255;
			B = *(m_pImgData + i*lineByteIn + j*pixelByteIn + 1) / 255;
			C = *(m_pImgData + i*lineByteIn + j*pixelByteIn + 2) / 255;
			D = MAX(A,MAX(B,C));
			*(m_pImgDataOut + i*lineByteOut + j) = D*255; 
		}
	}
}
void GrayChange::ColorRev()
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
	m_nBitCountOut = m_nBitCount;
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);
	if (m_nColorTableLengthOut != 0)
	{
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut, m_lpColorTable, sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;
	int lineByteOut = (m_imgWidth*m_nBitCountOut / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeight];
	int i, j;
	int pixelByte = m_nBitCountOut / 8;
	int k;
	for (i = 0; i<m_imgHeight; i++)                    //����
		for (j = 0; j<m_imgWidth; j++)
			for (k = 0; k<pixelByte; k++)
				*(m_pImgDataOut + i*lineByteOut + j*pixelByte + k) = 255 - *(m_pImgData + i*lineByteOut + j*pixelByte + k);
}
void GrayChange::Binary(int threshold)
{
	if (m_nBitCount == 8)
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
		m_nBitCountOut = m_nBitCount;
		m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut, m_lpColorTable, sizeof(RGBQUAD)*m_nColorTableLengthOut);
		m_imgWidthOut = m_imgWidth;
		m_imgHeightOut = m_imgHeight;
		int lineByte = (m_imgWidth*m_nBitCount / 8 + 3) / 4 * 4;
		m_pImgDataOut = new unsigned char[lineByte*m_imgHeight];
		int i, j;
		for (i = 0; i < m_imgHeight; i++)
		{
			for (j = 0; j < m_imgWidth; j++)
			{
				if (*(m_pImgData + i*lineByte + j) < threshold)
					*(m_pImgDataOut + i*lineByte + j) = 0;
				else
					*(m_pImgDataOut + i*lineByte + j) = 255;
			}
		}
	}
	else
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
		m_nBitCountOut = 8;
		m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);
		if (m_nColorTableLengthOut != 0)
		{
			m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
			for (int i = 0; i < m_nColorTableLengthOut; i++)
			{
				m_lpColorTableOut[i].rgbBlue = i;
				m_lpColorTableOut[i].rgbGreen = i;
				m_lpColorTableOut[i].rgbRed = i;
				m_lpColorTableOut[i].rgbReserved = 0;
			}
		}
		int pixelByteIn = 3;
		int lineByteIn = (m_imgWidth*pixelByteIn + 3) / 4 * 4;
		m_imgWidthOut = m_imgWidth;
		m_imgHeightOut = m_imgHeight;
		int lineByteOut = (m_imgWidth*m_nBitCountOut / 8 + 3) / 4 * 4;
		m_pImgDataOut = new unsigned char[lineByteOut*m_imgHeight];
		int m, n;
		for (m = 0; m < m_imgHeight; m++)		//���ݻ�ֵ����ʽΪ���ͼ��ֵ
		{
			for (n = 0; n < m_imgWidth; n++)
				*(m_pImgDataOut + m*lineByteOut + n) = 0.11**(m_pImgData + m*lineByteIn + n*pixelByteIn + 0)
				+ 0.59**(m_pImgData + m*lineByteIn + n*pixelByteIn + 1)+ 0.30**(m_pImgData + m*lineByteIn + n*pixelByteIn + 2) + 0.5;
		}
		int i, j;
		for (i = 0; i < m_imgHeight; i++)               //��ֵ��
		{
			for (j = 0; j < m_imgWidth; j++)
				if (*(m_pImgDataOut + i*lineByteOut + j) < threshold)
					*(m_pImgDataOut + i*lineByteOut + j) = 0;
				else
					*(m_pImgDataOut + i*lineByteOut + j) = 255;
		}
	}
}