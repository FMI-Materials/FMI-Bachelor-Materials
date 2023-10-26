\name{ex6}
\alias{median_and_dispersion}
\title{Median and Dispersion of g(X) and X, on a given repartition}
\usage{
  median_and_dispersion(f1,f2, d)
}
\description{
  Calculul mediei și dispersiei unei variabile aleatoare g(X), unde X are o repartiție continuă cunoscută iar g este o funcție continuă precizată de utilizator.
}
\examples{
  f1 <- function(x)(x^2)
  f2 <- function(x) (1 * exp(1)^(-1 * x))

  median_and_dispersion(f1,f2, c(0,Inf))
}
