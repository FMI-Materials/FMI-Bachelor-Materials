gambler_ruin <- function(suma, castig) {
  stake <- suma
  while (stake > 0 & stake < castig) {
    bet <- sample(c(-1, 1), 1, prob = c(0.5, 0.5))
    stake <- stake + bet
  }
  if (stake == 0)
    return(1)
  else 
    return(0)
}   

suma <- 23
castig <- 1000
N <- 100
contor <- 0
sum <- 0
while (contor < N){
  m <- gambler_ruin(suma,castig)
  sum <- sum + m
  contor <- contor + 1
  }

Probabilitate <- sum/N
