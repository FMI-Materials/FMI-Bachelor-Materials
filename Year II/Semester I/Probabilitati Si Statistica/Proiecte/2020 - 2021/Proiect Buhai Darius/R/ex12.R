library(pracma)

# suma a doua variabile aleatoare continue independente folosind formula de convolutie
convolution_sum <- function(fx,fy) {
  function(z) {
    integrate(function(y) {
      fx(z-y) * fy(y)
      },-Inf,Inf)
  } $ value
}

# diferenta a doua variabile aleatoare continue independente folosind formula de convolutie
convolution_diff <- function(fx,fy) {
  function(z) {
    integrate(function(y) {
      fx(y-z)*fy(y)
    },-Inf,Inf)
  } $ value
}

# Example:
# f_1 <- function(x)(dnorm(x,mean=1))
# f_2 <- function(x) (dnorm(x,mean=2))
# f_3 <- Vectorize(convolution_sum(f_1, f_2))
# f_4 <- Vectorize(convolution_diff(f_1,f_2))

# plot(f_1,from=-5,to=6,type="l")
# plot(f_2,from=-5,to=6,type="l")
# plot(f_3,from=-5,to=6,type="l")
# plot(f_4,from=-5,to=6,type="l")


