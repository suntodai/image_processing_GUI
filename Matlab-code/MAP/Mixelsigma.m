%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
% MixelSigma 
% ---------- 
%  AUTHOR: Stephen Rose, Maher Khoury 
%    DATE: March 1, 1999 
% PURPOSE: 
%         Calculate the variance of the mixels from the expected 
%         values based on one-quarter weighting from cardinal 
%         neighbors 
% 
% Notes: 
%   -once MixelDiff is found, the value of the variance is found graphically 
% 
% Variables: 
%   -AvgMixel       = just to see the mean value of the mixels 
%   -miHat          = expected mixel value based on cardinal neighbors 
%   -MixelDiff      = difference between expected mxiel value and true mixel value 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% 
mixels = double(imread('mixelstempfinal.bmp')); 
AvgMixel=mean(mean(mixels)); 
MixelDiff = zeros(size(mixels,1)-2,size(mixels,2)-2); 
for k=2:(size(mixels,1)-1), 
  for l=2:(size(mixels,2)-1), 
    miHat=(0.25*mixels((k-1),l))+(0.25*mixels((k+1),l))+(0.25*mixels(k,(l-1)))+(0.25* mixels(k,(l+1))); 
    MixelDiff(k-1,l-1)=mixels(k,l)-miHat; 
  end 
end 
%%%Look at data 
hist(MixelDiff(:),[-15:0.5:15]) 

%%%Read off this value for test dollar bill test image 
MixelSigma=2.75; 
