import numpy as np
import pdb
import cv2 as cv

num_images = 2000

images = np.load('images_test.npy')
new_images = []
for i in range(num_images):
    im = images[i]
    r = im[:32**2].reshape((32, 32))
    g = im[32**2: 2*32**2].reshape((32, 32))
    b = im[2*32**2:].reshape((32, 32)) 
    image=np.stack((r, g, b), axis=-1)
    new_images.append(image)

np.save('images_test_.npy', np.array(new_images))