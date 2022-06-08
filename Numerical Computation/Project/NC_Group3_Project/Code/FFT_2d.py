import numpy as np
import matplotlib.pyplot as plt

def FFT(Img, Wn,axis):
    if Img.shape[axis] == 2:     # base case(F_2)
        pic = np.zeros(Img.shape, dtype=complex)
        if axis == 1:
            pic[:,0] = Img[:,0] + Img[:,1] * Wn[:,0]
            pic[:,1] = Img[:,0] - Img[:,1] * Wn[:,0]
        elif axis == 0:
            pic[0,:] = Img[0,:] + Img[1,:] * Wn[0,:]
            pic[1,:] = Img[0,:] - Img[1,:] * Wn[0,:]
        return pic
    else:
        pic = np.empty(Img.shape, dtype=complex)
        if axis == 1:       # kepp recursion
            I_Fn = FFT(Img[:,::2], Wn[:,::2],axis)
            # split odd columns and even columns 
            Dn_Fn = FFT(Img[:,1::2], Wn[:,::2],axis)
            pic[:,0:Img.shape[1] // 2] = I_Fn + Wn * Dn_Fn
            # the forth part is -DnFn
            pic[:,Img.shape[1] // 2:Img.shape[1]] = I_Fn - Wn * Dn_Fn
        elif axis == 0:
            # Just same as the axis 0 part 
            I_Fn = FFT(Img[::2,:], Wn[::2,:], axis)
            Dn_Fn = FFT(Img[1::2,:], Wn[::2,:], axis)
            pic[0:Img.shape[0] // 2,:] = I_Fn + Wn * Dn_Fn
            pic[Img.shape[0] // 2:Img.shape[0],:] = I_Fn - Wn * Dn_Fn
        return pic


def FFT_1D(Img,axis):
    # the rotation factor.For f(t) omiga = e^(-i(n*pi*t)/N)
    Wn = np.zeros(Img.shape,dtype=complex)  # Initialize the Wn
    
    # Do the calculations separately for both axes
    if axis == 0:
        Wn = np.zeros((Img.shape[0]//2,Img.shape[1]), dtype=complex)   # Initialize
        temp = np.array([
        # we set the period is 2pi and Equidistant sampling
        # 1j is the imaginary part 
        np.cos(2*np.pi*i/Img.shape[0]) - 1j*np.sin(2*np.pi*i/Img.shape[0]) for i in range(Img.shape[0]//2)])
        for i in range(Wn.shape[1]):
            Wn[:,i] = temp
    # smae as axis 0
    elif axis == 1:
        Wn = np.zeros((Img.shape[0], Img.shape[1]//2), dtype=complex)
        # 1j is the imaginary part 
        temp = np.array([
            np.cos(2 * np.pi * i / Img.shape[1]) - 1j * np.sin(2 * np.pi * i / Img.shape[1]) for i in
            range(Img.shape[1] // 2)])
        for i in range(Wn.shape[0]):
            Wn[i,:] = temp
    return FFT(Img, Wn,axis)


def iFFT_1d(Img,axis):
    Wn = np.zeros(Img.shape,dtype=complex)
    if axis == 0:
        Wn = np.zeros((Img.shape[0]//2,Img.shape[1]), dtype=complex)
        temp = np.array([
            # 1j is the imaginary part 
            np.cos(2*np.pi*i/Img.shape[0]) + 1j*np.sin(2*np.pi*i/Img.shape[0]) for i in range(Img.shape[0]//2)])
        for i in range(Wn.shape[1]):
            Wn[:,i] = temp
    elif axis == 1:
        Wn = np.zeros((Img.shape[0], Img.shape[1]//2), dtype=complex)
        temp = np.array([
            np.cos(2 * np.pi * i / Img.shape[1]) + 1j * np.sin(2 * np.pi * i / Img.shape[1]) for i in
            range(Img.shape[1] // 2)])
        for i in range(Wn.shape[0]):
            Wn[i,:] = temp

    return FFT(Img, Wn,axis)*(1.0/Img.shape[axis])


def FFT_2d(Img):
    imgsize = Img.shape
    pic = np.zeros(imgsize, dtype=complex)
    if len(imgsize) == 2:
        N = 2
        while N < imgsize[0]:
            N = N << 1
        num1 = N - imgsize[0]
        N = 2
        while N < imgsize[1]:
            N = N << 1
        num2 = N - imgsize[1]
        # Prevent image edge information loss
        # For Axis 0, 'edge' argument means to fill with edge value, axis 1 part is not filled (0,0),
        pic = FFT_1D(np.pad(Img, ((num1 // 2, num1 - num1 // 2), (0, 0)), 'edge'), 0)[num1 // 2:num1 // 2 + imgsize[0], :]
        # For Axis 1, 'edge' argument means to fill with edge value, axis 0 part is not filled (0,0),
        pic = FFT_1D(np.pad(pic, ((0, 0), (num2 // 2, num2 - num2 // 2)), 'edge'), 1)[:, num2 // 2:num2 // 2 + imgsize[1]]
    return pic


def iFFT_2d(Img):
    imgsize = Img.shape
    pic = np.zeros(imgsize, dtype=complex)
    if len(imgsize) == 2:
        N = 2
        while N < imgsize[0]:
            N = N << 1
        num1 = N - imgsize[0]

        N = 2
        while N < imgsize[1]:
            N = N << 1
        num2 = N - imgsize[1]
        pic = iFFT_1d(np.pad(Img,((num1//2,num1-num1//2),(0,0)),'edge'),0)[num1//2:num1//2+imgsize[0],:]  
        pic = iFFT_1d(np.pad(pic,((0,0),(num2//2,num2-num2//2)),'edge'),1)[:,num2//2:num2//2+imgsize[1]] 

    return pic


if __name__ == "__main__":
    img = plt.imread('./img/flower.jpg')
    img = img.mean(2)       # gray 2d
    plt.imshow(img.astype(np.uint8),cmap='gray')
    plt.axis('off')    print(str(F1)+ '=====================' + str(F2))
    print((abs(F1 - F2) < 0.0000001).all())
    plt.show()
    F1 = np.fft.fft2(img[:, :])
    F2 = FFT_2d(img[:, :])
    print((abs(F1 - F2) < 0.0000001).all())
    print(str(F1)+ '=====================' + str(F2))
    print((abs(F1 - F2) < 0.0000001).all())
    F1 = np.fft.ifft2(F1)
    F2 = FFT_2d(F2)
    plt.imshow(F1.astype(np.uint8), cmap='gray')
    plt.axis('off')
    plt.show()