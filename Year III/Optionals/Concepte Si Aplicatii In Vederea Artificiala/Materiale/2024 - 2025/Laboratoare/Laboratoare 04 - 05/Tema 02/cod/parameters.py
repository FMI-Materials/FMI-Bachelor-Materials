import cv2 as cv
import sys
import numpy as np


class Parameters:

    def __init__(self, image_name):
        self.image_name = image_name
        self.image = cv.imread(image_name)
        if self.image is None:
            print('The image name %s is invalid.' % self.image_name)
            sys.exit(-1)
        self.image = np.float32(self.image)
        self.resize_option = 'micsoreazaLatime'
        self.num_pixels_width = 50
        self.num_pixel_height = 50
        self.show_path = False
        self.color_path = (0, 0, 255)
        self.method_select_path = 'greedy'
        self.factor_amplification = 1.05
