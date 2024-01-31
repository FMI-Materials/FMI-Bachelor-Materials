import numpy as np
import matplotlib.pyplot as plt

# regresii liniare

# puncte cu 2 coordonate de la 0 la 10
x_train = np.random.random(1000,2) * 10
x_test = np.randon.random(500,2) * 10

y_train = 3.5 * x_train [:,0] + 5.7 * x_train[:,1] - 3.2 + np.random.randn(1000,2) * 0.1
y_test = 3.5 * x_test [:,0] + 5.7 * x_test[:,1] - 3.2 + np.random.randn(500,2) * 0.1

w1 = np.random.randn()
w2 = np.random.randn()
b = np.random.randn()

for epoch in range(20):
    #calculate errors (using derivative formula E(w) - w0 / w - w0)
    for sample,target in zip(x_train,y_train):
        par = w1*sample[0]+w2*sample[1]+b-target
        #calculate derivative dE/dw1 ((w1x1+w2x2+b-t)^2) = 2*(w1x1+w2x2+b-t)*(x1)
        w1 = w1 - 2 * par * sample[0] * lr
        w2 = w2 - 2 * par * sample[1] * lr
        b = b - 2 * par * 1 * lr

    print("w1,w2,b: ",w1,w2,b)

    test_predictions = []
    for test_sample in x_test:
        test_predictions.append(w1*test_sample[0]+w2*test_sample[1]+b)
    test_predictions=np.array(test_predictions)
    print("mean:    ",np.mean(np.abs(test_predictions-y_test)))