
# Calculates medium
medium <- function(f, d = c(-Inf, Inf)){
  integrate(function(x){ x * f(x)}, d[1], d[2]) $ value
}
