-- Exemple
--1. Care este rezultatul urmatorului bloc?
DECLARE
    x NUMBER(1) := 5;
    y x%TYPE := NULL;
BEGIN
    IF x <> y THEN DBMS_OUTPUT.PUT_LINE ('valoare <> null este = true');
    ELSE DBMS_OUTPUT.PUT_LINE ('valoare <> null este != true');
    END IF;
    
    x := NULL;
    
    IF x = y
    then dbms_output.put_line('null = null este = true');
    else dbms_output.put_line('null = null este != true');
END IF;
END;
/


-- TIPUL DE DATE RECORD
--2. Definiti tipul inregistrare emp_record care contine campurile employee_id, salary si job_id.
-- Apoi definiti o variabila de acest tip.
--a) Initializati si afisati variabila definita.
SET SERVEROUTPUT ON
DECLARE
    TYPE emp_record IS RECORD
        (cod employees.employee_id%TYPE,
         salariu employees.salary%TYPE,
         job employees.job_id%TYPE);
    v_ang emp_record;
BEGIN
    v_ang.cod := 700;
    v_ang.salariu := 9000;
    v_ang.job := 'SA_MAN';
    DBMS_OUTPUT.PUT_LINE('Angajatul cu codul '||v_ang.cod||' si job_id-ul '||v_ang.job||' are un salariu de '||v_ang.salariu);
END;
/

--b) Initializati variabila cu valorile corespunzatoare angajatului avand codul 101.
DECLARE
    TYPE emp_record IS RECORD
        (cod_angajat employees.employee_id%TYPE,
         salariu employees.salary%TYPE,
         cod_job employees.job_id%TYPE);
    v_ang emp_record;
BEGIN
    SELECT employee_id, salary, job_id
    INTO v_ang
    FROM employees
    WHERE employee_id = 101;
    DBMS_OUTPUT.PUT_LINE('Angajatul cu codul '||v_ang.cod_angajat||' si job_id-ul '||v_ang.cod_job||' are un salariu de '||v_ang.salariu);
END;
/


--c) Stergeti angajatul avand codul 100 din  tabelul emp_*** si retineti in variabila definita anterior informatii corespunzatoare acestui angajat.
DECLARE
    TYPE emp_record IS RECORD
        (cod_angajat employees.employee_id%TYPE,
         salariu employees.salary%TYPE,
         cod_job employees.job_id%TYPE);
    v_ang emp_record;
BEGIN
    DELETE FROM emp_dda
    WHERE employee_id = 100
    RETURNING employee_id, salary, job_id INTO v_ang;
    DBMS_OUTPUT.PUT_LINE('Angajatul cu codul '||v_ang.cod_angajat||' si job_id-ul '||v_ang.cod_job||' are un salariu de '||v_ang.salariu);
END;
/
ROLLBACK;


--3. Declarati doua variabile cu aceeasi structura ca si tabelul emp_***. Stergeti din tabelul emp_*** angajatii 100 ?i 101,
-- mentinand valorile sterse in cele doua variabile definite. Folosind cele doua variabile, introduceti informatiile sterse in tabelul emp_***.
DESC emp_dda;
DECLARE
    v_ang1 employees%ROWTYPE;
    v_ang2 employees%ROWTYPE;
BEGIN
    -- se sterge linia ce contine informatii despre angajatul 100 si se mentine in variabila v_ang1
    DELETE FROM emp_dda
    WHERE employee_id = 100
    RETURNING employee_id, first_name, last_name, email, phone_number, 
        hire_date, job_id, salary, commission_pct, manager_id, department_id INTO v_ang1;
        
    -- se sterge linia ce contine informatii despre angajatul 101 si se mentine in variabila v_ang2  
    DELETE FROM emp_dda
    WHERE employee_id = 101;
        
    -- inseram inapoi informatiile sterse
    INSERT INTO emp_dda
    VALUES v_ang1;
    
    SELECT * INTO v_ang2
    FROM employees
    WHERE employee_id = 101;
    
    --se insereaza o linie oarecare in emp_***
    INSERT INTO emp_dda
    VALUES(701, 'FN', 'LN', 'E', null, sysdate, 'AD_VP', 1000, null, 100, 90);
    
    --se modifica linia adaugata anterior cu valorile variabilei v_ang2
    UPDATE emp_dda
    SET ROW = v_ang2
    WHERE employee_id = 1000;
END;
/


-- TABLOURI INDEXATE
--4. Definiti un tablou indexat de numere. Introduceti in acest tablou primele 10 numere naturale.
--   a. Afisati numarul de elemente al tabloului si elementele acestuia.
--   b. Setati la valoarea null elementele de pe pozitiile impare. Afisati nuarul de elemente al tabloului si elementele acestuia.
--   c. ?tergeti primul element, elementele de pe pozitiile 5, 6 si 7, respectiv ultimul element. Afi?ati valoarea 
--     si indicele primului, respectiv ultimului element. Afi?ati elementele tabloului si num?rul acestora.
--   d. Stergeti toate elementele tabloului.
SET SERVEROUTPUT ON
DECLARE
    TYPE tablou_indexat IS TABLE OF NUMBER INDEX BY PLS_INTEGER;
    t tablou_indexat;
BEGIN
--  punctul a.
    FOR i IN 1..10 LOOP
        t(i) := i;
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('t are '||t.COUNT||' elemente.');
    FOR i IN 1..10 LOOP
        DBMS_OUTPUT.PUT(t(i)||' ');
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
--  punctul b
    FOR i IN 1..10 LOOP
        IF i mod 2 = 1 THEN
            t(i) := NULL;
        END IF;
    END LOOP;
    DBMS_OUTPUT.PUT('Tabloul t are '||t.COUNT||' elemente.');
    FOR i IN 1..10 LOOP
        DBMS_OUTPUT.PUT(NVL(t(i), 0)||' ');
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
--  punctul c.
    t.DELETE(t.FIRST);
    t.DELETE(5,7);
    t.DELETE(t.LAST);
    DBMS_OUTPUT.PUT_LINE('Primul element are indicele ' || t.first ||' si valoarea ' || nvl(t(t.first),0));
    DBMS_OUTPUT.PUT_LINE('Ultimul element are indicele ' || t.last ||' si valoarea ' || nvl(t(t.last),0));
    DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT ||' elemente: ');
    FOR i IN t.FIRST..t.LAST LOOP
        IF t.EXISTS(i) THEN
            DBMS_OUTPUT.PUT(nvl(t(i), 0)|| ' ');
        END IF;
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
--  punctul d
    t.DELETE;
    DBMS_OUTPUT.PUT_LINE('Tabloul are ' || t.COUNT ||' elemente.');
END;
/


--5. Definiti un tablou indexat de inregistrari avand tipul celor din tabelul emp_***. Sterge?i primele doua linii din tabelul emp_***. 
--   Afisati elementele tabloului. Folosind tabelul indexat adaugati inapoi cele doua linii sterse.
DESC emp_dda;
SET SERVEROUTPUT ON
DECLARE
    TYPE tablou_indexat IS TABLE OF emp_dda%ROWTYPE INDEX BY BINARY_INTEGER;
    t tablou_indexat;
BEGIN
    DELETE FROM emp_dda
    WHERE ROWNUM <= 2
    RETURNING employee_id, first_name, last_name, email, phone_number, 
        hire_date, job_id, salary, commission_pct, manager_id, department_id
    BULK COLLECT INTO t;

    DBMS_OUTPUT.PUT_LINE(t(1).employee_id || ' ' || t(1).last_name || ' ' || t(1).first_name);
    DBMS_OUTPUT.PUT_LINE(t(2).employee_id || ' ' || t(2).last_name || ' ' || t(2).first_name);
    
    INSERT INTO emp_dda VALUES t(1);
    INSERT INTO emp_dda VALUES t(2);
END;
/


--6. Rezolvati exercitiul 4 folosind tablouri imbricate
SET SERVEROUTPUT ON
DECLARE
    TYPE tablou_imbricat IS TABLE OF NUMBER;
    t tablou_imbricat := tablou_imbricat();
BEGIN
--  punctul a.
    FOR i IN 1..10 LOOP
        t.extend;
        t(i) := i;
    END LOOP;
    
    DBMS_OUTPUT.PUT_LINE('Tabloul imbricat t are ' || t.COUNT || ' elemenente.');
    FOR i IN 1..10 LOOP
        DBMS_OUTPUT.PUT(t(i) || ' ');
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
--  punctul b.
    FOR i IN 1..10 LOOP
        IF i mod 2 = 1 THEN t(i) := null; END IF;
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('Tabloul t are '|| t.COUNT || ' elemente.');
    FOR i IN 1..10 LOOP
        DBMS_OUTPUT.PUT(NVL(t(i), 0) || ' ');
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
--  punctul c.
    t.DELETE(t.FIRST);
    t.DELETE(5,7);
    t.DELETE(t.LAST);
    DBMS_OUTPUT.PUT_LINE('Primul element are indicele ' || t.FIRST || ' si are valoarea ' || NVL(t(t.FIRST), 0));
    DBMS_OUTPUT.PUT_LINE('Ultimul element are indicele ' || t.LAST || ' si are valoarea ' || NVL(t(t.LAST), 0));
    DBMS_OUTPUT.PUT_LINE('Tabloul t are '|| t.COUNT || ' elemente.');
    FOR i IN t.FIRST..t.LAST LOOP
        IF t.EXISTS(i) THEN
            DBMS_OUTPUT.PUT(NVL(t(i), 0) || ' ');
        END IF;
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
--  punctul d
    t.DELETE;
    DBMS_OUTPUT.PUT_LINE('Tabloul t are ' || t.COUNT || ' elemente.');
END;
/


--7. Declarati un tip tablou imbricat de caractere si o variabila de acest tip. Initializati variabila cu
--  urmatoarele valori: m, i, n, i, m. Afisati continutul tabloului, de la primul la ultimul element si invers. 
--  Stergeti elementele 2 si 4 si apoi afisati continutul tabloului.
SET SERVEROUTPUT ON
DECLARE
    TYPE tablou_imbricat IS TABLE OF CHAR(1);
    t tablou_imbricat := tablou_imbricat('m', 'i', 'n', 'i', 'm');
    i INTEGER;
BEGIN
    DBMS_OUTPUT.PUT_LINE('Tabloul t are ' || t.COUNT || ' elemente.');
    i := t.FIRST;
    WHILE i <= t.LAST LOOP
        DBMS_OUTPUT.PUT(t(i));
        i := t.NEXT(i);
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
    
    i := t.LAST;
    WHILE i >= t.FIRST LOOP
        DBMS_OUTPUT.PUT(t(i));
        i := t.PRIOR(i);
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
    
    t.DELETE(t.NEXT(t.FIRST));
    t.DELETE(4);
    
    DBMS_OUTPUT.PUT_LINE('Tabloul t are ' || t.COUNT || ' elemente.');
    i := t.FIRST;
    WHILE i <= t.LAST LOOP
        DBMS_OUTPUT.PUT(t(i));
        i := t.NEXT(i);
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
END;
/


--8.  Rezolvati exercitiul 4 folosind vectori.
SET SERVEROUTPUT ON
DECLARE
    TYPE vector IS VARRAY(11) OF NUMBER;
    v vector := vector();
    num_elem INTEGER;
BEGIN
--  punctul a.
    FOR i IN 1..10 LOOP
        v.extend;
        v(i) := i;
    END LOOP;
    
    DBMS_OUTPUT.PUT_LINE('Vectorul v are ' || v.COUNT || ' elemente.');
    FOR i IN 1..10 LOOP
        DBMS_OUTPUT.PUT(v(i) || ', ');
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
    
--  punctul b.
    FOR i IN v.FIRST..v.LAST LOOP
        IF i mod 2 = 1 THEN v(i) := NULL; END IF;
    END LOOP;
    
    DBMS_OUTPUT.PUT_LINE('Vectorul v are ' || v.COUNT || ' elemente.');
    FOR i IN v.FIRST..v.LAST LOOP
        DBMS_OUTPUT.PUT(NVL(v(i), 0) || ', ');
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
    
--  punctul c.
--  metodele DELETE(n), DELETE(m,n) nu sunt valabile pentru vectori!!!
--  din vectori nu se pot sterge elemente individuale!!!
    -- stergem primul si ultimul element
    v.TRIM;
    FOR i IN v.FIRST + 1..v.LAST LOOP
        v(i - 1) := v(i);
    END LOOP;
    v.TRIM;
    -- stergem elementele de pe pozitiile 5, 6, 7
    num_elem := 0;
    FOR i IN v.FIRST..v.LAST LOOP
        IF i BETWEEN 5 AND 7 THEN
            num_elem := num_elem + 1;
        END IF;
        v(i - num_elem) := v(i);
    END LOOP;
    v.TRIM(num_elem);    

    DBMS_OUTPUT.PUT_LINE('Vectorul v are ' || v.COUNT || ' elemente.');
    FOR i IN v.FIRST..v.LAST LOOP
        IF v.EXISTS(i) THEN
            DBMS_OUTPUT.PUT(NVL(v(i), 0) || ' ');
        END IF;
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
--  punctul d.
    v.DELETE;
    DBMS_OUTPUT.PUT_LINE('Tabloul are ' || v.COUNT || ' elemente.');
END;
/


--9.  Definiti tipul subordonati_*** (vector, dimensiune maxima 10, mentine numere). Creati tabelul manageri_*** cu urmatoarele campuri: 
--  cod_mgr NUMBER(10), nume VARCHAR2(20), lista subordonati_***. Introduceti 3 linii in tabel. Afisati informatiile din tabel. 
--  Stergeti tabelul creat, apoi tipul.
DROP TABLE manageri_dda;

SET SERVEROUTPUT ON
CREATE OR REPLACE TYPE subordonati_dda AS VARRAY(10) OF NUMBER(4);
/
CREATE TABLE manageri_dda(
    cod_mng NUMBER(10) PRIMARY KEY,
    nume VARCHAR(20),
    lista subordonati_dda
);
DECLARE
    v_sub subordonati_dda := subordonati_dda(100, 200, 300);
    v_info manageri_dda.lista%TYPE;
BEGIN
    INSERT INTO manageri_dda
    VALUES (1, 'Manager1', v_sub);
    
    INSERT INTO manageri_dda
    VALUES (2, 'Manager2', null);
    
    INSERT INTO manageri_dda
    VALUES (3, 'Manager3', subordonati_dda(110, 130));
    
    SELECT lista INTO v_info
    FROM manageri_dda
    WHERE cod_mng = 1;
    
    FOR j IN v_info.FIRST..v_info.LAST loop
        DBMS_OUTPUT.PUT_LINE(v_info(j));
    END LOOP;
END;
/
DROP TABLE manageri_dda;
DROP TYPE subordonati_dda;


--10. Creati tabelul emp_test_*** cu coloanele employee_id si last_name din tabelul employees.
--  Adaugati in acest tabel un nou camp numit telefon de tip tablou imbricat. Acest tablou va mentine pentru fiecare salariat toate numerele de telefon 
--  la care poate fi contactat. Inserati o linie noua in tabel. Actualizati o linie din tabel. Afisati informatiile din tabel. ?tergeti tabelul si tipul.
DESC emp_dda;

CREATE TABLE emp_test_dda AS
    SELECT employee_id, last_name
    FROM emp_dda;
    
CREATE OR REPLACE TYPE tip_telefon_dda IS TABLE OF VARCHAR(13);
/

ALTER TABLE emp_test_dda
ADD (telefon tip_telefon_dda)
NESTED TABLE telefon STORE AS tabel_telefon_dda;

INSERT INTO emp_test_dda
VALUES(505, 'Petrican', tip_telefon_dda('074XXX', '0213XXX', '037XXX'));

UPDATE emp_test_dda
SET telefon = tip_telefon_dda('074XXX', '0213XXX')
WHERE employee_id = 505;

SELECT a.employee_id, b.*
FROM emp_test_dda a, TABLE (a.telefon) b;

DROP TABLE emp_test_dda;
DROP TYPE tip_telefon_dda;


--11. Stergeti din tabelul emp_dda salariatii avand codurile mentinute intr-un vector.
--        Obs. Comanda FORALL permite ca toate liniile unei colectii s? fie transferate simultan printr-o
--        singur? opera?ie. Procedeul este numit bulk bind.
DESC emp_dda;

SET SERVEROUTPUT ON
-- Varianta 1
DECLARE
    TYPE tip_cod IS VARRAY(5) OF NUMBER(6);
    coduri_salariati tip_cod := tip_cod(108, 109, 110);
BEGIN
    FOR i IN coduri_salariati.FIRST..coduri_salariati.LAST LOOP
        DELETE FROM emp_dda
        WHERE employee_id = coduri_salariati(i);
    END LOOP;
END;
/

SELECT employee_id
FROM emp_dda;
ROLLBACK;

-- Varianta 2
SAVEPOINT a;
DECLARE
    TYPE tip_coduri IS VARRAY(5) OF NUMBER(6);
    coduri tip_coduri := tip_coduri(1, 2, 3, 4, 5);
BEGIN
    FORALL i IN coduri.FIRST..coduri.LAST
        DELETE FROM emp_dda
        WHERE employee_id = coduri(i);
END;
/

SELECT employee_id
FROM emp_dda;
ROLLBACK TO a;


-- Exercitii
-- 1. Mentineti intr-o colectie codurile celor mai prost platiti 5 angajati care nu castiga comision. Folosind aceasta
--   colectie mariti cu 5% salariul acestor angajati. Afisati valoarea veche a salariului, respectiv valoarea noua a salariului.
SET SERVEROUTPUT ON
DECLARE
    TYPE emp# IS VARRAY(5) OF NUMBER(6);
    coduri emp# := emp#();
    salariu emp_dda.salary%TYPE;
BEGIN
    SELECT employee_id
    BULK COLLECT INTO coduri
    FROM ( SELECT employee_id, salary
           FROM emp_dda
           WHERE commission_pct IS NULL
           ORDER BY salary)
    WHERE ROWNUM <= 5;
    
    FOR i IN coduri.FIRST..coduri.LAST LOOP
        SELECT salary INTO salariu
        FROM emp_dda
        WHERE employee_id = coduri(i);
        DBMS_OUTPUT.PUT_LINE('Angajatul cu codul ' || coduri(i) || ' avea un salariu de ' || salariu);
        
        UPDATE emp_dda
        SET salary = 1.05 * salariu
        WHERE employee_id = coduri(i);
        
        SELECT salary INTO salariu
        FROM emp_dda
        WHERE employee_id = coduri(i);
        DBMS_OUTPUT.PUT_LINE('In urma maririi de salariu, angajatul cu codul ' || coduri(i) || ' are un salariu de ' || salariu);
    END LOOP;
END;
/
ROLLBACK;


--2. Definiti un tip colectie denumit tip_orase_***. Creati tabelul excursie_*** cu urmatoarea structura:
--  cod_excursie NUMBER(4), denumire VARCHAR2(20), orase tip_orase_*** (ce va contine lista oraselor care se viziteaza intr-o excursie, 
--  intr-o ordine stabilita; de exemplu, primul oras din lista va fi primul oras vizitat), status (disponibila sau anulata).

CREATE OR REPLACE TYPE tip_orase_dda IS TABLE OF VARCHAR(512);
/
CREATE TABLE excursie_dda(
    cod_excursie NUMBER(4) PRIMARY KEY,
    denumire VARCHAR(50) NOT NULL,
    status VARCHAR(15)
);

ALTER TABLE excursie_dda
ADD (orase tip_orase_dda)
NESTED TABLE orase STORE AS table_orase_dda;

--  a. Inserati 5 inregistrari in tabel.
INSERT INTO excursie_dda VALUES(1, 'BUCURESTI-BRASOV', 'Disponibila', TIP_ORASE_DDA('Bucuresti', 'Sinaia', 'Busteni', 'Predeal', 'Brasov'));
INSERT INTO excursie_dda VALUES(2, 'BUCURESTI-SIBIU', 'Disponibila', TIP_ORASE_DDA('Bucuresti', 'Sibiu'));
INSERT INTO excursie_dda VALUES(3, 'BUCURESTI-SIGHISOARA', 'Disponibila', TIP_ORASE_DDA('Bucuresti', 'Sinaia', 'Brasov', 'Sighisoara'));
INSERT INTO excursie_dda VALUES(4, 'TIMISOARA-ORADEA', 'Disponibila', TIP_ORASE_DDA('Timisoara', 'Arad', 'Oradea'));
INSERT INTO excursie_dda VALUES(5, 'SIBIU-TURDA', 'Disponibila', TIP_ORASE_DDA('Sibiu', 'Alba Iulia', 'Turda'));

--  b. Actualizati coloana orase pentru o excursie specificata:
--    - adaugati un oras nou in lista, ce va fi ultimul vizitat in excursia respectiva;
--    - adaugati un oras nou in lista, ce va fi al doilea oras vizitat in excursia respectiva;
--    - inversati ordinea de vizitare a doua dintre orase al caror nume este specificat;
--    - eliminati din lista un oras al carui nume este specificat.
SET SERVEROUTPUT ON
DECLARE
    v_cod_excursie excursie_dda.cod_excursie%TYPE := '&p_id';
    v_oras VARCHAR(20) := '&p_oras';
    v_lista_orase excursie_dda.orase%TYPE;
BEGIN
    SELECT orase INTO v_lista_orase
    FROM excursie_dda
    WHERE cod_excursie = v_cod_excursie;
    
    v_lista_orase.EXTEND;
    v_lista_orase(v_lista_orase.LAST) := v_oras;
    UPDATE excursie_dda
    SET orase = v_lista_orase
    WHERE cod_excursie = v_cod_excursie;
    
    DBMS_OUTPUT.PUT_LINE('In excursia ' || v_cod_excursie|| ' a fost adaugat orasul ' || v_lista_orase(v_lista_orase.LAST));
    
END;
/

DECLARE 
    v_cod_excursie excursie_dda.cod_excursie%TYPE := '&p_cod';
    v_oras_nou VARCHAR(32) := '&p_oras_nou';
    v_lista_orase excursie_dda.orase%TYPE;
BEGIN
    SELECT orase INTO v_lista_orase
    FROM excursie_dda
    WHERE cod_excursie = v_cod_excursie;
    
    v_lista_orase.EXTEND;
    FOR i IN REVERSE 2..v_lista_orase.LAST LOOP
        v_lista_orase(i) := v_lista_orase(i - 1);        
    END LOOP;
    v_lista_orase(2) := v_oras_nou;
    
    UPDATE excursie_dda
    SET orase = v_lista_orase
    WHERE cod_excursie = v_cod_excursie;
    DBMS_OUTPUT.PUT_LINE('Noul traseu al excursiei cu codul ' || v_cod_excursie || ' este: '); 
    FOR i IN v_lista_orase.FIRST..v_lista_orase.LAST LOOP
        DBMS_OUTPUT.PUT(v_lista_orase(i) || ', ');
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
END;
/

DECLARE
    v_cod_excursie excursie_dda.cod_excursie%TYPE := '&p_cod_excursie';
    v_nume_oras1 VARCHAR(32) := '&p_nume_oras1';
    v_nume_oras2 VARCHAR(32) := '&p_nume_oras2';
    v_lista_orase excursie_dda.orase%TYPE;
BEGIN
    SELECT orase INTO v_lista_orase
    FROM excursie_dda
    WHERE cod_excursie = v_cod_excursie;
    
    DBMS_OUTPUT.PUT_LINE('Traseul excursiei cu codul ' || v_cod_excursie || ' inainte de actualizare: '); 
    FOR i IN v_lista_orase.FIRST..v_lista_orase.LAST LOOP
        DBMS_OUTPUT.PUT(v_lista_orase(i) || ', ');
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
    
    FOR i IN v_lista_orase.FIRST..v_lista_orase.LAST LOOP
        IF UPPER(v_lista_orase(i)) LIKE UPPER(v_nume_oras1) THEN v_lista_orase(i) := v_nume_oras2;
        ELSIF UPPER(v_lista_orase(i)) LIKE TRIM(BOTH ' ' FROM UPPER(v_nume_oras2)) THEN v_lista_orase(i) := v_nume_oras1;
        END IF;
    END LOOP;
    
    UPDATE excursie_dda
    SET orase = v_lista_orase
    WHERE cod_excursie = v_cod_excursie;
    
    DBMS_OUTPUT.PUT_LINE('Traseul excursiei cu codul ' || v_cod_excursie || ' dupa actualizare: '); 
    FOR i IN v_lista_orase.FIRST..v_lista_orase.LAST LOOP
        DBMS_OUTPUT.PUT(v_lista_orase(i) || ', ');
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
END;


SET SERVEROUTPUT ON
DECLARE 
    v_cod_excursie excursie_dda.cod_excursie%TYPE := '&p_cod_excursie';
    v_nume_oras VARCHAR(32) := '&p_nume_oras';
    v_lista_orase excursie_dda.orase%TYPE;
    v_pos NUMBER(4);
BEGIN
    SELECT orase INTO v_lista_orase
    FROM excursie_dda
    WHERE cod_excursie = v_cod_excursie;
    
    FOR i IN v_lista_orase.FIRST..v_lista_orase.LAST LOOP
        IF UPPER(v_lista_orase(i)) LIKE TRIM(BOTH ' ' FROM UPPER(v_nume_oras)) THEN v_pos := i;
        END IF;
    END LOOP;
    v_lista_orase.DELETE(v_pos);
    
    UPDATE excursie_dda
    SET orase = v_lista_orase
    WHERE cod_excursie = v_cod_excursie;
END;
/


--  c. Pentru o excursie al carui cod este dat, afisati numarul de orase vizitate, respectiv numele oraselor.
DECLARE
    v_cod_excursie excursie_dda.cod_excursie%TYPE := '&p_cod';
    v_lista_orase excursie_dda.orase%TYPE;
    v_num_orase NUMBER(3) := 0;
BEGIN
    SELECT orase INTO v_lista_orase
    FROM excursie_dda
    WHERE cod_excursie = v_cod_excursie;
    
    DBMS_OUTPUT.PUT_LINE('Orase vizitate: ' || v_lista_orase.COUNT);
    FOR i IN v_lista_orase.FIRST..v_lista_orase.LAST LOOP
      IF v_lista_orase.EXISTS(I) THEN DBMS_OUTPUT.PUT(v_lista_orase(i) || ', ');
      END IF;
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
END;
/

--d. Pentru fiecare excursie afisati lista oraselor vizitate
DECLARE
    v_lista_orase excursie_dda.orase%TYPE;
    CURSOR c_orase IS
        SELECT orase
        FROM excursie_dda;
BEGIN
    OPEN c_orase;
    LOOP
        FETCH c_orase INTO v_lista_orase;
        EXIT WHEN c_orase%NOTFOUND;
        
        FOR i IN v_lista_orase.FIRST..v_lista_orase.LAST LOOP
            IF v_lista_orase.EXISTS(i) THEN 
                IF i = v_lista_orase.LAST THEN
                    DBMS_OUTPUT.PUT(v_lista_orase(i));
                ELSE 
                    DBMS_OUTPUT.PUT(v_lista_orase(i) || ', ');
                END IF;
            END IF;
        END LOOP;
        DBMS_OUTPUT.NEW_LINE;
    END LOOP;
END;
/


-- e. Anulati excursiile cu cele mai putine orase vizitate
DECLARE
    v_index_min excursie_dda.cod_excursie%TYPE;
    v_index_max excursie_dda.cod_excursie%TYPE;
    v_lista_orase excursie_dda.orase%TYPE;
    v_count NUMBER := 0;
BEGIN
    SELECT MIN(cod_excursie)
    INTO v_index_min
    FROM excursie_dda;
    
    SELECT MAX(cod_excursie)
    INTO v_index_max
    FROM excursie_dda;
    
    FOR i IN v_index_min..v_index_max LOOP
        SELECT orase INTO v_lista_orase
        FROM excursie_dda
        WHERE cod_excursie = i;
        
        IF i = v_index_min THEN
            v_count := v_lista_orase.COUNT;
        ELSE 
            IF v_count > v_lista_orase.COUNT THEN
                v_count := v_lista_orase.COUNT;
            END IF;
        END IF;
    END LOOP;
    
    
    FOR i IN v_index_min..v_index_max LOOP
        SELECT orase INTO v_lista_orase
        FROM excursie_dda
        WHERE cod_excursie = i;
        
        IF v_count = v_lista_orase.COUNT THEN
            UPDATE excursie_dda
            SET status = 'anulata'
            WHERE cod_excursie = i;
            
            DBMS_OUTPUT.PUT_LINE('Excursia cu codul ' || i ||' a fost anulata.');
        END IF;
    END LOOP;
END;
/


DROP TABLE excursie_dda;
DROP TYPE tip_orase_dda;


--3. Rezolvati problema anterioara folosind un alt tip de colectie studiat
CREATE OR REPLACE TYPE tip_orase_dda IS VARRAY(10) OF VARCHAR(256);
/
CREATE TABLE excursie_dda(
    cod_excursie NUMBER(4) PRIMARY KEY,
    denumire VARCHAR(50) NOT NULL,
    status VARCHAR(15),
    orase tip_orase_dda
);

-- a.
INSERT INTO excursie_dda VALUES(1, 'BUCURESTI-BRASOV', 'Disponibila', TIP_ORASE_DDA('Bucuresti', 'Sinaia', 'Busteni', 'Predeal', 'Brasov'));
INSERT INTO excursie_dda VALUES(2, 'BUCURESTI-SIBIU', 'Disponibila', TIP_ORASE_DDA('Bucuresti', 'Sibiu'));
INSERT INTO excursie_dda VALUES(3, 'BUCURESTI-SIGHISOARA', 'Disponibila', TIP_ORASE_DDA('Bucuresti', 'Sinaia', 'Brasov', 'Sighisoara'));
INSERT INTO excursie_dda VALUES(4, 'TIMISOARA-ORADEA', 'Disponibila', TIP_ORASE_DDA('Timisoara', 'Arad', 'Oradea'));
INSERT INTO excursie_dda VALUES(5, 'SIBIU-TURDA', 'Disponibila', TIP_ORASE_DDA('Sibiu', 'Alba Iulia', 'Turda'));

--  b. Actualizati coloana orase pentru o excursie specificata:
--    - adaugati un oras nou in lista, ce va fi ultimul vizitat in excursia respectiva;
--    - adaugati un oras nou in lista, ce va fi al doilea oras vizitat in excursia respectiva;
--    - inversati ordinea de vizitare a doua dintre orase al caror nume este specificat;
--    - eliminati din lista un oras al carui nume este specificat.

SET SERVEROUTPUT ON
DECLARE
    v_cod_excursie excursie_dda.cod_excursie%TYPE := '&p_id';
    v_oras VARCHAR(20) := '&p_oras';
    v_lista_orase excursie_dda.orase%TYPE;
BEGIN
    SELECT orase INTO v_lista_orase
    FROM excursie_dda
    WHERE cod_excursie = v_cod_excursie;
    
    v_lista_orase.EXTEND;
    v_lista_orase(v_lista_orase.LAST) := v_oras;
    UPDATE excursie_dda
    SET orase = v_lista_orase
    WHERE cod_excursie = v_cod_excursie;
    
    DBMS_OUTPUT.PUT_LINE('In excursia ' || v_cod_excursie|| ' a fost adaugat orasul ' || v_lista_orase(v_lista_orase.LAST));
    
END;
/

DECLARE 
    v_cod_excursie excursie_dda.cod_excursie%TYPE := '&p_cod';
    v_oras_nou VARCHAR(32) := '&p_oras_nou';
    v_lista_orase excursie_dda.orase%TYPE;
BEGIN
    SELECT orase INTO v_lista_orase
    FROM excursie_dda
    WHERE cod_excursie = v_cod_excursie;
    
    v_lista_orase.EXTEND;
    FOR i IN REVERSE 2..v_lista_orase.LAST LOOP
        v_lista_orase(i) := v_lista_orase(i - 1);        
    END LOOP;
    v_lista_orase(2) := v_oras_nou;
    
    UPDATE excursie_dda
    SET orase = v_lista_orase
    WHERE cod_excursie = v_cod_excursie;
    DBMS_OUTPUT.PUT_LINE('Noul traseu al excursiei cu codul ' || v_cod_excursie || ' este: '); 
    FOR i IN v_lista_orase.FIRST..v_lista_orase.LAST LOOP
        DBMS_OUTPUT.PUT(v_lista_orase(i) || ', ');
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
END;
/

DECLARE
    v_cod_excursie excursie_dda.cod_excursie%TYPE := '&p_cod_excursie';
    v_nume_oras1 VARCHAR(32) := '&p_nume_oras1';
    v_nume_oras2 VARCHAR(32) := '&p_nume_oras2';
    v_lista_orase excursie_dda.orase%TYPE;
BEGIN
    SELECT orase INTO v_lista_orase
    FROM excursie_dda
    WHERE cod_excursie = v_cod_excursie;
    
    DBMS_OUTPUT.PUT_LINE('Traseul excursiei cu codul ' || v_cod_excursie || ' inainte de actualizare: '); 
    FOR i IN v_lista_orase.FIRST..v_lista_orase.LAST LOOP
        DBMS_OUTPUT.PUT(v_lista_orase(i) || ', ');
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
    
    FOR i IN v_lista_orase.FIRST..v_lista_orase.LAST LOOP
        IF UPPER(v_lista_orase(i)) LIKE UPPER(v_nume_oras1) THEN v_lista_orase(i) := v_nume_oras2;
        ELSIF UPPER(v_lista_orase(i)) LIKE TRIM(BOTH ' ' FROM UPPER(v_nume_oras2)) THEN v_lista_orase(i) := v_nume_oras1;
        END IF;
    END LOOP;
    
    UPDATE excursie_dda
    SET orase = v_lista_orase
    WHERE cod_excursie = v_cod_excursie;
    
    DBMS_OUTPUT.PUT_LINE('Traseul excursiei cu codul ' || v_cod_excursie || ' dupa actualizare: '); 
    FOR i IN v_lista_orase.FIRST..v_lista_orase.LAST LOOP
        DBMS_OUTPUT.PUT(v_lista_orase(i) || ', ');
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
END;


DECLARE 
    v_cod_excursie excursie_dda.cod_excursie%TYPE := '&p_cod_excursie';
    v_nume_oras VARCHAR(32) := '&p_nume_oras';
    v_lista_orase excursie_dda.orase%TYPE;
    v_num NUMBER(4);
BEGIN
    SELECT orase INTO v_lista_orase
    FROM excursie_dda
    WHERE cod_excursie = v_cod_excursie;
    
    v_num := 0;
    FOR i IN v_lista_orase.FIRST..v_lista_orase.LAST LOOP
        v_lista_orase(i - v_num) := v_lista_orase(i);
        IF UPPER(v_lista_orase(i)) LIKE TRIM(BOTH ' ' FROM UPPER(v_nume_oras)) THEN v_num := v_num +1;
        END IF;
    END LOOP;
    v_lista_orase.TRIM(v_num);
    
    UPDATE excursie_dda
    SET orase = v_lista_orase
    WHERE cod_excursie = v_cod_excursie;
END;
/

-- c. Pentru o excursie al carui cod este dat, afisati numarul de orase vizitate, respectiv numele oraselor.
DECLARE
    v_cod_excursie excursie_dda.cod_excursie%TYPE := '&p_cod';
    v_lista_orase excursie_dda.orase%TYPE;
    v_num_orase NUMBER(3) := 0;
BEGIN
    SELECT orase INTO v_lista_orase
    FROM excursie_dda
    WHERE cod_excursie = v_cod_excursie;
    
    DBMS_OUTPUT.PUT_LINE('Traseu: ');
    FOR i IN v_lista_orase.FIRST..v_lista_orase.LAST LOOP
      IF v_lista_orase.EXISTS(I) THEN 
        DBMS_OUTPUT.PUT(v_lista_orase(i) || ' ');
        v_num_orase := v_num_orase + 1;
      END IF;
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
    DBMS_OUTPUT.PUT_LINE('Numar orase vizitate: ' || v_num_orase);
    
END;
/


--d. Pentru fiecare excursie afisati lista oraselor vizitate
DECLARE
    v_index_min excursie_dda.cod_excursie%TYPE;
    v_index_max excursie_dda.cod_excursie%TYPE;
    v_lista_orase excursie_dda.orase%TYPE;
BEGIN
    SELECT MIN(cod_excursie)
    INTO v_index_min
    FROM excursie_dda;
    
    SELECT MAX(cod_excursie)
    INTO v_index_max
    FROM excursie_dda;
    
    FOR i IN v_index_min..v_index_max LOOP
        SELECT orase INTO v_lista_orase
        FROM excursie_dda
        WHERE cod_excursie = i;
        
        DBMS_OUTPUT.NEW_LINE;    
        DBMS_OUTPUT.PUT_LINE('Excursia cu codul ' || i ||': ');
        FOR i IN v_lista_orase.FIRST..v_lista_orase.LAST LOOP
            IF v_lista_orase.EXISTS(I) THEN 
                IF i = v_lista_orase.LAST THEN
                    DBMS_OUTPUT.PUT(v_lista_orase(i));
                ELSE 
                    DBMS_OUTPUT.PUT(v_lista_orase(i) || ', ');
                END IF;
            END IF;
        END LOOP;
        DBMS_OUTPUT.NEW_LINE;
    END LOOP;
    
END;
/


-- e. Anulati excursiile cu cele mai putine orase vizitate
DECLARE
    v_index_min excursie_dda.cod_excursie%TYPE;
    v_index_max excursie_dda.cod_excursie%TYPE;
    v_lista_orase excursie_dda.orase%TYPE;
    v_count NUMBER := 0;
BEGIN
    SELECT MIN(cod_excursie)
    INTO v_index_min
    FROM excursie_dda;
    
    SELECT MAX(cod_excursie)
    INTO v_index_max
    FROM excursie_dda;
    
    FOR i IN v_index_min..v_index_max LOOP
        SELECT orase INTO v_lista_orase
        FROM excursie_dda
        WHERE cod_excursie = i;
        
        IF i = v_index_min THEN
            v_count := v_lista_orase.COUNT;
        ELSE 
            IF v_count > v_lista_orase.COUNT THEN
                v_count := v_lista_orase.COUNT;
            END IF;
        END IF;
    END LOOP;
    
    
    FOR i IN v_index_min..v_index_max LOOP
        SELECT orase INTO v_lista_orase
        FROM excursie_dda
        WHERE cod_excursie = i;
        
        IF v_count = v_lista_orase.COUNT THEN
            UPDATE excursie_dda
            SET status = 'anulata'
            WHERE cod_excursie = i;
            
            DBMS_OUTPUT.PUT_LINE('Excursia cu codul ' || i ||' a fost anulata.');
        END IF;
    END LOOP;
END;
/


DROP TABLE excursie_dda;
DROP TYPE tip_orase_dda;