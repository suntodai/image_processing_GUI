function iterComp

HR = imread('livingroom.BMP');
HR = double(HR);
for iter=5:5:50
    SR = imread(strcat('POCS��ԭ���',num2str(iter),'.bmp')); 
    SR = double(SR);
    x(iter/5)= iter;
    psnr(iter/5) = imgPSNR(SR,HR,255);
end
plot(x,psnr,'--rs');