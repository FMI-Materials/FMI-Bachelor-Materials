#Legea numerelor mari
#Zarul reprezinta X~Uniform(1,2,...100)
#media teoretica: E(X)=1/100*(1+2+3+...+100)=1/100*100*101/2=50.5
zar <- 1:100

########## Functia sample
set.seed(5)
x <- sample(1:5,3) #implicit foloseste repartitia uniforma si extragerile sunt fara revenire
sample(1:5,10, replace=T) #Trebuie sa fac extrageri cu revenire daca vreau sa extrag 10 valori din 5 disponibile 
x <- sample(1:5, 10000, replace=T, prob=c(1/10,2/10,3/10,2/10,2/10))
table(x)/10^4

##############################################################################
#Functia care va realiza esantionarea
#n este numarul de aruncari

arunca <- function(n) {
  mean(sample(zar, size = n, replace = TRUE))
}

#Pentru familia de functii apply vezi lab3 prof. Amarioarei
# sapply(1:10000, arunca) este echivalent cu apelul functiei arunca, pe rand, cu toate valorile
# de la 1 la 10 000
plot(sapply(10000:100000, arunca), type = "o", xlab = "numarul de aruncari", ylab = "media")
#Functia abline deseneaza drepte orizontale(h=ceva) sau verticale(v=ceva) peste un grafic
abline(h = 50.5, col = "red")



#Ilustrati LNM pt. repartiile binomiala, poisson si exponentiala
(folositi rbinom, rpois si rexp)


#Teorema limita centrala
alt_zar <- sample(1:100,10000, replace= TRUE)
hist(alt_zar, col ="light blue")
abline(v=50.5, col = "red")

x10 <- c()
k <- 10000
for ( i in 1:k) {
  x10[i] = mean(sample(1:100,10, replace = TRUE))}
hist(x10, col ="pink", main="Esantion de volum 10",xlab ="Rezultatul aruncarii",freq=F)
abline(v = mean(x10), col = "Red")
abline(v = 50.5, col = "blue")
t <- seq(20,80,0.001)
lines(t,dnorm(t,mean(x10),sd(x10)))
x30 <- c()
x100 <- c()
x1000 <- c()

for ( i in 1:k){
  x30[i] = mean(sample(1:100,30, replace = TRUE))
  x100[i] = mean(sample(1:100,100, replace = TRUE))
  x1000[i] = mean(sample(1:100,1000, replace = TRUE))
}

#functia par imi permite sa gestionez parametri grafici
#mfrow cere un vector cu 2 valori dintre care prima reprezinta numarul de linii si a doua numarul
#de coloane in care va fi impartit spatiul de plotare
par(mfrow=c(1,3))
hist(x30, col ="green",main="n=30",xlab ="Rezultatul aruncarii",freq=F)
abline(v = mean(x30), col = "blue")
t1 <- seq(30,70,0.001)
lines(t1,dnorm(t1,mean(x30),sd(x30)),col="magenta")

hist(x100, col ="light blue", main="n=100",xlab ="Rezultatul aruncarii")
abline(v = mean(x100), col = "red")

hist(x1000, col ="orange",main="n=1000",xlab ="Rezultatul aruncarii",freq=F)
abline(v = mean(x1000), col = "red")
t <- seq(47,54,0.001)
lines(t,dnorm(t,mean(x1000),sd(x1000)),col="magenta")

par(mfrow=c(1,1))


#Tema: Ilustrati TLC pentru repartitiile: Poisson, Geometrica si Exponentiala pentru toate cele 4 dimensiuni de esantion


x10bis <- c()
k <- 10000
for ( i in 1:k) {
  x10bis[i] = mean(rpois(2,5))}
hist(x10bis, col ="pink", main="Esantion de volum 10",xlab ="Rezultatul aruncarii",freq=F,breaks=50)
abline(v = mean(x10bis), col = "Red")
abline(v = 5, col = "blue") #Media teoretica pentru X~Pois(5) este 5



t <- seq(0,12,0.001)
lines(t,dnorm(t,mean(x10bis),sd(x10bis)))
x30 <- c()
x100 <- c()
x1000 <- c()

for ( i in 1:k){
  x30[i] = mean(sample(1:100,30, replace = TRUE))
  x100[i] = mean(sample(1:100,100, replace = TRUE))
  x1000[i] = mean(sample(1:100,1000, replace = TRUE))
}

#functia par imi permite sa gestionez parametri grafici
#mfrow cere un vector cu 2 valori dintre care prima reprezinta numarul de linii si a doua numarul
#de coloane in care va fi impartit spatiul de plotare
par(mfrow=c(1,3))
hist(x30, col ="green",main="n=30",xlab ="Rezultatul aruncarii",freq=F)
abline(v = mean(x30), col = "blue")
t1 <- seq(30,70,0.001)
lines(t1,dnorm(t1,mean(x30),sd(x30)),col="magenta")

hist(x100, col ="light blue", main="n=100",xlab ="Rezultatul aruncarii")
abline(v = mean(x100), col = "red")

hist(x1000, col ="orange",main="n=1000",xlab ="Rezultatul aruncarii",freq=F)
abline(v = mean(x1000), col = "red")
t <- seq(47,54,0.001)
lines(t,dnorm(t,mean(x1000),sd(x1000)),col="magenta")



