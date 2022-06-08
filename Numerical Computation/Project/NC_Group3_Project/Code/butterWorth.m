function butterWorth(filepath,noiseType)
img = imread(filepath);
img_noise = imnoise(img,noiseType);
%seperate the original image into 3 channels
R = img_noise(:,:,1);
G = img_noise(:,:,2);
B = img_noise(:,:,3);
%apply the lowpass filter that we implemented before on the 3 channels
%repectively
R1 = butterworthSub(R);
G1 = butterworthSub(G);
B1 = butterworthSub(B);
%combine the 3 channels to obtain the image after de-nosing
RGB(:,:,1)=R1(:,:,1);
RGB(:,:,2)=G1(:,:,1);
RGB(:,:,3)=B1(:,:,1);

figure();
subplot(1,3,1);
imshow(img);
title('original picture');

subplot(1,3,2);
imshow(img_noise);
title('after adding noise');

subplot(1,3,3);
imshow(RGB);
title('after processing');