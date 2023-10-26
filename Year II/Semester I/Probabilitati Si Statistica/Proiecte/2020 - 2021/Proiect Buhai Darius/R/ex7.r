####
# Cerinta: Crearea unei funcții P care permite calculul diferitelor tipuri de
# probabilități asociate unei variabile aleatoare continue(similar funcției P din pachetul discreteRV)
#
# Header functie: myP(f, p)
#    - unde f este o functie densitate de probabilitate (pdf)
#    - iar p este un string ce reprezinta probabilitatea (conditionata sau independenta).
#
# Obligatoriu, var se va afla in stanga operatorului

####


myP <- function(f, p) {
  operatii_posibile=c("<=",">=","=","<",">")

  # transforma string-ul dat in ceva ce pot utiliza
  parseaza_expresie <- function(expresie) {

    # scot whitespace
    expresie <- gsub(" ", "", expresie)

    for(op in operatii_posibile) {

      # am dat split corect => in stanga am variabila, in dreapta am bound-ul
      split <- unlist(strsplit(expresie, op, fixed = TRUE))
      splitSize <- length(split)

      if (splitSize == 2) {
        # returnez (v.a.c, operatie, bound)
        return (c(split[1],op,split[2]))
      }
    }
    return(c(-1))


  }

# calculez cdf, adica integrala -inf, bound, adica P(X <= bound)
cdf <- function(bound) { return (integrate(f, -Inf, bound) $ value)}

# transform din string in double
compute_bound <-function(bound) {
  rez <- switch(bound,
                "-Inf" = -Inf,
                "+Inf" = +Inf,
                as.double(bound))
  return (rez)
}

## Calculeaza probabilitatea ##
evalueaza <- function(operator, bound) {

  # parsez bound-ul, transform in double sau in +-inf
  bound = compute_bound(bound)
  integrala <- cdf(bound)

  #pentru >,>= din toata aria(1) scad cdf-ul si obtin restul
  ans <- switch(
    operator,
    "=" = 0,
    "<=" = integrala,
    "<" = integrala,
    ">=" = 1 - integrala,
    ">" = 1 - integrala)

  return(ans)

  }

# daca am o singura expresie e prob independenta
prob_independenta <- function(expresie) {

  # scot parametri din expresie
  parametri <- parseaza_expresie(expresie)

  if(length(parametri) != 3)
    return("Eroare la parsarea probabilitatii")

  # aici presupun ca expresiile mele sunt mereu de forma x operator bound
  # ar trebui o verificare, poate, a ordinii

  operator <- parametri[2]
  bound <- parametri[3]

  print(evalueaza(operator, bound))

}

#daca am 2 expresii e prob conditionata
prob_conditionata <- function(expresie1, expresie2) {

  # scot parametri in variabile ca sa fie readable ce fac mai jos
  parametri1 <- parseaza_expresie(expresie1)
  parametri2 <- parseaza_expresie(expresie2)
  op1 <- parametri1[2]
  op2 <- parametri2[2]
  bound1 <- parametri1[3]
  bound2 <- parametri2[3]

  # am formula P(a depinde de b) = P(a intersectat b)/P(b)
  # calculez cdf pentru fiecare functie si iau pe cazuri
  ans1 <- evalueaza(op1, bound1)
  ans2 <- evalueaza(op2, bound2)

  # daca vreuna e 0, intersectia va da 0
  if(ans1 == 0)
      return(0);
  if(ans2 == 0)
      return ("Cannot divide by zero")

  ## cazuri

  ## caz in care conditionarea face probabilitatea sa fie imposibila
  # p(x < 3 | x > 5) = 0
  if (op1 %in% c("<=","<") && op2 %in% c(">=", ">") && bound1 >=bound2)
    return (0);

  # p(x > 5 | x < 3) = 0
  if (op1 %in% c(">=",">") && op2 %in% c("<=", "<") && bound1 >=bound2)
    return (0);

 ## caz in care am acelasi fel de operator, facand intersectia defapt doar aleg intervalul cel mai restrans
  # p(x> 3 | x>7) => iau (-inf,3)
  if(op1 %in% c(">=",">") && op2 %in% c(">=",">"))
    if(bound1 > bound2)
      return (ans1/ans2)
    else return (1);
 # p( x<3 | x<7) => iau (-inf,3)
  if(op1 %in% c("<=","<") && op2 %in% c("<=","<"))
    if(bound1 < bound2)
    return (ans1/ans2)
    else return (1)

  ## daca nu e niciunul de mai sus, e intersectie de forma x > 5 | x < 7 si fac diferenta
  ## din cdf mai mare scad cdf mai mic si mi da bucata de dintre => intersectia
  return ((cdf(compute_bound(bound2))-cdf(compute_bound(bound1)))/ans2)

}

  # parsez parametri
  parti = unlist(strsplit(p, "|", fixed = TRUE))
  len = paste(length(parti))
  switch(len,
         "0" = return("Eroare"),
         "1" = return(prob_independenta(p)),
         "2" = return(prob_conditionata(parti[1],parti[2])),
         )
  return ("eroare");

}
# Example:
# g <- function (x) {
#  fun <- 0.1*(3*(x^2) + 1)
#  fun[x<0] = 0
#  fun[x>2]=0
#  return ( fun )
# }
#
# h <- function(x)(dunif(x))
# myP(g,"x>1|x<1.5") # 0.5897078
# myP(h,"x>0.6") # 0.4
