#pragma once
#include "imagedib.h"
struct ElementPair
{
	int hitElement[9];
	int missElement[9];
};
typedef struct tagEqualMark                   //定义MarkMap结构，用来存放等价对
{
	int MarkValue1;//标记值1
	int MarkValue2;//标记值2
}EqualMark;
typedef struct tagMarkMapping                //定义MarkMap结构，用来存放标记映射关系
{
	int nOriginalMark;//第一次扫描后的标记
	int nMappingMark;//等价整理之后对应标记
}MarkMapping;
class Morphology :
	public ImageDib
{
public:
	int m_nBitCountOut;	//输出图像每像素位数
	unsigned char * m_pImgDataOut;//输出图像位图数据指针
	LPRGBQUAD m_lpColorTableOut;	//输出图像颜色表
	int m_imgWidthOut;	//输出图像的宽
	int m_imgHeightOut;	//输出图像的高
	int m_nColorTableLengthOut;
	int m_InitTemp[25];
	int *m_TempBuf;	//结构元素（模板）指针
	int TempW;     //结构元素宽
	int TempH;     //结构元素高
	ElementPair m_hitMissMask[12];
public:
	Morphology();	//不带参数的构造函数
    Morphology(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData);	//带参数的构造函数
	virtual ~Morphology();	//析构函数
	CSize GetDimensions();	//返回输出图像的尺寸
public:
	void ImgErosion(unsigned char *imgBufIn,unsigned char *imgBufOut,	int imgWidth,
		int imgHeight,int *TempBuf, int TempW, int TempH);//腐蚀
	void ImgDilation(unsigned char *imgBufIn,unsigned char *imgBufOut,int imgWidth,
		int imgHeight,int *maskBuf, int maskW, int maskH);//膨胀
	void InputMask(int *mask,int maskW, int maskH);//结构元素（模板）输入函数，在调用其它形态学处理函数前必须先调用此函数
	void Open();	//二值开
	void Close();	//二值闭
	void ImgThinning();	//击中击不中细化
	void DefineElementPair();//定义击中击不中变换的结构元素对
	void HitAndMiss(unsigned char *imgBufIn, unsigned char *imgBufOut,
		int imgWidth,int imgHeight,ElementPair hitMissMask);	//击中击不中变换
	void Areas();                        //利用区域面积大小和圆形度的几何特征滤除噪声区域
	template<typename elemType> void AttachEqualMark(EqualMark &pEqualMark, elemType num1, elemType num2, int & pEqualNum, CList< EqualMark, EqualMark > & plEqualMark);
};

