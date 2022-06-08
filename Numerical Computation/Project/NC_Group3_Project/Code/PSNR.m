function [psnr]=PSNR(p1,p2)
%p1,p2 are 2 different pictures
%m is the length of the picture, n is the width of the picture, k is the
%dimensions of picture( if k=2, then picture is black and white, if k=3,
%then picture is color
[m,n,k]=size(p1);
[mm,nn,kk]=size(p2);
m=min(m,mm);
n=min(n,nn);
k=min(k,kk);
p1=p1(1:m,1:n,1:k);
p2=p2(1:m,1:n,1:k);
%calculate the value of psnr
psnr=0;
for i=1:k
    psnr=psnr+10*log10(225^2/mse(p1(:,:,i)-p2(:,:,i)));%2^8=225
end
psnr=psnr/k;