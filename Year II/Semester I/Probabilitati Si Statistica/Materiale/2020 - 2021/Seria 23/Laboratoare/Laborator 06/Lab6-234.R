#Lucru cu functii in R

f <- function()
{
  #optional return()
}

#Stocam expresii matematice
f1 <- function(x)
{
  x^2/3
}
f1(3)
#Fenomen ciudat
f11 <- function(x)
{
  x <- x^2/3
}
f11(3)
y <- f11(3)

#Functia integrate

a <- integrate(f1,0,1)
a$value
# Functia integrate lucrareaza si cu capete infinite, dar
#numai daca integrala e convergenta
integrate(f1,0,Inf)

fgama <- function(x,a)
{
  x^(a-1)*exp(-x)
}

integrate(fgama,0,Inf,a=7)
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


#SOlutie Darius Buhai
gama_bhd <- function(n)
{
  if(n==1)
    return(1)
  if(n==round(n)) # n-floor(n)==0 
    return(factorial(n-1))
  if(n==.5)
    return(sqrt(pi))
  if(n<1)
    return(integrate(fgama, 0, Inf, a=n))
               #BUBA
    return((n-1)*gama_bhd(n-1))
  
}

gama_bhd(9/4)

#Solutie Stelian Chichirim
gama_SCH <- function(n)
{
  if (n == 0.5) return(sqrt(pi))
  if (n == 1) return(1)
  if (n < 1) return(integrate(fgama, 0, Inf, a = n))
  if (n == floor(n)) {
    return(factorial(n - 1))
  }
  return((n - 1) * gama_SCH(n - 1))
}

gama_SCH(9/4)

#Solutia Bogdan Popa
gama_bip <- function(n)
{
  if(n == .5) {
    return(sqrt(pi))
  }
  
  if(n < 1) {
    return(integrate(fgama, 0, Inf, a = n))
  }
  
  if(n == round(n)) {
    return(factorial(n - 1))
  }
  
  return((n - 1) * gama_bip(n - 1))
}

#Solutia Theodor Moroianu

gama_teo <- function(x)
{
  if (x == round(x))
    return(factorial(x - 1))
  if (x > 1)
    return((x - 1.) * gama_teo(x - 1))
  if (x == 0.5)
    return(sqrt(pi))
  return(integrate(fgama, 0, Inf, a = x)$value)
}

#Optimizati solutia folosind switch sau altfel :)
#TEMA: Implementati o functie care calculeaza beta(a,b) folosindu-va de proprietati
#si de integrala gama

#Reprezentarea grafica a functiilor
#Discretizarea intervalului pe care vrem sa reprezentam grafic functia
t <- seq(-5,8,0.001)
plot(t,f1(t),col="magenta")
# Sa se reprezinte grafic sirul de functii fn(x)=x^n pe [0,1]
t <- seq(0,1,0.001)
plot(t,t,col="magenta")
for (i in 2:7)lines(t,t^i,col=i)

# Lucru cu DiscreteRV
#creez o v.a.
X <- RV(c(1,7,9),c(1/3,1/2,1/6))
X1 <- RV(1:100)
P(X1<22)
plot(X)
X2 <- RV(c(-10:10,14,29,49,102))
#P(8<X2<50)
P((X2>8)%AND%(X2<50))





