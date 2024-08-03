# Lucru cu functii in R

f <- function()
{
  # optional return()
}

# Stocam expresii matematice
f1 <- function(x)
{
  x^2 / 3
}
f1(10)

f11 <- function(x)
{
  x <- x^2 / 3
}
y <- f11(10)
y # prints 33.3

# Functia integrate
a <- integrate(f1, 0, 1)
a$value

integrate(f1, 0, Inf)

fgama <- function(x, a)
{
  x^(a-1)*exp(-x)
}

integrate(fgama, 0, Inf, a = 10)


gama_teo <- function(x)
{
  if (x == round(x))
    return(factorial(x - 1))
  if (x > 1)
    return((x - 1.0) * gama_teo(x - 1.0))
  if (x == 0.5)
    return(sqrt(pi))
  return(integrate(fgama, 0, Inf, a = x)$value)
}

gama_teo(1.2)


# TEMA: Implementati functie care calculeaza beta(a, b) folosinddu-va de 
# proprietati si de integrala gama

# Reprezentarea grafica a functiilor

# Discretizarea intervalului pe care vrem sa reprezentam grafic functia
t <- seq(-5, 8, 0.01)
plot(t, f1(t), col="magenta")

# Sa se reprezinte grafic sirul de functii fn(x) = x^n pe [0, 1]
t <- seq(0, 1, 0.001)
plot(t, t, col="magenta")
plot.new();

for (i in 2:100)
  lines(t, t^i, col=i)

# Pachetul DiscrereRV

X <- RV(c(1, 7, 9), c(1/3, 1/2, 1/6))
X1 <- RV(1:100)
P(X1 < 10)
plot(X)

X2 <- RV(c(-10:10, 14, 29, 49, 102))
P((X2 > 8) %AND% (X2 < 50))

