function [img] = butterworthSub(image)
f=double(image);   
g=fft2(f);
g=fftshift(g);
g1=fftshift(fft2(double(image)));%apply Fourier transform
[M,N,~]=size(g1);%size of the image
nn=2;%n=2
d0=30;%cutoff frequency
m=floor(M/2);n=floor(N/2);%calculate the position of the center
for i=1:M
    for j=1:N
        %use the transfer function for Butterworth lowpass filter to
        %construct matrix to de-noise
        d=sqrt((i-m)^2+(j-n)^2);
        h=1/(1+0.414*(d/d0)^(2*nn));
        result(i,j)=h*g(i,j);
    end
end
result=ifftshift(result);
img=ifft2(result);
img=uint8(real(img));