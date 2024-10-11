-- 1
SELECT last_name, TO_CHAR(hire_date, 'Month YYYY')
FROM EMPLOYEES
WHERE UPPER(last_name) LIKE '%A%'
      AND INITCAP(last_name) != 'Gates'
      AND department_id = (
                              SELECT department_id
                              FROM EMPLOYEES
                              WHERE INITCAP(last_name) = 'Gates'
                          );

-- 2
SELECT e.employee_id, e.last_name, e.department_id, department_name
FROM EMPLOYEES e
JOIN EMPLOYEES c ON (e.department_id = c.department_id)
JOIN DEPARTMENTS d ON (e.department_id = d.department_id)
WHERE UPPER(c.last_name) LIKE '%T%'
      AND (e.employee_id != c.employee_id)
ORDER BY 2;

-- 3
SELECT last_name, salary, job_title, city, country_name
FROM EMPLOYEES e
JOIN JOBS USING (job_id)
JOIN DEPARTMENTS USING (department_id)
JOIN LOCATIONS USING (location_id)
JOIN COUNTRIES USING (country_id)
WHERE e.manager_id IN (
                        SELECT employee_id
                        FROM EMPLOYEES
                        WHERE INITCAP(last_name) = 'King'
                      );

-- 4
SELECT department_id, department_name, last_name, job_id, TO_CHAR(salary, '$99,999.00')
FROM DEPARTMENTS
JOIN EMPLOYEES USING (department_id)
WHERE UPPER(department_name) LIKE '%TI%'
ORDER BY 2, 3;

-- 5
SELECT last_name || ' ' || first_name "Nume prenume", department_name "Departament"
FROM EMPLOYEES
LEFT JOIN DEPARTMENTS USING (department_id)
UNION
SELECT last_name || ' ' || first_name, department_name
FROM EMPLOYEES
RIGHT JOIN DEPARTMENTS USING (department_id);

SELECT last_name || ' ' || first_name "Nume prenume", department_name "Departament"
FROM EMPLOYEES
FULL JOIN DEPARTMENTS USING (department_id);

-- 6
SELECT department_id
FROM DEPARTMENTS
WHERE UPPER(department_name) like '%RE%'
UNION
SELECT department_id
FROM EMPLOYEES
WHERE UPPER(job_id) = 'SA_REP';

-- 7
SELECT department_id
FROM DEPARTMENTS
WHERE UPPER(department_name) like '%RE%'
UNION ALL
SELECT department_id
FROM EMPLOYEES
WHERE UPPER(job_id) = 'SA_REP';

-- 8
SELECT department_id
FROM DEPARTMENTS
MINUS
SELECT department_id
FROM EMPLOYEES;

SELECT department_id
FROM EMPLOYEES
RIGHT JOIN DEPARTMENTS USING (department_id)
WHERE employee_id IS NULL;

-- 9
SELECT department_id
FROM DEPARTMENTS
WHERE UPPER(department_name) LIKE '%RE%'
INTERSECT
SELECT department_id
FROM EMPLOYEES
WHERE UPPER(job_id) = 'HR_REP';