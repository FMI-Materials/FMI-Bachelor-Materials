

# Calculating central moment of order o
central_moment <- function(f, o){
  m = medium(f)
  f_new <- function(x){
    ((x - m) ^ o) * f(x)
  }
  res = safe_integrate(f)
  if(typeof(res)=="logical" && res==FALSE){
    print("Momentul nu există!")
    return(0)
  }
  res $ value
}

# Calculating initial moment of order o
initial_moment <- function(f, o){
  f_new <- function(x){
    x ^ o * f(x)
  }
  res = safe_integrate(f)
  if(typeof(res)=="logical" && res==FALSE){
    print("Momentul nu există!")
    return(0)
  }
  res $ value
}

# Example:
# f = function (x) {
#   if(x<0 || x>1)
#     return(0)
#   x ^ 3
# }
#
# initial_moment(f, 2)
# central_moment(f, 2)
