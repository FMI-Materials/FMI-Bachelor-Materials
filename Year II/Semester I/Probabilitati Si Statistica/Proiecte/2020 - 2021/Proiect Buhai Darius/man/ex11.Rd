\name{ex11}
\alias{marginal_and_conditional_density}
\title{Marginal and Conditional Density}
\usage{
  marginal_conditional_densities(f, x, y, ab, cd)
}
\description{
  Construirea densităților marginale și a densităților condiționate, pornind de la densitatea comună a două variabile aleatoare continue.
}
\examples{
  f <- function (x, y) {
     return ((3/2) * (x^2+y^2))
  }
  marginal_conditional_densities(f, 0.5, 0.5, c(0,1), c(0,1))
}
