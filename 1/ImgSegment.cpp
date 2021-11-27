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
void ImgSegment::Roberts()           //Roberts��Ե���
{
	if(m_pImgDataOut!=NULL)         //�ͷ�m_pImgDataOutָ���ͼ�����ݿռ�
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
	int x, y, t;//�м����
	for(i=1;i<m_imgHeight-1;i++)//Roberts����
	{
		for(j=1;j<m_imgWidth-1;j++)
		{
			for(k=0;k<pixelByte;k++)
			{
				x=*(m_pImgData+i*lineByte+j*pixelByte+k)-*(m_pImgData+(i+1)*lineByte+j*pixelByte+k);//x�����ݶ�
				y=*(m_pImgData+i*lineByte+j*pixelByte+k)-*(m_pImgData+i*lineByte+(j+1)*pixelByte+k);//y�����ݶ�
				t=sqrt(double((x*x+y*y)+0.5));
				if(t>255)
					t=255;
				*(m_pImgDataOut+i*lineByte+j*pixelByte+k)=t;
			}
		}
	}
}
void ImgSegment::Sobel()              //Sobel��Ե���
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
				
				x= *(m_pImgData+(i-1)*lineByte+(j+1)*pixelByte+k)+ 2 * *(m_pImgData+i*lineByte+(j+1)*pixelByte+k)//x�����ݶ�
				 + *(m_pImgData+(i+1)*lineByte+(j+1)*pixelByte+k) - *(m_pImgData+(i-1)*lineByte+(j-1)*pixelByte+k)
				 - 2 * *(m_pImgData+i*lineByte+(j-1)*pixelByte+k) - *(m_pImgData+(i+1)*lineByte+(j-1)*pixelByte+k);
				y= *(m_pImgData+(i-1)*lineByte+(j-1)*pixelByte+k) + 2 * *(m_pImgData+(i-1)*lineByte+j*pixelByte+k)//y�����ݶ�
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
void ImgSegment::Prewitt()           //Prewitt��Ե���
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
				
				x= *(m_pImgData+(i-1)*lineByte+(j+1)*pixelByte+k) + *(m_pImgData+i*lineByte+(j+1)*pixelByte+k) //x�����ݶ�
					+ *(m_pImgData+(i+1)*lineByte+(j+1)*pixelByte+k) - *(m_pImgData+(i-1)*lineByte+(j-1)*pixelByte+k)
					- *(m_pImgData+i*lineByte+(j-1)*pixelByte+k) - *(m_pImgData+(i+1)*lineByte+(j-1)*pixelByte+k);
				y= *(m_pImgData+(i-1)*lineByte+(j-1)*pixelByte+k) + *(m_pImgData+(i-1)*lineByte+j*pixelByte+k)//y�����ݶ�
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
void ImgSegment::Laplacian()       //Laplacian��Ե���
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
void ImgSegment::EdgeTrace()                //Ŀ��ı߽����
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
	//˳ʱ�붨���������ص��8�������꣬��һ��Ϊx�����ƫ��,�ڶ���Ϊy�����ƫ��
	int direction[8][2] = { { -1,1 },{ 0,1 },{ 1,1 },{ 1,0 },{ 1,-1 },{ 0,-1 },{ -1,-1 },{ -1,0 } };
	CPoint startP, currentP, neighborP;                                    //�߽���ʼ��,������ĵ�ǰ��,��ǰ��������
	int findStartPoint;                                                    //�Ƿ�ǰ������ʼ�߽���غϵı�־����
	findStartPoint = 0;                                                    //�����߽���ʼ��
	int i, j;
	for (i = 0; i<m_imgHeight; i++) 
	{
		for (j = 0; j<m_imgWidth; j++) 
		{
			if (*(m_pImgData + i*lineByte + j) == 0)                      //�ҵ���ʼ�߽��
			{
				startP.x = j;
				startP.y = i;
				*(m_pImgDataOut + i*lineByte + j) = 0;
				findStartPoint = 1;
				break;
			}
		}
		if (findStartPoint)                                              //�Ѿ��ҵ���ʼ�߽��
			break;
	}
	currentP.x = startP.x;
	currentP.y = startP.y;
	int isContourP;                                                     //������Ƿ�߽���־����
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
				startDirect -= 2;                                         //ɨ�跽����ʱ����ת90��
				if (startDirect<0)
					startDirect += 8;
			}
			else 
			{                                                           //ɨ�跽��˳ʱ����ת45��
				startDirect++;
				if (startDirect == 8)
					startDirect = 0;
			}
		}
	}
}
void ImgSegment::RegionGrow(CPoint SeedPos, int thresh)                   //��������
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
	//��ά����direction�����������ص�8����������õ���x��y�����ϵ�ƫ��
	int direction[8][2] = { { 0,1 },{ 1,1 },{ 1,0 },{ 1,-1 },{ 0,-1 },{ -1,-1 },{ -1,0 },{ -1,1 } };
	CPoint *stack = new CPoint[m_imgWidth*m_imgHeight];                   //ջ���룬�˴��ٶ���ջ���������Ϊͼ����������
	int top;                                                              //ջ��ָ��
	CPoint currentPoint, popPoint;                                        //��ǰ������ĵ�͵����ĵ�
	int k;  
	int label;                                                            //��Ǳ���
	int temp1, temp2;
	temp1 = *(m_pImgData + SeedPos.y*lineByte + SeedPos.x);                //��¼�������صĻҶ�ֵ
	*(m_pImgDataOut + SeedPos.y*lineByte + SeedPos.x) = 0;                  //���������ӵ��ñ��0,��ջ
	top = 0;
	stack[top].x = SeedPos.x;
	stack[top].y = SeedPos.y;
	while (top>-1) 
	{
		popPoint.x = stack[top].x;                                          //����ջ��Ԫ��,��Ԫ���Ѿ�������
		popPoint.y = stack[top].y;
		top--;
		for (k = 0; k < 8; k++)
		{
			currentPoint.x = popPoint.x + direction[k][0];
			currentPoint.y = popPoint.y + direction[k][1];
			if (currentPoint.x<0 || currentPoint.x>m_imgWidth - 1 || currentPoint.y<0 || currentPoint.y>m_imgHeight - 1)
				continue;
			label = *(m_pImgDataOut + currentPoint.y*lineByte + currentPoint.x);
			if (label == 255)                                                //�����ĵ���Χ����û�����ĵ�
			{
				temp2 = *(m_pImgData + currentPoint.y*lineByte + currentPoint.x);
				if (abs(temp1 - temp2) < thresh)                                  //�����ǰ����������ػҶ�ֵ�����ӵ�Ҷ�ֵ֮��С�ڸ�������ֵ,����Ϊ����,�����ջ����
				{
					*(m_pImgDataOut + currentPoint.y*lineByte + currentPoint.x) = 0;    //���õ����������0
					top++;
					stack[top].x = currentPoint.x;
					stack[top].y = currentPoint.y;
				}
			}
		}
	}
	delete[]stack;
}
void ImgSegment::AdThreshSeg(unsigned char *pImgData)           //��������Ӧ��ֵ�ָ�
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
	int nLocalThresh[2][2] ;// �ֲ���ֵ
	int nLocAvg =0;// ��ͼ���ƽ��ֵ
	for(j=0; j<m_imgHeight ; j++ )
	{
		for(i=0; i<m_imgWidth ; i++ )
		{
			nLocAvg += pImgData[j*lineByte + i];
		}
	}
	nLocAvg /= ( (m_imgHeight) * (m_imgWidth) ) ;// �����ֵ
	nLocalThresh[0][0] = nLocAvg ;// ������ֵΪ��ͼ���ƽ��ֵ
	for(j=0; j<m_imgHeight ; j++ )     // ������ͼ�����ɨ����зָ
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

void ImgSegment::AdaptThreshSeg(unsigned char *pImgData)     //�ֲ�����Ӧ��ֵ�ָ�
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
	int nLocalThresh[2][2] ;  // �ֲ���ֵ
	int nLocAvg =0;     // ��ͼ���ƽ��ֵ
	for(j=0; j<m_imgHeight/2 ; j++ )  // ������ͼ�����ɨ�裺
	{
		for(i=0; i<m_imgWidth/2 ; i++ )
		{
			nLocAvg += pImgData[j*lineByte + i];
		}
	}
	nLocAvg /= ( (m_imgHeight/2) * (m_imgWidth/2) ) ;     // �����ֵ
	nLocalThresh[0][0] = nLocAvg ;                        // ������ֵΪ��ͼ���ƽ��ֵ
	for(j=0; j<m_imgHeight/2 ; j++ )                      // ������ͼ�����ɨ����зָ�
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
	for(j=m_imgHeight/2; j<m_imgHeight ; j++ )            // ������ͼ�����ɨ��
	{
		for(i=0; i<m_imgWidth/2 ; i++ )
		{
			nLocAvg += pImgData[j*lineByte + i];
		}
	}
	nLocAvg /= ( (m_imgHeight - m_imgHeight/2) * (m_imgWidth/2) ) ;
	nLocalThresh[1][0] = nLocAvg ;                       // ������ֵΪ��ͼ���ƽ��ֵ
	for(j=m_imgHeight/2; j<m_imgHeight ; j++ )           // ������ͼ�����ɨ����зָ�
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
	for(j=0; j<m_imgHeight/2 ; j++ )                     // ������ͼ�����ɨ��
	{
		for(i=m_imgWidth/2; i<m_imgWidth ; i++ )
		{
			nLocAvg += pImgData[j*lineByte + i];
		}
	}
	nLocAvg /= ( (m_imgHeight/2) * (m_imgWidth - m_imgWidth/2) ) ;
	nLocalThresh[0][1] = nLocAvg ;
	for(j=0; j<m_imgHeight/2 ; j++ )                    // ������ͼ�����ɨ����зָ�
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
	for(j=m_imgHeight/2; j<m_imgHeight ; j++ )             // ������ͼ�����ɨ��
	{
		for(i=m_imgWidth/2; i<m_imgWidth ; i++ )
		{
			nLocAvg +=pImgData[j*lineByte + i];
		}
	}
	nLocAvg /= ( (m_imgHeight - m_imgHeight/2) * (m_imgWidth - m_imgWidth/2) ) ;
	nLocalThresh[1][1] = nLocAvg ;
	for (j = m_imgHeight / 2; j < m_imgHeight; j++)            // ������ͼ�����ɨ����зָ�
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
	int nGrayHistogram[256];//�Ҷ�ֱ��ͼ����
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
	float u0,u1;          //c0  c1��ľ�ֵ
	float w0,w1;          //c0   c1��ĸ���
	int nCount0;           //c0�����������
	int nT,nBestT;          //��ֵ�������ֵ����Ӧ�������ʱ����ֵ��
	float fVaria,fMaxVaria=0;//�������󷽲�
	int nSum=0;//ͳ��ֱ��ͼ�����ص����������������nSum ��
	for(i=0;i<256;i++)
		nSum+=nGrayHistogram[i];
	for(nT=0;nT<255;nT++)                    //����ֵnT��0������255
	{
		u0=0;
		nCount0=0;
		for(i=0;i<=nT;i++)
		{
			u0+=i*nGrayHistogram[i];
			nCount0+=nGrayHistogram[i];
		}
		u0/=nCount0;
		w0=(float)nCount0/nSum;             //��ֵΪnTʱ������c0��ľ�ֵ�͸���
		u1=0;
		for(i=nT+1;i<256;i++)
			u1+=i*nGrayHistogram[i];
		u1 /=(nSum-nCount0);
		w1=1-w0;                          //����ֵΪnTʱ������c1��ľ�ֵ�͸���
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
	int nGrayHistogram[256];//�Ҷ�ֱ��ͼ����
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
	float u0, u1;          //c0  c1��ľ�ֵ
	float w0, w1;          //c0   c1��ĸ���
	int nCount0;           //c0�����������
	int nT, nBestT;          //��ֵ�������ֵ����Ӧ�������ʱ����ֵ��
	float fVaria, fMaxVaria = 0;//�������󷽲�
	int nSum = 0;//ͳ��ֱ��ͼ�����ص����������������nSum ��
	for (i = 0; i<256; i++)
		nSum += nGrayHistogram[i];
	for (nT = 0; nT<255; nT++)         //����ֵnT��0������255
	{
		u0 = 0;
		nCount0 = 0;
		for (i = 0; i <= nT; i++)
		{
			u0 += i*nGrayHistogram[i];
			nCount0 += nGrayHistogram[i];
		}
		u0 /= nCount0;
		w0 = (float)nCount0 / nSum;        //��ֵΪnTʱ������c0��ľ�ֵ�͸���
		u1 = 0;
		for (i = nT + 1; i<256; i++) 
			u1 += i*nGrayHistogram[i];
		u1 /= (nSum - nCount0);
		w1 = 1 - w0;                       //����ֵΪnTʱ������c1��ľ�ֵ�͸���
		int mean = u0*w0 + u1*w1;
		if(w0>(5*w1)||w0<(5*w1))                     //c0����c1�����صĸ���ֵ���ⳬ��5��ʱ������������
			fVaria = pow(w0, float(0.85))*(u0 - mean)*(u0 - mean) + pow(w1, float(0.85))*(u1 - mean)*(u1 - mean);   
		else                                         //c0����c1�����صĸ���ֵ����ʱ�����㲻��
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