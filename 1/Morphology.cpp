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
	m_pImgDataOut=NULL;//���ͼ��λͼ����ָ��Ϊ��
	m_lpColorTableOut=NULL;//���ͼ����ɫ��ָ��Ϊ��
    m_nBitCountOut=0;//���ͼ��ÿ����λ��Ϊ0	
	m_imgWidthOut=0;//���ͼ��Ŀ�Ϊ0
	m_imgHeightOut=0;//���ͼ��ĸ�Ϊ0
	m_TempBuf=NULL;//�ṹԪ��ָ��Ϊ��
	TempH=3;   //�ṹԪ�ظ�
	TempW=3;   //�ṹԪ�ؿ�
    int i;
	for (i=0;i<TempH*TempW;i++)
		m_InitTemp[i]=0;
}
Morphology::Morphology(CSize size, int nBitCount, LPRGBQUAD lpColorTable,unsigned char *pImgData):
            ImageDib(size, nBitCount, lpColorTable, pImgData)
{
    m_nBitCountOut=m_nBitCount;
	m_lpColorTableOut=NULL;	//���ͼ����ɫ����
	int colorTableLength=ComputeColorTabalLength(m_nBitCountOut);
	if(colorTableLength!=0)
	{
      m_lpColorTableOut=new RGBQUAD[colorTableLength];
	  memcpy(m_lpColorTableOut,m_lpColorTable,sizeof(RGBQUAD)*colorTableLength);
	}
	m_imgWidthOut=m_imgWidth;
	m_imgHeightOut=m_imgHeight;
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;
	m_pImgDataOut=new unsigned char[lineByte*m_imgHeight];//�������ͼ������Ҫ�Ļ�����
	m_TempBuf=NULL;//�ṹԪ��ָ��Ϊ��
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
void Morphology::ImgErosion(unsigned char *imgBufIn,unsigned char *imgBufOut,int imgWidth,        //��ֵ��ʴ��������
							  int imgHeight,int *TempBuf, int TempW, int TempH) 			
{
	int lineByte=(imgWidth+3)/4*4;	
	memcpy(imgBufOut,imgBufIn,lineByte*imgHeight);	//������ͼ�񻺳����Ŀ��������ͼ�񻺳���
	int i,j,k,l;
	int flag;	                                   //��־����
	for(i=TempH/2;i<imgHeight-TempH/2;i++)        //���ͼ����ÿһ������λ�ã��ж��Ƿ�ṹԪ��������Ŀ���ڲ�
	{
		for(j=TempW/2;j<imgWidth-TempW/2;j++)
		{			
			flag=1;                              //�жϽṹԪ���Ƿ�����ڵ�ǰ������Ŀ���ڲ�,1Ϊ����,0Ϊ������
			for(k=-TempH/2;k<=TempH/2;k++)
			{
				for(l=-TempW/2;l<=TempW/2;l++)
				{
					if(TempBuf[(k+TempH/2)*TempW+l+TempW/2])           //�����ǰ�ṹԪ��λ��Ϊ1,�ж����Ӧͼ���ϵ����ص��Ƿ�Ϊ��0
					{
						if(!*(imgBufIn+(i+k)*lineByte+j+l))//���ͼ��ǰ����Ϊ0,��û�л��иõ�,���Ǹ�ʴ�����
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
void Morphology::InputMask(int *mask,int maskW, int maskH)           //�ṹԪ�����뺯�����ڵ�����������ǰ�����ȵ��ô˺���
{
	if(m_TempBuf)
	{
		delete []m_TempBuf;
		m_TempBuf=NULL;
	}
	m_TempBuf=new int[maskW*maskH];                                //������ĽṹԪ�ؿ�����m_maskBuf��������
	int i, j;
	for(i=0;i<maskH;i++)
	{
		for(j=0;j<maskW;j++)
			m_TempBuf[i*maskW+j]=mask[i*maskW+j];
	}
	TempW=maskW;                                                     //Ϊ�ṹԪ�ؿ�͸߸�ֵ
	TempH=maskH;
}
void Morphology::ImgDilation(unsigned char *imgBufIn,unsigned char *imgBufOut,int imgWidth,int imgHeight, //��ֵ���ͻ�������
					 int *TempBuf, int TempW, int TempH)
{
	int lineByte=(imgWidth+3)/4*4;
	memcpy(imgBufOut,imgBufIn,lineByte*imgHeight);
	int i,j,k,l;
	for(i=0;i<imgHeight;i++)                         //�����Ƕ�ͼ����Ŀ�겹���ĸ�ʴ�������������ͼ�����ݵĲ���
	{
		for(j=0;j<imgWidth;j++)
		{
			k=*(imgBufIn+i*lineByte+j);
			*(imgBufIn+i*lineByte+j)=255-*(imgBufIn+i*lineByte+j);
		}
	}
	int *tempMask=new int[TempW*TempH];//�����ǽṹԪ�صĶԳƼ��Բ����ĸ�ʴ,�˴�tempMask���m_mask�ĶԳƼ�
	for(k=0;k<TempH;k++)
	{
		for(l=0;l<TempW;l++)
			tempMask[k*TempW+l]=TempBuf[(TempH-1-k)*TempW+TempW-1-l];
	}
	int flag;	//��־����
	for(i=TempH/2;i<imgHeight-TempH/2;i++)
	{
		for(j=TempW/2;j<imgWidth-TempW/2;j++)
		{			
			flag=1;              //�жϽṹԪ���Ƿ�����ڵ�ǰ������Ŀ���ڲ�,1Ϊ����,0Ϊ������
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
	for(i=0;i<imgHeight;i++)                     //�ýṹԪ�ضԳƼ���Ŀ�겹����ʴ��,��Ҫ�Խ������һ�β���,�������ͽ�����
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
void Morphology::Open()                //��ֵ������
{
	if(m_TempBuf==NULL)
    	return;
	int lineByte=(m_imgWidth+3)/4*4;
	unsigned char *buf=new unsigned char[lineByte*m_imgHeight];//�м�������������,������Ÿ�ʴ����м���
	ImgErosion(m_pImgData, buf,m_imgWidth,m_imgHeight,m_TempBuf, TempW, TempH);	//�ȸ�ʴ
	ImgDilation(buf, m_pImgDataOut,m_imgWidth,m_imgHeight,m_TempBuf, TempW, TempH);	//������
	delete []buf;	//�ͷŻ�����
}
void Morphology::Close()                       //��ֵ������
{
	if(m_TempBuf==NULL)
		return;
	int lineByte=(m_imgWidth+3)/4*4;
	unsigned char *buf=new unsigned char[lineByte*m_imgHeight];
	ImgDilation(m_pImgData, buf,m_imgWidth,m_imgHeight,m_TempBuf, TempW, TempH);         //������
	ImgErosion(buf, m_pImgDataOut,m_imgWidth,m_imgHeight,m_TempBuf, TempW, TempH);        //��ʴ
	delete []buf;
}
void Morphology::DefineElementPair()               //Ϊ���л����б任�ĽṹԪ�ض�m_hitMissMask��ֵ����8��
{
	int i, k, l;//����8������Ļ��л����б任�ṹԪ�ض�
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
void Morphology::HitAndMiss(unsigned char *imgBufIn, unsigned char *imgBufOut,int imgWidth,int imgHeight, ElementPair hitMissMask)	//���л����б任				 
{
	int i, j;
	int validateFlag=1;         //��־������1��ʾ�ṹԪ�ض���Ч��0��ʾ��Ч
	for(i=0; i<3;i++)        //���ṹԪ�ض��Ƿ񽻼�Ϊ��,��������Ϊ����Ϊ��Ч�ṹԪ�ض�,�㷨���˳�
	{
		for(j=0;j<3;j++)
			if(hitMissMask.hitElement[i*3+j]&&hitMissMask.missElement[i*3+j])
			{
				validateFlag=0;
				break;
			}
	}
	if(validateFlag==0)                 //�Ƿ��ṹԪ�ض�,����
		return;
	int lineByte=(imgWidth+3)/4*4;
	memset(imgBufOut, 0, lineByte*imgHeight);
	int k,l;
	int hitFlag, missFlag;            //���б�־�����ͻ����б�־����
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
					if(hitMissMask.hitElement[(k+1)*3+l+1]==1)         //������нṹԪ�ص�ǰλ��Ϊ1
					{
						if(*(imgBufIn+(i+k)*lineByte+j+l))             //�ж�ͼ���Ӧ���Ƿ�Ϊ0,�����,��û�л���ͼ��ǰ��
							hitFlag=0;
					}
					if(hitMissMask.missElement[(k+1)*3+l+1]==1)        //��������нṹԪ�ص�ǰλ��Ϊ1
					{
						if(!*(imgBufIn+(i+k)*lineByte+j+l))            //�ж�ͼ���Ӧ���Ƿ�Ϊ0,�����,��û�л���ͼ��ǰ��
							missFlag=0;
					}
				}
			}
			if(hitFlag&&missFlag)
				*(imgBufOut+i*lineByte+j)=255;
		}
	}
}
void Morphology::ImgThinning()            //�û��л����б任������ͼ�����ϸ��
{
	DefineElementPair();//����8������ĽṹԪ�ض�
	int lineByte=(m_imgWidth+3)/4*4;
	unsigned char *buf=new unsigned char[lineByte*m_imgHeight];
	memcpy(buf, m_pImgData, lineByte*m_imgHeight);
	int i, k, l,m;
	for(m=0;m<4;m++)
	{
		for(i=0;i<12;i++)//��8������ĽṹԪ�ضԶ���ͼ����һ�λ��л����б任,������������ԭͼ��ȥ��
		{
			HitAndMiss(buf, m_pImgDataOut, m_imgWidth, m_imgHeight,m_hitMissMask[i]);
			for(k=0;k<m_imgHeight;k++)//�����л����б任����������ԭ������ȥ��
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
	LPBYTE m_lpImgBits = m_pImgData;                         //ͼ����������ָ��
	LPBYTE m_lpImgBitsMove;                                  //���������ƶ�ָ��
	int *m_lpnMark;                                          //�������ָ��
	m_lpnMark = NULL;
	int	*m_lpnMarkMove;                                     //��������ƶ�ָ��
	int m_nMarkNumbers;                                     //��ǵ��������		    
	if (m_lpnMark == NULL)                  //����������ռ䣬�ǵ�Ҫ��CImage��Ĺ��캯���н� m_lpnMark��ʼ��ΪNULL
	{
		m_lpnMark = new int[m_imgBitsCount];
		ASSERT(m_lpnMark != NULL);
		m_lpnMarkMove = m_lpnMark;
	}
	;; memset((LPBYTE)m_lpnMark, 0, m_imgBitsCount * 4);
	int nMarkValue = 1;                          //ÿ�α�ʶ��ֵ��nMarkValue���ں�ߵ���������ʾ��ͬ�����򣬴�1��ʼ���
	int nMaxMarkValue = 0;	                   //��¼���ı�ʶ��ֵ
	int i, j;
	CList<EqualMark, EqualMark>lEqualMark;
	m_lpImgBitsMove = m_lpImgBits;
	int nEqualNum = 0;
	EqualMark tempEqualMark;                   //������ʱ���ÿ���ҵ��ĵȼ۹�ϵ
	m_lpnMarkMove = m_lpnMark;
	m_lpImgBitsMove = m_lpImgBits;
	if (*m_lpImgBitsMove == 255)
		*m_lpnMarkMove = nMarkValue++;
	m_lpnMarkMove++;
	m_lpImgBitsMove++;
	for (i = 1; i <= m_imgWidth; i++)                //���ͼ��ĵ�һ�У���ʱ������ֵȼ۵����
	{
		if (*m_lpImgBitsMove == 255)                 //��Ҫ��ǵ����
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
			if (*(m_lpnMarkMove - m_imgWidthBytes) != 0)//<��>λ�ñ���ǹ�
			{
				*m_lpnMarkMove = *(m_lpnMarkMove - m_imgWidthBytes);
				if (*(m_lpnMarkMove - m_imgWidthBytes) != *(m_lpnMarkMove - m_imgWidthBytes + 1) && *(m_lpnMarkMove - m_imgWidthBytes + 1) != 0)
				{
					AttachEqualMark(tempEqualMark, *(m_lpnMarkMove - m_imgWidthBytes),
						*(m_lpnMarkMove - m_imgWidthBytes + 1), nEqualNum, lEqualMark);//<��><����>�ȼ۱��
				}
			}
			else
			{
				if (*(m_lpnMarkMove - m_imgWidthBytes + 1) != 0)
					*m_lpnMarkMove = *(m_lpnMarkMove - m_imgWidthBytes + 1);   //����<����>���
				else              //<��>��<����>��û�б�ǣ���ʼ�µı��
					*m_lpnMarkMove = nMarkValue++;
			}
		}
		m_lpnMarkMove++;
		m_lpImgBitsMove++;
		for (i = 1; i <= m_imgWidth - 1; i++)           //��ÿ�е��м������Ǵ�����ʱ����<��>��<����>��<��>��<����> 4�����
		{
			if ((*m_lpImgBitsMove) == 255)
			{
				if (*(m_lpnMarkMove - 1) != 0)
				{
					*m_lpnMarkMove = *(m_lpnMarkMove - 1);          //����<��>
					if (*(m_lpnMarkMove - 1) != *(m_lpnMarkMove - m_imgWidthBytes - 1) && *(m_lpnMarkMove - m_imgWidthBytes - 1) != 0)
						AttachEqualMark(tempEqualMark, *(m_lpnMarkMove - 1),*(m_lpnMarkMove - m_imgWidthBytes - 1), nEqualNum, lEqualMark);//���<��>��<����>�ȼ�
					if (*(m_lpnMarkMove - 1) != *(m_lpnMarkMove - m_imgWidthBytes) && *(m_lpnMarkMove - m_imgWidthBytes) != 0)
						AttachEqualMark(tempEqualMark, *(m_lpnMarkMove - 1),*(m_lpnMarkMove - m_imgWidthBytes), nEqualNum, lEqualMark);//���<��>��<��>�ȼ�
					if (*(m_lpnMarkMove - 1) != *(m_lpnMarkMove - m_imgWidthBytes + 1) && *(m_lpnMarkMove - m_imgWidthBytes + 1) != 0)
						AttachEqualMark(tempEqualMark, *(m_lpnMarkMove - 1),*(m_lpnMarkMove - m_imgWidthBytes + 1), nEqualNum, lEqualMark);//���<��>��<����>�ȼ�
				}
				else//<��>δ����ǹ�
				{
					if (*(m_lpnMarkMove - m_imgWidthBytes - 1) != 0)                   //<����>����ǹ�
					{
						*m_lpnMarkMove = *(m_lpnMarkMove - m_imgWidthBytes - 1);
						if (*(m_lpnMarkMove - m_imgWidthBytes - 1) != *(m_lpnMarkMove - m_imgWidthBytes) && *(m_lpnMarkMove - m_imgWidthBytes) != 0)	
							AttachEqualMark(tempEqualMark, *(m_lpnMarkMove - m_imgWidthBytes - 1),
								*(m_lpnMarkMove - m_imgWidthBytes), nEqualNum, lEqualMark);              //���<����>��<��>�ȼ�
						if (*(m_lpnMarkMove - m_imgWidthBytes - 1) != *(m_lpnMarkMove - m_imgWidthBytes + 1) && *(m_lpnMarkMove - m_imgWidthBytes + 1) != 0)
							AttachEqualMark(tempEqualMark, *(m_lpnMarkMove - m_imgWidthBytes - 1),
								*(m_lpnMarkMove - m_imgWidthBytes + 1), nEqualNum, lEqualMark);//���<����>��<����>�ȼ�
					}
					else                               //<��>��<����>δ��ǹ�
					{
						if (*(m_lpnMarkMove - m_imgWidthBytes) != 0)
						{
							*m_lpnMarkMove = *(m_lpnMarkMove - m_imgWidthBytes);        	//����<��>���
							if (*(m_lpnMarkMove - m_imgWidthBytes) != *(m_lpnMarkMove - m_imgWidthBytes + 1) && *(m_lpnMarkMove - m_imgWidthBytes + 1) != 0)
								AttachEqualMark(tempEqualMark, *(m_lpnMarkMove - m_imgWidthBytes),
									*(m_lpnMarkMove - m_imgWidthBytes + 1), nEqualNum, lEqualMark);//���<��>��<����>�ȼ�
						}
						else                        //<��>��<����>��<��>δ��ǹ�����ʱ�����ڵȼ۹�ϵ
						{
							if (*(m_lpnMarkMove - m_imgWidthBytes + 1) != 0)
								*m_lpnMarkMove = *(m_lpnMarkMove - m_imgWidthBytes + 1);    	//����<����>���
							else                //<��>��<����>��<��>��<����>δ��ǹ�����ʼ�µı��ֵ
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
			if (*(m_lpnMarkMove - 1) != 0)                        //<��>����ǹ�
			{
				*m_lpnMarkMove = *(m_lpnMarkMove - 1);
				if (*(m_lpnMarkMove - 1) != *(m_lpnMarkMove - m_imgWidthBytes - 1) && *(m_lpnMarkMove - m_imgWidthBytes - 1) != 0)
					AttachEqualMark(tempEqualMark, *(m_lpnMarkMove - 1),
						*(m_lpnMarkMove - m_imgWidthBytes - 1), nEqualNum, lEqualMark);              //���<��>��<����>�ȼ�
				if (*(m_lpnMarkMove - 1) != *(m_lpnMarkMove - m_imgWidthBytes) && *(m_lpnMarkMove - m_imgWidthBytes) != 0)
					AttachEqualMark(tempEqualMark, *(m_lpnMarkMove - 1),
						*(m_lpnMarkMove - m_imgWidthBytes), nEqualNum, lEqualMark);                   //���<��>��<��>�ȼ�
			}
			else                  //<��>δ����ǹ�
			{
				if (*(m_lpnMarkMove - m_imgWidthBytes - 1) != 0)
				{
					*m_lpnMarkMove = *(m_lpnMarkMove - m_imgWidthBytes - 1);    //����<����>
					if (*(m_lpnMarkMove - m_imgWidthBytes - 1) != *(m_lpnMarkMove - m_imgWidthBytes) && *(m_lpnMarkMove - m_imgWidthBytes) != 0)
						AttachEqualMark(tempEqualMark, *(m_lpnMarkMove - m_imgWidthBytes - 1),
							*(m_lpnMarkMove - m_imgWidthBytes), nEqualNum, lEqualMark);//���<����>��<��>�ȼ�
				}
				else//<��>��<����>δ��ǹ�
				{
					if (*(m_lpnMarkMove - m_imgWidthBytes) != 0)
						*m_lpnMarkMove = *(m_lpnMarkMove - m_imgWidthBytes);   	//����<��>���
					else//<��>��<����>��<��>δ��ǹ�,��ʼ�µı��ֵ
						*m_lpnMarkMove = nMarkValue++;
				}
			}
		}  
	}  
	nMaxMarkValue = nMarkValue - 1;	
	CPtrList exList;         //����˫������������������Ԫ����һ��ָ���ڲ������ָ���ڲ�������ͱ�Ҳ��CptrList����Ԫ���Ǳ��ֵ
	CPtrList *plnnerList;
	POSITION posExElem;
	if (lEqualMark.GetCount() != 0)
	{
		CPtrList* plnnerListAdd = new CPtrList;//pInnerListAdd��ÿ����exList����ӵ���Ԫ��
		ASSERT(plnnerListAdd != NULL);
		plnnerListAdd->AddTail((void*)lEqualMark.GetHead().MarkValue1);
		plnnerListAdd->AddTail((void*)lEqualMark.GetHead().MarkValue2);
		exList.AddTail((void*)plnnerListAdd);
		lEqualMark.RemoveHead();
		CPtrList* pFindValue1 = NULL;//����pFindVaIuel��pFindVaIue2������������ڲ��������ҵ���
		CPtrList* pFindValue2 = NULL;//��ֵ��ĳ���ڲ������ͷָ�룬Ҳ������������ĳ��Ԫ��ֵ
		while (!lEqualMark.IsEmpty())//����ʣ��ĵȼ۶�
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
			if (pFindValue1&&pFindValue2)              //�õȼ۶�������ֵ�����Ѿ�������ĵȼ۹�ϵ��
			{
				if (pFindValue1 != pFindValue2)           //��������ַ��һ��ʱ����������е���
				{
					pFindValue1->AddTail(pFindValue2);
					POSITION posDelete = exList.Find((void*)pFindValue2);
					pFindValue2->RemoveAll();
					delete pFindValue2;
					exList.RemoveAt(posDelete);
				}
			}
			else if (pFindValue1)             //8ֻ���Ѿ�������ĵȼ۹�ϵ���ҵ�Vafuel����ô��value2�ӵ�Valuel���ڵ�������
				pFindValue1->AddTail((void*)lEqualMark.GetHead().MarkValue2);
			else if (pFindValue2)
				pFindValue2->AddTail((void*)lEqualMark.GetHead().MarkValue1);
			else                     //�ȼ۶�������ֵ��������ĵȼ۹�ϵ�ж�û���ҵ�������exList��������Ԫ��
			{
				CPtrList* plnnerListAdd = new CPtrList;
				plnnerListAdd->AddTail((void*)lEqualMark.GetHead().MarkValue1);
				plnnerListAdd->AddTail((void*)lEqualMark.GetHead().MarkValue2);
				exList.AddTail((void*)plnnerListAdd);
			}
			lEqualMark.RemoveHead();           //ȥ����ʱ�ȼ۶Ե�ͷԪ��
		}
	}
	else
	{

	}
	int nTotalEqualNum = 0;               //����ȼ۹�ϵ�ı�Ǹ���
	int nMarkRegion = 0;                 //ͼ������ͨ�������
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
	for (i = 0; i<nMaxMarkValue; i++)               //��ʼ��ӳ������������������ӳ��
	{
		vMarkMap[i].nOriginalMark = i + 1;
		vMarkMap[i].nMappingMark = i + 1;
	}
	POSITION poslnneElem;                           //lnnerLjst��Ԫ�ص�λ��
	int nMin;                                     //1nnerList����Сֵ
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
		poslnneElem = plnnerList->GetHeadPosition();//����ÿ��ȼ۹�ϵ�е���С�ı��ֵ��Mapping��������������
		while (poslnneElem)
		{
			nIndex = (int)plnnerList->GetAt(poslnneElem) - 1;
			vMarkMap[nIndex].nMappingMark = nMin;
			plnnerList->GetNext(poslnneElem);
		}
		exList.GetNext(posExElem);
	}
	vector<int>vSortMark(nMarkRegion);                    //��������
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
		if (count[k] < MAXAreas)                  //���˳��������С��ͼ��������������1/10������
		{
			for (i = 1; i < m_imgHeight - 1; i++)
				for (j = 1; j < m_imgWidth - 1; j++)
					if (*(m_lpnMark + i*m_imgWidthBytes + j) == k)
						*(m_pImgData + i*m_imgWidthBytes + j) = 0;
		}
		else if (C[k] < 0.70)                           //���˳�ͼ��������Բ�ζ�С��0.75��������������
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
	for (i = 0; i<m_imgHeight; i++)                        //����������ʾ����
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
	if (num1 < num2)//num1С�����
	{
		if (pEqualMark.MarkValue1 != num1 || pEqualMark.MarkValue2 != num2)
		{
			pEqualMark.MarkValue1 = num1;
			pEqualMark.MarkValue2 = num2;
			pEqualNum++;
			plEqualMark.AddTail(pEqualMark);
		}
	}
	else                           //num2С�����
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
