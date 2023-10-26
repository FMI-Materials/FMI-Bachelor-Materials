-- 1
SELECT last_name, hire_date
FROM EMPLOYEES
WHERE hire_date > (
                        SELECT hire_date
                        FROM EMPLOYEES
                        WHERE INITCAP(last_name) = 'Gates'
                  );

-- 2
SELECT last_name, salary
FROM EMPLOYEES
WHERE department_id IN (
                            SELECT department_id
                            FROM EMPLOYEES
                            WHERE INITCAP(last_name) = 'Gates'
                       )
      AND INITCAP(last_name) != 'Gates';

SELECT last_name, salary
FROM EMPLOYEES
WHERE department_id IN (
                            SELECT department_id
                            FROM EMPLOYEES
                            WHERE INITCAP(last_name) = 'King'
                       )
      AND INITCAP(last_name) != 'King';

-- 3
SELECT last_name, salary
FROM EMPLOYEES
WHERE manager_id = (
                        SELECT employee_id
                        FROM EMPLOYEES
                        WHERE manager_id IS NULL
                   );

-- 4
SELECT last_name, department_id, salary
FROM EMPLOYEES
WHERE (department_id, salary) IN (
                                    SELECT department_id, salary
                                    FROM EMPLOYEES
                                    WHERE commission_pct IS NOT NULL 
                                 );

-- 5
SELECT employee_id, last_name, salary
FROM EMPLOYEES
WHERE salary > (
                    SELECT AVG(salary)
                    FROM EMPLOYEES
               );

-- 6
SELECT last_name, salary
FROM EMPLOYEES
WHERE salary + salary * NVL(commission_pct, 0) > (
                                                    SELECT MAX(salary)
                                                    FROM EMPLOYEES
                                                    WHERE UPPER(job_id) LIKE ('%CLERK')
                                                 )
ORDER BY salary DESC;

-- 7
SELECT last_name, department_name, salary
FROM EMPLOYEES e
JOIN DEPARTMENTS d ON(e.department_id = d.department_id)
WHERE e.manager_id IN (
                        SELECT employee_id
                        FROM EMPLOYEES
                        WHERE commission_pct IS NULL
                   )
      AND commission_pct IS NOT NULL;

-- 8
SELECT last_name, department_id, job_id
FROM EMPLOYEES
WHERE department_id IN (
                            SELECT department_id
                            FROM DEPARTMENTS d
                            JOIN LOCATIONS l ON(d.location_id = l.location_id
                                                AND INITCAP(city) = 'Toronto')
                       );

-- 9
SELECT department_id
FROM DEPARTMENTS
WHERE department_id NOT IN ( 
                                SELECT department_id
                                FROM EMPLOYEES
                                WHERE department_id IS NOT NULL
                           );

SELECT department_id
FROM DEPARTMENTS
WHERE department_id NOT IN (
                                SELECT NVL(department_id, -1)
                                FROM EMPLOYEES
                           );

-- 10
INSERT INTO EMP_ANE (employee_id, last_name, email, hire_date, job_id, salary, commission_pct)
VALUES (252, 'Nume252', 'nume252@emp.com', SYSDATE, 'SA_REP', 5000, NULL);

SELECT employee_id, last_name, email, hire_date, job_id, salary, commission_pct
FROM EMP_ANE
WHERE employee_id = 252;

ROLLBACK;

INSERT INTO
    (SELECT employee_id, last_name, email, hire_date, job_id, salary, commission_pct FROM EMP_ANE)
VALUES (252, 'Nume252', 'nume252@emp.com', SYSDATE, 'SA_REP', 5000, NULL);

SELECT employee_id, last_name, email, hire_date, job_id, salary, commission_pct
FROM EMP_ANE
WHERE employee_id = 252;

ROLLBACK;

-- 11
CREATE TABLE SUBALTERNI_ANE
(
    cod number(6) CONSTRAINT PK_SUBALTERNI PRIMARY KEY,
    nume VARCHAR2(25) CONSTRAINT SUBALTERNI_NUME NOT NULL,
    prenume VARCHAR(20),
    cod_manager number(6),
    nume_manager VARCHAR2(25) CONSTRAINT NUME_MANAGER NOT NULL
);

INSERT INTO SUBALTERNI_ANE(cod, nume, prenume, cod_manager, nume_manager)
(
    SELECT ang.employee_id, ang.last_name, ang.first_name, ang.manager_id, mg.last_name
    FROM EMPLOYEES ang
    JOIN EMPLOYEES mg ON(ang.manager_id = mg.employee_id)
    WHERE INITCAP(CONCAT(mg.last_name, mg.first_name)) = 'Kingsteven'
);

SELECT * FROM SUBALTERNI_ANE;
ROLLBACK;