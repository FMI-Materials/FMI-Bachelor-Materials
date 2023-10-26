-- EXEMPLE
-- 1. Definiti un subprogram prin care sa obtineti salariul unui angajat al carui nume este specificat. 
-- Tratati toate exceptiile ce pot fi generate. Apelati subprogramul pentru urmatorii angajati: Bell, King, Kimball. 
-- Rezolvati problema folosind o functie locala.
DESC employees;

SET SERVEROUTPUT ON
DECLARE
    v_name employees.last_name%TYPE := INITCAP('&p_name');
    FUNCTION  f1 RETURN NUMBER IS
        emp_salary employees.salary%TYPE;
    BEGIN
        SELECT salary INTO emp_salary
        FROM employees
        WHERE last_name =  v_name;
        RETURN emp_salary;
    EXCEPTION
        WHEN NO_DATA_FOUND THEN
            DBMS_OUTPUT.PUT_LINE('There are no employees with the name ' || v_name || '!');
        WHEN TOO_MANY_ROWS THEN
            DBMS_OUTPUT.PUT_LINE('There are several employees with the name ' || v_name || '!');
        WHEN OTHERS THEN
            DBMS_OUTPUT.PUT_LINE('Error!');
    END f1;
BEGIN
    DBMS_OUTPUT.PUT_LINE(INITCAP(v_name) || ': ' || f1); 
    
    EXCEPTION WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('Error code = ' || SQLCODE || ' and message = ' || SQLERRM);
END;
/


--2. Rezolvati exercitiul 1 folosind o functie stocata.
CREATE OR REPLACE FUNCTION f2_dda
    (v_name employees.last_name%TYPE DEFAULT 'Bell')
RETURN NUMBER 
IS
    v_salary employees.salary%TYPE;
    BEGIN 
        SELECT salary INTO v_salary
        FROM employees
        WHERE INITCAP(last_name) = INITCAP(v_name);
        RETURN v_salary;
    EXCEPTION
        WHEN NO_DATA_FOUND THEN
            RAISE_APPLICATION_ERROR(-20000, 'There are no employees with the given name!');
        WHEN TOO_MANY_ROWS THEN
            RAISE_APPLICATION_ERROR(-20001, 'There are several employees with the given name!');
        WHEN OTHERS THEN
            RAISE_APPLICATION_ERROR(-20002, 'Error!');
END f2_dda;
/

-- Metode de apelare
-- Bloc PL/SQL
BEGIN
    DBMS_OUTPUT.PUT_LINE('Salary: ' || f2_dda);
END;
/

BEGIN
    DBMS_OUTPUT.PUT_LINE('Salary: ' || f2_dda('King'));
END;
/

-- SQL
SELECT f2_dda FROM dual;
SELECT f2_dda('King') FROM dual;

-- SQL*PLUS
VARIABLE num NUMBER
EXECUTE :num := f2_dda('Hunold');
PRINT num


-- 3. Rezolvati exercitiul 1 folosind o procedura locala.
-- Varianta 1
DECLARE
    v_last_name employees.last_name%TYPE := INITCAP('&p_last_name');
 
    PROCEDURE p3
    IS
        v_salary employees.salary%TYPE;
    BEGIN
        SELECT salary INTO v_salary
        FROM employees
        WHERE INITCAP(last_name) = v_last_name;
        DBMS_OUTPUT.PUT_LINE('Salary: ' || v_salary);
    EXCEPTION
        WHEN NO_DATA_FOUND THEN
            DBMS_OUTPUT.PUT_LINE('There are no employees with the given name!');
        WHEN TOO_MANY_ROWS THEN
            DBMS_OUTPUT.PUT_LINE('Thre are several employees with the given name!');
        WHEN OTHERS THEN
            DBMS_OUTPUT.PUT_LINE('Error!');
    END p3;
    
BEGIN
    p3;
END;
/

--Varianta 2
DECLARE
    v_last_name employees.last_name%TYPE := INITCAP('&p_last_name');
    v_salary employees.salary%TYPE;
    
    PROCEDURE p3(emp_salary OUT employees.salary%TYPE) IS
    BEGIN
        SELECT salary INTO emp_salary
        FROM employees
        WHERE INITCAP(last_name) = v_last_name;
    EXCEPTION
        WHEN NO_DATA_FOUND THEN
            RAISE_APPLICATION_ERROR(-20000, 'There are no employees with the given name!');
        WHEN TOO_MANY_ROWS THEN
            RAISE_APPLICATION_ERROR(-20001, 'There are several employees with the given name!');
        WHEN OTHERS THEN
            RAISE_APPLICATION_ERROR(-20002, 'Error!');
    END p3;
    
BEGIN
    p3(v_salary);
    DBMS_OUTPUT.PUT_LINE('Salary: ' || v_salary);
END;
/


-- 4. Folositi exercitiul 1 folosind o procedura stocata
-- Varianta 1
CREATE OR REPLACE PROCEDURE p4_dda
        (v_last_name employees.last_name%TYPE)
    IS
        emp_salary employees.salary%TYPE;
    BEGIN
        SELECT salary INTO emp_salary
        FROM employees
        WHERE INITCAP(last_name) = v_last_name;
        DBMS_OUTPUT.PUT_LINE('Salary: ' || emp_salary);
        
    EXCEPTION
        WHEN NO_DATA_FOUND THEN
            RAISE_APPLICATION_ERROR(-20000, 'There are no employees with the given name!');
        WHEN TOO_MANY_ROWS THEN
            RAISE_APPLICATION_ERROR(-20001, 'There are several employees with the given name!');
        WHEN OTHERS THEN
            RAISE_APPLICATION_ERROR(-20002, 'Error!');
    END p4_dda;
/

-- Metode de apelare
-- Bloc PL/SQL
BEGIN
    p4_dda('Hunold');
END;
/

-- SQL*PLUS
EXECUTE p4_dda('Hunold')


-- Varianta 2
CREATE OR REPLACE PROCEDURE 
    p4_dda( v_last_name IN employees.last_name%TYPE,
            v_salary OUT employees.salary%TYPE) IS
    BEGIN
        SELECT salary INTO v_salary
        FROM employees
        WHERE INITCAP(last_name) = v_last_name;
    EXCEPTION
        WHEN NO_DATA_FOUND THEN
            RAISE_APPLICATION_ERROR(-20000, 'There are no employees with the given name!');
        WHEN TOO_MANY_ROWS THEN
            RAISE_APPLICATION_ERROR(-20001, 'There are several employees with the given name!');
        WHEN OTHERS THEN
            RAISE_APPLICATION_ERROR(-20002, 'Error!');
    END p4_dda;
/

-- Metode de aplicare
-- Bloc PL/SQL
DECLARE
    v_salary employees.salary%TYPE;
BEGIN
    p4_dda('Hunold', v_salary);
    DBMS_OUTPUT.PUT_LINE('Salary: ' || v_salary);
END;
/

-- SQL*PLUS
VARIABLE v_salary NUMBER
EXECUTE p4_dda('Hunold', :v_salary)
PRINT v_salary


-- 5. Creati o procedura stocata care primeste printr-un parametru codul unui angajat si returneaza prin intermediul 
-- aceluiasi parametru codul managerului corespunzator acelui angajat (parametru de tip IN OUT).
VARIABLE emp_id NUMBER
BEGIN
    :emp_id := 102;
END;
/

CREATE OR REPLACE PROCEDURE p5_dda (num IN OUT NUMBER) IS
BEGIN
    SELECT manager_id INTO num
    FROM employees
    WHERE employee_id = num;
END p5_dda;
/

EXECUTE p5_dda (:emp_id)
PRINT emp_id;


-- 6. Declarati o procedura locala care are parametrii:
--    - rezultat (parametru de tip OUT) de tip last_name din employees;
--    - comision (parametru de tip IN) de tip commission_pct din employees, ini?ializat cu NULL;
--    - cod (parametru de tip IN) de tip employee_id din employees, ini?ializat cu NULL.
-- Daca comisionul nu este NULL atunci in rezultat se va memora numele salariatului care are comisionul respectiv. 
-- In caz contrar, in rezultat se va memora numele salariatului al carui cod are valoarea data in apelarea procedurii.
DECLARE
    v_name employees.last_name%TYPE;
    PROCEDURE p6 (resultp OUT employees.last_name%TYPE,
                  commission IN employees.commission_pct%TYPE := NULL,
                  emp_id IN employees.employee_id%TYPE := NULL)
    IS
    BEGIN
        IF commission IS NOT NULL THEN
            SELECT last_name INTO resultp
            FROM employees
            WHERE commission_pct = commission;
            DBMS_OUTPUT.PUT_LINE('Numele salariatului care are comisionul ' || commission || ' este ' || resultp);
        ELSE
            SELECT last_name INTO resultp
            FROM employees
            WHERE employee_id = emp_id;
            DBMS_OUTPUT.PUT_LINE('Numele salariatului avand codul ' || emp_id || ' este ' || resultp);
        END IF;
    END p6;
BEGIN
    p6(v_name, 0.4);
    p6(v_name, null, 101);
END;
/


-- 7. Definiti doua functii locale cu acelasi nume (overload) care sa calculeze media salariilor astfel:
--    - prima functie va avea ca argument codul departamentului, adica functia calculeaza media salariilor din departamentul specificat;
--    - a doua functie va avea doua argumente, unul reprezentand codul departamentului, iar celalalt reprezentand job-ul, adica
--    functia va calcula media salariilor dintr-un anumit departament si care apartin unui job specificat.
DECLARE
    average1 NUMBER(10,2);
    average2 NUMBER(10,2);
    
    FUNCTION average(v_dep# employees.department_id%TYPE)
    RETURN NUMBER IS resultf NUMBER(10,2);
    BEGIN
        SELECT TRUNC(AVG(salary),2)
        INTO resultf
        FROM employees
        WHERE department_id = v_dep#;
        RETURN resultf;
    END;
    
    FUNCTION average(v_dep# employees.department_id%TYPE,
                     v_job# employees.job_id%TYPE)
    RETURN NUMBER IS resultf NUMBER(10,2);
    BEGIN
        SELECT TRUNC(AVG(salary),2)
        INTO resultf
        FROM employees
        WHERE department_id = v_dep#
            AND job_id = v_job#;
        RETURN resultf;
    END;
BEGIN
    average1 := average(80);
    DBMS_OUTPUT.PUT_LINE('Dep#: 80  ' || 'Average: ' || average1);
    
    average2 := average(80, 'SA_MAN');
    DBMS_OUTPUT.PUT_LINE('Dep#: 80  ' || 'Job# : SA_MAN  ' || 'Average: ' || average2);
END;


--8. Calculati recursiv factorialul unui numar
CREATE OR REPLACE FUNCTION factorial_dda(n NUMBER)
RETURN INTEGER IS
BEGIN
    IF n = 0 THEN RETURN 1;
    ELSE RETURN n * factorial_dda(n-1);
    END IF;
END factorial_dda;
/

SET SERVEROUTPUT ON
DECLARE
    v_result LONG;
BEGIN 
    v_result := factorial_dda(3);
    DBMS_OUTPUT.PUT_LINE(v_result);
END;
/


--9. Afisati numele si salariul angajatilor al caror salariu este mai mare decat media tuturor salariilor. 
-- Media salariilor va fi obtinuta prin apelarea unei functii stocate.
CREATE OR REPLACE FUNCTION avg_salaries_dda 
RETURN NUMBER IS avg_salaries NUMBER;
BEGIN
    SELECT AVG(salary) INTO avg_salaries
    FROM employees;
    RETURN avg_salaries;
END;
/
SELECT first_name||' '||last_name name, salary
FROM employees
WHERE salary > avg_salaries_dda;


-- Informatii despre procedurile si functiile detinute de utilizatorul curent se pot obtine interogand vizualizarea USER_OBJECTS.
SELECT *
FROM USER_OBJECTS
WHERE OBJECT_TYPE IN ('PROCEDURE','FUNCTION');

-- Codul complet al unui subprogram poate fi vizualizat folosind urmatoarea sintaxa:
--SELECT TEXT
--FROM USER_SOURCE
--WHERE NAME = UPPER('nume_subprogram');

 -- Eroarea aparuta la compilarea unui subprogram poate fi vizualizata folosind urmatoarea sintaxa:
--SELECT LINE, POSITION, TEXT
--FROM USER_ERRORS
--WHERE NAME = UPPER('nume');


--EXERCITII
--1. Creati tabelul info_*** cu urmatoarele coloane:
--   - utilizator (numele utilizatorului care a initiat o comanda)
--   - data (data si timpul la care utilizatorul a initiat comanda)
--   - comanda (comanda care a fost initiata de utilizatorul respectiv)
--   - nr_linii (numarul de linii selectate/modificate de comanda)
--   - eroare (un mesaj pentru exceptii).
SELECT user FROM dual;

DROP TABLE info_dda;

CREATE TABLE info_dda(
    utilizator VARCHAR(32),
    data VARCHAR2(64),
    comanda VARCHAR(256),
    nr_linii NUMBER(3),
    eroare VARCHAR(128)  
);

DESCRIBE info_dda;


-- 2.   Modificati functia definita la exercitiul 2, respectiv procedura definita la exerci?iul 4 astfel incat
--   sa determine inserarea in tabelul info_*** a informatiilor corespunzatoare fiecarui caz determinat de valoarea data pentru parametru:
--    - exista un singur angajat cu numele specificat;
--    - exista mai multi angajati cu numele specificat;
--    - nu exista angajati cu numele specificat. 
CREATE OR REPLACE FUNCTION f2_dda
    (v_name employees.last_name%TYPE DEFAULT 'Bell')
RETURN NUMBER IS
    v_salary employees.salary%TYPE;
    BEGIN 
        SELECT salary INTO v_salary
        FROM employees
        WHERE INITCAP(last_name) = INITCAP(v_name);
        RETURN v_salary;
END f2_dda;
/

DECLARE
    v_user VARCHAR(32);
    v_result employees.salary%TYPE;
    v_error_code NUMBER;
    v_error_msg  VARCHAR(100);
BEGIN
    SELECT user INTO v_user
    FROM dual;
    
    v_result := f2_dda('King');
    
    INSERT INTO info_dda VALUES(v_user, TO_CHAR(sysdate, 'DD-MM-YYYY HH:MI:SS'), 'Function f2_dda', 0, 
        'Function executed with no errors and the result is ' || v_result);
    
    EXCEPTION
        WHEN NO_DATA_FOUND THEN
            INSERT INTO info_dda VALUES(
                v_user, TO_CHAR(sysdate, 'DD-MM-YYYY HH:MI:SS'), 'Function f2_dda', 0, 
                'There are no employees with the given name!');
        WHEN TOO_MANY_ROWS THEN
            INSERT INTO info_dda VALUES(
                v_user, TO_CHAR(sysdate, 'DD-MM-YYYY HH:MI:SS'), 'Function f2_dda', 0, 
                'There are several employees with the given name!');
        WHEN OTHERS THEN
            v_error_code := SQLCODE;
            v_error_msg := SUBSTR(SQLERRM, 1, 100);
            INSERT INTO info_dda VALUES(
                v_user, TO_CHAR(sysdate, 'DD-MM-YYYY HH:MI:SS'), 'Function f2_dda', 0, 
                v_error_code || ':' || v_error_msg);
END;
/

SELECT * FROM info_dda FOR UPDATE;
COMMIT;

CREATE OR REPLACE PROCEDURE p4_dda
        (v_last_name employees.last_name%TYPE)
    IS
        emp_salary employees.salary%TYPE;
    BEGIN
        SELECT salary INTO emp_salary
        FROM employees
        WHERE INITCAP(last_name) = v_last_name;
    END p4_dda;
/


DECLARE
    v_user VARCHAR2(32);
    v_error_code NUMBER;
    v_error_message VARCHAR2(100);
BEGIN
    SELECT user INTO v_user FROM dual;
    
    p4_dda('Kimball');
    
        INSERT INTO info_dda VALUES(v_user, TO_CHAR(sysdate, 'DD-MM-YYYY HH:MI:SS'), 'Procedure f2_dda', 0, 
            'Procedure executed with no errors.');
    
    EXCEPTION
        WHEN NO_DATA_FOUND THEN
            INSERT INTO info_dda VALUES(
                v_user, TO_CHAR(sysdate, 'DD-MM-YYYY HH:MI:SS'), 'Procedure f2_dda', 0, 
                'There are no employees with the given name!');
        WHEN TOO_MANY_ROWS THEN
            INSERT INTO info_dda VALUES(
                v_user, TO_CHAR(sysdate, 'DD-MM-YYYY HH:MI:SS'), 'Procedure f2_dda', 0, 
                'There are several employees with the given name!');
        WHEN OTHERS THEN
            v_error_code := SQLCODE;
            v_error_message := SUBSTR(SQLERRM, 1, 100);
            INSERT INTO info_dda VALUES(
                v_user, TO_CHAR(sysdate, 'DD-MM-YYYY HH:MI:SS'), 'Procedure f2_dda', 0, 
                v_error_code || ':' || v_error_message);    
END;
/

SELECT * FROM info_dda FOR UPDATE;
COMMIT;

-- 3. Definiti o functie stocata care determina numarul de angajati care au avut cel putin 2 joburi diferite si care in prezent lucreaza 
-- intr-un oras dat ca parametru. Tratati cazul in care orasul dat ca parametru nu exista, respectiv cazul in care in orasul dat nu 
-- lucreaza niciun angajat. Inserati in tabelul info_*** informatiile corespunzatoare fiecarui caz determinat de valoarea data pentru parametru. 
CREATE OR REPLACE FUNCTION num_employees(v_city locations.city%TYPE)
RETURN NUMBER IS number_employees NUMBER;
BEGIN
    SELECT COUNT(*) INTO number_employees
    FROM (
        SELECT COUNT(*) number_jobs
        FROM(
            SELECT e.employee_id, e.job_id
            FROM employees e
            JOIN departments d ON e.department_id = d.department_id
            JOIN locations l ON d.location_id = l.location_id
            WHERE INITCAP(l.city) LIKE INITCAP(v_city)
            UNION
            SELECT employee_id, job_id
            FROM job_history)
        HAVING COUNT(*) >= 2);
    
    RETURN number_employees;
END;
/


DECLARE
    v_user VARCHAR(32);
    v_error_code NUMBER;
    v_error_message VARCHAR2(100);
    v_city locations.city%TYPE := INITCAP('&p_city');
    v_count_employees NUMBER := 0;
    v_exist_city NUMBER := 0;
    v_result NUMBER := 0;
BEGIN
    SELECT user INTO v_user FROM dual;

    -- Tratarea cazului in care nu exista orasul dat ca parametru
    SELECT 1 INTO v_exist_city
    FROM locations
    WHERE INITCAP(city) = v_city;
    
    IF v_exist_city = 0 THEN
        INSERT INTO info_dda VALUES( v_user, TO_CHAR(sysdate, 'DD-MM-YYYY HH:MI:SS'), 'Function num_employees',
            0, 'There are no cities with the given name.');
    ELSE
        v_result := num_employees(v_city);
        IF v_result = 0 THEN
           INSERT INTO info_dda VALUES( v_user, TO_CHAR(sysdate, 'DD-MM-YYYY HH:MI:SS'), 'Function num_employees',
                0, 'No such employee');
        ELSE
            INSERT INTO info_dda VALUES( v_user, TO_CHAR(sysdate, 'DD-MM-YYYY HH:MI:SS'), 'Function num_employees',
                0, 'Function executed with no errors.');
        END IF;
    END IF;
    
    EXCEPTION
        WHEN NO_DATA_FOUND THEN
            INSERT INTO info_dda VALUES(
                v_user, TO_CHAR(sysdate, 'DD-MM-YYYY HH:MI:SS'), 'Function num_employees', 0, 
                'Nothing found');
        WHEN OTHERS THEN
            v_error_code := SQLCODE;
            v_error_message := SUBSTR(SQLERRM, 1, 100);
            INSERT INTO info_dda VALUES(
                v_user, TO_CHAR(sysdate, 'DD-MM-YYYY HH:MI:SS'), 'Function num_employees', 0, 
                v_error_code || ':' || v_error_message);  
END;
/
    
SELECT * FROM info_dda;


-- 4. Definiti o procedura stocata care mareste cu 10% salariile tuturor angajatilor condusi direct sau indirect de catre 
-- un manager al carui cod este dat ca parametru. Tratati cazul in care nu exista niciun manager cu codul dat. 
-- Inserati in tabelul info_*** informatiile corespunzatoare fiecarui caz determinat de valoarea data pentru parametru.
CREATE OR REPLACE PROCEDURE update_salaries_dda( mng# IN employees.manager_id%TYPE,
                                                 num_rows_updated OUT NUMBER)
AS
    manager_exists NUMBER := 0;
    TYPE TABLE_SUBALTERNS IS  TABLE OF NUMBER;
    subalterns TABLE_SUBALTERNS;
    num_subalterns NUMBER := 0;
BEGIN
    SELECT COUNT(*) 
        INTO manager_exists
    FROM emp_dda
    WHERE employee_id = mng#;
    
    IF manager_exists = 0 THEN
        RAISE_APPLICATION_ERROR(-20001, 'There are no employees with the id ' || mng# || '!');
    END IF;
    
    SELECT employee_id BULK COLLECT INTO subalterns
    FROM emp_dda
    START WITH employee_id = mng#
    CONNECT BY PRIOR employee_id = manager_id;
    
    IF subalterns.COUNT = 0 THEN
        RAISE_APPLICATION_ERROR(-20002, 'The employee ' || mng# || ' has no subordinates!');
    END IF;
    
    num_rows_updated := 0;
    FOR i IN subalterns.FIRST..subalterns.LAST LOOP
        UPDATE emp_dda
        SET salary = 1.10 * salary
        WHERE employee_id = subalterns(i)
            AND employee_id <> mng#;
        num_rows_updated := num_rows_updated + SQL%ROWCOUNT;
    END LOOP;
END update_salaries_dda;
/
    
    
DECLARE
    v_user VARCHAR2(32);
    v_error_code NUMBER;
    v_error_message VARCHAR2(32);
    mng# employees.manager_id%TYPE := '&p_manager_id';
    number_rows_updated NUMBER := 0;
BEGIN
    SELECT user INTO v_user FROM dual;

    update_salaries_dda(mng#, number_rows_updated);
    INSERT INTO info_dda VALUES(v_user, TO_CHAR(sysdate, 'DD-MM-YYYY HH:MI:SS'), 'Procedure update_salaries_dda',
        number_rows_updated, '-');
        
    EXCEPTION
        WHEN VALUE_ERROR THEN
            INSERT INTO info_dda VALUES(v_user, TO_CHAR(sysdate, 'DD-MM-YYYY HH:MI:SS'), 'Procedure update_salaries_dda',
                0, 'An arithmetic, conversion, truncation, or sizeconstraint error occured!');
        WHEN OTHERS THEN
            v_error_code := SQLCODE;
            v_error_message := SUBSTR(SQLERRM, 1, 100);
            INSERT INTO info_dda VALUES(
                v_user, TO_CHAR(sysdate, 'DD-MM-YYYY HH:MI:SS'), 'Procedure update_salaries', 0, 
                v_error_code || ':' || v_error_message);  
END;
/

SELECT * FROM info_dda;
SELECT * FROM emp_dda;


--5.  Definiti un subprogram care obtine pentru fiecare nume de departament ziua din saptamana in care au fost angajate cele mai
--  multe persoane, lista cu numele acestora, vechimea si venitul lor lunar. Afisati mesaje corespunzatoare urmatoarelor cazuri:
--  - intr-un departament nu lucreaza niciun angajat;
--  - intr-o zi a saptamanii nu a fost angajat niciun angajat
--  Observatii:
--  a. Numele departamentului si ziua apar o singura data in rezultat.
--  b. Rezolvati problema in doua variante, dupa cum se tine cont sau nu de istoricul joburilor angajatilor.

-- Varianta 1 - Nu se tine cont de istoricul angajatilor
SET SERVEROUTPUT ON
DECLARE 
    CURSOR c IS
        SELECT department_id, department_name
        FROM departments;
        
    PROCEDURE p6(dep# IN employees.department_id%TYPE) 
    AS
        v_dep_exist NUMBER := 0;
        v_nume VARCHAR2(52);
        v_zi VARCHAR2(12);
        v_vechime VARCHAR2(3);
        v_venit NUMBER(12) := 0;
        TYPE TABLOU_ANGAJATI IS TABLE OF employees.employee_id%TYPE;
        angajati TABLOU_ANGAJATI;
        v_zi_afisata BOOLEAN := FALSE;
    BEGIN
        SELECT COUNT(*) INTO v_dep_exist
        FROM employees
        WHERE department_id = dep#;
        
        IF v_dep_exist = 0 THEN
            DBMS_OUTPUT.PUT_LINE('In acest departemnt nu lucreaza angajati!');
        ELSE
            SELECT employee_id BULK COLLECT INTO angajati
            FROM employees e
            WHERE e.department_id = dep#
                AND TO_CHAR(e.hire_date, 'DAY') IN ( SELECT MAX(TO_CHAR(hire_date, 'DAY'))
                                                    FROM employees
                                                    WHERE department_id = dep#
                                                    GROUP BY TO_CHAR(hire_date, 'DAY')
                                                    HAVING COUNT(employee_id) = ( SELECT MAX(COUNT(employee_id))
                                                                                  FROM employees
                                                                                  WHERE department_id = dep#
                                                                                  GROUP BY TO_CHAR(hire_date, 'DAY')));
            IF angajati.COUNT = 0 THEN
                DBMS_OUTPUT.PUT_LINE('Nu a fost angajat intr-o zi a saptamanii niciun angajat');
            ELSE
                v_zi_afisata := FALSE;
                FOR i IN angajati.FIRST..angajati.LAST LOOP
                    SELECT NVL(first_name, '')||' '||last_name, TO_CHAR(hire_date, 'DAY'),
                        EXTRACT(YEAR FROM sysdate) - EXTRACT(YEAR FROM hire_date),
                        NVL(salary, 0) + NVL(commission_pct, 0) * NVL(salary, 0)
                    INTO v_nume, v_zi, v_vechime, v_venit
                    FROM employees
                    WHERE employee_id = angajati(i);
        
                    IF v_zi_afisata = FALSE THEN
                        DBMS_OUTPUT.PUT_LINE('Ziua din saptamana in care au fost angajati cei mai multi salariati este ' || v_zi);
                        v_zi_afisata := TRUE;
                    END IF;
                
                    DBMS_OUTPUT.PUT_LINE('Angajatul ' || v_nume || ' are o vechime de ' || v_vechime || ' de ani '
                        || ' si un venit de ' || v_venit);
                END LOOP;
            END IF;
        END IF;
    END p6;
    
BEGIN
    FOR i IN c LOOP
        DBMS_OUTPUT.PUT_LINE('---------------------------------------------------------------------------');
        DBMS_OUTPUT.PUT_LINE(i.department_name);
        DBMS_OUTPUT.PUT_LINE('---------------------------------------------------------------------------');
        
        p6(i.department_id);
        DBMS_OUTPUT.NEW_LINE;
    END LOOP;
END;
/


--6. Modificati exercitiul anterior astfel încat lista cu numele angajatilor sa apara intr-un clasament creat in functie de 
-- vechimea acestora in departament. Specificati numarul pozitiei din clasament si apoi lista angajatilor care ocupa acel loc. 
-- Daca doi angajati au aceeasi vechime, atunci acetia ocupa aceeasi pozitie in clasament.

-- Varianta 1 - Nu se tine cont de istoricul angajatilor
SET SERVEROUTPUT ON
DECLARE 
    CURSOR c IS
        SELECT department_id, department_name
        FROM departments;
        
    PROCEDURE p6(dep# IN employees.department_id%TYPE) 
    AS
        v_dep_exist NUMBER := 0;
        v_nume VARCHAR2(52);
        v_zi VARCHAR2(12);
        v_vechime VARCHAR2(3);
        v_venit NUMBER(12) := 0;
        TYPE TABLOU_ANGAJATI IS TABLE OF employees.employee_id%TYPE;
        angajati TABLOU_ANGAJATI;
        v_zi_afisata BOOLEAN := FALSE;
        v_vechime_anterioara VARCHAR2(3) := '0';
        v_count NUMBER := 0;
    BEGIN
        SELECT COUNT(*) INTO v_dep_exist
        FROM employees
        WHERE department_id = dep#;
        
        IF v_dep_exist = 0 THEN
            DBMS_OUTPUT.PUT_LINE('In acest departemnt nu lucreaza angajati!');
        ELSE
            SELECT employee_id BULK COLLECT INTO angajati
            FROM employees e
            WHERE e.department_id = dep#
                AND TO_CHAR(e.hire_date, 'DAY') IN ( SELECT MAX(TO_CHAR(hire_date, 'DAY'))
                                                    FROM employees
                                                    WHERE department_id = dep#
                                                    GROUP BY TO_CHAR(hire_date, 'DAY')
                                                    HAVING COUNT(employee_id) = ( SELECT MAX(COUNT(employee_id))
                                                                                  FROM employees
                                                                                  WHERE department_id = dep#
                                                                                  GROUP BY TO_CHAR(hire_date, 'DAY')));
            IF angajati.COUNT = 0 THEN
                DBMS_OUTPUT.PUT_LINE('Nu a fost angajat intr-o zi a saptamanii niciun angajat');
            ELSE
                FOR i IN angajati.FIRST..angajati.LAST LOOP
                    SELECT NVL(first_name, '')||' '||last_name, TO_CHAR(hire_date, 'DAY'),
                        EXTRACT(YEAR FROM sysdate) - EXTRACT(YEAR FROM hire_date),
                        NVL(salary, 0) + NVL(commission_pct, 0) * NVL(salary, 0)
                    INTO v_nume, v_zi, v_vechime, v_venit
                    FROM employees
                    WHERE employee_id = angajati(i)
                    ORDER BY 3;
        
                    IF v_zi_afisata = FALSE THEN
                        DBMS_OUTPUT.PUT_LINE('Ziua din saptamana in care au fost angajati cei mai multi salariati este ' || v_zi);
                        v_zi_afisata := TRUE;
                    END IF;
                
                    IF v_vechime_anterioara <> v_vechime THEN
                        v_count := v_count + 1;
                        DBMS_OUTPUT.PUT_LINE(v_count || '. Angajatul ' || v_nume || ' are o vechime de ' || v_vechime || ' de ani '
                            || ' si un venit de ' || v_venit);
                    ELSE
                        DBMS_OUTPUT.PUT_LINE('   Angajatul ' || v_nume || ' are o vechime de ' || v_vechime || ' de ani '
                            || ' si un venit de ' || v_venit);
                    END IF;
                    
                    v_vechime_anterioara := v_vechime;
                END LOOP;
            END IF;
        END IF;
    END p6;
    
BEGIN
    FOR i IN c LOOP
        DBMS_OUTPUT.PUT_LINE('---------------------------------------------------------------------------');
        DBMS_OUTPUT.PUT_LINE(i.department_name);
        DBMS_OUTPUT.PUT_LINE('---------------------------------------------------------------------------');
        
        p6(i.department_id);
        DBMS_OUTPUT.NEW_LINE;
    END LOOP;
END;
/
