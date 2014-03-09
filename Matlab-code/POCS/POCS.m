function POCS(iterNum,LRNum)
psf = fspecial('gaussian',[5,5],1);
weights = psf;
mbSize = 16;
p = 7;

HR  = imread('lena.png');
%HR  = double(HR);
%生成LR图像序列
for i= 1:1:LRNum
    LR{i}= GenLR(HR);
end
ref  = LR{1};
%imshow(ref,[]);
imRow = size(ref,1);
imCol = size(ref,2);

%[x, y] = meshgrid(1:imCol, 1:imRow); 
%[X, Y] = meshgrid(1:imCol*2, 1:imRow*2); 

%upref  = interp2(x,y,double(ref),X./2,Y./2,'linear');
upref  = imresize(ref,2,'bilinear');
upref  = double(upref);
psnrRef = imgPSNR(upref, HR, 255);
imshow(upref,[]),title(sprintf('reference HR,psnrRef=%.2f',psnrRef));




for iter = 1:1:iterNum
    for picNum = 2:1:LRNum

       [motionVect, DScomputations] = motionEstDS(LR{picNum}, ref, mbSize, p);
       imgComp = motionComp(ref, motionVect, mbSize);
       imgComp = imfilter(imgComp,psf,'circular');
                
       %%% Loop over entire (low-res) frame 
       for m2 = 1:imCol, 
           for m1 = 1:imRow, 
           %%% Calculate the residual 
           R = imgComp(m1,m2) - ref(m1,m2); 
           R=double(R);
           n1 = 2*m1;
           n2 = 2*m2;
           
           if ( n1>3 & n1<2*imRow-2 & n2>3 & n2<2*imCol-2 )  %控制了距离边距两
           %%% Calculate new values for the reference frame 
           if (R>1) 
              upref(n1-2:n1+2,n2-2:n2+2) = upref(n1-2:n1+2,n2-2:n2+2) + ... 
              (weights.*(R-1))./sum(sum(weights.^2)); 
           elseif (R<-1) 
              upref(n1-2:n1+2,n2-2:n2+2) = upref(n1-2:n1+2,n2-2:n2+2) + ... 
              (weights.*(R+1))./sum(sum(weights.^2)); 
           end 
           end
           end 
           end
    end 
       

   upref(upref<0) = 0; 
   upref(upref>255) = 255; 
 
end 
psnrPOCS= imgPSNR(upref, HR, 255);
figure,imshow(upref,[]),title(sprintf('POCS method,psnrPOCS=%.2f',psnrPOCS));




