#! /usr/bin/env python3

# AASD 4005 Adv. Mathematical Concepts for Machine Learning
# George Brown College

 
# Program: Part 1
# "Building an Image Enhancer using Fourier Transform"
# version: 3.0. 
# date: 2022-11-06

# usage: 
# python fourierfilters3.0.py --image yourimage.jpg
import cv2
from matplotlib import pyplot as plt
import numpy as np
import argparse


class Filters:
    """
    The 'Filters' class represents a cv image with its respective methods to calculate different FFT filters:
    
    - Low pass_filter_fft
    - High pass_filter_fft
    - Band pass_filter_fft
    
    """
    
    def __init__(self, image):
        """
        Method for initializing a Filters object
    
        Args: 
            image (image)
            
        Attributes:
            image (image)
            dft (complex array)
            dft_shift (ndarray)
            
        """
        self.img = image
        #Output is a 2D complex array. 1st channel real and 2nd imaginary
        #For fft in opencv input image needs to be converted to float32
        self.dft = cv2.dft(np.float32(self.img), flags=cv2.DFT_COMPLEX_OUTPUT)
        
        #Rearranges a Fourier transform X by shifting the zero-frequency 
        #component to the center of the array.
        #Otherwise it starts at the tope left corenr of the image (array)
        self.dft_shift = np.fft.fftshift(self.dft)
           
           
    def get_noisy_image(self, noise_type):
        """
        The get_noisy_image method produces an image with different kind of noises added 
        (in order to be filtered later)      
        
        Args: 
            noise_type ("gauss", "s&p", "poisson", "poisson", "speckle")
            
        Returns: noisy_image  (image)
                 fshift_mask_mag
        
        """
        image = self.img
        if noise_type == "gauss":
            row,col= image.shape
            mean = 0
            var = 200#0.1
            sigma = var**0.5
            gauss = np.random.normal(mean,sigma,(row,col))
            gauss = gauss.reshape(row,col)
            noisy_image = image + gauss
            return noisy_image
            
        elif noise_type == "s&p":
            row,col = image.shape
            s_vs_p = 0.5
            amount = 0.004
            noisy_image = np.copy(image)
            # Salt mode
            num_salt = np.ceil(amount * image.size * s_vs_p)
            coords = [np.random.randint(0, i - 1, int(num_salt))
                for i in image.shape]
            noisy_image[coords] = 1

            # Pepper mode
            num_pepper = np.ceil(amount* image.size * (1. - s_vs_p))
            coords = [np.random.randint(0, i - 1, int(num_pepper))
                for i in image.shape]
            noisy_image[coords] = 0
            return noisy_image
        
        elif noise_type == "poisson":
            vals = len(np.unique(image))
            vals = 2 ** np.ceil(np.log2(vals))
            noisy = np.random.poisson(image * vals) / float(vals)
            return noisy_image
        
        elif noise_type =="speckle":
            row,col = image.shape
            gauss = np.random.randn(row,col)
            gauss = gauss.reshape(row,col)        
            noisy = image + image * gauss
            return noisy_image
        
        
    def change_image_to(self, new_image):
        """
        Method for re-initializing a Filters object with a new image
    
        Args: 
            new_image (image)
            
        Returns: None
        """        
        self.img = new_image 
        self.dft = cv2.dft(np.float32(self.img), flags=cv2.DFT_COMPLEX_OUTPUT)
        self.dft_shift = np.fft.fftshift(self.dft)
    
    
    def calculate_magnitude_spectrum(self):
        """The calculate_magnitude_spectrum calculates the magnitude of the spectrum      
        Args: 
            None (as the image is given in the class definition)
            
        Returns: magnitude_spectrum (image)
        
        """       
        ##Magnitude of the function is 20.log(abs(f))
        #For values that are 0 we may end up with indeterminate values for log. 
        #So we can add 1 to the array to avoid seeing a warning. 
        magnitude_spectrum = 20 * np.log(cv2.magnitude(self.dft_shift[:, :, 0], self.dft_shift[:, :, 1]))
        return magnitude_spectrum
    
    
    def low_pass_filter_fft(self, r = 60):
        """
        The low_pass_filter_fft calculates the new filtered image 
        (allowing only the low frequencies to pass)      
        
        Args: 
            r (radius of circular LPF mask, center circle is 1). By default r = 60 frequency units
            
        Returns: img_back  (image)
                 fshift_mask_mag (complex array)
        
        """
        # Circular LPF mask, center circle is 1, remaining all zeros
        # Only allows low frequency components - smooth regions
        # Can smooth out noise but blurs edges.
        #

        rows, cols = self.img.shape
        crow, ccol = int(rows / 2), int(cols / 2)
        mask = np.zeros((rows, cols, 2), np.uint8)
        # r = 50
        center = [crow, ccol]
        x, y = np.ogrid[:rows, :cols]
        mask_area = (x - center[0]) ** 2 + (y - center[1]) ** 2 <= r*r
        mask[mask_area] = 1
        # apply mask and inverse DFT: Multiply fourier transformed image (values)
        #with the mask values. 
        fshift = self.dft_shift * mask

        #Get the magnitude spectrum (only for plotting purposes)
        fshift_mask_mag = 20 * np.log(cv2.magnitude(fshift[:, :, 0], fshift[:, :, 1]))

        #Inverse shift to shift origin back to top left.
        f_ishift = np.fft.ifftshift(fshift)

        #Inverse DFT to convert back to image domain from the frequency domain. 
        #Will be complex numbers
        img_back = cv2.idft(f_ishift)

        #Magnitude spectrum of the image domain
        img_back = cv2.magnitude(img_back[:, :, 0], img_back[:, :, 1])
        return [img_back, fshift_mask_mag]

        
    def high_pass_filter_fft(self, r = 0.02):
        """
        The high_pass_filter_fft calculates the new filtered image 
        (allowing only the high frequencies to pass)      
        
        Args: 
            r (Radius of ircular HPF mask, center circle is 0). By default: r= 0.02
            
        Returns: img_back  (image)
                 fshift_mask_mag (complex array)
        
        """
        # Circular HPF mask, center circle is 0, remaining all ones
        # Can be used for edge detection and image sharpening because low frequencies at center are blocked
        # and only high frequencies are allowed. Edges are high frequency components.
        # Amplifies noise.

        rows, cols = self.img.shape
        crow, ccol = int(rows / 2), int(cols / 2)

        mask = np.ones((rows, cols, 2), np.uint8)
        #r = 0.02
        center = [crow, ccol]
        x, y = np.ogrid[:rows, :cols]
        mask_area = (x - center[0]) ** 2 + (y - center[1]) ** 2 <= r*r
        mask[mask_area] = 0
        # apply mask and inverse DFT: Multiply fourier transformed image (values)
        #with the mask values. 
        fshift = self.dft_shift * mask

        #Get the magnitude spectrum (only for plotting purposes)
        fshift_mask_mag = 20 * np.log(cv2.magnitude(fshift[:, :, 0], fshift[:, :, 1]))

        #Inverse shift to shift origin back to top left.
        f_ishift = np.fft.ifftshift(fshift)

        #Inverse DFT to convert back to image domain from the frequency domain. 
        #Will be complex numbers
        img_back = cv2.idft(f_ishift)

        #Magnitude spectrum of the image domain
        img_back = cv2.magnitude(img_back[:, :, 0], img_back[:, :, 1])
        return [img_back, fshift_mask_mag]

        
    def band_pass_filter_fft(self, r_in = 10, r_out = 80):
        """
        The band_pass_filter_fft calculates the new filtered image 
        (allowing only a certain range of freqencies to pass)      
        
        Args: 
            r_in (Radius of inner concentric circle mask, only the points living in concentric circle are ones). By default: r_in = 10 
            r_out (Radius of outter concentric circle mask, only the points living in concentric circle are ones) By default: r_out = 80
            
        Returns: img_back  (image)
                 fshift_mask_mag (complex array)
        
        """
        # Band Pass Filter - Concentric circle mask, only the points living in concentric circle are ones
        rows, cols = self.img.shape
        crow, ccol = int(rows / 2), int(cols / 2)
        mask = np.zeros((rows, cols, 2), np.uint8)
        # r_out = 80
        # r_in = 10
        center = [crow, ccol]
        x, y = np.ogrid[:rows, :cols]
        mask_area = np.logical_and(((x - center[0]) ** 2 + (y - center[1]) ** 2 >= r_in ** 2),
                                   ((x - center[0]) ** 2 + (y - center[1]) ** 2 <= r_out ** 2))
        mask[mask_area] = 1
        # apply mask and inverse DFT: Multiply fourier transformed image (values)
        #with the mask values. 
        fshift = self.dft_shift * mask

        #Get the magnitude spectrum (only for plotting purposes)
        fshift_mask_mag = 20 * np.log(cv2.magnitude(fshift[:, :, 0], fshift[:, :, 1]))

        #Inverse shift to shift origin back to top left.
        f_ishift = np.fft.ifftshift(fshift)

        #Inverse DFT to convert back to image domain from the frequency domain. 
        #Will be complex numbers
        img_back = cv2.idft(f_ishift)

        #Magnitude spectrum of the image domain
        img_back = cv2.magnitude(img_back[:, :, 0], img_back[:, :, 1])
        return [img_back, fshift_mask_mag]


if __name__ == "__main__":

    # construct the argument parser and parse the arguments
    ap = argparse.ArgumentParser()
    ap.add_argument("-i", "--image", type=str, default="mypicture.jpg",
        help="path to the input image")
    args = vars(ap.parse_args())
    
    # load the input image from disk
    img = cv2.imread(args["image"], 0) # load an image
    
    # instantiate class
    filters =Filters(img)
    
    noisy_image = filters.get_noisy_image("gauss")
    
    # original image
    fig = plt.figure(figsize=(24, 24))
    ax1 = fig.add_subplot(3,3,1)
    ax1.imshow(img, cmap='gray')
    ax1.title.set_text('Input Image')
    
    # # spectrum of the image
    # ax2 = fig.add_subplot(3,3,2)
    # ax2.imshow(filters.calculate_magnitude_spectrum(), cmap='gray')
    # ax2.title.set_text('FFT of image')
    
    # 'fshift_mask_mag mask' of low pass filter
    ax2 = fig.add_subplot(3,3,2)
    ax2.imshow(filters.low_pass_filter_fft()[1], cmap='gray')
    ax2.title.set_text('FFT + LPF Mask')
    
    # image after applying low pass filter
    ax3 = fig.add_subplot(3,3,3)
    ax3.imshow(filters.low_pass_filter_fft()[0], cmap='gray')
    ax3.title.set_text('Image blurred after LPF')
   
    # 'fshift_mask_mag mask' of high pass filter
    ax4 = fig.add_subplot(3,3,4)
    ax4.imshow(filters.high_pass_filter_fft()[1], cmap='gray')
    ax4.title.set_text('FFT + HPF Mask')
   
    # image after applying high pass filter
    ax5 = fig.add_subplot(3,3,5)
    ax5.imshow(filters.high_pass_filter_fft()[0], cmap='gray')
    ax5.title.set_text('Image Sharpening HPF')
   
    # 'fshift_mask_mag mask' of band pass filter
    ax6 = fig.add_subplot(3,3,6)
    ax6.imshow(filters.band_pass_filter_fft()[1], cmap='gray')
    ax6.title.set_text('FFT + BPF Mask')
   
    # image after applying band pass filter
    ax7 = fig.add_subplot(3,3,7)
    ax7.imshow(filters.band_pass_filter_fft()[0], cmap='gray')
    ax7.title.set_text('Image Edge Detection BPF')
    
    # noisy image
    #noisy_image = get_noisy_image("gauss")
    
    filters.change_image_to(noisy_image)
    filters.img = noisy_image
    
    ax8 = fig.add_subplot(3,3,8)
    ax8.imshow(noisy_image, cmap='gray')
    ax8.title.set_text('Image with noise')
    
    # un-noised imaged image
    unnoised_image = filters.high_pass_filter_fft(r=0.0075)[0]
    
    ax9 = fig.add_subplot(3,3,9)
    ax9.imshow(unnoised_image, cmap='gray')
    ax9.title.set_text('Filtered Image un-noised')
    
    plt.show()
    
