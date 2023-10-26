\name{ex11}
\alias{convolution_sum and convolution_diff}
\title{Sum and difference of 2 pdfs}
\usage{
  convolution_sum(fx, fy)
  convolution_diff(fx, fy)
}
\description{
  Construirea sumei și diferenței a două variabile aleatoare continue independente folosind formula de convoluție
}
\examples{

  f_1 <- function(x)(pnorm(x,mean=1))
  f_2 <- function(x)(pnorm(x,mean=2))
  f_3 <- Vectorize(convolution_sum(f_1, f_2))
  f_4 <- Vectorize(convolution_diff(f_1,f_2))
  frez <- Vectorize(f_3)

  t = seq(1,10)
  plot(f_1,from=-10,to=10,type="l")
  plot(f_2,from=-10,to=10,type="l")
  plot(f_3(t),from=-10,to=10,type="l")
  plot(f_4(t),from=-10,to=10,type="l")
}
