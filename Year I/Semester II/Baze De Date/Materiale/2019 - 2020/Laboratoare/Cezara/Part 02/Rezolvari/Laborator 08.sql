--11
select avg(nvl(commission_pct,0)) from employees;

--12 
select job_title as "Job", nvl(sum(decode(department_id, 30, salary)),0) as "Dep30",
nvl(sum(decode(department_id, 50, salary)),0) as "Dep50",
nvl(sum(decode(department_id, 80, salary)),0) as "Dep80",
sum(salary) as "Total"
from jobs join employees using (job_id)
group by job_id, job_title;

--13
select count(employee_id), count(decode(to_char(hire_date, 'yyyy'),'1997',1)) as "1997",
count(decode(to_char(hire_date, 'yyyy'),'1998',1)) as "1998",
count(decode(to_char(hire_date, 'yyyy'),'1999',1)) as "1999",
count(decode(to_char(hire_date, 'yyyy'),'2000',1)) as "2000"
from employees;

--15
SELECT distinct j.job_title, tb.avv, (j.max_salary+j.min_salary)/ 2 - tb.avv
FROM jobs j, (SELECT e.job_id, AVG(e.salary) as avv
                    FROM employees e
                    GROUP BY e.job_id) tb
WHERE j.job_id = tb.job_id (+);


--16
SELECT distinct j.job_title, tb.avv, (j.max_salary+j.min_salary)/ 2 - tb.avv, tb.nr
FROM jobs j, (SELECT e.job_id, AVG(e.salary) as avv, count(*) as nr
                    FROM employees e
                    GROUP BY e.job_id) tb
WHERE j.job_id = tb.job_id (+);

--17
select d.department_name, e.first_name, tb.ms as "Min Salary"
from departments d, employees e, (select min(salary) as ms, department_id from employees group by department_id) tb
where tb.department_id = d.department_id and e.salary = tb.ms;

--- Lab 6
--2
--v1
select e.first_name, e.salary from employees e where e.salary > all (select avg(salary) from employees group by department_id);
--v2
select e.first_name, e.salary from employees e where e.salary > (select max(avg(salary)) from employees group by department_id);

--3
--v1
select e.first_name, e.salary from employees e
where e.salary = (select min(salary) from employees where department_id = e.department_id); 
--v2
select e.first_name, e.salary from employees e
where (department_id, e.salary) in (select department_id, min(salary) from employees group by department_id); 
--v3

--4
select d.department_name, e.last_name
from departments d, employees e
where d.department_id = e.department_id
and e.hire_date = (select MIN(hire_date)
                    from employees
                    where employees.department_id = e.department_id)
order by d.department_name; 

--6
select first_name, salary from employees where rownum<=3 order by salary desc;

--7
select e.employee_id, e.first_name, e.last_name from employees e where (select count(*) from employees where manager_id = e.employee_id) >= 2;

--8
select l.city from locations l where exists (select 1 from departments where location_id = l.location_id);
select l.city from locations l where l.location_id in (select location_id from departments where location_id = l.location_id);
select l.city from locations l where (select count(1) from departments where location_id = l.location_id) > 0;
