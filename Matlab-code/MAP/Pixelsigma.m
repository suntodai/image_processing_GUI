METHOD 1 - using only pixel data 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
% PixelSigma 
% ---------- 
%  AUTHOR: Stephen Rose, Maher Khoury 
%    DATE: March 1, 1999 
% PURPOSE: 
%         Calculate the variance of the pixels from the expected 
%         values based on one-quarter weighting from cardinal 
%         neighbors 
% 
% Notes: 
%   -once PixelDiff is found, the value of the variance is found graphically 
% 
% Variables: 
%   -AvgPixel       = just to see the mean value of the pixels 
%   -piHat          = expected pixel value based on cardinal neighbors 
%   -PixelDiff      = difference between expected pixel value and true pixel value 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
pixels = double(imread('sframe00.tif','tif')); 
AvgPixel=mean(mean(pixels)); 
PixelDiff = zeros(size(pixels,1)-2,size(pixels,2)-2); 
for k=2:(size(pixels,1)-1), 
  for l=2:(size(pixels,2)-1), 
piHat=(0.25*pixels((k-1),l))+(0.25*pixels((k+1),l))+(0.25*pixels(k,(l-1)))+(0.25*pixels(k,(l+1))); 
    PixelDiff(k-1,l-1)=pixels(k,l)-piHat; 
  end 
end 
%%%Look at data 
hist(PixelDiff(:),[-15:0.5:15]) 

%%%Read off this value for test dollar bill test image 
PixelSigma=20; 

METHOD 2 - using Intial Guess mixel data 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
% PixelSigma 
% ---------- 
%  AUTHOR: Stephen Rose, Maher Khoury 
%    DATE: March 1, 1999 
% PURPOSE: 
%         Calculate the variance of the pixels from the expected 
%         values based on one-quarter weighting from cardinal 
%         neighbors 
% 
% Notes: 
%   -init.m contains the affine transformation parameters 
%   -Assuming a gaussian PSF 
%   -u,v are affine transformation vectors for (x,y) 
%   -mcX,mcY are transformed coordines in mixel frame 
%   -once PixelDiff is found, the value of the variance is found graphically 
% 
% Variables: 
%   -psfThreshold   = "Maximum Effective Width" for the PSF - a window 
%   -psfSigma       = width for the Gaussian PSF 
%   -NumberOfFrames = Number of pixel frames to consider 
%   -dist           = mixel-pixel distance 
%   -weights        = mixel-pixel weights based on Gaussian PSF 
%   -TopSum         = running sum of top part of equation 
%   -BottomSum      = running sum of bottom part of equation 
%   -AvgPixel       = just to see the mean value of the pixels 
%   -piHat          = expected pixel value based on cardinal neighbors 
%   -PixelDiff      = difference between expected pixel value and true pixel value 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
init; 
psfThreshold = 5.0; 
psfSigma = 1.0; 
pixels = double(imread('sframe00.tif','tif')); 
mixels = double(imread('mixelstempfinal.bmp')); 
num=0; 
[x, y] = meshgrid(1:size(pixels,2), 1:size(pixels,1)); 
[X, Y] = meshgrid(1:2.*size(pixels,2), 1:2.*size(pixels,1)); 
u = A((num+1),1).*x + A((num+1),2).*y + A((num+1),3); 
v = A((num+1),4).*x + A((num+1),5).*y + A((num+1),6); 
%%% Calculate the coordinates of the motion compensated pixels 
mcX = (2.*(x + u))-1; 
mcY = (2.*(y + v))-1; 
AvgPixel = mean(mean(pixels)); 
PixelHat = zeros(size(pixels,1),size(pixels,2)); 
PixelDiff = zeros(size(pixels,1),size(pixels,2)); 

for m=1:size(pixels,1), 
  disp(m) 
  for n=1:size(pixels,2), 
    %%%looking at pixel(m,n), go through, add up contributions from all mixels 
    dist = sqrt((mcX(m,n)-X).^2+(mcY(m,n)-Y).^2); 
    dist(dist > psfThreshold) = Inf; 
    weights = (1./(psfSigma.*sqrt(2.*pi))).*exp(-(dist.^2)./(2.*psfSigma.^2)); 
    PixelHat(m,n) = (sum(sum((weights.*mixels))))/(sum(sum(weights))); 
  end 
end 
PixelDiff=PixelHat-pixels; 

%%%Look at data 
hist(PixelDiff(:),[-50:5:50]) 

%%%Read off this value for test dollar bill test image 
PixelSigma=22; 
  
