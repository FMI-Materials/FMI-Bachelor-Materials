# Examen ML

## Links

Link la intrebari din anii trecuti:
    - [CheatSheet](https://docs.google.com/document/d/1a0W5_j6gT0kQ6bveNjJczeOU4dyit6JesaGqSxg30Nk/edit)
    - [Exercitii rezolvate](https://docs.google.com/document/d/13WX6yz3jVaoXQnxX0Lkii8X939P5BjPZfCSC1dFEbzk/edit#heading=h.iu429wxt7qcc)

## Formule

```
D_1((a, b), (x, y)) = rad_1(abs(a - x)^1 + abs(b - y)^1)
D_2((a, b), (x, y)) = rad_2(abs(a - x) ^ 2 + abs(b - y) ^ 2)
```

```
Precision           = TP/(TP+FP)
Sensitivity(recall) = TP/(TP+FN)
Specificity         = TN/(TN+FP)
Accuracy            = (TP+TN)/(TP+TN+FP+FN)
F1                  = 2/(1/Precision+1/Recall)
```

# Bayes
```
P(A|B) = P(B|A) * P(A) / P(B)
P(A|B) = P(A & B) / P(B)
```
# Kendall Tau 

```
(perechi concordante - perechi discordante) / C n luate cate 2 
```

# Functii Kernel

1. Functia RBF

Forma duala al unei matrice X: X.dot(X.T)
Forma al lui X_test, dandu-se X_train este
```
X_test.dot(X_train.T)
```

# Blestemul dimensionalitatii

Nevoie de 5^dimensiune date

# Functii de performanta

1. MSE -> Regresie
2. Media erorilor in valoare absolutia (MAE) -> Regresie
3. True positive ... matrice de confuzie -> Clasificare
4. Misclassificaiton error -> Clasificare

# Normalizare L1:

input: E
R: E / np.abs(E).sum()

# Regresii

1. Regresia Ridge: 𝑐𝑜𝑠𝑡𝑅𝑖𝑑𝑔𝑒 (𝑦, 𝑦ℎ𝑎𝑡 ) = 𝛴 (𝑦ℎ𝑎𝑡𝑖 − 𝑦𝑖)^2+ 𝛼||𝑊||_2
! alpha determina cat de mici sunt ponderile

2. Regresia Lasso - la fel ca la Ridge dar norma este L1

# Convolutii Calculator

Formula:

input: WxHxD
filtre: K
filtre_dim: FxF
stride: S
padding: P

R: (W - F + 2P) / S + 1

## eg.
strat de pooling=11x11
stride=4
intrare=227x227
pdding=0
R: (227 - 11 + 2 * 0) / 4 + 1

# Calcul perceptroane: 

input: X
layer_1: W1, B1
activation_1: ReLU
layer_2: W2, B2
activation_2: ReLU

R:  A_1 = (x.dot(W1)+B1).clip()
    A_2 = (A_1.dot(W2)+B2).clip()


# Bias - Variance

Imbunatati capacitatea de generalizare (p. 115):
 1. Early stopping
 2. Regularizare

Bias - underfitting (p. 82):
 * Eroare sistematica din inabilitatea de-a invata adevarata relatie dintre trasaturi.
 * Poate fi corectat prin cresterea complexitatii modelului

Variance - varianta - overfitting (p.82):
 * Erare din senzitivitatea ridicata la mici fluctuatii
 * Poate fi corectat prin:
   1. Adaugarea de exemple
   2. Scaderea complexitatii modelului
   3. (regularizare)