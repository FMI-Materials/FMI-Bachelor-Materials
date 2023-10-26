



create table hotel_ati
(
    id number(5) primary key,
    denumire varchar2(20),
    nr_stele number(2),
    localitate varchar2(20)
);

create table camera_ati
(
    id number(5) primary key,
    id_hotel number(5) references hotel_ati(id),
    nr_camera number(5),
    capacitate number(10)
);

create table cazare_ati
(
    id number(5) primary key,
    id_camera number(5) references camera_ati(id),
    data_cazare date,
    nr_zile number(5)
);

create table tarif_camera_ati
(
    id_camera number(5) references camera_ati(id),
    data_start date,
    data_end date,
    tarif number(6),
    constraint pk_tc primary key(id_camera, data_start)
);

create table turist_ati
(
    id number(5) primary key,
    nume varchar2(20),
    prenume varchar2(20),
    data_nasterii date not null,
    localitate_domiciliu varchar2(20),
    tara varchar2(20),
    telefon number(10)
);

create table turist_cazare_ati
(
    id_cazare number(5) references cazare_ati(id),
    id_turist number(5) references turist_ati(id),
    constraint pk_tcaz primary key(id_cazare, id_turist)
);

create table facilitate_ati
(
    id number(5) primary key,
    denumire varchar2(20)
);

create table facilitati_hotel_ati
(
    id_hotel number(5) references hotel_ati(id), 
    id_facilitate number(5) references facilitate_ati(id),
    constraint pk_fh primary key(id_hotel, id_facilitate)
);

insert into hotel_ati values (1, 'H', 3, 'SV');
insert into hotel_ati values (2, 'C', 4, 'SV');
insert into hotel_ati values (3, 'A', 5, 'V');

insert into camera_ati values(1, 1, 1, 1);
insert into camera_ati values(3, 1, 1, 1);
insert into camera_ati values(2, 1, 1, 1);

select sysdate from dual;

insert into turist_ati values(1, 'X', 'X', '10-JAN-1989', 'X', 'X', null);
insert into turist_ati values(3, 'y', 'X', '10-JAN-2005', 'X', 'X', null);

insert into cazare_ati values(1, 1, sysdate, 2);
insert into cazare_ati values(2, 3, sysdate, 2);
insert into cazare_ati values(2, 3, sysdate, 2);

insert into turist_cazare_ati values(2, 3);



--EXAM 16
--1

SELECT DISTINCT h.denumire, f.denumire
FROM hotel_ati h JOIN camera_ati c ON (h.id = c.id_hotel)
    JOIN cazare_ati caz ON (caz.id_camera = c.id)
    JOIN facilitati_hotel_ati fh ON (fh.id_hotel = h.id)
    LEFT JOIN facilitate_ati f ON (fh.id_facilitate = f.id)
WHERE EXTRACT(YEAR FROM caz.data_cazare) = 2020;

--2


SELECT h.denumire, c.nr_camera,
    COUNT(CASE WHEN EXTRACT(YEAR FROM caz.data_cazare) = 2017 AND
                    EXTRACT(YEAR FROM caz.data_cazare + caz.nr_zile) = 2017
                THEN caz.id END) "2017",
    COUNT(CASE WHEN EXTRACT(YEAR FROM caz.data_cazare) = 2020 AND
                    EXTRACT(YEAR FROM caz.data_cazare + caz.nr_zile) = 2020
                THEN caz.id END) "2020"
FROM camera_ati c JOIN cazare_ati caz ON (c.id = caz.id_camera)
    JOIN hotel_ati h ON (h.id = c.id_hotel)
GROUP BY h.denumire, c.nr_camera;



--3

WITH good_hotel AS
    (SELECT h.id
     FROM hotel_ati h JOIN camera_ati c ON (h.id = c.id_hotel)
        JOIN tarif_camera_ati tc ON (tc.id_camera = c.id AND data_end > sysdate)
     GROUP BY h.id
     HAVING MIN (tc.tarif) = (SELECT MIN(tarif)
                              FROM tarif_camera_ati
                              WHERE data_start <= sysdate AND data_end >= sysdate))
     
SELECT *
FROM turist_ati t
WHERE (SELECT COUNT(*)
       FROM hotel_ati h
       WHERE EXISTS (SELECT *
                     FROM turist_cazare_ati tc 
                        JOIN cazare_ati caz ON (tc.id_cazare = caz.id)
                        JOIN camera_ati c ON (c.id = caz.id_camera)
                     WHERE tc.id_turist = t.id AND c.id_hotel = h.id)
         AND h.id IN (SELECT * FROM good_hotel)
) >= 2;


--4

UPDATE camera_ati
SET capacitate = capacitate + 1
WHERE id_hotel = (SELECT *
                  FROM(SELECT c.id_hotel
                       FROM camera_ati c
                       GROUP BY c.id_hotel
                       ORDER BY sum(capacitate))
                  WHERE rownum = 1);


--5

CREATE TABLE c_facilitati_hotel_ati AS
SELECT *
FROM facilitati_hotel_ati;

DESC c_facilitati_hotel_ati;

ALTER TABLE c_facilitati_hotel_ati
ADD CONSTRAINT PK PRIMARY KEY(id_hotel, id_facilitate);

ALTER TABLE c_facilitati_hotel_ati
ADD CONSTRAINT fk_hotel FOREIGN KEY (id_hotel) REFERENCES hotel_ati(id) ON DELETE CASCADE;
ALTER TABLE c_facilitati_hotel_ati
ADD CONSTRAINT fk_facilitate FOREIGN KEY (id_facilitate) REFERENCES facilitate_ati(id) ON DELETE CASCADE;

DESC turist_ati;

ALTER TABLE turist_ati
ADD CONSTRAINT nume_not_null CHECK(NUME IS NOT NULL);

ALTER TABLE turist_ati
MODIFY nume NOT NULL;

SELECT *
FROM user_constraints
WHERE LOWER(table_name) = 'turist_ati';



DESC user_constraints;
SELECT *
FROM user_constraints WHERE lower(table_name) = 'c_facilitati_hotel_ati';

ALTER TABLE c_Facilitati_hotel_ati
DROP CONSTRAINT fk_facilitate;







































