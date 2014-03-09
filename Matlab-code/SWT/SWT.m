load noiswom
%X = imread('livingroom_LR_1.tif');
X = double(X);
  % 6. Perform a multilevel Stationary Wavelet Decomposition.
 % To perform a decomposition at level 3 of the image (again using the db1 wavelet), type
%  X = imread('cameraman_LR_2.tif');
%  X = double(X);
 [swa,swh,swv,swd] = swt2(X,3,'db1');
%  clear A0 A1 D1 H1 V1 err nulcfs;
 
colormap(map)

% mzero = zeros(size(swd));
% A = mzero;
% A(:,:,3) = iswt2(swa,mzero,mzero,mzero,'db1');
% 
% H = mzero; V = mzero;
% D = mzero;
% 
% 
% A(:,:,2) = A(:,:,3) + H(:,:,3) + V(:,:,3) + D(:,:,3);
% A(:,:,1) = A(:,:,2) + H(:,:,2) + V(:,:,2) + D(:,:,2);
% 
 colormap(gray)


thr=[46.12 46.12 46.12];
sorh = 's';
for i=1:3
   dswh(:,:,i) = wthresh(swh(:,:,i) ,sorh,thr(i));
   dswv(:,:,i)  = wthresh(swv(:,:,i) ,sorh,thr(i));
   dswd(:,:,i)  = wthresh(swd(:,:,i) ,sorh,thr(i));
end
clean = iswt2(swa,dswh,dswv,dswd,'db1');
%colormap(map)
%colormap(gray)
 image(wcodemat(X,192));
%title('原始噪声图象')
image(wcodemat(clean,192));
%title('去噪图象')