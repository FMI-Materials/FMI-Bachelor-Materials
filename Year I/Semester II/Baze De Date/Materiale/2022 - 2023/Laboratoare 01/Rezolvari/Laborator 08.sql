-- 1
-- a)
SELECT last_name, salary, department_id
FROM EMPLOYEES
WHERE salary > (
                    SELECT ROUND(AVG(salary))
                    FROM EMPLOYEES
               );

-- b)
SELECT last_name, salary, department_id
FROM EMPLOYEES e
WHERE salary > (
                    SELECT ROUND(AVG(salary))
                    FROM EMPLOYEES
                    WHERE department_id = e.department_id
               );

-- c)
SELECT last_name, salary, e.department_id, department_name, 
                                                            (
                                                                SELECT ROUND(AVG(salary))
                                                                FROM EMPLOYEES
                                                                WHERE department_id = e.department_id
                                                            ) "Media salariilor",
                                                            (
                                                                SELECT COUNT(employee_id)
                                                                FROM EMPLOYEES
                                                                WHERE department_id = e.department_id
                                                            ) "Nr. Angajati"
FROM EMPLOYEES e
JOIN DEPARTMENTS d ON(e.department_id = d.department_id);

-- 2
SELECT last_name, salary
FROM EMPLOYEES
WHERE salary > ALL (
                        SELECT ROUND(AVG(salary))
                        FROM EMPLOYEES
                        GROUP BY department_id
                   );


SELECT last_name, salary
FROM EMPLOYEES
WHERE salary > (
                    SELECT ROUND(MAX(AVG(salary)))
                    FROM EMPLOYEES
                    GROUP BY department_id
               );

-- 3
SELECT last_name, salary, department_id
FROM EMPLOYEES e
WHERE salary = (
                    SELECT MIN(salary)
                    FROM EMPLOYEES
                    WHERE department_id = e.department_id
               );

-- 4
SELECT last_name, salary
FROM EMPLOYEES
WHERE department_id IN (
                            SELECT department_id
                            FROM EMPLOYEES
                            WHERE salary = (
                                                SELECT MAX(salary)
                                                FROM EMPLOYEES
                                                WHERE department_id = 30
                                           )
                       );

-- 5
-- a)
SELECT employee_id, last_name, first_name
FROM EMPLOYEES
WHERE employee_id IN (
                        SELECT manager_id
                        FROM EMPLOYEES
                        GROUP BY manager_id
                        HAVING COUNT(employee_id) > 2
                    );

-- b)
SELECT employee_id, last_name, first_name,
                                           (
                                                SELECT COUNT(employee_id)
                                                FROM EMPLOYEES
                                                WHERE manager_id = e.employee_id
                                           ) "Nr subalterni"
FROM EMPLOYEES e;

-- 6
SELECT location_id
FROM LOCATIONS
INTERSECT
SELECT location_id
FROM DEPARTMENTS;

SELECT location_id
FROM LOCATIONS
WHERE location_id IN (
                        SELECT DISTINCT location_id  
                        FROM DEPARTMENTS
                     );

SELECT location_id
FROM LOCATIONS l
WHERE EXISTS (
                SELECT 'x'
                FROM DEPARTMENTS
                WHERE location_id = l.location_id
             );

-- 7
SELECT department_id, department_name
FROM DEPARTMENTS d
WHERE NOT EXISTS (
                    SELECT 'x'
                    FROM EMPLOYEES
                    WHERE department_id = d.department_id
                 );

-- 8
WITH 
val_dep AS 
(
    SELECT department_name, SUM(salary) AS total
    FROM DEPARTMENTS d
    JOIN EMPLOYEES e ON(d.department_id = e.department_id)
    GROUP BY department_name
),
val_medie AS 
(
    SELECT SUM(total) / COUNT(*) AS medie
    FROM val_dep
)
SELECT *
FROM val_dep
WHERE total > 
              (
                SELECT medie
                FROM val_medie
              )
ORDER BY department_name;

-- 9
WITH
subord_SK AS
(
    SELECT employee_id, first_name, last_name, hire_date
    FROM EMPLOYEES
    WHERE manager_id IN (
                            SELECT employee_id
                            FROM EMPLOYEES  
                            WHERE INITCAP(CONCAT(first_name, last_name)) = 'Stevenking'
                        )
         AND TO_CHAR(hire_date, 'YYYY') != '1970'
)
SELECT employee_id, first_name, last_name, hire_date
FROM subord_SK
WHERE hire_date = (
                    SELECT MIN(hire_date)
                    FROM subord_SK
                  );

-- 10
SELECT employee_id, last_name, salary, rownum
FROM 
(
    SELECT employee_id, salary, last_name
    FROM EMPLOYEES
    ORDER BY salary DESC
)
WHERE rownum <= 10
ORDER BY salary;

-- 11
SELECT employee_id, last_name, first_name, salary, rownum
FROM
(
    SELECT employee_id, last_name, first_name, salary
    FROM EMPLOYEES
    ORDER BY salary DESC
)
WHERE rownum <= 3
ORDER BY salary DESC;

-- 12
SELECT 'Departamentul ' || department_name || ' este condus de ' || NVL(TO_CHAR(manager_id), 'nimeni') || ' si ' ||
                                                                CASE (
                                                                            SELECT COUNT(employee_id)
                                                                            FROM EMPLOYEES 
                                                                            WHERE department_id = d.department_id
                                                                     )
                                                                WHEN 0 THEN 'nu are salariati'
                                                                ELSE 'are numarul de salariati ' || TO_CHAR((
                                                                            SELECT COUNT(employee_id)
                                                                            FROM EMPLOYEES 
                                                                            WHERE department_id = d.department_id
                                                                     ))
                                                                END "Informatii"
FROM DEPARTMENTS d;

-- 13
SELECT CASE LENGTH(last_name)
WHEN LENGTH(first_name) THEN last_name || ' ' || first_name
ELSE last_name || ' ' || first_name || ' ' || LENGTH(first_name)
END "Informatii"
FROM EMPLOYEES e;

-- 14
SELECT last_name, hire_date, salary, 
                                    CASE TO_CHAR(hire_date, 'yyyy')
                                        WHEN '1989' THEN salary * 1.20
                                        WHEN '1990' THEN salary * 1.15
                                        WHEN '1991' THEN salary * 1.10
                                        ELSE salary
                                    END "Salariu marit"
FROM EMPLOYEES;

-- 15
-- a)
SELECT job_title, CASE SUBSTR(job_title, 1, 1)
            WHEN 'S' THEN (
                            SELECT SUM(salary)
                            FROM EMPLOYEES
                            WHERE job_id = j.job_id
                          )
            ELSE 0
       END "Suma salariilor"
FROM JOBS j
ORDER BY 1 DESC;

-- b)
SELECT job_id, ROUND(AVG(salary))
FROM EMPLOYEES
GROUP BY job_id
HAVING SUM(salary) = (
                    SELECT MAX(SUM(salary))
                    FROM EMPLOYEES
                    GROUP BY job_id
                );