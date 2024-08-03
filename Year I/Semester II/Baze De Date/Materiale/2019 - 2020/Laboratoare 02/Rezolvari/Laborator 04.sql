SELECT last_name, hire_date FROM employees WHERE  hire_date > (SELECT hire_date FROM employees WHERE  INITCAP(last_name)='Gates'); 

select last_name, department_id, salary from employees where manager_id = (select employee_id from employees where manager_id is null);

select e.last_name, d.department_name, e.salary from employees e, departments d where (e.department_id = d.department_id) and e.commission_pct is null and e.manager_id in (select e2.employee_id from employees e2 where e2.commission_pct is not null);

select last_name, department_id, salary, job_id from employees e where (e.salary, nvl(e.commission_pct, -1)) in 
(select salary, nvl(commission_pct, -1) from employees t, departments d, locations l where t.department_id = d.department_id and d.location_id = l.location_id and lower(l.city) = 'oxford');

select last_name, department_id, job_id from employees where employee_id in
(select e.employee_id from employees e, departments d, locations l where e.department_id = d.department_id and d.location_id = l.location_id and lower(l.city) = 'toronto');

select max(salary) "Maxim", min(salary) "Minim", sum(salary) "Suma", round(avg(salary)) "Media", count(*) from employees;

select job_id Job, max(salary) Maxim, min(salary) Minim, sum(salary) Suma, round(avg(salary)) Media, count(employee_id) from employees group by job_id;

select department_name "Nume Dep", city "Oras", count(employee_id) "Nr. angajati", nvl(round(avg(salary)), 0) "Salariu mediu" from employees right join departments using (department_id) join locations using (location_id) group by department_id, department_name, city;

select employee_id, last_name from employees where salary >
(select avg(salary) from employees)
order by salary desc;
--18
select manager_id, min(salary) from employees where manager_id is not null group by manager_id having min(salary) > 1000 order by min(salary) desc;
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
select d.department_id, d.department_name, nvl(sum(e.salary),0)
from departments d left join employees e on (d.department_id = e.department_id)
group by d.department_id, d.department_name;

--22
SELECT MAX(AVG(salary))
FROM employees
GROUP BY department_id;

--23
SELECT job_id, job_title, AVG(salary)
FROM employees join jobs using (job_id)
group by job_id, job_title
HAVING AVG(salary) = (select min(avg(salary))
                      from employees
                      group by job_id);


--24
select avg(salary)
from employees
having avg(salary) > 2500;



