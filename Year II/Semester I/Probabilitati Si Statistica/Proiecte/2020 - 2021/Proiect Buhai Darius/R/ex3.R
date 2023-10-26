# Continuous RV class

Continuous_RV <- setClass(
  "continuous_RV",
  slots = list(
    pdf = "function",
    normalized = "function",
    cdf = "function",
    norm_constant = "numeric",
    mean = "numeric"
  )
)

init <- function(.Object, pdf)
  # initialization
  setMethod("init", "Continuous_RV", function(.Object, pdf){
    tryCatch({
      rand_var <- .Object
      rand_var@pdf = pdf
      rand_var@norm_constant = compute_normalizing_constant(pdf)
      rand_var@normalized <- rand_var@pdf * rand_var@norm_constant
      rand_var@cdf <- rand_var@pdf
      rand_var@deviation <- rand_var@pdf
      rand_var@mean <- E(rand_var@pdf)
    })
  })


show <- function(.Object)
  setMethod("show", "Continuous_RV", function(.Object){
    print(rand_var@norm_constant)
    print(rand_var@pdf)
    print(rand_var@mean)
    print(rand_var@normalized)
  })

# compute the mean
E <- function (probability_density_function, normalization_constant = 1){
  # int (x * pdf(x)dx)
  forIntegration <- function(x){
    return (x * pdf(x) / normalization_constant)
  }
  # try to compute the integral
  tryCatch(
    expr = {
      integral <- integrate(forIntegration, lower = -Inf, upper = Inf)$value
      return(integral)
    },
    error = function(e){
      message('Caught an error when calculating the mean!')
      print(e)
      return(0)
    },
    warning = function(w){
      message('Caught a warning!')
      print(w)
    },
    finally = {
      message('')
    })
}
