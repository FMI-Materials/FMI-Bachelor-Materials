-- EXEMPLE
-- 1. Remediati pe rand exceptiile din urmatorul exemplu:
SET SERVEROUTPUT ON
DECLARE
    v NUMBER;
    CURSOR c IS
        SELECT employee_id FROM employees;
BEGIN
-- exception: NO DATA FOUND
    SELECT employee_id INTO v
    FROM employees
    WHERE 1 = 0;
    
-- exception: TOO MANY ROWS
    SELECT employee_id INTO v
    FROM employees;
    
-- exception: INVALID NUMBER
    SELECT employee_id
    INTO v
    FROM employees
    WHERE 2='s';
    
    OPEN c;
-- exception: cursor is already open
    OPEN c;
-- when others
    v := 'sql';
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE(SQLCODE || ' - ' || UPPER(SQLERRM));
    WHEN TOO_MANY_ROWS THEN
        DBMS_OUTPUT.PUT_LINE(SQLCODE || ' - ' || UPPER(SQLERRM));
        DBMS_OUTPUT.PUT_LINE('Try use BULK COLLECT INTO');
    WHEN INVALID_NUMBER THEN
        DBMS_OUTPUT.PUT_LINE(SQLCODE || ' - ' || UPPER(SQLERRM));
    WHEN CURSOR_ALREADY_OPEN THEN
        DBMS_OUTPUT.PUT_LINE(SQLCODE || ' - ' || UPPER(SQLERRM));
        CLOSE c;
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE(SQLCODE || ' - ' || UPPER(SQLERRM));
END;
/

-- 2. Sa se creeze tabelul error_dda care va contine doua campuri: cod de tip NUMBER si mesaj de tip VARCHAR(100).
-- Sa se creeze un bloc PL/SQL care sa permita gestiunea erorii "divide by 0" in doua moduri: prin definirea unei exceptii de 
-- catre utilizator si prin captarea erorii interne a sistemului. Codul si mesajul eroii vor fi introduse in tabelul error_dda.
CREATE TABLE error_dda (
    cod NUMBER,
    mesaj VARCHAR(100)
);

-- Varianta 1 - exceptie ddefinita de catre utilizator
DECLARE
    v_cod NUMBER;
    v_mesaj VARCHAR(100);
    x NUMBER;
    my_exception EXCEPTION;
BEGIN
    x := 1;
    IF x = 1 THEN RAISE my_exception;
    ELSE 
        x := x / (x - 1);
    END IF;
EXCEPTION
    WHEN my_exception THEN
        v_cod := -20001;
        v_mesaj := 'x=1 determina o impartire la 0';
        INSERT INTO error_dda
        VALUES(v_cod, v_mesaj);
END;
/

SELECT * FROM error_dda;

-- Varianta 2 - captarea erorii interne a sistemului
DECLARE
    v_cod   NUMBER;
    v_mesaj VARCHAR2(100);
    x       NUMBER := 1;
BEGIN
    x := x / (x - 1);
EXCEPTION
    WHEN ZERO_DIVIDE THEN
        v_cod := SQLCODE;
        v_mesaj := SUBSTR(SQLERRM,1,100);
        INSERT INTO error_dda
        VALUES(v_cod,v_mesaj);
END;
/

SELECT * FROM error_dda;


-- 3. Sa se creeze un bloc PL/SQL prin care sa se afiseze numele departamentului care functioneaza intr-o anumita locatie.
-- Daca interogarea nu intoarce nicio linie, atunci sa se trateze exceptia si sa se insereze in tabelul error_dda codul erorii 
-- -20002 cu mesajul "nu exista departamente in locatia data". Daca interogarea intoarce o singura linie, atunci sa se afiseze
-- numle departamentului. Daca interogarea intoarce mai multe linii, atunci sa se introduca in tabelul error_dda codul erorii 
-- -20003 cu mesajul "exista mai multe departamente in locatia data". Testati pentru urmatoarele locatii: 1400, 1700, 3000.

SET VERIFY OFF
ACCEPT p_location PROMPT 'Introduceti locatia: '

SET SERVEROUTPUT ON
DECLARE
    v_location departments.location_id%TYPE := &p_location;
    v_dep_name departments.department_name%TYPE;
BEGIN
    SELECT department_name INTO v_dep_name
    FROM departments
    WHERE location_id = v_location;
    
    DBMS_OUTPUT.PUT_LINE('Nume departament: ' || v_dep_name);
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        INSERT INTO error_dda
        VALUES(-20002, 'nu exista departamente in locatia data');
    WHEN TOO_MANY_ROWS THEN
        INSERT INTO error_dda
        VALUES(-20003, 'exista mai multe departamente in locatia data');
END;
/

SELECT * FROM error_dda;


-- 4. Sa se adauge constrangerea de cheie primara pentru campul department_id din tabelul dep_dda si
-- constrangerea de cheie externa pentru campul department_id din tabelul emp_dda care refera campul
-- cu acelasi nume din tabelul dep_dda. Sa se creeze un bloc PL/SQL care trateaza exceptia aparuta in 
-- cazul in care se sterge un departament in care lucreaza angajati (exceptie interna nepredefinita.
SELECT * FROM user_constraints WHERE table_name = UPPER('dep_dda');
SELECT * FROM user_constraints WHERE table_name = UPPER('emp_dda');

ALTER TABLE emp_dda
ADD CONSTRAINT c_ex_dda FOREIGN KEY (department_id)
    REFERENCES dep_dda;

DELETE FROM dep_dda
WHERE department_id = 10; -- apare eroarea ORA-02292

SET VERIFY OFF
SET SERVEROUTPUT ON
ACCEPT p_cod_dep PROMPT 'Introduceti un cod de departament '
DECLARE
    exceptie EXCEPTION;
    PRAGMA EXCEPTION_INIT(exceptie,-02292);
    -- exceptia nu are un nume predefinit, cu PRAGMA EXCEPTION_INIT asociez erorii avand codul -02292 un nume
BEGIN
    DELETE FROM dep_dda
    WHERE department_id = &p_cod_dep;
EXCEPTION
    WHEN exceptie THEN
        DBMS_OUTPUT.PUT_LINE('Nu puteti sterge un departament in care lucreaza salariati!');
END;
/


-- 5. Sa se creeze un bloc PL/SQL prin care se afiseaza numarul de salariati care au venitul anual mai mare decat valoarea data.
-- Sa se trateze cazul in care niciun salariat nu indeplineste aceasta conditie (exceptii externe).
SET SERVEROUTPUT ON
SET VERIFY OFF
ACCEPT p_val PROMPT 'Introduceti valoarea'
DECLARE
    v_val        NUMBER := &p_val;
    count_emp    NUMBER(4);
    my_exception EXCEPTION;
BEGIN
    SELECT COUNT(*) INTO count_emp
    FROM employees
    WHERE (salary + NVL(commission_pct,0) * salary) * 12 > v_val;
    
    IF count_emp = 0 THEN
        RAISE my_exception;
    END IF;
EXCEPTION
    WHEN my_exception THEN
        DBMS_OUTPUT.PUT_LINE('Nu exista angajati pentru care sa se indeplineasca aceasta conditie!');
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE(SQLCODE || ' - ' || SQLERRM);
END;
/


-- 6. Sa se mareasca cu 1000 sala  riul unui angajat al carui cod este dat de la tastatura. Sa se trateze cazul in care
-- nu exista angajatul al carui cod este specificat. Tratarea exceptiei se va face in sectiunea executabila.
SET VERIFY OFF
ACCEPT p_cod PROMPT 'Introduceti codul:'
DECLARE
    v_cod emp_dda.employee_id%TYPE := &p_cod;
BEGIN
    UPDATE emp_dda
    SET salary =  salary + 1000
    WHERE employee_id = v_cod;
    
    IF SQL%NOTFOUND THEN
        RAISE_APPLICATION_ERROR(-20999, 'Nu exista niciun angajat cu codul ' || v_cod);
    END IF;
END;
/
SET VERIFY ON


-- 7. Sa se afiseze numele si salariul unui angajat al carui cod este dat de la tastatura. Sa se trateze cazul in care nu exista
-- angajatul al carui cod este specificat. Tratarea exceptiei se va face in sectiunea de tratare a erorilor.
SET VERIFY OFF
ACCEPT p_cod_emp PROMPT 'Introduceti codul angajatului:'
SET SERVEROUTPUT ON
DECLARE
    v_cod_emp  NUMBER := &p_cod;
    v_nume_emp emp_dda.last_name%TYPE;
    v_salariu  emp_dda.salary%TYPE;
BEGIN
    SELECT last_name, salary
    INTO v_nume_emp, v_salariu
    FROM emp_dda
    WHERE employee_id = v_cod_emp;
    DBMS_OUTPUT.PUT_LINE(v_nume_emp || ' are un salariu lunar in valoare de ' || v_salariu);
EXCEPTION 
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('Nu exista angajatul cu codul ' || v_cod_emp);
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE(SQLCODE || ' - ' || SQLERRM);
END;
/
SET VERIFY ON


-- 8. Sa se creeze un bloc PL/SQL care foloseste 3 comenzi SELECT. Una dintre aceste comenzi nu va intoarce nicio linie. 
-- Sa se determine care dintre cele trei comenzi SELECT determina aparitia exceptiei NO_DATA_FOUND.

-- Varianta 1
SET SERVEROUTPUT ON
DECLARE
     v_localizare NUMBER(1):=1;
     v_nume emp_dda.last_name%TYPE;
     v_sal emp_dda.salary%TYPE;
     v_job emp_dda.job_id%TYPE;
BEGIN
    v_localizare:=1;
    SELECT last_name
    INTO v_nume
    FROM emp_dda
    WHERE employee_id=200;
    DBMS_OUTPUT.PUT_LINE(v_nume);

    v_localizare:=2;
    SELECT salary
    INTO v_sal
    FROM emp_dda
    WHERE employee_id=455;
    DBMS_OUTPUT.PUT_LINE(v_sal);

    v_localizare:=3;
    SELECT job_id
    INTO v_job
    FROM emp_dda
    WHERE employee_id=200;
    DBMS_OUTPUT.PUT_LINE(v_job);
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('comanda SELECT ' || v_localizare || ' nu returneaza nimic');
END;
/
SET SERVEROUTPUT OFF

-- Varianta 2
SET SERVEROUTPUT ON
DECLARE
     v_nume emp_dda.last_name%TYPE;
     v_sal emp_dda.salary%TYPE;
     v_job emp_dda.job_id%TYPE;
BEGIN
    BEGIN
        SELECT last_name
        INTO v_nume
        FROM emp_dda
        WHERE employee_id=200;
        DBMS_OUTPUT.PUT_LINE(v_nume);
    EXCEPTION
        WHEN NO_DATA_FOUND THEN
            DBMS_OUTPUT.PUT_LINE('comanda SELECT1 nu returneaza nimic');
    END;
    
    BEGIN
        SELECT salary
        INTO v_sal
        FROM emp_dda
        WHERE employee_id=455;
        DBMS_OUTPUT.PUT_LINE('v_sal');
    EXCEPTION
        WHEN NO_DATA_FOUND THEN
            DBMS_OUTPUT.PUT_LINE('comanda SELECT2 nu returneaza nimic');
    END;
 
    BEGIN
        SELECT job_id
        INTO v_job
        FROM emp_dda
        WHERE employee_id=200;
        DBMS_OUTPUT.PUT_LINE(v_job);
    EXCEPTION
        WHEN NO_DATA_FOUND THEN
            DBMS_OUTPUT.PUT_LINE('comanda SELECT3 nu returneaza nimic');
    END;
END;
/
SET SERVEROUTPUT OFF


-- 9. Dati un exemplu prin care sa se arate ca nu este permis saltul de la sectiunea de tratare a unei exceptii, in blocul curent.
DECLARE
    v_comm NUMBER(4);
BEGIN
    SELECT ROUND(salary * NVL(commission_pct,0))
    INTO v_comm
    FROM emp_dda
    WHERE employee_id = 455;
    <<eticheta>>
    UPDATE emp_dda
    SET salary = salary + v_comm
    WHERE employee_id = 200;
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        v_comm := 500;
        GOTO eticheta;
END;
/

-- 10. Dati un exemplu prin care sa se arate ca nu este permis saltul la sectiunea de tratare a unei exceptii.
SET SERVEROUTPUT ON
DECLARE
    v_comm_val NUMBER(4);
    v_comm     emp_dda.commission_pct%TYPE;
BEGIN
    SELECT NVL(commission_pct,0),
        ROUND(salary*NVL(commision_pct,0))
    INTO v_comm, v_comm_val
    FROM emp_dda
    WHERE employee_id = 200;
    
    IF v_comm = 0 THEN
        GOTO eticheta;
    ELSE
        UPDATE emp_dda
        SET salary = salary + v_comm_val
        WHERE employee_id = 200;
    END IF;
    
<<eticheta>>
    --DBMS_OUTPUT.PUT_LINE('Este ok!');
EXCEPTION
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('Is an exception!');
END;
/


-- EXERCITII
-- 1. Sa se creeze un bloc PL/SQL care afiseaza radicalul unei variabile introduse de la tastatura. Sa se trateze cazul in care 
-- valoarea variabilei este negativa. Gestiunea erorii se va realiza prin definirea unei exceptii de cate utilizator, respectiv 
-- prin captarea erorii interne a sistemului. Codul si mesajul erorii vor fi introduse in tabel error_dda.
SET VERIFY OFF
ACCEPT p_variable PROMPT ' n = '
SET SERVEROUTPUT ON
DECLARE
    v_variable   NUMBER := &p_variable;
    v_result     FLOAT;
    my_exception EXCEPTION;
BEGIN
    IF v_variable < 0 THEN RAISE my_exception;
    ELSE
        v_result := SQRT(v_variable);
    END IF;
    DBMS_OUTPUT.PUT_LINE('SQRT(' || v_variable || ') = ' || v_result);
EXCEPTION
    WHEN my_exception THEN
        DBMS_OUTPUT.PUT_LINE('Must be a positive number!');
END;
/
SET VERIFY ON


-- 2.  Sa se creeze un bloc PL/SQL prin care sa se afiseze numele salariatului (din tabelul emp_***) care castiga un anumit 
-- salariu. Valoarea salariului se introduce de la tastatura. Se va testa programul pentru urmatoarele valori: 500, 3000 si 5000.
-- Daca interogarea nu intoarce nicio linie, atunci sa se trateze exceptia si sa se afiseze mesajul “nu exista salariati care 
-- sa castige acest salariu ”. Daca interogarea intoarce o singura linie, atunci sa se afiseze numele salariatului. 
-- Daca interogarea intoarce mai multe linii, atunci sa se afiseze mesajul “exista mai multi salariati care castiga acest salariu”.
SET SERVEROUTPUT ON
SET VERIFY OFF
ACCEPT p_salary PROMPT 'Introduceti salariul:'
DECLARE
    v_salary    emp_dda.salary%TYPE := &p_salary;
    v_last_name emp_dda.last_name%TYPE;
BEGIN
    SELECT last_name INTO v_last_name
    FROM employees
    WHERE salary = v_salary;
    DBMS_OUTPUT.PUT_LINE('Nume: ' || v_last_name);
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('Nu exista salariati care sa castige acest salariu');
    WHEN TOO_MANY_ROWS THEN
        DBMS_OUTPUT.PUT_LINE('Exista mai multi salariati care castiga acest salariu');
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE(SQLCODE || ' - ' || SQLERRM);
END;
/
SET VERIFY ON


-- 3. Sa se creeze un bloc PL/SQL care trateaza eroarea aparuta in cazul in care se modifica 
-- codul unui departament in care lucreaza angajati.
SET SERVEROUTPUT ON
DECLARE
    exceptie EXCEPTION;
    PRAGMA EXCEPTION_INIT(exceptie,-02292);
BEGIN
    UPDATE dep_dda
    SET department_id = 1000
    WHERE department_id = 10;
EXCEPTION
    WHEN exceptie THEN
        DBMS_OUTPUT.PUT_LINE('Nu puteti modifica codul unui departament in care lucreaza salariati');
END;
/


--4. Sa se creeze un bloc PL/SQL prin care sa se afiseze numele departamentului 10 daca numarul sau de angajati este 
-- intr-un interval dat de la tastatura. Sa se trateze cazul in care departamentul nu indeplineste aceasta conditie.
SET SERVEROUTPUT ON
ACCEPT p_lim_inf PROMPT 'Introduceti limita inferioara:'
ACCEPT p_lim_sup PROMPT 'Introduceti limita superioara:'
DECLARE
    v_lim_inf     NUMBER := &p_lim_inf;
    v_lim_sup     NUMBER := &p_lim_sup;
    v_count_emp   NUMBER;
    v_name_dep    dep_dda.department_name%TYPE;
    my_exception  EXCEPTION;
    my_exception2 EXCEPTION;
BEGIN
    IF v_lim_inf > v_lim_sup THEN RAISE my_exception;
    END IF;
    
    SELECT COUNT(*), MAX(d.department_name)
    INTO v_count_emp, v_name_dep
    FROM employees e
    INNER JOIN departments d 
        ON e.department_id = d.department_id
    WHERE d.department_id = 10;

    IF v_count_emp >= v_lim_inf AND v_count_emp <= v_lim_sup THEN
        IF v_count_emp = 1 THEN
          DBMS_OUTPUT.PUT_LINE('Nume departament: ' || v_name_dep || ' are un angajat');
        ELSE
            DBMS_OUTPUT.PUT_LINE('Nume departament: ' || v_name_dep || ' are ' || v_count_emp || ' angajati');
        END IF;
    ELSE
        RAISE my_exception2;
    END IF;
EXCEPTION
    WHEN my_exception THEN
        DBMS_OUTPUT.PUT_LINE('Limita inferioara trebuie sa fie mai mica decat limita superioara');
    WHEN my_exception2 THEN
        DBMS_OUTPUT.PUT_LINE('Departamentul nu indeplineste conditia specificata');
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE(SQLCODE || ' - ' || SQLERRM);
END;
/


-- 5. Sa se modifice numele unui departament al carui cod este dat de la tastatura. Sa se trateze cazul in care nu exista
-- acel departament. Tratarea exceptiei se va face in sectiunea executabila.
ACCEPT p_cod_dep PROMPT 'Introduceti codul departamentului:'
SET SERVEROUTPUT ON
DECLARE 
    v_cod_dep  dep_dda.department_id%TYPE := &p_cod_dep;
    exceptie   EXCEPTION;
BEGIN
    UPDATE dep_dda
    SET department_name = SUBSTR(department_name,1,3)
    WHERE department_id = v_cod_dep;
    IF SQL%NOTFOUND THEN RAISE exceptie;
    END IF;
EXCEPTION
    WHEN exceptie THEN
        DBMS_OUTPUT.PUT_LINE('Nu exista departamentul cu codul ' || v_cod_dep);
END;
/

ROLLBACK;


-- 6. Sa se creeze un bloc PL/SQL care afiseaza numele departamentului ce se afla intr-o anumita locatie si
-- numele departamentului ce are un anumit cod (se vor folosi doua comenzi SELECT). Sa se trteze exceptia
-- NO_DATA_FOUND si sa se afiseze care dintre comenzi a determinat eroarea.
SET SERVEROUTPUT ON
-- Varianta 1
DECLARE
    v_localizare VARCHAR(5) := 'I';
    v_nume_dep departments.department_name%TYPE;
BEGIN
    SELECT department_name 
    INTO v_nume_dep
    FROM departments
    WHERE location_id = 2400;
    DBMS_OUTPUT.PUT_LINE(v_nume_dep);
    
    v_localizare := 'II';
    SELECT department_name
    INTO v_nume_dep
    FROM departments
    WHERE department_id = 780;
    DBMS_OUTPUT.PUT_LINE(v_nume_dep);
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('NO DATA FOUND OCCURED IN ' || v_localizare || ' SELECT');
END;
/

-- Varianta II
DECLARE
    v_nume_dep departments.department_name%TYPE;
BEGIN
    BEGIN
        SELECT department_name 
        INTO v_nume_dep
        FROM departments
        WHERE location_id = 2900;
        DBMS_OUTPUT.PUT_LINE(v_nume_dep);
    EXCEPTION
        WHEN NO_DATA_FOUND THEN
            DBMS_OUTPUT.PUT_LINE('NO DATA FOUND IN 1st SELECT');
    END;
    
    BEGIN    
        SELECT department_name
        INTO v_nume_dep
        FROM departments
        WHERE department_id = 780;
        DBMS_OUTPUT.PUT_LINE(v_nume_dep);
    EXCEPTION
        WHEN NO_DATA_FOUND THEN
            DBMS_OUTPUT.PUT_LINE('NO DATA FOUND IN 2nd SELECT');
    END;
END;
/


DROP TABLE error_dda;

-- Infromatiile despre erorile aparute la compilare pot fi obtinute consultand vizualizarea USER_ERRORS
SELECT LINE, POSITION, TEXT
FROM USER_ERRORS
WHERE NAME = UPPER('danadascalescu');