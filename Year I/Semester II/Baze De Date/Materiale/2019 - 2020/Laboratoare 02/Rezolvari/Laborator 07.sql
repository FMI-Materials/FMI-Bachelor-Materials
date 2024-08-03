--1
-- met 1
SELECT DISTINCT employee_id, last_name
FROM employees a
WHERE NOT EXISTS
    (SELECT 1
     FROM project p
     WHERE to_char(start_date, 'yyyy')=2006 and to_char(start_date, 'mm') <=6
     AND NOT EXISTS
        (SELECT 'x'
        FROM works_on b
        WHERE p.project_id=b.project_id
        AND b.employee_id=a.employee_id));


--met 2
SELECT employee_id
FROM works_on
WHERE project_id IN
    (SELECT project_id
    FROM project
    WHERE to_char(start_date, 'yyyy')=2006 and to_char(start_date, 'mm') <=6)
GROUP BY employee_id
HAVING COUNT(project_id)=
    (SELECT COUNT(*)
    FROM project
    WHERE to_char(start_date, 'yyyy')=2006 and to_char(start_date, 'mm') <=6);
    
-- met 3
SELECT employee_id
FROM works_on
MINUS
SELECT employee_id from
 (SELECT employee_id, project_id
  FROM (SELECT DISTINCT employee_id FROM works_on) t1,
       (SELECT project_id FROM project WHERE to_char(start_date, 'yyyy')=2006 and to_char(start_date, 'mm') <=6) t2
  MINUS
  SELECT employee_id, project_id
  FROM works_on
 ) t3;
 
 --met 4
 SELECT DISTINCT employee_id
FROM works_on a
WHERE NOT EXISTS (
    (SELECT project_id
     FROM project p
     WHERE to_char(start_date, 'yyyy')=2006 and to_char(start_date, 'mm') <=6)
     MINUS
    (SELECT p.project_id
     FROM project p, works_on b
     WHERE p.project_id=b.project_id
     AND b.employee_id=a.employee_id));

--2
--met 4
select *
from project p
where not exists(select employee_id
from job_history
having count(job_id) = 2
group by employee_id
minus
select employee_id
from works_on
where project_id = p.project_id
);


 --met 1
SELECT *
FROM project p
WHERE NOT EXISTS
    (SELECT 1
     FROM employees e
     WHERE employee_id in (select employee_id
                           from job_history
                           having count(job_id) = 2
                           group by employee_id
                          )
     AND NOT EXISTS
        (SELECT 'x'
        FROM works_on b
        WHERE p.project_id=b.project_id
        AND b.employee_id=e.employee_id));
-- ex 3
select COUNT (*)
FROM employees e
WHERE (select count (job_id)
        FROM (SELECT employee_id, job_id
            FROM job_history
            UNION
            SELECT employee_id, job_id
            FROM employees)
        WHERE employee_id = e.employee_id) >= 3;
--5
WITH nelivrate AS (SELECT project_id
                   FROM project
                   WHERE NVL(delivery_date, sysdate) > deadline)
SELECT *
FROM employees e
WHERE (SELECT COUNT(*) 
       FROM WORKS_ON
       WHERE employee_id = e.employee_id AND project_id IN (SELECT * FROM nelivrate)) 
--ex 6
select e.employee_id,w.project_id
from employees e left join works_on w on(e.employee_id = w.employee_id);

--ex 7
with manageri as(select project_manager from project),
dep_manageri as(select department_id from employees where employee_id in (select * from manageri))
select * 
from employees
where department_id in (select* from dep_manageri);

--ex 8 
with manageri as(select project_manager from project),
dep_manageri as(select nvl(department_id,-1) from employees where employee_id in (select * from manageri))
select * 
from employees
where department_id not in (select* from dep_manageri) or department_id is NULL;
--ex9
select department_id
from employees
group by department_id
having avg(salary) > &p;
--10
select e.first_name, e.last_name, e.salary, count(project_id)
from employees e join (select employee_id, project_id from works_on union select project_manager, project_id from project) t on (e.employee_id = t.employee_id)
where 2 = (select count(*) from project where e.employee_id = project_manager)
group by e.first_name, e.last_name, e.salary;
--11
SELECT DISTINCT a.employee_id, e.last_name, e.first_name
FROM works_on a join employees e on (a.employee_id = e.employee_id)
WHERE NOT EXISTS ( (SELECT w.project_id FROM works_on w where w.employee_id = a.employee_id) 
MINUS (SELECT p.project_id FROM project p
WHERE p.project_manager = 102));

-- 12 a
with projects_200 as (select project_id
                    from works_on
                    where employee_id = 200)
select last_name
from employees e
where not exists(select project_id
        from projects_200
        
        minus
        
        select project_id
        from works_on w
        where w.employee_id = e.employee_id);

-- 12 b
with projects_200 as (select project_id
                    from works_on
                    where employee_id = 200)
select last_name
from employees e
where not exists(
        select project_id
        from works_on w
        where w.employee_id = e.employee_id
        
        minus
        
        select project_id
        from projects_200);

-- 13
with projects_200 as (select project_id
                    from works_on
                    where employee_id = 200)
select last_name
from employees e
where not exists(
        select project_id
        from works_on w
        where w.employee_id = e.employee_id
        
        minus
        
        select project_id
        from projects_200)
    and
    not exists(select project_id
        from projects_200
        
        minus
        
        select project_id
        from works_on w
        where w.employee_id = e.employee_id);

--ex 14
select * from job_grades;
select first_name, last_name, salary, (select grade_level from job_grades where e.salary>lowest_sal and e.salary<highest_sal) from employees e;

--17
--I
SELECT employee_id, last_name, salary, department_id
FROM employees
WHERE employee_id = &p_cod;
--II
--DEFINE p_cod = "101" // Ce efect are?
DEFINE p_cod
SELECT employee_id, last_name, salary, department_id
FROM employees
WHERE employee_id = &p_cod;
UNDEFINE p_cod;
--III
DEFINE p_cod=100;
SELECT employee_id, last_name, salary, department_id
FROM employees
WHERE employee_id = &&p_cod;
UNDEFINE p_cod;
--IV
ACCEPT p_cod PROMPT "cod= ";
SELECT employee_id, last_name, salary, department_id
FROM employees
WHERE employee_id = &p_cod;

--18
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
ACCEPT min_date DATE format 'MM/DD/RR' PROMPT 'min date= ';
ACCEPT max_date DATE format 'MM/DD/RR' PROMPT 'max date= ';
select first_name || ',' || job_id as "Angajati", hire_date from employees 
where hire_date between to_date('&min_date', 'MM/DD/RR') and to_date('&max_date', 'MM/DD/RR');
--22
ACCEPT city PROMPT 'city= ';
select first_name, job_id, salary, department_name from employees
join departments using (department_id) join locations using (location_id) where lower(city) = lower('&city');
