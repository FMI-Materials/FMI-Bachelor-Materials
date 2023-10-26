# Check if a function is positive in a given interval
is_positive <- function(f, d = c(-10000000, 10000000), step=10000000){
  # Set maximum lower and upper bounds
  if(d[2] == Inf)
    d[2] = 10000000;
  if(d[1] == -Inf)
    d[1] = -10000000;
  # Calculate values in that intervals
  vals <- seq(d[1], d[2], len=step)
  # Check if all values are positive
  all(f(vals)>=0)
}

check_pdf <- function(f, d = c(-Inf, Inf)){
  # Check if the function is positive
  if(!is_positive(f, d)){
    print("Function is negative")
    return(FALSE)
  }
  # Safe integrate, handle errors
  i = safe_integrate(f, d)
  # Cannot integrate
  if(typeof(i)=='logical' && i==FALSE)
    return(FALSE)
  v = i $ value
  round(v) == 1
}

# Example:
# f <- function(x){
#   if (x > 0 && x < 2){
#      3/8 * (4*x-2*x^2)
#   }else{
#      0
#   }
# }
#
# check_pdf(f)
