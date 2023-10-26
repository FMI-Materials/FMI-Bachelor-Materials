first_wins <- function() {
  first <- 0
  second <- 0
  while( first != 1 && second != 6){
    first <- sample(1:6, size = 1, replace = TRUE)
    second <-  sample(1:6, size = 1, replace = TRUE)
  }
  if (first == 1)
    return(1)
  else 
    return(0)
}  


N <- 1000
contor <- 0
nr_first <- 0
nr_second <- 0
while (contor < N){
  m <- first_wins()
  if(m)
    nr_first = nr_first + 1
  else 
    nr_second = nr_second + 1
  contor <- contor + 1
}

p_first <- nr_first/N
p_second <- nr_second/N

