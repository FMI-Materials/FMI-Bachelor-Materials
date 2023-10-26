# compute the normalizing constant of a pdf

compute_normalizing_constant <- function(f, lowerBound=-Inf, upperBound=Inf){
  tryCatch(
    expr = {
      # compute the integral
      integral <- integrate(f, lower = lowerBound, upper = upperBound)$value
      # the constant is 1 / computed integral
      normalizing_constant <- 1 / integral
      return(normalizing_constant)
    },
    error = function(e){
      message('Caught an error!')
      print(e)
      return(0)
    },
    warning = function(w){
      message('Caught a warning!')
      print(w)
    },
    finally = {
      message('')
    }
  )
}
