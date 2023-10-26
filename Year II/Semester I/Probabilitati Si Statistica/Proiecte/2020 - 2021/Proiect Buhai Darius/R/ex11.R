library(pracma)

# conditia 1 pentru o functie de densitate corecta
# f trebuie sa aiba valori pozitive pentru
# toate valorile din domeniu
# cum in domeniu sunt o infinitate de puncte
# am ales sa verific 'pe sarite' o parte dintre ele
check_positive_2d <- function(f, ab, cd, step) {
  for (x in seq(ab[1], ab[2], step)) {
    for (y in seq(cd[1], cd[2], step)) {
      if (f(x, y) < 0) return(FALSE)
    }
  }

  return(TRUE)
}

# conditia 2 pentru o functie de densitate corecta
# f terbuie sa aiba probabilitatea totala egala cu 1
# pentru a calcula integrala dubla am folosit functia
# 'integral2' din pachetul 'pracma'
check_integral_is_1 <- function(f, ab, cd) {
  integral <- integral2(f, ab[1], ab[2], cd[1], cd[2])$Q
  return(abs(integral - 1) < 0.0000000001)
}

# intoarce o noua functie g(y) definita
# ca f(x, y), unde x este o valoare fixata
f_set_x <- function(x, f) function(y) f(x, y)

# intoarce o noua functie g(x) definita
# ca f(x, y), unde y este o valoare fixata
f_set_y <- function(y, f) function(x) f(x, y)

# calculeaza densitatea marginala in X
# il setam pe x si integram peste y
x_marginal_pdf <- function(f, x, c, d) {
  return (integrate(f_set_x(x, f), c, d)$value)
}

# calculeaza densitatea marginala in Y
# il setam pe y si integram peste x
y_marginal_pdf <- function(f, y, a, b) {
  return (integrate(f_set_y(y, f), a, b)$value)
}

# calculeaza densitatea in X conditionata de Y = y
h_x_conditioned_by_y <- function(y, x, f, c, d) {
  f(x, y) / x_marginal_pdf(f, x, c, d)
}

# calculeaza densitatea in Y conditionata de X = x
h_y_conditioned_by_x <- function(x, y, f, a, b) {
  f(x, y) / y_marginal_pdf(f, y, a, b)
}

marginal_conditional_densities <- function(f, x, y, ab, cd) {

  tryCatch({
    if (!check_positive_2d(f, ab, cd, 0.01)) {
      print("functia nu este pozitiva pentru valorile din domeniu")
      return ()
    }

    if (!check_integral_is_1(f, ab, cd)) {
      print("probabilitatea totala este diferita de 1")
      return ()
    }

    print(paste("testez cu x=", x, " y=", y, " pe [", ab[1], ",",
                ab[2], "]x[", cd[1], ",", cd[2], "]", sep=""))

    # densitatea marginala pentru X cu x fixat
    print(paste("pdf marginal cu x fixat:", x_marginal_pdf(f, x, cd[1], cd[2])))

    # densitatea marginala pentru Y cu y fixat
    print(paste("pdf marginal cu y fixat:", y_marginal_pdf(f, y, ab[1], ab[2])))

    # densitatea conditionata in x cand Y = y
    print(paste("pdf conditionat de y=", y, ": ", h_x_conditioned_by_y(y, x, f, cd[1], cd[2]), sep=""))

    # densitatea conditionata in y cand X = x
    print(paste("pdf conditionat de x=", x, ": ", h_y_conditioned_by_x(x, y, f, ab[1], ab[2]), sep=""))
  }, error = function(e) {
    print(paste("A aparut o eroare", e, sep = " "))
  })
}

# Examples:
#
# f <- function(x, y) (8 / 3) * x ^ 3 * y
# marginal_conditional_densities(f, 0.5, 1.5, c(0, 1), c(1, 2))
#
# f <- function(x, y) (3 / 2) * (x ^ 2 + y ^ 2)
# marginal_conditional_densities(f, 0, 0.5, c(0, 1), c(0, 1))
