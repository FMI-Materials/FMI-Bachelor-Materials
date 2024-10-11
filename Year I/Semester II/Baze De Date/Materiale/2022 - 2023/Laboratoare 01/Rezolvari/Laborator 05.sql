CREATE TABLE ANGAJATI_ANE
    nume varchar2(20) constraint nume_ang_ane not null,
    prenume varchar2(20),
    email char(15)unique,
    data_ang date default sysdate,
    job varchar2(10),
    cod_sef number(4),
    salariu number(8, 2) constraint salariu_ang_ane not null,
    cod_dep number(2),
    constraint pkey_ang_ane primary key(cod_ang)
 );

INSERT INTO ANGAJATI_ANE(cod_ang, nume, prenume, data_ang, job, salariu, cod_dep)
VALUES(100, 'nume1', 'prenume1', null, 'Director', 20000, 10);

INSERT INTO ANGAJATI_ANE
VALUES(101, 'nume2', 'prenume2', 'nume2', to_date('02-02-2004','dd-mm-yyyy'), 
       'Inginer', 100, 10000, 10);

INSERT INTO ANGAJATI_ANE
VALUES(102, 'nume3', 'prenume3', 'nume3', to_date('05-06-2000','dd-mm-yyyy'), 
       'Analist', 101, 5000, 20);

INSERT INTO ANGAJATI_ANE(cod_ang, nume, prenume, data_ang, job, cod_sef, salariu, cod_dep)
VALUES(103, 'nume4', 'prenume4', null, 'Inginer', 100, 9000, 20);

INSERT INTO ANGAJATI_ANE
VALUES(104, 'nume5', 'prenume5', 'nume5', null, 'Analist', 101, 3000, 30);

COMMIT;

DESC ANGAJATI_ANE;

ALTER TABLE ANGAJATI_ANE
ADD comision number(4, 2);

ALTER TABLE ANGAJATI_ANE
MODIFY (salariu number(6, 2));

ALTER TABLE ANGAJATI_ANE
MODIFY (salariu number(8,2) default 100); 

ALTER TABLE ANGAJATI_ANE
MODIFY 
( 
    comision number(2,2),
    salariu number(10,2)
);

UPDATE ANGAJATI_ANE
SET comision = 0.1
WHERE UPPER(job) LIKE 'A%';

ALTER TABLE angajati_pnu
MODIFY (email varchar2(15));

CREATE TABLE DEPARTAMENTE_ANE
(   
    cod_dep number(2),
    nume varchar2(15) constraint nume_dep_ane not null,
    cod_director number(4)
);

SELECT *
FROM DEPARTAMENTE_ANE;

ALTER TABLE DEPARTAMENTE_ANE
ADD CONSTRAINT pkey_dep_ane PRIMARY KEY(cod_dep);

INSERT INTO DEPARTAMENTE_ANE
VALUES (10, 'Administrativ', 100);

INSERT INTO DEPARTAMENTE_ANE
VALUES (20, 'Proiectare', 101);

INSERT INTO DEPARTAMENTE_ANE
VALUES (30, 'Programare', null);

DROP TABLE ANGAJATI_ANE;

CREATE TABLE ANGAJATI_ANE
(
     cod_ang number(4) constraint pkey_ang primary key,
     nume varchar2(20) constraint nume_ang not null,
     prenume varchar2(20),
     email char(15) unique,
     data_ang date default sysdate,
     job varchar2(10),
     cod_sef number(4) constraint sef_ang references ANGAJATI_ANE(cod_ang), -- cheie externa
     salariu number(8, 2) constraint salariu_ang not null,
     cod_dep number(2) constraint fk_cod_dep_ane references DEPARTAMENTE_ANE(cod_dep)
                       constraint cod_dep_poz_ane check(cod_dep > 0),
     comision number(2,2),
     constraint nume_pren_unice_ane unique(nume, prenume),
     constraint verif_sal_ane check(salariu > 100 * comision)
);

CREATE TABLE ANGAJATI_ANE
(
    cod_ang number(4),
    nume varchar2(20) constraint nume_ane not null,
    prenume varchar2(20),
    email char(15),
    data_ang date default sysdate,
    job varchar2(10),
    cod_sef number(4),
    salariu number(8, 2) constraint salariu_ane not null,
    cod_dep number(2),
    comision number(2,2),
    constraint nume_prenume_unique_ane unique(nume,prenume),
    constraint verifica_sal_ane check(salariu > 100*comision),
    constraint pk_angajati_ane primary key(cod_ang),
    constraint email_unic_ane unique(email),
    constraint sef_ane foreign key(cod_sef) references ANGAJATI_ANE(cod_ang),
    constraint fk_dep_ane foreign key(cod_dep) references DEPARTAMENTE_ANE(cod_dep),
    constraint cod_dep_poz_ane check(cod_dep > 0)
);