select first_name, e.department_id, d.department_name from employees e, departments d where e.department_id = d.department_id;

select jh.job_id, j.job_title from jobs j, job_history jh where jh.department_id = 30;

select e.first_name, d.department_name, l.city from employees e, departments d, locations l where e.department_id = d.department_id and e.commission_pct is not null and d.location_id = l.location_id;

select e.first_name, d.department_name from employees e, departments d where e.first_name like '%A%';

select e1.employee_id as Ang#, e1.first_name as Angajat, e1.manager_id as Mgr#, e2.last_name as Manager from employees e1, employees e2 where e1.manager_id = e2.employee_id(+); 

select e1.last_name as Nume, e1.department_id as "Cod dep", e2.last_name as Colegi from employees e1, employees e2 where e1.department_id = e2.department_id(+) and e1.employee_id != e2.employee_id order by e1.employee_id;

select e.last_name, e.job_id, j.job_title, d.department_name, e.salary from employees e, departments d, jobs j where e.job_id = j.job_id and e.department_id = d.department_id(+);

select e1.last_name, e1.hire_date from employees e1, employees e2 where lower(e2.last_name) = 'gates' and e1.hire_date > e2.hire_date;

select e1.last_name as Angajat, e1.hire_date as Data_ang, e1.manager_id as Manager, e2.hire_date as Data_mgr from employees e1, employees e2 where e1.manager_id = e2.employee_id and e1.hire_date < e2.hire_date;