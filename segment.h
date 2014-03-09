//��Ե���
void sobel(unsigned char *imgBuf, int width, int height, int biBitCount);
void robot(unsigned char *imgBuf, int width, int height, int biBitCount);
void prewitt(unsigned char *imgBuf, int width, int height, int biBitCount);
void laplacian(unsigned char *imgBuf, int width, int height, int biBitCount);

//��ֵ�ָ�
void ErZhiSegment(unsigned char *imgBuf, int width, int height, int thresh);

//�����ֵ�ָ�
void autoThreshSegment(unsigned char *imgBuf, int width, int height);
//��ֵƽ��
void meanFilter(unsigned char *imgBuf, int width, int height, int biBitCount, 
                int *mask, int masksize);
//��ֵƽ��
void midFilter(unsigned char *imgBuf, int width, int height, int biBitCount,
               int *mask, int masksize);
//ģ��
void Filter(unsigned char *imgBuf, int width, int height, int biBitCount,
               double *mask, int masksize);