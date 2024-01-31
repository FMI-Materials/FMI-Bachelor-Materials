import numpy as np
import matplotlib.pyplot as plt
from sklearn import svm

training_sentences = np.load("training_sentences.npy", allow_pickle = True)
test_sentences = np.load("test_sentences.npy", allow_pickle = True)
training_labels = np.load("training_labels.npy", allow_pickle = True)
test_labels = np.load("test_labels.npy", allow_pickle = True)

# facem un vocabular cu toate cuvintele

vocabular = []
for sent in training_sentences:
    for cuv in sent:
        if cuv not in vocabular:
            vocabular.append(cuv)

# print(vocabular)

# lista de vectori de frecventa
# pentru fiecare propozitie

frecv = [[] for x in range(len(training_sentences))]

for i, sent in enumerate(training_sentences):
    for cuv in vocabular:
        frecv[i].append(sent.count(cuv))

# print(frecv[0])

frecv = np.array(frecv)

model = svm.SVC()
model.fit(frecv, training_labels)

frecv_test = [[] for x in range(len(test_sentences))]

for i, sent in enumerate(test_sentences):
    for cuv in vocabular:
        frecv_test[i].append(sent.count(cuv))

acuratete = np.mean(model.predict(frecv_test) == test_labels)
print(acuratete)






