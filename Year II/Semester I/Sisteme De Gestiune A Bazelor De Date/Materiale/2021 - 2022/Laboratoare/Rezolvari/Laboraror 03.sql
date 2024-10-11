-- TIPS
-- Cursoarele inseamna spatiu de memorie in plus, asa ca, daca avem un set activ foarte mare
-- acest lucru are un impact asupra performantei
-- cand dorim sa procesam fiecare linie, cu cursors for loop  (ambele variante) este mai simplu
-- atentie la for loop cursors, daca in loop avem DML, atunci schimbam in colectii + forall
-- daca vrem sa procesam cate n linii at a time, folosim cursor explicit cu limit
-- pentru o singura linie folosim select into nu cursoare


--1
DECLARE
 v_nr number(4);
 v_nume departments.department_name%TYPE;
 CURSOR c IS
 SELECT department_name nume, COUNT(employee_id) nr 
 FROM departments d, employees e
 WHERE d.department_id=e.department_id(+) 
 GROUP BY department_name; 
BEGIN
 OPEN c;
 LOOP
     FETCH c INTO v_nume,v_nr;
     EXIT WHEN c%NOTFOUND;
     IF v_nr=0 THEN
        DBMS_OUTPUT.PUT_LINE('In departamentul '|| v_nume||' nu lucreaza angajati');
     ELSIF v_nr=1 THEN
        DBMS_OUTPUT.PUT_LINE('In departamentul '|| v_nume||' lucreaza un angajat');
     ELSE
        DBMS_OUTPUT.PUT_LINE('In departamentul '|| v_nume||' lucreaza '|| v_nr||' angajati');
     END IF;
END LOOP;
CLOSE c;
END;

--2

DECLARE
 TYPE tab_nume IS TABLE OF departments.department_name%TYPE;
 TYPE tab_nr IS TABLE OF NUMBER(4);
 t_nr tab_nr;
 t_nume tab_nume;
 CURSOR c IS
 SELECT department_name nume, COUNT(employee_id) nr 
 FROM departments d, employees e
 WHERE d.department_id=e.department_id(+)
 GROUP BY department_name; 
BEGIN
 OPEN c;
 FETCH c BULK COLLECT INTO t_nume, t_nr;
 CLOSE c;
 FOR i IN t_nume.FIRST..t_nume.LAST LOOP
 IF t_nr(i)=0 THEN
    DBMS_OUTPUT.PUT_LINE('In departamentul '|| t_nume(i)|| ' nu lucreaza angajati');
 ELSIF t_nr(i)=1 THEN
    DBMS_OUTPUT.PUT_LINE('In departamentul '||t_nume(i)|| ' lucreaza un angajat');
 ELSE
    DBMS_OUTPUT.PUT_LINE('In departamentul '|| t_nume(i)||' lucreaza '|| t_nr(i)||' angajati');
 END IF;
 
 END LOOP;
END;
/





DECLARE
 TYPE tab_nume IS TABLE OF departments.department_name%TYPE;
 TYPE tab_nr IS TABLE OF NUMBER(4);
 t_nr tab_nr;
 t_nume tab_nume;
 CURSOR c IS
 SELECT department_name nume, COUNT(employee_id) nr 
 FROM departments d, employees e
 WHERE d.department_id=e.department_id(+)
 GROUP BY department_name; 
BEGIN
 OPEN c;
 FETCH c BULK COLLECT INTO t_nume, t_nr LIMIT 5;

    if t_nume.count = 0 then
        DBMS_OUTPUT.PUT_LINE('Nici o linie returnata');
    else
        DBMS_OUTPUT.PUT_LINE('Primele 5 linii returnate');
    END IF;  
 
 FOR i IN t_nume.FIRST..t_nume.LAST LOOP
     IF t_nr(i)=0 THEN
        DBMS_OUTPUT.PUT_LINE('In departamentul '|| t_nume(i)||' nu lucreaza angajati');
     ELSIF t_nr(i)=1 THEN
        DBMS_OUTPUT.PUT_LINE('In departamentul '||t_nume(i)||' lucreaza un angajat');
     ELSE
        DBMS_OUTPUT.PUT_LINE('In departamentul '|| t_nume(i)||' lucreaza '|| t_nr(i)||' angajati');
     END IF;
 END LOOP;
 
 dbms_output.new_line;
DBMS_OUTPUT.PUT_LINE('Urmatoarele 5 linii returnate');
   FETCH c BULK COLLECT INTO t_nume, t_nr LIMIT 5;
   
 FOR i IN t_nume.FIRST..t_nume.LAST LOOP
     IF t_nr(i)=0 THEN
        DBMS_OUTPUT.PUT_LINE('In departamentul '|| t_nume(i)||' nu lucreaza angajati');
     ELSIF t_nr(i)=1 THEN
        DBMS_OUTPUT.PUT_LINE('In departamentul '||t_nume(i)||' lucreaza un angajat');
     ELSE
        DBMS_OUTPUT.PUT_LINE('In departamentul '|| t_nume(i)||' lucreaza '|| t_nr(i)||' angajati');
     END IF;
 END LOOP;
 
    dbms_output.new_line;
    DBMS_OUTPUT.PUT_LINE('Ultimele linii returnate');
    
    FETCH c BULK COLLECT INTO t_nume, t_nr;
   
 FOR i IN t_nume.FIRST..t_nume.LAST LOOP
     IF t_nr(i)=0 THEN
        DBMS_OUTPUT.PUT_LINE('In departamentul '|| t_nume(i)||' nu lucreaza angajati');
     ELSIF t_nr(i)=1 THEN
        DBMS_OUTPUT.PUT_LINE('In departamentul '||t_nume(i)||' lucreaza un angajat');
     ELSE
        DBMS_OUTPUT.PUT_LINE('In departamentul '|| t_nume(i)||' lucreaza '|| t_nr(i)||' angajati');
     END IF;
 END LOOP;
 
CLOSE c;

END;
/

--3
DECLARE
 CURSOR c IS
 SELECT department_name nume, COUNT(employee_id) nr
 FROM departments d, employees e
 WHERE d.department_id=e.department_id(+)
 GROUP BY department_name; 
BEGIN
 FOR i in c LOOP
     IF i.nr=0 THEN
        DBMS_OUTPUT.PUT_LINE('In departamentul '|| i.nume||' nu lucreaza angajati');
     ELSIF i.nr=1 THEN
        DBMS_OUTPUT.PUT_LINE('In departamentul '|| i.nume ||' lucreaza un angajat');
     ELSE
        DBMS_OUTPUT.PUT_LINE('In departamentul '|| i.nume|| ' lucreaza '|| i.nr||' angajati');
     END IF;
END LOOP;
END;
/

--4
BEGIN
 FOR i in (SELECT department_name nume, COUNT(employee_id) nr
             FROM departments d, employees e
             WHERE d.department_id=e.department_id(+)
             GROUP BY department_name) LOOP
 IF i.nr=0 THEN
    DBMS_OUTPUT.PUT_LINE('In departamentul '|| i.nume|| ' nu lucreaza angajati');
 ELSIF i.nr=1 THEN
    DBMS_OUTPUT.PUT_LINE('In departamentul '|| i.nume || ' lucreaza un angajat');
 ELSE
    DBMS_OUTPUT.PUT_LINE('In departamentul '|| i.nume|| ' lucreaza '|| i.nr||' angajati');
 END IF;
END LOOP;
END;
/

--5
--a
DECLARE
 v_cod employees.employee_id%TYPE;
 v_nume employees.last_name%TYPE;
 v_nr NUMBER(4);
 CURSOR c IS
     SELECT sef.employee_id cod, MAX(sef.last_name) nume, count(*) nr
     FROM employees sef, employees ang
     WHERE ang.manager_id = sef.employee_id
     GROUP BY sef.employee_id
     ORDER BY nr DESC;
BEGIN
 OPEN c;
 LOOP
     FETCH c INTO v_cod,v_nume,v_nr;
     EXIT WHEN c%ROWCOUNT>3 OR c%NOTFOUND;
     DBMS_OUTPUT.PUT_LINE('Managerul '|| v_cod ||' avand numele ' || v_nume || ' conduce ' || v_nr||' angajati');
 END LOOP;
 CLOSE c;
END;
/

--b
-- primii 4
DECLARE
 v_cod employees.employee_id%TYPE;
 v_nume employees.last_name%TYPE;
 v_nr NUMBER(4);
 CURSOR c IS
     SELECT sef.employee_id cod, MAX(sef.last_name) nume, count(*) nr
     FROM employees sef, employees ang
     WHERE ang.manager_id = sef.employee_id
     GROUP BY sef.employee_id
     ORDER BY nr DESC;
BEGIN
 OPEN c;
 LOOP
     FETCH c INTO v_cod,v_nume,v_nr;
     EXIT WHEN c%ROWCOUNT > 4 OR c%NOTFOUND;
     DBMS_OUTPUT.PUT_LINE('Managerul '|| v_cod ||' avand numele ' || v_nume || ' conduce ' || v_nr||' angajati');
 END LOOP;
 CLOSE c;
END;
/

-- top 3 in pl sql


DECLARE
 v_cod employees.employee_id%TYPE;
 v_nume employees.last_name%TYPE;
 v_nr NUMBER(4);
 CURSOR c IS
     SELECT sef.employee_id cod, MAX(sef.last_name) nume, count(*) nr
     FROM employees sef, employees ang
     WHERE ang.manager_id = sef.employee_id
     GROUP BY sef.employee_id
     ORDER BY nr DESC;
top binary_integer :=1;
v_nr_anterior binary_integer;

BEGIN
 OPEN c;
 
  FETCH c INTO v_cod,v_nume,v_nr;
     DBMS_OUTPUT.PUT_LINE('Pe pozitia ' || top || ' Managerul '|| v_cod ||' avand numele ' || v_nume || ' conduce ' || v_nr||' angajati');
   v_nr_anterior := v_nr;
     
 LOOP
     FETCH c INTO v_cod,v_nume,v_nr;
     if v_nr <> v_nr_anterior then
        top := top +1;
    end if;
     v_nr_anterior := v_nr;
     
     exit when top > 3 or c%NOTFOUND;
     DBMS_OUTPUT.PUT_LINE('Pe pozitia ' || top || ' Managerul '|| v_cod ||' avand numele ' || v_nume || ' conduce ' || v_nr||' angajati');
 END LOOP;
 CLOSE c;
END;
/


with tabel as(
SELECT sef.employee_id cod, MAX(sef.last_name) nume, count(*) nr
     FROM employees sef, employees ang
     WHERE ang.manager_id = sef.employee_id
     GROUP BY sef.employee_id
     ORDER BY nr DESC
)
select * 
from tabel
where nr in (select * from (select distinct(nr) from tabel
                            ORDER BY nr DESC) tb
            where rownum <= 3);
            
 
 
with tabel as(
SELECT sef.employee_id cod, MAX(sef.last_name) nume, count(*) nr
     FROM employees sef, employees ang
     WHERE ang.manager_id = sef.employee_id
     GROUP BY sef.employee_id
     ORDER BY nr DESC
)
select * 
from tabel t
where 3 > (select count(distinct nr)
            from tabel
            where nr > t.nr);


DECLARE
CURSOR c IS 

with tabel as(
SELECT sef.employee_id cod, MAX(sef.last_name) nume, count(*) nr
     FROM employees sef, employees ang
     WHERE ang.manager_id = sef.employee_id
     GROUP BY sef.employee_id
     ORDER BY nr DESC
)
select * 
from tabel t
where 3 > (select count(distinct nr)
            from tabel
            where nr > t.nr);

BEGIN
    for i in c loop
        EXIT WHEN c%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE('Managerul '|| i.cod ||' avand numele ' || i.nume || ' conduce ' || i.nr||' angajati');
    end loop;
END;
/

--6
DECLARE
 CURSOR c IS
 SELECT sef.employee_id cod, MAX(sef.last_name) nume, count(*) nr
 FROM employees sef, employees ang
 WHERE ang.manager_id = sef.employee_id
 GROUP BY sef.employee_id
 ORDER BY nr DESC;
BEGIN
 FOR i IN c LOOP
 EXIT WHEN c%ROWCOUNT>3 OR c%NOTFOUND;
 DBMS_OUTPUT.PUT_LINE('Managerul '|| i.cod || ' avand numele ' || i.nume || ' conduce '|| i.nr||' angajati');
 END LOOP;
END;
/

--7
DECLARE
 top number(1):= 0; 
BEGIN
 FOR i IN (SELECT sef.employee_id cod, MAX(sef.last_name) nume, count(*) nr
             FROM employees sef, employees ang
             WHERE ang.manager_id = sef.employee_id
             GROUP BY sef.employee_id
             ORDER BY nr DESC) LOOP
 DBMS_OUTPUT.PUT_LINE('Managerul '|| i.cod ||' avand numele ' || i.nume ||' conduce '|| i.nr||' angajati');
 top := top+1;
 EXIT WHEN top=3;
 END LOOP;
END;
/

--8
DECLARE
 v_x number(4) := &p_x;
 v_nr number(4);
 v_nume departments.department_name%TYPE;
CURSOR c (paramentru NUMBER) IS
         SELECT department_name nume, COUNT(employee_id) nr 
         FROM departments d, employees e
         WHERE d.department_id=e.department_id
         GROUP BY department_name
         HAVING COUNT(employee_id)> paramentru; 
BEGIN
 OPEN c(v_x);
 LOOP
     FETCH c INTO v_nume,v_nr;
     EXIT WHEN c%NOTFOUND;
     DBMS_OUTPUT.PUT_LINE('In departamentul '|| v_nume|| ' lucreaza '|| v_nr||' angajati');
END LOOP;
CLOSE c;
END;
/

DECLARE
v_x number(4) := &p_x;
CURSOR c (paramentru NUMBER) IS
         SELECT department_name nume, COUNT(employee_id) nr
         FROM departments d, employees e
         WHERE d.department_id=e.department_id
         GROUP BY department_name
         HAVING COUNT(employee_id)> paramentru; 
BEGIN
 FOR i in c(v_x) LOOP
    DBMS_OUTPUT.PUT_LINE('In departamentul '|| i.nume|| ' lucreaza '|| i.nr||' angajati');
 END LOOP;
END;
/

DECLARE
v_x number(4) := &p_x;
BEGIN
 FOR i in (SELECT department_name nume, COUNT(employee_id) nr
             FROM departments d, employees e
             WHERE d.department_id=e.department_id
             GROUP BY department_name 
             HAVING COUNT(employee_id)> v_x) LOOP
 DBMS_OUTPUT.PUT_LINE('In departamentul '|| i.nume|| ' lucreaza '|| i.nr||' angajati');
END LOOP;
END;
/

--9

-- Clarificari pentru for update of
-- e folosita pentru a pune lock-ul pe randurile din tabelul dorit
-- in cazul de mai jos nu are nici un rost, pt ca ma uit intr-un singur tabel
-- dar daca de exemplu am avea mai multe join-uri
-- acest for update ar bloca toate randurile din toate tabelele joined
-- atunci are avea sens sa spunem for update of nume_tabel.nume_coloana
-- ca sa blocam doar liniile din tabelul care ne intereseaza


-- where current of ne ajuta sa nu ne mai folosim de cheia primara de exemplu
-- pentru a face un update/ delete pentru anumite linii
-- oracle stie pe ce linie sa faca update pe baza rowid-ului ei
-- dar daca in cursorul nostru avem mai multe tabele joined
-- where current of nu o sa mai functioneze si trebuie sa selectam noi rowid-ului
-- sau cheia primara pentru a identifica liniile

-- liniile sunt blocate pana facem un commit sau rollback
SELECT last_name, hire_date, salary
FROM emp_prof
WHERE TO_CHAR(hire_date, 'yyyy') = 2000;

DECLARE
 CURSOR c IS
 SELECT * FROM emp_prof
 WHERE TO_CHAR(hire_date, 'YYYY') = 2000
 FOR UPDATE OF salary NOWAIT;
BEGIN
 FOR i IN c LOOP
 UPDATE emp_prof
 SET salary= salary+1000
 WHERE CURRENT OF c;
 END LOOP;
END;
/

rollback;

--10
--a

BEGIN
 FOR v_dept IN (SELECT department_id, department_name
                     FROM departments
                     WHERE department_id IN (10,20,30,40)) LOOP
     DBMS_OUTPUT.PUT_LINE('-------------------------------------');
     DBMS_OUTPUT.PUT_LINE ('DEPARTAMENT '||v_dept.department_name);
     DBMS_OUTPUT.PUT_LINE('-------------------------------------');
     FOR v_emp IN (SELECT last_name
                     FROM employees
                    WHERE department_id = v_dept.department_id) LOOP
     DBMS_OUTPUT.PUT_LINE (v_emp.last_name);
     END LOOP;
 END LOOP;
END;
/

--b
DECLARE
 TYPE refcursor IS REF CURSOR;
 CURSOR c_dept IS
 SELECT department_name, 
 CURSOR (SELECT last_name 
         FROM employees e
         WHERE e.department_id = d.department_id)
 FROM departments d
 WHERE department_id IN (10,20,30,40);
 v_nume_dept departments.department_name%TYPE;
 v_cursor refcursor;
 v_nume_emp employees.last_name%TYPE;
BEGIN
 OPEN c_dept;
 LOOP
     FETCH c_dept INTO v_nume_dept, v_cursor;
     EXIT WHEN c_dept%NOTFOUND;
     DBMS_OUTPUT.PUT_LINE('-------------------------------------');
     DBMS_OUTPUT.PUT_LINE ('DEPARTAMENT '||v_nume_dept);
     DBMS_OUTPUT.PUT_LINE('-------------------------------------');
     LOOP
         FETCH v_cursor INTO v_nume_emp;
         EXIT WHEN v_cursor%NOTFOUND;
         DBMS_OUTPUT.PUT_LINE (v_nume_emp);
     END LOOP;
 END LOOP;
 CLOSE c_dept;
END;
/

--11

-- daca avem return statement pentru ref cursors => strong ref cursor
-- altfel weak ref cursor
-- strong ref cursors sunt less error-prone pentru ca se poate verifica compatibilitatea
-- selectului sau a comenzii fetch into la compilare

DECLARE
 TYPE emp_tip IS REF CURSOR RETURN employees%ROWTYPE;
 -- sau 
 -- TYPE emp_tip IS REF CURSOR;
 
 v_emp emp_tip;
    v_optiune NUMBER := &p_optiune;
 v_ang employees%ROWTYPE;
BEGIN
 IF v_optiune = 1 THEN
     OPEN v_emp FOR SELECT * FROM employees;
 ELSIF v_optiune = 2 THEN
    OPEN v_emp FOR SELECT * FROM employees
                WHERE salary BETWEEN 10000 AND 20000;
 ELSIF v_optiune = 3 THEN
    OPEN v_emp FOR SELECT * FROM employees
                WHERE TO_CHAR(hire_date, 'YYYY') = 2000;
 ELSE
    DBMS_OUTPUT.PUT_LINE('Optiune incorecta'); 
 END IF;
 
 IF v_emp%ISOPEN THEN
     LOOP
         FETCH v_emp into v_ang;
         EXIT WHEN v_emp%NOTFOUND;
         DBMS_OUTPUT.PUT_LINE(v_ang.last_name);
     END LOOP;
     
     DBMS_OUTPUT.PUT_LINE('Au fost procesate '||v_emp%ROWCOUNT || ' linii');
     CLOSE v_emp;
 END IF;
END;
/

--12

DECLARE
TYPE empref IS REF CURSOR; 
v_emp empref;
v_nr INTEGER := &n;
v_id number;
v_sal number;
v_comm number;

BEGIN
OPEN v_emp FOR  'SELECT employee_id, salary, commission_pct ' || 'FROM employees WHERE salary > :bind_var'
                USING v_nr;

LOOP
    FETCH v_emp into v_id, v_sal, v_comm;
    EXIT WHEN v_emp%notfound;
    if v_comm  is not null then
         DBMS_OUTPUT.PUT_LINE(v_id || ' ' || v_sal || ' ' || v_comm);
    else
        DBMS_OUTPUT.PUT_LINE(v_id || ' ' || v_sal);
    end if;
END LOOP;

close v_emp;
END;
/

-- nu conteaza numele variabilei de legatura, daca se repeta sau nu, important este ca in USING 
-- sa existe suficiente valori
-- se pot pune aproape orice tip de date in USING

DECLARE
TYPE empref IS REF CURSOR; 
v_emp empref;

v_id number;
v_sal number;
v_ln varchar2(10) :='KING';
v_fn varchar2(10) := 'STEVEN';
v_sal2 number := 200;
BEGIN
OPEN v_emp FOR  'SELECT employee_id, salary FROM employees WHERE upper(last_name) = :n AND upper(first_name) = :n'
|| ' AND salary > :n' USING v_ln, v_fn, v_sal2;
   LOOP
        FETCH v_emp into v_id, v_sal;
        EXIT WHEN v_emp%notfound; 
         DBMS_OUTPUT.PUT_LINE(v_id || ' ' || v_sal);
    END LOOP;
close v_emp;
END;
/

-- EXERCITII
--1
--a

DECLARE
CURSOR j IS SELECT job_id, job_title FROM jobs;
CURSOR e(job_curent VARCHAR2) IS SELECT last_name, salary FROM employees WHERE job_id = job_curent;

nume employees.last_name%type;
salariu employees.salary%type;
titlu_job jobs.job_title%type;
job jobs.job_id%type;
BEGIN

    OPEN j;
    LOOP
        FETCH j INTO job, titlu_job;
        EXIT WHEN j%notfound;
        DBMS_OUTPUT.PUT_LINE(titlu_job);
        OPEN e(job);
        LOOP
           FETCH e INTO nume, salariu;
           EXIT WHEN e%notfound;
           DBMS_OUTPUT.PUT_LINE('Ang ' || nume || ' ' || salariu);
        END LOOP;
        IF e%rowcount = 0 THEN
              DBMS_OUTPUT.PUT_LINE('Fara ang');
        END IF;
        CLOSE e;
    END LOOP;
    CLOSE j;
END;
/

--c

DECLARE
nr number;
BEGIN
     FOR j IN (SELECT job_id, job_title FROM jobs) LOOP
        DBMS_OUTPUT.PUT_LINE(j.job_title);
        nr :=0;
        FOR e IN (SELECT last_name, salary FROM employees WHERE job_id = j.job_id) LOOP
            nr := nr +1;
              DBMS_OUTPUT.PUT_LINE('Ang ' || e.last_name || ' ' || e.salary);
        END LOOP;
        IF nr = 0 THEN
          DBMS_OUTPUT.PUT_LINE('Fara ang');
        END IF;
     END LOOP;
END;
/

