--14
select * from job_grades;
select first_name, last_name, salary, (select grade_level from job_grades 
where e.salary>lowest_sal and e.salary<highest_sal) from employees e;

--18
DEFINE id_job = IT_PROG;
select first_name, department_id, salary from employees where job_id = '&id_job';

ACCEPT id_job_2 PROMPT 'cod= ';
select first_name, department_id, salary from employees where job_id = '&id_job_2';

--19
ACCEPT given_date DATE format 'YYYY-MM-DD' PROMPT 'date= ';
select first_name, department_id, salary, hire_date from employees
where hire_date > to_date('&given_date', 'YYYY-MM-DD');

--20
ACCEPT p_coloana PROMPT 'coloana= ';
ACCEPT p_tabel PROMPT 'tabel= ';
ACCEPT p_where PROMPT 'where= ';
SELECT &p_coloana FROM &p_tabel WHERE &p_where ORDER BY '&p_coloana';

--21
ACCEPT min_date DATE format 'MM/DD/YYYY' PROMPT 'min date= ';
ACCEPT max_date DATE format 'MM/DD/YYYY' PROMPT 'max date= ';
select first_name || ',' || job_id as "Angajati", hire_date from employees 
where hire_date > to_date('&min_date', 'MM/DD/YYYY') and
hire_date < to_date('&max_date', 'MM/DD/YYYY');

--22
ACCEPT city PROMPT 'city= ';
select first_name, job_id, salary, department_name from employees
join departments using (department_id) join locations using (location_id) where lower(city) = lower('&city');

--Lab 8
--1
CREATE TABLE EMP_BD AS SELECT * FROM employees; 
CREATE TABLE DEPT_BD AS SELECT * FROM departments;
 
--2




