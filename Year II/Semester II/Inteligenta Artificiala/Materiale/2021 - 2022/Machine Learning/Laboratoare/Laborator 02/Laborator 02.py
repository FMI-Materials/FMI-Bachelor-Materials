import os
from sklearn.naive_bayes import MultinomialNB
import numpy as np
import matplotlib.pyplot as plt


train_images = np.loadtxt('train_images.txt') # incarc imaginile
train_labels = np.loadtxt('train_labels.txt', 'int') # incarcam etichetele avand
                                                     # tipul de date int
test_images = np.loadtxt('test_images.txt')
test_labels = np.loadtxt('test_labels.txt', 'int')

image = train_images[0, :]
image = np.reshape(image, (28, 28))
plt.imshow(image.astype(np.uint64), cmap='gray')
plt.show()

image = train_images[1, :]
image = np.reshape(image, (28, 28))
plt.imshow(image.astype(np.uint64), cmap='gray')
plt.show()

# pregatim datele pentru clasificator
# bins = np.linspace(start=0, stop=255, num=5)
# print(bins)
# x_to_bins = np.digitize(train_images, bins)
# print(x_to_bins)

def digitize_values(x, num_bins):
    bins = np.linspace(start=0, stop=255, num=num_bins)
    digitize_x = np.digitize(x, bins)

    return digitize_x


train_images_bins = digitize_values(train_images, 5)
test_images_bins = digitize_values(test_images, 5)

# initializarea modulului
model = MultinomialNB()
model.fit(train_images_bins, train_labels)

# print(model.predict(test_images_bins))

# acuratetea modelului
model_acc = model.score(train_images_bins, train_labels)
print(f"Model accuracy is: {model_acc}\n")

# punctul 4
for num_bins in range(3, 12, 2):
    train_images_bins = digitize_values(train_images, num_bins)
    #test_images_bins = digitize_values(test_images, num_bins)
    model = MultinomialNB()
    model.fit(train_images, train_labels)
    print(model.predict(test_images))

