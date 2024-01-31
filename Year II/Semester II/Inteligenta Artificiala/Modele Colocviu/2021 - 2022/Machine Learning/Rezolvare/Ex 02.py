import numpy as np
import matplotlib.pyplot as plt

def similaritate(s1, s2, p):
    count = 0
    s1 = [x for x in s1]
    s2 = [x for x in s2]
    for i in range(0, len(s1) - p + 1):
        for j in range(0, len(s2) - p + 1):
            if s1[i:i+p] == s2[j:j+p]:
                count = count + 1

    return count

def classify(test_data):
    # calculam distantele de la imaginea de test
    # la toate imaginile de training

    diferente = np.zeros(len(train_data))

    for i in range(len(train_data)):
        diferente[i] = similaritate(train_data[i], test_data, 8)

    # pastrez cei mai apropiati K vecini

    # indicii elementelor sortate dupa suma
    indici = np.argsort(diferente)
    k = 5

    # returnez labelul cel mai frecvent printre vecini
    labels = []
    for i in range(k):
        labels.append(train_labels[indici[i]])

    label = max(labels, key = labels.count)
    
    return label

sim = similaritate("ananas copt", "banana verde", 4)

test_data = np.load("varianta2/test_data.npy", allow_pickle = True)
train_data = np.load("varianta2/train_data.npy", allow_pickle = True)
train_labels = np.load("varianta2/train_labels.npy", allow_pickle = True)

f = open("Lazaroiu_Teodora_241_subiect_2_solutia_1.txt", "w")

for test in test_data:
    label = classify(test)
    label = str(label) + '\n'
    f.write(label)

f.close()