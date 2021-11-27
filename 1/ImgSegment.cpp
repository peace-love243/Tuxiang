#include "StdAfx.h"
#include "1.h"
#include <math.h>
#include "ImgSegment.h"
ImgSegment::ImgSegment(void)
{
	m_pImgDataOut=NULL;
	m_lpColorTableOut=NULL;
	m_nColorTableLengthOut=0;
    m_nBitCountOut=0;	
	m_imgWidthOut=0;
	m_imgHeightOut=0;
}
ImgSegment::ImgSegment(CSize size, int nBitCount, LPRGBQUAD lpColorTable, unsigned char *pImgData):
ImageDib(size, nBitCount, lpColorTable, pImgData)
{
	m_pImgDataOut=NULL;
	m_lpColorTableOut=NULL;
	m_nColorTableLengthOut = 0;
    m_nBitCountOut=0;
	m_imgWidthOut=0;
	m_imgHeightOut=0;
}
ImgSegment::~ImgSegment()
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
}
CSize ImgSegment::GetDimensions()
{	
	if(m_pImgDataOut == NULL)
		return CSize(0, 0);
	return CSize(m_imgWidthOut, m_imgHeightOut);
}
void ImgSegment::Roberts()           //Roberts边缘检测
{
	if(m_pImgDataOut!=NULL)         //释放m_pImgDataOut指向的图像数据空间
	{
		delete []m_pImgDataOut;
    	m_pImgDataOut=NULL;
	}
	if(m_lpColorTableOut!=NULL)
	{
		delete []m_lpColorTableOut;
		m_lpColorTableOut=NULL;
	}
	m_nBitCountOut=m_nBitCount;
	m_nColorTableLengthOut=ComputeColorTabalLength(m_nBitCountOut);
	if(m_nColorTableLengthOut!=0)
	{
    	m_lpColorTableOut=new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut,m_lpColorTable,sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}
	m_imgWidthOut=m_imgWidth;
	m_imgHeightOut=m_imgHeight;
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;
	m_pImgDataOut=new unsigned char[lineByte*m_imgHeight];
	int i,j;
	int pixelByte=m_nBitCount/8;
	int k;
	int x, y, t;//中间变量
	for(i=1;i<m_imgHeight-1;i++)//Roberts算子
	{
		for(j=1;j<m_imgWidth-1;j++)
		{
			for(k=0;k<pixelByte;k++)
			{
				x=*(m_pImgData+i*lineByte+j*pixelByte+k)-*(m_pImgData+(i+1)*lineByte+j*pixelByte+k);//x方向梯度
				y=*(m_pImgData+i*lineByte+j*pixelByte+k)-*(m_pImgData+i*lineByte+(j+1)*pixelByte+k);//y方向梯度
				t=sqrt(double((x*x+y*y)+0.5));
				if(t>255)
					t=255;
				*(m_pImgDataOut+i*lineByte+j*pixelByte+k)=t;
			}
		}
	}
}
void ImgSegment::Sobel()              //Sobel边缘检测
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
	m_nBitCountOut=m_nBitCount;
	m_nColorTableLengthOut=ComputeColorTabalLength(m_nBitCountOut);
	if(m_nColorTableLengthOut!=0)
	{
    	m_lpColorTableOut=new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut,m_lpColorTable,sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}
	m_imgWidthOut=m_imgWidth;
	m_imgHeightOut=m_imgHeight;
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;
	m_pImgDataOut=new unsigned char[lineByte*m_imgHeight];
	int i,j;
	int pixelByte=m_nBitCount/8;
	int k;
	int x, y, t;
	for(i=1;i<m_imgHeight-1;i++)
	{
		for(j=1;j<m_imgWidth-1;j++)
		{
			for(k=0;k<pixelByte;k++)
			{
				
				x= *(m_pImgData+(i-1)*lineByte+(j+1)*pixelByte+k)+ 2 * *(m_pImgData+i*lineByte+(j+1)*pixelByte+k)//x方向梯度
				 + *(m_pImgData+(i+1)*lineByte+(j+1)*pixelByte+k) - *(m_pImgData+(i-1)*lineByte+(j-1)*pixelByte+k)
				 - 2 * *(m_pImgData+i*lineByte+(j-1)*pixelByte+k) - *(m_pImgData+(i+1)*lineByte+(j-1)*pixelByte+k);
				y= *(m_pImgData+(i-1)*lineByte+(j-1)*pixelByte+k) + 2 * *(m_pImgData+(i-1)*lineByte+j*pixelByte+k)//y方向梯度
				 + *(m_pImgData+(i-1)*lineByte+(j+1)*pixelByte+k)- *(m_pImgData+(i+1)*lineByte+(j-1)*pixelByte+k)
				 - 2 * *(m_pImgData+(i+1)*lineByte+j*pixelByte+k) - *(m_pImgData+(i+1)*lineByte+(j+1)*pixelByte+k);
				t=sqrt(double((x*x+y*y)+0.5));
				if(t>255)
					t=255;
				*(m_pImgDataOut+i*lineByte+j*pixelByte+k)=t;
			}
		}
	}
}
void ImgSegment::Prewitt()           //Prewitt边缘检测
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
	m_nBitCountOut=m_nBitCount;
	m_nColorTableLengthOut=ComputeColorTabalLength(m_nBitCountOut);
	if(m_nColorTableLengthOut!=0)
	{
    	m_lpColorTableOut=new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut,m_lpColorTable,sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}
	m_imgWidthOut=m_imgWidth;
	m_imgHeightOut=m_imgHeight;
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;
	m_pImgDataOut=new unsigned char[lineByte*m_imgHeight];
	int i,j;
	int pixelByte=m_nBitCount/8;
	int k;
	int x, y, t;
	for(i=1;i<m_imgHeight-1;i++)
	{
		for(j=1;j<m_imgWidth-1;j++)
		{
			for(k=0;k<pixelByte;k++)
			{
				
				x= *(m_pImgData+(i-1)*lineByte+(j+1)*pixelByte+k) + *(m_pImgData+i*lineByte+(j+1)*pixelByte+k) //x方向梯度
					+ *(m_pImgData+(i+1)*lineByte+(j+1)*pixelByte+k) - *(m_pImgData+(i-1)*lineByte+(j-1)*pixelByte+k)
					- *(m_pImgData+i*lineByte+(j-1)*pixelByte+k) - *(m_pImgData+(i+1)*lineByte+(j-1)*pixelByte+k);
				y= *(m_pImgData+(i-1)*lineByte+(j-1)*pixelByte+k) + *(m_pImgData+(i-1)*lineByte+j*pixelByte+k)//y方向梯度
				 + *(m_pImgData+(i-1)*lineByte+(j+1)*pixelByte+k) - *(m_pImgData+(i+1)*lineByte+(j-1)*pixelByte+k)
				 - *(m_pImgData+(i+1)*lineByte+j*pixelByte+k) - *(m_pImgData+(i+1)*lineByte+(j+1)*pixelByte+k);
				t=sqrt(double((x*x+y*y)+0.5));
				if(t>255)
					t=255;
				*(m_pImgDataOut+i*lineByte+j*pixelByte+k)=t;
			}
		}
	}
}
void ImgSegment::Laplacian()       //Laplacian边缘检测
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
	m_nBitCountOut=m_nBitCount;
	m_nColorTableLengthOut=ComputeColorTabalLength(m_nBitCountOut);
	if(m_nColorTableLengthOut!=0)
	{
    	m_lpColorTableOut=new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut,m_lpColorTable,sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}
	m_imgWidthOut=m_imgWidth;
	m_imgHeightOut=m_imgHeight;
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;
	m_pImgDataOut=new unsigned char[lineByte*m_imgHeight];
	int i,j;
	int pixelByte=m_nBitCount/8;
	int k;
	int t;
	for(i=1;i<m_imgHeight-1;i++)
	{
		for(j=1;j<m_imgWidth-1;j++)
		{
			for(k=0;k<pixelByte;k++)
			{
				t= 4 * *(m_pImgData+i*lineByte+j*pixelByte+k)- *(m_pImgData+(i-1)*lineByte+j*pixelByte+k)
				 - *(m_pImgData+(i+1)*lineByte+j*pixelByte+k)
				 - *(m_pImgData+i*lineByte+(j-1)*pixelByte+k)
				 - *(m_pImgData+i*lineByte+(j+1)*pixelByte+k);

				t=abs(t)+0.5;
				if(t>255)
					t=255;
				*(m_pImgDataOut+i*lineByte+j*pixelByte+k)=t;
			}
		}
	}
}
void ImgSegment::EdgeTrace()                //目标的边界跟踪
{
	if (m_nBitCount != 8)
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
	m_nBitCountOut = m_nBitCount;
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);
	if (m_nColorTableLengthOut != 0) 
	{
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut, m_lpColorTable,sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;
	int lineByte = (m_imgWidth*m_nBitCount / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByte*m_imgHeight];
	memset(m_pImgDataOut, 255, lineByte*m_imgHeight);
	//顺时针定义中心像素点的8邻域坐标，第一列为x方向的偏移,第二列为y方向的偏移
	int direction[8][2] = { { -1,1 },{ 0,1 },{ 1,1 },{ 1,0 },{ 1,-1 },{ 0,-1 },{ -1,-1 },{ -1,0 } };
	CPoint startP, currentP, neighborP;                                    //边界起始点,待处理的当前点,当前点的邻域点
	int findStartPoint;                                                    //是否当前点与起始边界点重合的标志变量
	findStartPoint = 0;                                                    //搜索边界起始点
	int i, j;
	for (i = 0; i<m_imgHeight; i++) 
	{
		for (j = 0; j<m_imgWidth; j++) 
		{
			if (*(m_pImgData + i*lineByte + j) == 0)                      //找到起始边界点
			{
				startP.x = j;
				startP.y = i;
				*(m_pImgDataOut + i*lineByte + j) = 0;
				findStartPoint = 1;
				break;
			}
		}
		if (findStartPoint)                                              //已经找到起始边界点
			break;
	}
	currentP.x = startP.x;
	currentP.y = startP.y;
	int isContourP;                                                     //邻域点是否边界点标志变量
	int startDirect = 0;
	findStartPoint = 0;
	while (findStartPoint == 0)
	{
		isContourP = false;
		while (isContourP == false) 
		{
			neighborP.x = currentP.x + direction[startDirect][0];
			neighborP.y = currentP.y + direction[startDirect][1];
			if (*(m_pImgData + neighborP.y*lineByte + neighborP.x) == 0) 
			{
				isContourP = true;
				currentP.x = neighborP.x;
				currentP.y = neighborP.y;
				if (currentP.x == startP.x&&currentP.y == startP.y)
					findStartPoint = true;
				*(m_pImgDataOut + currentP.y*lineByte + currentP.x) = 0;
				startDirect -= 2;                                         //扫描方向逆时针旋转90度
				if (startDirect<0)
					startDirect += 8;
			}
			else 
			{                                                           //扫描方向顺时针旋转45度
				startDirect++;
				if (startDirect == 8)
					startDirect = 0;
			}
		}
	}
}
void ImgSegment::RegionGrow(CPoint SeedPos, int thresh)                   //区域生长
{
	if (m_nBitCount != 8)
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
	m_nBitCountOut = m_nBitCount;
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);
	if (m_nColorTableLengthOut != 0) 
	{
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut, m_lpColorTable,sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;
	int lineByte = (m_imgWidth*m_nBitCount / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByte*m_imgHeight];
	memset(m_pImgDataOut, 255, lineByte*m_imgHeight);
	//二维数组direction代表中心像素点8邻域坐标与该点在x和y方向上的偏移
	int direction[8][2] = { { 0,1 },{ 1,1 },{ 1,0 },{ 1,-1 },{ 0,-1 },{ -1,-1 },{ -1,0 },{ -1,1 } };
	CPoint *stack = new CPoint[m_imgWidth*m_imgHeight];                   //栈申请，此处假定进栈的像素最多为图像总像素数
	int top;                                                              //栈顶指针
	CPoint currentPoint, popPoint;                                        //当前正处理的点和弹出的点
	int k;  
	int label;                                                            //标记变量
	int temp1, temp2;
	temp1 = *(m_pImgData + SeedPos.y*lineByte + SeedPos.x);                //记录种子像素的灰度值
	*(m_pImgDataOut + SeedPos.y*lineByte + SeedPos.x) = 0;                  //将给定种子点置标记0,入栈
	top = 0;
	stack[top].x = SeedPos.x;
	stack[top].y = SeedPos.y;
	while (top>-1) 
	{
		popPoint.x = stack[top].x;                                          //弹出栈顶元素,该元素已经生长过
		popPoint.y = stack[top].y;
		top--;
		for (k = 0; k < 8; k++)
		{
			currentPoint.x = popPoint.x + direction[k][0];
			currentPoint.y = popPoint.y + direction[k][1];
			if (currentPoint.x<0 || currentPoint.x>m_imgWidth - 1 || currentPoint.y<0 || currentPoint.y>m_imgHeight - 1)
				continue;
			label = *(m_pImgDataOut + currentPoint.y*lineByte + currentPoint.x);
			if (label == 255)                                                //弹出的点周围有尚没生长的点
			{
				temp2 = *(m_pImgData + currentPoint.y*lineByte + currentPoint.x);
				if (abs(temp1 - temp2) < thresh)                                  //如果当前被考察的像素灰度值与种子点灰度值之差小于给定的阈值,则认为相似,将其进栈处理
				{
					*(m_pImgDataOut + currentPoint.y*lineByte + currentPoint.x) = 0;    //给该点置生长标记0
					top++;
					stack[top].x = currentPoint.x;
					stack[top].y = currentPoint.y;
				}
			}
		}
	}
	delete[]stack;
}
void ImgSegment::AdThreshSeg(unsigned char *pImgData)           //整体自适应阈值分割
{
	if(m_nBitCount!=8)
		return;
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
	m_nBitCountOut=m_nBitCount;
	m_nColorTableLengthOut=ComputeColorTabalLength(m_nBitCountOut);
	if(m_nColorTableLengthOut!=0)
	{
		m_lpColorTableOut=new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut,m_lpColorTable,sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}
	m_imgWidthOut=m_imgWidth;
	m_imgHeightOut=m_imgHeight;
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;
	m_pImgDataOut=new unsigned char[lineByte*m_imgHeight];
	int i,j;
	int nLocalThresh[2][2] ;// 局部阈值
	int nLocAvg =0;// 子图象的平均值
	for(j=0; j<m_imgHeight ; j++ )
	{
		for(i=0; i<m_imgWidth ; i++ )
		{
			nLocAvg += pImgData[j*lineByte + i];
		}
	}
	nLocAvg /= ( (m_imgHeight) * (m_imgWidth) ) ;// 计算均值
	nLocalThresh[0][0] = nLocAvg ;// 设置阈值为子图象的平均值
	for(j=0; j<m_imgHeight ; j++ )     // 对整幅图像逐点扫描进行分割：
	{
		for(i=0; i<m_imgWidth; i++ )
		{
			if(pImgData[j*lineByte + i]<nLocalThresh[0][0])
				m_pImgDataOut[j*lineByte + i] = 255 ;
			else
			{
				m_pImgDataOut[j*lineByte + i] = 0 ;
			}
		}
	}
	for(j=0; j<m_imgHeight ; j++ )
	{
		for(i=0; i<m_imgWidth ; i++ )
		{
			m_pImgDataOut[j*lineByte + i] = 255 - m_pImgDataOut[j*lineByte + i] ;
		}
	}
}

void ImgSegment::AdaptThreshSeg(unsigned char *pImgData)     //局部自适应阈值分割
{
	if(m_nBitCount!=8)
		return;
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
	m_nBitCountOut=m_nBitCount;
	m_nColorTableLengthOut=ComputeColorTabalLength(m_nBitCountOut);
	if(m_nColorTableLengthOut!=0)
	{
		m_lpColorTableOut=new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut,m_lpColorTable,sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}
	m_imgWidthOut=m_imgWidth;
	m_imgHeightOut=m_imgHeight;
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;
	m_pImgDataOut=new unsigned char[lineByte*m_imgHeight];
	int i,j;
	int nLocalThresh[2][2] ;  // 局部阈值
	int nLocAvg =0;     // 子图象的平均值
	for(j=0; j<m_imgHeight/2 ; j++ )  // 对左上图像逐点扫描：
	{
		for(i=0; i<m_imgWidth/2 ; i++ )
		{
			nLocAvg += pImgData[j*lineByte + i];
		}
	}
	nLocAvg /= ( (m_imgHeight/2) * (m_imgWidth/2) ) ;     // 计算均值
	nLocalThresh[0][0] = nLocAvg ;                        // 设置阈值为子图象的平均值
	for(j=0; j<m_imgHeight/2 ; j++ )                      // 对左上图像逐点扫描进行分割
	{
		for(i=0; i<m_imgWidth/2 ; i++ )
		{
			if(pImgData[j*lineByte + i]<nLocalThresh[0][0])
				m_pImgDataOut[j*lineByte + i] = 255 ;
			else
			{
				m_pImgDataOut[j*lineByte + i] = 0 ;
			}
		}
	}
	nLocAvg = 0 ;
	for(j=m_imgHeight/2; j<m_imgHeight ; j++ )            // 对左下图像逐点扫描
	{
		for(i=0; i<m_imgWidth/2 ; i++ )
		{
			nLocAvg += pImgData[j*lineByte + i];
		}
	}
	nLocAvg /= ( (m_imgHeight - m_imgHeight/2) * (m_imgWidth/2) ) ;
	nLocalThresh[1][0] = nLocAvg ;                       // 设置阈值为子图象的平均值
	for(j=m_imgHeight/2; j<m_imgHeight ; j++ )           // 对左下图像逐点扫描进行分割
	{
		for(i=0; i<m_imgWidth/2 ; i++ )
		{
			if(pImgData[j*lineByte + i]<nLocalThresh[1][0])
			    m_pImgDataOut[j*lineByte + i] = 255 ;
			else
			{
				m_pImgDataOut[j*lineByte + i] = 0 ;
			}
		}
	}
	nLocAvg = 0 ;
	for(j=0; j<m_imgHeight/2 ; j++ )                     // 对右上图像逐点扫描
	{
		for(i=m_imgWidth/2; i<m_imgWidth ; i++ )
		{
			nLocAvg += pImgData[j*lineByte + i];
		}
	}
	nLocAvg /= ( (m_imgHeight/2) * (m_imgWidth - m_imgWidth/2) ) ;
	nLocalThresh[0][1] = nLocAvg ;
	for(j=0; j<m_imgHeight/2 ; j++ )                    // 对右上图像逐点扫描进行分割
	{
		for(i=m_imgWidth/2; i<m_imgWidth ; i++ )
		{
			if(pImgData[j*lineByte + i]<nLocalThresh[0][1])
				m_pImgDataOut[j*lineByte + i] = 255 ;
			else
			{
				m_pImgDataOut[j*lineByte + i] = 0 ;
			}
		}
	}
	nLocAvg = 0 ;
	for(j=m_imgHeight/2; j<m_imgHeight ; j++ )             // 对右下图像逐点扫描
	{
		for(i=m_imgWidth/2; i<m_imgWidth ; i++ )
		{
			nLocAvg +=pImgData[j*lineByte + i];
		}
	}
	nLocAvg /= ( (m_imgHeight - m_imgHeight/2) * (m_imgWidth - m_imgWidth/2) ) ;
	nLocalThresh[1][1] = nLocAvg ;
	for (j = m_imgHeight / 2; j < m_imgHeight; j++)            // 对右下图像逐点扫描进行分割
	{
		for (i = m_imgWidth / 2; i < m_imgWidth; i++)
		{
			if (pImgData[j*lineByte + i] < nLocalThresh[1][1])
				m_pImgDataOut[j*lineByte + i] = 255;
			else
			{
				m_pImgDataOut[j*lineByte + i] = 0;
			}
		}
	}
}
void ImgSegment::OtsuThreshold()
{
	if(m_nBitCount!=8)
		return;
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
	m_nBitCountOut=m_nBitCount;
	m_nColorTableLengthOut=ComputeColorTabalLength(m_nBitCountOut);
	if(m_nColorTableLengthOut!=0)
	{
		m_lpColorTableOut=new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut,m_lpColorTable,sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}
	m_imgWidthOut=m_imgWidth;
	m_imgHeightOut=m_imgHeight;
	int lineByte=(m_imgWidth*m_nBitCount /8+3)/4*4;
	m_pImgDataOut=new unsigned char[lineByte*m_imgHeight];
	int i,j;
	int nGrayHistogram[256];//灰度直方图数组
	memset(nGrayHistogram,0,sizeof(nGrayHistogram));
	int nPixel;
	for(j=0;j<m_imgHeight;j++)
	{
		for(i=0;i<m_imgWidth;i++)
		{
			nPixel=m_pImgData[lineByte*j + i];
			nGrayHistogram[nPixel]++;
		}
	}
	float u0,u1;          //c0  c1组的均值
	float w0,w1;          //c0   c1组的概率
	int nCount0;           //c0组的像素总数
	int nT,nBestT;          //阈值和最佳阈值（对应方差最大时的阈值）
	float fVaria,fMaxVaria=0;//方差和最大方差
	int nSum=0;//统计直方图中像素点的总数，并保存至nSum 中
	for(i=0;i<256;i++)
		nSum+=nGrayHistogram[i];
	for(nT=0;nT<255;nT++)                    //令阈值nT从0遍历到255
	{
		u0=0;
		nCount0=0;
		for(i=0;i<=nT;i++)
		{
			u0+=i*nGrayHistogram[i];
			nCount0+=nGrayHistogram[i];
		}
		u0/=nCount0;
		w0=(float)nCount0/nSum;             //阈值为nT时，计算c0组的均值和概率
		u1=0;
		for(i=nT+1;i<256;i++)
			u1+=i*nGrayHistogram[i];
		u1 /=(nSum-nCount0);
		w1=1-w0;                          //当阈值为nT时，计算c1组的均值和概率
		fVaria=w0*w1*(u0-u1)*(u0-u1);     
		if(fVaria>fMaxVaria)
		{
			fMaxVaria=fVaria;
			nBestT=nT;
		}
	}
	for(j=0;j<m_imgHeightOut;j++)
		for(i=0;i<m_imgWidthOut;i++)
		{
			if(m_pImgData[j*lineByte + i]<nBestT)
				m_pImgDataOut[j*lineByte + i]=0;
			else 
				m_pImgDataOut[j*lineByte + i]=255;
		}
}
void ImgSegment::NewOtsu()
{
	if (m_nBitCount != 8)
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
	m_nBitCountOut = m_nBitCount;
	m_nColorTableLengthOut = ComputeColorTabalLength(m_nBitCountOut);
	if (m_nColorTableLengthOut != 0)
	{
		m_lpColorTableOut = new RGBQUAD[m_nColorTableLengthOut];
		memcpy(m_lpColorTableOut, m_lpColorTable,
			sizeof(RGBQUAD)*m_nColorTableLengthOut);
	}
	m_imgWidthOut = m_imgWidth;
	m_imgHeightOut = m_imgHeight;
	int lineByte = (m_imgWidth*m_nBitCount / 8 + 3) / 4 * 4;
	m_pImgDataOut = new unsigned char[lineByte*m_imgHeight];
	int i, j;
	int nGrayHistogram[256];//灰度直方图数组
	memset(nGrayHistogram, 0, sizeof(nGrayHistogram));
	int nPixel;
	for (j = 0; j<m_imgHeight; j++)
	{
		for (i = 0; i<m_imgWidth; i++)
		{
			nPixel = m_pImgData[lineByte*j + i];
			nGrayHistogram[nPixel]++;
		}
	}
	float u0, u1;          //c0  c1组的均值
	float w0, w1;          //c0   c1组的概率
	int nCount0;           //c0组的像素总数
	int nT, nBestT;          //阈值和最佳阈值（对应方差最大时的阈值）
	float fVaria, fMaxVaria = 0;//方差和最大方差
	int nSum = 0;//统计直方图中像素点的总数，并保存至nSum 中
	for (i = 0; i<256; i++)
		nSum += nGrayHistogram[i];
	for (nT = 0; nT<255; nT++)         //令阈值nT从0遍历到255
	{
		u0 = 0;
		nCount0 = 0;
		for (i = 0; i <= nT; i++)
		{
			u0 += i*nGrayHistogram[i];
			nCount0 += nGrayHistogram[i];
		}
		u0 /= nCount0;
		w0 = (float)nCount0 / nSum;        //阈值为nT时，计算c0组的均值和概率
		u1 = 0;
		for (i = nT + 1; i<256; i++) 
			u1 += i*nGrayHistogram[i];
		u1 /= (nSum - nCount0);
		w1 = 1 - w0;                       //当阈值为nT时，计算c1组的均值和概率
		int mean = u0*w0 + u1*w1;
		if(w0>(5*w1)||w0<(5*w1))                     //c0组与c1组像素的概率值悬殊超过5倍时，加入幂运算
			fVaria = pow(w0, float(0.85))*(u0 - mean)*(u0 - mean) + pow(w1, float(0.85))*(u1 - mean)*(u1 - mean);   
		else                                         //c0组与c1组像素的概率值相差不大时，运算不变
			fVaria = w0*w1*(u0 - u1)*(u0 - u1);
		if (fVaria>fMaxVaria)
		{
			fMaxVaria = fVaria;
			nBestT = nT;
		}
	}
	for (j = 0; j<m_imgHeightOut; j++)
		for (i = 0; i<m_imgWidthOut; i++)
		{
			if (m_pImgData[j*lineByte + i]<nBestT)
				m_pImgDataOut[j*lineByte + i] = 0;
			else
				m_pImgDataOut[j*lineByte + i] = 255;
		}
}