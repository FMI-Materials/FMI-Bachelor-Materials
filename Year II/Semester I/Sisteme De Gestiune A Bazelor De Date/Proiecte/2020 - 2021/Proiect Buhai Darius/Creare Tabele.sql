DROP TABLE comanda_contine_produse;
DROP TABLE Produse;
DROP TABLE Categorii;
DROP TABLE Comenzi;
DROP TABLE Promotii;
DROP TABLE Adresa;
DROP TABLE Sesiuni;
DROP TABLE Utilizator;

CREATE TABLE Categorii (
    id_categorie INT NOT NULL,
    id_parinte INT,
    denumire VARCHAR2(20),
    CONSTRAINT categorie_pk PRIMARY KEY (id_categorie),
    CONSTRAINT categorie_fk FOREIGN KEY (id_parinte) REFERENCES Categorii(id_categorie)
);
CREATE TABLE Produse (
    id_produs INT NOT NULL,
    id_categorie INT NOT NULL,
    denumire VARCHAR2(20),
    pret INTEGER,
    descriere VARCHAR2(300),
    stoc INT,
    CONSTRAINT produs_pk PRIMARY KEY (id_produs),
    CONSTRAINT produs_fk FOREIGN KEY (id_categorie) REFERENCES Categorii(id_categorie)
);
CREATE TABLE Promotii (
    cod_promotional VARCHAR2(20) NOT NULL,
    discount INT,
    descriere VARCHAR2(300),
    CONSTRAINT promotie_pk PRIMARY KEY (cod_promotional)
);
CREATE TABLE Utilizator (
    id_utilizator INT NOT NULL,
    nume VARCHAR2(20) NOT NULL,
    prenume VARCHAR2(20) NOT NULL,
    email VARCHAR2(30),
    parola VARCHAR2(100),
    data_nastere DATE,
    data_cont DATE,
    rol VARCHAR(30),
    CONSTRAINT utilizator_pk PRIMARY KEY (id_utilizator)
);
CREATE TABLE Sesiuni (
	id_sesiune INT NOT NULL,
    id_utilizator INT NOT NULL,
    data_start DATE NOT NULL,
    data_expirare DATE NOT NULL,
    CONSTRAINT sesiune_pk PRIMARY KEY (id_sesiune),
    CONSTRAINT sesiune_fk FOREIGN KEY (id_utilizator) REFERENCES Utilizator(id_utilizator)
);

CREATE TABLE Adresa (
    id_adresa INT NOT NULL,
    id_utilizator INT NOT NULL,
    judet VARCHAR2(50),
    oras VARCHAR2(50),
    adresa VARCHAR2(50),
    CONSTRAINT adresa_pk PRIMARY KEY (id_adresa),
    CONSTRAINT adresa_fk FOREIGN KEY (id_utilizator) REFERENCES Utilizator(id_utilizator)
);
CREATE TABLE Comenzi (
    id_comanda INT NOT NULL,
    id_utilizator INT NOT NULL,
    id_adresa INT NOT NULL,
    cod_promotional VARCHAR2(20),
    data DATE,
    detalii VARCHAR2(300),
    CONSTRAINT comanda_pk PRIMARY KEY (id_comanda),
    CONSTRAINT comanda_fk1 FOREIGN KEY (id_utilizator) REFERENCES Utilizator(id_utilizator),
    CONSTRAINT comanda_fk2 FOREIGN KEY (id_adresa) REFERENCES Adresa(id_adresa),
    CONSTRAINT comanda_fk3 FOREIGN KEY (cod_promotional) REFERENCES Promotii(cod_promotional)
);
CREATE TABLE comanda_contine_produse (
    id_produs INT NOT NULL,
    id_comanda INT NOT NULL,
    cantitate INT,
    CONSTRAINT cos_pk1 PRIMARY KEY (id_produs, id_comanda),
    CONSTRAINT cos_fk1 FOREIGN KEY (id_produs) REFERENCES Produse(id_produs),
    CONSTRAINT cos_fk2 FOREIGN KEY (id_comanda) REFERENCES Comenzi(id_comanda)
);