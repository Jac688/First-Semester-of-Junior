function [img] = lowpassG(image)
    d0=150;  %cutoff frequency
    [M ,N]=size(image);

    img_f = fft2(double(image));%apply FT to get frequency
    img_f=fftshift(img_f);  %shift to the center

    m_mid=floor(M/2);%the coordinates of the center
    n_mid=floor(N/2);  

    h = zeros(M,N);%initialize a matrix for constructing the Gaussian lowpass filter
    for i = 1:M
        for j = 1:N
            d = ((i-m_mid)^2+(j-n_mid)^2);
            h(i,j) = exp(-d/(2*(d0^2)));      
        end
    end

    img_lpf = h.*img_f;

    img_lpf=ifftshift(img_lpf);    %shift what shift to the center previously back
    img_lpf=uint8(real(ifft2(img_lpf)));  %inverse Fourier transform and take the real part
    
    img = img_lpf;
end