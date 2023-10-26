# Integrate a function and return False if any errors are generated
safe_integrate <- function(f, d = c(-Inf, Inf)){
  tryCatch(integrate(Vectorize(f), d[1], d[2]),
           error = function(e){
             print(e)
             FALSE
           })
}

# Double integrates x and y
double_integrate <- function(f, dx, dy){
  integrate(
    Vectorize(function(y){
      integrate(function(x){f(x, y)}, dx[1], dx[2]) $ value
    })
    , dy[1], dy[2]) $ value
}
