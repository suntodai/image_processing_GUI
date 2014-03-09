% use this program to test the motion estimate subprogram
% image_orign1 = imread('F:/registration/HaiChengStreet/haicheng1.jpg');
image_orign1 = imread('livingroom.BMP');
image_orign1 = double(image_orign1);
%subplot(2,3,1),subplot( 'Position', [0, 0.5, 0.33, 0.44]),imshow(image_orign1,[]),title('原图','fontsize',10.5,'fontname','宋体');
image_orign2 = shift(image_orign1,0.8,0.9);
%subplot(2,3,2), subplot( 'Position', [0.33, 0.5, 0.33, 0.44]),imshow(image_orign2,[]), title('位移图像','fontsize',10.5,'fontname','宋体');
image_orign2 = imrotate(image_orign2,0,'bicubic','crop');
% image_orign2 = imread('F:/registration/HaiChengStreet/haicheng4.jpg');
%subplot(2,3,3), subplot( 'Position', [0.66, 0.5, 0.33, 0.44]), imshow(image_orign2,[]), title('位移旋转图像','fontsize',10.5,'fontname','宋体');
% important to make image_orign2 as double,otherwise the image will be look
% black
image_orign2 = double(image_orign2);
image_diff = image_orign1 - image_orign2;
%subplot(2,3,4), subplot( 'Position', [0, 0, 0.33, 0.44]),imshow(image_diff,[]), title('原始差分图像','fontsize',10.5,'fontname','宋体');

[motionVect, DScomputations] = motionEstDS(image_orign2, image_orign1, 16, 9);
%[motionVect, DScomputations] = motionEstTSS(image_orign2, image_orign1, 16, 9);
image_mc = motionComp(image_orign1, motionVect, 16);

% image_mc = imrotate(image_affine,-4,'bicubic','crop');
% image_mc = shift(image_mc,-4,-4);

%subplot(2,3,5), subplot( 'Position', [0.33, 0, 0.33, 0.44]),imshow(image_mc,[]), title('运动补偿后图像','fontsize',10.5,'fontname','宋体');
figure, imshow(image_mc,[]), title('运动补偿后图像','fontsize',10.5,'fontname','宋体');
image_diff2 = image_orign2 - image_mc;
%subplot(2,3,6), subplot( 'Position', [0.66, 0, 0.33, 0.44]), imshow(image_diff2,[]), title('运动补偿后差分图像','fontsize',10.5,'fontname','宋体');
psnr = imgPSNR(double(image_orign2), double(image_mc), 255)
computations = DScomputations
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% use the program to test the estimation error

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% use this program to test the motion estimate subprogram
% image_orign1 = imread('cameraman.tif');
% % 
% image_orign1 = double(image_orign1);
% imshow(image_orign1,[]),title('orign image');
% image_orign2 = shift(image_orign1,0.5,0.5);
% figure, imshow(image_orign2,[]), title('shift image');
% image_orign2 = imrotate(image_orign2,0.5,'bicubic','crop');
% figure, imshow(image_orign2,[]), title('shift+rotation image');
% image_orign2 = double(image_orign2);
% image_diff = image_orign2 - image_orign1;
% figure, imshow(image_diff,[]), title('orign difference image');
% 
% 
% [motionVect, DScomputations] = motionEstDS(image_orign2(:,:,1), image_orign1(:,:,1), 16, 7);
% image_mc = motionComp(image_orign1(:,:,1), motionVect, 16);
% 
% % image_mc = imrotate(image_affine,-4,'bicubic','crop');
% % image_mc = shift(image_mc,-4,-4);
% 
% figure, imshow(image_mc,[]), title('compensated image');
% image_diff2 = image_orign2(:,:,1) - image_mc;
% figure, imshow(image_diff2,[]), title('compensated difference image');
% psnr = imgPSNR(double(image_orign2(:,:,1)), double(image_mc), 255)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%