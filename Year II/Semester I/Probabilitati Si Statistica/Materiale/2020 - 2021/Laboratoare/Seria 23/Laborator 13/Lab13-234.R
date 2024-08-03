#Statistica descriptiva
data() #pentru listarea tuturor dataset-urilor care sunt disponibile
#Simulare de valori dintr-o variabila aleatoare

#Functia sample
set.seed(15129)
sample(1:100,4)
sample(1:100,400,replace=T)
x <- sample(-1:1,10^6,replace=T,prob=c(1/2,1/3,1/6))
x[1:20]
valminus1 <- length(x[x==-1])/10^6
val0 <- length(x[x==0])/10^6
val1 <- length(x[x==1])/10^6
#sau folosim functia table
u <- table(x)
str(u)
indice_mod <- max(u)
u[u==max(u)]
#To Do: cum extrag doar atributul numeric pentru calcularea valorii modale

x1 <- sample(-1:1,10,replace=T,prob=c(1/2,1/3,1/6))
valminus11 <- length(x1[x1==-1])/10
val01 <- length(x1[x1==0])/10
val11 <- length(x1[x1==1])/10

sample(1:5,5)



#Import date in R
y <- Departament_facultate$y
media <- mean(y)
dispersia <- var(y)
deviatia_standard <- sd(y)
minim <-min(y)
maxim <- max(y)
#range(y)

hist(y,col="pink") #Foloseste implicit formula lui Sturges
#De continuat