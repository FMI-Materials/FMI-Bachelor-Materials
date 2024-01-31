# Broscoteanu Daria Mihaela
# Grupa 243

# Importuri

import numpy as np # Pentru prelucrari de array-uri
from sklearn.metrics import accuracy_score # Pentru a vedea acuratetea
from PIL import Image # Pentru porcesari de imagine
from PIL import ImageFilter # Pentru adaugarea de noise peste datele de train -> mai multe date de antrenare
import matplotlib.pyplot as plt # Pentru afisarea matricii de confuzie


# Clasa cu toate metodele relevante algoritmului
class ProjectKNN:
    def __init__(self):
        print()

    def add_noise(self, image): # functie folosita pentru a adauga blur peste o imagine
        newImage = image.filter(ImageFilter.GaussianBlur(3)) # am ales in mod aleator 3 ca parametru pentru bulr-ul gaussian
        return newImage

    def read_train_validation(self): # functie pentru citirea datelor de validare si de train
        # pentru datele de train
        txtName = "../input/competitie/train.txt"
        trainImages = []
        trainLabels = []

        with open(txtName, "r") as reader:
            line = reader.readline()
            line = reader.readline()  # trec peste linia cu id, label
            while line != "":
                imageName, imageLabel = line.rstrip("\n").split(",")  # linia are formatul numePoza.png,valoareLabel
                imagePath = "../input/competitie/train+validation/" + imageName # dau path-ul imaginii pe care vreau sa o citesc
                image = Image.open(imagePath)  # ma folosesc de Image din PIL pentru a deschide imaginea
                imgArray = np.array(image.getdata())  # preiau datele din aceasta imagine si le transform in np.array
                                                      # pentru a putea mai usor cu datele
                trainImages.append(imgArray) # adaug imaginea in vectorul corespunzator
                trainLabels.append(int(imageLabel)) # adaug labelul pozei in vectorul corespunzator

                newImage = self.add_noise(image) # adaug blur peste imaginea citita
                newImageArray = np.array(image.getdata()) # preiau datele din aceasta imagine si le transform in np.array
                                                          # pentru a putea mai usor cu datele
                trainImages.append(newImageArray) # adaug imaginea in vectorul corespunzator
                trainLabels.append(int(imageLabel))  # adaug labelul pozei in vectorul corespunzator

                line = reader.readline()

        # pentru datele de validare - abordez aceeasi procedare ca la datele de train
        validationImages = []
        validationLabels = []
        txtName = "../input/competitie/validation.txt"
        with open(txtName, "r") as reader:
            line = reader.readline()
            line = reader.readline()  # trec peste linia cu id, label
            while line != "":
                imageName, imageLabel = line.rstrip("\n").split(",")
                imagePath = "../input/competitie/train+validation/" + imageName
                image = Image.open(imagePath)
                imgArray = np.array(image.getdata())
                validationImages.append(imgArray)
                validationLabels.append(int(imageLabel))
                line = reader.readline()
        return trainImages, trainLabels, validationImages, validationLabels


    def read_test(self): # functie pentru citirea datelor de test
        txtName = "../input/competitie/test.txt"
        testImages = []
        with open(txtName, "r") as reader:
            line = reader.readline()
            line = reader.readline()  # trec peste linia cu id
            while line != "":
                imageName = line.rstrip("\n") # linia are formatul numePoza.png
                imagePath = "../input/competitie/test/" + imageName # dau path-ul imaginii pe care vreau sa o citesc
                image = Image.open(imagePath)  # ma folosesc de Image din PIL pentru a deschide imaginea
                imgArray = np.array(image.getdata())  # transform elementele imaginii in np array
                testImages.append(imgArray) # adaug imaginea la lista de imagini de test
                line = reader.readline()
        return testImages


    def create_submission(self, predictedLabels): # functie pentru crearea submisiei
        index = 0
        submission = "id,label\n"
        txtName = "../input/competitie/test.txt"
        testImagesNames = [] # imi creez o lista cu nuemle imaginilor de test asa cum se gasesc in test.txt
        with open(txtName, "r") as reader:
            line = reader.readline()
            line = reader.readline()  # trec peste linia cu id
            while line != "":
                imageName = line.rstrip("\n")
                testImagesNames.append(imageName)
                line = reader.readline()

        for image in testImagesNames: # parcurg numele acestor imagini
            line = image + ',' + str(predictedLabels[index]) + "\n" # imi formez lina de submisie pentru imaginea curenta
            # image reprezinta numele imaginii, dupa care concatenez o virgula
            # si adaug label-ul prezis din lista de labelul primita drept parametru
            submission += line  # adaug linia la submisie
            index += 1
        return submission

    # Abordare preluata si modificata din laborator
    def clasifica_imagine(self, imaginiTrain, labelsTrain, imagineTest, numar_vecini, metrica): # functie care clasifica o imagine de test
        # in functie de numarul de vecini si metrica primita ca parametru
        if metrica == 'l2': # implementez metrica l2 - am folosit l2 pt ca obtineam o acuratete mai buna
            distante_vecini = np.sqrt(np.sum(((imaginiTrain - imagineTest) ** 2), axis=2))
            distante_vecini = np.sqrt(np.sum(distante_vecini, axis=1))
        elif metrica == 'l1': # implementez metrica l1
            distante_vecini = np.sum(np.abs(imaginiTrain - imagineTest), axis=0)

        indecsi_vecini = distante_vecini.argsort() # ordonez indicii elementelor in functie de distanta
        indecsi_vecini = indecsi_vecini[:numar_vecini] # preiau primii k cei mai apropiati vecini ai imaginii pe care o clasific

        votare = labelsTrain[indecsi_vecini] # iau label-urile celor k vecini
        votare = np.reshape(votare, votare.size) # dau reshape pentru ca nu imi functiona bincount
        return (np.argmax(np.bincount(votare))) # returnez labelul majoritar in voting labels

    def clasifica_imagini(self, imaginiTrain, labelsTrain, imaginiTest, numar_vecini, metrica):
        numar = imaginiTest.shape[0]
        preziceri = np.array([0 for i in range(numar)]) # intialize vectorul de label-uri prezise cu 0
        for i in range(numar): # parcurg imaginile de test
            imagineTest = imaginiTest[i]
            eticheta = self.clasifica_imagine(imaginiTrain, labelsTrain, imagineTest, numar_vecini, metrica) # la pozitia i, pun in vectorul de label-uri predictia generata de functia de mai sus
            preziceri[i] = eticheta
        return np.array(preziceri)

    def scor_acuratete(self, labels, predictedLabels): # functie care calculeaza acuratetea
        return np.mean(labels == predictedLabels) # calculez media corespondentelor

    def matrice_confuzie(self, validationLabels, predicted_validation): # construiesc matricea de confuzie
        confusionMatrix = np.zeros((7, 7)) # construiesc o matrice 7 x 7 avand toate elementele 0
        index = 0
        for label in predicted_validation:
            confusionMatrix[validationLabels[index], predicted_validation[index]] += 1 # pentru fiecare label, adaug 1 in matricea e confuzie pe
                                                        # linia corespunzatoare label-ului corect si pe coloana labelului prezis de algoritmul meu
            index += 1
        return confusionMatrix

    def proiect(self):
        trainImages, trainLabels, validationImages, validationLabels = self.read_train_validation()  # apelez functia de citire
                                                                                            # a datelor de validare si de train
        trainImages = np.array(trainImages) # transform lista de imagini de train in np array
        trainLabels = np.array(trainLabels) # transform lista de label-uri de train in np array

        validationImages = np.array(validationImages) # transform lista de imagini de validare in np array
        validationLabels = np.array(validationLabels) # transform lista de label-uri de validare in np array

        testImages = self.read_test() # citesc imaginile de test
        testImages = np.array(testImages) # transform lista cu aceste imagini in np array

        etichete_validare = self.clasifica_imagini(trainImages, trainLabels, validationImages, 400, 'l2') # prezic label-urile pentru setul de validare pentru a determina acuratetea

        print(self.scor_acuratete(validationLabels, etichete_validare)) # afiez acuratetea, la ultima rulare era ~= 0.41
        confusionMatrix = self.matrice_confuzie(validationLabels, etichete_validare)  # generez matricea de confuzie
        plt.imshow(confusionMatrix) # plot-uiesc matricea de confuzie

        etichete_test = self.clasifica_imagini(trainImages, trainLabels, testImages, 400, 'l2') # prezic label-urile pentru setul de test

        submission = self.create_submission(etichete_test) # creez submisia cu functia de mai sus
        g = open("mysubmission.txt", "w") # scriu rezultatul in fisierul mysubmission.txt
        g.write(submission)
        g.close() # fisierul rezultat este cel pe care il pot uploada pe kaggle


if __name__ == '__main__':
    proiectKNN = ProjectKNN()
    proiectKNN.proiect()