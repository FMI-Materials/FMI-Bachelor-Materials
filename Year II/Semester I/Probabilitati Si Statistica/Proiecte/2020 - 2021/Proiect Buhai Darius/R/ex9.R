
#function to integrate the probability density function
integrate_pdf <- function (f, X) {
  tryCatch (
    expr = {
      integrate (f, 0, X)$value
    },
    error = function (e) {
      print(e)
    }
  )
}

# compute the inverse function
inverse_function <- function (f, u, lowerBound = -10000, upperBound = 10000) {
  tryCatch (
    expr = {
      uniroot((function (x) f(x) - u), lower = lowerBound, upper = upperBound, extendInt = 'yes')
    },
    error = function (e) {
      print(e)
    }
  )
}



random_variable_generator <- function(f, n, lowerBound, upperBound) {
  # generates random deviates
  values <- runif(n, min = 0, max = 1)
  # combines its arguments into a list
  r <- c()
  for (v in values) {
    r <- append (r, inverse_function(function (x) (integrate_pdf(f, x)), v, lowerBound, upperBound)[1]$root)
  }
  r
}

