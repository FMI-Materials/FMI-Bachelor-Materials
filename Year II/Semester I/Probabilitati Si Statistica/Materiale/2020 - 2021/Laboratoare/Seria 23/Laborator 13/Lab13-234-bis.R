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
mediana <- median(y)
#prima cuartila lasa 25% din datele ordonate crescator la stanga si restul de 75% la dreapta
q1 <- quantile(y,1/4)
#OBS: q2 este mediana  
#a treia cuartila lasa 75% din datele ordonate crescator la stanga si restul de 25% la dreapta
q3 <- quantile(y,3/4)  
dispersia <- var(y)
deviatia_standard <- sd(y)
minim <-min(y)
maxim <- max(y)
#range(y)

hist(y,col="pink") #Foloseste implicit formula lui Sturges
#De continuat
t <- seq(14,32,0.001)
plot(t,dnorm(t,20,0.25))


#Pentru a putea suprapune o densitate peste histograma trebuie ca pe axa Oy sa avem valori compatibile cu o densitate
hist(y,col="pink",freq=F)
lines(t,dnorm(t,media,deviatia_standard),col="blue")
#Normala aproximeaza binisor datele
lines(density(y),col="magenta")
z <- rnorm(10000,5,2)
hist(z,freq=F,col="blue")
#Aici normala aproximeaza foarte bine datele
t1 <- seq(-2,12,0.001)
lines(t1,dnorm(t1,5,2),col="red")

#Diagrama boxplot

#"cutia" este delimitata de q1 si q3 si reprezinta valorile "comune"
#capetele mustatilor se determina cu urmatoarea formula
#capat_sus=min(max(y),q3+1.5*IQR) unde IQR=q3-q1 (interquartilical range)
#capat_jos=max(min(y),q1-1.5*IQR)

boxplot(y)
#functia abline deseneaza drepte verticale v=ceva sau orizontale h=ceva
abline(h=mediana,col="blue")
abline(h=q1,col="blue")
abline(h=q3,col="blue")
abline(h=q1,col="blue")
abline(h=minim,col="blue")
abline(h=maxim,col="blue")

y1 <- c(y,100)

media1 <- mean(y1)
mediana1 <- median(y1)
#prima cuartila lasa 25% din datele ordonate crescator la stanga si restul de 75% la dreapta
q11 <- quantile(y1,1/4)
#OBS: q2 este mediana  
#a treia cuartila lasa 75% din datele ordonate crescator la stanga si restul de 25% la dreapta
q31 <- quantile(y1,3/4)  
dispersia1 <- var(y1)
deviatia_standard1 <- sd(y1)
minim1 <-min(y1)
maxim1 <- max(y1)

boxplot(y1)
abline(h=q31+1.5*(q31-q11),col="blue") #de revazut!
#functia abline deseneaza drepte verticale v=ceva sau orizontale h=ceva
abline(h=mediana1,col="blue")
abline(h=q11,col="blue")
abline(h=q31,col="blue")
abline(h=minim1,col="blue")
abline(h=maxim1,col="blue")

y2 <- c(y1,2)
boxplot(y2)

g <- sample(c(0,1),36, replace=T)

boxplot(y~g)


