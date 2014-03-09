function iterComp

HR1 = imread('house.bmp');
HR1 = double(HR1);
HR1 = imresize(HR1,0.5);
HR2 = imread('cameraman.bmp');
HR2 = double(HR2);
HR2 = imresize(HR2,0.5);
HR3 = imread('livingroom.bmp');
HR3 = double(HR3);
HR3 = imresize(HR3,0.5);
for iter=4:1:10
    SR1 = imread(strcat('housePOCS',num2str(iter),'.tif')); 
    SR1 = double(SR1);
    SR2 = imread(strcat('cameramanPOCS',num2str(iter),'.tif')); 
    SR2 = double(SR2);
    SR3 = imread(strcat('livingroomPOCS',num2str(iter),'.tif')); 
    SR3 = double(SR3);
    x(iter-3)= iter;
    psnr1(iter-3) = imgPSNR(SR1,HR1,255);
    psnr2(iter-3) = imgPSNR(SR2,HR2,255);
    psnr3(iter-3) = imgPSNR(SR3,HR3,255);
end

plot(x,psnr1,'--rs');axis([4 10 20 26]); hold on
plot(x,psnr2,'-bd');hold on
plot(x,psnr3,':mo');hold on;legend('house','cameraman','livingroom')
