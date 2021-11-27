#pragma once
#include "imagedib.h"
class ImgSegment :public ImageDib
{
public:
	//输出图像每像素位数
	int m_nBitCountOut;
	//输出图像位图数据指针
	unsigned char * m_pImgDataOut;	
	//输出图像颜色表
	LPRGBQUAD m_lpColorTableOut;	
    //输出图像的宽
	int m_imgWidthOut;	
	//输出图像的高
	int m_imgHeightOut;
	//输出图像颜色表长度
	int m_nColorTableLengthOut;	
public:
	//不带参数的构造函数
	ImgSegment();	
	//带参数的构造函数
	ImgSegment(CSize size, int nBitCount, LPRGBQUAD lpColorTable,unsigned char *pImgData);
	//析构函数
	virtual ~ImgSegment();
public:
	//以像素为单位返回输出图像的尺寸
	CSize GetDimensions();
    //自适应阈值分割
	void AdaptThreshSeg(unsigned char *pImgData);

	//修改自适应测试
	void AdThreshSeg(unsigned char *pImgData);
	
	//最大类间方差分割
	void OtsuThreshold();
	void NewOtsu();
	//Roberts算子
	void Roberts();	
    //Sobel算子
	void Sobel();	
	//Prewitt算子
	void Prewitt();	
	//Laplacian算子
	void Laplacian();	
public:
	//区域生长
	void RegionGrow(CPoint SeedPos, int thresh);
	//曲线跟踪
	void EdgeTrace();
};

