#Stocam expresii matematice
f1 <- function(x)
{
  x^2/3
}
f1(3)
#
f11 <- function(x)
{
  x <- x^2/3
}
f11(3)
y <- f11(3)
# Functia integrate
a <- integrate(f1, 0, 1)
a$value
# Functia integrate lucreaza si cu capete infinite,
# dar numai daca integrala e convergenta
integrate(f1, 0, Inf)
#
fgama <- function(x, a)
{
  x^(a-1)*exp(-x)
}
integrate(fgama, 0, Inf, 7)
factorial(6)
#Creati o functie in R numita gama_nume care sa implementeze proprietatile
#pe care le are functia gama(vezi documentul Integrale euleriene) si sa 
#foloseasca apelul functiei integrate doar atunci cand parametrul nu satisface 
#nicio conditie "buna"

# gama_nume <- function(....)
#{
#daca n e natural atunci foloseste propr. 3)     #folosim functia din R numita factorial
#daca n e de forma b/2(cu b natural) foloseste formula 2) si 4)
#altfel foloseste formula 2) pana cand argumentul devine subunitar
#si doar pentru acea valoare calculeaza cu integrate
gama_bhd <- function(n)
{
  if(n<0) stop("Gama e definita pe (0, +inf)")
  if(n==round(n)) return(factorial(n-1))
  if(n==.5) return(sqrt(pi))
  if(n<1)
    return(integrate(fgama, 0, Inf, a=n)$value)
  return((n-1)*gama_bhd(n-1))
}
gama_bhd(9/4)
# Reprezentarea grafica a functiilor
# Discretizarea intervalului pe care vrem sa reprezentam grafic functia
t <- seq(-5,8,0.001)
plot(t, f1(t), col="magenta")
lines(t)
# Sa se reprezinte grafic sirul de functii fn(x)=x^n pe [0,1]
t <- seq(0,1,0.001)
plot(t, t,col="magenta")
for (i in 2:7) lines(t, t^i, col=i)
# Lucru cu DiscreteRV
# creez o v.a.
X <- RV(c(1,7,9), c(1/3,1/2,1/6))
# TEMA: Implementati functie care calculeaza Beta(a, b), folosindu-va de proprietati
# si de integrala gama
beta_bhd <- function(a, b)
{
  # TEMA...
}



