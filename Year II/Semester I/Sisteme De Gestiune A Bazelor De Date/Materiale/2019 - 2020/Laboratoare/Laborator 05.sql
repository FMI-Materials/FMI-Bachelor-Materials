-- Exemple
-- 1. Definiti un declansator care sa nu permita lucrul asupra tabelului emp_***(INSERT,  UPDATE, DELETE) 
-- in afara intervalul de ore 8:00-20:00, de luni pana sambata (declansator  la  nivel de instructiune).
CREATE OR REPLACE TRIGGER trig1_dda
    BEFORE INSERT OR UPDATE OR DELETE ON emp_dda
BEGIN
    IF (TO_CHAR(sysdate, 'D') = 1) OR (TO_CHAR(sysdate, 'HH24') NOT BETWEEN 8 AND 20) THEN
        RAISE_APPLICATION_ERROR(-20001, 'The table can not be updated during this time');
    END IF;
END;
/

DROP TRIGGER trig1_dda;


-- 2. Definiti un declansator prin care sa nu se permita micsorarea salariilor angajatilor din tabelul emp_*** (declansator la nivel de linie).
-- Varianta 1
CREATE OR REPLACE TRIGGER trig21_dda
    BEFORE UPDATE OF salary ON emp_dda
    FOR EACH ROW
BEGIN
    IF(:NEW.salary < :OLD.salary) THEN
        RAISE_APPLICATION_ERROR(-20002, 'Salariul nu poate fi micsorat');
    END IF;
END;
/

UPDATE emp_dda
SET salary = salary-100;

DROP TRIGGER trig21_dda;

-- Varianta 2
CREATE OR REPLACE TRIGGER trig22_dda 
    BEFORE UPDATE OF salary ON emp_dda
    FOR EACH ROW
    WHEN(NEW.salary < OLD.salary)
BEGIN
    RAISE_APPLICATION_ERROR(-20002, 'Salariu; nu poate fi micsorat');
END;
/

UPDATE emp_dda
SET salary = salary - 100;

DROP TRIGGER trig22_dda;

-- 3. Creati un declansator care sa nu permita marirea limitei inferioare a grilei de salarizare 1, respectiv micsorarea limitei 
-- superioare a grilei de salarizare 7, decat daca toate salariile se gasesc in intervalul dat de aceste doua valori modificate.
-- Se va utiliza tabelul job_grades_***.
CREATE TABLE job_grades_dda AS SELECT * FROM job_grades;

CREATE OR REPLACE TRIGGER trig3_dda
    BEFORE UPDATE OF lowest_sal, highest_sal ON job_grades_dda
    FOR EACH ROW
DECLARE
    v_min_sal emp_dda.salary%TYPE;
    v_max_sal emp_dda.salary%TYPE;
    exception1 EXCEPTION;
    exception2 EXCEPTION;
BEGIN
    SELECT MIN(salary), MAX(salary)
    INTO v_min_sal, v_max_sal
    FROM emp_dda;
    
    IF (v_min_sal < :NEW.lowest_sal) AND (:OLD.grade_level = 1) THEN
        RAISE exception1;
    ELSIF (v_max_sal > :NEW.highest_sal) AND (:OLD.grade_level = 7) THEN
        RAISE exception1;
    ELSIF (:NEW.lowest_sal > :NEW.highest_sal) THEN
        RAISE exception2;
    END IF;
EXCEPTION
    WHEN exception1 THEN
        RAISE_APPLICATION_ERROR(-20004, 'Exista salarii care se gasesc in afara intervalului');
    WHEN exception2 THEN
        RAISE_APPLICATION_ERROR(-20005, 'LOWEST_SAL nu poate fi mai mic decat HIGHEST_SAL!');
END;
/

DROP TRIGGER trig3_dda;
DROP TABLE job_grades_dda;


-- 4. a) Creati tabelul info_dept_*** cu urmatoarele coloane:
--       - id (codul departamentului - cheie primara)
--       - nume_dept (numele departamentului)
--       - plati (suma alocata pentru plata salariilor angajatilor care lucreaza in departamentul respectiv)
CREATE TABLE dep_dda AS SELECT * FROM departments;

CREATE TABLE info_dept_dda(
    id NUMBER(4) PRIMARY KEY,
    nume_dept VARCHAR2(30),
    plati NUMBER(16,2)
);
     
--    b) Introduceti date in tabelul creat anterior corespunzatoare informatiilor existente in schema
INSERT INTO info_dept_dda
SELECT d.department_id, d.department_name, SUM(NVL(e.salary, 0))
FROM dep_dda d, emp_dda e
WHERE d.department_id = e.department_id(+)
GROUP BY d.department_id, d.department_name;

--    c) Definiti un declansator care va actualiza automat campul plati atunci cand se introduce un
--  nou salariat, respectiv se sterge un salariat sau se modifica salariul unui angajat.

CREATE OR REPLACE PROCEDURE modific_plati_dda
    (v_id_dep info_dept_dda.id%TYPE,
     v_salary emp_dda.salary%TYPE)AS
BEGIN
    UPDATE info_dept_dda
    SET plati = plati + v_salary
    WHERE id = v_id_dep;
END;
/

CREATE OR REPLACE TRIGGER trig4_dda
    AFTER DELETE OR INSERT OR UPDATE OF salary ON emp_dda
    FOR EACH ROW
BEGIN
    IF DELETING THEN 
    -- se sterge un angajat din baza de date
        modific_plati_dda(:OLD.department_id, (-1) * :OLD.salary);
    ELSIF INSERTING THEN
    -- se introduce un nou angajat in baza de date
        modific_plati_dda(:NEW.department_id, :NEW.salary);
    ELSE
    -- se modifica salariul unui angajat din baza de date
        modific_plati_dda(:OLD.department_id, :NEW.salary - :OLD.salary);
    END IF;
END;
/

SELECT * FROM info_dept_dda WHERE id=90;

INSERT INTO emp_dda (employee_id, last_name, email, hire_date,
 job_id, salary, department_id)
VALUES (300, 'N1', 'n1@g.com',sysdate, 'SA_REP', 2000, 90);

SELECT * FROM info_dept_dda WHERE id=90;

UPDATE emp_dda
SET salary = salary + 1000
WHERE employee_id=300;

SELECT * FROM info_dept_dda WHERE id=90;

DELETE FROM emp_dda
WHERE employee_id=300;

SELECT * FROM info_dept_dda WHERE id=90;
ROLLBACK;

DROP PROCEDURE modific_plati_dda;
DROP TRIGGER trig4_dda;


-- 5. a) Creati tabelul info_emp_*** cu urmatoarele coloane:
--       - id_emp (codul angajatului) – cheie primara;
--       - nume (numele angajatului);
--       - prenume (prenumele angajatului);
--       - salariu (salariul angajatului);
--       - id_dept (codul departamentului) – cheie externa care refera tabelul info_dept_***.
CREATE TABLE info_emp_dda(
    id_emp NUMBER(6) PRIMARY KEY,
    nume VARCHAR(25) NOT NULL,
    prenume VARCHAR2(20),
    salariu NUMBER(8,2),
    id_dept NUMBER(4) REFERENCING info_dept_dda
);

--    b) Introduceti date in tabelul creat anterior corespunzatoare informatiilor existente in schema.
INSERT INTO info_emp_dda
SELECT e.employee_id, e.last_name, e.first_name,
    e.salary, e.department_id
FROM emp_dda e;

--    c) Creati vizualizarea v_info_*** care va contine informatii complete despre angajati si departamentele acestora. 
--  Folositi cele doua tabele create anterior, info_emp_***, respectiv info_dept_***.
CREATE OR REPLACE VIEW v_info_dda AS
    SELECT e.id_emp, e.nume, e.prenume, e.salariu, e.id_dept,
        d.nume_dept, d.plati
    FROM info_emp_dda e, info_dept_dda d
    WHERE e.id_dept = d.id;

--    d) Se pot realiza actualizari asupra acestei vizualizari? Care este tabelul protejat prin cheie?
-- Tabelul protejat de cheie este info_emp_dda;
SELECT *
FROM USER_UPDATABLE_COLUMNS
WHERE TABLE_NAME = 'V_INFO_DDA';

--    e) Definiti un declansator prin care actualizarile ce au loc asupra vizualizarii se propaga automat in 
--  tabelele de baza (declansator INSTEAD OF). Se considera ca au loc urmatoarele actualizari asupra vizualizarii:
--    - se adauga un angajat intr-un departament deja existent;
--    - se elimina un angajat;
--    - se modifica valoarea salariului unui angajat;
--    - se modifica departamentul unui angajat (codul departamentului).

--    f) Verificati daca declansatorul definit functioneaza corect.
--    g) Modificati declansatorul definit astfel incat sa permita si urmatoarele operatii:
--      - se adauga un angajat si departamentul acestuia (departamentul este nou);
--      - se adauga doar un departament.
--    j) Modificati declansatorul definit anterior astfel incat sa permita propagarea in tabelele de
--    baza a actualizarilor realizate asupra numelui si prenumelui angajatului, respectiv asupra numelui de departament.


CREATE OR REPLACE TRIGGER trig5_dda
    INSTEAD OF DELETE OR INSERT OR UPDATE ON v_info_dda
    FOR EACH ROW
DECLARE
    id_dept_exists NUMBER(3) := 0;
BEGIN
    IF DELETING THEN
    -- stergerea unui angajat din vizualizarea v_info_dda determina stergerea acestuia din
    -- tabela info_emp_dda si reactualizarea tabelei info_dept_dda
        DELETE FROM info_emp_dda
        WHERE id_emp = :OLD.id_emp;
        
        UPDATE info_dept_dda
        SET plati = plati - :OLD.salariu
        WHERE id = :OLD.id_dept;
        
    ELSIF INSERTING THEN
    -- adaugarea unui nou angajat in baza de date prin intermediul vizualizarii v_info_dda determina introducerea 
    -- angajatului in tabela info_emp_dda si actualizarea/introducerea de date in tabelui info_dept_dda    
        IF :NEW.id_emp <> NULL THEN
            INSERT INTO info_emp_dda
            VALUES (:NEW.id_emp, :NEW.nume, :NEW.prenume, :NEW.salariu, :NEW.id_dept);
        END IF;
        
        SELECT COUNT(*) INTO id_dept_exists
        FROM info_dept_dda
        WHERE id = :NEW.id_dept;
        
        IF id_dept_exists = 0 THEN
        -- introducem un nou departament
            INSERT INTO info_dept_dda
            VALUES(:NEW.id_dept, :NEW.nume_dept, NVL(:NEW.salariu,0));
        ELSE
        -- departamentul exista
            UPDATE info_dept_dda
            SET plati = plati + :NEW.salariu
            WHERE id = :NEW.id_dept;
        END IF;
            
    ELSIF UPDATING('salariu') THEN
    -- modificarea unui salariu din vizualizare determina modificarea 
    -- salariului in info_emp_dda si reactualizarea in info_dept_dda
        UPDATE info_emp_dda
        SET salariu = :NEW.salariu
        WHERE id_emp = :OLD.id_emp;
        
        UPDATE info_dept_dda
        SET plati = plati + :NEW.salariu - :OLD.salariu
        WHERE id = :OLD.id_dept;
        
    ELSIF UPDATING('nume') THEN
    -- modificarea numelui unui angajat din vizualizare determina modificarea numelui angajatului in tabela info_emp_dda
        UPDATE info_emp_dda
        SET nume = :NEW.nume
        WHERE id_emp = :OLD.id_emp;
    
    ELSIF UPDATING('prenume') THEN
    -- modificarea numelui unui angajat din vizualizare determina modificarea numelui angajatului in tabela info_emp_dda
        UPDATE info_emp_dda
        SET prenume = :NEW.prenume
        WHERE id_emp = :OLD.id_emp;
        
    ELSIF UPDATING('id_dept') THEN
    -- modificarea unui cod de departament din vizualizare determina modificarea 
    -- codului in info_emp_dda si reactualizarea in info_dept_dda
        UPDATE info_emp_dda
        SET id_dept = :NEW.id_dept;
        
        UPDATE info_dept_dda
        SET plati = plati - :OLD.salariu
        WHERE id = :OLD.id_dept;
        
        UPDATE info_dept_dda
        SET plati = plati + :OLD.salariu
        WHERE id = :NEW.id_dept;
    END IF;
END;
/

-- adaugarea unui nou angajat
SELECT * FROM info_dept_dda WHERE id=10;
INSERT INTO v_info_dda
VALUES (400, 'N1', 'P1', 3000, 10, 'Nume dept', 0);

SELECT * FROM info_emp_dda WHERE id_emp=400;
SELECT * FROM info_dept_dda WHERE id=10;
-- modificarea salariului unui angajat
UPDATE v_info_dda
SET salariu=salariu + 1000
WHERE id_emp=400;

SELECT * FROM info_emp_dda WHERE id_emp=400;
SELECT * FROM info_dept_dda WHERE id=10;

-- modificarea numelui unui angajat
SELECT * FROM info_emp_dda WHERE id_emp=400;
UPDATE v_info_dda
SET nume = 'Nume1'
WHERE id_emp = 400;

SELECT * FROM info_emp_dda WHERE id_emp=400;

-- modificarea departamentului unui angajat
SELECT * FROM info_dept_dda WHERE id=90;
UPDATE v_info_dda
SET id_dept = 90
WHERE id_emp=400;
SELECT * FROM info_emp_dda WHERE id_emp=400;
SELECT * FROM info_dept_dda WHERE id IN (10,90);

-- eliminarea unui angajat
DELETE FROM v_info_dda WHERE id_emp = 400;

SELECT * FROM info_emp_dda WHERE id_emp=400;
SELECT * FROM info_dept_dda WHERE id = 90;

DROP TRIGGER trig5_dda;


-- 6. Definiti un declansator care sa nu se permita stergerea informatiilor din tabelul emp_*** de catre utilizatorul grupa***.
CREATE OR REPLACE TRIGGER trig6_dda
    BEFORE DELETE ON emp_dda
BEGIN
    IF USER = UPPER('DANADASCALESCU') THEN
        RAISE_APPLICATION_ERROR(-20090, 'Nu ai voie sa stergi!');
    END IF;
END;
/

DELETE * FROM emp_dda;

DROP TRIGGER trig6_dda;


-- 7. a) Creati tabelul audit_*** cu urmatoarele campuri:
--        - utilizator (numele utilizatorului);
--        - nume_bd (numele bazei de date);
--        - eveniment (evenimentul sistem);
--        - nume_obiect (numele obiectului);
--        - data (data producerii evenimentului).
CREATE TABLE audit_dda(
    utilizator VARCHAR2(32),
    nume_bd VARCHAR2(64),
    eveniment VARCHAR2(24),
    nume_obiect VARCHAR2(32),
    data DATE
);

--    b.) Definiti un declansator care sa introduca date in acest tabel dupa ce utilizatorul a folosit o
--  comanda LDD (declansator sistem - la nivel de schema).
CREATE OR REPLACE TRIGGER trig7_dda
    AFTER CREATE OR DROP OR ALTER ON SCHEMA
BEGIN
    INSERT INTO audit_dda
    VALUES(SYS.LOGIN_USER, SYS.DATABASE_NAME, 
        SYS.SYSEVENT, SYS.DICTIONARY_OBJ_NAME, SYSDATE);
END;
/

CREATE INDEX ind_dda ON info_emp_dda(nume);
DROP INDEX ind_dda;
SELECT * FROM audit_dda;

DROP TRIGGER trig7_dda;
DROP TABLE audit_dda;


-- 8. Definiti un declansator care sa nu permita modificarea:
--    - valorii salariului maxim astfel incat acesta sa devina mai mare decat media tuturor salariilor;
--    - valorii salariului minim astfel incat acesta sa devina mai mare decat media tuturor salariilor;

--    In acest caz este necesara mentinerea unor variabile in care sa se retina salariul minim,
-- salariul maxim, respectiv media salariilor. Variabilele se definesc intr-un pachet, iar apoi pot
-- fi referite in declansator prin nume_pachet.nume_variabila.

--    Este necesar sa se defineasca doi declansatori:
--    - un declansator la nivel de comanda care sa actualizeze variabilele din pachet
--    - un declansator la nivel de linie care sa realizeze verificarea conditiilor.
CREATE OR REPLACE PACKAGE package_dda
AS
    smin emp_dda.salary%TYPE;
    smax emp_dda.salary%TYPE;
    smean emp_dda.salary%TYPE;
END package_dda;
/

CREATE TRIGGER trig81_dda
    BEFORE UPDATE OF salary ON emp_dda
BEGIN
    SELECT MIN(salary), MAX(salary), AVG(salary)
    INTO package_dda.smin, package_dda.smax, package_dda.smean
    FROM emp_dda;
END;
/

CREATE OR REPLACE TRIGGER trig82_dda
    BEFORE UPDATE OF salary ON emp_dda
    FOR EACH ROW
BEGIN
    IF(:OLD.salary = package_dda.smin) AND (:NEW.salary > package_dda.smean) THEN
        RAISE_APPLICATION_ERROR(-20005, 'Acest salariu depaseste valoarea medie');
    ELSIF (:OLD.salary = package_dda.smax) AND (:NEW.salary < package_dda.smean) THEN
        RAISE_APPLICATION_ERROR(-20006, 'Acest salariu este sub valoarea medie');
    END IF;
END;
/

SELECT AVG(salary)
FROM emp_dda;

UPDATE emp_dda
SET salary = 7000
WHERE salary = (SELECT MIN(salary) FROM emp_dda);

UPDATE emp_dda
SET salary = 6000
WHERE salary = (SELECT MAX(salary) FROM emp_dda);

DROP TRIGGER trig81_dda;
DROP TRIGGER trig82_dda;
DROP PACKAGE package_dda;

-- Exercitii
-- 1.  Definiti un declansator care sa permita stergerea informatiilor din tabelul dept_*** decat daca utilizatorul este SCOTT. 
CREATE OR REPLACE TRIGGER trig1_dda
    BEFORE DELETE ON dep_dda
BEGIN
    IF USER <> 'SCOTT' THEN
        RAISE_APPLICATION_ERROR(-20001, 'Nu ai voie sa stergi!');
    END IF;
END;
/

DELETE FROM dep_dda WHERE department_id = 30;

DROP TRIGGER trig1_dda;


-- 2. Creati un declansator prin care sa nu se permita marirea comisionului astfel incat sa depaseasca 50% din valoarea salariului.
-- Varianta 1
CREATE OR REPLACE TRIGGER trig21_dda
    BEFORE UPDATE OF commission_pct ON emp_dda
    FOR EACH ROW
BEGIN
    IF (:NEW.commission_pct > 0.5) THEN
        RAISE_APPLICATION_ERROR(-20007, 'Comisionul depaseste 50% din valoarea salariului');
    END IF;
END;
/

-- Varianata 2
CREATE OR REPLACE TRIGGER trig22_dda
    BEFORE UPDATE OF commission_pct ON emp_dda
    FOR EACH ROW
    WHEN (NEW.commission_pct > 0.5)
BEGIN
    RAISE_APPLICATION_ERROR(-20007, 'Comisionul depaseste 50% din valozarae salariului');
END;
/

DROP TRIGGER trig21_dda;
DROP TRIGGER trig22_dda;


--3. a) Introduceti in tabelul info_dept_*** coloana numar care va reprezenta pentru fiecare departament numarul de angajati 
-- care lucreaza in departamentul respectiv. Populati cu date aceasta coloana pe baza informatiilor din schema.
ALTER TABLE info_dept_dda
ADD numar NUMBER(4);

DESC info_dept_dda;
CREATE OR REPLACE PROCEDURE actualizare_info_dept_dda AS
    count_emp NUMBER(4) := 0;
    CURSOR c IS
        SELECT id
        FROM info_dept_dda;
BEGIN
    FOR i IN c LOOP
        SELECT COUNT(*)
        INTO count_emp
        FROM info_emp_dda
        WHERE id_dept = i.id;
        
        UPDATE info_dept_dda
        SET numar = count_emp
        WHERE id = i.id;
        
    END LOOP;
END;
/

SELECT * FROM info_dept_dda;

BEGIN
    actualizare_info_dept_dda();
END;
/

--  b) Definiti un declansator care va actualiza automat aceasta coloana in functie de actualizarile realizate asupra tabelului info_emp_***.
CREATE OR REPLACE TRIGGER trig3_dda
    AFTER INSERT OR DELETE OR UPDATE ON info_emp_dda
    FOR EACH ROW
BEGIN 
    IF INSERTING THEN
        UPDATE info_dept_dda
        SET numar = numar +1
        WHERE id = :NEW.id_dept;
    ELSIF DELETING THEN
        UPDATE INFO_DEPT_DDA
        SET numar = numar -1
        WHERE id = :OLD.id_dept;
    ELSIF UPDATING ('id_dept') THEN
        UPDATE INFO_DEPT_DDA
        SET numar = numar - 1
        WHERE id = :OLD.id_dept;
        
        UPDATE info_dept_dda
        SET numar = numar +1
        WHERE id = :NEW.id_dept;
    END IF;
END;
/
    
SELECT * FROM info_dept_dda;
DESC info_emp_dda;
SELECT * FROM info_emp_dda WHERE id_dept = 100;
DELETE FROM info_emp_dda WHERE id_emp = 108;
SELECT * FROM info_dept_dda;

DROP TRIGGER trig3_dda;


--    4. Definiti un declansator cu ajutorul caruia sa se implementeze restrictia conform careia intr-un departament nu pot lucra 
--  mai mult de 45 persoane (se vor utiliza doar tabelele emp_*** si dept_*** fara a modifica structura acestora).
-- Varianata 1 - Nu merge pentru inserturi multiple
CREATE OR REPLACE TRIGGER trig41_dda 
    BEFORE INSERT ON emp_dda
    FOR EACH ROW
DECLARE
    v_count_emp NUMBER(4) := 0;
BEGIN
    SELECT COUNT(*) INTO v_count_emp
    FROM emp_dda
    WHERE department_id = :NEW.department_id;
    
    IF v_count_emp + 1 > 45 THEN
        RAISE_APPLICATION_ERROR(-20008, 'S-a atins numarul maxim de angajati ce pot lucra in acest departament.');
    END IF;
END;
/

INSERT INTO emp_dda(employee_id,last_name, email, hire_date, job_id, department_id)
VALUES (300, 'Test', 'Test@gmail.com', sysdate, 'SA_MAN', 50);

DROP TRIGGER trig41_dda;


-- Varianta 2 - CORECTA
DESC emp_dda;

CREATE OR REPLACE PACKAGE pachet42dda
AS
    TYPE tip_rec IS RECORD
    ( id emp_dda.department_id%TYPE, num NUMBER(4));
    TYPE tip_t_ind IS TABLE OF tip_rec
        INDEX BY PLS_INTEGER;
    t tip_t_ind;
    contor NUMBER(4) := 0;
END;
/

DROP TRIGGER trig42_dda_comanda;

CREATE OR REPLACE TRIGGER trig42_dda_comanda
BEFORE INSERT OR UPDATE OF department_id ON emp_dda
BEGIN
    pachet42dda.contor := 0; 
    -- pentru fiecare salariat retinem cati angajati lucreaza in departamentul respectiv
    SELECT department_id, COUNT(*)
        BULK COLLECT INTO pachet42dda.t
    FROM emp_dda 
    GROUP BY department_id;
END;
/


CREATE OR REPLACE TRIGGER trig43_dda_linie
BEFORE INSERT OR UPDATE OF department_id ON emp_dda
FOR EACH ROW
BEGIN
    FOR i IN pachet42dda.t.FIRST..pachet42dda.t.LAST LOOP
        IF pachet42dda.t(i).id = :NEW.department_id AND pachet42dda.t(i).num + pachet42dda.contor > 45 THEN
            RAISE_APPLICATION_ERROR(-20005, 'Acest departament are maximul de angajati!');
        END IF;
    END LOOP;
    pachet42dda.contor := pachet42dda.contor + 1;
END;
/

ALTER TABLE emp_dda
DISABLE CONSTRAINT PRIMARY KEY;

SELECT * FROM USER_TRIGGERS;
SELECT * FROM USER_PROCEDURES
WHERE OBJECT_TYPE = 'PACKAGE';

DROP TABLE info_emp_dda;
DROP TABLE info_dept_dda;
DROP VIEW v_info_dda;


-- 5. a) Pe baza informatiilor din schema creati si populati cu date urmatoarele doua tabele:
--       - emp_test_*** (employee_id – cheie primara, last_name, first_name, department_id);
--       - dept_test_*** (department_id – cheie primara, department_name).
CREATE TABLE emp_test_dda AS
    SELECT employee_id, last_name, 
        first_name, department_id
    FROM employees;

ALTER TABLE emp_test_dda
ADD PRIMARY KEY (employee_id);

CREATE TABLE dept_test_dda AS
    SELECT department_id, department_name
    FROM departments;
    
ALTER TABLE dept_test_dda
ADD PRIMARY KEY (department_id);

ALTER TABLE emp_test_dda
ADD FOREIGN KEY (department_id) REFERENCES dept_test_dda(department_id)
ON DELETE SET NULL;

--    b) Definiti un declansator care va determina stergeri si modificari in cascada:
--       - stergerea angajatilor din tabelul emp_test_*** daca este eliminat departamentul acestora din tabelul dept_test_***;
--       - modificarea codului de departament al angajatilor din tabelul emp_test_*** daca departamentul respectiv este 
--    modificat in tabelul dept_test_***. 
CREATE OR REPLACE TRIGGER trig5_dda
    BEFORE DELETE OR UPDATE OF department_id ON dept_test_dda
    FOR EACH ROW
BEGIN
    IF DELETING THEN
        DELETE FROM emp_test_dda
        WHERE department_id = :OLD.department_id;
    ELSIF UPDATING('department_id') THEN
        UPDATE emp_test_dda
        SET department_id = :NEW.department_id
        WHERE department_id = :OLD.department_id;
    END IF;
END;
/

-- modificarea codului unui departament
SELECT * FROM emp_test_dda;

UPDATE dept_test_dda
SET department_id = 290
WHERE department_id = 90;

SELECT * FROM emp_test_dda;

-- stergerea unui departament
-- Pentru constrangere ON DELETE CASCADE nu este necesara crearea unui declansator
ALTER TRIGGER trig5_dda DISABLE;

SELECT * FROM emp_test_dda WHERE department_id = 30;
DELETE FROM dept_test_dda
WHERE department_id = 30;
SELECT * FROM emp_test_dda WHERE department_id = 30;

ROLLBACK;

DROP TRIGGER trig5_dda;
DROP TABLE emp_test_dda;
DROP TABLE dept_test_dda;

-- 6. a) Creati un tabel cu urmatoarele coloane:
--    - user_id (SYS.LOGIN_USER);
--    - nume_bd (SYS.DATABASE_NAME);
--    - erori (DBMS_UTILITY.FORMAT_ERROR_STACK);
--    - data.

CREATE TABLE errors_dda(
    user_id VARCHAR2(32),
    nume_bd VARCHAR2(32),
    erori VARCHAR2(32),
    data DATE
);

--    b) Definiti un declansator sistem(la nivel de baza de date) care sa introduca date in acest tabel referitoare la erorile aparute.
CREATE OR REPLACE TRIGGER trig6_dda
    AFTER DDL ON SCHEMA
BEGIN
    INSERT INTO errors_dda
    VALUES(SYS.LOGIN_USER, SYS.DATABASE_NAME, DBMS_UTILITY.FORMAT_ERROR_STACK, SYSDATE);
END;
/

DROP TRIGGER trig6_dda;
DROP TABLE errors_dda;

-- Informatii despre declansatori se pot obtine:
SELECT *
FROM USER_TRIGGERS;

SELECT *
FROM DBA_TRIGGERS;

SELECT * 
FROM ALL_TRIGGERS;

