--8
select city
from locations l
where exists (select 1
              from departments
              where location_id = l.location_id); 
              
select city
from locations l
where location_id in (select location_id
              from departments);

--9
select department_name
from departments d  
where not exists (select 1
                  from employees
                  where department_id = d.department_id);

--10
WITH val_dep AS (select department_name, sum(salary) total
                 from employees join departments using (department_id)
                 group by department_id, department_name),
val_medie AS (select avg(total) medie
              from val_dep)
SELECT *
FROM val_dep
WHERE total > (SELECT medie
               FROM val_medie)
ORDER BY department_name;


--11
with steven_id as ( select employee_id
                    from employees
                    where first_name = 'Steven' and last_name = 'King'),
subalterni_steven as (select *
                    from employees
                    where manager_id = (select employee_id
                                        from steven_id)),
vechime_max as (select min(hire_date) minh
                from subalterni_steven)
select employee_id, first_name, last_name, job_id, hire_date
from employees 
where manager_id = (select employee_id from subalterni_steven, vechime_max where hire_date = minh);

--12
--v1
select first_name, salary from (select first_name, salary from employees order by salary desc) where rownum <= 10;
--v2
select first_name, salary from employees e where (select count(*) from employees where salary >e.salary) < 10;

--13
--v1
select job_title from 
(select job_title from jobs j order by (select avg(salary) from employees where job_id = j.job_id) asc)
where rownum <=3;
--v2
with tab_medie as (select job_id, avg(salary) medie from employees group by job_id)
select job_title 
from (select job_title from jobs j join tab_medie using(job_id) order by medie asc) 
where rownum <=3;

--- Lab 7
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

--met 2
SELECT project_id, project_name
FROM works_on join project using (project_id)
WHERE employee_id IN
    (select employee_id
     from job_history
     having count(job_id) = 2
     group by employee_id)
GROUP BY project_id, project_name
HAVING COUNT(employee_id)=
    (SELECT count(COUNT(*))
     FROM job_history
     having count(job_id) = 2
     group by employee_id);

