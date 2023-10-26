
library(mlr3misc)
library(R6)

data = Dictionary$new()

item = R6Class("Item")

########## UNIFORM ###########

data_aux = Dictionary$new()
data_aux$add("Sursa", R6Class(public = list(print = "Curs + Wikipedia")))
data_aux$add("Notatie", R6Class(public = list(print = "U(a, b)")))
data_aux$add("Parametri", R6Class(public = list(print = "-Inf < a < b < Inf")))
data_aux$add("Domeniu", R6Class(public = list(print = "x in [a, b]")))
data_aux$add("PDF", R6Class(public = list(print = "1 / (b - a)")))
data_aux$add("CDF", R6Class(public = list(print = "(x - a) / (b - a)")))
data_aux$add("Mediana", R6Class(public = list(print = "(1 / 2) * (a + b)")))
data_aux$add("Media", R6Class(public = list(print = "(1 / 2) * (a + b)")))
data_aux$add("Utilizari", R6Class(public = list(print = "In economie, pentru managerierea inventarului, cand un produs complet nou este analizat, distributia uniforma e cea mai utila.")))
data$add("uniform", data_aux)

########## EXPONENTIAL ###########

data_aux = Dictionary$new()
data_aux$add("Sursa", R6Class(public = list(print = "Curs + Wikipedia")))
data_aux$add("Parametri", R6Class(public = list(print = "labmda > 0")))
data_aux$add("Domeniu", R6Class(public = list(print = "x in [0, +Inf]")))
data_aux$add("PDF", R6Class(public = list(print = "lambda * exp(1)^(-lambda * x)")))
data_aux$add("CDF", R6Class(public = list(print = "1 - exp(1)^(-lambda * x)")))
data_aux$add("Media", R6Class(public = list(print = "1 / labmda")))
data_aux$add("Mediana", R6Class(public = list(print = "ln2 / lambda")))
data_aux$add("Utilizari", R6Class(public = list(print = "Dupa observarea unui set de n puncte dintr-o distibutie exponentiala necunoscuta, se pot face predictii destul de precise despre viitor, pe baza datelor sursa.")))
data$add("exponential", data_aux)

########## NORMAL ###########

data_aux = Dictionary$new()
data_aux$add("Sursa", R6Class(public = list(print = "Curs + Wikipedia")))
data_aux$add("Notatie", R6Class(public = list(print = "N(mu, sigma^2)")))
data_aux$add("Parametri", R6Class(public = list(print = "mu in R, sigma ^ 2 >= 0")))
data_aux$add("Domeniu", R6Class(public = list(print = "x in [-Inf, +Inf]")))
data_aux$add("PDF", R6Class(public = list(print = "(1 / (sigma * sqrt(pi * 2)))*(exp(1)^((-(x - mu)^2)/(2  * sigma ^ 2)))")))
data_aux$add("CDF", R6Class(public = list(print = "(1 / 2) * (1 + erf((x - mu) / (sigma * sqrt(2)))")))
data_aux$add("Media", R6Class(public = list(print = "mu")))
data_aux$add("Mediana", R6Class(public = list(print = "mu")))
data_aux$add("Utilizari", R6Class(public = list(print = "Poate fi observata in ziua de zi cu zi. De exempul distributia notelor unor studenti la examenul de Probabilitati si Statistica.")))
data$add("normal", data_aux)

########## PARETO ###########

data_aux = Dictionary$new()
data_aux$add("Sursa", R6Class(public = list(print = "Curs + Wikipedia")))
data_aux$add("Parametri", R6Class(public = list(print = "m > 0, alpha > 0")))
data_aux$add("Domeniu", R6Class(public = list(print = "x in [m, +Inf]")))
data_aux$add("PDF", R6Class(public = list(print = "(alpha * m^alpha) / (x ^ (alpha + 1))")))
data_aux$add("CDF", R6Class(public = list(print = "(1 - (m ^ alpha) / (x ^ alpha))")))
data_aux$add("Media", R6Class(public = list(print = "Inf, alpha <= 1\n (alpha * m) / (alpha - 1), alpha > 1")))
data_aux$add("Mediana", R6Class(public = list(print = "m * sqrt_alpha(2)")))
data_aux$add("Utilizari", R6Class(public = list(print = "A fost folosita de catre creatorul ei, Vilfredo Pareto, pentru analiza distributiei banilor intre indivizi. Aceasta arata destul de precis cum cea mai mare cantitate de bani este controlata de un procent foarte mic din populatie.")))
data$add("pareto", data_aux)

########## CAUCHY ###########

data_aux = Dictionary$new()
data_aux$add("Sursa", R6Class(public = list(print = "Curs + Wikipedia")))
data_aux$add("Parametrii", R6Class(public = list(print = "x0, y > 0")))
data_aux$add("Domeniu", R6Class(public = list(print = "x in [-Inf, Inf]")))
data_aux$add("PDF", R6Class(public = list(print = "1 / (pi * y * (1 + (x - x0) / y)^2)")))
data_aux$add("CDF", R6Class(public = list(print = "(1 / pi) * arctan((x - x0) / y) + (1/2)")))
data_aux$add("Mediana", R6Class(public = list(print = "x0")))
data_aux$add("Media", R6Class(public = list(print = "undefined")))
data_aux$add("Utilizari", R6Class(public = list(print = "Distributia Cauchy este folosita des in analiza distributiei observatiilor facute de catre oameni de stiinta despre despre obiecte care se invartesc.")))
data$add("cauchy", data_aux)

########## WEIBULL ###########

data_aux = Dictionary$new()
data_aux$add("Sursa", R6Class(public = list(print = "Wikipedia")))
data_aux$add("Parametri", R6Class(public = list(print = "lambda in (0,+inf) da scara, k in (0,+inf) da forma")))
data_aux$add("Domeniu", R6Class(public = list(print = "x in [0, +inf]")))
data_aux$add("PDF", R6Class(public = list(print = "k/lambda * (x/lambda) ^ (k-1) * e^(-(x/lambda)^k), x>=0, altfel 0")))
data_aux$add("CDF", R6Class(public = list(print = "1-e^((-x/lambda)^k), x>=0, altfel 0")))
data_aux$add("Mediana", R6Class(public = list(print = "lambda * (ln 2)^(1/k)")))
data_aux$add("Media", R6Class(public = list(print = "(lambda * gamma(1+1/k)")))
data_aux$add("Utilizari", R6Class(public = list(print = "In meteorologie, folosita la prezicerea distributiei vitezei vantului, in ingineria electrica.")))
data$add("weibull", data_aux)


########## LOGISTIC ###########

data_aux = Dictionary$new()
data_aux$add("Sursa", R6Class(public = list(print = "Curs + Wikipedia")))
data_aux$add("Parametrii", R6Class(public = list(print = "u, s>0")))
data_aux$add("Domeniu", R6Class(public = list(print = "x in [-Inf, Inf]")))
data_aux$add("PDF", R6Class(public = list(print = "(e^(-(x-u)/s))/(s*(1+e^(-(x-u)/s))))^2")))
data_aux$add("CDF", R6Class(public = list(print = "1/(1+e^(-(x-u)/s)))")))
data_aux$add("Mediana", R6Class(public = list(print = "u")))
data_aux$add("Media", R6Class(public = list(print = "u")))
data_aux$add("Utilizari", R6Class(public = list(print = "Este adesea folosita in regresia logistica si in Retelele Neuronale de tip 'feedforward'.")))
data$add("logistic", data_aux)


########## FUNCTIE DE AFISARE ###########

output_details <- function(distribution_name) {
  out_data = data$get(distribution_name)
  for (key in out_data$keys()) {
    print(noquote(paste(key, ": ", out_data$get(key)$print, sep="")))
  }
}


# Examples:
#
# output_details("uniform")
# output_details("exponential")
# output_details("normal")
# output_details("pareto")
# output_details("cauchy")
# output_details("logistic")
# output_details("weibull")
