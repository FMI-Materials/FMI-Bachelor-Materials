--Laborator 4
select last_name, salary
from employees
where manager_id = ( SELECT employee_id
                    		FROM employees  
                     		where manager_id is NULL);
                            
--7
select e.last_name, d.department_name, e.salary from employees e, departments d where (e.department_id = d.department_id) and e.commission_pct is null
and e.manager_id in (select e2.employee_id from employees e2 where e2.commission_pct is not null);

--8
select last_name, department_id, salary, job_id
from employees e
where (e.salary, e.commission_pct) in (select salary, commission_pct
                                       from employees t, departments d, locations l
                                       where t.department_id = d.department_id
                                       and d.location_id = l.location_id
                                       and lower(l.city) = 'oxford');
                                       
--9
--Constantin
select last_name, department_id, job_id
from employees
where employee_id in(
    select e.employee_id
    from employees e, departments d, locations l
    where e.department_id = d.department_id and
        d.location_id = l.location_id and
        lower(l.city) = 'toronto'
);


--12+13
select job_id Job, max(salary) Maxim, min(salary) Minim, sum(salary) Suma, round(avg(salary)) Media, count(employee_id)
from employees
group by job_id;

--14
select count(distinct manager_id) from employees;

--15
select max(salary) - min(salary) "Diferente" 
from employees;

--16
select department_name, city, count(employee_id), nvl(avg(salary), 0)
from employees right join departments using (department_id) join locations using(location_id)
group by department_id, department_name, city;

--17
select employee_id, last_name
from employees
where salary > (
    select avg(salary)
    from employeess
)
order by salary desc;

--18
select m.employee_id, e.salary
from employees m, employees e
where e.manager_id = e.employee_id and
    e.salary = (
        select min(salary)
        from employees
        where manager_id = m.employee_id
    ) and
    e.salary > 1000
order by e.salary desc;




