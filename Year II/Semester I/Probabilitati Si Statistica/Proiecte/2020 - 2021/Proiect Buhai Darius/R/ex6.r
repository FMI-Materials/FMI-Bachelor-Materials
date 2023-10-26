library(pracma)

### Cerinta 6: Calculul mediei și dispersiei unei variabile aleatoare g(X), unde X are o repartiție continuă cunoscută
## iar g este o funcție continuă precizată de utilizator.

median_and_dispersion <- function(g, fx, domeniu_valori) {
  # y = g(X) e o noua variabila aleatoare, ii calculez media

  # folosesc formula pt media functiilor de x
  e_y <- integral(Vectorize(function(x){g(x) *fx(x)}),domeniu_valori[1],domeniu_valori[2])

  # pt dispersie, mai folosesc o data formula mediei functiilor de x
  # pentru a afla X^2
  e_y2 <- integral(Vectorize(function(x){x^2 * g(x) *fx(x)}),domeniu_valori[1],domeniu_valori[2])
  dispersie <- e_y2 - e_y^2

  print(paste("Media: ",e_y))
  print(paste("Dispersia:", dispersie))
}

# Example
# f1 <- function(x)(x^2)
# f2 <- function(x) (1 * exp(1)^(-1 * x))

# median_and_dispersion(f1,f2, c(0,Inf)) # 2, 20
