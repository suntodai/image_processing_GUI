//   MBSIZE : ��E���Ĵ�С
//   P : ������������

#define MBSIZE 16
#define P 9
#include "motionES.h"
#include <cmath>
#include "string.h"
//#include <stdafx.h>

const struct Point{int x;int y;};
const Point LDSP[9]={{0,-2},{-1,-1},{1,-1},{-2,0},{0,0},{2,0},{-1,1},{1,1},{0,2}};
const Point SDSP[5]={{0,-1},{-1,0},{0,0},{1,0},{0,1}};

//********************************************************************************************
// TSS�㷨����PԽ����������Խ�󣬼�����Խ��MBSIZE�����������˶�ʸ���٣�������С��Ч������
//
// ��ȁE
//   imgI : �ο�ͼρE
//   imgP : ҪѰ���˶�ʸ����ͼρE
//   imgComp : ������ͼ�����������ָՁE
//   imgWidth : ͼ��Ŀ���
//   imgHeight: ͼ��Ŀ���
// �䳁E
//   motionvector: ͼ����Ƶ��˶�ʸ����ՁE
//   TSScomputations: TSS�㷨�ļ�����
//*********************************************************************************************
void motionEstTSS(unsigned char *imgP, unsigned char* imgI, int imgWidth, int imgHeight, int motionVect[2][MAX], double* TSScomputations)
{
//��ʼ������	

     double costs[3][3]={{65537,65537,65537},{65537,65537,65537},{65537,65537,65537}};
     double computations = 0;
     int L = 0; 
     int stepMax = 0;
     int vectorsNum = 0;
	 // ��������Ҫ��������
	 L= (int)floor(log10(P+1.0)/log10(2.0));  //p=7,s=4
	 stepMax = (int)pow(2.0,(L-1));
	 vectorsNum =(int)(imgWidth*imgHeight/pow((double)MBSIZE,2));
//��̬��ŁE
	 //��ʼ���˶�ʸ��Ϊ��E
     int vectors[2][MAX] ={0};//int vectors[2][vectorsNum] ;
// ��ͼ�����Ͻǿ�ʼ��˵���������ĵ������ϽǴ���ʼ
	 //����ΪMBSIZE������Ѱ�ҵ�ÿ����E�����������������p���ش���ƥŁE
     int mbCount = 1;
     int i,j;
     for( i = 0; i< imgHeight;i+=MBSIZE)//��ֹ�糁E-ͼ���ЁE�MBSIZE^2������?�ܱߵ�ģ�鲻ȥ��ˁE
	 {
        for(j = 0; j<imgWidth;j+=MBSIZE)
		{   
        //������������ÿһ������������Χ��9�����ҳ�������
            double  pVector[3]={0,0,0};//----------[dx,dy,min]
            int  x = j;//ͼ�����
            int  y = i;//ͼ�����
			int  k,t;
			int  stepSize;
        // Ϊ�˱�����������ĵķ������㣬���Ǵ洢��ǰһ�����еõ�����ֵ��
		//���ڵ�һ�ε�E������ǰѴ�ֵ��ŵ�ѭ��֮�⣬�����ĵ�E������ǰ�ֵ��ŵ��ƶ����������ĵ㴦

			//��̬�����ά��ׁE
			unsigned char** imgPtmp;
			unsigned char** imgItmp;
			imgPtmp = new unsigned char*[MBSIZE];
			imgItmp = new unsigned char*[MBSIZE];
			for (k=0;k<MBSIZE;k++)
			{		
				imgPtmp[k]=new unsigned char[MBSIZE];
			    memset(imgPtmp[k],0,MBSIZE*sizeof(unsigned char));//�½��ڴ���ǁE�E
			}

			for (k=0;k<MBSIZE;k++)
			{			
				imgItmp[k]=new unsigned char[MBSIZE];
                memset(imgItmp[k],0,MBSIZE*sizeof(unsigned char));//�½��ڴ���ǁE�E
			}

            for(int blkX=0;blkX<MBSIZE;blkX++)
			{
	    		for(int blkY=0;blkY<MBSIZE;blkY++)
				{
					int MAX1=0,MAX2=0;//���糁E
					//Ϊ�˱����糁E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!�������ϱ�Ե
					MAX1 =((i+blkY)*imgWidth+(j+blkX)<=(imgWidth*imgHeight-1))?(i+blkY)*imgWidth+(j+blkX):(imgWidth*imgHeight-1); 
                    *(imgPtmp[blkX]+blkY) = *(imgP+MAX1);
		    	    *(imgItmp[blkX]+blkY) = *(imgI+MAX1);
				}
			}
			   //     costs(2,2) = costFuncMAD(imgP(i:i+MBSIZE-1,j:j+MBSIZE-1), ...
                             //       imgI(i:i+MBSIZE-1,j:j+MBSIZE-1),MBSIZE);
			//ǿ��ת������ֵΪ����
			//ѭ��ǰ�ȼ���ο����Ĵ���ρE
            costs[1][1] = costFuncMAD(imgPtmp,imgItmp,MBSIZE);
            computations = computations + 1;
            stepSize = stepMax;               

            while(stepSize >= 1)  
			{
                int m,n;
				int dx,dy;
	     		double min;
            // m ���л��ߴ�ֱ��������
            // n ���л���ˮƽ��������
                for( m = -stepSize;m <= stepSize ; m += stepSize)
				{
                   for( n = -stepSize;n <= stepSize ; n += stepSize)
				   {
				    	int refBlkVer,refBlkHor;
				    	int costRow,costCol;
                        refBlkVer = y + m;   // �ο�����У���ֱ����E
                        refBlkHor = x + n;   // �ο���E��У�ˮƽ����E
               //         if (( refBlkVer < 1 )||( refBlkVer+MBSIZE-1 > imgHeight)|| (refBlkHor < 1 )|| (refBlkHor+MBSIZE-1)> imgWidth)
						if (( refBlkVer < 0 )||( refBlkVer+MBSIZE > imgHeight)|| (refBlkHor < 0 )|| (refBlkHor+MBSIZE)> imgWidth)
                           continue;
						//����cost�������������E����±�E
                        costRow = m/stepSize + 1;//0~2  
                        costCol = n/stepSize + 1;//0~2
						//���Ĵ�����E
                        if (costRow == 1 && costCol == 1)
                           continue;
				        for(int blkX2=0;blkX2<MBSIZE;blkX2++)
						{
	                     	for(int blkY2=0;blkY2<MBSIZE;blkY2++)
							{
							   int MAX1=0,MAX2=0;//���糁E
							//Ϊ�˱����糁E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!�������ϱ�Ե
							   MAX1 =((i+blkY2)*imgWidth+(j+blkX2)<=(imgWidth*imgHeight-1))?(i+blkY2)*imgWidth+(j+blkX2):(imgWidth*imgHeight-1); 
				               MAX2 =(((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2))<=(imgWidth*imgHeight-1))?((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2)):(imgWidth*imgHeight-1); 
                               *(imgPtmp[blkX2]+blkY2) = *(imgP+MAX1);
			                   *(imgItmp[blkX2]+blkY2) = *(imgI+MAX2);
							}
						}
                        costs[costRow][costCol] = costFuncMAD(imgPtmp,imgItmp,MBSIZE);
     //                 costs(costRow, costCol ) = costFuncMAD(imgP(i:i+MBSIZE-1,j:j+MBSIZE-1), ...
     //                   imgI(refBlkVer:refBlkVer+MBSIZE-1, refBlkHor:refBlkHor+MBSIZE-1), MBSIZE);
                        computations = computations + 1;//��������һ
				   }
				}
            
            // ���������ҵ���졿������Ҵ洢��ֵ
                minCost(costs,pVector);      // finds which macroblock in imgI gave us min Cost
                dx  = (int)(pVector[0]);//dx.dy����0~2����1~3
		     	dy  = (int)(pVector[1]);
			    min = pVector[2];
               // ��������������E�Eµ���졿�����
                x = x + (dx-1)*stepSize;
                y = y + (dy-1)*stepSize; 
            // Arohs thought: At this point we can check and see if the shifted co-ordinates are exactly the same 
			//as the root co-ordinates of the last step, then we check them against a preset threshold, 
			//and ifthe cost is less then that, than we can exit from teh loop right here. 
			//This way we can save more computations. However, as this is not implemented in the paper I am modeling, 
			//am not incorporating this test. May be later...as my own addition to the algorithm
            //  ������������E
                stepSize = stepSize / 2;
			//  �ο����ĵĿ���ֵ��E�ΪĿǰ����䴦��
                costs[1][1] = costs[dy][dx]; 
				
			}


			//�ж��Ƿ�д�糁E
			if(mbCount>vectorsNum)
				mbCount = vectorsNum;
            vectors[0][mbCount-1] = y - i;    // �˶�ʸ����������E
            vectors[1][mbCount-1] = x - j;    // �˶�ʸ����������E
			//ģ�������һ
            mbCount = mbCount + 1;
       //     costs[3][3]={{65537,65537,65537},{65537,65537,65537},{65537,65537,65537}};
			//������������ԭ---�������򵥷���ô��
			for(k=0;k<3;k++)  //memset(costs,65537,3*sizeof(int));//memset���ַ���������65537�ضϳ�01,int ռ2�ֽڣ���ɁE010101---16843009��������ԣ�����
			{
				for(t=0;t<3;t++)
					costs[k][t]=65537;
			}	 			//�ͷ��ڴ�E
     	    for (k=0;k<MBSIZE;k++)
            	delete []imgPtmp[k];
        	for (k=0;k<MBSIZE;k++)
            	delete []imgItmp[k];
	        delete []imgPtmp;
	        delete []imgItmp;
		}
	 }
 	 for(i=0;i<2;i++) 
		{
			for(j=0;j<MAX;j++)
			{
				if(j>=vectorsNum)
					motionVect[i][j]=0;
				else
				    motionVect[i][j]=vectors[i][j];
			}

		}
     *TSScomputations = computations/(mbCount - 1);    

}

//*******************************************************************************************
//   ���㲹����ͼ���PSNR
// ��ȁE
//   imgP: ԭͼ
//   imgComp:������ͼρE
//   imgHeight: ͼ��ĸ�
//   imgWidth: ͼ��Ŀ�E
//   n : ͼ�����ص����߷��ֵ
// �䳁E
//   psnr:����ͼ��ķ�ֵ��ԁE�
//******************************************************************************************
double psnr(unsigned char* imgP,unsigned char* imgComp,int imgWidth,int imgHeight,int n)
{

    double err = 0;
    double mse,psnr;
	int i,j;
    for (i=0;i<imgHeight;i++)
	{
     	for(j=0;j<imgWidth;j++)
		{
     	  err = err + pow(double(*(imgP+i*imgWidth+j) - *(imgComp+i*imgWidth+j)),2);
		}
	}

    mse = err / (imgHeight*imgWidth);
    psnr = 10*log10(n*n/mse);
    return psnr;
	
}

//****************************************************************************
// �����������ƽ��������E
// ��ȁE
// currentBlk : ����MADֵ����E
// refBlk : ����MADֵ�Ĳο���E
// �䳁E
// cost : �����MADֵ
//******************************************************************************
double costFuncMAD(unsigned char** currentBlk,unsigned char** refBlk,int mbSize)
{
	
	double err = 0;
	double cost;
	int i,j;
    for(i = 0;i<mbSize;i++)
	{
		for(j = 0;j<mbSize;j++)
		{
		  err = err + labs(*(currentBlk[i]+j) - *(refBlk[i]+j));
		}
	}
    cost = err / (mbSize*mbSize);
	return cost;
	
}

//****************************************************************************
// �ҵ���졿�����������ֵ���±�E
//
// ��ȁE
//   costs : ��E��鿪����ՁE
//         
// �䳁E
//   pVector: dx,dy,min�����졿���У�������E����ֵ
//****************************************************************************
void minCost(double costs[3][3],double pVector[] )
{
//��ʼ��
  double min = *(costs[1]+1);
  double dx=1,dy=1;
  int i,j;
  for(i =0; i< 3;i++) 
  {
	 for(j =0; j< 3;j++) 
	 {     
		 if (*(costs[i]+j) < min)
		 {
		    min = *(costs[i]+j);
            dx = j; dy = i;
		 }
	 }
  }
  pVector[0]=dx;
  pVector[1]=dy;
  pVector[2]=min;

}

//*****************************************************************************
// �����˶�����ʸ�������˶�����ͼρE
//
// ��ȁE
//   imgI : �ο�ͼρE
//   motionVect : �����˶�ʸ����ՁE
//   MBSIZE �� ��E����С
///  imgWidth : ͼ�����
//   imgHeight: ͼ��ĸ߶�
// �䳁E
//   imgComp :����ͼ������ָՁE
//*****************************************************************************
void motionComp(unsigned char* imgI,int mbSize,int imgWidth,int imgHeight,int motionVect[2][MAX],unsigned char*imgComp)
{

   int mbCount = 1;
   int i,j;
//ָʾ�Ƿ���ȁE�����MBSIZE��������
   int xExtra,yExtra;
   for(i = 0; i<imgHeight; i+= mbSize) //�˶�����ͼ��Ĳ�����Ҫѭ����������
   { 
	   for(j = 0; j<imgWidth; j+=mbSize) 
	   {
		// dy �� ��ֱ����E
        // dx �� ˮƽ����E
		   xExtra = imgWidth-j;//�в�������һ�ε���0��������  ͼ�����
		   yExtra = imgHeight-i;

		   int dy,dx,refBlkVer,refBlkHor;
           dy = motionVect[0][mbCount-1];//����E858993460
           dx = motionVect[1][mbCount-1];
           refBlkVer = i + dy;
           refBlkHor = j + dx;
		   //����˶����������ĵ���������Ͻ�
		   for(int m=0;m<mbSize;m++)
		   {
		     for(int n=0;n<mbSize;n++)
			 {
				 int MAX1 = 0,MAX2 = 0;
				 //Ϊ�˱����糁E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!�������ϱ�Ե
				 MAX1 = ((refBlkVer+m)*imgWidth+(refBlkHor+n)<=(imgWidth*imgHeight-1))?((refBlkVer+m)*imgWidth+(refBlkHor+n)):(imgWidth*imgHeight-1);
				 MAX2 = (((i+m)*imgWidth+(n+j))<=(imgWidth*imgHeight-1))?((i+m)*imgWidth+(n+j)):(imgWidth*imgHeight-1);
				 imgComp[MAX2]= imgI[MAX1];
			//	imageComp(i:i+MBSIZE-1,j:j+MBSIZE-1) = imgI(refBlkVer:refBlkVer+MBSIZE-1, refBlkHor:refBlkHor+MBSIZE-1);
			 }
		   }
           mbCount = mbCount + 1;
	   }
    }
    if(yExtra!=0)//��������
		if(xExtra==0)
	     	for(i=imgHeight-1;i>=imgHeight-1-yExtra;i--)
		    	for(j=0;j<imgWidth;j++)
				{				
			    	 imgComp[i*imgWidth+j]= imgI[i*imgWidth+j];
				}
		else
		{
			for(i=imgHeight-1;i>=imgHeight-1-yExtra;i--)
		    	for(j=0;j<imgWidth;j++)
				{				
			    	 imgComp[i*imgWidth+j]= imgI[i*imgWidth+j];
				}
			for(i=0;i<imgHeight-yExtra;i++)
		    	for(j=imgWidth-1;j>=imgWidth-1-xExtra;j--)
				{				
			    	 imgComp[i*imgWidth+j]= imgI[i*imgWidth+j];
				}
		}
	else
	;


}

//***************************************************************************************************/
//����һά��������ֵ�������ڵ��±�E
//��ȁE
//matrix:N��Ԫ�ؾ�ՁE
//N: ���󳤶ȣ�Ϊ����
//minNum:�����е����ֵ
//index:�������ֵ������
//***************************************************************************************************
void minSearch(double* matrix,int N,double* minNum,int* index)
{
			//��ʼ������м�E
	int i,k;
	double value;
	k = (N-1)/2;
	value = *(matrix+k);
	for(i=0;i<N;i++)
	{
		if(*(matrix+i)<*(matrix+k))
		{
			k = i;
			value = *(matrix+i);
		}

	}
	*index = k;
	*minNum =value;
}

//********************************************************************************************
// DS�˶������㷨---����ƥ������������ĵ�Ϊ���ģ�PΪ��E��ķ����ڣ�����P�������������Ч����ã�MBSIZE��С����������Ч����ã�
//
// ��ȁE
//   imgI : �ο�ͼρE
//   imgP : ҪѰ���˶�ʸ����ͼρE
//   imgComp : ������ͼ�����������ָՁE
//   imgWidth : ͼ��Ŀ���
//   imgHeight: ͼ��Ŀ���
// �䳁E
//   motionvector: ͼ����Ƶ��˶�ʸ����ՁE
//   DScomputations: DS�㷨�ļ�����
//*********************************************************************************************

void motionEstDS(unsigned char *imgP, unsigned char* imgI, int imgWidth, int imgHeight, int motionVect[2][MAX], double* DScomputations)
{

//��ʼ������	
     int vectorsNum = 0;
     double costs[9];
     double computations = 0;
     int L = 0; 
// ��������Ҫ��������
	 L= (int)floor(log10(P+1.0)/log10(2.0));  //p=7
	 vectorsNum =(int)(imgWidth*imgHeight/pow((double)MBSIZE,2));
//��̬��ŁE
	 //��ʼ���˶�ʸ��Ϊ��E
     int vectors[2][MAX] ={0};//int vectors[2][vectorsNum] ;
// ��ͼ�����Ͻǿ�ʼ��˵���������ĵ������ϽǴ���ʼ
	 //����ΪMBSIZE������Ѱ�ҵ�ÿ����E�����������������p���ش���ƥŁE
     int mbCount = 1;
     int i=0,j=0;
	 //��ʼ��������ՁE
	 for(j=0;j<9;j++)
	 {
		 costs[j]=65537;
	 }
     int SDSPFlag;//���������ı�E�
	 int cornerFlag;//�����νǵ㱁E�

	 // ��ͼ�����Ͻǿ�ʼ��˵���������ĵ������ϽǴ���ʼ
	 //����ΪMBSIZE������Ѱ�ҵ�ÿ����E�����������������p���ش���ƥŁE
     for( i = 0; i< imgHeight;i+=MBSIZE)//��ֹ�糁E-ͼ���ЁE�MBSIZE^2������?�ܱߵ�ģ�鲻ȥ��ˁE
	 {
//		if(i == 128)
//		{	
//			i = i;
//		}
		for(j = 0; j<imgWidth;j+=MBSIZE)
		{   
//			if(j == 42)
//			{
//				j = j;
//			}
			double costsSDSP[5]={65537,65537,65537,65537,65537};
			double cost[1]={65535};//costs �����ֵ
            int    point[1]={4};// costs �����ֵ������E
			double costSDSP[1]={65535};
			int    pointSDSP[1]={4};
			int    xLast,yLast;//�洢��һ�ε���������E
        //������������ÿһ������������Χ��9�����ҳ�������
            int    x = j;//ͼ�����
            int    y = i;//ͼ�����
			int    k;
        // Ϊ�˱�����������ĵķ������㣬���Ǵ洢��ǰһ�����еõ�����ֵ��
		//���ڵ�һ�ε�E������ǰѴ�ֵ��ŵ�ѭ��֮�⣬�����ĵ�E������ǰ�ֵ��ŵ��ƶ����������ĵ㴦

			//��̬�����ά��ׁE
			unsigned char** imgPtmp;
			unsigned char** imgItmp;
			imgPtmp = new unsigned char*[MBSIZE];
			imgItmp = new unsigned char*[MBSIZE];
			for (k=0;k<MBSIZE;k++)
			{		
				imgPtmp[k]=new unsigned char[MBSIZE];
			    memset(imgPtmp[k],0,MBSIZE*sizeof(unsigned char));//�½��ڴ���ǁE�E
			}

			for (k=0;k<MBSIZE;k++)
			{			
				imgItmp[k]=new unsigned char[MBSIZE];
                memset(imgItmp[k],0,MBSIZE*sizeof(unsigned char));//�½��ڴ���ǁE�E
			}

            for(int blkX=0;blkX<MBSIZE;blkX++)
			{
	    		for(int blkY=0;blkY<MBSIZE;blkY++)
				{
					int MAX1=0;
					//Ϊ�˱����糁E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!�������ϱ�Ե
					MAX1 =((i+blkY)*imgWidth+(j+blkX)<=(imgWidth*imgHeight-1))?(i+blkY)*imgWidth+(j+blkX):(imgWidth*imgHeight-1); 
                    *(imgPtmp[blkX]+blkY) = *(imgP+MAX1);
		    	    *(imgItmp[blkX]+blkY) = *(imgI+MAX1);
				}
			}
			   //     costs(5) = costFuncMAD(imgP(i:i+MBSIZE-1,j:j+MBSIZE-1), ...
                             //       imgI(i:i+MBSIZE-1,j:j+MBSIZE-1),MBSIZE);
			//ѭ��ǰ�ȼ���ο����Ĵ���ρE
            costs[4] = costFuncMAD(imgPtmp,imgItmp,MBSIZE);
            computations = computations + 1;

    //**************************************LDSP������ˁE***************************************//
		    for(k=0;k<9;k++)
			{
				int refBlkVer,refBlkHor;
				refBlkVer = y + LDSP[k].y;//�ο�����С���ֱ����E
				refBlkHor = x + LDSP[k].x;//�ο�����С�ˮƽ����E
				if( refBlkVer < 0 || refBlkVer+MBSIZE > imgHeight || refBlkHor < 0 || refBlkHor+MBSIZE > imgWidth)
				continue;
				if (k == 4)
                continue;
			    for(int blkX2=0;blkX2<MBSIZE;blkX2++)
				{
	               for(int blkY2=0;blkY2<MBSIZE;blkY2++)
				   {
					  int MAX1=0,MAX2=0;
					//Ϊ�˱����糁E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!�������ϱ�Ե
					  MAX1 =((i+blkY2)*imgWidth+(j+blkX2)<=(imgWidth*imgHeight-1))?((i+blkY2)*imgWidth+(j+blkX2)):(imgWidth*imgHeight-1); 
				      MAX2 =(((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2))<=(imgWidth*imgHeight-1))?((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2)):(imgWidth*imgHeight-1); 
                      *(imgPtmp[blkX2]+blkY2) = *(imgP+MAX1);
			          *(imgItmp[blkX2]+blkY2) = *(imgI+MAX2);
					}
				}
                costs[k] = costFuncMAD(imgPtmp,imgItmp,MBSIZE);
                computations = computations + 1;
			}
//******************************һ��ȫLDSP������ʁE***************************************//

	//��һ�ε��ü����ʼ����@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//
			minSearch(costs,9,cost,point);
            // ������сEDSPFlag ��E���1---������û��λ�ƵĻ�Ӧ��́E��غϣ�SDSPFlagʼ��Ϊ1,point[0]����4����2
            if (point[0] == 4)
                SDSPFlag = 1;
            else
			{
			    SDSPFlag = 0;
                if ( abs(LDSP[point[0]].x) == abs(LDSP[point[0]].y) )
                   cornerFlag = 0;
                else
				   cornerFlag = 1; //�ǵ㱁E�
                xLast = x;
                yLast = y;
			    //���������Ƶ��µ�����
                x = x + LDSP[point[0]].x;
                y = y + LDSP[point[0]].y;
                for(int index=0;index<9;index++)
				{
				    costs[index]=65537;
				}
					 //����ֵ������ֵ
                costs[4] = cost[0];
			}
		//**********************************LDSPѭ����ˁE****************************************//
            while (SDSPFlag == 0)//LDSP������SDSPFlag =1Ϊֹ,�ֳɽǵ�ͷǽǵ�����E
			{
				if (cornerFlag == 1)
					//�ų��ǽǵ�����ĵ㣬����ǵ㴦�Ŀ�ρE
                for(int k=0;k<9;k++)
				{      
					int refBlkVer,refBlkHor;
					refBlkVer = y + LDSP[k].y;   
                    refBlkHor = x + LDSP[k].x;   
                    if( refBlkVer < 0 || refBlkVer+MBSIZE > imgHeight || refBlkHor < 0 || refBlkHor+MBSIZE > imgWidth)
                        continue;
                    if (k == 4)
                        continue;      
                    if ( refBlkHor >= xLast - 1  && refBlkHor <= xLast + 1 && refBlkVer >= yLast - 1  && refBlkVer <= yLast + 1 )//�ǽǵ���ɵ�������������
                        continue;// �Ƴ������������ڵ�������E
                    else if (refBlkHor < j-P || refBlkHor > j+P || refBlkVer < i-P || refBlkVer > i+P)//��������֮́E
                        continue;
                    else
					{   
			            for(int blkX2=0;blkX2<MBSIZE;blkX2++)
						{
	                        for(int blkY2=0;blkY2<MBSIZE;blkY2++)
							{
							   int MAX1=0,MAX2=0;
					       //Ϊ�˱����糁E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!�������ϱ�Ե
					           MAX1 =((i+blkY2)*imgWidth+(j+blkX2)<=(imgWidth*imgHeight-1))?(i+blkY2)*imgWidth+(j+blkX2):(imgWidth*imgHeight-1); 
				               MAX2 =(((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2))<=(imgWidth*imgHeight-1))?((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2)):(imgWidth*imgHeight-1); 
                               *(imgPtmp[blkX2]+blkY2) = *(imgP+MAX1);
			                   *(imgItmp[blkX2]+blkY2) = *(imgI+MAX2);
							}
						}
                        costs[k] =  costFuncMAD(imgPtmp,imgItmp,MBSIZE);//һ�������ˁE��E
		            	 //   costs[k] = costFuncMAD(imgP(i:i+MBSIZE-1,j:j+MBSIZE-1), imgI(refBlkVer:refBlkVer+MBSIZE-1, refBlkHor:refBlkHor+MBSIZE-1), MBSIZE);
                        computations = computations + 1;
					}
				}     
                else//�ǽǵ㣬4���������
				{      
					switch (point[0])// 1  2  6  7
                    {
				    	case '1':      // just 3 block 1 2 4
						{
							int refBlkVer,refBlkHor;
						    refBlkVer = y + LDSP[0].y;  
                            refBlkHor = x + LDSP[0].x;   
                            if( refBlkVer < 0 || refBlkVer+MBSIZE > imgHeight || refBlkHor < 0 || refBlkHor+MBSIZE > imgWidth)
                            ;
                            else if (refBlkHor < j-P || refBlkHor > j+P || refBlkVer < i-P || refBlkVer > i+P)
                            ;
                            else 
							{                      
			                    for(int blkX2=0;blkX2<MBSIZE;blkX2++)
								{
	                                for(int blkY2=0;blkY2<MBSIZE;blkY2++)
									{
										int MAX1=0,MAX2=0;
					       //Ϊ�˱����糁E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!�������ϱ�Ե
					                    MAX1 =((i+blkY2)*imgWidth+(j+blkX2)<=(imgWidth*imgHeight-1))?(i+blkY2)*imgWidth+(j+blkX2):(imgWidth*imgHeight-1); 
				                        MAX2 =(((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2))<=(imgWidth*imgHeight-1))?((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2)):(imgWidth*imgHeight-1); 
                                        *(imgPtmp[blkX2]+blkY2) = *(imgP+MAX1);
			                            *(imgItmp[blkX2]+blkY2) = *(imgI+MAX2);
									}
								}
                                costs[0] = (int) costFuncMAD(imgPtmp,imgItmp,MBSIZE);
                                computations = computations + 1;
                            }
                            refBlkVer = y + LDSP[1].y;   
                            refBlkHor = x + LDSP[1].x;   
                            if( refBlkVer < 0 || refBlkVer+MBSIZE > imgHeight || refBlkHor < 0 || refBlkHor+MBSIZE > imgWidth)
                            ;  //ͼ���Ե֮�⣬����E
                            else if (refBlkHor < j-P || refBlkHor > j+P || refBlkVer < i-P  || refBlkVer > i+P)
                            ;  //��������֮�⣬����E
                            else
							{       
			                    for(int blkX2=0;blkX2<MBSIZE;blkX2++)
								{
	                                for(int blkY2=0;blkY2<MBSIZE;blkY2++)
									{
										int MAX1=0,MAX2=0;
					       //Ϊ�˱����糁E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!�������ϱ�Ե
					                    MAX1 =((i+blkY2)*imgWidth+(j+blkX2)<=(imgWidth*imgHeight-1))?(i+blkY2)*imgWidth+(j+blkX2):(imgWidth*imgHeight-1); 
				                        MAX2 =(((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2))<=(imgWidth*imgHeight-1))?((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2)):(imgWidth*imgHeight-1); 
                                        *(imgPtmp[blkX2]+blkY2) = *(imgP+MAX1);
			                            *(imgItmp[blkX2]+blkY2) = *(imgI+MAX2);
									}
								}
                                costs[1] =  costFuncMAD(imgPtmp,imgItmp,MBSIZE);
                                computations = computations + 1;
                            }
                            refBlkVer = y + LDSP[3].y;   
                            refBlkHor = x + LDSP[3].x;  
                            if( refBlkVer < 0 || refBlkVer+MBSIZE > imgHeight || refBlkHor < 0 || refBlkHor+MBSIZE > imgWidth)
                            ; //ͼ���Ե֮�⣬����E
                            else if (refBlkHor < j-P || refBlkHor > j+P || refBlkVer < i-P  || refBlkVer > i+P)
                            ; //��������֮�⣬����E
                            else
							{   
			                    for(int blkX2=0;blkX2<MBSIZE;blkX2++)
								{
	                               for(int blkY2=0;blkY2<MBSIZE;blkY2++)
								   {
									    int MAX1=0,MAX2=0;
					       //Ϊ�˱����糁E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!�������ϱ�Ե
					                    MAX1 =((i+blkY2)*imgWidth+(j+blkX2)<=(imgWidth*imgHeight-1))?(i+blkY2)*imgWidth+(j+blkX2):(imgWidth*imgHeight-1); 
				                        MAX2 =(((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2))<=(imgWidth*imgHeight-1))?((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2)):(imgWidth*imgHeight-1); 
                                        *(imgPtmp[blkX2]+blkY2) = *(imgP+MAX1);
			                            *(imgItmp[blkX2]+blkY2) = *(imgI+MAX2);
								   }
								}
                                costs[3] = costFuncMAD(imgPtmp,imgItmp,MBSIZE);
                                computations = computations + 1;
                                break;
							}
						}
                        case '2': // three blocks 1  3 6
						{
							int refBlkVer,refBlkHor;
					    	refBlkVer = y + LDSP[0].y;  
                            refBlkHor = x + LDSP[0].x;   
                            if ( refBlkVer < 0 || refBlkVer+MBSIZE > imgHeight|| refBlkHor < 0 || refBlkHor+MBSIZE> imgWidth)
                            ;
                            else if (refBlkHor < j-P || refBlkHor > j+P || refBlkVer < i-P || refBlkVer > i+P)
                            ;
                            else 
							{    
			                    for(int blkX2=0;blkX2<MBSIZE;blkX2++)
								{
	                               for(int blkY2=0;blkY2<MBSIZE;blkY2++)
									{
									    int MAX1=0,MAX2=0;
					       //Ϊ�˱����糁E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!�������ϱ�Ե
					                    MAX1 =((i+blkY2)*imgWidth+(j+blkX2)<=(imgWidth*imgHeight-1))?(i+blkY2)*imgWidth+(j+blkX2):(imgWidth*imgHeight-1); 
				                        MAX2 =(((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2))<=(imgWidth*imgHeight-1))?((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2)):(imgWidth*imgHeight-1); 
                                        *(imgPtmp[blkX2]+blkY2) = *(imgP+MAX1);
			                            *(imgItmp[blkX2]+blkY2) = *(imgI+MAX2);
								   }
								}
                                costs[0] =  costFuncMAD(imgPtmp,imgItmp,MBSIZE);
                                computations = computations + 1;
							}

                            refBlkVer = y + LDSP[2].y;   
                            refBlkHor = x + LDSP[2].x;   
                            if( refBlkVer < 0 || refBlkVer+MBSIZE > imgHeight || refBlkHor < 0 || refBlkHor+MBSIZE > imgWidth)
                            ;//ͼ���Ե֮�⣬����E
                            else if (refBlkHor < j-P || refBlkHor > j+P || refBlkVer < i-P  || refBlkVer > i+P)
                            ; //��������֮�⣬����E
                            else
							{        
			                    for(int blkX2=0;blkX2<MBSIZE;blkX2++)
								{
	                                for(int blkY2=0;blkY2<MBSIZE;blkY2++)
									{
									   int MAX1=0,MAX2=0;
					       //Ϊ�˱����糁E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!�������ϱ�Ե
					                   MAX1 =((i+blkY2)*imgWidth+(j+blkX2)<=(imgWidth*imgHeight-1))?(i+blkY2)*imgWidth+(j+blkX2):(imgWidth*imgHeight-1); 
				                       MAX2 =(((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2))<=(imgWidth*imgHeight-1))?((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2)):(imgWidth*imgHeight-1); 
                                       *(imgPtmp[blkX2]+blkY2) = *(imgP+MAX1);
			                           *(imgItmp[blkX2]+blkY2) = *(imgI+MAX2);
									}
								}
                                costs[2] =  costFuncMAD(imgPtmp,imgItmp,MBSIZE);
                                computations = computations + 1;
							}
                        
                            refBlkVer = y + LDSP[5].y;   
                            refBlkHor = x + LDSP[5].x;  
                            if( refBlkVer < 0 || refBlkVer+MBSIZE > imgHeight || refBlkHor < 0 || refBlkHor+MBSIZE > imgWidth)
                            ;//ͼ���Ե֮�⣬����E
                            else if (refBlkHor < j-P || refBlkHor > j+P || refBlkVer < i-P  || refBlkVer > i+P)
                            ;//��������֮�⣬����E
                            else
							{        
			                    for(int blkX2=0;blkX2<MBSIZE;blkX2++)
								{
	                                for(int blkY2=0;blkY2<MBSIZE;blkY2++)
									{
										int MAX1=0,MAX2=0;
					       //Ϊ�˱����糁E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!�������ϱ�Ե
					                    MAX1 =((i+blkY2)*imgWidth+(j+blkX2)<=(imgWidth*imgHeight-1))?(i+blkY2)*imgWidth+(j+blkX2):(imgWidth*imgHeight-1); 
				                        MAX2 =(((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2))<=(imgWidth*imgHeight-1))?((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2)):(imgWidth*imgHeight-1); 
                                        *(imgPtmp[blkX2]+blkY2) = *(imgP+MAX1);
			                            *(imgItmp[blkX2]+blkY2) = *(imgI+MAX2);
									}
								}
                                costs[5] = costFuncMAD(imgPtmp,imgItmp,MBSIZE);
                                computations = computations + 1;
							}
				        	break;
						}
                        case '6': // three blocks 4 7 9
						{
							int refBlkVer,refBlkHor;
					        refBlkVer = y + LDSP[3].y;  
                            refBlkHor = x + LDSP[3].x;   
                            if ( refBlkVer < 0 || refBlkVer+MBSIZE> imgHeight|| refBlkHor < 0 || refBlkHor+MBSIZE > imgWidth)
                            ;
                            else if (refBlkHor < j-P || refBlkHor > j+P || refBlkVer < i-P || refBlkVer > i+P)
                            ;
                            else 
							{         
			                    for(int blkX2=0;blkX2<MBSIZE;blkX2++)
								{
	                               for(int blkY2=0;blkY2<MBSIZE;blkY2++)
								   {
									   int MAX1=0,MAX2=0;
					       //Ϊ�˱����糁E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!�������ϱ�Ե
					                   MAX1 =((i+blkY2)*imgWidth+(j+blkX2)<=(imgWidth*imgHeight-1))?(i+blkY2)*imgWidth+(j+blkX2):(imgWidth*imgHeight-1); 
				                       MAX2 =(((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2))<=(imgWidth*imgHeight-1))?((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2)):(imgWidth*imgHeight-1); 
                                       *(imgPtmp[blkX2]+blkY2) = *(imgP+MAX1);
			                           *(imgItmp[blkX2]+blkY2) = *(imgI+MAX2);
								   }
								}
                                costs[3] =  costFuncMAD(imgPtmp,imgItmp,MBSIZE);
                                computations = computations + 1;
							}

                            refBlkVer = y + LDSP[6].y;   
                            refBlkHor = x + LDSP[6].x;   
                            if( refBlkVer < 0 || refBlkVer+MBSIZE > imgHeight || refBlkHor < 0 || refBlkHor+MBSIZE > imgWidth)
                            ;//ͼ���Ե֮�⣬����E
                            else if (refBlkHor < j-P || refBlkHor > j+P || refBlkVer < i-P  || refBlkVer > i+P)
                            ;//��������֮�⣬����E
                            else
							{      
			                    for(int blkX2=0;blkX2<MBSIZE;blkX2++)
								{
	                                for(int blkY2=0;blkY2<MBSIZE;blkY2++)
									{
										int MAX1=0,MAX2=0;
					       //Ϊ�˱����糁E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!�������ϱ�Ե
					                    MAX1 =((i+blkY2)*imgWidth+(j+blkX2)<=(imgWidth*imgHeight-1))?(i+blkY2)*imgWidth+(j+blkX2):(imgWidth*imgHeight-1); 
				                        MAX2 =(((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2))<=(imgWidth*imgHeight-1))?((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2)):(imgWidth*imgHeight-1); 
                                       *(imgPtmp[blkX2]+blkY2) = *(imgP+MAX1);
			                            *(imgItmp[blkX2]+blkY2) = *(imgI+MAX2);
									}
								}
                                costs[6] =  costFuncMAD(imgPtmp,imgItmp,MBSIZE);
                                computations = computations + 1;
							}
                        
                            refBlkVer = y + LDSP[8].y;   
                            refBlkHor = x + LDSP[8].x;  
                            if( refBlkVer < 0 || refBlkVer+MBSIZE > imgHeight || refBlkHor < 0 || refBlkHor+MBSIZE > imgWidth)
                            ;//ͼ���Ե֮�⣬����E
                            else if (refBlkHor < j-P || refBlkHor > j+P || refBlkVer < i-P  || refBlkVer > i+P)
                            ;//��������֮�⣬����E
                            else
							{        
			                    for(int blkX2=0;blkX2<MBSIZE;blkX2++)
								{
	                                for(int blkY2=0;blkY2<MBSIZE;blkY2++)
									{
										int MAX1=0,MAX2=0;
					       //Ϊ�˱����糁E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!�������ϱ�Ե
					                    MAX1 =((i+blkY2)*imgWidth+(j+blkX2)<=(imgWidth*imgHeight-1))?(i+blkY2)*imgWidth+(j+blkX2):(imgWidth*imgHeight-1); 
				                        MAX2 =(((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2))<=(imgWidth*imgHeight-1))?((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2)):(imgWidth*imgHeight-1); 
                                        *(imgPtmp[blkX2]+blkY2) = *(imgP+MAX1);
			                            *(imgItmp[blkX2]+blkY2) = *(imgI+MAX2);
									}
								}
                                costs[8] =  costFuncMAD(imgPtmp,imgItmp,MBSIZE);
                                computations = computations + 1;
							}
                            break;
						}
                        case '7': // three blocks 6 8 9
						{
							int refBlkVer,refBlkHor;
                            refBlkVer = y + LDSP[5].y;  
                            refBlkHor = x + LDSP[5].x;   
                            if ( refBlkVer < 0 || refBlkVer+MBSIZE > imgHeight|| refBlkHor < 0 || refBlkHor+MBSIZE> imgWidth)
                            ;
                            else if (refBlkHor < j-P || refBlkHor > j+P || refBlkVer < i-P || refBlkVer > i+P)
                            ;
                            else 
							{            
			                    for(int blkX2=0;blkX2<MBSIZE;blkX2++)
								{
	                               for(int blkY2=0;blkY2<MBSIZE;blkY2++)
								   {
									    int MAX1=0,MAX2=0;
					       //Ϊ�˱����糁E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!�������ϱ�Ե
					                    MAX1 =((i+blkY2)*imgWidth+(j+blkX2)<=(imgWidth*imgHeight-1))?(i+blkY2)*imgWidth+(j+blkX2):(imgWidth*imgHeight-1); 
				                        MAX2 =(((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2))<=(imgWidth*imgHeight-1))?((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2)):(imgWidth*imgHeight-1); 
                                        *(imgPtmp[blkX2]+blkY2) = *(imgP+MAX1);
			                            *(imgItmp[blkX2]+blkY2) = *(imgI+MAX2);
								   }
								}
                                costs[5] =  costFuncMAD(imgPtmp,imgItmp,MBSIZE);
                                computations = computations + 1;
							}

                            refBlkVer = y + LDSP[7].y;   
                            refBlkHor = x + LDSP[7].x;   
                            if( refBlkVer < 0 || refBlkVer+MBSIZE > imgHeight || refBlkHor < 0 || refBlkHor+MBSIZE > imgWidth)
                            ; //ͼ���Ե֮�⣬����E
                            else if (refBlkHor < j-P || refBlkHor > j+P || refBlkVer < i-P  || refBlkVer > i+P)
                            ;//��������֮�⣬����E
                            else
							{              
			                    for(int blkX2=0;blkX2<MBSIZE;blkX2++)
								{
	                                for(int blkY2=0;blkY2<MBSIZE;blkY2++)
									{
										int MAX1=0,MAX2=0;
					       //Ϊ�˱����糁E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!�������ϱ�Ե
					                    MAX1 =((i+blkY2)*imgWidth+(j+blkX2)<=(imgWidth*imgHeight-1))?(i+blkY2)*imgWidth+(j+blkX2):(imgWidth*imgHeight-1); 
				                        MAX2 =(((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2))<=(imgWidth*imgHeight-1))?((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2)):(imgWidth*imgHeight-1); 
                                        *(imgPtmp[blkX2]+blkY2) = *(imgP+MAX1);
			                            *(imgItmp[blkX2]+blkY2) = *(imgI+MAX2);
									}
								}
                                costs[7] =  costFuncMAD(imgPtmp,imgItmp,MBSIZE);
                                computations = computations + 1;
							}
                         
                            refBlkVer = y + LDSP[8].y;   
                            refBlkHor = x + LDSP[8].x;  
                            if( refBlkVer < 0 || refBlkVer+MBSIZE > imgHeight || refBlkHor < 0 || refBlkHor+MBSIZE > imgWidth)
                            ;//ͼ���Ե֮�⣬����E
                            else if (refBlkHor < j-P || refBlkHor > j+P || refBlkVer < i-P  || refBlkVer > i+P)
                            ;//��������֮�⣬����E
                            else
							{             
			                   for(int blkX2=0;blkX2<MBSIZE;blkX2++)
							   {
	                              for(int blkY2=0;blkY2<MBSIZE;blkY2++)
								  {
									   int MAX1=0,MAX2=0;
					       //Ϊ�˱����糁E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!�������ϱ�Ե
					                   MAX1 =((i+blkY2)*imgWidth+(j+blkX2)<=(imgWidth*imgHeight-1))?(i+blkY2)*imgWidth+(j+blkX2):(imgWidth*imgHeight-1); 
				                       MAX2 =(((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2))<=(imgWidth*imgHeight-1))?((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2)):(imgWidth*imgHeight-1); 
                                       *(imgPtmp[blkX2]+blkY2) = *(imgP+MAX1);
			                           *(imgItmp[blkX2]+blkY2) = *(imgI+MAX2);
								  }
							   }
                               costs[8] =  costFuncMAD(imgPtmp,imgItmp,MBSIZE);
                               computations = computations + 1;
							}
				        	break;
						}
				    	default:
						{
				        	break;
						}
					}//switch

				}//else
  
	//�ڶ��ε��ü���LDSP����́E�@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//	
		     	minSearch(costs,9,cost,point);
                if (point[0] == 4)
                   SDSPFlag = 1;
                else
				{
			       SDSPFlag = 0;
                   if ( abs(LDSP[point[0]].x) == abs(LDSP[point[0]].y) )
                      cornerFlag = 0;
                   else
					   cornerFlag = 1; //�ǵ㱁E�
                   xLast = x;
                   yLast = y;
                   x = x + LDSP[point[0]].x;
                   y = y + LDSP[point[0]].y;
                   for(int index=0;index<9;index++)
				   {
					  costs[index]=65537;
				   }
                   costs[4] = cost[0];

				}
			}//while ѭ����ʁE
//************************************* ��ȁESDSP ��ˁE**********************************************//
			costsSDSP[2]=cost[0];
            for(k=0;k<5;k++)
			{        
				int refBlkVer,refBlkHor;
				refBlkVer = y + SDSP[k].y;   
                refBlkHor = x + SDSP[k].x;   
                if ( refBlkVer < 0 || refBlkVer+MBSIZE > imgHeight|| refBlkHor < 0 || refBlkHor+MBSIZE > imgWidth)
                continue; 
                else if (refBlkHor < j-P || refBlkHor > j+P || refBlkVer < i-P || refBlkVer > i+P)
                continue;  
			    if (k == 2)
                continue;
			    for(int blkX2=0;blkX2<MBSIZE;blkX2++)
				{
	               for(int blkY2=0;blkY2<MBSIZE;blkY2++)
				   {
					  int MAX1=0,MAX2=0;
					//Ϊ�˱����糁E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!�������ϱ�Ե
					  MAX1 =((i+blkY2)*imgWidth+(j+blkX2)<=(imgWidth*imgHeight-1))?(i+blkY2)*imgWidth+(j+blkX2):(imgWidth*imgHeight-1); 
				      MAX2 =(((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2))<=(imgWidth*imgHeight-1))?((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2)):(imgWidth*imgHeight-1); 
                      *(imgPtmp[blkX2]+blkY2) = *(imgP+MAX1);
			          *(imgItmp[blkX2]+blkY2) = *(imgI+MAX2);
					}
				}
                costsSDSP[k] =  costFuncMAD(imgPtmp,imgItmp,MBSIZE);
                computations = computations + 1;
                   
            }
		//�����ε�������SDSP@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//		
            minSearch(costsSDSP,5,cost,point);
            x = x + SDSP[point[0]].x;
            y = y + SDSP[point[0]].y;  
         	//�ж��Ƿ�д�糁E
			if(mbCount>vectorsNum)
				mbCount = vectorsNum;
            vectors[0][mbCount-1] = y - i;    // �˶�ʸ����������E
            vectors[1][mbCount-1] = x - j;    // �˶�ʸ����������E
			//ģ�������һ
            mbCount = mbCount + 1;
       //     costs[3][3]={{65537,65537,65537},{65537,65537,65537},{65537,65537,65537}};
			//������������ԭ---�������򵥷���ô��
			for(k=0;k<5;k++)  
			{
				costsSDSP[k]=65537;
			}	 		
            //��ԭcostsֵ
		    for(k=0;k<9;k++)
			{
		        costs[k]=65537;
			}
			//�ͷ��ڴ�E
     	    for (k=0;k<MBSIZE;k++)
            	delete []imgPtmp[k];
        	for (k=0;k<MBSIZE;k++)
            	delete []imgItmp[k];
	        delete []imgPtmp;
	        delete []imgItmp;
		}
	 }


	for(i=0;i<2;i++) 
		{
			for(j=0;j<MAX;j++)
			{
				if(j>=vectorsNum)
					motionVect[i][j]=0;
				else
				    motionVect[i][j]=vectors[i][j];
			}
		}
    *DScomputations = computations/(mbCount - 1);    

}
