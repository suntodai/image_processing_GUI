function LRPSNR

HR = imread('livingroom.BMP');
HR = double(HR);
for i=1:1:8
    LR = imread(strcat('��',num2str(i),'��LRͼ','.bmp')); 
    LR = double(LR);
    LR2 = imread(strcat('��',num2str(i),'��LRͼ2','.bmp')); 
    LR2 = double(LR2);
    LR3 = imread(strcat('��',num2str(i),'��LRͼ3','.bmp')); 
    LR3 = double(LR3);
    LR4 = imread(strcat('��',num2str(i),'��LRͼ4','.bmp')); 
    LR4 = double(LR4);
    LRs = imread(strcat('��',num2str(i),'��LRͼs','.bmp')); 
    LRs = double(LRs);
%     %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% ȥ��srand������
%     LR5 = imread(strcat('��',num2str(i),'��LRͼ5','.bmp')); 
%     LR5 = double(LR5);
%     LR6 = imread(strcat('��',num2str(i),'��LRͼ6','.bmp')); 
%     LR6 = double(LR6);
%     LR7 = imread(strcat('��',num2str(i),'��LRͼ7','.bmp')); 
%     LR7 = double(LR7);
    x(i)= i;
    psnr(i) = imgPSNR(LR,HR,255);
    psnr2(i) = imgPSNR(LR2,HR,255);
    psnr3(i) = imgPSNR(LR3,HR,255);
    psnr4(i) = imgPSNR(LR4,HR,255);
    psnrs(i) = imgPSNR(LRs,HR,255);
%     psnr5(i) = imgPSNR(LR4,HR,255);
%     psnr6(i) = imgPSNR(LR4,HR,255);
%     psnr7(i) = imgPSNR(LR4,HR,255);
end
plot(x,psnr,'--rs');hold on
plot(x,psnr2,'*-b');hold on
plot(x,psnr3,'o:g');hold on
plot(x,psnr4,'+:k');hold on
plot(x,psnrs,'p-m');
% plot(x,psnr5,'d-y');hold on
% plot(x,psnr6,'p-m');hold on
% plot(x,psnr7,'h-c');hold on