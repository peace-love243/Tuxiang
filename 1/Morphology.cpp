#include "StdAfx.h"
#include  "1.h"
#include "Morphology.h"
#include "math.h"
#include<Afxtempl.h>
#include <algorithm>
#include<vector>
#define PI 3.141592653
Morphology::Morphology(void)
{
	m_pImgDataOut=NULL;//输出图像位图数据指针为空
	m_lpColorTableOut=NULL;//输出图像颜色表指针为空
    m_nBitCountOut=0;//输出图像每像素位数为0	
	m_imgWidthOut=0;//输出图像的宽为0
	m_imgHeightOut=0;//输出图像的高为0
	m_TempBuf=NULL;//结构元素指针为空
	TempH=3;   //结构元素高
	TempW=3;   //结构元素宽
    int i;
	for (i=0;i<TempH*TempW;i++)
		m_InitTemp[i]=0;
}
Morphology::Morphology(CSize size, int nBitCount, LPRGBQUAD lpColorTable,unsigned char *pImgData):
            ImageDib(size, nBitCount, lpColorTable, pImgData)
{
    m_nBitCountOut=m_nBitCount;
	m_lpColorTableOut=NULL;	//输出图像颜色表处理
	int colorTableLength=ComputeColorTabalLength(m_nBitCountOut);
	if(colorTableLength!=0)
	{
      m_lpColorTableOut=new RGBQUAD[colorTableLength];
	  memcpy(m_lpColorTableOut,m_lpColorTable,sizeof(RGBQUAD)*colorTableLength);
	}
	m_imgWidthOut=m_imgWidth;
	m_imgHeightOut=m_imgHeight;
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;
	m_pImgDataOut=new unsigned char[lineByte*m_imgHeight];//申请输出图像所需要的缓冲区
	m_TempBuf=NULL;//结构元素指针为空
	TempH=3;
	TempW=3;
	int i;
	for (i=0;i<TempH*TempW;i++) 
	{
	    m_InitTemp[i]=0;
	}
}
Morphology::~Morphology()
{
	if(m_pImgDataOut!=NULL)
	{
		delete []m_pImgDataOut;
		m_pImgDataOut=NULL;
	}
	if(m_lpColorTableOut!=NULL)
	{
		delete []m_lpColorTableOut;
		m_lpColorTableOut=NULL;
	}
	if(m_TempBuf)
	{
		delete []m_TempBuf;
		m_TempBuf=NULL;
	}
}
CSize Morphology::GetDimensions()
{	
	if(m_pImgDataOut == NULL) return CSize(0, 0);
	return CSize(m_imgWidthOut, m_imgHeightOut);
}
void Morphology::ImgErosion(unsigned char *imgBufIn,unsigned char *imgBufOut,int imgWidth,        //二值腐蚀基本运算
							  int imgHeight,int *TempBuf, int TempW, int TempH) 			
{
	int lineByte=(imgWidth+3)/4*4;	
	memcpy(imgBufOut,imgBufIn,lineByte*imgHeight);	//把输入图像缓冲区的拷贝到输出图像缓冲区
	int i,j,k,l;
	int flag;	                                   //标志变量
	for(i=TempH/2;i<imgHeight-TempH/2;i++)        //针对图像中每一个像素位置，判断是否结构元素能填入目标内部
	{
		for(j=TempW/2;j<imgWidth-TempW/2;j++)
		{			
			flag=1;                              //判断结构元素是否可以在当前点填入目标内部,1为可以,0为不可以
			for(k=-TempH/2;k<=TempH/2;k++)
			{
				for(l=-TempW/2;l<=TempW/2;l++)
				{
					if(TempBuf[(k+TempH/2)*TempW+l+TempW/2])           //如果当前结构元素位置为1,判断与对应图像上的像素点是否为非0
					{
						if(!*(imgBufIn+(i+k)*lineByte+j+l))//如果图像当前象素为0,则没有击中该点,不是腐蚀的输出
							flag=0;	
					}
				}
			}
			if(flag)
				*(imgBufOut+i*lineByte+j)=255;
			else
				*(imgBufOut+i*lineByte+j)=0;
		}
	}
}
void Morphology::InputMask(int *mask,int maskW, int maskH)           //结构元素输入函数，在调用其它函数前必须先调用此函数
{
	if(m_TempBuf)
	{
		delete []m_TempBuf;
		m_TempBuf=NULL;
	}
	m_TempBuf=new int[maskW*maskH];                                //将输入的结构元素拷贝到m_maskBuf缓冲区中
	int i, j;
	for(i=0;i<maskH;i++)
	{
		for(j=0;j<maskW;j++)
			m_TempBuf[i*maskW+j]=mask[i*maskW+j];
	}
	TempW=maskW;                                                     //为结构元素宽和高赋值
	TempH=maskH;
}
void Morphology::ImgDilation(unsigned char *imgBufIn,unsigned char *imgBufOut,int imgWidth,int imgHeight, //二值膨胀基本运算
					 int *TempBuf, int TempW, int TempH)
{
	int lineByte=(imgWidth+3)/4*4;
	memcpy(imgBufOut,imgBufIn,lineByte*imgHeight);
	int i,j,k,l;
	for(i=0;i<imgHeight;i++)                         //膨胀是对图像中目标补集的腐蚀，因此先求输入图像数据的补集
	{
		for(j=0;j<imgWidth;j++)
		{
			k=*(imgBufIn+i*lineByte+j);
			*(imgBufIn+i*lineByte+j)=255-*(imgBufIn+i*lineByte+j);
		}
	}
	int *tempMask=new int[TempW*TempH];//膨胀是结构元素的对称集对补集的腐蚀,此处tempMask存放m_mask的对称集
	for(k=0;k<TempH;k++)
	{
		for(l=0;l<TempW;l++)
			tempMask[k*TempW+l]=TempBuf[(TempH-1-k)*TempW+TempW-1-l];
	}
	int flag;	//标志变量
	for(i=TempH/2;i<imgHeight-TempH/2;i++)
	{
		for(j=TempW/2;j<imgWidth-TempW/2;j++)
		{			
			flag=1;              //判断结构元素是否可以在当前点填入目标内部,1为可以,0为不可以
			for(k=-TempH/2;k<=TempH/2;k++)
			{
				for(l=-TempW/2;l<=TempW/2;l++)
				{
					if(tempMask[(k+TempH/2)*TempW+l+TempW/2])
					{
						if(!*(imgBufIn+(i+k)*lineByte+j+l))
							flag=0;	
					}
				}
			}
			if(flag)
				*(imgBufOut+i*lineByte+j)=255;
			else
				*(imgBufOut+i*lineByte+j)=0;
		}
	}
	for(i=0;i<imgHeight;i++)                     //用结构元素对称集对目标补集腐蚀后,还要对结果再求一次补集,才是膨胀结果输出
	{
		for(j=0;j<imgWidth;j++)
		{
			k=*(imgBufOut+i*lineByte+j);
			*(imgBufOut+i*lineByte+j)=255-*(imgBufOut+i*lineByte+j);
		}
	}
	for(i=0;i<imgHeight;i++)
		for(j=0;j<imgWidth;j++)
			*(imgBufIn+i*lineByte+j)=255-*(imgBufIn+i*lineByte+j);
	delete []tempMask;
}
void Morphology::Open()                //二值开运算
{
	if(m_TempBuf==NULL)
    	return;
	int lineByte=(m_imgWidth+3)/4*4;
	unsigned char *buf=new unsigned char[lineByte*m_imgHeight];//中间结果缓冲区申请,用来存放腐蚀后的中间结果
	ImgErosion(m_pImgData, buf,m_imgWidth,m_imgHeight,m_TempBuf, TempW, TempH);	//先腐蚀
	ImgDilation(buf, m_pImgDataOut,m_imgWidth,m_imgHeight,m_TempBuf, TempW, TempH);	//后膨胀
	delete []buf;	//释放缓冲区
}
void Morphology::Close()                       //二值闭运算
{
	if(m_TempBuf==NULL)
		return;
	int lineByte=(m_imgWidth+3)/4*4;
	unsigned char *buf=new unsigned char[lineByte*m_imgHeight];
	ImgDilation(m_pImgData, buf,m_imgWidth,m_imgHeight,m_TempBuf, TempW, TempH);         //先膨胀
	ImgErosion(buf, m_pImgDataOut,m_imgWidth,m_imgHeight,m_TempBuf, TempW, TempH);        //后腐蚀
	delete []buf;
}
void Morphology::DefineElementPair()               //为击中击不中变换的结构元素对m_hitMissMask赋值，共8对
{
	int i, k, l;//定义8个方向的击中击不中变换结构元素对
	for(i=0;i<12;i++)
	{
		for(k=0;k<3;k++)
		{
			for(l=0;l<3;l++)
			{
				m_hitMissMask[i].hitElement[k*3+l]=0;
				m_hitMissMask[i].missElement[k*3+l]=0;
			}
		}
	}
	m_hitMissMask[0].hitElement[0]=1;
	m_hitMissMask[0].hitElement[1]=1;
	m_hitMissMask[0].hitElement[2]=1;
	m_hitMissMask[0].hitElement[4]=1;
	m_hitMissMask[0].missElement[7]=1;
	m_hitMissMask[1].hitElement[6]=1;
	m_hitMissMask[1].hitElement[7]=1;
	m_hitMissMask[1].hitElement[8]=1;
	m_hitMissMask[1].hitElement[4]=1;
	m_hitMissMask[1].missElement[1]=1;
	m_hitMissMask[2].hitElement[2]=1;
	m_hitMissMask[2].hitElement[5]=1;
	m_hitMissMask[2].hitElement[8]=1;
	m_hitMissMask[2].hitElement[4]=1;
	m_hitMissMask[2].missElement[3]=1;
	m_hitMissMask[3].hitElement[0]=1;
	m_hitMissMask[3].hitElement[3]=1;
	m_hitMissMask[3].hitElement[6]=1;
	m_hitMissMask[3].hitElement[4]=1;
	m_hitMissMask[3].missElement[5]=1;
	m_hitMissMask[4].hitElement[0]=1;
	m_hitMissMask[4].hitElement[1]=1;
	m_hitMissMask[4].hitElement[3]=1;
	m_hitMissMask[4].hitElement[4]=1;
	m_hitMissMask[4].missElement[5]=1;
	m_hitMissMask[4].missElement[7]=1;
	m_hitMissMask[5].hitElement[5]=1;
	m_hitMissMask[5].hitElement[7]=1;
	m_hitMissMask[5].hitElement[8]=1;
	m_hitMissMask[5].hitElement[4]=1;
	m_hitMissMask[5].missElement[1]=1;
	m_hitMissMask[5].missElement[3]=1;
	m_hitMissMask[6].hitElement[1]=1;
	m_hitMissMask[6].hitElement[2]=1;
	m_hitMissMask[6].hitElement[5]=1;
	m_hitMissMask[6].hitElement[4]=1;
	m_hitMissMask[6].missElement[3]=1;
	m_hitMissMask[6].missElement[7]=1;
	m_hitMissMask[7].hitElement[3]=1;
	m_hitMissMask[7].hitElement[6]=1;
	m_hitMissMask[7].hitElement[7]=1;
	m_hitMissMask[7].hitElement[4]=1;
	m_hitMissMask[7].missElement[1]=1;
	m_hitMissMask[7].missElement[5]=1;
	m_hitMissMask[8].hitElement[4]=1;
	m_hitMissMask[8].hitElement[5]=1;
	m_hitMissMask[8].missElement[1]=1;
	m_hitMissMask[8].missElement[3]=1;
	m_hitMissMask[8].missElement[7]=1;
	m_hitMissMask[9].hitElement[4]=1;
	m_hitMissMask[9].hitElement[7]=1;
	m_hitMissMask[9].missElement[1]=1;
	m_hitMissMask[9].missElement[3]=1;
	m_hitMissMask[9].missElement[5]=1;
	m_hitMissMask[10].hitElement[3]=1;
	m_hitMissMask[10].hitElement[4]=1;
	m_hitMissMask[10].missElement[1]=1;
	m_hitMissMask[10].missElement[5]=1;
	m_hitMissMask[10].missElement[7]=1;
	m_hitMissMask[11].hitElement[1]=1;
	m_hitMissMask[11].hitElement[4]=1;
	m_hitMissMask[11].missElement[3]=1;
	m_hitMissMask[11].missElement[5]=1;
	m_hitMissMask[11].missElement[7]=1;
}
void Morphology::HitAndMiss(unsigned char *imgBufIn, unsigned char *imgBufOut,int imgWidth,int imgHeight, ElementPair hitMissMask)	//击中击不中变换				 
{
	int i, j;
	int validateFlag=1;         //标志变量，1表示结构元素对有效，0表示无效
	for(i=0; i<3;i++)        //检查结构元素对是否交集为空,交集若不为空则为无效结构元素对,算法将退出
	{
		for(j=0;j<3;j++)
			if(hitMissMask.hitElement[i*3+j]&&hitMissMask.missElement[i*3+j])
			{
				validateFlag=0;
				break;
			}
	}
	if(validateFlag==0)                 //非法结构元素对,返回
		return;
	int lineByte=(imgWidth+3)/4*4;
	memset(imgBufOut, 0, lineByte*imgHeight);
	int k,l;
	int hitFlag, missFlag;            //击中标志变量和击不中标志变量
	for(i=1; i<imgHeight-1; i++)
	{
		for(j=1;j<imgWidth-1; j++)
		{
			hitFlag=1;
			missFlag=1;
			for(k=-1;k<=1;k++)
			{
				for(l=-1;l<=1;l++)
				{
					if(hitMissMask.hitElement[(k+1)*3+l+1]==1)         //如果击中结构元素当前位置为1
					{
						if(*(imgBufIn+(i+k)*lineByte+j+l))             //判断图像对应点是否为0,如果是,则没有击中图像当前点
							hitFlag=0;
					}
					if(hitMissMask.missElement[(k+1)*3+l+1]==1)        //如果击不中结构元素当前位置为1
					{
						if(!*(imgBufIn+(i+k)*lineByte+j+l))            //判断图像对应点是否为0,如果是,则没有击中图像当前点
							missFlag=0;
					}
				}
			}
			if(hitFlag&&missFlag)
				*(imgBufOut+i*lineByte+j)=255;
		}
	}
}
void Morphology::ImgThinning()            //用击中击不中变换对输入图像进行细化
{
	DefineElementPair();//定义8个方向的结构元素对
	int lineByte=(m_imgWidth+3)/4*4;
	unsigned char *buf=new unsigned char[lineByte*m_imgHeight];
	memcpy(buf, m_pImgData, lineByte*m_imgHeight);
	int i, k, l,m;
	for(m=0;m<4;m++)
	{
		for(i=0;i<12;i++)//用8个方向的结构元素对都对图像作一次击中击不中变换,并将输出结果从原图中去除
		{
			HitAndMiss(buf, m_pImgDataOut, m_imgWidth, m_imgHeight,m_hitMissMask[i]);
			for(k=0;k<m_imgHeight;k++)//将击中击不中变换的输出结果从原数据中去除
				for(l=0;l<lineByte;l++)
					if(*(m_pImgDataOut+k*lineByte+l)==255)
						*(buf+k*lineByte+l)=255;
		}
	}
	memcpy(m_pImgDataOut, buf,lineByte*m_imgHeight);
	delete []buf;
}
void Morphology::Areas()
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
	long m_imgWidthBytes = (m_imgWidth*m_nBitCount / 8 + 3) / 4 * 4;
	long m_imgBitsCount = m_imgWidthBytes*m_imgHeight;
	LPBYTE m_lpImgBits = m_pImgData;                         //图像数据区域指针
	LPBYTE m_lpImgBitsMove;                                  //数据区域移动指针
	int *m_lpnMark;                                          //标记数组指针
	m_lpnMark = NULL;
	int	*m_lpnMarkMove;                                     //标记数组移动指针
	int m_nMarkNumbers;                                     //标记的区域个数		    
	if (m_lpnMark == NULL)                  //申请标记数组空间，记得要在CImage类的构造函数中将 m_lpnMark初始化为NULL
	{
		m_lpnMark = new int[m_imgBitsCount];
		ASSERT(m_lpnMark != NULL);
		m_lpnMarkMove = m_lpnMark;
	}
	;; memset((LPBYTE)m_lpnMark, 0, m_imgBitsCount * 4);
	int nMarkValue = 1;                          //每次标识的值．nMarkValue会在后边递增．来表示不同的区域，从1开始标记
	int nMaxMarkValue = 0;	                   //记录最大的标识的值
	int i, j;
	CList<EqualMark, EqualMark>lEqualMark;
	m_lpImgBitsMove = m_lpImgBits;
	int nEqualNum = 0;
	EqualMark tempEqualMark;                   //用以暂时存放每次找到的等价关系
	m_lpnMarkMove = m_lpnMark;
	m_lpImgBitsMove = m_lpImgBits;
	if (*m_lpImgBitsMove == 255)
		*m_lpnMarkMove = nMarkValue++;
	m_lpnMarkMove++;
	m_lpImgBitsMove++;
	for (i = 1; i <= m_imgWidth; i++)                //标记图象的第一行，此时不会出现等价的情况
	{
		if (*m_lpImgBitsMove == 255)                 //需要标记的情况
		{
			if (*(m_lpnMarkMove - 1) == 0)
			{
				*m_lpnMarkMove = nMarkValue++;
			}
			else
			{
				*m_lpnMarkMove = *(m_lpnMarkMove - 1);
			}
		}
		m_lpnMarkMove++;
		m_lpImgBitsMove++;
	}
	for (j = 1; j <= m_imgHeight; j++)
	{
		m_lpImgBitsMove = m_lpImgBits + j*m_imgWidthBytes;
		m_lpnMarkMove = m_lpnMark + j*m_imgWidthBytes;
		if (*m_lpImgBitsMove == 255)
		{
			if (*(m_lpnMarkMove - m_imgWidthBytes) != 0)//<上>位置被标记过
			{
				*m_lpnMarkMove = *(m_lpnMarkMove - m_imgWidthBytes);
				if (*(m_lpnMarkMove - m_imgWidthBytes) != *(m_lpnMarkMove - m_imgWidthBytes + 1) && *(m_lpnMarkMove - m_imgWidthBytes + 1) != 0)
				{
					AttachEqualMark(tempEqualMark, *(m_lpnMarkMove - m_imgWidthBytes),
						*(m_lpnMarkMove - m_imgWidthBytes + 1), nEqualNum, lEqualMark);//<上><右上>等价标记
				}
			}
			else
			{
				if (*(m_lpnMarkMove - m_imgWidthBytes + 1) != 0)
					*m_lpnMarkMove = *(m_lpnMarkMove - m_imgWidthBytes + 1);   //跟随<右上>标记
				else              //<上>、<右上>都没有标记，则开始新的标记
					*m_lpnMarkMove = nMarkValue++;
			}
		}
		m_lpnMarkMove++;
		m_lpImgBitsMove++;
		for (i = 1; i <= m_imgWidth - 1; i++)           //对每行的中间点做标记处理，此时存在<左>、<左上>、<上>、<右上> 4种情况
		{
			if ((*m_lpImgBitsMove) == 255)
			{
				if (*(m_lpnMarkMove - 1) != 0)
				{
					*m_lpnMarkMove = *(m_lpnMarkMove - 1);          //跟随<左>
					if (*(m_lpnMarkMove - 1) != *(m_lpnMarkMove - m_imgWidthBytes - 1) && *(m_lpnMarkMove - m_imgWidthBytes - 1) != 0)
						AttachEqualMark(tempEqualMark, *(m_lpnMarkMove - 1),*(m_lpnMarkMove - m_imgWidthBytes - 1), nEqualNum, lEqualMark);//标记<左>、<左上>等价
					if (*(m_lpnMarkMove - 1) != *(m_lpnMarkMove - m_imgWidthBytes) && *(m_lpnMarkMove - m_imgWidthBytes) != 0)
						AttachEqualMark(tempEqualMark, *(m_lpnMarkMove - 1),*(m_lpnMarkMove - m_imgWidthBytes), nEqualNum, lEqualMark);//标记<左>、<上>等价
					if (*(m_lpnMarkMove - 1) != *(m_lpnMarkMove - m_imgWidthBytes + 1) && *(m_lpnMarkMove - m_imgWidthBytes + 1) != 0)
						AttachEqualMark(tempEqualMark, *(m_lpnMarkMove - 1),*(m_lpnMarkMove - m_imgWidthBytes + 1), nEqualNum, lEqualMark);//标记<左>、<右上>等价
				}
				else//<左>未被标记过
				{
					if (*(m_lpnMarkMove - m_imgWidthBytes - 1) != 0)                   //<左上>被标记过
					{
						*m_lpnMarkMove = *(m_lpnMarkMove - m_imgWidthBytes - 1);
						if (*(m_lpnMarkMove - m_imgWidthBytes - 1) != *(m_lpnMarkMove - m_imgWidthBytes) && *(m_lpnMarkMove - m_imgWidthBytes) != 0)	
							AttachEqualMark(tempEqualMark, *(m_lpnMarkMove - m_imgWidthBytes - 1),
								*(m_lpnMarkMove - m_imgWidthBytes), nEqualNum, lEqualMark);              //标记<左上>、<上>等价
						if (*(m_lpnMarkMove - m_imgWidthBytes - 1) != *(m_lpnMarkMove - m_imgWidthBytes + 1) && *(m_lpnMarkMove - m_imgWidthBytes + 1) != 0)
							AttachEqualMark(tempEqualMark, *(m_lpnMarkMove - m_imgWidthBytes - 1),
								*(m_lpnMarkMove - m_imgWidthBytes + 1), nEqualNum, lEqualMark);//标记<左上>、<右上>等价
					}
					else                               //<左>、<左上>未标记过
					{
						if (*(m_lpnMarkMove - m_imgWidthBytes) != 0)
						{
							*m_lpnMarkMove = *(m_lpnMarkMove - m_imgWidthBytes);        	//跟随<上>标记
							if (*(m_lpnMarkMove - m_imgWidthBytes) != *(m_lpnMarkMove - m_imgWidthBytes + 1) && *(m_lpnMarkMove - m_imgWidthBytes + 1) != 0)
								AttachEqualMark(tempEqualMark, *(m_lpnMarkMove - m_imgWidthBytes),
									*(m_lpnMarkMove - m_imgWidthBytes + 1), nEqualNum, lEqualMark);//标记<上>和<右上>等价
						}
						else                        //<左>、<左上>、<上>未标记过，此时不存在等价关系
						{
							if (*(m_lpnMarkMove - m_imgWidthBytes + 1) != 0)
								*m_lpnMarkMove = *(m_lpnMarkMove - m_imgWidthBytes + 1);    	//跟随<右上>标记
							else                //<左>、<左上>、<上>、<右上>未标记过，则开始新的标记值
								*m_lpnMarkMove = nMarkValue++;
						}                          
					}                            
				}                               
			}                                    
			m_lpnMarkMove++;
			m_lpImgBitsMove++;
		}                                          
		if ((*m_lpImgBitsMove) == 255)
		{
			if (*(m_lpnMarkMove - 1) != 0)                        //<左>被标记过
			{
				*m_lpnMarkMove = *(m_lpnMarkMove - 1);
				if (*(m_lpnMarkMove - 1) != *(m_lpnMarkMove - m_imgWidthBytes - 1) && *(m_lpnMarkMove - m_imgWidthBytes - 1) != 0)
					AttachEqualMark(tempEqualMark, *(m_lpnMarkMove - 1),
						*(m_lpnMarkMove - m_imgWidthBytes - 1), nEqualNum, lEqualMark);              //标记<左>、<左上>等价
				if (*(m_lpnMarkMove - 1) != *(m_lpnMarkMove - m_imgWidthBytes) && *(m_lpnMarkMove - m_imgWidthBytes) != 0)
					AttachEqualMark(tempEqualMark, *(m_lpnMarkMove - 1),
						*(m_lpnMarkMove - m_imgWidthBytes), nEqualNum, lEqualMark);                   //标记<左>、<上>等价
			}
			else                  //<左>未被标记过
			{
				if (*(m_lpnMarkMove - m_imgWidthBytes - 1) != 0)
				{
					*m_lpnMarkMove = *(m_lpnMarkMove - m_imgWidthBytes - 1);    //跟随<左上>
					if (*(m_lpnMarkMove - m_imgWidthBytes - 1) != *(m_lpnMarkMove - m_imgWidthBytes) && *(m_lpnMarkMove - m_imgWidthBytes) != 0)
						AttachEqualMark(tempEqualMark, *(m_lpnMarkMove - m_imgWidthBytes - 1),
							*(m_lpnMarkMove - m_imgWidthBytes), nEqualNum, lEqualMark);//标记<左上>、<上>等价
				}
				else//<左>、<左上>未标记过
				{
					if (*(m_lpnMarkMove - m_imgWidthBytes) != 0)
						*m_lpnMarkMove = *(m_lpnMarkMove - m_imgWidthBytes);   	//跟随<上>标记
					else//<左>、<左上>、<上>未标记过,则开始新的标记值
						*m_lpnMarkMove = nMarkValue++;
				}
			}
		}  
	}  
	nMaxMarkValue = nMarkValue - 1;	
	CPtrList exList;         //定义双层链表的外层链表，它的元素是一个指向内层链表的指针内层链表的型别也是CptrList，其元素是标记值
	CPtrList *plnnerList;
	POSITION posExElem;
	if (lEqualMark.GetCount() != 0)
	{
		CPtrList* plnnerListAdd = new CPtrList;//pInnerListAdd，每次向exList中添加的新元素
		ASSERT(plnnerListAdd != NULL);
		plnnerListAdd->AddTail((void*)lEqualMark.GetHead().MarkValue1);
		plnnerListAdd->AddTail((void*)lEqualMark.GetHead().MarkValue2);
		exList.AddTail((void*)plnnerListAdd);
		lEqualMark.RemoveHead();
		CPtrList* pFindValue1 = NULL;//定义pFindVaIuel和pFindVaIue2．存放在所有内层链表中找到特
		CPtrList* pFindValue2 = NULL;//定值的某个内层链表的头指针，也就是外层链表的某个元素值
		while (!lEqualMark.IsEmpty())//整理剩余的等价对
		{
			posExElem = exList.GetHeadPosition();
			pFindValue1 = NULL;
			pFindValue2 = NULL;
			while (posExElem)
			{
				plnnerList = (CPtrList*)exList.GetAt(posExElem);
				if (plnnerList->Find((void*)lEqualMark.GetHead().MarkValue1))
					pFindValue1 = plnnerList;
				if (plnnerList->Find((void*)lEqualMark.GetHead().MarkValue2))
					pFindValue2 = plnnerList;
				exList.GetNext(posExElem);
			}
			if (pFindValue1&&pFindValue2)              //该等价对中两个值都在已经整理过的等价关系中
			{
				if (pFindValue1 != pFindValue2)           //当两个地址不一样时，对链表进行调整
				{
					pFindValue1->AddTail(pFindValue2);
					POSITION posDelete = exList.Find((void*)pFindValue2);
					pFindValue2->RemoveAll();
					delete pFindValue2;
					exList.RemoveAt(posDelete);
				}
			}
			else if (pFindValue1)             //8只在已经整理过的等价关系中找到Vafuel，那么将value2加到Valuel所在的链表中
				pFindValue1->AddTail((void*)lEqualMark.GetHead().MarkValue2);
			else if (pFindValue2)
				pFindValue2->AddTail((void*)lEqualMark.GetHead().MarkValue1);
			else                     //等价对中两个值在整理过的等价关系中都没有找到，则在exList中增加新元素
			{
				CPtrList* plnnerListAdd = new CPtrList;
				plnnerListAdd->AddTail((void*)lEqualMark.GetHead().MarkValue1);
				plnnerListAdd->AddTail((void*)lEqualMark.GetHead().MarkValue2);
				exList.AddTail((void*)plnnerListAdd);
			}
			lEqualMark.RemoveHead();           //去掉此时等价对的头元素
		}
	}
	else
	{

	}
	int nTotalEqualNum = 0;               //列入等价关系的标记个数
	int nMarkRegion = 0;                 //图像中连通区域个数
	posExElem = exList.GetHeadPosition();
	while (posExElem)
	{
		plnnerList = (CPtrList*)exList.GetAt(posExElem);
		nTotalEqualNum += plnnerList->GetCount();
		exList.GetNext(posExElem);
	}
	nMarkRegion = nMaxMarkValue - nTotalEqualNum + exList.GetCount();
	using std::vector;
	vector<MarkMapping>vMarkMap(nMaxMarkValue);
	for (i = 0; i<nMaxMarkValue; i++)               //初始化映射向量，令其做自身映射
	{
		vMarkMap[i].nOriginalMark = i + 1;
		vMarkMap[i].nMappingMark = i + 1;
	}
	POSITION poslnneElem;                           //lnnerLjst中元素的位置
	int nMin;                                     //1nnerList中最小值
	int nIndex = 0;
	posExElem = exList.GetHeadPosition();
	while (posExElem)
	{
		plnnerList = (CPtrList*)exList.GetAt(posExElem);
		nMin = (int)plnnerList->GetHead();
		poslnneElem = plnnerList->GetHeadPosition();
		plnnerList->GetNext(poslnneElem);
		while (poslnneElem)
		{
			if ((int)plnnerList->GetAt(poslnneElem)<nMin)
				nMin = (int)plnnerList->GetAt(poslnneElem);
			plnnerList->GetNext(poslnneElem);
		}
		poslnneElem = plnnerList->GetHeadPosition();//根据每组等价关系中的最小的标记值对Mapping向量做出调整。
		while (poslnneElem)
		{
			nIndex = (int)plnnerList->GetAt(poslnneElem) - 1;
			vMarkMap[nIndex].nMappingMark = nMin;
			plnnerList->GetNext(poslnneElem);
		}
		exList.GetNext(posExElem);
	}
	vector<int>vSortMark(nMarkRegion);                    //排序向量
	nIndex = 0;
	for (i = 0; i<nMaxMarkValue; i++)
		if (find(vSortMark.begin(), vSortMark.end(), vMarkMap[i].nMappingMark) == vSortMark.end())
			vSortMark[nIndex++] = vMarkMap[i].nMappingMark;
	sort(vSortMark.begin(), vSortMark.end());
	vector<int>::iterator itFind;
	vector<int>::iterator itBegin;
	itBegin = vSortMark.begin();
	for (i = 0; i<nMaxMarkValue; i++)
	{
		itFind = find(vSortMark.begin(), vSortMark.end(), vMarkMap[i].nMappingMark);
		vMarkMap[i].nMappingMark = (itFind - itBegin + 1);
	}
	for (j = 0; j<m_imgHeight; j++)
	{
		m_lpnMarkMove = m_lpnMark + j*m_imgWidthBytes;
		for (i = 0; i<m_imgWidth; i++)
		{
			if (*m_lpnMarkMove != 0)
			{
				*m_lpnMarkMove = vMarkMap[*m_lpnMarkMove - 1].nMappingMark;
			}
			m_lpnMarkMove++;
		}
	}
	posExElem = exList.GetHeadPosition();
	while (posExElem)
	{
		plnnerList = (CPtrList*)exList.GetAt(posExElem);
		plnnerList->RemoveAll();
		delete plnnerList;
		exList.GetNext(posExElem);
	}
	exList.RemoveAll();
	m_nMarkNumbers = nMarkRegion;
	int count[3000] = { 0 }, len[3000] = { 0 }, mean = 0,MAXAreas=100;
	double C[3000] = {0};
	for (int k = 1; k <= m_nMarkNumbers; k++)
	{
		for (i = 1; i<m_imgHeight - 1; i++)
		{
			for (j = 1; j<m_imgWidth - 1; j++)
			{
				if (*(m_lpnMark + i*m_imgWidthBytes + j) == k)
					count[k]++;
				if (*(m_lpnMark + i*m_imgWidthBytes + j) == k && (*(m_lpnMark + i*m_imgWidthBytes + j - 1) != k
					|| *(m_lpnMark + i*m_imgWidthBytes + j + 1) != k || *(m_lpnMark + (i + 1)*m_imgWidthBytes + j) != k ||
					*(m_lpnMark + (i - 1)*m_imgWidthBytes + j) != k))
					len[k]++;
			}
		}
		C[k]=4.0*PI*count[k]/(len[k]*len[k]*1.0);
		if (MAXAreas < count[k])
			MAXAreas = count[k];
	}
	MAXAreas /= 10;
	for (int k = 1; k <= m_nMarkNumbers; k++)
	{
		if (count[k] < MAXAreas)                  //先滤除区域面积小于图像中最大区域面积1/10的区域
		{
			for (i = 1; i < m_imgHeight - 1; i++)
				for (j = 1; j < m_imgWidth - 1; j++)
					if (*(m_lpnMark + i*m_imgWidthBytes + j) == k)
						*(m_pImgData + i*m_imgWidthBytes + j) = 0;
		}
		else if (C[k] < 0.70)                           //再滤除图像中区域圆形度小于0.75的噪声干扰区域
		{
			for (i = 1; i < m_imgHeight - 1; i++)
				for (j = 1; j < m_imgWidth - 1; j++)
					if (*(m_lpnMark + i*m_imgWidthBytes + j) == k)
						*(m_pImgData + i*m_imgWidthBytes + j) = 0;
		}
		else
		{
			for (i = 0; i<m_imgHeight; i++)
			{
				for (j = 0; j<m_imgWidth; j++)
				{
					if (*(m_lpnMark + i*m_imgWidthBytes + j) == k)
						*(m_pImgData + i*m_imgWidthBytes + j) = 255;
				}
			}
		}
	}
	for (i = 0; i<m_imgHeight; i++)                        //将处理结果显示出来
	{
		for (j = 0; j<m_imgWidth; j++)
		{
			*(m_pImgDataOut + i*m_imgWidthBytes + j) = *(m_pImgData + i*m_imgWidthBytes + j);
		}
	}
}
template<typename elemType> void Morphology::AttachEqualMark(EqualMark &pEqualMark,
	elemType num1, elemType num2, int & pEqualNum, CList< EqualMark, EqualMark > & plEqualMark)
{
	if (num1 < num2)//num1小的情况
	{
		if (pEqualMark.MarkValue1 != num1 || pEqualMark.MarkValue2 != num2)
		{
			pEqualMark.MarkValue1 = num1;
			pEqualMark.MarkValue2 = num2;
			pEqualNum++;
			plEqualMark.AddTail(pEqualMark);
		}
	}
	else                           //num2小的情况
	{
		if (pEqualMark.MarkValue2 != num1 || pEqualMark.MarkValue1 != num2)
		{
			pEqualMark.MarkValue1 = num2;
			pEqualMark.MarkValue2 = num1;
			pEqualNum++;
			plEqualMark.AddTail(pEqualMark);
		}
	}
}
