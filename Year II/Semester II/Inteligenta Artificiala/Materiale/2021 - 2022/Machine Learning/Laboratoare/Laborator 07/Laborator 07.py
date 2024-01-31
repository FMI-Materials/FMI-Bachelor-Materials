import numpy as np
import matplotlib.pyplot as plt
import sklearn
from sklearn.neural_network import MLPClassifier

# impartim la 255 pentru a normaliza valorile
# si pentru a creste acuratetea modelului

training_images = np.loadtxt("data/MNIST/train_images.txt") / 255
test_images = np.loadtxt("data/MNIST/test_images.txt") / 255
training_labels = np.loadtxt("data/MNIST/train_labels.txt")
test_labels = np.loadtxt("data/MNIST/test_labels.txt")

# multi layer perceptron classifier
model = MLPClassifier()
model.fit(training_images, training_labels)
accuracy = np.mean(model.predict(test_images) == test_labels)
print(accuracy)

