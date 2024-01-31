import numpy as np
import glob
import matplotlib.pyplot as plt

filenames = glob.glob('./images/*')
# ca sa iei toate folderele din images si
# toate imaginile din folderele din images

im = np.load(filenames[0])

# plt.imshow(im, cmap = 'gray')
# plt.show()

imag = []

for f in filenames:
    img = np.load(f)
    imag.append(img)

imag = np.array(imag)

val = np.mean(imag, axis=0)
# print(val.shape)

plt.imshow(val / 255,cmap='gray')
# plt.show()

#BROADCASTING

# vector cu suma pixelilor pentru fiecare imagine
suma = np.sum(imag, axis=(1,2))
print(suma)


