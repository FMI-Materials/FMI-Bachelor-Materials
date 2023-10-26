-- 19
select e.department_id, d.department_name, max(e.salary)
from employees e join departments d on (e.department_id = d.department_id)
group by e.department_id, d.department_name
having max(salary) > 3000;


-- 20
select min((select avg(salary)
           from employees e
           where e.job_id = j.job_id))
from jobs j;

--21
SELECT e.department_id, d.department_name, SUM(e.salary)
FROM employees e JOIN departments d ON (e.department_id = d.department_id)
GROUP BY e.department_id, d.department_name;

--22
SELECT MAX(AVG(salary))
FROM employees
GROUP BY department_id;

--23
select job_id, job_title, avg(salary) 
from employees join jobs using (job_id)
group by job_id, job_title
having avg(salary) = (select min(avg(salary)) from employees group by job_id);

--24
select AVG(salary)
from employees
having avg(salary) > 2500;

--- Lab 5
--1
select department_id, job_id, sum(salary)
from employees
group by department_id, job_id order by department_id;

--2
select department_id, job_id,department_name,job_title, sum(salary)
from employees
join departments using (department_id)
join jobs using (job_id)
group by department_id, job_id, department_name, job_title;

--3
select department_name, min(salary) from employees join departments using (department_id)
group by department_id, department_name 
having avg(salary) = (select max(avg(salary)) from employees group by department_id);

--4
--a
select e.department_id, d.department_name, count(*)
from employees e, departments d
where e.department_id = d.department_id
group by e.department_id, d.department_name
having count(*) < 4;
--b


--5
select employee_id, last_name, hire_date
from employees
where to_char(hire_date, 'DD') in (
    select to_char(hire_date, 'DD')
    from employees
    group by to_char(hire_date, 'DD')
    having count(*) = (
        select max(count(*))
        from employees
        group by to_char(hire_date, 'DD')
    )
);

--6
select e.department_id, d.department_name, count(*)as "Numar angajati"
from employees e, departments d
where e.department_id = d.department_id
group by e.department_id, d.department_name
having count(*) >= 15;

--7
select d.department_id, sum(e.salary) "Suma salariilor"
from departments d join employees e on (d.department_id = e.department_id)
having count(e.employee_id) > 10 and d.department_id != 30
group by d.department_id
order by sum(e.salary);

--8
select d.department_id, d.department_name,
count(e.employee_id), avg(e.salary),
e2.first_name, e2.salary, e2.job_id
from departments d 
left join employees e on (e.department_id = d.department_id) 
left join employees e2 on (e2.department_id = d.department_id)
group by d.department_id, d.department_name, e2.first_name, e2.salary, e2.job_id;

--9
select l.city, d.department_name, nvl(sum(e.salary),0)
from departments d join locations l using (location_id) left join employees e using (department_id)
where department_id > 80
group by department_id, d.department_name, l.city;

--10
select e.employee_id, e.first_name 
from employees e
join job_history j on (j.employee_id = e.employee_id)
having count(j.job_id) >= 2
group by e.employee_id, e.first_name


