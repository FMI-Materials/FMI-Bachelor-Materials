functie <- function() {
  n <- 1000
  first <- 0
  second <- 0
  cont <- 0
  sum <- 0
  while( sum != 5 && sum!=7 && cont < n - 1 ){
    first <- sample(1:6, size = 1, replace = TRUE)
    second <-  sample(1:6, size = 1, replace = TRUE)
    sum <- first + second
    cont <- cont + 1
  }
  if(cont == n - 1){
    first <- sample(1:6, size = 1, replace = TRUE)
    second <-  sample(1:6, size = 1, replace = TRUE)
    sum <- first + second
    if(sum == 5){
      return (1)
      }
      else{
        return (0)
        }
  }
  else
    {return (0)}
    
}  


N <- 10000
contor <- 0
nr <- 0
while (contor < N){
  m <- functie()
  if(m){
    nr <- nr + 1}
  contor <- contor + 1
}

prob <- nr/N

