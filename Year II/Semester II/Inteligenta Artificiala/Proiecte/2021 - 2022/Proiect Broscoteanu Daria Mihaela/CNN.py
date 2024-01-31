# Broscoteanu Daria Mihaela
# Grupa 243

# Importuri

import numpy as np # Pentru prelucrari de array-uri.
import os
from sklearn.metrics import accuracy_score # pentru acuratete.
from PIL import Image # Pentru prelucrari de imagine.
from PIL import ImageFilter # Pentru adaugarea de noise peste poze => set de date de train mai mare
import matplotlib.pyplot as plt # Pentru plot-uri.
import cv2 as cv2
# Importuri pentru CNN
import tensorflow as tf
from tensorflow.keras.models import Sequential # Modelul pentru CNN
from tensorflow.keras.layers import Conv2D # Pentru un layer 2D de convolutie
from tensorflow.keras.layers import Dropout # Pentru aplicarea dropout-ului asupra inputului.
from tensorflow.keras.layers import MaxPool2D # Pentru aplicarea operatiei de max-pooling.
from tensorflow.keras.layers import Dense # Pentru un layer de NN conenctat dens.
from tensorflow.keras.layers import Flatten # Pentru aplatizarea inputului.
from tensorflow.keras.optimizers import RMSprop # Pentru optimizari cu algoritmul RMS.
from tensorflow.keras.preprocessing.image import ImageDataGenerator # Pentru preprocesari
from tensorflow.keras.layers import BatchNormalization # Pentru layere de normalizare in CNN
from tensorflow.keras.layers import GaussianNoise
from keras.utils.np_utils import to_categorical
from keras.callbacks import ModelCheckpoint


# CNN
class ProjectCNN:
    def __init__(self):
        print()

    def read_train_validation(self): # Functie pentru citirea datelor de train si de validare
        txtName = "../input/competitie/train.txt"
        trainImages = []
        trainLabels = []

        with open(txtName, "r") as reader:
            line = reader.readline()
            line = reader.readline()  # trec peste linia cu id, label
            while line != "":
                imageName, imageLabel = line.rstrip("\n").split(",")
                imagePath = "../input/competitie/train+validation/" + imageName
                image = cv2.imread(imagePath)
                #             Initial, pentru augumentarea setului de date, m-am folosit doar de rotirea imaginilor in diferite directii si asocierea acestora
                #             cu label-urile corespunzatoare. Acest lucru a dus insa la overfitting pe datele de train.
                #             flipedImage1 = cv2.flip(image, -1)
                #             flipedImage2 = cv2.flip(image, 0)
                #             flipedImage3 = cv2.flip(image, 1)
                #             image = image / 255
                #             flipedImage1 = flipedImage1 / 255
                #             flipedImage2 = flipedImage2 / 255
                #             flipedImage3 = flipedImage3 / 255
                trainImages.append(image)
                trainLabels.append(int(imageLabel))
                #             trainImages.append(flipedImage1)
                #             trainLabels.append(int(imageLabel))
                #             trainImages.append(flipedImage2)
                #             trainLabels.append(int(imageLabel))
                #             trainImages.append(flipedImage3)
                #             trainLabels.append(int(imageLabel))
                line = reader.readline()

        bigData = [image for image in trainImages]
        bigLabels = [label for label in trainLabels]

        validationImages = []
        validationLabels = []
        txtName = "../input/competitie/validation.txt"
        with open(txtName, "r") as reader:
            line = reader.readline()
            line = reader.readline()  # trec peste linia cu id, label
            while line != "":
                imageName, imageLabel = line.rstrip("\n").split(",")
                imagePath = "../input/competitie/train+validation/" + imageName
                image = cv2.imread(imagePath)
                validationImages.append(image)
                validationLabels.append(int(imageLabel))

                bigData.append(image)
                bigLabels.append(int(imageLabel))

                line = reader.readline()
        return trainImages, trainLabels, validationImages, validationLabels, bigData, bigLabels

    def read_test(self): # Functie pentru citirea datelor de test
        txtName = "../input/competitie/test.txt"
        testImages = []
        with open(txtName, "r") as reader:
            line = reader.readline()
            line = reader.readline()  # trec peste linia cu id
            while line != "":
                imageName = line.rstrip("\n")
                imagePath = "../input/competitie/test/" + imageName
                image = cv2.imread(imagePath)
                image = image / 255 # scalez valorile RGB in intervalul [0,1]
                testImages.append(image)
                line = reader.readline()
        return testImages

    def create_data_generators(self, trainImages, trainLabels, validationImages, validationLabels):
        trainDataGen = ImageDataGenerator(
            rescale=1.0 / 255,
            featurewise_std_normalization=True,
            featurewise_center=True,
            horizontal_flip=True,
            vertical_flip=True,
            data_format="channels_last"
        )

        validationDataGen = ImageDataGenerator(
            rescale=1.0 / 255,
            featurewise_std_normalization=True,
            data_format="channels_last"
        )

        trainIterator = trainDataGen.flow(trainImages, trainLabels,
                                          batch_size=32
                                          )
        validationIterator = validationDataGen.flow(validationImages, validationLabels,
                                                    batch_size=32
                                                    )
        return trainIterator, validationIterator

    def define_CNN_model(self): # Functei pentru definrea layerelor de CNN
        modelCNN = Sequential()
        modelCNN.add(Conv2D(16, kernel_size=(3, 3), activation="relu", input_shape=(16, 16, 3), padding="same"))
        modelCNN.add(BatchNormalization())
        modelCNN.add(Conv2D(16, kernel_size=(3, 3), activation="relu", padding="same", input_shape=(16, 16, 3)))
        modelCNN.add(BatchNormalization())
        modelCNN.add(MaxPool2D())
        modelCNN.add(Dropout(0.25))

        modelCNN.add(Conv2D(32, kernel_size=(3, 3), activation="relu", padding="same", input_shape=(16, 16, 3)))
        modelCNN.add(BatchNormalization())
        modelCNN.add(Conv2D(32, kernel_size=(3, 3), activation="relu", padding="same", input_shape=(16, 16, 3)))
        modelCNN.add(BatchNormalization())
        modelCNN.add(MaxPool2D())
        modelCNN.add(Dropout(0.25))

        modelCNN.add(Conv2D(64, kernel_size=(3, 3), activation="relu", padding="same", input_shape=(16, 16, 3)))
        modelCNN.add(BatchNormalization())
        modelCNN.add(Conv2D(64, kernel_size=(3, 3), activation="relu", padding="same", input_shape=(16, 16, 3)))
        modelCNN.add(BatchNormalization())
        modelCNN.add(MaxPool2D())
        modelCNN.add(Dropout(0.25))

        modelCNN.add(Conv2D(128, kernel_size=(3, 3), activation="relu", padding="same", input_shape=(16, 16, 3)))
        modelCNN.add(BatchNormalization())
        modelCNN.add(Conv2D(128, kernel_size=(3, 3), activation="relu", padding="same", input_shape=(16, 16, 3)))
        modelCNN.add(BatchNormalization())
        modelCNN.add(MaxPool2D())
        modelCNN.add(Dropout(0.25))

        modelCNN.add(Flatten())
        modelCNN.add(Dense(256, activation="relu"))
        modelCNN.add(Dropout(0.25))
        modelCNN.add(Dense(256, activation="relu"))
        modelCNN.add(Dropout(0.25))
        modelCNN.add(Dense(256, activation="relu"))
        modelCNN.add(Dropout(0.25))
        modelCNN.add(Dense(7, activation='softmax'))
        modelCNN.summary()

        return modelCNN

    def training_and_predicting(self): # Functie in care antrenez modelul si prezic label-urile pentru datele de test
        trainImages, trainLabels, validationImages, validationLabels, bigData, bigLabels = self.read_train_validation() # Citirea datelor de antrenare si validare

        trainImages = np.array(trainImages)
        trainLabels = np.array(trainLabels)
        trainLabels = to_categorical(trainLabels)

        validationImages = np.array(validationImages)
        validationLabels = np.array(validationLabels)
        validationLabels = to_categorical(validationLabels)

        bigData = np.array(bigData)
        bigLabels = np.array(bigLabels)
        bigLabels = to_categorical(bigLabels)

        testImages = self.read_test()
        testImages = np.array(testImages)

        trainIterator, validationIterator = self.create_data_generators(trainImages, trainLabels, validationImages,
                                                                        validationLabels) # Creez iteratorii prin batch-urile de date

        modelCNN = self.define_CNN_model()
        modelCNN_bestAccuracyCheckpoint = ModelCheckpoint( # Definesc un checkpoint pe care il folosesc
            filepath="bestAccuracyCheckpoint",             # Pentru a mi salva weight-urile pentru acuratetea maxima pe validare
            monitor='val_accuracy',
            mode='max',
            save_weights_only=True,
            save_best_only=True
        )
        modelCNN.compile(loss='categorical_crossentropy', # Compilez modelul
                         optimizer=tf.keras.optimizers.Adam(),
                         metrics=['accuracy'],
                         )
        modelCNN_history = modelCNN.fit(trainIterator, # Antrenez modelul in 150 de epoci, salvand epoca in care acuratetea pe validare e maxima
                                        batch_size=32,
                                        epochs=150,
                                        verbose=1,
                                        validation_data=validationIterator,
                                        callbacks=modelCNN_bestAccuracyCheckpoint
                                        )
        modelCNN.load_weights("bestAccuracyCheckpoint") # Incarc valorile weight-urilor salvate in checkpoint

        predictions = modelCNN.predict(testImages, batch_size=32) # Prezic etichetele pentru datele de test
        predictedLabels = [element.argmax() for element in predictions]

        return predictedLabels

    def create_submission(self, predictedLabels): # Functie pentru a crea o submisie
        index = 0
        submission = "id,label\n"
        txtName = "../input/competitie/test.txt"
        testImagesNames = []
        with open(txtName, "r") as reader:
            line = reader.readline()
            line = reader.readline()  # trec peste linia cu id
            while line != "":
                imageName = line.rstrip("\n")
                testImagesNames.append(imageName)
                line = reader.readline()

        for image in testImagesNames:
            line = image + ',' + str(predictedLabels[index]) + "\n"
            submission += line
            index += 1
        return submission

    def project(self): # Apelarea functiilor corespunzatoare pentru a obtine o submisie
        predictedLabels = self.training_and_predicting()
        submission = self.create_submission(predictedLabels)
        writer = open("mysubmission.txt", "w")
        writer.write(submission)
        writer.close()


if __name__ == "__main__":
    projectCNN = ProjectCNN()
    projectCNN.project()
    # Rezultatul se afla intr-un fisier intitulat mysubmission.txt care cuprinde pt fiecare imagine de test id ul si label-ul pe care
    # il asigneaza modelul meu.