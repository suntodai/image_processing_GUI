clc;
clear;
f = fopen('a.dat','r');
im = fread(f,inf);
x = zeros(240,640);
for j = 1:640
    for i= 1:2:479
      x((i+1)/2,j)=mod(im(j+(i-1)*640),8)*2^5+mod(im(j+1+(i-1)*640),8)*2^2;
    end
end

imshow(x,[]);