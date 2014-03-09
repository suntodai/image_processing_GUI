function random

HR = imread('livingroom.BMP');
HR = double(HR);
for iter=1:1:8
    SR = imread(strcat(num2str(iter),'POCS¸´Ô­½á¹û40','.bmp')); 
    SR = double(SR);
    x(iter)= iter;
    psnr(iter) = imgPSNR(SR,HR,255);
end
plot(x,psnr,'--rs');