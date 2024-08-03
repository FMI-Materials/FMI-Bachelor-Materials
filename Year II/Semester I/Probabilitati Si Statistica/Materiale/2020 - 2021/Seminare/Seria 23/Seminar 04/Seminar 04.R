# Lucru cu pachetul `prob`

# Documentatia unei functii: Din consola scriem > ?rolldie

# Aruncarea cu moneda

tosscoin(4);

# Probabilitatea ca din 3 aruncari sa apara capul cel putin o data:
omega <- tosscoin(3);
str(omega);

# Auxiliar: Arunc o data moneda, vreau cap:
omega <- tosscoin(1);
favorabile <- sum(omega == "H");
totale <- nrow(omega);
probabilitate <- favorabile / totale;
probabilitate;

# Acum problema initiala:
omega <- tosscoin(3);
favorabile <- sum(rowSums(omega == 'H') > 0);
totale <- nrow(omega);
probabilitate <- favorabile / totale;
probabilitate;


# Arunc de 10 ori, vreau nr de cap sa fie intre 4 si 7:
omega <- tosscoin(10);
favorabile <- sum((4 <= rowSums(omega == 'H')) & (rowSums(omega == 'H') <= 7));
totale <- nrow(omega);
probabilitate <- favorabile / totale;
probabilitate;


# Aruncari cu zarul

omega <- rolldie(4);

# Probabilitatea ca din 7 aruncari cel putin 3 sa fie pare:
omega <- rolldie(7);
favorabile <- sum(3 <= rowSums(omega %% 2 == 0));
totale <- nrow(omega);
probabilitate <- favorabile / totale;
probabilitate;

# Alegerea unei carti

card <- cards();
favorabile <- sum(card['suit'] == "Diamond");
totale <- nrow(card);
probabilitate <- favorabile / totale;
probabilitate;

card1 <- cbind(card[1:13,], card[14:26,], card[27:39,], card[40:52,])
card1

# Evenimentele in R (doar in pachetul prob)
# union(A, B) -> reuniunea
# intersect(A, B) -> intersectia
# setdiff(A, B) -> diferenta


# Calculati probabilitatea ca extragand o carte dintr-un pachet cu 52 de carti
# de joc sa obtinem o valoare >7 si culoare "Spade"?

card <- cards()
A <- card[card['rank'] == '7' |
     card['rank'] == '8' |
     card['rank'] == '9' |
     card['rank'] == '10' |
     card['rank'] == 'J' |
     card['rank'] == 'Q' |
     card['rank'] == 'K' |
     card['rank'] == 'A',]
B <- card[card['suit'] == 'Spade',]
favorabile <- nrow(intersect(A, B))
totale <- nrow(card)
probabilitate <- favorabile / totale
probabilitate

# Prb 13:
# prob ca suma a doua numere luate la intamplare din multimea [0, 1]
# 









