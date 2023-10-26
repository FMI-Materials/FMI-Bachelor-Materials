-- Exemple
--1.
<<principal>>
DECLARE
    v_client_id     NUMBER(4) := 1600;
    v_client_nume   VARCHAR2(50) := 'N1';
    v_nou_client_id NUMBER(3) := 500;
BEGIN
    <<secundar>>
    DECLARE
        v_client_id       NUMBER(4) := 0;
        v_client_nume     VARCHAR2(50) := 'N2';
        v_nou_client_id   NUMBER(3) := 300;
        v_nou_client_nume VARCHAR2(50) := 'N3';
    BEGIN
        v_client_id := v_nou_client_id;
        principal.v_client_nume := v_client_nume||' '||v_nou_client_nume;
        --pozitia 1
    END;
    v_client_id := (v_client_id * 12) / 10;
    --pozitia 2
END;

--Determinati:
---valoarea variabilei v_client_id la pozitia 1; 300
---valoarea variabilei v_client_nume la pozitia 1;  N2
---valoarea variabilei v_nou_client_id la pozitia 1; 300
---valoarea variabilei v_nou_client_nume la pozitia 1; N3
---valoarea variabilei v_id_client la pozitia 2; 1920
---valoarea variabilei v_client_nume la pozi?ia 2. N2 N3


--2. Crearti un bloc anonim care sa afiseze propozitia "Invat PL/SQL"pe ecran.
--Varianta 1 - Afisarea folosind variabile de legatura
VARIABLE g_mesaj VARCHAR2(50)
BEGIN
    :g_mesaj := 'Invat PL/SQL';
END;
/
PRINT g_mesaj

--Varianta 2 - Afisarea folosind procedurile din pachetul standard DBMS_OUTPUT
BEGIN
    DBMS_OUTPUT.PUT_LINE('Invat PL/SQL');
END;
/


--3. Definiti un bloc anonim in care sa se afle numele departamentului cu cei mai multi angajati.
--Varianta 1 - cererea intoarce o singura linie(o variabila de acelabi tip ca si coloana departments.department_name)
SET SERVEROUTPUT ON
DECLARE 
    v_dep_name departments.department_name%TYPE;
BEGIN
    SELECT d.department_name
    INTO v_dep_name
    FROM departments d
    JOIN employees e 
        ON d.department_id = e.department_id
    GROUP BY d.department_name
    HAVING COUNT(*) = (SELECT MAX(COUNT(*))
                       FROM employees
                       GROUP BY department_id);
    DBMS_OUTPUT.PUT_LINE('Departamentul '||v_dep_name);
END;
/
SET SERVEROUTPUT OFF

--Varianta 2 - utilizand variabile de legatura(cererea intoarce o singura linie)
VARIABLE dep_name VARCHAR2(124);

BEGIN
    SELECT d.department_name
    INTO :dep_name
    FROM departments d
    JOIN employees e 
        ON d.department_id = e.department_id
    GROUP BY d.department_name
    HAVING COUNT(*) = (SELECT MAX(COUNT(*))
                       FROM employees
                       GROUP BY department_id);
END;
/
PRINT dep_name


--4. Modificati exercitiul anterior astfel incat sa obtineti si numarul de angajati
SET SERVEROUTPUT ON
DECLARE
    v_dep_name departments.department_name%TYPE;
    v_num_emp NUMBER;
BEGIN
    SELECT d.department_name, COUNT(*) 
    INTO v_dep_name, v_num_emp
    FROM departments d
    JOIN employees e 
        ON d.department_id = e.department_id
    GROUP BY d.department_name
    HAVING COUNT(*) = (SELECT MAX(COUNT(*))
                       FROM employees
                       GROUP BY department_id);
    DBMS_OUTPUT.PUT_LINE('Departamentul '||v_dep_name||' are '||v_num_emp);
END;
/
SET SERVEROUTPUT OFF


--5. Determinati salariul anual si bonusul pe care il primeste un salariat al carui cod este dat de la tastatura. 
-- Bonusul este determinat astfel: daca salariul anual este cel putin 200001, atunci bonusul este de 20000; 
-- daca salariul anual este cel putin 100001 si cel mult 200000, aunci bonusul este de 10000, iar
-- daca salariul anual este cel mult 100000, atunci bonusul este 5000. Afisati bonusul obtinut.

--Varianta 1 - utilizand instructiunea IF
SET SERVEROUTPUT ON;
SET VERIFY OFF;
DECLARE
    v_cod_emp       employees.employee_id%TYPE := &p_cod;
    v_salariu_anual NUMBER(7);
    v_bonus         NUMBER(7);
BEGIN
    SELECT salary * 12 INTO v_salariu_anual
    FROM employees
    WHERE employee_id = v_cod_emp;
    IF v_salariu_anual >= 200001
        THEN v_bonus := 20000;
    ELSIF v_salariu_anual BETWEEN 100001 AND 200001
        THEN v_bonus := 10000;
    ELSE v_bonus := 5000;
    END IF;
    DBMS_OUTPUT.PUT_LINE('Angajatul cu codul '||v_cod_emp||' are un bonus de '||v_bonus);
END;
/
SET VERIFY ON

--Varianta 2 - folosind instructiunea CASE
SET SERVEROUTPUT ON
SET VERIFY OFF
DECLARE
    v_cod_emp       employees.employee_id%TYPE := &p_cod;
    v_salariu_anual NUMBER(8);
    v_bonus         NUMBER(5);
BEGIN
    SELECT salary * 12 INTO v_salariu_anual
    FROM employees
    WHERE employee_id = v_cod_emp;
    CASE
        WHEN v_salariu_anual > 200001
            THEN v_bonus := 20000;
        WHEN v_salariu_anual BETWEEN 100001 AND 200001
            THEN v_bonus := 10000;
        WHEN v_salariu_anual < 100000
            THEN v_bonus  := 50000;
    END CASE;
    DBMS_OUTPUT.PUT_LINE('Angajatul '||v_cod_emp||' are un bonus de '||v_bonus);
END;
/
SET VERIFY ON
SET SERVEROUTPUT OFF


--6. Scrieti un blocPL/SQL in care stocati prin variabile de substitutie un cod de angajat, un cod de departament si procentul cu care se mare?te salariul acestuia.  
-- Sa se mute salariatul in noul departament si sa i se creasca salariul in mod corespunzator. Daca modificarea s-a putut realiza
--(exista in tabelul emp_*** un salariat avand codul respectiv)sa se afiseze mesajul “Actualizare realizata”, 
-- iar in caz contrar mesajul “Nu exista un angajat cu acest cod”. Anulati modificarile realizate.
CREATE TABLE emp_dda
AS SELECT * FROM employees;
DESC emp_dda;

SET SERVEROUTPUT ON
DEFINE p_cod_sal = 110
DEFINE p_cod_dep = 80
DEFINE p_procent = 20
DECLARE
    v_cod_ang emp_dda.employee_id%TYPE := &p_cod_sal;
    v_cod_dep emp_dda.department_id%TYPE := &p_cod_dep;
    v_procent NUMBER(4) := &p_procent;
BEGIN
    UPDATE emp_dda
    SET department_id = v_cod_dep,
        salary = salary + (salary * v_procent / 100)
    WHERE employee_id = v_cod_ang;
    IF SQL%ROWCOUNT = 0 THEN 
        DBMS_OUTPUT.PUT_LINE('Nu exista niciun angajat cu acest cod '||v_cod_ang);
        ELSE DBMS_OUTPUT.PUT_LINE('Actualizare realizata');
    END IF;
END;
/
ROLLBACK;   


--7. Creati tabelul zile_***(id, data, nume_zi). Introduceti in tabelul zile_*** informatiile corespunzatoare tuturor zilelor care au ramas din luna curenta.
CREATE TABLE zile_dda(
      id      NUMBER(3),
      data    DATE,
      nume_zi VARCHAR(12)
);
DESC zile_dda;


--Varianta 1 - folosinf instructiunea LOOP
DECLARE
    contor   zile_dda.id%TYPE := 1;
    v_data   zile_dda.data%TYPE;
    maxim    NUMBER(2) := LAST_DAY(SYSDATE) - SYSDATE;
BEGIN
    LOOP
        v_data := sysdate + contor;
        INSERT INTO zile_dda
        VALUES(contor, v_data, TO_CHAR(v_data, 'Day'));
        contor := contor + 1;
        EXIT WHEN contor > maxim;
    END LOOP;
END;
/
SELECT * FROM zile_dda;
TRUNCATE TABLE zile_dda;

--Varianta 2 - folosind instructiunea WHILE
DECLARE
    contor  zile_dda.id%TYPE := 1;
    v_data  zile_dda.data%TYPE := SYSDATE + 1;
    maxim   NUMBER(2) := LAST_DAY(SYSDATE) - SYSDATE;
BEGIN
    WHILE contor <= maxim LOOP
    INSERT INTO zile_dda
    VALUES(contor, v_data, TO_CHAR(v_data, 'Day'));
    v_data := v_data + contor;
    contor := contor + 1;
    END LOOP;    
END;
/
SELECT * FROM zile_dda;
TRUNCATE TABLE zile_dda;

--Varianta 3 - folosind instructiunea FOR
DECLARE
    v_data  zile_dda.data%TYPE;
    maxim   NUMBER(2) := LAST_DAY(SYSDATE) - SYSDATE;
BEGIN
    FOR contor IN 1..maxim LOOP
        v_data := sysdate + contor;
        INSERT INTO zile_dda
        VALUES(contor, v_data, TO_CHAR(v_data, 'Day'));
    END LOOP;
END;
/
SELECT * FROM zile_dda;


--8. Sa se declare si sa se initializeze cu 1 variabila de tip POSITIVE si cu 10 constanta max_loop de tip POSITIVE. Sa se implementeze un ciclu LOOP
-- care incrementeaza pe i pana cand acesta ajunge la o valoare > max_loop, moment in care ciclul LOOP este parasit si se sare la instruc?iunea i:=1.  
SET SERVEROUTPUT ON
DECLARE
    i        POSITIVE := 1;
    max_loop CONSTANT POSITIVE :=10;
BEGIN
    LOOP
        i := i + 1;
        IF i > max_loop THEN
            DBMS_OUTPUT.PUT_LINE('In LOOP i = '||i);
            GOTO urmator;
        END IF;
    END LOOP;
    <<urmator>>
    i := 1;
    DBMS_OUTPUT.PUT_LINE('Out of LOOP i = '||i);
END;
/


--Exercitii
--1. Ce returneaza urmatorul bloc?
DECLARE
    numar number(3) := 100;
    mesaj1 VARCHAR2(255) := 'text 1';
    mesaj2 VARCHAR2(255) := 'text 2';
BEGIN
    DECLARE
        numar number(3) := 1;
        mesaj1 VARCHAR2(255) := 'text 2';
        mesaj2 VARCHAR2(255) := 'text 3';
    BEGIN 
        numar := numar + 1;
        dbms_output.put_line('numar in subcerere este '||numar);
        dbms_output.put_line('mesaj1 in subcerere este '||mesaj1);
        mesaj2 := mesaj2||' adaugat in sub-bloc';
        dbms_output.put_line('mesaj2 in subcerere este '||mesaj2);
    END;
 numar := numar + 1;
 DBMS_OUTPUT.PUT_LINE('numar in blocul principal este: '||numar);
 mesaj1 := mesaj1||' adaugat in blocul principal';
 DBMS_OUTPUT.PUT_LINE('mesaj1 in blocul principal este: '||mesaj1);
 mesaj2 := mesaj2||' adaugat in blocul principal';
 DBMS_OUTPUT.PUT_LINE('mesaj2 in blocul principal este: '||mesaj2);
 END;
 /
 
 --a)Valoarea variabilei numar în subbloc este: 2
 --b)Valoarea variabilei mesaj1 în subbloc este: 'text 2'
 --c)Valoarea variabilei mesaj2 în subbloc este: 'text 3 adaugat in subloc'
 --d)Valoarea variabilei numar în bloc este: 101
 --e)Valoarea variabilei mesaj1 în bloc este: 'text 1 adaugat in blocul principal'
 --f)Valoarea variabilei mesaj2 în bloc este: 'text 2 adaugat in blocul principal'


--2. Se da urmatorul enunt: 
--a)Pentru fiecare zi a lunii octombrie(se vor lua in considerare si zilele din luna in care nu au fost realizate imprumuturi) 
-- obtineti numarul de imprumuturi efectuate. Incercati sa rezolvati problema in SQL fara a folosi structuri ajutatoare.
--b) Definiti tabelul octombrie_*** (id, data).  Folosind  PL/SQL  populati cu date acest tabel. Rezolvati in SQL problema data.
WITH zile_octombrie
    AS(SELECT TO_DATE(TO_DATE('31-OCT-2020') - ROWNUM) AS zi
       FROM DUAL
       CONNECT BY ROWNUM <= 30)
    
SELECT zile_octombrie.zi, NVL(num, 0)
FROM(
    --Cererea furnizeaza doar zilele in care s-au efectuat imprumuturi
    SELECT TO_CHAR(book_date, 'DD') zi_imprumut, COUNT(copy_id) AS num
    FROM rental
    WHERE TO_CHAR(book_date, 'MON') = 'OCT'
    GROUP BY TO_CHAR(book_date, 'DD')) zile_imprumuturi
RIGHT JOIN zile_octombrie 
    ON TO_CHAR(zile_octombrie.zi, 'DD') = zile_imprumuturi.zi_imprumut
ORDER BY 1;


DROP TABLE octombrie_dda;
CREATE TABLE octombrie_dda(
    id    NUMBER(2) PRIMARY KEY,
    data  DATE NOT NULL UNIQUE
);


DECLARE
    zi DATE := '01-OCT-2020';
BEGIN
    FOR i IN 1..31 LOOP
        INSERT INTO octombrie_dda
        VALUES(i, zi);
        zi := zi + 1;
    END LOOP;
END;
/


--3. Definiti un bloc anonim in care sa se determine numarul de filme(titluri) imprumutate de un membru al carui nume este introdus de la tastatura. 
-- Tratati urmatoarele doua situatii: nu exista nici un membru cu numele dat; exista mai multi membrii cu acelasi nume.
SELECT * FROM member;
DESC member;

SET SERVEROUTPUT ON
DECLARE
    v_member_name  member.last_name%TYPE := '&input';
    v_member_id    NUMBER;
    v_no_movies   NUMBER(2);
BEGIN
    SELECT member_id INTO v_member_id
    FROM member m
    WHERE TRIM(BOTH ' ' FROM UPPER(m.last_name)) = TRIM(BOTH ' ' FROM UPPER(v_member_name));
    
    SELECT COUNT(DISTINCT title_id) INTO v_no_movies
    FROM rental r, member m
    WHERE r.member_id = m.member_id
        AND TRIM(BOTH ' ' FROM UPPER(m.last_name)) = TRIM(BOTH ' ' FROM UPPER(v_member_name));
    
    IF v_no_movies = 0 THEN
        DBMS_OUTPUT.PUT_LINE('No movies rented!');
    ELSE DBMS_OUTPUT.PUT_LINE('Rented: '||v_no_movies);
    END IF;
EXCEPTION
    WHEN no_data_found THEN
        DBMS_OUTPUT.PUT_LINE('Nobody with the given name!');
    WHEN too_many_rows THEN
        DBMS_OUTPUT.PUT_LINE('There are many people with the given name!');
    WHEN others THEN
        DBMS_OUTPUT.PUT_LINE('ERROR');
END;
/


--4. Modificati problema anterioara astfel incat sa afisati si urmatorul text:
--   -Categoria 1 (a imprumutat mai mult de 75% din titlurile existente)
--   -Categoria 2 (a imprumutat mai mult de 50% din titlurile existente)
--   -Categoria 3 (a imprumutat mai mult de 25% din titlurile existente)
--   -Categoria 4 (altfel)

SET SERVEROUTPUT ON
DECLARE
    v_member_name  member.last_name%TYPE := '&input';
    v_member_id    NUMBER;
    v_no_movies    NUMBER(2);
    v_no_total     NUMBER(2);
    v_percent      NUMBER;
BEGIN
    SELECT member_id INTO v_member_id
    FROM member m
    WHERE TRIM(BOTH ' ' FROM UPPER(m.last_name)) = TRIM(BOTH ' ' FROM UPPER(v_member_name));
    
    SELECT COUNT(DISTINCT title_id) INTO v_no_movies
    FROM rental r, member m
    WHERE r.member_id = m.member_id
        AND TRIM(BOTH ' ' FROM UPPER(m.last_name)) = TRIM(BOTH ' ' FROM UPPER(v_member_name));
    
    SELECT COUNT(*) INTO v_no_total
    FROM title;
    
    IF v_no_movies = 0 THEN
        DBMS_OUTPUT.PUT_LINE('No movies rented!');
    ELSE DBMS_OUTPUT.PUT_LINE('Rented: '||v_no_movies);
    END IF;
    
    v_percent := v_no_movies / v_no_total;
    CASE
        WHEN v_percent > 0.75 THEN
            DBMS_OUTPUT.PUT_LINE('Caterogy I');
        WHEN v_percent BETWEEN 0.5 AND 0.75 THEN
            DBMS_OUTPUT.PUT_LINE('Caterogy II');
        WHEN v_percent BETWEEN 0.25 AND 0.5 THEN 
            DBMS_OUTPUT.PUT_LINE('Caterogy III');
        ELSE
            DBMS_OUTPUT.PUT_LINE('Caterogy IV');
    END CASE;
EXCEPTION
    WHEN no_data_found THEN
        DBMS_OUTPUT.PUT_LINE('Nobody with the given name!');
    WHEN too_many_rows THEN
        DBMS_OUTPUT.PUT_LINE('There are many people with the given name!');
    WHEN others THEN
        DBMS_OUTPUT.PUT_LINE('ERROR');
END;
/


--5. Creati tabelul member_*** (o  copie  a  tabelului member). Adaugati in acest tabel coloana discount, care va reprezenta procentul de reducere
-- aplicat pentru membrii, in functie de categoria din care fac parte acestia:
-- -10% pentru membrii din Categoria 1 
-- -5% pentru membrii din Categoria II
-- -2-3% pentru membrii din Categoria 3
-- -nimic.
-- Actualizati coloana discount pentru un membru al carui cod este dat de la tastatura. Afisati un mesaj din care sa reiasa daca actualizarea s-a produs sau nu.
DROP TABLE member_dda;

CREATE TABLE member_dda
AS ( SELECT * FROM member);

ALTER TABLE member_dda
ADD discount NUMBER DEFAULT 0;


SET SERVEROUTPUT ON
DECLARE
    v_member_name  member.last_name%TYPE := '&input';
    v_member_id    NUMBER;
    v_no_movies    NUMBER(2);
    v_no_total     NUMBER(2);
    v_percent      NUMBER;
BEGIN
    SELECT member_id INTO v_member_id
    FROM member m
    WHERE TRIM(BOTH ' ' FROM UPPER(m.last_name)) = TRIM(BOTH ' ' FROM UPPER(v_member_name));
    
    SELECT COUNT(DISTINCT title_id) INTO v_no_movies
    FROM rental r, member m
    WHERE r.member_id = m.member_id
        AND TRIM(BOTH ' ' FROM UPPER(m.last_name)) = TRIM(BOTH ' ' FROM UPPER(v_member_name));
    
    SELECT COUNT(*) INTO v_no_total
    FROM title;
    
    IF v_no_movies = 0 THEN
        DBMS_OUTPUT.PUT_LINE('No movies rented!');
    ELSE DBMS_OUTPUT.PUT_LINE('Rented: '||v_no_movies);
    END IF;
    
    v_percent := v_no_movies / v_no_total;
    CASE
        WHEN v_percent > 0.75 THEN
            UPDATE member_dda SET discount = 10 WHERE member_id = v_member_id;
        WHEN v_percent BETWEEN 0.5 AND 0.75 THEN
            UPDATE member_dda SET discount = 5 WHERE member_id = v_member_id;
        WHEN v_percent BETWEEN 0.25 AND 0.5 THEN 
            UPDATE member_dda SET discount = 3 WHERE member_id = v_member_id;        
    END CASE;
    
    IF SQL%ROWCOUNT > 0
        THEN DBMS_OUTPUT.PUT_LINE('Discount updated for member with ID '||v_member_id);
        ELSE DBMS_OUTPUT.PUT_LINE('No update!');
    END IF;
EXCEPTION
    WHEN no_data_found THEN
        DBMS_OUTPUT.PUT_LINE('Nobody with the given name!');
    WHEN too_many_rows THEN
        DBMS_OUTPUT.PUT_LINE('There are many people with the given name!');
    WHEN others THEN
        DBMS_OUTPUT.PUT_LINE('ERROR');
END;
/
