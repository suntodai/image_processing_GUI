%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
% InitalComposite 
% --------------- 
%  AUTHOR: Stephen Rose, Maher Khoury 
%    DATE: March 1, 1999 
% PURPOSE: 
%         Calculate the initial guess of the mixels from the pixel 
%         values from all frames 
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
%   -dist           = mixel-pixel distance 
%   -weights        = mixel-pixel weights based on Gaussian PSF 
%   -TopSum         = running sum of top part of equation 
%   -BottomSum      = running sum of bottom part of equation 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
init; 
psfThreshold = 2.5; 
psfSigma = 1.0; 
NumberOfFrames=5; 
%%%Read in first pixel frame for sizing of matricies 
pixels = double(imread('pixels3200.tif','tif')); 
[x, y] = meshgrid(1:size(pixels,2), 1:size(pixels,1)); 
[X, Y] = meshgrid(1:2.*size(pixels,2), 1:2.*size(pixels,1)); 
mixels = zeros(2*size(pixels,1),2*size(pixels,2)); 
TopSum = zeros(2*size(pixels,1),2*size(pixels,2)); 
BottomSum = zeros(2*size(pixels,1),2*size(pixels,2)); 

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
%%% Loop over all pixel frames 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
for num = 0:NumberOfFrames, 
  if (num < 10); 
      pixels = double(imread(strcat('pixels320',num2str(num),'.tif'))); 
    else 
      pixels = double(imread(strcat('pixels32',num2str(num),'.tif'))); 
  end 

  %%%Calculate affine transformation parameters for this frame 
  u = A((num+1),1).*x + A((num+1),2).*y + A((num+1),3); 
  v = A((num+1),4).*x + A((num+1),5).*y + A((num+1),6); 

  %%%Calculate the coordinates of the motion compensated pixels 
  mcX = (2.*(x + u))-1; 
  mcY = (2.*(y + v))-1; 

  %Loop over all mixels for mixel contribution from these pixels 
  for k=1:size(mixels,1), 
    disp(k); 
    for l=1:size(mixels,2), 
      dist = sqrt((mcX-l).^2+(mcY-k).^2); 
      dist(dist > psfThreshold) = Inf; 
      weights = (1./(psfSigma.*sqrt(2.*pi))).*exp(-(dist.^2)./(2.*psfSigma.^2)); 
      TopSum(k,l) = TopSum(k,l) + (sum(sum(pixels.*weights))); 
      BottomSum(k,l) = BottomSum(k,l) + (sum(sum(weights))); 
    end 
  end 
end 

%%%divide out for mixel values 
mixels = TopSum./BottomSum; 
  
