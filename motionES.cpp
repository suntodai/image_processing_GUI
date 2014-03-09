//   MBSIZE : ºE£¿éµÄ´óĞ¡
//   P : ËÑË÷²½³¤²ÎÊı

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
// TSSËã·¨¡ª¡ªPÔ½´ó£¬ËÑË÷´°¿ÚÔ½´ó£¬¼ÆËãÁ¿Ô½´ó£¬MBSIZEÓú´ó£¬ËÑË÷µÄÔË¶¯Ê¸Á¿ÉÙ£¬¼ÆËãÁ¿Ğ¡£¬Ğ§¹û²û¿¿
//
// ÊäÈE
//   imgI : ²Î¿¼Í¼ÏE
//   imgP : ÒªÑ°ÕÒÔË¶¯Ê¸Á¿µÄÍ¼ÏE
//   imgComp : ²¹³¥ºóÍ¼ÏñµÄÊı¾İÇøµÄÖ¸ÕE
//   imgWidth : Í¼ÏñµÄ¿úÒÈ
//   imgHeight: Í¼ÏñµÄ¿úÒÈ
// Êä³E
//   motionvector: Í¼Ïñ¹À¼ÆµÄÔË¶¯Ê¸Á¿¾ØÕE
//   TSScomputations: TSSËã·¨µÄ¼ÆËãÁ¿
//*********************************************************************************************
void motionEstTSS(unsigned char *imgP, unsigned char* imgI, int imgWidth, int imgHeight, int motionVect[2][MAX], double* TSScomputations)
{
//³õÊ¼»¯²ÎÊı	

     double costs[3][3]={{65537,65537,65537},{65537,65537,65537},{65537,65537,65537}};
     double computations = 0;
     int L = 0; 
     int stepMax = 0;
     int vectorsNum = 0;
	 // ¼ÆËãËùĞèÒªµÄ×ûĞó²½Êı
	 L= (int)floor(log10(P+1.0)/log10(2.0));  //p=7,s=4
	 stepMax = (int)pow(2.0,(L-1));
	 vectorsNum =(int)(imgWidth*imgHeight/pow((double)MBSIZE,2));
//¶¯Ì¬·ÖÅE
	 //³õÊ¼»¯ÔË¶¯Ê¸Á¿ÎªÁE
     int vectors[2][MAX] ={0};//int vectors[2][vectorsNum] ;
// ´ÓÍ¼Ïñ×óÉÏ½Ç¿ªÊ¼£¬ËµÃ÷Ïñ¿éµÄÖĞĞÄµãÔÚ×óÉÏ½Ç´¦¿ªÊ¼
	 //²½³¤ÎªMBSIZE£¬ÎÒÃÇÑ°ÕÒµÄÃ¿¸öºE£¿éËÑË÷ÆäÉÏÏÂ×óÓÒpÏñËØ´¦µÄÆ¥ÅE
     int mbCount = 1;
     int i,j;
     for( i = 0; i< imgHeight;i+=MBSIZE)//·ÀÖ¹Òç³E-Í¼Ïñ±ØĞEÇMBSIZE^2ÕûÊı±¶?ÖÜ±ßµÄÄ£¿é²»È¥ÔËËE
	 {
        for(j = 0; j<imgWidth;j+=MBSIZE)
		{   
        //¶ÔÓÚÈı²½·¨£¬Ã¿Ò»²½ÎÒÃÇÆÀ¹ÀÖÜÎ§µÄ9²¿·ÖÕÒ³ö×ûâ¥ÅäµÄ
            double  pVector[3]={0,0,0};//----------[dx,dy,min]
            int  x = j;//Í¼ÏñµÄÁĞ
            int  y = i;//Í¼ÏñµÄĞĞ
			int  k,t;
			int  stepSize;
        // ÎªÁË±ÜÃâ¶ÔËÑË÷ÖĞĞÄµÄ·´¸´¼ÆËã£¬ÎÒÃÇ´æ´¢ÆäÇ°Ò»´ÎÔËĞĞµÃµ½µÄÊıÖµ¡£
		//¶ÔÓÚµÚÒ»´ÎµEú£¬ÎÒÃÇ°Ñ´ËÖµ´æ·Åµ½Ñ­»·Ö®Íâ£¬µ«ËæºóµÄµEú£¬ÎÒÃÇ°ÑÖµ´æ·Åµ½ÒÆ¶¯µ¹µÄĞÂÖĞĞÄµã´¦

			//¶¯Ì¬·ÖÅä¶şÎ¬Êı×E
			unsigned char** imgPtmp;
			unsigned char** imgItmp;
			imgPtmp = new unsigned char*[MBSIZE];
			imgItmp = new unsigned char*[MBSIZE];
			for (k=0;k<MBSIZE;k++)
			{		
				imgPtmp[k]=new unsigned char[MBSIZE];
			    memset(imgPtmp[k],0,MBSIZE*sizeof(unsigned char));//ĞÂ½¨ÄÚ´æÇøÇEE
			}

			for (k=0;k<MBSIZE;k++)
			{			
				imgItmp[k]=new unsigned char[MBSIZE];
                memset(imgItmp[k],0,MBSIZE*sizeof(unsigned char));//ĞÂ½¨ÄÚ´æÇøÇEE
			}

            for(int blkX=0;blkX<MBSIZE;blkX++)
			{
	    		for(int blkY=0;blkY<MBSIZE;blkY++)
				{
					int MAX1=0,MAX2=0;//·ÀÒç³E
					//ÎªÁË±ÜÃâÒç³E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!¹ıÁËÔò²¹ÉÏ±ßÔµ
					MAX1 =((i+blkY)*imgWidth+(j+blkX)<=(imgWidth*imgHeight-1))?(i+blkY)*imgWidth+(j+blkX):(imgWidth*imgHeight-1); 
                    *(imgPtmp[blkX]+blkY) = *(imgP+MAX1);
		    	    *(imgItmp[blkX]+blkY) = *(imgI+MAX1);
				}
			}
			   //     costs(2,2) = costFuncMAD(imgP(i:i+MBSIZE-1,j:j+MBSIZE-1), ...
                             //       imgI(i:i+MBSIZE-1,j:j+MBSIZE-1),MBSIZE);
			//Ç¿ÖÆ×ª»»¿ªÏúÖµÎªÕûÊı
			//Ñ­»·Ç°ÏÈ¼ÆËã²Î¿¼ÖĞĞÄ´¦¿ªÏE
            costs[1][1] = costFuncMAD(imgPtmp,imgItmp,MBSIZE);
            computations = computations + 1;
            stepSize = stepMax;               

            while(stepSize >= 1)  
			{
                int m,n;
				int dx,dy;
	     		double min;
            // m ÊÇĞĞ»òÕß´¹Ö±ËÑË÷²ÎÊı
            // n ÊÇÁĞ»òÕßË®Æ½ËÑË÷²ÎÊı
                for( m = -stepSize;m <= stepSize ; m += stepSize)
				{
                   for( n = -stepSize;n <= stepSize ; n += stepSize)
				   {
				    	int refBlkVer,refBlkHor;
				    	int costRow,costCol;
                        refBlkVer = y + m;   // ²Î¿¼¿éµÄĞĞ£¬´¹Ö±×ø±E
                        refBlkHor = x + n;   // ²Î¿¼¿EÄÁĞ£¬Ë®Æ½×ø±E
               //         if (( refBlkVer < 1 )||( refBlkVer+MBSIZE-1 > imgHeight)|| (refBlkHor < 1 )|| (refBlkHor+MBSIZE-1)> imgWidth)
						if (( refBlkVer < 0 )||( refBlkVer+MBSIZE > imgHeight)|| (refBlkHor < 0 )|| (refBlkHor+MBSIZE)> imgWidth)
                           continue;
						//Éú³Écost¾ØÕóµÄĞĞÁĞ×ø±EÑË÷ÏÂ±E
                        costRow = m/stepSize + 1;//0~2  
                        costCol = n/stepSize + 1;//0~2
						//ÖĞĞÄ´¦Ìø³E
                        if (costRow == 1 && costCol == 1)
                           continue;
				        for(int blkX2=0;blkX2<MBSIZE;blkX2++)
						{
	                     	for(int blkY2=0;blkY2<MBSIZE;blkY2++)
							{
							   int MAX1=0,MAX2=0;//·ÀÒç³E
							//ÎªÁË±ÜÃâÒç³E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!¹ıÁËÔò²¹ÉÏ±ßÔµ
							   MAX1 =((i+blkY2)*imgWidth+(j+blkX2)<=(imgWidth*imgHeight-1))?(i+blkY2)*imgWidth+(j+blkX2):(imgWidth*imgHeight-1); 
				               MAX2 =(((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2))<=(imgWidth*imgHeight-1))?((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2)):(imgWidth*imgHeight-1); 
                               *(imgPtmp[blkX2]+blkY2) = *(imgP+MAX1);
			                   *(imgItmp[blkX2]+blkY2) = *(imgI+MAX2);
							}
						}
                        costs[costRow][costCol] = costFuncMAD(imgPtmp,imgItmp,MBSIZE);
     //                 costs(costRow, costCol ) = costFuncMAD(imgP(i:i+MBSIZE-1,j:j+MBSIZE-1), ...
     //                   imgI(refBlkVer:refBlkVer+MBSIZE-1, refBlkHor:refBlkHor+MBSIZE-1), MBSIZE);
                        computations = computations + 1;//ÔËËãÁ¿¼ÓÒ»
				   }
				}
            
            // µ½´ËÎÒÃÇÕÒµ½×ûì¡¿ªÏú²¢ÇÒ´æ´¢¸ÃÖµ
                minCost(costs,pVector);      // finds which macroblock in imgI gave us min Cost
                dx  = (int)(pVector[0]);//dx.dy¶¼ÊÇ0~2²»ÊÇ1~3
		     	dy  = (int)(pVector[1]);
			    min = pVector[2];
               // ½«ËÑË÷´°¿Ú×ø±EEÂµ½×ûì¡¿ªÏú´¦
                x = x + (dx-1)*stepSize;
                y = y + (dy-1)*stepSize; 
            // Arohs thought: At this point we can check and see if the shifted co-ordinates are exactly the same 
			//as the root co-ordinates of the last step, then we check them against a preset threshold, 
			//and ifthe cost is less then that, than we can exit from teh loop right here. 
			//This way we can save more computations. However, as this is not implemented in the paper I am modeling, 
			//am not incorporating this test. May be later...as my own addition to the algorithm
            //  ËÑË÷²½³¤¼õ°E
                stepSize = stepSize / 2;
			//  ²Î¿¼ÖĞĞÄµÄ¿ªÏúÖµ¸EÂÎªÄ¿Ç°×ûâ¥Åä´¦µÄ
                costs[1][1] = costs[dy][dx]; 
				
			}


			//ÅĞ¶ÏÊÇ·ñĞ´Òç³E
			if(mbCount>vectorsNum)
				mbCount = vectorsNum;
            vectors[0][mbCount-1] = y - i;    // ÔË¶¯Ê¸Á¿µÄĞĞ×ø±E
            vectors[1][mbCount-1] = x - j;    // ÔË¶¯Ê¸Á¿µÄÁĞ×ø±E
			//Ä£¿é¼ÆÊı¼ÓÒ»
            mbCount = mbCount + 1;
       //     costs[3][3]={{65537,65537,65537},{65537,65537,65537},{65537,65537,65537}};
			//½«¿ªÏúº¯Êı¸´Ô­---ÓĞÆäËû¼òµ¥·½·¨Ã´£¿
			for(k=0;k<3;k++)  //memset(costs,65537,3*sizeof(int));//memset°´×Ö·û²Ù×÷µ¼ÖÂ65537½Ø¶Ï³É01,int Õ¼2×Ö½Ú£¬²úÉE010101---16843009£¬½á¹û²»¶Ô£¡£¡£¡
			{
				for(t=0;t<3;t++)
					costs[k][t]=65537;
			}	 			//ÊÍ·ÅÄÚ´E
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
//   ¼ÆËã²¹³¥ºóÍ¼ÏñµÄPSNR
// ÊäÈE
//   imgP: Ô­Í¼
//   imgComp:²¹³¥ºóÍ¼ÏE
//   imgHeight: Í¼ÏñµÄ¸ß
//   imgWidth: Í¼ÏñµÄ¿E
//   n : Í¼ÏñÏñËØµÄ×ûÔß·å·åÖµ
// Êä³E
//   psnr:²¹³¥Í¼ÏñµÄ·åÖµĞÅÔEÈ
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
// ¶ÔÁ½¸ö¿é¼ÆËãÆ½¾ù¾ø¶ÔÎó²E
// ÊäÈE
// currentBlk : ¼ÆËãMADÖµµÄÏñ¿E
// refBlk : ¼ÆËãMADÖµµÄ²Î¿¼Ïñ¿E
// Êä³E
// cost : Á½Ïñ¿éMADÖµ
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
// ÕÒµ½×ûì¡¿ªÏú¾ØÕóµÄ×ûì¡ÖµµÄÏÂ±E
//
// ÊäÈE
//   costs : ºE£¿é¿ªÏú¾ØÕE
//         
// Êä³E
//   pVector: dx,dy,minÊä³ö×ûì¡¿éµÄÁĞ£¬ĞĞ×ø±EÍ×ûì¡Öµ
//****************************************************************************
void minCost(double costs[3][3],double pVector[] )
{
//³õÊ¼»¯
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
// ¸ù¾İÔË¶¯¹À¼ÆÊ¸Á¿Éú³ÉÔË¶¯²¹³¥Í¼ÏE
//
// ÊäÈE
//   imgI : ²Î¿¼Í¼ÏE
//   motionVect : ¹À¼ÆÔË¶¯Ê¸Á¿¾ØÕE
//   MBSIZE £º ºE£¿é´óĞ¡
///  imgWidth : Í¼Ïñ¿úÒÈ
//   imgHeight: Í¼ÏñµÄ¸ß¶È
// Êä³E
//   imgComp :²¹³¥Í¼ÏñÊı¾İÖ¸ÕE
//*****************************************************************************
void motionComp(unsigned char* imgI,int mbSize,int imgWidth,int imgHeight,int motionVect[2][MAX],unsigned char*imgComp)
{

   int mbCount = 1;
   int i,j;
//Ö¸Ê¾ÊÇ·ñÊäÈE¼ÏñÊÇMBSIZEµÄÕûÊı±¶
   int xExtra,yExtra;
   for(i = 0; i<imgHeight; i+= mbSize) //ÔË¶¯²¹³¥Í¼ÏñµÄ²úÉúĞèÒªÑ­»·ËùÓĞÏñËØ
   { 
	   for(j = 0; j<imgWidth; j+=mbSize) 
	   {
		// dy ĞĞ ´¹Ö±×ø±E
        // dx ÁĞ Ë®Æ½×ø±E
		   xExtra = imgWidth-j;//²Ğ²û¿¬×ûÖóÒ»´ÎµÈÓÚ0ÔòÕûÊı±¶  Í¼ÏñµÄÁĞ
		   yExtra = imgHeight-i;

		   int dy,dx,refBlkVer,refBlkHor;
           dy = motionVect[0][mbCount-1];//¶Á³E858993460
           dx = motionVect[1][mbCount-1];
           refBlkVer = i + dy;
           refBlkHor = j + dx;
		   //Ïñ¿éÔË¶¯²¹³¥£¬ÖĞĞÄµãÔÚÏñ¿é×óÉÏ½Ç
		   for(int m=0;m<mbSize;m++)
		   {
		     for(int n=0;n<mbSize;n++)
			 {
				 int MAX1 = 0,MAX2 = 0;
				 //ÎªÁË±ÜÃâÒç³E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!¹ıÁËÔò²¹ÉÏ±ßÔµ
				 MAX1 = ((refBlkVer+m)*imgWidth+(refBlkHor+n)<=(imgWidth*imgHeight-1))?((refBlkVer+m)*imgWidth+(refBlkHor+n)):(imgWidth*imgHeight-1);
				 MAX2 = (((i+m)*imgWidth+(n+j))<=(imgWidth*imgHeight-1))?((i+m)*imgWidth+(n+j)):(imgWidth*imgHeight-1);
				 imgComp[MAX2]= imgI[MAX1];
			//	imageComp(i:i+MBSIZE-1,j:j+MBSIZE-1) = imgI(refBlkVer:refBlkVer+MBSIZE-1, refBlkHor:refBlkHor+MBSIZE-1);
			 }
		   }
           mbCount = mbCount + 1;
	   }
    }
    if(yExtra!=0)//·ÇÕûÊı±¶
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
//¼ÆËãÒ»Î¬¾ØÕóµÄ×ûì¡ÖµºÍÆäËùÔÚµÄÏÂ±E
//ÊäÈE
//matrix:N¸öÔªËØ¾ØÕE
//N: ¾ØÕó³¤¶È£¬ÎªÆæÊı
//minNum:¾ØÕóÖĞµÄ×ûì¡Öµ
//index:¾ØÕó×ûì¡ÖµµÄË÷Òı
//***************************************************************************************************
void minSearch(double* matrix,int N,double* minNum,int* index)
{
			//³õÊ¼×ûì¡ÔÚÖĞ¼E
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
// DSÔË¶¯¹À¼ÆËã·¨---×ûòÕÆ¥Åä¿éÉèÖÃÔÚÖĞĞÄµãÎªÖĞĞÄ£¬PÎª°E¶µÄ·½¿òÄÚ£¬Ëæ×ÅPÔö´ó¼ÆËãÁ¿Ôö´ó£¬Ğ§¹û±äºÃ£¬MBSIZE±äĞ¡¼ÆËãÁ¿Ôö´ó£¬Ğ§¹û±äºÃ£¿
//
// ÊäÈE
//   imgI : ²Î¿¼Í¼ÏE
//   imgP : ÒªÑ°ÕÒÔË¶¯Ê¸Á¿µÄÍ¼ÏE
//   imgComp : ²¹³¥ºóÍ¼ÏñµÄÊı¾İÇøµÄÖ¸ÕE
//   imgWidth : Í¼ÏñµÄ¿úÒÈ
//   imgHeight: Í¼ÏñµÄ¿úÒÈ
// Êä³E
//   motionvector: Í¼Ïñ¹À¼ÆµÄÔË¶¯Ê¸Á¿¾ØÕE
//   DScomputations: DSËã·¨µÄ¼ÆËãÁ¿
//*********************************************************************************************

void motionEstDS(unsigned char *imgP, unsigned char* imgI, int imgWidth, int imgHeight, int motionVect[2][MAX], double* DScomputations)
{

//³õÊ¼»¯²ÎÊı	
     int vectorsNum = 0;
     double costs[9];
     double computations = 0;
     int L = 0; 
// ¼ÆËãËùĞèÒªµÄ×ûĞó²½Êı
	 L= (int)floor(log10(P+1.0)/log10(2.0));  //p=7
	 vectorsNum =(int)(imgWidth*imgHeight/pow((double)MBSIZE,2));
//¶¯Ì¬·ÖÅE
	 //³õÊ¼»¯ÔË¶¯Ê¸Á¿ÎªÁE
     int vectors[2][MAX] ={0};//int vectors[2][vectorsNum] ;
// ´ÓÍ¼Ïñ×óÉÏ½Ç¿ªÊ¼£¬ËµÃ÷Ïñ¿éµÄÖĞĞÄµãÔÚ×óÉÏ½Ç´¦¿ªÊ¼
	 //²½³¤ÎªMBSIZE£¬ÎÒÃÇÑ°ÕÒµÄÃ¿¸öºE£¿éËÑË÷ÆäÉÏÏÂ×óÓÒpÏñËØ´¦µÄÆ¥ÅE
     int mbCount = 1;
     int i=0,j=0;
	 //³õÊ¼»¯¿ªÏú¾ØÕE
	 for(j=0;j<9;j++)
	 {
		 costs[j]=65537;
	 }
     int SDSPFlag;//´óÁâĞÎÖĞĞÄ±E¾
	 int cornerFlag;//´óÁâĞÎ½Çµã±E¾

	 // ´ÓÍ¼Ïñ×óÉÏ½Ç¿ªÊ¼£¬ËµÃ÷Ïñ¿éµÄÖĞĞÄµãÔÚ×óÉÏ½Ç´¦¿ªÊ¼
	 //²½³¤ÎªMBSIZE£¬ÎÒÃÇÑ°ÕÒµÄÃ¿¸öºE£¿éËÑË÷ÆäÉÏÏÂ×óÓÒpÏñËØ´¦µÄÆ¥ÅE
     for( i = 0; i< imgHeight;i+=MBSIZE)//·ÀÖ¹Òç³E-Í¼Ïñ±ØĞEÇMBSIZE^2ÕûÊı±¶?ÖÜ±ßµÄÄ£¿é²»È¥ÔËËE
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
			double cost[1]={65535};//costs ÖĞ×ûì¡Öµ
            int    point[1]={4};// costs ÖĞ×ûì¡ÖµµÄ×ø±E
			double costSDSP[1]={65535};
			int    pointSDSP[1]={4};
			int    xLast,yLast;//´æ´¢ÉÏÒ»´ÎµÄÖĞĞÄ×ø±E
        //¶ÔÓÚÈı²½·¨£¬Ã¿Ò»²½ÎÒÃÇÆÀ¹ÀÖÜÎ§µÄ9²¿·ÖÕÒ³ö×ûâ¥ÅäµÄ
            int    x = j;//Í¼ÏñµÄÁĞ
            int    y = i;//Í¼ÏñµÄĞĞ
			int    k;
        // ÎªÁË±ÜÃâ¶ÔËÑË÷ÖĞĞÄµÄ·´¸´¼ÆËã£¬ÎÒÃÇ´æ´¢ÆäÇ°Ò»´ÎÔËĞĞµÃµ½µÄÊıÖµ¡£
		//¶ÔÓÚµÚÒ»´ÎµEú£¬ÎÒÃÇ°Ñ´ËÖµ´æ·Åµ½Ñ­»·Ö®Íâ£¬µ«ËæºóµÄµEú£¬ÎÒÃÇ°ÑÖµ´æ·Åµ½ÒÆ¶¯µ¹µÄĞÂÖĞĞÄµã´¦

			//¶¯Ì¬·ÖÅä¶şÎ¬Êı×E
			unsigned char** imgPtmp;
			unsigned char** imgItmp;
			imgPtmp = new unsigned char*[MBSIZE];
			imgItmp = new unsigned char*[MBSIZE];
			for (k=0;k<MBSIZE;k++)
			{		
				imgPtmp[k]=new unsigned char[MBSIZE];
			    memset(imgPtmp[k],0,MBSIZE*sizeof(unsigned char));//ĞÂ½¨ÄÚ´æÇøÇEE
			}

			for (k=0;k<MBSIZE;k++)
			{			
				imgItmp[k]=new unsigned char[MBSIZE];
                memset(imgItmp[k],0,MBSIZE*sizeof(unsigned char));//ĞÂ½¨ÄÚ´æÇøÇEE
			}

            for(int blkX=0;blkX<MBSIZE;blkX++)
			{
	    		for(int blkY=0;blkY<MBSIZE;blkY++)
				{
					int MAX1=0;
					//ÎªÁË±ÜÃâÒç³E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!¹ıÁËÔò²¹ÉÏ±ßÔµ
					MAX1 =((i+blkY)*imgWidth+(j+blkX)<=(imgWidth*imgHeight-1))?(i+blkY)*imgWidth+(j+blkX):(imgWidth*imgHeight-1); 
                    *(imgPtmp[blkX]+blkY) = *(imgP+MAX1);
		    	    *(imgItmp[blkX]+blkY) = *(imgI+MAX1);
				}
			}
			   //     costs(5) = costFuncMAD(imgP(i:i+MBSIZE-1,j:j+MBSIZE-1), ...
                             //       imgI(i:i+MBSIZE-1,j:j+MBSIZE-1),MBSIZE);
			//Ñ­»·Ç°ÏÈ¼ÆËã²Î¿¼ÖĞĞÄ´¦¿ªÏE
            costs[4] = costFuncMAD(imgPtmp,imgItmp,MBSIZE);
            computations = computations + 1;

    //**************************************LDSP³õ´ÎËÑËE***************************************//
		    for(k=0;k<9;k++)
			{
				int refBlkVer,refBlkHor;
				refBlkVer = y + LDSP[k].y;//²Î¿¼¿éµÄĞĞ¡¢´¹Ö±×ø±E
				refBlkHor = x + LDSP[k].x;//²Î¿¼¿éµÄÁĞ¡¢Ë®Æ½×ø±E
				if( refBlkVer < 0 || refBlkVer+MBSIZE > imgHeight || refBlkHor < 0 || refBlkHor+MBSIZE > imgWidth)
				continue;
				if (k == 4)
                continue;
			    for(int blkX2=0;blkX2<MBSIZE;blkX2++)
				{
	               for(int blkY2=0;blkY2<MBSIZE;blkY2++)
				   {
					  int MAX1=0,MAX2=0;
					//ÎªÁË±ÜÃâÒç³E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!¹ıÁËÔò²¹ÉÏ±ßÔµ
					  MAX1 =((i+blkY2)*imgWidth+(j+blkX2)<=(imgWidth*imgHeight-1))?((i+blkY2)*imgWidth+(j+blkX2)):(imgWidth*imgHeight-1); 
				      MAX2 =(((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2))<=(imgWidth*imgHeight-1))?((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2)):(imgWidth*imgHeight-1); 
                      *(imgPtmp[blkX2]+blkY2) = *(imgP+MAX1);
			          *(imgItmp[blkX2]+blkY2) = *(imgI+MAX2);
					}
				}
                costs[k] = costFuncMAD(imgPtmp,imgItmp,MBSIZE);
                computations = computations + 1;
			}
//******************************Ò»´ÎÈ«LDSPËÑË÷½áÊE***************************************//

	//µÚÒ»´Îµ÷ÓÃ¼ÆËã³õÊ¼ËÑË÷@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//
			minSearch(costs,9,cost,point);
            // ÁâĞÎÖĞÑEDSPFlag ±E¾ÖÃ1---ÀúŞÛÉÏÃ»ÓĞÎ»ÒÆµÄ»°Ó¦¸ÃÍE«ÖØºÏ£¬SDSPFlagÊ¼ÖÕÎª1,point[0]²»ÊÇ4¾ÍÊÇ2
            if (point[0] == 4)
                SDSPFlag = 1;
            else
			{
			    SDSPFlag = 0;
                if ( abs(LDSP[point[0]].x) == abs(LDSP[point[0]].y) )
                   cornerFlag = 0;
                else
				   cornerFlag = 1; //½Çµã±E¾
                xLast = x;
                yLast = y;
			    //ËÑË÷ÖĞĞÄÒÆµ½ĞÂµÄÖĞĞÄ
                x = x + LDSP[point[0]].x;
                y = y + LDSP[point[0]].y;
                for(int index=0;index<9;index++)
				{
				    costs[index]=65537;
				}
					 //ÖĞĞÄÖµ±ä³É×ûì¡Öµ
                costs[4] = cost[0];
			}
		//**********************************LDSPÑ­»·ËÑËE****************************************//
            while (SDSPFlag == 0)//LDSPËÑË÷ÖÁSDSPFlag =1ÎªÖ¹,·Ö³É½ÇµãºÍ·Ç½ÇµãÁ½ÀE
			{
				if (cornerFlag == 1)
					//ÅÅ³ı·Ç½ÇµãºÍÖĞĞÄµã£¬¼ÆËã½Çµã´¦µÄ¿ªÏE
                for(int k=0;k<9;k++)
				{      
					int refBlkVer,refBlkHor;
					refBlkVer = y + LDSP[k].y;   
                    refBlkHor = x + LDSP[k].x;   
                    if( refBlkVer < 0 || refBlkVer+MBSIZE > imgHeight || refBlkHor < 0 || refBlkHor+MBSIZE > imgWidth)
                        continue;
                    if (k == 4)
                        continue;      
                    if ( refBlkHor >= xLast - 1  && refBlkHor <= xLast + 1 && refBlkVer >= yLast - 1  && refBlkVer <= yLast + 1 )//·Ç½Çµã×é³ÉµÄÕı·½ĞÎÇøÓòÄÚ
                        continue;// ÒÆ³ıÕı·½ĞÎÇøÓòÄÚµÄÈı¸öµE
                    else if (refBlkHor < j-P || refBlkHor > j+P || refBlkVer < i-P || refBlkVer > i+P)//ËÑË÷´°¿ÚÖ®ÍE
                        continue;
                    else
					{   
			            for(int blkX2=0;blkX2<MBSIZE;blkX2++)
						{
	                        for(int blkY2=0;blkY2<MBSIZE;blkY2++)
							{
							   int MAX1=0,MAX2=0;
					       //ÎªÁË±ÜÃâÒç³E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!¹ıÁËÔò²¹ÉÏ±ßÔµ
					           MAX1 =((i+blkY2)*imgWidth+(j+blkX2)<=(imgWidth*imgHeight-1))?(i+blkY2)*imgWidth+(j+blkX2):(imgWidth*imgHeight-1); 
				               MAX2 =(((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2))<=(imgWidth*imgHeight-1))?((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2)):(imgWidth*imgHeight-1); 
                               *(imgPtmp[blkX2]+blkY2) = *(imgP+MAX1);
			                   *(imgItmp[blkX2]+blkY2) = *(imgI+MAX2);
							}
						}
                        costs[k] =  costFuncMAD(imgPtmp,imgItmp,MBSIZE);//Ò»°ãÇé¿ö¼ÆËEµE
		            	 //   costs[k] = costFuncMAD(imgP(i:i+MBSIZE-1,j:j+MBSIZE-1), imgI(refBlkVer:refBlkVer+MBSIZE-1, refBlkHor:refBlkHor+MBSIZE-1), MBSIZE);
                        computations = computations + 1;
					}
				}     
                else//·Ç½Çµã£¬4ÖÖÇé¿öÌÖÂÛ
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
					       //ÎªÁË±ÜÃâÒç³E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!¹ıÁËÔò²¹ÉÏ±ßÔµ
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
                            ;  //Í¼Ïñ±ßÔµÖ®Íâ£¬Ìø³E
                            else if (refBlkHor < j-P || refBlkHor > j+P || refBlkVer < i-P  || refBlkVer > i+P)
                            ;  //ËÑË÷´°¿ÚÖ®Íâ£¬Ìø³E
                            else
							{       
			                    for(int blkX2=0;blkX2<MBSIZE;blkX2++)
								{
	                                for(int blkY2=0;blkY2<MBSIZE;blkY2++)
									{
										int MAX1=0,MAX2=0;
					       //ÎªÁË±ÜÃâÒç³E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!¹ıÁËÔò²¹ÉÏ±ßÔµ
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
                            ; //Í¼Ïñ±ßÔµÖ®Íâ£¬Ìø³E
                            else if (refBlkHor < j-P || refBlkHor > j+P || refBlkVer < i-P  || refBlkVer > i+P)
                            ; //ËÑË÷´°¿ÚÖ®Íâ£¬Ìø³E
                            else
							{   
			                    for(int blkX2=0;blkX2<MBSIZE;blkX2++)
								{
	                               for(int blkY2=0;blkY2<MBSIZE;blkY2++)
								   {
									    int MAX1=0,MAX2=0;
					       //ÎªÁË±ÜÃâÒç³E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!¹ıÁËÔò²¹ÉÏ±ßÔµ
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
					       //ÎªÁË±ÜÃâÒç³E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!¹ıÁËÔò²¹ÉÏ±ßÔµ
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
                            ;//Í¼Ïñ±ßÔµÖ®Íâ£¬Ìø³E
                            else if (refBlkHor < j-P || refBlkHor > j+P || refBlkVer < i-P  || refBlkVer > i+P)
                            ; //ËÑË÷´°¿ÚÖ®Íâ£¬Ìø³E
                            else
							{        
			                    for(int blkX2=0;blkX2<MBSIZE;blkX2++)
								{
	                                for(int blkY2=0;blkY2<MBSIZE;blkY2++)
									{
									   int MAX1=0,MAX2=0;
					       //ÎªÁË±ÜÃâÒç³E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!¹ıÁËÔò²¹ÉÏ±ßÔµ
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
                            ;//Í¼Ïñ±ßÔµÖ®Íâ£¬Ìø³E
                            else if (refBlkHor < j-P || refBlkHor > j+P || refBlkVer < i-P  || refBlkVer > i+P)
                            ;//ËÑË÷´°¿ÚÖ®Íâ£¬Ìø³E
                            else
							{        
			                    for(int blkX2=0;blkX2<MBSIZE;blkX2++)
								{
	                                for(int blkY2=0;blkY2<MBSIZE;blkY2++)
									{
										int MAX1=0,MAX2=0;
					       //ÎªÁË±ÜÃâÒç³E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!¹ıÁËÔò²¹ÉÏ±ßÔµ
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
					       //ÎªÁË±ÜÃâÒç³E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!¹ıÁËÔò²¹ÉÏ±ßÔµ
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
                            ;//Í¼Ïñ±ßÔµÖ®Íâ£¬Ìø³E
                            else if (refBlkHor < j-P || refBlkHor > j+P || refBlkVer < i-P  || refBlkVer > i+P)
                            ;//ËÑË÷´°¿ÚÖ®Íâ£¬Ìø³E
                            else
							{      
			                    for(int blkX2=0;blkX2<MBSIZE;blkX2++)
								{
	                                for(int blkY2=0;blkY2<MBSIZE;blkY2++)
									{
										int MAX1=0,MAX2=0;
					       //ÎªÁË±ÜÃâÒç³E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!¹ıÁËÔò²¹ÉÏ±ßÔµ
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
                            ;//Í¼Ïñ±ßÔµÖ®Íâ£¬Ìø³E
                            else if (refBlkHor < j-P || refBlkHor > j+P || refBlkVer < i-P  || refBlkVer > i+P)
                            ;//ËÑË÷´°¿ÚÖ®Íâ£¬Ìø³E
                            else
							{        
			                    for(int blkX2=0;blkX2<MBSIZE;blkX2++)
								{
	                                for(int blkY2=0;blkY2<MBSIZE;blkY2++)
									{
										int MAX1=0,MAX2=0;
					       //ÎªÁË±ÜÃâÒç³E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!¹ıÁËÔò²¹ÉÏ±ßÔµ
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
					       //ÎªÁË±ÜÃâÒç³E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!¹ıÁËÔò²¹ÉÏ±ßÔµ
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
                            ; //Í¼Ïñ±ßÔµÖ®Íâ£¬Ìø³E
                            else if (refBlkHor < j-P || refBlkHor > j+P || refBlkVer < i-P  || refBlkVer > i+P)
                            ;//ËÑË÷´°¿ÚÖ®Íâ£¬Ìø³E
                            else
							{              
			                    for(int blkX2=0;blkX2<MBSIZE;blkX2++)
								{
	                                for(int blkY2=0;blkY2<MBSIZE;blkY2++)
									{
										int MAX1=0,MAX2=0;
					       //ÎªÁË±ÜÃâÒç³E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!¹ıÁËÔò²¹ÉÏ±ßÔµ
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
                            ;//Í¼Ïñ±ßÔµÖ®Íâ£¬Ìø³E
                            else if (refBlkHor < j-P || refBlkHor > j+P || refBlkVer < i-P  || refBlkVer > i+P)
                            ;//ËÑË÷´°¿ÚÖ®Íâ£¬Ìø³E
                            else
							{             
			                   for(int blkX2=0;blkX2<MBSIZE;blkX2++)
							   {
	                              for(int blkY2=0;blkY2<MBSIZE;blkY2++)
								  {
									   int MAX1=0,MAX2=0;
					       //ÎªÁË±ÜÃâÒç³E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!¹ıÁËÔò²¹ÉÏ±ßÔµ
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
  
	//µÚ¶ş´Îµ÷ÓÃ¼ÆËãLDSPÔËËãÍEÉ@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//	
		     	minSearch(costs,9,cost,point);
                if (point[0] == 4)
                   SDSPFlag = 1;
                else
				{
			       SDSPFlag = 0;
                   if ( abs(LDSP[point[0]].x) == abs(LDSP[point[0]].y) )
                      cornerFlag = 0;
                   else
					   cornerFlag = 1; //½Çµã±E¾
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
			}//while Ñ­»·½áÊE
//************************************* ½øÈESDSP ¼ÆËE**********************************************//
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
					//ÎªÁË±ÜÃâÒç³E!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!¹ıÁËÔò²¹ÉÏ±ßÔµ
					  MAX1 =((i+blkY2)*imgWidth+(j+blkX2)<=(imgWidth*imgHeight-1))?(i+blkY2)*imgWidth+(j+blkX2):(imgWidth*imgHeight-1); 
				      MAX2 =(((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2))<=(imgWidth*imgHeight-1))?((refBlkVer+blkY2)*imgWidth+(refBlkHor+blkX2)):(imgWidth*imgHeight-1); 
                      *(imgPtmp[blkX2]+blkY2) = *(imgP+MAX1);
			          *(imgItmp[blkX2]+blkY2) = *(imgI+MAX2);
					}
				}
                costsSDSP[k] =  costFuncMAD(imgPtmp,imgItmp,MBSIZE);
                computations = computations + 1;
                   
            }
		//µÚÈı´Îµ÷ÓÃÓÃÓÚSDSP@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@//		
            minSearch(costsSDSP,5,cost,point);
            x = x + SDSP[point[0]].x;
            y = y + SDSP[point[0]].y;  
         	//ÅĞ¶ÏÊÇ·ñĞ´Òç³E
			if(mbCount>vectorsNum)
				mbCount = vectorsNum;
            vectors[0][mbCount-1] = y - i;    // ÔË¶¯Ê¸Á¿µÄĞĞ×ø±E
            vectors[1][mbCount-1] = x - j;    // ÔË¶¯Ê¸Á¿µÄÁĞ×ø±E
			//Ä£¿é¼ÆÊı¼ÓÒ»
            mbCount = mbCount + 1;
       //     costs[3][3]={{65537,65537,65537},{65537,65537,65537},{65537,65537,65537}};
			//½«¿ªÏúº¯Êı¸´Ô­---ÓĞÆäËû¼òµ¥·½·¨Ã´£¿
			for(k=0;k<5;k++)  
			{
				costsSDSP[k]=65537;
			}	 		
            //»¹Ô­costsÖµ
		    for(k=0;k<9;k++)
			{
		        costs[k]=65537;
			}
			//ÊÍ·ÅÄÚ´E
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
