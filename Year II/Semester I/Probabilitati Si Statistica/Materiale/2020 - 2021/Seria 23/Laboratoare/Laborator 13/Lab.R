# Statistica descriptiva

data() # pentru listarea tuturor dataset-urilor care sunt disponibile
# Simulare de valori dintr-o variabila aleatoare

# Functie sample
sample(1:100,4)
sample(1:100, 400, replace=T)
x <- sample(-1:1,10^6,replace=T,prob=c(1/2,1/3,1/6))
x[1:20]
valminus1 <- length(x[x==-1])/10^6
val0 <- length(x[x==0])/10^6
val1 <- length(x[x==1])/10^6
# sau folosim functie table
table(x)

x1 <- sample(-1:1,10,replace=T,prob=c(1/2,1/3,1/6))
valminus11 <- length(x1[x1==-1])/10
val01 <- length(x1[x1==0])/10
val11 <- length(x1[x1==1])/10

sample(1:5,5)

