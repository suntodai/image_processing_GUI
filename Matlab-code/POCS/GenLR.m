function LR = GenLR(im)
im = im2double(im);%不能用double
%imshow(im,[]);title('原始图像');

Pvariance=[0.005 0.015 0.025 0.035 0.045 0.055 0.065 0.075 0.0087 0.095];
Pangle   =[0.005 0.015 0.025 0.035 0.045 0.055 0.065 0.075 0.085 0.095... 
                        -0.005 -0.015 -0.025 -0.035 -0.045 -0.055 -0.065 -0.075 -0.085 -0.095];
PshiftX  =[0.05 0.15 0.25 0.35 0.45,0.55 0.65 0.75 0.85 0.95...
                        -0.05 -0.15 -0.25 -0.35 -0.45 -0.55 -0.65 -0.75 -0.85 -0.95]; 
PshiftY  =[0.05 0.15 0.25 0.35 0.45,0.55 0.65 0.75 0.85 0.95...
                        -0.05 -0.15 -0.25 -0.35 -0.45 -0.55 -0.65 -0.75 -0.85 -0.95]; 
                    
rand1 = mod(floor(100*rand(1,1)),10)+1;    
rand2 = mod(floor(100*rand(1,1)),20)+1;
rand3 = mod(floor(100*rand(1,1)),20)+1;
rand4 = mod(floor(100*rand(1,1)),20)+1;

imRow = size(im,1);
imCol = size(im,2);

% variance = Pvariance(rand1);
% angle    = 10*Pangle(rand2);
% shiftX  =  10*PshiftX(rand3);
% shiftY  =  10*PshiftY(rand4);
variance = 0.01;
angle    = 5;
shiftX  =  5;
shiftY  =  5;


imNoise = imnoise(im,'gaussian',0,variance);
%figure,imshow(imNoise,[]);title('加噪之后的图像');

psf = fspecial('gaussian',[5,5],1);
imBlur = imfilter(imNoise,psf,'circular');
%figure,imshow(imBlur,[]);title('高斯模糊后的图像');

imRot= imrotate(imBlur,angle);
%figure, imshow(imRot,[]);title('旋转之后图像');

imShift = shift(imRot,shiftX,shiftY);
%figure,imshow(imShift,[]);title('位移之后的图像');

imZoom = imresize(imShift,[imRow/2,imCol/2],'bilinear');
%figure,imshow(imZoom,[]);title('缩放之后的图像');

LR = im2uint8(imZoom);
%LR = (imZoom);

