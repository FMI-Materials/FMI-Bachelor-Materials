-- 2
SELECT MAX(salary) Maxim, MIN(salary) Minim, SUM(salary) Suma, ROUND(AVG(salary)) Media
FROM EMPLOYEES;

-- 3
SELECT e.job_id, job_title, MAX(salary) Maxim, MIN(salary) Minim, SUM(salary) Suma, ROUND(AVG(salary)) Media
FROM EMPLOYEES e
JOIN JOBS j ON(e.job_id = j.job_id)
GROUP BY e.job_id, job_title;

-- 4
SELECT NVL(TO_CHAR(department_id), 'Angajat fara departament'), COUNT(employee_id)
FROM EMPLOYEES
GROUP BY department_id;

-- 5
SELECT COUNT(DISTINCT manager_id) "Nr. manageri"
FROM EMPLOYEES;

-- 6
SELECT MAX(salary) - MIN(salary) Diferenta
FROM EMPLOYEES;

SELECT department_id, MAX(salary) - MIN(salary) Diferenta
FROM EMPLOYEES
WHERE department_id IS NOT NULL
GROUP BY department_id;

-- 7
SELECT department_name "Nume departament", d.location_id Locatie, COUNT(employee_id) "Nr. Angajati", ROUND(AVG(salary)) "Salariul mediu"
FROM EMPLOYEES e
JOIN DEPARTMENTS d ON(e.department_id = d.department_id)
JOIN LOCATIONS l ON(d.location_id = l.location_id)
GROUP BY department_name, d.location_id;

-- 8
SELECT employee_id, last_name
FROM EMPLOYEES
WHERE salary > (
                    SELECT ROUND(AVG(salary))
                    FROM EMPLOYEES
               )
ORDER BY salary DESC;

-- 9
SELECT manager_id, min(salary)
FROM EMPLOYEES
WHERE manager_id IS NOT NULL
GROUP BY manager_id
HAVING min(salary) > 1000
ORDER BY 2 DESC;

-- 10
SELECT e.department_id, department_name, max(salary)
FROM EMPLOYEES e
JOIN DEPARTMENTS d ON(e.department_id = d.department_id)
GROUP BY e.department_id, department_name
HAVING max(salary) >= 3000;

-- 11
SELECT MIN(ROUND(AVG(salary))) "Salariu mediu minim"
FROM EMPLOYEES
GROUP BY job_id;

-- 12
SELECT MAX(ROUND(AVG(salary))) "Salariu mediu maxim"
FROM EMPLOYEES
GROUP BY department_id;

-- 13
SELECT e.job_id, job_title, AVG(salary)
FROM EMPLOYEES e
JOIN JOBS j ON(e.job_id = j.job_id)
GROUP BY e.job_id, job_title
HAVING ROUND(AVG(salary)) = (
                        SELECT MIN(ROUND(AVG(salary)))
                        FROM EMPLOYEES
                        GROUP BY job_id
                     );
-- 14
SELECT ROUND(AVG(salary))
FROM EMPLOYEES
HAVING AVG(salary) > 2500;

-- 15
SELECT department_id, job_id, SUM(salary)
FROM EMPLOYEES
GROUP BY department_id, job_id;

-- 16
SELECT d.department_id, department_name, COUNT(employee_id)
FROM EMPLOYEES e
JOIN DEPARTMENTS d ON(e.department_id = d.department_id)
GROUP BY d.department_id, department_name
HAVING COUNT(employee_id) < 4;


SELECT d.department_id, department_name, COUNT(employee_id)
FROM EMPLOYEES e
JOIN DEPARTMENTS d ON(e.department_id = d.department_id)
GROUP BY d.department_id, department_name
HAVING COUNT(employee_id) = (
                                SELECT MAX(COUNT(employee_id))
                                FROM EMPLOYEES
                                GROUP BY department_id
                            );

-- 17
SELECT COUNT(department_id)
FROM
(
    SELECT department_id, COUNT(employee_id) NrAngajati
    FROM EMPLOYEES
    GROUP BY department_id
)
WHERE NrAngajati > 15;

-- 18
SELECT department_id, SUM(salary)
FROM EMPLOYEES
WHERE department_id != 30
GROUP BY department_id
HAVING COUNT(employee_id) > 10
ORDER BY 1;

-- 19
SELECT jh.employee_id, CONCAT(last_name, ' ' || first_name)
FROM JOB_HISTORY jh
JOIN EMPLOYEES e ON(e.employee_id = jh.employee_id)
GROUP BY jh.employee_id, last_name, first_name
HAVING COUNT(jh.job_id) >= 2;

-- 20
SELECT ROUND(SUM(commission_pct) / COUNT(*), 2)
FROM EMPLOYEES;

-- 21
SELECT job_id Job, SUM(DECODE(department_id, 30, salary)) Dep30,
                   SUM(DECODE(department_id, 50, salary)) Dep50,
                   SUM(DECODE(department_id, 80, salary)) Dep80,
                   SUM(salary) Total
FROM EMPLOYEES
GROUP BY job_id;

SELECT job_id, 
              (
                    SELECT SUM(salary)
                    FROM EMPLOYEES
                    WHERE department_id = 30
                    AND job_id = e.job_id
              ) Dep30,
              (
                    SELECT SUM(salary)
                    FROM EMPLOYEES
                    WHERE department_id = 50
                    AND job_id = e.job_id
              ) Dep50,
              (
                    SELECT SUM(salary)
                    FROM EMPLOYEES
                    WHERE department_id = 80
                    AND job_id = e.job_id
              ) Dep80,
              SUM(salary) Total
FROM EMPLOYEES e
GROUP BY job_id;

-- 22
SELECT COUNT(employee_id) "Nr. Total Angajati", COUNT(DECODE(TO_CHAR(hire_date, 'YYYY'), 1997, employee_id)) "1997",
                                                COUNT(DECODE(TO_CHAR(hire_date, 'YYYY'), 1998, employee_id)) "1998",
                                                COUNT(DECODE(TO_CHAR(hire_date, 'YYYY'), 1998, employee_id)) "1999",
                                                COUNT(DECODE(TO_CHAR(hire_date, 'YYYY'), 2000, employee_id)) "2000"
FROM EMPLOYEES;

-- 23
SELECT e.department_id, department_name, SUM(salary)
FROM EMPLOYEES e
JOIN DEPARTMENTS d ON(e.department_id = d.department_id)
GROUP BY e.department_id, department_name;

SELECT d.department_id, department_name, a.suma
FROM DEPARTMENTS d
JOIN
(
    SELECT department_id, SUM(salary) suma
    FROM EMPLOYEES
    GROUP BY department_id
) a ON(a.department_id = d.department_id);

-- 24
SELECT last_name, salary, e.department_id, department_name, sal_med, nr_ang
FROM EMPLOYEES e
JOIN DEPARTMENTS d ON(e.department_id = d.department_id)
JOIN 
(
    SELECT ROUND(AVG(salary)) sal_med, COUNT(employee_id) nr_ang, department_id
    FROM EMPLOYEES
    GROUP BY department_id
) ac ON (ac.department_id = e.department_id);

SELECT last_name, salary, e.department_id, department_name,
                                                            (
                                                                SELECT ROUND(AVG(salary))
                                                                FROM EMPLOYEES
                                                                WHERE department_id = e.department_id
                                                            ) "Salariu mediu",
                                                            (
                                                                SELECT COUNT(employee_id)
                                                                FROM EMPLOYEES
                                                                WHERE department_id = e.department_id
                                                            ) "Nr Angajati"
FROM EMPLOYEES e
JOIN DEPARTMENTS d ON(e.department_id = d.department_id);