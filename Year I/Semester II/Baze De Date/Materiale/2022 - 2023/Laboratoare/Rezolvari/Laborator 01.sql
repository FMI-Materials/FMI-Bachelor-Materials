-- 2
DESC EMPLOYEES;

-- 3
SELECT *
FROM EMPLOYEES;

-- 4
SELECT employee_id, last_name, job_id, hire_date
FROM EMPLOYEES;

-- 5
SELECT job_id
FROM EMPLOYEES;

SELECT UNIQUE job_id
FROM EMPLOYEES;

-- 6
SELECT last_name || ', ' || first_name || ', ' || job_id "Detalii Angajat"
FROM EMPLOYEES;

-- 7
SELECT last_name, salary
FROM EMPLOYEES
WHERE salary > 2850;

-- 8
SELECT last_name, department_id
FROM EMPLOYEES
where employee_id = 104;

-- 9
SELECT last_name, salary
FROM EMPLOYEES
WHERE salary NOT BETWEEN 14000 AND 24000;

SELECT last_name, first_name, salary
FROM EMPLOYEES
WHERE salary BETWEEN 3000 AND 7000;

SELECT last_name, first_name, salary
FROM EMPLOYEES
WHERE salary >= 3000 AND salary <= 7000;

-- 10
SELECT last_name, job_id, hire_date
FROM EMPLOYEES
WHERE hire_date BETWEEN '20-FEB-1987' AND '1-MAY-1989'
ORDER BY hire_date;

-- 11
SELECT last_name, employee_id
FROM EMPLOYEES
WHERE department_id IN (10, 30)
ORDER BY last_name;

-- 12
SELECT last_name "Angajat", salary "Salariu lunar"
FROM EMPLOYEES
WHERE department_id IN (10, 30) AND salary > 1500
ORDER BY last_name;

-- 13
SELECT sysdate
FROM DUAL;

SELECT TO_CHAR(sysdate, 'DD-MM-YYYY HH24:MI:SS')
FROM DUAL;

-- 14
SELECT last_name, hire_date
FROM EMPLOYEES
WHERE hire_date LIKE ('%87');

SELECT last_name, hire_date
FROM EMPLOYEES
WHERE TO_CHAR(hire_date, 'YYYY') = '1987';

-- 15
SELECT last_name, job_id
FROM EMPLOYEES
WHERE manager_id IS NULL;

-- 16
SELECT last_name, SALARY, commission_pct
FROM EMPLOYEES
WHERE commission_pct IS NOT NULL
ORDER BY salary DESC, commission_pct DESC;

-- 17
SELECT last_name, SALARY, commission_pct
FROM EMPLOYEES
ORDER BY salary DESC, commission_pct DESC;

-- 18
SELECT last_name
FROM EMPLOYEES
WHERE UPPER(last_name) LIKE '__A%';

-- 19
SELECT last_name
FROM EMPLOYEES
WHERE (UPPER(last_name) LIKE '%L%L%' AND department_id = 30) OR manager_id = 102;

-- 20
SELECT last_name, job_id, salary
FROM EMPLOYEES
WHERE (UPPER(job_id) LIKE '%CLERK%' OR UPPER(job_id) LIKE '%REP%') AND salary NOT IN (1000, 2000, 3000);