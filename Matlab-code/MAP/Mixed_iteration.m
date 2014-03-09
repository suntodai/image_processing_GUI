%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
% Mixel Iteration 
% --------------- 
%  AUTHOR: Stephen Rose, Maher Khoury 
%    DATE: March 1, 1999 
% PURPOSE: 
%         Iteratively improve the guess of the mixel data based on 
%         the statistics of the image 
% 
% Notes: 
%   -init.m contains the affine transformation parameters 
%   -Assuming a gaussian PSF 
%   -u,v are affine transformation vectors for (x,y) 
%   -mcX,mcY are transformed coordines in mixel frame 
% 
% Variables: 
%   -psfThreshold   = "Maximum Effective Width" for the PSF - a window 
%   -psfSigma       = width for the Gaussian PSF 
%   -NumberOfFrames = Number of pixel frames to consider 
%   -dist           = mixel-pixel distance (matrix from 1 mixel to all pixels) 
%   -weights        = mixel-pixel weights based on Gaussian PSF (matrix as above) 
%   -PixelHat       = matrix containing expected value of every mixel 
%   -ScalarDist     = pixel-mixel distance (scalar - given pixel to given mixel) 
%   -ScalarWeight   = pixel-mixel weight (scalar - as above) 
%   -TopSum         = running sum of top part of equation 
%   -BottomSum      = running sum of bottom part of equation 
%   -Term1Top       = first term on top of iteration equation 
%   -Term2Top       = second term on top of iteration equation 
%   -Term3Top       = third term on top of iteration equation 
%   -miHat=0.0; 
%   -Term1Bottom    = first term on bottom of iteration equation 
%   -Term2Bottom    = second term on bottom of iteration equation 
%   -Term3Bottom    = third term on bottom of iteration equation 
%   -MixelSigma     = previously calculated sqrt(variance) 
%   -PixelSigma     = previously calculated sqrt(variance) 
%   -Lambda         = numerical prefactor (see explanation of method) 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
init; 
psfThreshold = 2.5; 
psfSigma = 1.0; 
NumberOfFrames=5; 
%%%Read in first pixel frame for sizing of matricies 
pixels = double(imread('pixels3200.tif','tif')); 
[x, y] = meshgrid(1:size(pixels,2), 1:size(pixels,1)); 
[X, Y] = meshgrid(1:2.*size(pixels,2), 1:2.*size(pixels,1)); 

%%%Read in previously calculated first guess 
mixels = double(imread('mixels5','tif')); 

%%%Zero out necessary terms (refer to explanation for mathematical 
%%%description of variables) and define known terms 
Term1Top=0.0; 
Term2Top=0.0; 
Term3Top=0.0; 
miHat=0.0; 
Term2Bottom=1; 
Term3Bottom=4*((1/4)*(1/4)); 
MixelSigma=2.75; 
PixelSigma=20; 
Lambda=1; 
VarianceRatio=(MixelSigma.^2)/(PixelSigma.^2); 
PixelHat = zeros(size(pixels,1),size(pixels,2)); 

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
%%% Begin loop (k x l x numframes x n x m) iterations 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
%%%Begin loop over first mixel dimension 
for k=2:(size(mixels,1)-1), 
  disp(k); 
  %%%Begin loop over second mixel dimension 
  for l=2:(size(mixels,2)-1), 
    miHat=(0.25*mixels((k-1),l))+(0.25*mixels((k+1),l))+(0.25*mixels(k,(l-1)))+(0.25* mixels(k,(l+1))); 
    Term2Top=mixels(k,l)-miHat; 
    Term3Top=(0.25*(mixels((k-1),l)-miHat))+(0.25*(mixels((k+1),l)-miHat))+(0.25*(mixels(k,(l-1))-miHat))+(0.25*(mixels(k,(l+1))-miHat)); 
    Term1Top=0.0; 
    Term1Bottom=0.0; 
    %%%Begin loop over number of frames 
    for num=0:NumberOfFrames, 
      if (num < 10); 
        pixels = double(imread(strcat('pixels320',num2str(num),'.tif'))); 
      else 
        pixels = double(imread(strcat('pixels32',num2str(num),'.tif'))); 
      end 
      %%%Calculate affine parameters 
      u = A((num+1),1).*x + A((num+1),2).*y + A((num+1),3); 
      v = A((num+1),4).*x + A((num+1),5).*y + A((num+1),6); 
      mcX = (2.*(x + u))-1; 
      mcY = (2.*(y + v))-1; 
      %%%Figure out PixelHat matrix for this mixel for this frame 
      %%%Begin loop over first pixel dimension 
      for m=1:size(pixels,1), 
        %%%Begin loop over second pixel dimension 
        for n=1:size(pixels,2), 
          %looking at pixel(m,n), go through, add up contributions from all mixels 
          dist = sqrt((mcX(m,n)-X).^2+(mcY(m,n)-Y).^2); 
          dist(dist > psfThreshold) = Inf; 
          weights = (1./(psfSigma.*sqrt(2.*pi))).*exp(-(dist.^2)./(2.*psfSigma.^2)); 
          PixelHat(m,n) = (sum(sum((weights.*mixels))))/(sum(sum(weights))); 
          %now figure out weight of this pixel to the mixel 
          ScalarDist = sqrt((mcX(m,n)-l).^2+(mcY(m,n)-k).^2); 
          ScalarWeight = (1./(psfSigma.*sqrt(2.*pi))).*exp(-(ScalarDist.^2)./(2.*psfSigma.^2)); 
          Term1Top=Term1Top+((VarianceRatio)*(ScalarWeight*(pixels(m,n)-PixelHat(m,n)))); 
          Term1Bottom=Term2Bottom+((VarianceRatio)*(ScalarWeight.^2)); 
        end 
      end 
    end 
    Top = Term1Top + Term2Top + Term3Top; 
    Bottom = Term1Bottom + Term2Bottom + Term3Bottom; 
    DeltaMi=Lambda*Top/Bottom; 
    mixels(k,l)=mixels(k,l)+DeltaMi; 
  end 
end 
imwrite(mixels,gray(256),'mixelsmod.tif','tif') 
  
