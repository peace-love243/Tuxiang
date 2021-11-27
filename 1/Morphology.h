#pragma once
#include "imagedib.h"
struct ElementPair
{
	int hitElement[9];
	int missElement[9];
};
typedef struct tagEqualMark                   //����MarkMap�ṹ��������ŵȼ۶�
{
	int MarkValue1;//���ֵ1
	int MarkValue2;//���ֵ2
}EqualMark;
typedef struct tagMarkMapping                //����MarkMap�ṹ��������ű��ӳ���ϵ
{
	int nOriginalMark;//��һ��ɨ���ı��
	int nMappingMark;//�ȼ�����֮���Ӧ���
}MarkMapping;
class Morphology :
	public ImageDib
{
public:
	int m_nBitCountOut;	//���ͼ��ÿ����λ��
	unsigned char * m_pImgDataOut;//���ͼ��λͼ����ָ��
	LPRGBQUAD m_lpColorTableOut;	//���ͼ����ɫ��
	int m_imgWidthOut;	//���ͼ��Ŀ�
	int m_imgHeightOut;	//���ͼ��ĸ�
	int m_nColorTableLengthOut;
	int m_InitTemp[25];
	int *m_TempBuf;	//�ṹԪ�أ�ģ�壩ָ��
	int TempW;     //�ṹԪ�ؿ�
	int TempH;     //�ṹԪ�ظ�
	ElementPair m_hitMissMask[12];
public:
	Morphology();	//���������Ĺ��캯��
    Morphology(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData);	//�������Ĺ��캯��
	virtual ~Morphology();	//��������
	CSize GetDimensions();	//�������ͼ��ĳߴ�
public:
	void ImgErosion(unsigned char *imgBufIn,unsigned char *imgBufOut,	int imgWidth,
		int imgHeight,int *TempBuf, int TempW, int TempH);//��ʴ
	void ImgDilation(unsigned char *imgBufIn,unsigned char *imgBufOut,int imgWidth,
		int imgHeight,int *maskBuf, int maskW, int maskH);//����
	void InputMask(int *mask,int maskW, int maskH);//�ṹԪ�أ�ģ�壩���뺯�����ڵ���������̬ѧ������ǰ�����ȵ��ô˺���
	void Open();	//��ֵ��
	void Close();	//��ֵ��
	void ImgThinning();	//���л�����ϸ��
	void DefineElementPair();//������л����б任�ĽṹԪ�ض�
	void HitAndMiss(unsigned char *imgBufIn, unsigned char *imgBufOut,
		int imgWidth,int imgHeight,ElementPair hitMissMask);	//���л����б任
	void Areas();                        //�������������С��Բ�ζȵļ��������˳���������
	template<typename elemType> void AttachEqualMark(EqualMark &pEqualMark, elemType num1, elemType num2, int & pEqualNum, CList< EqualMark, EqualMark > & plEqualMark);
};

