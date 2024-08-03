SELECT department_id, job_id, SUM(salary)
FROM employees
GROUP BY department_id, job_id;
--2
select department_id, job_id,department_name,job_title, sum(salary)
from employees
join departments using (department_id)
join jobs using (job_id)
group by department_id, job_id, department_name, job_title;
--3
Select department_name, min(salary) from employees join departments using (department_id)
group by department_name having avg(salary) = (select max(avg(salary)) from employees group by department_id);
--4
select e.department_id, d.department_name, count(*)
from employees e, departments d
where e.department_id = d.department_id
group by e.department_id, d.department_name
having count(*) < 4;
--5
select employee_id, last_name, hire_date
from employees
where to_char(hire_date, 'DD') = (
    select max(count(*))
    from employees
    group by to_char(hire_date, 'DD'));
--6
select count(count(*))
from employees
group by department_id
having count(*) >= 15;
--7
select department_id, sum(salary)
from employees
where department_id != 30
group by department_id
having count(*) > 10
order by department_id, sum(salary);
--8
select d.department_id, d.department_name,
count(e.employee_id), avg(e.salary),
e2.first_name, e2.salary, e2.job_id
from departments d left join employees e on (e.department_id = d.department_id) 
Left join employees e2 on (e2.department_id = d.department_id)
group by e.department_id, d.department_name, e2.first_name, e2.salary, e2.job_id;

--9
select d.department_id, l.city, d.department_name, nvl(sum(e.salary), 0)
from departments d, locations l, employees e
where e.department_id(+) = d.department_id 
and d.location_id=l.location_id(+)
and d.department_id > 80
group by d.department_id, d.department_name, l.city;
--10 modificat
--Pb 10 completata: informatii despre angajatii care au avut cel putin 3 job-uri (inclusiv cel curent), fara a considera duplicatele.
select e.employee_id, e.first_name 
from employees e
join job_history j on (j.employee_id = e.employee_id and j.job_id != e.job_id)
having count(distinct j.job_id) >= 2
group by e.employee_id, e.first_name;
--12 
select job_id, 
       nvl(sum(case department_id when 30 then salary end), 0) "Dep30",
      nvl( sum(case department_id when 50 then salary end), 0) "Dep50",
       nvl(sum(case department_id when 80 then salary end),0) "Dep80",
       sum(salary) Total
from employees
group by job_id;

--13
select count(employee_id), count(decode(to_char(hire_date, 'yyyy'),'1997',1)) as "1997",
count(decode(to_char(hire_date, 'yyyy'),'1998',1)) as "1998",
count(decode(to_char(hire_date, 'yyyy'),'1999',1)) as "1999",
count(decode(to_char(hire_date, 'yyyy'),'2000',1)) as "2000"
from employees;


--14
SELECT department_id, department_name,nvl(a.suma, 0)
FROM departments d left join (SELECT department_id ,SUM(salary) suma
                     FROM employees
                     GROUP BY department_id) a using(department_id); 
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
SELECT department_name, last_name, min_sal
FROM departments d, employees e, (SELECT department_id, min(salary) min_sal
                                  FROM employees
                                  GROUP BY department_id) a
WHERE e.department_id(+)=d.department_id and d.department_id = a.department_id(+)
and nvl(e.salary, -1) = nvl(a.min_sal, -1);



