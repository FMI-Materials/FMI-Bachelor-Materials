--1b
SELECT last_name, salary, e.department_id, (select department_name from departments where department_id = e.department_id) "Departament", 
       round((select avg(salary) from employees where department_id = e.department_id), 2) "Medie",
       (select count(*) from employees where department_id = e.department_id) "Numar"
FROM employees e
WHERE salary > (SELECT AVG(salary)
                FROM employees
                WHERE department_id = e.department_id);
--2
select e.first_name, e.salary from employees e where e.salary > all (select avg(salary) from employees group by department_id);
--3
select e.first_name, e.salary from employees e
where salary = (select min(salary) from employees where department_id = e.department_id); 
--4
select d.department_name, e.last_name
from departments d, employees e
where d.department_id = e.department_id
and e.hire_date = (select MIN(hire_date)
                    from employees
                    where employees.department_id = e.department_id)
order by d.department_name; 
--6
select first_name, salary from employees where rownum<4 order by salary desc;
--7
select e.employee_id, e.first_name, e.last_name from employees e where (select count(*) from employees where manager_id = e.employee_id) >= 2;
--8
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
select first_name, salary from (select first_name, salary from employees order by salary desc) where rownum<=10;
--13
with tab_medie as (select job_id, avg(salary) medie from employees group by job_id)
select job_title 
from (select job_title from jobs j join tab_medie using(job_id) order by medie asc) 
where rownum <=3;

