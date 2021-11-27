#pragma once
#include "imagedib.h"
class ImgSegment :public ImageDib
{
public:
	//���ͼ��ÿ����λ��
	int m_nBitCountOut;
	//���ͼ��λͼ����ָ��
	unsigned char * m_pImgDataOut;	
	//���ͼ����ɫ��
	LPRGBQUAD m_lpColorTableOut;	
    //���ͼ��Ŀ�
	int m_imgWidthOut;	
	//���ͼ��ĸ�
	int m_imgHeightOut;
	//���ͼ����ɫ������
	int m_nColorTableLengthOut;	
public:
	//���������Ĺ��캯��
	ImgSegment();	
	//�������Ĺ��캯��
	ImgSegment(CSize size, int nBitCount, LPRGBQUAD lpColorTable,unsigned char *pImgData);
	//��������
	virtual ~ImgSegment();
public:
	//������Ϊ��λ�������ͼ��ĳߴ�
	CSize GetDimensions();
    //����Ӧ��ֵ�ָ�
	void AdaptThreshSeg(unsigned char *pImgData);

	//�޸�����Ӧ����
	void AdThreshSeg(unsigned char *pImgData);
	
	//�����䷽��ָ�
	void OtsuThreshold();
	void NewOtsu();
	//Roberts����
	void Roberts();	
    //Sobel����
	void Sobel();	
	//Prewitt����
	void Prewitt();	
	//Laplacian����
	void Laplacian();	
public:
	//��������
	void RegionGrow(CPoint SeedPos, int thresh);
	//���߸���
	void EdgeTrace();
};
