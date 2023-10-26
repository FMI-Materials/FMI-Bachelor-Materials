INSERT INTO Categorii VALUES (1, NULL, 'Tricouri');
INSERT INTO Categorii VALUES (2, 1, 'Polo');
INSERT INTO Categorii VALUES (3, 1, 'Clasic');
INSERT INTO Categorii VALUES (4, NULL, 'Pantaloni');
INSERT INTO Categorii VALUES (5, 4, 'Costum');
INSERT INTO Categorii VALUES (6, 4, 'Blugi');

INSERT INTO Produse VALUES (1, 2, 'Tricou Guess Alb', 211, 'Tricou de calitate superioara GUESS', 50);
INSERT INTO Produse VALUES (2, 2, 'Tricou Guess Maro', 211, 'Tricou de calitate superioara GUESS', 30);
INSERT INTO Produse VALUES (3, 3, 'Tricou Zara', 211, 'Tricou din materiale reciclabile',22);
INSERT INTO Produse VALUES (4, 6, 'Pantaloni Zara', 211, 'Pantaloni din materiale reciclabile', 15);
INSERT INTO Produse VALUES (5, 6, 'Pantaloni Reserved', 211, 'Pantaloni din materiale reciclabile', 189);

INSERT INTO Promotii VALUES ('Promo11', 11, 'Discount de 11%');
INSERT INTO Promotii VALUES ('Promo20', 20, 'Discount de 20%');
INSERT INTO Promotii VALUES ('BlackFriday', 50, 'Discount de 50% de Black Friday');

INSERT INTO Utilizator VALUES (1, 'Darius', 'Buhai', 'dariusb@yahoo.com', '$23AJakOamOamII', TO_DATE('2001-05-03', 'yyyy-mm-dd'), TO_DATE('2020-08-03', 'yyyy-mm-dd'), 'admin');
INSERT INTO Utilizator VALUES (2, 'George', 'Mihai', 'gmihai@s.unibuc.ro', '$23KiamOioOmaja', TO_DATE('2001-07-08', 'yyyy-mm-dd'), TO_DATE('2020-08-05', 'yyyy-mm-dd'), 'user');
INSERT INTO Utilizator VALUES (3, 'Matei', 'Barbu', 'mbarb@gmail.com', '$23AIIjaOamll', TO_DATE('2000-08-10', 'yyyy-mm-dd'), TO_DATE('2020-08-07', 'yyyy-mm-dd'), 'user');

INSERT INTO Sesiuni VALUES (1, 1, TO_DATE('2020-08-03', 'yyyy-mm-dd'), TO_DATE('2020-08-30', 'yyyy-mm-dd'));
INSERT INTO Sesiuni VALUES (2, 3, TO_DATE('2020-12-03', 'yyyy-mm-dd'), TO_DATE('2020-12-31', 'yyyy-mm-dd'));
INSERT INTO Sesiuni VALUES (3, 2, TO_DATE('2021-01-01', 'yyyy-mm-dd'), TO_DATE('2021-01-31', 'yyyy-mm-dd'));

INSERT INTO Adresa VALUES (1, 1, 'Brasov', 'Brasov', 'Nicopolei 22');
INSERT INTO Adresa VALUES (2, 2, 'Ilfov', 'Bucuresti', 'Iancului 11');
INSERT INTO Adresa VALUES (3, 3, 'Iasi', 'Iasi', 'Matei Babes 55');

INSERT INTO Comenzi VALUES (1, 1, 1, 'Promo11', TO_DATE('2020-11-27', 'yyyy-mm-dd'),NULL);
INSERT INTO Comenzi VALUES (2, 2, 2, NULL, TO_DATE('2020-12-21', 'yyyy-mm-dd'),'Sa fie impachetat de Craciun');
INSERT INTO Comenzi VALUES (3, 3, 3, 'Promo11', TO_DATE('2020-11-30', 'yyyy-mm-dd'),NULL);

INSERT INTO comanda_contine_produse VALUES (1, 1, 1);
INSERT INTO comanda_contine_produse VALUES (2, 3, 3);
INSERT INTO comanda_contine_produse VALUES (5, 2, 1);
INSERT INTO comanda_contine_produse VALUES (3, 2, 4);
