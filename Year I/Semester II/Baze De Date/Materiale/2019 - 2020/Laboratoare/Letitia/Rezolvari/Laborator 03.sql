select e1.last_name, to_char(e1.hire_date, 'MONTH') as Luna, extract(year from e1.hire_date) as An from employees e1, employees e2 where e1.department_id = e2.department_id and lower(e1.last_name) like '%a%' and lower(e1.last_name) != 'gates' and lower(e2.last_name) = 'gates';
select e1.last_name, to_char(e1.hire_date, 'MONTH') as Luna, extract(year from e1.hire_date) as An from employees e1 join employees e2 on (e1.department_id = e2.department_id) and lower(e1.last_name) like '%a%' and lower(e1.last_name) != 'gates' and lower(e2.last_name) = 'gates';

select distinct e1.employee_id, e1.last_name, e1.department_id, d.department_name from employees e1, employees e2, departments d where e1.department_id = e2.department_id and lower(e2.last_name) like '%t%';

select e1.last_name, e1.salary, j.job_title, l.city, c.country_name from employees e1 join employees e2 on (e1.manager_id = e2.employee_id) join jobs j on (e1.job_id = j.job_id) left join departments d on (e1.department_id = d.department_id) left join locations l on (l.location_id = d.location_id) left join countries c on (c.country_id = l.country_id) where e2.last_name = 'King';
select e1.last_name, e1.salary, j.job_title, l.city, c.country_name
from employees e1, employees e2, jobs j, departments d, locations l, countries c
where (e2.last_name = 'Zlotkey'  and
    e1.manager_id = e2.employee_id and
    e1.job_id = j.job_id and
    e1.department_id = d.department_id (+) and
    d.location_id = l.location_id (+) and
    l.country_id = c.country_id (+) );


SELECT d.department_id, d.department_name, e.last_name, j.job_title, TO_CHAR(e.salary, '$99,999.00') Salariu FROM departments d JOIN employees e ON (e.department_id = d.department_id) JOIN jobs j ON (e.job_id = j.job_id) WHERE LOWER(d.department_name) LIKE '%ti%';

select e.last_name, department_id, d.department_name, l.city, j.job_title from employees e join departments d using (department_id) join locations l using (location_id) join jobs j using (job_id) where lower(l.city) = 'oxford';

select d.department_id from departments d where lower(d.department_name) like '%re'
union
select department_id from employees e where e.job_id = 'SA_REP';

select 'Departamentul ' || d.department_name || ' este condus de ' || NVL(to_char(d.manager_id), 'nimeni') || ' si ' ||
case nvl(e.employee_id, -1)
when -1 then 'nu are salariati'
else 'are salariati '
end
from employees e right outer join departments d on (e.department_id = d.department_id);

select last_name, first_name, length(last_name) from employees where nullif(length(last_name), length(first_name)) is not null; 

select last_name, hire_date, salary, decode(extract(year from hire_date), 1989, salary + 0.2*salary, 1990, salary + 0.15*salary, 1991, salary + 0.1*salary, salary) from employees;