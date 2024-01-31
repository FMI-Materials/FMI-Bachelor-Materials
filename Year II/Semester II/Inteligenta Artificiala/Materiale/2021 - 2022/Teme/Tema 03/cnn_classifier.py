import numpy as np
from os import path
from keras.models import Sequential, load_model
from keras.layers import Dense, Dropout, Flatten, Conv2D, BatchNormalization
from keras.preprocessing.image import ImageDataGenerator
from keras.callbacks import LearningRateScheduler, ModelCheckpoint
from matplotlib import pyplot as plt

from data import Data


# Best Score: ~0.82
class CnnClassifier:
    BEST_MODEL = 'best_model.h5'

    def __init__(self, dropout=.4):
        self.model = Sequential()

        self.model.add(Conv2D(32, input_shape=(50, 50, 1), activation='relu', kernel_size=3))
        self.model.add(BatchNormalization())
        self.model.add(Conv2D(32, activation='relu', kernel_size=3))
        self.model.add(BatchNormalization())
        self.model.add(Conv2D(32, activation='relu', kernel_size=5, strides=2, padding='same'))
        self.model.add(BatchNormalization())
        self.model.add(Dropout(dropout))

        self.model.add(Conv2D(64, activation='relu', kernel_size=3))
        self.model.add(BatchNormalization())
        self.model.add(Conv2D(64, activation='relu', kernel_size=3))
        self.model.add(BatchNormalization())
        self.model.add(Conv2D(64, activation='relu', kernel_size=5, strides=2, padding='same'))
        self.model.add(BatchNormalization())
        self.model.add(Dropout(dropout))

        self.model.add(Flatten())
        self.model.add(Dense(128, activation='relu'))
        self.model.add(BatchNormalization())
        self.model.add(Dropout(dropout))
        self.model.add(Dense(10, activation='softmax'))

        self.model.compile(metrics=["accuracy"], optimizer="Adam", loss="sparse_categorical_crossentropy")

        self.datagen = ImageDataGenerator(zoom_range=0.10, rotation_range=10, height_shift_range=0.1,
                                          width_shift_range=0.1)
        self.model_checkpoint = ModelCheckpoint(f'data/{self.BEST_MODEL}', monitor='val_accuracy', mode='max',
                                                save_best_only=True, verbose=1)

    def load_best(self):
        if path.isfile(f'data/{self.BEST_MODEL}'):
            self.model = load_model(f'data/{self.BEST_MODEL}')

    def train(self, train_images, train_labels, validation_images, validation_labels, epochs=5):
        self.annealer = LearningRateScheduler(lambda x: 1e-3 * 0.95 ** (x + epochs))
        self.model.fit(self.datagen.flow(train_images, train_labels, batch_size=64), epochs=epochs,
                       steps_per_epoch=train_images.shape[0] // 64, callbacks=[self.model_checkpoint, self.annealer],
                       validation_data=(validation_images, validation_labels))

    def classify_images(self, test_images):
        return self.model.predict_classes(test_images)


def accuracy_score(ground_truth_labels, predicted_labels):
    return np.mean(ground_truth_labels == predicted_labels)


def test_accuracy(cnn_classifier, validation_images, validation_labels):
    cnn_classifier.load_best()
    predicted_labels = cnn_classifier.classify_images(validation_images)
    acc = accuracy_score(validation_labels, predicted_labels)
    print(f"\nAccuracy: {acc * 100}%")
    return acc


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

    # Convert data to np array
    train_labels_c = np.array(train_labels)
    train_images_c = np.array(train_images_mat)
    validation_labels_c = np.array(validation_labels)
    validation_images_c = np.array(validation_images_mat)
    test_images_c = np.array(test_images_mat)

    # Define model
    cnn_classifier = CnnClassifier()

    # Train model, keep only best epochs
    best_accuracy = 0
    for i in range(20):
        cnn_classifier.load_best()
        cnn_classifier.train(train_images_c, train_labels_c, validation_images_c, validation_labels_c, epochs=(16 + i))

        # Test best accuracy
        acc = test_accuracy(cnn_classifier, validation_images_c, validation_labels_c)

        # Dump only the best model
        if acc > best_accuracy:
            best_accuracy = acc
            predicted_labels = cnn_classifier.classify_images(test_images_c)
            Data.dump(predicted_labels, input_file="test", output_file="cnn")

    # Test best accuracy
    test_accuracy(cnn_classifier, validation_images_c, validation_labels_c)

    # Calculate confusion matrix
    cnn_classifier.load_best()
    predicted_labels = cnn_classifier.classify_images(validation_images_c)
    conf_mat = confunsion_matrix(predicted_labels, validation_labels_c)

    # Display confusion matrix
    plt.imshow(conf_mat, cmap='gray')

    # Dump only the best model
    predicted_labels = cnn_classifier.classify_images(test_images_c)
    Data.dump(predicted_labels, input_file="test", output_file="cnn")
