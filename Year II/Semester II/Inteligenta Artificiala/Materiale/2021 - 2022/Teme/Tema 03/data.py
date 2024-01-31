import imageio
import numpy as np
from os import path
from matplotlib import pyplot as plt
from keras.preprocessing import image


class Data:
    TUMOR_TYPES = ('native', 'arterial', 'venous')

    # Load input data (labels and images)
    @staticmethod
    def load(input_file='train'):
        images_arr, images_mat, labels = [], [], []
        with open(f"data/{input_file}.txt", "r") as f:
            line = f.readline()
            while line:
                line_data = line.replace("\n", "").split(",")
                line = f.readline()

                # Check if image path exists
                image_path = f"data/{input_file}/{line_data[0]}"
                if not path.exists(image_path):
                    continue

                # Read images as arrays
                img_arr = imageio.imread(image_path)
                img_arr = np.asarray(img_arr).reshape(-1)

                # Read images as matrixes
                img_mat = image.load_img(image_path, target_size=(50, 50, 1), color_mode='grayscale')
                img_mat = image.img_to_array(img_mat)
                img_mat = img_mat / 255

                images_arr.append(img_arr)
                images_mat.append(img_mat)

                if len(line_data) > 1:
                    labels.append(int(line_data[1]))
        return images_mat, images_arr, labels

    # Dump data
    @staticmethod
    def dump(predicted_labels, input_file="test", output_file="test"):
        output = []
        i = 0
        with open(f"data/{input_file}.txt", "r") as f:
            line = f.readline()
            while line:
                line_data = line.replace("\n", "").split(",")
                line = f.readline()
                output.append(f"{line_data[0]},{predicted_labels[i]}")
                i += 1
        with open(f"data/submission_{output_file}.txt", "w") as o:
            o.write("id,label\n")
            o.write("\n".join(output))

    # Print data
    @staticmethod
    def print_data(images, labels, r):
        for i in range(r[0], r[1]):
            image = np.reshape(images[i], (50, 50))
            print("Tumor type:", Data.TUMOR_TYPES[labels[i]])
            plt.imshow(image, cmap='gray')
            plt.show()
