#Lucru cu pachetul prob
#Aruncarea cu moneda
tosscoin(3)
#Probabilitatea ca din 3 aruncari sa apara capul cel putin o dataa
#Auxiliar arunc moneda o data si vreau probabilitatea sa obtin cap
omega1 <- tosscoin(1)
sum(omega1=="H")/nrow(omega1)
# Acum, problema initiala
omega3 <- tosscoin(3)
sum(rowSums(omega3=="H")>0)/nrow(omega3)
# Arunc de 10 ori, vreau nr de cap sa fie intre 4 si 7
omega <- tosscoin(10)
favorabile <- sum(4<=rowSums(omega=="H")&&rowSums(omega=="H")<=7)
totale <- nrow(omega)
probabilitate <- favorabile / totale
probabilitate
# Probabilitatea ca dinn 7 aruncari cel putin 3 sa fie pare
omega_zar7 <- rolldie(7)
favorabile <- sum(rowSums(omega_zar7%%2==0)>=3)
totale<-nrow(omega_zar7)
probabilitate<-favorabile/totale
probabilitate

#Jocuri de carti
o<-cards()
sum(colSums(o=="Diamond"))/nrow(o)
card <- cards()
favorabile <- sum(card['suit']=="Diamond")
totale<-nrow(card)
probabilitate<-favorabile/totale
probabilitate

a <- 1:3
b <- 4:6
cbind(a, b)
rbind(a, b)

o1 <- cbind(o[1:13,],o[14:26,],o[27:39,],o[40:52,])
o[o["rank"]=="7"]

