-- Exemple
-- 1. Obtineti pentru fiecare departament numele acestuia si numarul de angajati.
SET SERVEROUTPUT ON
DECLARE
    v_num NUMBER(4);
    v_nume_dep departments.department_name%TYPE;
    CURSOR c IS
        SELECT department_name nume, COUNT(employee_id) nr
        FROM departments d, employees e
        WHERE d.department_id = e.department_id(+)
        GROUP BY d.department_name;
BEGIN
    OPEN c;
    LOOP
        FETCH c INTO v_nume_dep, v_num;
        EXIT WHEN c%NOTFOUND;
        IF v_num=0 THEN
            DBMS_OUTPUT.PUT_LINE('In departamentul ' || v_nume_dep || ' nu lucreaza niciun angajat.');
        ELSIF v_num = 1 THEN
            DBMS_OUTPUT.PUT_LINE('In departamentul ' || v_nume_dep || ' lucreaza un angajat.');
        ELSE 
            DBMS_OUTPUT.PUT_LINE('In departamentul ' || v_nume_dep || ' lucreaza ' || v_num || ' angajati.');
        END IF;
    END LOOP;
    CLOSE c;
END;
/

--2. Rezolvati exercitiul 1 mentinand informatiile din cursor in colectii.
DECLARE
    TYPE tab_nume IS TABLE OF departments.department_name%TYPE;
    TYPE var_num IS TABLE OF NUMBER(4);
    t_nume tab_nume;
    v_nr var_num;
    CURSOR c IS
        SELECT d.department_name, COUNT(e.employee_id)
        FROM departments d, employees e
        WHERE d.department_id = e.department_id(+)
        GROUP BY d.department_name;
BEGIN
    OPEN c;
    FETCH c BULK COLLECT INTO t_nume, v_nr;
    CLOSE c;
    FOR i IN t_nume.FIRST..t_nume.LAST LOOP
        IF v_nr(i)=0 THEN
            DBMS_OUTPUT.PUT_LINE('In departamentul ' || t_nume(i) || ' nu lucreaza angajati.');
        ELSIF v_nr(i)=1 THEN
            DBMS_OUTPUT.PUT_LINE('In departamentul ' || t_nume(i) || ' lucreaza un angajat.');
        ELSE
            DBMS_OUTPUT.PUT_LINE('In departamentul ' || t_nume(i) || ' lucreaza ' || v_nr(i) || ' angajati.');
        END IF;
    END LOOP;
END;
/


-- 3. Rezolvati exercitiul 1 folosind un ciclu cursor.
SET SERVEROUTPUT ON
DECLARE
    CURSOR C IS
        SELECT department_name dep, COUNT(employee_id) nr
        FROM departments d, employees e
        WHERE d.department_id = e.department_id(+)
        GROUP BY department_name;
BEGIN
    FOR i IN c LOOP
        IF i.nr =0 THEN
            DBMS_OUTPUT.PUT_LINE('In departamentul ' || i.dep || ' nu lucreaza angajati.');
        ELSIF i.nr=1 THEN
            DBMS_OUTPUT.PUT_LINE('In departamentul ' || i.dep || ' lucreaza un angajat.');
        ELSE
            DBMS_OUTPUT.PUT_LINE('In departamentul ' || i.dep || ' lucreaza ' || i.nr || ' angajati.');
        END IF;
    END LOOP;
END;
/


-- 4. Rezolvati exercitiul 1 folosind un ciclu cursor cu subcereri.
SET SERVEROUTPUT ON
BEGIN
    FOR i IN ( SELECT d.department_name dep_name, COUNT(e.employee_id) count_emp
               FROM departments d, employees e
               WHERE d.department_id = e.department_id(+)
               GROUP BY d.department_name) LOOP
        IF i.count_emp=0 THEN
            DBMS_OUTPUT.PUT_LINE('In departamentul ' || i.dep_name || ' nu lucreaza angajati.');
        ELSIF i.count_emp=1 THEN
            DBMS_OUTPUT.PUT_LINE('In departamentul ' || i.dep_name || ' lucreaza un angajat.');
        ELSE
            DBMS_OUTPUT.PUT_LINE('In departamentul ' || i.dep_name || ' lucreaza ' || i.count_emp || ' angajati.');
        END IF;
    END LOOP;     
END;
/


-- 5. Obtineti primii 3 manageri care au cei mai multi subordonati. Afisati numele managerului, respectiv numarul de angajati.
--- Rezolvati problema folosind un cursor explicit
-- Cererea SQL care returneaza primii 3 manageri care au cei mai multi subordonati
SELECT *
FROM (  SELECT mng.employee_id mng#, MAX(mng.last_name) mng, COUNT(*) count_emp
        FROM employees mng, employees e
        WHERE e.manager_id = mng.employee_id
        GROUP BY mng.employee_id)
WHERE ROWNUM < 4;


SET SERVEROUTPUT ON
DECLARE
    CURSOR c IS
        SELECT *
        FROM (  SELECT mng.employee_id mng#, MAX(mng.last_name) mng, COUNT(*) count_emp
                FROM employees mng, employees e
                WHERE e.manager_id = mng.employee_id
                GROUP BY mng.employee_id
                ORDER BY 3 DESC)
        WHERE ROWNUM < 4;
    v_cod_manager employees.employee_id%TYPE;
    v_nume_manager employees.last_name%TYPE;
    v_num_subordonati NUMBER(4) := 0;
BEGIN
    OPEN c;
    LOOP
        FETCH c INTO v_cod_manager, v_nume_manager, v_num_subordonati;
        EXIT WHEN c%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE(v_nume_manager || ' ' || v_num_subordonati);
    END LOOP;
    CLOSE c;
END;
/


-- 6. Exercitiul 5 rezolvat folosind un ciclu cursor
DECLARE 
    CURSOR c IS
        SELECT *
        FROM (  SELECT mng.employee_id mng#, MAX(mng.last_name) mng, COUNT(*) count_emp
                FROM employees mng, employees e
                WHERE e.manager_id = mng.employee_id
                GROUP BY mng.employee_id
                ORDER BY 3 DESC);
                
BEGIN
    FOR i IN c LOOP
        EXIT WHEN c%ROWCOUNT>4 OR c%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE(i.mng || ' ' || i.count_emp);
    END LOOP;
END;
/


SET SERVEROUTPUT ON
DECLARE
    v_top NUMBER(1) := 1;
    CURSOR c IS
        SELECT *
        FROM (  SELECT mng.employee_id mng#, MAX(mng.last_name) mng, COUNT(*) count_emp
                FROM employees mng, employees e
                WHERE e.manager_id = mng.employee_id
                GROUP BY mng.employee_id
                ORDER BY 3 DESC);
    v_cod_manager employees.employee_id%TYPE;
    v_nume_manager employees.last_name%TYPE;
    v_num_subordonati NUMBER(4) := 0;
    v_num_anterior NUMBER(4) := 0;
BEGIN
    OPEN c;
    LOOP
        FETCH c INTO v_cod_manager, v_nume_manager, v_num_subordonati;
        EXIT WHEN v_top = 4;
        IF v_num_subordonati <> v_num_anterior THEN
            v_top := v_top + 1;
            DBMS_OUTPUT.PUT_LINE(v_nume_manager || ' ' || v_num_subordonati);
        END IF;
        v_num_anterior := v_num_subordonati;
    END LOOP;
    CLOSE c;
END;
/


-- 7. Rezolvati exercitiul 5 folosind un ciclu cursor cu subcereri.
SET SERVEROUTPUT ON
DECLARE
    v_top NUMBER(1) := 0;
BEGIN
    FOR i IN( SELECT sef.employee_id cod, MAX(sef.last_name) nume, count(*) nr
              FROM employees sef, employees ang
              WHERE ang.manager_id = sef.employee_id
              GROUP BY sef.employee_id
              ORDER BY 3 DESC) LOOP
        v_top := v_top + 1;
        DBMS_OUTPUT.PUT_LINE('Managerul ' || i.cod || ' avand numele ' || i.nume || ' conduce ' || i.nr || ' angajati.');
        EXIT WHEN v_top=3;
    END LOOP;
END;
/


-- 8. Modificati exercitiul 1 astfel incat sa obtineti doar departamentele in care lucreaza cel putin x angajati, 
-- unde x reprezinta un numar introdus de la tastatura. Rezolvati problema folosind toate cele trei tipuri de cursoare studiate. 
-- Varianta 1 - cursor explicit
SET SERVEROUTPUT ON
DECLARE
    v_x NUMBER := '&p_x';
    v_num NUMBER(4);
    v_nume_dep departments.department_name%TYPE;
    CURSOR c(parametru NUMBER) IS
        SELECT department_name nume, COUNT(employee_id) nr
        FROM departments d, employees e
        WHERE d.department_id = e.department_id(+)
        GROUP BY d.department_name
        HAVING COUNT(employee_id) > parametru;
BEGIN
    OPEN c(v_x);
    LOOP
        FETCH c INTO v_nume_dep, v_num;
        EXIT WHEN c%NOTFOUND;
        IF v_num = 0 THEN
            DBMS_OUTPUT.PUT_LINE('In departamentul ' || v_nume_dep || ' nu lucreaza niciun angajat.');
        ELSIF v_num = 1 THEN
            DBMS_OUTPUT.PUT_LINE('In departamentul ' || v_nume_dep || ' lucreaza un angajat.');
        ELSE 
            DBMS_OUTPUT.PUT_LINE('In departamentul ' || v_nume_dep || ' lucreaza ' || v_num || ' angajati.');
        END IF;
    END LOOP;
    CLOSE c;
END;
/


-- Varianta 2 - ciclu cursor
DECLARE
    v_x NUMBER := '&p_x';
    CURSOR c(parametru NUMBER) IS
        SELECT department_name nume, COUNT(employee_id) nr
        FROM departments d, employees e
        WHERE d.department_id = e.department_id(+)
        GROUP BY d.department_name
        HAVING COUNT(employee_id) > parametru;
BEGIN
    FOR i IN c(v_x) LOOP
        DBMS_OUTPUT.PUT_LINE('In departamentul ' || i.nume || ' lucreaza ' || i.nr || ' angajati.');        
    END LOOP;
END;
/


-- Varianta 3 - ciclu cursor cu subcerere
DECLARE
    v_x NUMBER := '&p_x';
BEGIN
    FOR i IN ( SELECT department_name nume, COUNT(employee_id) nr
               FROM departments d, employees e
               WHERE d.department_id=e.department_id
               GROUP BY department_name
               HAVING COUNT(employee_id)> v_x) LOOP
    DBMS_OUTPUT.PUT_LINE('In departamentul '|| i.nume || ' lucreaza ' || i.nr || ' angajati');
    END LOOP;
END;
/


-- 9. Mariti cu 1000 salariile celor care au fost angajati in 2000, blocand liniile inainte de actualizare.
SELECT last_name, hire_date, salary
FROM emp_dda
WHERE TO_CHAR(hire_date, 'yyyy') = 2000;

DECLARE
    CURSOR c IS
        SELECT *
        FROM emp_dda
        WHERE TO_CHAR(hire_date, 'YYYY') = '2000'
        FOR UPDATE OF salary NOWAIT;
BEGIN
    FOR i IN c LOOP
        UPDATE emp_dda
        SET salary = salary + 1000
        WHERE CURRENT OF c;
    END LOOP;
END;
/

SELECT last_name, hire_date, salary
FROM emp_dda
WHERE TO_CHAR(hire_date, 'yyyy') = 2000;
ROLLBACK;


-- 10. Pentru fiecare departament 10, 20, 30 si 40, obtineti numele precum si lista numelor angajatilor
-- care isi desfasoara activitatea in cadrul acestora.
-- Varianta 1 - cursor clasic
DECLARE
    CURSOR c_dep IS
        SELECT department_id, department_name
        FROM departments
        WHERE department_id IN (10, 20, 30, 40);
        
    CURSOR c_emp IS
        SELECT department_id, last_name
        FROM employees;
        
    v_dep_id_c_dep departments.department_id%TYPE;
    v_dep_id_c_emp employees.department_id%TYPE;
    v_dep_name departments.department_name%TYPE;
    v_emp_name employees.last_name%TYPE;
BEGIN
    OPEN c_dep;
    LOOP
        FETCH c_dep INTO v_dep_id_c_dep, v_dep_name;
        EXIT WHEN c_dep%NOTFOUND;
        
        DBMS_OUTPUT.PUT_LINE('-------------------------------------');
        DBMS_OUTPUT.PUT_LINE ('DEPARTAMENT '|| v_dep_name);
        DBMS_OUTPUT.PUT_LINE('-------------------------------------');
        
        OPEN c_emp;
        LOOP
            FETCH c_emp INTO v_dep_id_c_emp, v_emp_name;
            EXIT WHEN c_emp%NOTFOUND;
            IF v_dep_id_c_emp = v_dep_id_c_dep THEN
                DBMS_OUTPUT.PUT_LINE(v_emp_name);
            END IF;
        END LOOP;
        CLOSE c_emp;
    END LOOP;
    CLOSE c_dep;
END;
/


-- Varianta 2 - ciclu cursor
DECLARE
    CURSOR c_dep IS
        SELECT department_id, department_name
        FROM departments
        WHERE department_id IN (10, 20, 30, 40);
        
    CURSOR c_emp IS
        SELECT department_id, first_name||' '||last_name name
        FROM employees;
BEGIN
    FOR i IN c_dep LOOP
        DBMS_OUTPUT.PUT_LINE('------------------------------------------------');
        DBMS_OUTPUT.PUT_LINE('DEPARTAMENTUL ' || i.department_name);
        DBMS_OUTPUT.PUT_LINE('------------------------------------------------');
        
        FOR j IN c_emp LOOP
            IF j.department_id = i.department_id THEN
                DBMS_OUTPUT.PUT_LINE(j.name);
            END IF;
        END LOOP;
    END LOOP;
END;
/


-- Varianta 3 - ciclu cursor cu subcereri
SET SERVEROUTPUT ON
BEGIN 
    FOR v_dept IN ( SELECT department_id, department_name
                   FROM departments
                   WHERE department_id IN (10, 20, 30, 40)) LOOP
        DBMS_OUTPUT.PUT_LINE('-------------------------------------');
        DBMS_OUTPUT.PUT_LINE ('DEPARTAMENT '||v_dept.department_name);
        DBMS_OUTPUT.PUT_LINE('-------------------------------------');
             
        FOR v_emp IN ( SELECT first_name||' '||last_name name
                       FROM employees
                       WHERE department_id = v_dept.department_id) LOOP
            DBMS_OUTPUT.PUT_LINE(v_emp.name);
        END LOOP;
    END LOOP;    
END;
/

-- Varianta 4 - expresii cursor
DECLARE
    TYPE refcursor IS REF CURSOR;
    CURSOR c_dep IS
        SELECT department_name,
            CURSOR ( SELECT last_name
                     FROM employees
                     WHERE department_id = d.department_id)
        FROM departments d
        WHERE d.department_id IN (10,20,30,40);
    
    v_cursor   refcursor;
    v_nume_dep departments.department_name%TYPE;
    v_nume_emp employees.last_name%TYPE;
BEGIN
    OPEN c_dep;
    LOOP
        FETCH c_dep INTO v_nume_dep, v_cursor;
        EXIT WHEN c_dep%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE('-------------------------------------');
        DBMS_OUTPUT.PUT_LINE ('DEPARTAMENT '||v_nume_dep);
        DBMS_OUTPUT.PUT_LINE('-------------------------------------');
        
        LOOP
            FETCH v_cursor INTO v_nume_emp;
            EXIT WHEN v_cursor%NOTFOUND;
            DBMS_OUTPUT.PUT_LINE(v_nume_emp);
        END LOOP;
    END LOOP;
    CLOSE c_dep;
END;
/


-- 11.   Declarati un cursor dinamic care intoarce linii de tipul celor din tabelul emp_***. In functie de o optiune
--     introdusa de la tastatura(una dintre valorile 1,2 sau 3) deschideti cursorul astfel incat sa se regaseasca:
--     - toate informatiile din tabelul emp_*** (optiunea 1)
--     - doar angajatii avand salariul cuprins intre 10000 si 20000 (optiunea 2)
--     - doar salariatii angajati in anul 2000 (optiunea 3)
DECLARE
    TYPE emp_tip IS REF CURSOR RETURN employees%ROWTYPE;
    v_emp     emp_tip;
    v_optiune NUMBER := '&p_optiune';
    v_ang     employees%ROWTYPE;
BEGIN
    IF v_optiune = 1 THEN
        OPEN v_emp FOR SELECT *
                       FROM employees;
    ELSIF v_optiune = 2 THEN
        OPEN v_emp FOR SELECT *
                       FROM employees
                        WHERE salary BETWEEN 10000 AND 20000;
    ELSIF v_optiune = 3 THEN
        OPEN v_emp FOR SELECT *
                       FROM employees
                       WHERE TO_CHAR(hire_date, 'YYYY') = 2000;
    ELSE
        DBMS_OUTPUT.PUT_LINE('Optiune incorecta');
    END IF;
    
    LOOP
        FETCH v_emp INTO v_ang;
        EXIT WHEN v_emp%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE(v_ang.first_name||' '||v_ang.last_name);
    END LOOP;
    DBMS_OUTPUT.PUT_LINE('Au fost procesate ' || v_emp%ROWCOUNT || ' linii.');
    
    CLOSE v_emp;
END;
/


--12.  Cititi de la tastatura o valoare n. Prin intermediul unui cursor deschis cu ajutorul unui sir dinamic,
--    obtineti angajatii avand salariul mai mare decat n. Pentru fiecare linie regasita de cursor afisati urmatoarele informatii:
--    - numele si salariul daca angajatul nu are comision;
--    - numele, salariul si comisionul daca angajatul are comision.

DECLARE
    TYPE empref IS REF CURSOR;
    v_emp empref;
    v_employee_id               employees.employee_id%TYPE;
    v_employee_salary           employees.salary%TYPE;
    v_employee_commission_pct   employees.commission_pct%TYPE;
    v_nr  employees.salary%TYPE := '&n';
BEGIN
    OPEN v_emp FOR
        'SELECT employee_id, salary, commission_pct ' ||
        'FROM employees WHERE salary > :bind_var'
        USING v_nr;
    LOOP
        FETCH v_emp INTO v_employee_id, v_employee_salary, v_employee_commission_pct;
        EXIT WHEN v_emp%NOTFOUND;
        IF v_employee_commission_pct IS NOT NULL THEN
            DBMS_OUTPUT.PUT_LINE('Angajatul ' || v_employee_id || ' are un salariu in valoare de ' 
                || v_employee_salary || ' si un comision de ' || v_employee_commission_pct);
        ELSE
            DBMS_OUTPUT.PUT_LINE('Angajatul ' || v_employee_id || 'are un salariu de ' || v_employee_salary);
        END IF;
    END LOOP;
    CLOSE v_emp;
END;
/

-- 1. Pentru fiecare job (titlu  care va fi afisat o singura data) obtineti lista angajatilor (nume si salariu) care lucreaza
-- in prezent pe jobul respectiv. Tratati cazul in care nu exista angajati care sa lucreze in prezent pe un anumit job. Rezolvati problema folosind:
-- a. cursoare clasice

-- Varianta 1 - nu se iau in considerare job-urile fara angajati
SET SERVEROUTPUT ON
DECLARE
    CURSOR c_jobs IS
        SELECT job_id, job_title
        FROM jobs;
    CURSOR c_employees IS
        SELECT last_name, salary, job_id
        FROM employees;
    
    v_count NUMBER(2) := 0;
    v_job_id_cj jobs.job_id%TYPE;
    v_job_title jobs.job_title%TYPE;
    v_job_id_ce employees.job_id%TYPE;
    v_emp_name employees.last_name%TYPE;
    v_emp_salary employees.salary%TYPE;
BEGIN
    OPEN c_jobs;
    LOOP
        FETCH c_jobs INTO v_job_id_cj, v_job_title;
        EXIT WHEN c_jobs%NOTFOUND;
        DBMS_OUTPUT.NEW_LINE;
        DBMS_OUTPUT.PUT_LINE(v_job_title);
        
        OPEN c_employees;
        LOOP
            FETCH c_employees INTO v_emp_name, v_emp_salary, v_job_id_ce;
            EXIT WHEN c_employees%NOTFOUND;
            
            IF v_job_id_cj = v_job_id_ce THEN
                DBMS_OUTPUT.PUT_LINE('Angajatul ' || v_emp_name || ' are salariul ' || v_emp_salary);
                v_count := v_count + 1;
            END IF;
        END LOOP;        
        CLOSE c_employees;
        
        IF v_count <> 0 THEN
            DBMS_OUTPUT.PUT_LINE('Total angajati: ' || v_count);
        END IF;
        v_count := 0;
    END LOOP;
    CLOSE c_jobs;
END;
/


-- Varianta 2 - se iau in considerare departamentele fara angajati
SET SERVEROUTPUT ON
DECLARE
    CURSOR c IS
        SELECT j.job_id id, MAX(j.job_title) title, COUNT(*) emp_count
        FROM jobs j, employees e
        WHERE j.job_id = e.job_id(+)
        GROUP BY j.job_id;
        
    v_job_id    jobs.job_id%TYPE;
    v_job_title jobs.job_title%TYPE;
    v_count_emp NUMBER;
BEGIN
    OPEN c;
    LOOP
        FETCH c INTO v_job_id, v_job_title, v_count_emp;
        EXIT WHEN c%NOTFOUND;
        
        IF v_count_emp = 0 THEN
            DBMS_OUTPUT.PUT_LINE('Nicun angajat nu are job-ul' || v_job_title);
        ELSE
            DBMS_OUTPUT.PUT_LINE('------------------------------------------------------------------------');
            DBMS_OUTPUT.PUT_LINE(v_job_title);
            DBMS_OUTPUT.PUT_LINE('------------------------------------------------------------------------');
            
            FOR i IN ( SELECT first_name||' '||last_name name, salary
                       FROM employees
                       WHERE job_id = v_job_id) LOOP
                DBMS_OUTPUT.PUT_LINE(i.name || ' are un salariu in valoare de ' || i.salary);   
            END LOOP;
        END IF;
    END LOOP;
    CLOSE c;
END;
/

-- b. ciclu cursoare
DESC jobs;

SET SERVEROUTPUT ON
DECLARE
    CURSOR c_jobs IS
        SELECT j.job_id id, MAX(j.job_title) title, COUNT(*) count_emp
        FROM jobs j, employees e
        WHERE j.job_id = e.job_id(+)
        GROUP BY j.job_id;
    
    CURSOR c_emp(parametru jobs.job_id%TYPE) IS
        SELECT first_name||' '||last_name name, salary
        FROM employees
        WHERE job_id = parametru;   
BEGIN
    FOR i in c_jobs LOOP
        IF i.count_emp = 0 THEN
            DBMS_OUTPUT.PUT_LINE('Nu exista angajati cu job-ul ' || i.title);
            DBMS_OUTPUT.NEW_LINE;
        ELSE
            DBMS_OUTPUT.PUT_LINE('------------------------------------------------------------------');
            DBMS_OUTPUT.PUT_LINE(i.title);
            DBMS_OUTPUT.PUT_LINE('------------------------------------------------------------------');
            
            FOR j in c_emp(i.id) LOOP
                DBMS_OUTPUT.PUT_LINE(j.name || ' are un salariu in valoare de ' || j.salary);  
            END LOOP;
        END IF;
    END LOOP;
END;
/

-- c. ciclu cursoare cu subcereri
SET SERVEROUTPUT ON
BEGIN
    FOR i IN (  SELECT j.job_id id, MAX(j.job_title) title, COUNT(*) count_emp
                FROM jobs j, employees e
                WHERE j.job_id = e.job_id(+)
                GROUP BY j.job_id)  LOOP
    IF i.count_emp = 0 THEN
        DBMS_OUTPUT.PUT_LINE('Nu exista niciun angajat cu job-ul ' || i.title);
    ELSE 
        FOR j IN ( SELECT first_name||' '||last_name name, salary
                   FROM employees
                   WHERE job_id = i.id) LOOP
            DBMS_OUTPUT.PUT_LINE(j.name || ' are un salariu in valoare de ' || j.salary);   
        END LOOP;
    END IF;            
    END LOOP;
END;
/


-- d. expresii cursor
DECLARE
    TYPE refcursor IS REF CURSOR;
    v_cursor_emp refcursor;
    CURSOR c IS
        SELECT job_id, job_title,
            CURSOR( SELECT job_id, last_name, salary
                    FROM employees e
                    WHERE j.job_id = e.job_id)
        FROM jobs j;
    v_emp_job_id  employees.job_id%TYPE;
    v_jobs_job_id jobs.job_id%TYPE;
    v_job_title   jobs.job_title%TYPE;
    v_emp_name    employees.last_name%TYPE;
    v_salary      employees.salary%TYPE;
BEGIN
    LOOP
        FETCH c INTO v_jobs_job_id, v_job_title, v_cursor_emp;
        EXIT WHEN c%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE('---------------------------------------------------');
        DBMS_OUTPUT.PUT_LINE('JOB ' || v_job_title);
        DBMS_OUTPUT.PUT_LINE('---------------------------------------------------');
        
        LOOP
            FETCH v_cursor_emp INTO v_emp_job_id, v_emp_name, v_salary;
            EXIT WHEN v_cursor_emp%NOTFOUND;
            IF v_emp_job_id = v_jobs_job_id THEN
                DBMS_OUTPUT.PUT_LINE(v_emp_name || ' are un salariu in valoare de ' || v_salary); 
            END IF;            
        END LOOP;        
    END LOOP;
END;
/


-- 2.  Modificati exercitiul anterior astfel incat sa ob?ineti si urmatoarele informatii:
--     - un numar de ordine pentru fiecare angajat care va fi resetat pentru fiecare job
--     - pentru fiecare job:
--       o numarul de angajati
--       o valoarea lunara a veniturilor angajatilor
--       o valoarea medie a veniturilor angajatilor
--     - indiferent job
--       o numarul total de angajati
--       o valoarea totala lunara a veniturilor angajatilor
--       o valoarea medie a veniturilor angajatilor
SET SERVEROUTPUT ON
DECLARE
    CURSOR c_jobs IS
        SELECT j.job_id id, MAX(j.job_title) title, COUNT(*) count_emp,
            TO_CHAR(TRUNC(SUM(e.salary),4), 'L99G999D99MI', ' NLS_NUMERIC_CHARACTERS = '',.'' NLS_CURRENCY = ''$'' ') total_salaries, 
            TO_CHAR(TRUNC(AVG(e.salary),4), 'L99G999D99MI', ' NLS_NUMERIC_CHARACTERS = '',.'' NLS_CURRENCY = ''$'' ') avg_salaries
        FROM jobs j, employees e
        WHERE j.job_id = e.job_id(+)
        GROUP BY j.job_id;
    
    CURSOR c_emp(parametru jobs.job_id%TYPE) IS
        SELECT first_name||' '||last_name name, salary
        FROM employees
        WHERE job_id = parametru;  
    
    v_index_emp            NUMBER(2);
    v_total_employees      NUMBER(32) := 0;
    v_avg_salaries_jobs    NUMBER(32) := 0;
    v_total_salaries_jobs  NUMBER(32) := 0;
BEGIN
    FOR i in c_jobs LOOP
        IF i.count_emp = 0 THEN
            DBMS_OUTPUT.PUT_LINE('Nu exista angajati cu job-ul ' || i.title);
            DBMS_OUTPUT.NEW_LINE;
        ELSE
            DBMS_OUTPUT.PUT_LINE('------------------------------------------------------------------');
            DBMS_OUTPUT.PUT_LINE(i.title);
            DBMS_OUTPUT.PUT_LINE('------------------------------------------------------------------');
            
            v_index_emp := 1;
            FOR j in c_emp(i.id) LOOP
                DBMS_OUTPUT.PUT_LINE(v_index_emp || '. ' || j.name || ' are un salariu in valoare de ' || 
                    TO_CHAR(j.salary, 'L999G999D99MI', ' NLS_NUMERIC_CHARACTERS = '',.'' NLS_CURRENCY = ''$'' '));
                
                v_total_salaries_jobs := v_total_salaries_jobs + NVL(j.salary, 0);
                v_index_emp := v_index_emp + 1;
            END LOOP;
            
            
            DBMS_OUTPUT.NEW_LINE;
            DBMS_OUTPUT.PUT_LINE('Total angajati: ' || i.count_emp);
            DBMS_OUTPUT.PUT_LINE('Valoarea totala lunara a veniturilor angajatilor: ' || i.total_salaries);
            DBMS_OUTPUT.PUT_LINE('Valoarea medie a veniturilor angajatilor: ' || i.avg_salaries);
            DBMS_OUTPUT.NEW_LINE;            

            v_total_employees := v_total_employees + i.count_emp;
        END IF;
    END LOOP;
    
    DBMS_OUTPUT.PUT_LINE('Numar total de angajati(indiferent de job): ' || v_total_employees);
    DBMS_OUTPUT.PUT_LINE('Valoarea totala lunara a veniturilor angjatilor(indiferent de job): ' 
        || TO_CHAR(v_total_salaries_jobs, 'L999G999D99MI', ' NLS_NUMERIC_CHARACTERS = '',.'' NLS_CURRENCY = ''$'' '));
    DBMS_OUTPUT.PUT_LINE('Valoarea medie a veniturilor angajatilor: ' || 
        TO_CHAR(v_total_salaries_jobs / v_total_employees, 'L99G999D99MI', ' NLS_NUMERIC_CHARACTERS = '',.'' NLS_CURRENCY = ''$'' '));
END;
/


--3. Modificati exercitiul anterior astfel incat sa obtineti suma totala alocata lunar pentru plata salariilor si
-- a comisioanelor tuturor angajatilor, iar pentru fiecare angajat, cat la suta din aceasta suma castiga lunar.
SET SERVEROUTPUT ON
DECLARE
    CURSOR c_jobs IS
        SELECT j.job_id id, MAX(j.job_title) title, COUNT(*) count_emp,
            TO_CHAR(TRUNC(SUM(e.salary),4), 'L99G999D99MI', ' NLS_NUMERIC_CHARACTERS = '',.'' NLS_CURRENCY = ''$'' ') total_salaries, 
            TO_CHAR(TRUNC(AVG(e.salary),4), 'L99G999D99MI', ' NLS_NUMERIC_CHARACTERS = '',.'' NLS_CURRENCY = ''$'' ') avg_salaries
        FROM jobs j, employees e
        WHERE j.job_id = e.job_id(+)
        GROUP BY j.job_id;
    
    CURSOR c_emp(parametru jobs.job_id%TYPE) IS
        SELECT first_name||' '||last_name name, 
            salary, commission_pct
        FROM employees
        WHERE job_id = parametru;  
    
    v_index_emp       NUMBER(2);
    v_venit_emp      NUMBER(32) := 0;
    v_total_salaries  NUMBER(32) := 0;
BEGIN
    -- obtinem valoarea totala alocata pentru plata salariilor si a comisioanelor angajatilor
    FOR k IN ( SELECT salary, commission_pct FROM employees) LOOP
        v_total_salaries := v_total_salaries + (NVL(k.salary, 0) + NVL(k.commission_pct, 0) * NVL(k.salary, 0));
    END LOOP;

    FOR i in c_jobs LOOP
        IF i.count_emp = 0 THEN
            DBMS_OUTPUT.PUT_LINE('Nu exista angajati cu job-ul ' || i.title);
            DBMS_OUTPUT.NEW_LINE;
        ELSE
            DBMS_OUTPUT.PUT_LINE('------------------------------------------------------------------');
            DBMS_OUTPUT.PUT_LINE(i.title);
            DBMS_OUTPUT.PUT_LINE('------------------------------------------------------------------');
            
            v_index_emp := 1;
            FOR j in c_emp(i.id) LOOP
                v_venit_emp := NVL(j.salary, 0) + NVL(j.salary, 0) * NVL(j.commission_pct, 0);
                DBMS_OUTPUT.PUT_LINE(v_index_emp || '. ' || j.name || ' are un salariu in valoare de ' || 
                    TO_CHAR(j.salary, 'L999G999D99MI', ' NLS_NUMERIC_CHARACTERS = '',.'' NLS_CURRENCY = ''$'' ') ||
                    'si castiga un commission de ' || NVL(j.commission_pct, 0));
                DBMS_OUTPUT.PUT_LINE('      Castiga un venit de ' || TRUNC((v_venit_emp * 100) / v_total_salaries, 3) 
                    || '% ' || ' din suma totala alocata platilor salariilor si comisioanelor ');
                v_index_emp := v_index_emp + 1;  
            END LOOP;
            
            DBMS_OUTPUT.NEW_LINE;
            
        END IF;
    END LOOP;
    
    DBMS_OUTPUT.PUT_LINE('Valoarea totala alocata pentru plata salariilor angajatilor si commisioanelor): ' 
        || TO_CHAR(v_total_salaries, 'L999G999D99MI', ' NLS_NUMERIC_CHARACTERS = '',.'' NLS_CURRENCY = ''$'' '));
END;
/


-- 4. Modificati exercitiul anterior astfel incat sa obtineti pentru fiecare job primii 5 angajati care
-- castiga cel mai mare salariu lunar. Specificati daca pentru un job sunt mai putin de 5 angajati.
SET SERVEROUTPUT ON
DECLARE
    CURSOR c_jobs IS
        SELECT j.job_id job_id, MAX(job_title) job_title, COUNT(e.employee_id) count_emp
        FROM jobs j, employees e
        WHERE j.job_id = e.job_id(+)
        GROUP BY j.job_id;
        
    CURSOR c_employees(parametru jobs.job_id%TYPE) IS
        SELECT *
        FROM (  SELECT first_name||' '||last_name name, salary
                FROM employees
                WHERE job_id = parametru
                ORDER BY salary DESC)
        WHERE ROWNUM <= 5;
BEGIN
    FOR i IN c_jobs LOOP
        IF i.count_emp = 0 THEN
            DBMS_OUTPUT.PUT_LINE('Nu exista niciun angajat cu job-ul ' || i.job_title);
        ELSIF i.count_emp < 5 THEN
            DBMS_OUTPUT.PUT_LINE('Sunt mai putin de 5 angajati cu job-ul ' || i.job_title);
            FOR j IN c_employees(i.job_id) LOOP
                DBMS_OUTPUT.PUT_LINE(j.name || ' castiga ' || j.salary);
            END LOOP;
        ELSE
            DBMS_OUTPUT.PUT_LINE('-----------------------------------------------------------------------');
            DBMS_OUTPUT.PUT_LINE(i.job_title);
            DBMS_OUTPUT.PUT_LINE('-----------------------------------------------------------------------');
            
            FOR j IN c_employees(i.job_id) LOOP
                DBMS_OUTPUT.PUT_LINE(j.name || ' castiga ' || j.salary);
            END LOOP;
        END IF;
        DBMS_OUTPUT.NEW_LINE;
    END LOOP;
END;
/


-- 5. Modificati  exercitiul anterior astfel incat sa obtineti pentru fiecare job top 5 angajati. Daca exista mai multi 
-- angajati care respecta criteriul de selectie care au acelasi salariu, atunci acestia vor ocupa aceeasi pozitie in top 5.
SET SERVEROUTPUT ON
DECLARE
    CURSOR c_jobs IS
        SELECT j.job_id, MAX(j.job_title) job_title, COUNT(e.employee_id) count_emp
        FROM jobs j, employees e
        WHERE j.job_id = e.job_id(+)
        GROUP BY j.job_id;

    CURSOR c_emp(parametru jobs.job_id%TYPE) IS
        SELECT first_name, last_name, NVL(salary, 0)
        FROM employees
        WHERE job_id = parametru
        ORDER BY 3 DESC;
        
    v_top            NUMBER;
    v_emp_first_name employees.first_name%TYPE;
    v_emp_last_name  employees.last_name%TYPE;
    v_emp_salary     employees.salary%TYPE;
    v_prev_salary    employees.salary%TYPE := 0;
BEGIN
    FOR i IN c_jobs LOOP
        IF i.count_emp = 0 THEN
            DBMS_OUTPUT.PUT_LINE('Nu exista niciun angajat cu job-ul ' || i.job_title);
        ELSE
            DBMS_OUTPUT.PUT_LINE('---------------------------------------------------------------------');
            DBMS_OUTPUT.PUT_LINE(i.job_title);
            DBMS_OUTPUT.PUT_LINE('---------------------------------------------------------------------');
            
            v_top := 1;
            v_prev_salary := 0;
            OPEN c_emp(i.job_id);
            LOOP
                FETCH c_emp INTO v_emp_first_name, v_emp_last_name, v_emp_salary;
                EXIT WHEN v_top > 5 OR c_emp%NOTFOUND;
                
                IF v_emp_salary <> v_prev_salary AND v_prev_salary <> 0 THEN
                    v_top := v_top + 1;
                    IF v_top <= 5 THEN
                        DBMS_OUTPUT.PUT_LINE(v_top || '. ' || v_emp_first_name || ' ' || v_emp_last_name || ' castiga ' || v_emp_salary);
                    END IF;
                ELSIF v_prev_salary = 0 THEN
                    DBMS_OUTPUT.PUT_LINE('1. ' || v_emp_first_name || ' ' || v_emp_last_name || ' castiga ' || v_emp_salary);
                ELSE
                    DBMS_OUTPUT.PUT_LINE('   ' || v_emp_first_name || ' ' ||v_emp_last_name || ' castiga ' || v_emp_salary);
                END IF;
                
                v_prev_salary := v_emp_salary;
            END LOOP;
            CLOSE c_emp;
        END IF;
    END LOOP;
END;
/
