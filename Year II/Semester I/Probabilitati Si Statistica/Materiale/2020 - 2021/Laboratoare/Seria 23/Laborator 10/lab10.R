#Lucru cu discreteRV pentru v.a. bidimensionale
library(discreteRV)
X <- RV(1:100)
P(X==13)
#vezi problema din fisierul Lab10-234.png
(XsiY <- jointRV(outcomes = list(c(0,4), c(-2,0,2)), probs = c(2/8,1/16,1/16,1/8,1/16,7/16)))
X <- marginal(XsiY,1)
Y <- marginal(XsiY,2)
P(X<Y)
#1/16

P(X==4|Y==0)
#1/2
#Verificam independenta dintre X si Y
independent(X,Y)
#repartitiile conditionate
X|(Y==0)
E(X|(Y==0))
V(X|(Y==0))

#TEMA: De reluat exercitiile care dadeau rezultate neplauzibile din tema in R anterioara
#si de refacut construind in prealabil repartitia comuna a v.a.
