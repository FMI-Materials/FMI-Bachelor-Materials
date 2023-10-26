--met 1
SELECT *
FROM project p
WHERE NOT EXISTS
    (SELECT 1
     FROM employees e
     WHERE employee_id in (select employee_id
                           from job_history
                           having count(job_id) = 2
                           group by employee_id
                          )
     AND NOT EXISTS
        (SELECT 'x'
        FROM works_on b
        WHERE p.project_id=b.project_id
        AND b.employee_id=e.employee_id));

--met 2
SELECT project_id, project_name
FROM works_on join project using (project_id)
WHERE employee_id IN
    (select employee_id
     from job_history
     having count(job_id) = 2
     group by employee_id)
GROUP BY project_id, project_name
HAVING COUNT(employee_id)=
    (SELECT count(COUNT(*))
     FROM job_history
     having count(job_id) = 2
     group by employee_id);\

--4
select c.country_name, count(e.employee_id), count (distinct department_id)
from employees e right outer join departments d using (department_id) right join locations l using (location_id) right join countries c using (country_id)
group by country_id, c.country_name;




-- ex 3
select COUNT (*)
FROM employees e
WHERE (select count (job_id)
        FROM (SELECT employee_id, job_id
            FROM job_history
            UNION
            SELECT employee_id, job_id
            FROM employees)
        WHERE employee_id = e.employee_id) >= 3;


--ex 5
--angajatii care au lucrat la cel putin doua proiecte nelivrate
WITH nelivrate AS (SELECT project_id
                   FROM project
                   WHERE NVL(delivery_date, sysdate) > deadline)
SELECT *
FROM employees e
WHERE (SELECT COUNT(*) 
       FROM WORKS_ON
       WHERE employee_id = e.employee_id AND project_id IN (SELECT * FROM nelivrate)) > 1;

-- a doua varianta
--WITH nelivrate AS (SELECT project_id
--                   FROM project
--                   WHERE NVL(delivery_date, sysdate) > deadline)
SELECT e.employee_id,  e.last_name, e.first_name
FROM employees e JOIN works_on w ON (e.employee_id = w.employee_id) JOIN project p ON (w.project_id = p.project_id)
WHERE NVL(delivery_date, sysdate) > deadline
GROUP BY e.employee_id, e.last_name, e.first_name
HAVING COUNT(w.project_id) > 1;

--ex 6

select e.employee_id,w.project_id
from employees e left join works_on w on(e.employee_id = w.employee_id);

--ex 7
with manageri as(select project_manager from project),
dep_manageri as(select department_id from employees where employee_id in (select * from manageri))
select * 
from employees
where department_id in (select* from dep_manageri);

--ex 8 
with manageri as(select project_manager from project),
dep_manageri as(select nvl(department_id,-1) from employees where employee_id in (select * from manageri))
select * 
from employees
where department_id not in (select* from dep_manageri) or department_id is NULL;


--- ex 7 & 8 cu cereri sincronizate
--ex 7
with manageri as(select project_manager from project),
dep_manageri as(select department_id from employees where employee_id in (select * from manageri))
select * 
from employees e
where EXISTS ( SELECT *
               FROM dep_manageri
               WHERE e.department_id = department_id);

--ex 8 
with manageri as(select project_manager from project),
dep_manageri as(select nvl(department_id,-1) department_id from employees where employee_id in (select * from manageri))
select * 
from employees e
where NOT EXISTS (SELECT *
              FROM dep_manageri
              WHERE e.department_id = department_id) OR e.department_id IS NULL;


-- ex9
select department_id
from employees
group by department_id
having avg(salary) > &p;

-- ex 10
select e.first_name, e.last_name, e.salary, (select count(*) from works_on where employee_id = e.employee_id) + 
(select count(*) from project where e.employee_id = project_manager and project_id not in (select project_id from works_on where employee_id = e.employee_id)) as nr_proiecte
from employees e
where 2 = (select count(*) from project where e.employee_id = project_manager);

select e.first_name, e.last_name, e.salary, count(project_id)
from employees e join (select employee_id, project_id from works_on union select project_manager, project_id from project) t on (e.employee_id = t.employee_id)
where 2 = (select count(*) from project where e.employee_id = project_manager)
group by e.first_name, e.last_name, e.salary;

--11
SELECT DISTINCT a.employee_id, e.last_name, e.first_name
FROM works_on a join employees e on (a.employee_id = e.employee_id)
WHERE NOT EXISTS ( (SELECT w.project_id FROM works_on w where w.employee_id = a.employee_id) 
MINUS (SELECT p.project_id FROM project p
WHERE p.project_manager = 102));


-- 12 a
with projects_200 as (select project_id
                    from works_on
                    where employee_id = 200)
select last_name
from employees e
where not exists(select project_id
        from projects_200
        
        minus
        
        select project_id
        from works_on w
        where w.employee_id = e.employee_id);

-- 12 b
with projects_200 as (select project_id
                    from works_on
                    where employee_id = 200)
select last_name
from employees e
where not exists(
        select project_id
        from works_on w
        where w.employee_id = e.employee_id
        
        minus
        
        select project_id
        from projects_200);

-- 13
with projects_200 as (select project_id
                    from works_on
                    where employee_id = 200)
select last_name
from employees e
where not exists(
        select project_id
        from works_on w
        where w.employee_id = e.employee_id
        
        minus
        
        select project_id
        from projects_200)
    and
    not exists(select project_id
        from projects_200
        
        minus
        
        select project_id
        from works_on w
        where w.employee_id = e.employee_id);

--ex 14
select * from job_grades;
select first_name, last_name, salary, (select grade_level from job_grades where e.salary>lowest_sal and e.salary<highest_sal) from employees e;

