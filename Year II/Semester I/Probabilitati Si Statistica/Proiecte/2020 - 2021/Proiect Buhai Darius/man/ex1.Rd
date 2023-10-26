\name{ex1}
\alias{Normalizing Constant}
\title{Normalizing Constant}
\usage{
  compute_normalizing_constant(f, lowerBound=-Inf, upperBound=Inf)
}
\description{
  Fiind dată o funcție f, introdusă de utilizator, determinarea unei constante de normalizare k. Ȋn cazul ȋn care o asemenea constantă nu există, afișarea unui mesaj corespunzător către utilizator.
}
\examples{
 f <- function(x){
    return (exp((-x^2)/2))
  }
  compute_normalizing_constant(f, 0, 1)
  compute_normalizing_constant(f)
}
