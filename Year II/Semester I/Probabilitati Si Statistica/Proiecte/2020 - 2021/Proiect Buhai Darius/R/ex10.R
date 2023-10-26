
# Extracts x out of common density of x and y
extract_x_marginal <- function(f, dx){
  Vectorize(function(y){
    integrate(function(x){f(x, y)}, dx[1], dx[2]) $ value
  })
}

# Extracts y out of common density of x and y
extract_y_marginal <- function(f, dy){
  Vectorize(function(x){
    integrate(function(y){f(x, y)}, dy[1], dy[2]) $ value
  })
}

# Calculates Covariance and Correlation coefficient
covariance_and_correlation <- function(pdf, dx, dy){

  fx = extract_x_marginal(pdf, dx)
  fy = extract_y_marginal(pdf, dy)

  mx = medium(fx, dx)
  my = medium(fy, dy)

  cov = double_integrate(function(x,y){x*y*pdf(x,y)}, dx, dy) - (mx*my)

  cor = cov / (mx*my)

  list(cov = cov, cor = cor)
}

# Example
# f1 <- function (x, y) {
#   return (3/2 * (x^2+y^2))
# }
#
# covariance_and_correlation(f1, c(0,1), c(0, 1))
