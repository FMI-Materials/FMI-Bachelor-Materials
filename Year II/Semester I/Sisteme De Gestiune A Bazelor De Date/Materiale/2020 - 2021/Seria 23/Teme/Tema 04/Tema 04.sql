SET SERVEROUTPUT ON;
-- 1
-- select * from jobs;
-- create table jobs_bhd as select * from jobs;
-- select * from jobs_bhd;
DECLARE
    TYPE job_record IS RECORD
        (id_job jobs.job_id %type, job_title jobs.job_title %type, avg_salary integer);
    job_rec job_record;
    job_rec_del job_record;
BEGIN
    -- a
    job_rec.id_job := 1;
    job_rec.job_title := 'Programator';
    job_rec.avg_salary := 5000;
    DBMS_OUTPUT.put_line(job_rec.id_job || ' ' || job_rec.job_title || ' ' || job_rec.avg_salary);
    -- b
    select job_id, job_title, (min_salary + max_salary)/2 as avg_salary into job_rec from jobs where job_id = 'IT_PROG';
    DBMS_OUTPUT.put_line(job_rec.id_job || ' ' || job_rec.job_title || ' ' || job_rec.avg_salary);
    -- c
    delete from jobs_bhd
    where job_id = 'ST_MAN'
    returning job_id, job_title, (min_salary+max_salary) / 2 into job_rec_del;
    DBMS_OUTPUT.put_line(job_rec_del.id_job || ' ' || job_rec_del.job_title || ' ' || job_rec_del.avg_salary);
    ROLLBACK;
END;
-- 2
SET SERVEROUTPUT ON;
select * from emp_bhd;
DECLARE
    emp_best emp_bhd%ROWTYPE;
    emp_worst emp_bhd%ROWTYPE;
BEGIN
    select * into emp_best from emp_bhd where salary = (select max(salary) from emp_bhd) and rownum = 1;
    select * into emp_worst from emp_bhd where salary = (select min(salary) from emp_bhd) and rownum = 1;
    DBMS_OUTPUT.put_line(emp_best.salary || ' ' || emp_worst.salary);
    if (emp_worst.salary / emp_best.salary)*100 < 10 then
        update emp_bhd set salary = emp_worst.salary*1.1 where employee_id = emp_worst.employee_id;
    end if;
    ROLLBACK;
END;
-- 3
-- create table dept_bhd as select * from departments;
-- select * from dept_bhd;
DECLARE
    dept_1 dept_bhd%ROWTYPE;
    dept_2 dept_bhd%ROWTYPE;
BEGIN
    -- a
    dept_1.department_id := 300;
    dept_1.department_name := 'Research';
    dept_1.manager_id := 103;
    dept_1.location_id := 1700;
    insert into dept_bhd values dept_1;
    -- b
    delete from dept_bhd where department_id = 50 
    returning department_id, department_name, manager_id, location_id into dept_2;
    DBMS_OUTPUT.put_line(dept_2.department_id || ' ' || dept_2.department_name || ' ' || dept_2.manager_id || ' ' || dept_2.location_id);
    rollback;
END;
select * from dept_bhd;
-- 4
select * from emp_bhd;
DECLARE
    TYPE tablou_indexat IS TABLE OF emp_bhd%ROWTYPE INDEX BY PLS_INTEGER;
    emp_cols tablou_indexat;
BEGIN
    DELETE FROM emp_bhd WHERE commission_pct >= 0.1 AND commission_pct <= 0.3
    RETURNING employee_id, first_name, last_name, email, phone_number, hire_date, job_id, salary, commission_pct, manager_id, department_id
    BULK COLLECT INTO emp_cols;
    for i in emp_cols.first..emp_cols.last loop
        DBMS_OUTPUT.put_line(emp_cols(i).first_name || ' ' || emp_cols(i).employee_id || ' ' || emp_cols(i).commission_pct);
    end loop;
    rollback;
END;

