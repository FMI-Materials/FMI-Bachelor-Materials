import os
from scipy.misc import imread, imresize, imsave
import matplotlib.pyplot as plt
import pdb
import numpy as np
from sklearn.linear_model import Perceptron

folder_name = 'images_before'
files = os.listdir(folder_name)  
size = 64
images = []

for file in files:
    img = imread(os.path.join(folder_name, file), mode='RGB') 
    img = imresize(img, (size, size)) 
    imsave(os.path.join('images', file[:file.rfind('.')] + ".png"), img)
    images.append(np.reshape(img, [-1])) # img.flatten();
 

images = np.array(images) / 255
mean_image = np.mean(images, axis=0)
img = mean_image.reshape((64, 64, 3))  
plt.imshow(np.uint8(img * 255))
plt.show()

images = images - mean_image 
print(files)
y = [0, 0, 1, 1, 2, 2, 3, 2]
perceptron = Perceptron(eta0=0.1)
perceptron.fit(images, y)  
print(perceptron.score(images, y))
print(perceptron.predict(images))
np.save('coefs.npy', np.squeeze(perceptron.coef_).T)
np.save('bias.npy', perceptron.intercept_)
