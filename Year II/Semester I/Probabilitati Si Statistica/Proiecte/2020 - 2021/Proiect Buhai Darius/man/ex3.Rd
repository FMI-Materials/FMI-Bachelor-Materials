\name{ex3}
\alias{Random Variable Object}
\title{Random Variable Object}
\usage{
  Continuous_RV object_name
  init(object_name, pdf)
  show(object_name)
}
\description{
  Crearea unui obiect de tip variabilă aleatoare continuă pornind de la o densitate de
probabilitate introdusă de utilizator.
}
\examples{
  f <- function(x){
  return (exp((-x^2)/2))
  }
  Continuous_RV obj
  init(obj, f)
  show(obj)
}
