\name{ex9}
\alias{Random Values Generator}
\title{Random Values Generator}
\usage{
  random_variable_generator(f, n, lowerBound, upperBound)
}
\description{
  Generarea a n valori dintr-o repartiție de variabile aleatoare continue.
}
\examples{
  f <- function(x) (3*x^2 + 1) * (0 < x & x <= 2)
  random_variable_generator (f, 50, 0, 2)
}
