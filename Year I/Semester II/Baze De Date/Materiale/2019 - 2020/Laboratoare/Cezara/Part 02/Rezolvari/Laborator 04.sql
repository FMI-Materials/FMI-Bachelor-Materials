select first_name, hire_date, to_char(hire_date, 'dy') as "Zi" from employees order by mod(to_number(to_char(hire_date, 'd')+5), 7) asc;

select first_name, nvl(to_char(commission_pct), 'Fara comision') as "Comision" from employees;

select first_name, salary, commission_pct from employees where (salary+salary*nvl(commission_pct, 0))>10000;

select first_name, job_id, salary, case job_id 
when 'IT_PROG' then (salary+0.2*salary) 
when 'SA_REP' then (salary+0.25*salary)
when 'SA_MAN' then (salary+0.35*salary)
else salary
end 
as "Salariu renegociat" from employees;

select first_name, employee_id, department_name from employees e, departments d where d.department_id = e.department_id;

select j.job_id, j.job_title from jobs j, employees e where e.department_id = 30 and e.job_id = j.job_id;

select first_name, d.department_name, l.city from employees e, departments d, locations l where e.department_id = d.department_id and e.commission_pct is not null and l.location_id = d.location_id;

select first_name, departments.department_name, locations.city from employees join departments using (department_id) join locations using(location_id) where employees.commission_pct is not null;

select last_name, departments.department_name from employees join departments using (department_id) where lower(last_name) like '%a%';

select first_name, j.job_title, d.department_name from employees e join departments d using (department_id) join locations l using(location_id) join jobs j using(job_id) where lower(l.city) = ‘oxford’;

select e.job_id "Ang#", e.last_name "Angajat" , m.job_id "Mgr#" , m.last_name "Manager"
from employees e, employees m
where e.manager_id = m.employee_id;

select e.job_id "Ang#", e.last_name "Angajat" , m.job_id "Mgr#" , m.last_name "Manager"
from employees e, employees m;

