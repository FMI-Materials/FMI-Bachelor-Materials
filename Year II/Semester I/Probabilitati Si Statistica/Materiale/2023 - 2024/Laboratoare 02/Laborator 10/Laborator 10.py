from pydataset import data
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import gaussian_kde
from scipy.stats import linregress

def ex1a():
    iris = data('iris')

    sepal_length = iris['Sepal.Length']
    petal_length = iris['Petal.Length']

    sepal_kde = gaussian_kde(sepal_length)
    sepal_range = np.linspace(sepal_length.min(), sepal_length.max(), 100)
    sepal_density = sepal_kde(sepal_range)

    petal_kde = gaussian_kde(petal_length)
    petal_range = np.linspace(petal_length.min(), petal_length.max(), 100)
    petal_density = petal_kde(petal_range)

    plt.figure(figsize=(8, 6))

    plt.plot(sepal_range, sepal_density, color='red', label='Sepal Length')

    plt.plot(petal_range, petal_density, color='blue', label='Petal Length')

    plt.xlabel('Length')
    plt.ylabel('Density')
    plt.title('Kernel Density Estimate (KDE) of Sepal and Petal Lengths')
    plt.legend()

    plt.grid(True)
    plt.show()

def ex1b():
    trees = data('trees')

    circumferinta = trees['Girth']
    inaltime = trees['Height']

    plt.figure(figsize=(8, 6))
    plt.scatter(circumferinta, inaltime, c='green', alpha=0.6, label='Circumference', marker='o')

    plt.xlabel('Circumferință')
    plt.ylabel('Înălțime')
    plt.title('Circumferința copacilor vs. Înălțimea lor')

    plt.grid(True)
    plt.show()

def ex1c():
    women = data('women')
    plt.figure(figsize=(8, 6))
    plt.scatter(women['height'], women['weight'])
    plt.title('Înălțime vs. Masă Corporală la Femei')
    plt.xlabel('Înălțime (inch)')
    plt.ylabel('Masă Corporală (lb)')
    plt.show()

def ex1d():
    trees = data('trees')
    circumference = trees['Girth']
    height = trees['Height']

    niu = np.mean(circumference)
    v = np.mean(height)

    circumference = circumference - niu
    height = height - v

    product = circumference * height
    sum = np.sum(product)
    cov = sum/len(trees)

    deviationCircumference = np.sqrt(np.sum((trees['Girth'] - niu)**2) / len(trees))
    deviationHeight = np.sqrt(np.sum((trees['Height'] - v)**2) / len(trees))

    corr = cov / (deviationCircumference * deviationHeight)

    print("Covarianta a:", cov)
    print("Correlation a:", corr)
    print()

    iris = data('iris')

    covarianceb = np.cov(iris['Sepal.Length'], iris['Petal.Length'])[0,1]
    correlationb = np.corrcoef(iris['Sepal.Length'], iris['Petal.Length'])[0,1]
    print("Covarianta b:", covarianceb)
    print("Correlation b:", correlationb)
    print()

    women = data('women')
    covariancec = np.cov(women['height'], women['weight'])[0,1]
    correlationc = np.corrcoef(women['height'], women['weight'])[0,1]
    print("Covarianta c:", covariancec)
    print("Correlation c:", correlationc)

def ex1e():
    trees = data('trees')
    circumference = trees['Girth']
    tree_height = trees['Height']

    iris = data('iris')
    sepal = iris['Sepal.Length']
    petal = iris['Petal.Length']

    women = data('women')
    height = women['height']
    weight = women['weight']

    def calculate_regression(x,y,xlab,ylab):
        slope, intercept, r_value, p_value, std_err = linregress(x,y)

        print(f'Ecuatia regresiei liniare: y = {slope:.4f} * x + {intercept:.4f}')
        print(f'Coeficient de determinare (R-squared): {r_value**2:.4f}')
        print(f'Slope: {slope}')
        print(f'Intercept: {intercept}')
        print()

        plt.scatter(x, y, label='Date reale')
        plt.plot(x, slope * x + intercept, color='red', label='Regresie liniara')
        plt.xlabel(xlab)
        plt.ylabel(ylab)
        plt.show()

    calculate_regression(circumference, tree_height, 'Circumference', 'Height')
    calculate_regression(sepal, petal, 'Sepal', 'Petal')
    calculate_regression(height, weight, 'Height', 'Weight')

def ex1g():
    women = data('women')
    weight = women['weight']
    height = women['height']

    weight80, weight20 = np.split(weight, [int(0.8 * len(weight))])
    height80, height20 = np.split(height, [int(0.8 * len(height))])

    slope, intercept, _ , _ , _ = linregress(weight80, height80)

    print(f"Coeficientul de înclinare (Slope): {slope}")
    print(f"Interceptul: {intercept}")

    height_pred = slope * weight20 + intercept

    print("\nValori reale vs. Predicția regresiei liniare:")
    comparison = np.column_stack((height20, height_pred))
    print(comparison)