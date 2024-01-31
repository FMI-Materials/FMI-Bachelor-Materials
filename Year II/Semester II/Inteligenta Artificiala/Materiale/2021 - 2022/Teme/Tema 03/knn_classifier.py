import numpy as np
from data import Data
from matplotlib import pyplot as plt


# Model discutat in laborator
# Best: ~0.51
class KnnClassifier:
    def __init__(self, train_images, train_labels):
        self.train_images = train_images
        self.train_labels = train_labels

    def classify_image(self, test_image, num_neighbors=3, metric='l2'):
        if metric == 'l1':
            distances = np.sum(np.abs(self.train_images - test_image), axis=1)
        elif metric == 'l2':
            distances = np.sqrt(np.sum(((self.train_images - test_image) ** 2), axis=1))
        else:
            raise Exception("Metric not implemented")
        sorted_indices = distances.argsort()
        nearest_indices = sorted_indices[:num_neighbors]
        nearest_labels = self.train_labels[nearest_indices]

        return np.bincount(nearest_labels).argmax()

    def classify_images(self, test_images, num_neighbors=3, metric='l2'):
        predicted_labels = [self.classify_image(image, num_neighbors, metric) for image in test_images]

        return np.array(predicted_labels)


def accuracy_score(ground_truth_labels, predicted_labels):
    return np.mean(ground_truth_labels == predicted_labels)


def confunsion_matrix(predicted_labels, ground_truth_labels):
    num_labels = ground_truth_labels.max() + 1
    conf_mat = np.zeros((num_labels, num_labels))

    for i in range(len(predicted_labels)):
        conf_mat[ground_truth_labels[i], predicted_labels[i]] += 1
    return conf_mat

if __name__ == "__main__":
    # Load data
    test_images_mat, test_images_arr, _ = Data.load("test")
    train_images_mat, train_images_arr, train_labels = Data.load("train")
    validation_images_mat, validation_images_arr, validation_labels = Data.load("validation")

    # Format data, convert to np.array
    train_labels_k = np.array(train_labels)
    train_images_k = np.array(train_images_arr)
    validation_labels_k = np.array(validation_labels)
    validation_images_k = np.array(validation_images_arr)
    test_images_k = np.array(test_images_arr)

    # Define classifier and classify images
    knn_classifier = KnnClassifier(train_images_k, train_labels_k)
    predicted_labels = knn_classifier.classify_images(validation_images_k, metric="l2")

    # Determine accuracy
    acc = accuracy_score(validation_labels_k, predicted_labels)
    print(f"Accuracy = {acc}")

    conf_mat = confunsion_matrix(predicted_labels, validation_labels_k)
    plt.imshow(conf_mat, cmap='gray')

    # Predict test data and write prediction
    predicted_labels = knn_classifier.classify_images(test_images_k)
    Data.dump(predicted_labels, input_file="test", output_file="knn")
