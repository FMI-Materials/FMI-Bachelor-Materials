\name{ex2}
\alias{check_pdf}
\title{Check Pdf}
\usage{
  check_pdf(f)
}
\description{
  Verificarea dacă o funcție introdusă de utilizator este densitate de probabilitate.
}
\examples{
  f1 <- function(x){
    if (x > 0 && x < 2){
      3/8 * (4*x-2*x^2)
    }else{
      0
    }
  }

  check_pdf(f1)

  f2 <- function(x){
    x * (4*x-2*x^2)
  }

  check_pdf(f2)
}
