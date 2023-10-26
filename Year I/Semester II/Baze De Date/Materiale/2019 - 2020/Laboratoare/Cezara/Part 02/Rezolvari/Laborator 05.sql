--23

--25
select e.last_name, e.job_id, j.job_title, d.department_name, e.salary 
from employees e, departments d, jobs j where e.job_id = j.job_id and e.department_id = d.department_id(+);


select e.last_name, e.job_id, d.department_name, e.salary 
from employees e left join departments d on (e.department_id = d.department_id);

--26

select e1.last_name, e1.hire_date from employees e1, employees e2 
where lower(e2.last_name) = 'gates' and e1.hire_date > e2.hire_date;

--27
select e1.last_name as Angajat, e1.hire_date as Data_ang, e1.manager_id as Manager, e2.hire_date as Data_mgr from employees e1, employees e2 
where e1.manager_id = e2.employee_id and e1.hire_date < e2.hire_date;

---Lab 3
--1
SELECT e1.last_name, TO_CHAR(e1.hire_date, 'MONTH') AS "Luna",
EXTRACT(YEAR FROM e1.hire_date) as "An"
FROM employees e1, employees e2
WHERE e1.department_id = e2.department_id
 AND LOWER(e1.last_name) LIKE '%a%'
 AND LOWER(e1.last_name) != 'gates'
 AND LOWER(e2.last_name) = 'gates';
 
SELECT e1.last_name, TO_CHAR(e1.hire_date, 'MONTH') AS "Luna",
EXTRACT(YEAR FROM e1.hire_date) as "An"
FROM employees e1
JOIN employees e2
ON (e1.department_id = e2.department_id)
WHERE LOWER(e1.last_name) LIKE '%a%'
 AND LOWER(e1.last_name) != 'gates'
 AND LOWER(e2.last_name) = 'gates';
 
SELECT e1.last_name, TO_CHAR(e1.hire_date, 'MONTH') AS "Luna",
EXTRACT(YEAR FROM e1.hire_date) as "An"
FROM employees e1
JOIN employees e2
ON (e1.department_id = e2.department_id)
WHERE INSTR(LOWER(e1.last_name), 'a') != 0
 AND LOWER(e1.last_name) != 'gates'
 AND LOWER(e2.last_name) = 'gates';

---------------
SELECT e1.last_name, TO_CHAR(e1.hire_date, 'MONTH') AS "Luna",
EXTRACT(YEAR FROM e1.hire_date) as "An"
FROM employees e1
JOIN employees e2
using (department_id)
where (INSTR(LOWER(e1.last_name), 'a') != 0
 AND LOWER(e1.last_name) != 'gates'
 AND LOWER(e2.last_name) = 'gates');
 --------------------
 
 --3
 SELECT e.last_name, e.salary, j.job_title, l.city,
 c.country_name
FROM employees e
JOIN employees m on (e.manager_id = m.employee_id)
JOIN jobs j on (e.job_id = j.job_id)
JOIN departments d on (e.department_id = d.department_id)
JOIN locations l ON (l.location_id = d.location_id)
JOIN countries c ON (c.country_id = l.country_id)
WHERE m.last_name = 'Zlotkey';

select * from employees
--where last_name='Grant';
where employee_id=149;

SELECT e.last_name, e.salary, j.job_title, l.city,
 c.country_name
FROM employees e
JOIN employees m on (e.manager_id = m.employee_id)
JOIN jobs j on (e.job_id = j.job_id)
LEFT JOIN departments d on (e.department_id = d.department_id)
LEFT JOIN locations l ON (l.location_id = d.location_id)
LEFT JOIN countries c ON (c.country_id = l.country_id)
WHERE m.last_name = 'Zlotkey';

select e1.last_name, e1.salary, j.job_title, l.city, c.country_name
from employees e1, employees e2, jobs j, departments d, locations l, countries c
where (e2.last_name = 'Zlotkey'  and
    e1.manager_id = e2.employee_id and
    e1.job_id = j.job_id and
    e1.department_id = d.department_id (+) and
    d.location_id = l.location_id (+) and
    l.country_id = c.country_id (+) );

 --7
SELECT e.last_name, d.department_name
FROM employees e, departments d
WHERE e.department_id = d.department_id (+);

SELECT e.last_name, d.department_name
FROM employees e
LEFT OUTER JOIN departments d ON (e.department_id =
d.department_id);

--8
SELECT e.last_name, d.department_name
FROM employees e, departments d
WHERE e.department_id(+) = d.department_id;

SELECT e.last_name, d.department_name
FROM employees e
RIGHT OUTER JOIN departments d ON (e.department_id =
d.department_id);

--9
SELECT e.employee_id, e.last_name, d.department_name
FROM employees e, departments d
WHERE e.department_id = d.department_id (+)
union
SELECT e.employee_id, e.last_name, d.department_name
FROM employees e, departments d
WHERE e.department_id(+) = d.department_id;

SELECT e.last_name, d.department_name
FROM employees e
full OUTER JOIN departments d ON (e.department_id =
d.department_id);

--10
SELECT D.DEPARTMENT_ID
FROM DEPARTMENTS D
WHERE LOWER(D.DEPARTMENT_NAME) LIKE '%re%'
UNION all
SELECT DEPARTMENT_ID
FROM EMPLOYEES E
WHERE E.JOB_ID='SA_REP';

--11
SELECT d.department_id
FROM departments d
MINUS
SELECT UNIQUE department_id
FROM employees;

SELECT department_id
FROM departments
WHERE department_id NOT IN
    (
    SELECT d.department_id
    FROM departments d
    --where department_id is not null
    JOIN employees e ON(d.department_id=e.department_id)
    );
    
--12
SELECT d.department_id
FROM departments d
WHERE LOWER(d.department_name) LIKE '%re%'
INTERSECT
SELECT e.department_id
FROM employees e
WHERE e.job_id = 'HR_REP';

--13
SELECT e.employee_id, e.job_id, e.last_name
FROM employees e
WHERE (e.salary > 3000)
UNION
SELECT e.employee_id, e.job_id, e.last_name
FROM employees e
JOIN jobs j ON (j.job_id = e.job_id)
WHERE e.salary = (j.min_salary + j.max_salary) / 2;
LOWER(e2.last_name) LIKE '%t%'
ORDER BY e1.last_name;


--3
SELECT e.last_name, e.salary, j.job_title, l.city, c.country_name
FROM employees e
LEFT JOIN employees m on (e.manager_id = m.employee_id)
LEFT JOIN jobs j on (e.job_id = j.job_id)
LEFT JOIN departments d on (e.department_id = d.department_id)
LEFT JOIN locations l ON (l.location_id = d.location_id)
LEFT JOIN countries c ON (c.country_id = l.country_id)
where m.last_name = 'Zlotkey';

--4
select d.department_id, d.department_name, e.last_name,
    j.job_title, to_char(e.salary, '$99,999.00') Salariu
from employees e, departments d, jobs j
where (lower(d.department_name) like '%ti%' and
    e.department_id = d.department_id and
    e.job_id = j.job_id)
order by d.department_name, e.last_name;

--5
select e.last_name, e.department_id, d.department_name, 
    l.city, j.job_title
from employees e, departments d, jobs j, locations l
where (l.city = 'Oxford' and
    e.department_id = d.department_id and
    d.location_id = l.location_id and
    e.job_id = j.job_id);

--6
select unique e.employee_id, e.last_name, e.salary, j.max_salary, j.min_salary
from employees e, employees e2, jobs j
where (e.department_id = e2.department_id and
    lower(e2.last_name) like '%t%' and
    e.job_id = j.job_id and
    e.salary > (j.max_salary + j.min_salary ) / 2)
order by e.salary;

