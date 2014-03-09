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

% SR1 = imread(strcat('housePOCS',num2str(50),'hn','.tif')); 
% SR11 = imread(strcat('housePOCS',num2str(50),'h','.tif')); 
% SR111 = imread(strcat('housePOCS',num2str(50),'hedge1.1','.tif')); 
% SR1= double(SR1);
% SR11 = double(SR11);
% SR111 = double(SR111);
% PSNR_LR = imgPSNR(SR1,HR1,255)
% PSNR_Denoise = imgPSNR(SR11,HR1,255)
% PSNR_Canny = imgPSNR(SR111,HR1,255)

SR2 = imread(strcat('cameramanPOCS',num2str(50),'noise0.005','.tif')); 
SR22 = imread(strcat('cameramanPOCS',num2str(50),'SW','.tif')); 
SR222 = imread(strcat('cameramanPOCS',num2str(50),'canny1.1','.tif')); 
SR2= double(SR2);imshow(SR2,[])
SR22 = double(SR22);figure, imshow(SR22,[])
SR222 = double(SR222);figure,imshow(SR222,[])
PSNR2_LR = imgPSNR(SR2,HR2,255)
PSNR2_Denoise = imgPSNR(SR22,HR2,255)
PSNR2_Canny = imgPSNR(SR222,HR2,255)
% 
% SR3 = imread(strcat('livingroomPOCS',num2str(50),'.tif')); 
% SR33 = imread(strcat('livingroomPOCS',num2str(50),'SW','.tif')); 
% SR3= double(SR3);
% SR33 = double(SR33);
% PSNR3 = imgPSNR(SR3,HR3,255)
% PSNRSW3 = imgPSNR(SR33,HR3,255)
% for iter=4:1:10
%     SR1 = imread(strcat('housePOCS',num2str(iter),'.tif')); 
%     SR1 = double(SR1);
%     SR2 = imread(strcat('cameramanPOCS',num2str(iter),'.tif')); 
%     SR2 = double(SR2);
%     SR3 = imread(strcat('livingroomPOCS',num2str(iter),'.tif')); 
%     SR3 = double(SR3);
%     x(iter-3)= iter;
%     psnr1(iter-3) = imgPSNR(SR1,HR1,255);
%     psnr2(iter-3) = imgPSNR(SR2,HR2,255);
%     psnr3(iter-3) = imgPSNR(SR3,HR3,255);
% end
% plot(x,psnr1,'--rs');hold on
% plot(x,psnr2,'-bd');hold on
% plot(x,psnr3,':mo');hold on;legend('house','cameraman','livingroom')
