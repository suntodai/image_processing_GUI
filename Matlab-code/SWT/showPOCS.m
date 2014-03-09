POCS = imread('SJPOCS.tif');
imshow(POCS(180:260,320:480),[]);
POCSSW = imread('SJPOCSSW.tif');
figure,imshow(POCSSW(180:260,320:480),[]);
POCSCanny = imread('SJPOCSCanny.tif');
figure,imshow(POCSCanny(180:260,320:480),[]);