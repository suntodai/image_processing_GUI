//��̬ѧ����
//��ֵ��ʴ
void Terode(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int *mask);
//��ֵ����
void Texpand(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int *mask);
//��ֵ��ʴ
void GrayErosion(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int *mask);
//��ֵ����
void GrayDilation(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int *mask);
//��̬ѧ�ݶ�
void MorphGrad(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int *mask);
//������
void TopHatPeak(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int *mask);
//���ȼ��
void TopHatVally(LPBYTE lpIn,LPBYTE lpOut,int imgWidth,int imgHeight,int *mask);

