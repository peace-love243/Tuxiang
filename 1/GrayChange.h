#pragma once
#include "ImageDib.h"
class GrayChange :public ImageDib
{
public:
	int m_nBitCountOut;//���ͼ��ÿ����λ��
	unsigned char * m_pImgDataOut;//���ͼ��λͼ����ָ��
	LPRGBQUAD m_lpColorTableOut;//���ͼ����ɫ��
	int m_imgWidthOut;//���ͼ��Ŀ�����Ϊ��λ
	int m_imgHeightOut;//���ͼ��ĸߣ�����Ϊ��λ
	int m_nColorTableLengthOut;//���ͼ����ɫ����
public:
	GrayChange();//���������Ĺ��캯��
	GrayChange(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData);//�������Ĺ��캯��
	~GrayChange();//��������
	CSize GetDimensions();//������Ϊ��λ�������ͼ��Ŀ�͸�
	//�Ҷȱ任
	void ColorToGrayJiaoQuan();             //��Ȩ�ҶȻ�
	void ColorToGrayAverage();              //��ֵ�ҶȻ�
	void ColorToGrayMax();                  //���ֵ�ҶȻ�
	void Binary(int threshold = 128);       //��ֵ��
	void ColorRev();                        //��ת
};

