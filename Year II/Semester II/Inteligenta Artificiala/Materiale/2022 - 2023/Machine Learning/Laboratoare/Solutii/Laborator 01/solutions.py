import os
from scipy.misc import imread, imresize, imsave
import matplotlib.image as mpimg 
import matplotlib.pyplot as plt 
import numpy as np
from sklearn.linear_model import Perceptron
from PIL import Image


import pdb

# ------ 1 ------
folder_name = 'images'
files = os.listdir(folder_name)   
images = []

for file in files:
    # img = imread(os.path.join(folder_name, file), mode='RGB')   
    # im = Image.open(os.path.join(folder_name, file))
    # img = np.array(im)
    img = mpimg.imread(os.path.join(folder_name, file)) * 255
     
    images.append(img.flatten() / 255) # ;np.reshape(img, [-1])

images = np.array(images)

# ------ 2 ------
mean_image = np.mean(images, axis=0)

# ------ 3 ------
normalized_images = images - mean_image

# ------ 4 ------
weights = np.load('coefs.npy') 
bias = np.load('bias.npy')

def softmax(Z):
    return np.exp(Z) / np.sum(np.exp(Z))

z_1 = np.dot(normalized_images, weights) + bias
a_1 = softmax(z_1)
y_pred = np.argmax(a_1, axis=1)

# ------ 5 ------
def accuracy_score(y_true, y_pred):
    return np.mean(y_true == y_pred)
    
y_true = [0, 0, 1, 1, 2, 2, 3, 3]
print(y_pred)
print('the accuracy is ', accuracy_score(y_true, y_pred))

# ------ 6 ------
labels = {0: 'cat', 1: 'dog', 2: 'frog', 3: 'horse'}

for i in range(4):
    print('class %d has the label %s' % (i, labels[i]))

# ------ 7 ------
img = mean_image.reshape((64, 64, 3))  
plt.imshow(np.uint8(img * 255))
plt.show()

pdb.set_trace()