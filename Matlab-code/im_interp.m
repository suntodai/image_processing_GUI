function im_interp
ref = imread('lena.png');
[x, y] = meshgrid(1:size(ref,2), 1:size(ref,1)); 
[X, Y] = meshgrid(1:2.*size(ref,2), 1:2.*size(ref,1)); 
upref_nearest = interp2(x,y,double(ref),X./2,Y./2,'nearest');
upref_bilinear = interp2(x,y,double(ref),X./2,Y./2,'bilinear');
upref_bicubic = interp2(x,y,double(ref),X./2,Y./2,'bicubic');

imshow(ref,[]); axis image off
set(gca, 'FontSize', 8);
%title('ԭʼͼ��', 'FontSize', 10.5);

figure, imshow(upref_nearest(128:384, 128:384), []); axis image off
set(gca, 'FontSize', 8);
%title('�ڽ���ֵ', 'FontSize', 10.5);

figure, imshow(upref_bilinear(128:384, 128:384), []); axis image off
set(gca, 'FontSize', 8);
%title('˫���Բ�ֵ', 'FontSize', 10.5);

figure, imshow(upref_bicubic(128:384, 128:384), []); axis image off
set(gca, 'FontSize', 8);
%title('˫���β�ֵ','FontSize', 10.5);