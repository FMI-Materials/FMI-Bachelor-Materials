drop table depozite cascade constraints;
drop table sectoare cascade constraints;
drop table zone cascade constraints;
drop table unitati_de_masura cascade constraints;
drop table caracteristici cascade constraints;
drop table categorii cascade constraints;
drop table produse cascade constraints;
drop table produse_au_caracteristici cascade constraints;
drop table clienti cascade constraints;
drop table clienti_persoane_fizice cascade constraints;
drop table clienti_persoane_juridice cascade constraints;
drop table tip_livrare cascade constraints;
drop table adrese cascade constraints;
drop table tip_plata cascade constraints;
drop table clienti_au_pret_preferential cascade constraints;
drop table case cascade constraints;
drop table facturi cascade constraints;
drop table facturi_contin_produse cascade constraints;
drop table clasific_clienti;

select 
sys_context('userenv','nls_territory') nls_territory,
sys_context('userenv','nls_date_format') nls_date_format,
sys_context('userenv','nls_date_language') nls_date_language,
sys_context('userenv','nls_sort') nls_sort, 
sys_context('userenv','language') language
from dual;

select sysdate from dual;

alter session set nls_language='american';
alter session set nls_territory='america';
alter session set nls_date_language='american';

create table depozite 
   (id_depozit number(20,0), 
	denumire varchar2(20 byte), 
	adresa varchar2(20 byte), 
	oras varchar2(20 byte), 
	judet varchar2(20 byte), 
	orar varchar2(20 byte), 
	capacitate float(126), 
	valoare float(126), 
	id_director number(20,0), 
	id_tara number(20,0)
   );

create unique index depozite_pk on depozite (id_depozit);

alter table depozite add constraint depozite_pk primary key (id_depozit) enable;

alter table depozite modify (id_depozit not null enable);

insert into depozite (id_depozit,denumire,adresa,oras,judet,orar,capacitate,valoare,id_director,id_tara) 
values (1,'mosilor','calea mosilor 274','seini','maramures','07-21',2156.4,5200.5,73,22);
insert into depozite (id_depozit,denumire,adresa,oras,judet,orar,capacitate,valoare,id_director,id_tara) 
values (2,'banloc','str. bratianu nr.1','sector 3','bucuresti','08-23',256.84,17817.1,57,48);
insert into depozite (id_depozit,denumire,adresa,oras,judet,orar,capacitate,valoare,id_director,id_tara) 
values (3,'unirii','str. unirii 19','tecuci','galati','09-15',65484,2561.4,47,8);
insert into depozite (id_depozit,denumire,adresa,oras,judet,orar,capacitate,valoare,id_director,id_tara) 
values (4,'calea sagului','p-ta revolutiei nr.3','timisoara','timis','04-21',65.84,489489.849,2564,8);
insert into depozite (id_depozit,denumire,adresa,oras,judet,orar,capacitate,valoare,id_director,id_tara) 
values (5,'eroilor','b-dul eroilor nr. 5','cluj-napoca','cluj','09-15',6264.16,21894.48,8,784);
insert into depozite (id_depozit,denumire,adresa,oras,judet,orar,capacitate,valoare,id_director,id_tara) 
values (6,'tomis','b-dul tomis nr.51','iasi','iasi','15-22',28423.87,89416.549,4894,74);
insert into depozite (id_depozit,denumire,adresa,oras,judet,orar,capacitate,valoare,id_director,id_tara) 
values (7,'gherman','str. unirii nr.19','craiova','dolj','07-23',26584.41,894.849,894,18);
insert into depozite (id_depozit,denumire,adresa,oras,judet,orar,capacitate,valoare,id_director,id_tara) 
values (8,'victoriei','p-ta victoriei nr.2','ovidiu','constanta','17-23',2644.12,48948,4,4818);
insert into depozite (id_depozit,denumire,adresa,oras,judet,orar,capacitate,valoare,id_director,id_tara) 
values (9,'primariei','str. primariei nr.2','sibiu','sibiu','10-20',254412.45,5489.54,156,9);
insert into depozite (id_depozit,denumire,adresa,oras,judet,orar,capacitate,valoare,id_director,id_tara) 
values (10,'berlin','lützowplatz 17 ','berlin','germania','05-20',2852.48,8424,489,28);

create table sectoare 
   (id_sector number(20,0), 
	descriere varchar2(20 byte), 
	id_depozit number(20,0)
   );

create unique index sectoare_pk on sectoare (id_sector);

alter table sectoare add constraint sectoare_pk primary key (id_sector) enable;

alter table sectoare modify (id_sector not null enable);

alter table sectoare add constraint sectoare_depozite_fk foreign key (id_depozit)
  references depozite (id_depozit) enable;

insert into sectoare (id_sector,descriere,id_depozit) values (1,'maramures',1);
insert into sectoare (id_sector,descriere,id_depozit) values (2,'bucuresti',2);
insert into sectoare (id_sector,descriere,id_depozit) values (3,'galati',3);
insert into sectoare (id_sector,descriere,id_depozit) values (4,'timis',4);
insert into sectoare (id_sector,descriere,id_depozit) values (5,'cluj',5);
insert into sectoare (id_sector,descriere,id_depozit) values (6,'iasi',6);
insert into sectoare (id_sector,descriere,id_depozit) values (7,'dolj',7);
insert into sectoare (id_sector,descriere,id_depozit) values (8,'constanta',8);
insert into sectoare (id_sector,descriere,id_depozit) values (9,'sibiu',9);
insert into sectoare (id_sector,descriere,id_depozit) values (10,'germania',10);

create table zone 
   (	id_zona number(20,0), 
	descriere varchar2(20 byte), 
	capacitate_maxima float(126), 
	capacitate_folosita float(126), 
	id_sector number(20,0)
   );

create unique index zone_pk on zone (id_zona);

alter table zone modify (id_zona not null enable);

alter table zone add constraint zone_pk primary key (id_zona) enable;

alter table zone add constraint zone_sectoare_fk foreign key (id_sector)
  references sectoare (id_sector) enable;

insert into zone (id_zona,descriere,capacitate_maxima,capacitate_folosita,id_sector) 
	values (1,'nord',500,20,1);
insert into zone (id_zona,descriere,capacitate_maxima,capacitate_folosita,id_sector) 
	values (2,'sud',1000,30,2);
insert into zone (id_zona,descriere,capacitate_maxima,capacitate_folosita,id_sector) 
	values (3,'est',2000,40,3);
insert into zone (id_zona,descriere,capacitate_maxima,capacitate_folosita,id_sector) 
	values (4,'vest',4000,50,4);
insert into zone (id_zona,descriere,capacitate_maxima,capacitate_folosita,id_sector) 
	values (5,'nord-vest',8000,60,5);
insert into zone (id_zona,descriere,capacitate_maxima,capacitate_folosita,id_sector) 
	values (6,'nord-est',16000,100,6);
insert into zone (id_zona,descriere,capacitate_maxima,capacitate_folosita,id_sector) 
	values (7,'sud-vest',32000,200,7);
insert into zone (id_zona,descriere,capacitate_maxima,capacitate_folosita,id_sector) 
	values (8,'sud-est',64000,400,8);
insert into zone (id_zona,descriere,capacitate_maxima,capacitate_folosita,id_sector) 
	values (9,'centru',120000,800,9);
insert into zone (id_zona,descriere,capacitate_maxima,capacitate_folosita,id_sector) 
	values (10,'altele',240000,1000,10);

create table unitati_de_masura 
  ( id_um number(20,0) primary key,
    denumire varchar2(20) not null,
    descriere varchar2(20)
  );

insert into unitati_de_masura
	values (1,'buc','bucata');
insert into unitati_de_masura
	values (2,'kg','kilogram(1kg=1000g)');
insert into unitati_de_masura
	values (3,'l','litru');
insert into unitati_de_masura
	values (4,'m','metru');
insert into unitati_de_masura
	values (5,'pachet',null);
insert into unitati_de_masura
	values (6,'g','gram');

create table caracteristici 
   (id_caracteristica number(38,0), 
	descriere varchar2(255 byte), 
	denumire varchar2(35 byte)
   );

create unique index caracteristici_pk on caracteristici (id_caracteristica);

alter table caracteristici add constraint caracteristici_pk primary key (id_caracteristica) enable;

alter table caracteristici modify (id_caracteristica not null enable);

insert into caracteristici (id_caracteristica,descriere,denumire) 
values (1,null,'culoare');
insert into caracteristici (id_caracteristica,descriere,denumire) 
values (2,'se strica sau nu','valabilitate');
insert into caracteristici (id_caracteristica,descriere,denumire) 
values (3,'ani','garantie');
insert into caracteristici (id_caracteristica,descriere,denumire) 
values (44,'antisoc etc','impachetare');
insert into caracteristici (id_caracteristica,descriere,denumire) 
values (5,'date clientului daca le cumpara','puncte bonus');
insert into caracteristici (id_caracteristica,descriere,denumire) 
values (6,'la ce temperatura trebuie tinute (vin etc)','temperatura specifica');
insert into caracteristici (id_caracteristica,descriere,denumire) 
values (7,'mediu in care trebuie tinute (poate nu in umezeala?)','umiditate specifica');
insert into caracteristici (id_caracteristica,descriere,denumire) 
values (8,'versiuni america/europa ce trebuie diferentiate rapid','voltaj');
insert into caracteristici (id_caracteristica,descriere,denumire) 
values (9,'daca trebuie intretinut, udat, asteapta prelucrare, asteapta trimitere undeva, trebuie sa vina cineva sa il ia etc','conditii speciale');
insert into caracteristici (id_caracteristica,descriere,denumire) 
values (10,'restul','altele');

create table categorii
  ( id_categorie number(20,0) primary key,
    denumire varchar2(20) not null,
    nivel number(20,0),
    id_parinte number(20,0) references categorii(id_categorie)
  );

insert into categorii
values ( 1,'it',1,null);
insert into categorii
values ( 2,'electrocasnice',2,null);
insert into categorii
values ( 3,'alimente',3,null);
insert into categorii
values (4,'make-up',6,null);
insert into categorii
values ( 5,'tablete',2,1);
insert into categorii
values ( 6,'fructe',2,3);
insert into categorii
values ( 7,'legume',7,3);
insert into categorii
values ( 8,'papetarie',7,null);
insert into categorii
values ( 9,'telefoane',1,1);
insert into categorii
values (10,'accesorii',8,null);

create table produse 
   (denumire varchar2(20 byte), 
	descriere nvarchar2(500), 
	stoc_curent float(126), 
	stoc_impus float(126), 
	pret_unitar float(126), 
	greutate float(126), 
	volum float(126), 
	tva float(126), 
	id_zona number(20,0), 
	id_um number(20,0), 
	id_categorie number(20,0), 
	data_crearii date, 
	data_modificarii date, 
	activ number(20,0), 
	id_produs number(38,0)
   );

create unique index produse_pk on produse (id_produs) ;

alter table produse add constraint produse_pk primary key (id_produs) enable;

alter table produse add constraint produse_categorii_fk foreign key (id_categorie)
  references categorii (id_categorie) enable;

alter table produse add constraint produse_um_fk foreign key (id_um)
  references unitati_de_masura (id_um) enable;

alter table produse add constraint produse_zone_fk foreign key (id_zona)
  references zone (id_zona) enable;

insert into produse (denumire,descriere,stoc_curent,stoc_impus,
pret_unitar,greutate,volum,tva,id_zona,id_um,id_categorie,data_crearii,data_modificarii,activ,id_produs) 
values ('pasta de dinti','pasta de din?i este o past? (sau un gel) folosit? pentru a cur??a ?i îmbun?t??i s?n?tatea ?i aspectul estetic al din?ilor.',
2,1,10,100,null,4.5,1,1,1,to_date('12-oct-11','dd-mon-rr'),to_date('12-oct-16','dd-mon-rr'),1,1);

insert into produse (denumire,descriere,stoc_curent,stoc_impus,
pret_unitar,greutate,volum,tva,id_zona,id_um,id_categorie,data_crearii,data_modificarii,activ,id_produs) 
values ('cafea','cafeaua este o b?utur? de culoare neagr? ce con?ine cafein? ?i care se ob?ine din boabe de cafea pr?jite ?i m?cinate.',
4,2,40,400,null,6.7,2,2,2,to_date('02-oct-10','dd-mon-rr'),to_date('12-aug-16','dd-mon-rr'),0,2);

insert into produse (denumire,descriere,stoc_curent,stoc_impus,
pret_unitar,greutate,volum,tva,id_zona,id_um,id_categorie,data_crearii,data_modificarii,activ,id_produs) 
values ('televizor','televizorul (sau simplu, tv) este un dispozitiv electronic folosit pentru a recep?iona ?i reda emisiuni de radiodifuziune vizual? (televiziune radiodifuzat?), care difuzeaz? programe de televiziune, fiind folosit ast?zi pentru divertisment, pentru educare ?i pentru informare.',
8,3,800,8000,null,19,3,3,3,to_date('26-aug-09','dd-mon-rr'),to_date('12-mar-16','dd-mon-rr'),0,3);

insert into produse (denumire,descriere,stoc_curent,stoc_impus,
pret_unitar,greutate,volum,tva,id_zona,id_um,id_categorie,data_crearii,data_modificarii,activ,id_produs) 
values ('detergent','detergen?ii sunt produ?i de sintez?, având o structur? asem?n?toare cu cea a s?punurilor.',
6,4,32,5000,null,10.15,4,4,4,to_date('11-mar-04','dd-mon-rr'),to_date('12-oct-16','dd-mon-rr'),1,4);

insert into produse (denumire,descriere,stoc_curent,stoc_impus,
pret_unitar,greutate,volum,tva,id_zona,id_um,id_categorie,data_crearii,data_modificarii,activ,id_produs) 
values ('burete','un burete este o ustensil? pentru cur??are alc?tuit? dintr-un material poros cu proprietatea de a absorbi lichide.',
18,5,5,50,null,21,5,5,5,to_date('19-mar-03','dd-mon-rr'),to_date('12-oct-16','dd-mon-rr'),1,5);

insert into produse (denumire,descriere,stoc_curent,stoc_impus,
pret_unitar,greutate,volum,tva,id_zona,id_um,id_categorie,data_crearii,data_modificarii,activ,id_produs) 
values ('ciocolata','ciocolata este un produs alimentar ob?inut dintr-un amestec de cacao, zah?r, uneori lapte ?i unele arome specifice.',
32,6,3,200,null,19,6,6,6,to_date('10-jun-09','dd-mon-rr'),to_date('17-mar-16','dd-mon-rr'),1,6);

insert into produse (denumire,descriere,stoc_curent,stoc_impus,
pret_unitar,greutate,volum,tva,id_zona,id_um,id_categorie,data_crearii,data_modificarii,activ,id_produs) 
values ('cola','cola este o b?utur? carbogazoas?, îndulcit? artificial, derivat? din b?utura care ini?ial con?inea cofein? din nuca de cola ?i cocain? din frunzele de cola, cu arom? de vanilie sau alte ingrediente.',
64,7,5,2000,2000,23.4,7,1,7,to_date('16-oct-09','dd-mon-rr'),to_date('19-may-16','dd-mon-rr'),0,7);

insert into produse (denumire,descriere,stoc_curent,stoc_impus,
pret_unitar,greutate,volum,tva,id_zona,id_um,id_categorie,data_crearii,data_modificarii,activ,id_produs) 
values ('paine','pâinea este un aliment de baz? produs prin coacerea aluatului ob?inut din f?in? amestecat? cu ap? ?i drojdie, ad?ugându-se de la caz la caz diferi?i ingredien?i în func?ie de categoria pâinii ob?inute.',
128,8,1,1000,null,27,8,2,8,to_date('19-may-11','dd-mon-rr'),to_date('12-oct-16','dd-mon-rr'),0,8);

insert into produse (denumire,descriere,stoc_curent,stoc_impus,
pret_unitar,greutate,volum,tva,id_zona,id_um,id_categorie,data_crearii,data_modificarii,activ,id_produs) 
values ('tricou','tricoul este un articol de îmbr?c?minte, de obicei cu mâneci scurte, care se îmbrac? direct pe corp',
256,9,50.8,300,null,19,9,3,9,to_date('31-dec-08','dd-mon-rr'),to_date('12-may-16','dd-mon-rr'),0,9);

insert into produse (denumire,descriere,stoc_curent,stoc_impus,
pret_unitar,greutate,volum,tva,id_zona,id_um,id_categorie,data_crearii,data_modificarii,activ,id_produs) 
values ('bicicleta','o biciclet? poate fi definit? în general ca fiind un vehicul rutier cu dou? ro?i a?ezate în linie una în spatele celeilalte, pus în mi?care prin intermediul a dou? pedale ac?ionate cu picioarele.',
512,10,456.789,9000,null,19,10,4,10,to_date('12-oct-16','dd-mon-rr'),to_date('12-oct-16','dd-mon-rr'),1,10);

create table produse_au_caracteristici
(id_caracteristica number(38,0), 
id_produs number(38,0), 
valoare varchar2(255 byte)
);

create unique index pac_pk on produse_au_caracteristici (id_caracteristica, id_produs, valoare);

alter table produse_au_caracteristici add constraint pac_pk primary key (id_caracteristica, id_produs, valoare) enable;

alter table produse_au_caracteristici add constraint pac_caracteristici_fk foreign key (id_caracteristica)
  references caracteristici (id_caracteristica) enable;

alter table produse_au_caracteristici add constraint pac_produse_fk foreign key (id_produs)
  references produse (id_produs) enable;

insert into produse_au_caracteristici VALUES (6,1,20);
insert into produse_au_caracteristici VALUES (8,1,15);

insert into produse_au_caracteristici VALUES (2,2,20);
insert into produse_au_caracteristici VALUES (7,2,10);

insert into produse_au_caracteristici VALUES (3,3,2000);
insert into produse_au_caracteristici VALUES (44,3,8000);

insert into produse_au_caracteristici VALUES (6,4,100);
insert into produse_au_caracteristici VALUES (44,4,50);

insert into produse_au_caracteristici VALUES (2,5,5);
insert into produse_au_caracteristici VALUES (9,5,10);

insert into produse_au_caracteristici VALUES (2,6,20);
insert into produse_au_caracteristici VALUES (6,6,50);

insert into produse_au_caracteristici VALUES (2,7,20);
insert into produse_au_caracteristici VALUES (7,7,10);

insert into produse_au_caracteristici VALUES (2,8,10);
insert into produse_au_caracteristici VALUES (6,8,15);

insert into produse_au_caracteristici VALUES (8,9,50);
insert into produse_au_caracteristici VALUES (9,9,100);

insert into produse_au_caracteristici VALUES (8,10,2000);
insert into produse_au_caracteristici VALUES (44,10,2800);

create table clienti (
id_client number(10) primary key,
telefon varchar(20),
email varchar(50),
tip varchar(20),
oras varchar(30),
data_nasterii date,
data_modificarii date
);

create table clienti_persoane_fizice (
id_client_f number(10) primary key references clienti (id_client),
nume varchar(20),
prenume varchar(20),
cnp varchar(20)
);

create table clienti_persoane_juridice (
id_client_j number(10) primary key references clienti (id_client),
denumire varchar(50),
persoana_contact varchar(20),
cui varchar(20),
cont varchar(50),
banca varchar(30),
cod_fiscal varchar(20),
numar_inregistrare varchar(20)
);

---inserari (f =pers fizica; j = juridica)
---1f
insert into clienti(id_client,telefon, email, tip, oras, data_nasterii, data_modificarii)
values (1,'0712123123', 'razvy96@gmail.com', 'fizica', 'bucuresti', sysdate, sysdate);

insert into clienti_persoane_fizice(id_client_f, nume, prenume, cnp)
values (1, 'razvan', 'padina', '1961210303132');

---2j
insert into clienti(id_client,telefon, email, tip, oras, data_nasterii, data_modificarii)
values (2,'0790100200', 'contact@dconstr.com', 'juridica', 'bucuresti', to_date('10-10-1997','dd-mm-yyyy'), sysdate);

insert into clienti_persoane_juridice(id_client_j, denumire, persoana_contact, cui, cont, banca, cod_fiscal, numar_inregistrare)
values (2, 'sc dorel constructions srl', 'dorel gabriel', '6859662', 'ro60ingb0000999912345678', 'ing bank', 'ro122333' ,'j24/2673/1997');

---3j
insert into clienti(id_client,telefon, email, tip, oras, data_nasterii, data_modificarii)
values (3,'0711222333', 'george_filip@gmail.com', 'juridica', 'bucuresti', to_date('10-11-2010','dd-mm-yyyy'), sysdate);

insert into clienti_persoane_juridice(id_client_j, denumire, persoana_contact, cui, cont, banca, cod_fiscal, numar_inregistrare)
values (3, 'sc georgel auto srl', 'george filip', '1245789', 'ro60bnrb0000999987654321', 'bnr', 'ro557891' ,'j30/3000/2010');

---4f
insert into clienti(id_client,telefon, email, tip, oras, data_nasterii, data_modificarii)
values (4,'0790900900', 'edy_2k1@yahoo.ro', 'fizica', 'iasi', to_date('02-02-2001','dd-mm-yyyy'), sysdate);

insert into clienti_persoane_fizice(id_client_f, nume, prenume, cnp)
values (4, 'eduard', 'lorand', '1010202123123');

---5f
insert into clienti(id_client,telefon, email, tip, oras, data_nasterii, data_modificarii)
values (5,'0730300123', 'larissa_anghel@gmail.com', 'fizica', 'galati', to_date('12-04-1996','dd-mm-yyyy'), sysdate);

insert into clienti_persoane_fizice(id_client_f, nume, prenume, cnp)
values (5, 'larisa', 'anghel', '2960412100200');

--6f
insert into clienti(id_client,telefon, email, tip, oras, data_nasterii, data_modificarii)
values (6,'0750504505', 'roxpic@gmail.com', 'fizica', 'galati', to_date('20-04-1996','dd-mm-yyyy'), sysdate);

insert into clienti_persoane_fizice(id_client_f, nume, prenume, cnp)
values (6, 'roxana', 'picu', '2960420350450');

---7j
insert into clienti(id_client,telefon, email, tip, oras, data_nasterii, data_modificarii)
values (7,'0744117795', 'contact@bestphotos.ro', 'juridica', 'tulcea', to_date('10-06-2016','dd-mm-yyyy'), sysdate);

insert into clienti_persoane_juridice(id_client_j, denumire, persoana_contact, cui, cont, banca, cod_fiscal, numar_inregistrare)
values (7, 'sc best moments photography srl', 'valentina plopea', '4579125', 'ro60ingb0000999954627412', 'ingb', 'ro223456' ,'j45/6520/2016');

--8j
insert into clienti(id_client,telefon, email, tip, oras, data_nasterii, data_modificarii)
values (8,'0711845569', 'tortulet@bogdancakes.ro', 'juridica', 'iasi', to_date('10-05-2000','dd-mm-yyyy'), sysdate);

insert into clienti_persoane_juridice(id_client_j, denumire, persoana_contact, cui, cont, banca, cod_fiscal, numar_inregistrare)
values (8, 'tasty cakes srl', 'bogdan bradus', '7896543', 'ro80ingb0000999954629410', 'ingb', 'ro117895' ,'j67/7123/2000');

--9j
insert into clienti(id_client,telefon, email, tip, oras, data_nasterii, data_modificarii)
values (9,'0711753951', 'contact@brutariafericita.ro', 'juridica', 'bucuresti', to_date('10-10-2008','dd-mm-yyyy'), sysdate);

insert into clienti_persoane_juridice(id_client_j, denumire, persoana_contact, cui, cont, banca, cod_fiscal, numar_inregistrare)
values (9, 'brutaria fericita', 'ramona brutaru', '9517532', 'ro10ingb00009999345297109', 'ingb', 'ro100213' ,'j20/5462/2008');

--10j
insert into clienti(id_client,telefon, email, tip, oras, data_nasterii, data_modificarii)
values (10,'0752753852', 'florinel@progaminggear.ro', 'juridica', 'timisoara', to_date('20-09-2007','dd-mm-yyyy'), sysdate);

insert into clienti_persoane_juridice(id_client_j, denumire, persoana_contact, cui, cont, banca, cod_fiscal, numar_inregistrare)
values (10, 'sc pro-gaming gear srl', 'florin alexandru', '3025149', 'ro40bnrb00009999345594150', 'bnr', 'ro812085' ,'j70/8085/2007');

--11j
insert into clienti(id_client,telefon, email, tip, oras, data_nasterii, data_modificarii)
values (11,'0785953751', 'alex_rando@weseesharp.ro', 'juridica', 'bucuresti', to_date('05-10-2007','dd-mm-yyyy'), sysdate);

insert into clienti_persoane_juridice(id_client_j, denumire, persoana_contact, cui, cont, banca, cod_fiscal, numar_inregistrare)
values (11, 'we see sharp', 'alexander randovic', '7517530', 'ro40bnrb0000999934593264', 'bnr', 'ro800861' ,'j95/1052/2007');

--12j
insert into clienti(id_client,telefon, email, tip, oras, data_nasterii, data_modificarii)
values (12,'0775153759', 'woof@fluffyfriends.ro', 'juridica', 'arad', to_date('03-04-2016','dd-mm-yyyy'), sysdate);

insert into clienti_persoane_juridice(id_client_j, denumire, persoana_contact, cui, cont, banca, cod_fiscal, numar_inregistrare)
values (12, 'sc fluffy friends srl', 'alexandra ramona', '1537519', 'ro40bnrb0000999955517319', 'banca transilvania', 'ro759953' ,'j12/9856/2016');

--13f
insert into clienti(id_client,telefon, email, tip, oras, data_nasterii, data_modificarii)
values (13,'0780153420', 'pgheorghe@gmail.com', 'fizica', 'arad', to_date('18-10-1994','dd-mm-yyyy'), sysdate);

insert into clienti_persoane_fizice(id_client_f, nume, prenume, cnp)
values (13, 'paul', 'gheorghe', '1941018102896');

--14f
insert into clienti(id_client,telefon, email, tip, oras, data_nasterii, data_modificarii)
values (14,'0744622448', 'cgheorghe@gmail.com', 'fizica', 'arad', to_date('18-10-1994','dd-mm-yyyy'), sysdate);

insert into clienti_persoane_fizice(id_client_f, nume, prenume, cnp)
values (14, 'cristian', 'gheorghe', '1941018102897');

create table tip_livrare
   (id_tip_livrare number(38,0), 
	denumire varchar2(20 byte), 
	tarif number(5,2), 
	id_firma_t number(38,0)
   );

create unique index tip_livrare_pk on tip_livrare(id_tip_livrare);

alter table tip_livrare modify (id_tip_livrare not null enable);
 
alter table tip_livrare modify (denumire not null enable);

alter table tip_livrare add constraint tip_livrare_pk primary key (id_tip_livrare) enable;

insert into tip_livrare (id_tip_livrare,denumire,tarif,id_firma_t) 
values (5,'avion',999,5);

insert into tip_livrare (id_tip_livrare,denumire,tarif,id_firma_t) 
values (6,'vapor',400,8);

insert into tip_livrare (id_tip_livrare,denumire,tarif,id_firma_t) 
values (7,'tir',450,13);

insert into tip_livrare (id_tip_livrare,denumire,tarif,id_firma_t) 
values (8,'tren',500,21);

insert into tip_livrare (id_tip_livrare,denumire,tarif,id_firma_t) 
values (9,'ridicare sediu',0,null);

insert into tip_livrare (id_tip_livrare,denumire,tarif,id_firma_t) 
values (10,'altele',null,null);

insert into tip_livrare (id_tip_livrare,denumire,tarif,id_firma_t) 
values (1,'posta',300,1);

insert into tip_livrare (id_tip_livrare,denumire,tarif,id_firma_t) 
values (2,'dhl',300,1);

insert into tip_livrare (id_tip_livrare,denumire,tarif,id_firma_t) 
values (3,'curier',300,2);

insert into tip_livrare (id_tip_livrare,denumire,tarif,id_firma_t) 
values (4,'curier rapid',600,3);

-- insert all 
-- into tip_livrare values(1,'transport particular cu avion privat (200kg)',1400,354)
-- into tip_livrare values(2,'transport de marfuri generale (3t)',300,333)
-- into tip_livrare values(3,'transport de marfuri periculoase (400kg)',1000,75)
-- into tip_livrare values(4,'transport agabaritic (2t)',700,14)
-- into tip_livrare values(5,'transport cu vehicule specializate (1t)',600,658)
-- into tip_livrare values(6,'transport de animale vii ',500,33)
-- into tip_livrare values(7,'transport rapid',300,10)
-- into tip_livrare values(8,'transport mediu',200,9)
-- into tip_livrare values(9,'transport incet',100,8)
-- into tip_livrare values(10,'transport usor',150,3)
-- select * from dual;

create table adrese (
id_adresa number(10) primary key,
strada varchar(50),
oras varchar(20),
tara varchar(20),
cod_postal varchar(20),
id_client number(10),
constraint adrese_clienti_fk foreign key (id_client) references clienti(id_client)
);

--insert into adresa (id_adresa,strada,oras,tara,cod_postal,id_client) 
--values (1,'bulevard pompeiu dimitrie, mat. nr. 7',' bucuresti','romania',20335,1);
--
--insert into adresa (id_adresa,strada,oras,tara,cod_postal,id_client) 
--values (2,'calea dudesti nr. 94','bucuresti','romania',31087,2);
--
--insert into adresa (id_adresa,strada,oras,tara,cod_postal,id_client) 
--values (3,'strada antonescu petre, arh. nr. 6','bucuresti','romania',23591,3);
--
--insert into adresa (id_adresa,strada,oras,tara,cod_postal,id_client) 
--values (4,'bulevard vasile milea, g-ral. nr. 2','bucuresti','romania',61344,5);
--
--insert into adresa (id_adresa,strada,oras,tara,cod_postal,id_client) 
--values (5,'piata mare nr. 8','sibiu','romania',550163,2);
--
--insert into adresa (id_adresa,strada,oras,tara,cod_postal,id_client) 
--values (6,'strada muscatelor nr. 2','constanta','romania',900013,4);
--
--insert into adresa (id_adresa,strada,oras,tara,cod_postal,id_client) 
--values (7,'bulevard bratianu i. c. nr. 7','timisoara','romania',300001,6);
--
--insert into adresa (id_adresa,strada,oras,tara,cod_postal,id_client) 
--values (8,'strada lalelelor nr. 4','carei','romania',445100,7);
--
--insert into adresa (id_adresa,strada,oras,tara,cod_postal,id_client) 
--values (9,'kreisfreie stadt berlin no. 3','berlin','germania',10117,7);
--
--insert into adresa (id_adresa,strada,oras,tara,cod_postal,id_client) 
--values (10,'sadovaya ulitsa, 13','sankt-peterburg','russia',19101,1);

insert into adrese(id_adresa, strada, oras, tara, cod_postal, id_client)
values(1, 'prometeu, nr. 10', 'bucuresti', 'romania', '100201', 1);

insert into adrese(id_adresa, strada, oras, tara, cod_postal, id_client)
values(2, 'libertatii, nr. 10', 'bucuresti', 'romania', '123875', 2);

insert into adrese(id_adresa, strada, oras, tara, cod_postal, id_client)
values(3, 'marinarilor, nr. 10', 'bucuresti', 'romania', '123700', 3);

insert into adrese(id_adresa, strada, oras, tara, cod_postal, id_client)
values(4, 'bulevardul expozitiei, nr. 1', 'iasi', 'romania', '205751', 4);

insert into adrese(id_adresa, strada, oras, tara, cod_postal, id_client)
values(5, 'strada siret, nr. 5', 'galati', 'romania', '300102', 5);

insert into adrese(id_adresa, strada, oras, tara, cod_postal, id_client)
values(6, 'strada fabricii, nr. 143', 'galati', 'romania', '300157', 6);

insert into adrese(id_adresa, strada, oras, tara, cod_postal, id_client)
values(7, 'strada dunarii, nr. 70', 'tulcea', 'romania', '502101', 7);

insert into adrese(id_adresa, strada, oras, tara, cod_postal, id_client)
values(8, 'aleea botorani, nr. 99', 'iasi', 'romania', '750200', 8);

insert into adrese(id_adresa, strada, oras, tara, cod_postal, id_client)
values(9, 'calea plevnei, nr. 5', 'bucuresti', 'romania', '109400', 9);

insert into adrese(id_adresa, strada, oras, tara, cod_postal, id_client)
values(10, 'craisorului, nr. 17', 'timisoara', 'romania', '800251', 10);

insert into adrese(id_adresa, strada, oras, tara, cod_postal, id_client)
values(11, 'bulevardul uverturii, nr. 54', 'bucuresti', 'romania', '108300', 11);

insert into adrese(id_adresa, strada, oras, tara, cod_postal, id_client)
values(12, 'sfatului, nr. 102', 'tulcea', 'romania', '502101', 12);

insert into adrese(id_adresa, strada, oras, tara, cod_postal, id_client)
values(13, 'sergent turturica, nr. 30', 'arad', 'romania', '400120', 13);

insert into adrese(id_adresa, strada, oras, tara, cod_postal, id_client)
values(14, 'sergent turturica, nr. 30', 'arad', 'romania', '400120', 14);

create table tip_plata (
id_tip_plata number(10),
cod varchar(20),
descriere varchar(100)
);

create unique index tip_plata_pk on tip_plata(id_tip_plata);

alter table tip_plata modify (id_tip_plata not null enable);
 
alter table tip_plata modify (cod not null enable);

alter table tip_plata add constraint tip_plata_pk primary key (id_tip_plata);

--insert into tip_plata(id_tip_plata, cod, descriere)
--values(1, 100, 'la sediu, numerar');
--
--insert into tip_plata(id_tip_plata, cod, descriere)
--values(2, 101, 'la sediu, cu card');
--
--insert into tip_plata(id_tip_plata, cod, descriere)
--values(3, 200, 'online, card credit');
--
--insert into tip_plata(id_tip_plata, cod, descriere)
--values(4, 201, 'online, prin cardavantaj');
--
--insert into tip_plata(id_tip_plata, cod, descriere)
--values(5, 201, 'online, prin credit bcr');
--
--insert into tip_plata(id_tip_plata, cod, descriere)
--values(6, 203, 'online, cu card raiffeisen');
--
--insert into tip_plata(id_tip_plata, cod, descriere)
--values(7, 300, 'la livrare, ramburs');
--
--insert into tip_plata(id_tip_plata, cod, descriere)
--values(8, 400, 'ordin de plata');

insert into tip_plata (id_tip_plata,cod,descriere) 
values (1,'numerar','num');

insert into tip_plata (id_tip_plata,cod,descriere) 
values (2,'paypal','ppl');

insert into tip_plata (id_tip_plata,cod,descriere) 
values (3,'card online','col');

insert into tip_plata (id_tip_plata,cod,descriere) 
values (4,'card livrare','clv');

insert into tip_plata (id_tip_plata,cod,descriere) 
values (5,'ramburs','rmb');

insert into tip_plata (id_tip_plata,cod,descriere) 
values (6,'bitcoin','bit');

insert into tip_plata (id_tip_plata,cod,descriere) 
values (7,'ordin de plata','ord');

insert into tip_plata (id_tip_plata,cod,descriere) 
values (8,'transfer bancar','trb');

insert into tip_plata (id_tip_plata,cod,descriere) 
values (9,'western union','wnu');

insert into tip_plata (id_tip_plata,cod,descriere) 
values (10,'altul','alt');

create table clienti_au_pret_preferential
(
   id_pret_pref number(20,0),
   id_categorie number(20,0),
   id_client_j number(20,0),
   discount number(20,0),
   data_in date default sysdate,
   data_sf date,
   constraint clienti_au_pret_pref_pk primary key(id_pret_pref,id_categorie,id_client_j)
   );

alter table clienti_au_pret_preferential
add constraint pret_preferential_categorii_fk foreign key(id_categorie)
	references categorii(id_categorie);

alter table clienti_au_pret_preferential
add constraint pret_preferential_j_fk foreign key(id_client_j)
	references clienti_persoane_juridice(id_client_j);

insert into clienti_au_pret_preferential
 values (1,2,2,20,sysdate,to_date('07-dec-2016','dd-mon-yyyy'));

insert into clienti_au_pret_preferential
 values (2,1,3,30,to_date('07-sep-2016','dd-mon-yyyy'),to_date('07-dec-2016','dd-mon-yyyy'));

insert into clienti_au_pret_preferential
 values (3,5,7,50,to_date('10-aug-2016','dd-mon-yyyy'),to_date('07-oct-2016','dd-mon-yyyy'));

insert into clienti_au_pret_preferential
 values (4,1,8,15,to_date('21-sep-2016','dd-mon-yyyy'),to_date('24-sep-2016','dd-mon-yyyy'));

insert into clienti_au_pret_preferential
 values (5,7,9,25,to_date('07-aug-2016','dd-mon-yyyy'),to_date('07-feb-2017','dd-mon-yyyy'));

insert into clienti_au_pret_preferential
 values (6,7,10,50,to_date('22-oct-2016','dd-mon-yyyy'),to_date('23-oct-2016','dd-mon-yyyy'));

insert into clienti_au_pret_preferential
 values (7,3,11,30,to_date('07-sep-2016','dd-mon-yyyy'),to_date('07-dec-2016','dd-mon-yyyy'));

insert into clienti_au_pret_preferential
 values (8,4,12,35,to_date('07-dec-2016','dd-mon-yyyy'),to_date('10-dec-2016','dd-mon-yyyy'));

insert into clienti_au_pret_preferential
 values (9,8,12,45,to_date('07-oct-2016','dd-mon-yyyy'),to_date('07-feb-2016','dd-mon-yyyy'));

insert into clienti_au_pret_preferential
 values (10,1,10,33,to_date('07-sep-2016','dd-mon-yyyy'),to_date('25-dec-2016','dd-mon-yyyy'));

create table case (  
  id_casa int not null primary key,
  nume varchar(56),
  serie int not null,
  parola varchar2(24 char)
);

insert all 
into case values 
(1, 'casa1', 11, 'marketcasa1')
into case values 
(2, 'casa2', 21, 'marketcasa2')
into case values 
(3, 'casa3', 31, 'marketcasa3')
into case values 
(4, 'casa4', 41, 'marketcasa4')
into case values 
(5, 'casa5', 51, 'marketcasa5')
into case values 
(6, 'casa6', 61, 'marketcasa6')
into case values 
(7, 'casa7', 71, 'marketcasa7')
into case values 
(8, 'casa8', 81, 'marketcasa8')
into case values 
(9, 'casa9', 91, 'marketcasa9')
into case values 
(10, 'casa10', 101, 'marketcasa10')
select * from dual;

create table facturi
(  
	id_factura number(20,0) primary key,
   	data date,
   	status varchar2(20),
   	id_casa number(20,0),
   	id_client number(20,0),
   	id_adresa_livrare number(20,0),
   	id_adresa_facturare number(20,0),
   	id_tip_livrare number(20,0),
   	id_tip_plata number(20,0),
   	interval_livrare number(20,0)
);

alter table facturi 
add constraint facturi_clienti_fk foreign key(id_client)
references clienti(id_client);

alter table facturi 
add constraint facturi_case_fk foreign key(id_casa)
references case(id_casa);

alter table facturi 
add constraint facturi_tip_livrare_fk foreign key(id_tip_livrare)
references tip_livrare(id_tip_livrare);

alter table facturi 
add constraint facturi_tip_plata_fk foreign key(id_tip_plata)
references tip_plata(id_tip_plata);

insert into facturi
values (1,to_date('07-sep-2016','dd-mon-yyyy'),'achitat',1,1,1,1,1,1,5);

insert into facturi
values (2,to_date('17-sep-2016','dd-mon-yyyy'),'neachitat',1,1,1,1,1,2,10);

insert into facturi
values (3,to_date('13-sep-2016','dd-mon-yyyy'),'achitat',1,3,1,3,3,1,2);

insert into facturi
values (4,to_date('14-sep-2016','dd-mon-yyyy'),'achitat',1,3,1,3,2,1,2);

insert into facturi
values (5,to_date('02-sep-2016','dd-mon-yyyy'),'neachitat',1,2,3,4,1,2,3);

insert into facturi
values (6,to_date('01-sep-2016','dd-mon-yyyy'),'neachitat',2,1,1,1,3,5,1);

insert into facturi
values (7,to_date('04-sep-2016','dd-mon-yyyy'),'achitat',2,1,1,1,4,2,2);

insert into facturi
values (8,to_date('07-sep-2016','dd-mon-yyyy'),'achitat',3,3,8,5,2,7,2);

insert into facturi
values (9,to_date('07-sep-2016','dd-mon-yyyy'),'achitat',4,5,1,1,1,1,2);

insert into facturi
values (10,to_date('09-sep-2016','dd-mon-yyyy'),'neachitat',2,3,4,1,1,7,10);

create table facturi_contin_produse(
  id_factura int not null references facturi(id_factura),
  id_produs int not null references produse(id_produs),
  cantitate int not null,
  pret_facturare int not null
);

insert all
into facturi_contin_produse values (1,1, 68, 544)
into facturi_contin_produse values (2,2, 5, 25)
into facturi_contin_produse values (3,3, 10, 1600)
into facturi_contin_produse values (4,4, 90, 10800)
into facturi_contin_produse values (5,5, 400, 800)
into facturi_contin_produse values (6,6, 100, 200)
into facturi_contin_produse values (7,7, 30, 90)
into facturi_contin_produse values (8,8, 100, 500)
into facturi_contin_produse values (9,9, 50, 250)
into facturi_contin_produse values (10,10, 5, 1500)
select * from dual;

create table clasific_clienti 
   (id_client number(10,0) references clienti(id_client), 
	id_categorie number(20,0) references categorii(id_categorie), 
	nr_produse number(10,0), 
	clasificare varchar2(5 byte),
	primary key(id_client,id_categorie)
   );

insert into clasific_clienti (id_client,id_categorie,nr_produse,clasificare) values ('1','1','10','a');
insert into clasific_clienti (id_client,id_categorie,nr_produse,clasificare) values ('2','2','50','a');
insert into clasific_clienti (id_client,id_categorie,nr_produse,clasificare) values ('3','2','7','c');
insert into clasific_clienti (id_client,id_categorie,nr_produse,clasificare) values ('4','3','10','d');
insert into clasific_clienti (id_client,id_categorie,nr_produse,clasificare) values ('5','4','12','a');
insert into clasific_clienti (id_client,id_categorie,nr_produse,clasificare) values ('6','6','4','b');
insert into clasific_clienti (id_client,id_categorie,nr_produse,clasificare) values ('7','7','3','a');
insert into clasific_clienti (id_client,id_categorie,nr_produse,clasificare) values ('8','7','22','c');
insert into clasific_clienti (id_client,id_categorie,nr_produse,clasificare) values ('9','8','99','a');
insert into clasific_clienti (id_client,id_categorie,nr_produse,clasificare) values ('10','8','4','b');

insert into clasific_clienti (id_client,id_categorie,nr_produse,clasificare) values ('1','9','10','a');
insert into clasific_clienti (id_client,id_categorie,nr_produse,clasificare) values ('2','10','50','a');
insert into clasific_clienti (id_client,id_categorie,nr_produse,clasificare) values ('3','5','7','c');
insert into clasific_clienti (id_client,id_categorie,nr_produse,clasificare) values ('4','7','10','d');
insert into clasific_clienti (id_client,id_categorie,nr_produse,clasificare) values ('5','8','12','a');
insert into clasific_clienti (id_client,id_categorie,nr_produse,clasificare) values ('6','9','4','b');
insert into clasific_clienti (id_client,id_categorie,nr_produse,clasificare) values ('7','10','3','a');
insert into clasific_clienti (id_client,id_categorie,nr_produse,clasificare) values ('8','9','22','c');
insert into clasific_clienti (id_client,id_categorie,nr_produse,clasificare) values ('9','10','99','a');
insert into clasific_clienti (id_client,id_categorie,nr_produse,clasificare) values ('10','10','4','b');

commit;