\name{ex5}
\alias{initial_moment and central_moment}
\title{Central and Intial moments}
\usage{
  initial_moment(pdf, order)
  central_moment(pdf, order)
}
\description{
  Calculul mediei, dispersiei si a momentelor initiale si centrate pana la ordinul 4 (daca exista).
}
\examples{
  f = function (x) {
    if(x<0 || x>1)
      return(0)
    x ^ 3
  }

  initial_moment(f, 2)
  central_moment(f, 2)
}
