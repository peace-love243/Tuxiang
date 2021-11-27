#pragma once
#include "ImageDib.h"
class GrayChange :public ImageDib
{
public:
	int m_nBitCountOut;//输出图像每像素位数
	unsigned char * m_pImgDataOut;//输出图像位图数据指针
	LPRGBQUAD m_lpColorTableOut;//输出图像颜色表
	int m_imgWidthOut;//输出图像的宽，像素为单位
	int m_imgHeightOut;//输出图像的高，像素为单位
	int m_nColorTableLengthOut;//输出图像颜色表长度
public:
	GrayChange();//不带参数的构造函数
	GrayChange(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData);//带参数的构造函数
	~GrayChange();//析构函数
	CSize GetDimensions();//以像素为单位返回输出图像的宽和高
	//灰度变换
	void ColorToGrayJiaoQuan();             //加权灰度化
	void ColorToGrayAverage();              //均值灰度化
	void ColorToGrayMax();                  //最大值灰度化
	void Binary(int threshold = 128);       //二值化
	void ColorRev();                        //反转
};

