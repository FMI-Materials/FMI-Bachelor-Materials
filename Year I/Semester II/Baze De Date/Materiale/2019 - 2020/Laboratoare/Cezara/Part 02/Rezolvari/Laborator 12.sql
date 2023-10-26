--Laborator 8

-- 6
INSERT INTO emp_rtu(employee_id, last_name, email, hire_date, job_id, department_id)
VALUES(250, 'Nume1', 'nume1@gmail.com', sysdate, 'IT_PROG', 300);

COMMIT;

--7
desc emp_pnu;

INSERT INTO emp_pnu
VALUES(251, 'Prenume2', 'Nume2', 'nume2@gmail.com', '0212345', sysdate, 'IT_PROG', 3000, null, null, 300);

--8
INSERT INTO
 (SELECT employee_id, last_name, email, hire_date, job_id, salary, commission_pct
 FROM emp_pnu)
VALUES ((select max(employee_id) + 1 from emp_pnu), 'Nume252', 'nume252@emp.com',SYSDATE, 'SA_REP', 5000, NULL);

--12
REM setari
set verify off
REM comenzi ACCEPT
accept p_cod prompt 'Introduceti codul'
accept p_nume prompt 'Introduceti numele'
accept p_prenume prompt 'Introduceti prenumele'
accept p_salariu prompt 'Introduceti salariul'
INSERT INTO emp_pnu
VALUES (&p_cod, '&p_prenume', '&p_nume', substr('&p_prenume', 1, 1) || substr('&p_nume', 1, 7), null, sysdate, 'IT_PROG', &p_salariu, null, null, null);
REM suprimarea variabilelor utilizate
REM anularea setarilor, prin stabilirea acestora la valorile implicite

--13
select * from emp1_lma;
CREATE TABLE emp2_lma AS SELECT * FROM employees where 1=0;
CREATE TABLE emp3_lma AS SELECT * FROM employees where 1=0;

INSERT ALL
 WHEN salary < 5000 THEN INTO emp1_lma
 WHEN salary between 5000 and 10000 THEN INTO emp2_lma
 ELSE INTO emp3_lma
SELECT * FROM employees;

select * from emp1_lma;
select * from emp2_lma;
select * from emp3_lma;


--14
CREATE TABLE emp0_lma AS SELECT * FROM employees where 1=0;
INSERT FIRST
 WHEN department_id=80 THEN INTO emp0_lma
 WHEN salary < 5000 THEN INTO emp1_lma
 WHEN salary between 5000 and 10000 THEN INTO emp2_lma
 ELSE INTO emp3_lma
SELECT * FROM employees;
select * from emp0_lma;
select * from emp1_lma;
select * from emp2_lma;
select * from emp3_lma;
