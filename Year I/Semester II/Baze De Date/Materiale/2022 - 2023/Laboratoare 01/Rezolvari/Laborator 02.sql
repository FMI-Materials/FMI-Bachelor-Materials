-- 1
SELECT CONCAT(last_name, ' ' || first_name) || ' castiga ' || salary || ' lunar dar doreste ' || salary * 3 "Salariu ideal"
FROM EMPLOYEES;

-- 2
SELECT INITCAP(first_name), UPPER(last_name), LENGTH(last_name)
FROM EMPLOYEES
WHERE UPPER(last_name) LIKE 'J%' OR
      UPPER(last_name) LIKE 'M%' OR
      UPPER(last_name) LIKE '__A%';

SELECT INITCAP(first_name), UPPER(last_name), LENGTH(last_name)
FROM EMPLOYEES
WHERE SUBSTR(UPPER(last_name), 1, 1) IN ('J', 'M') OR
      SUBSTR(UPPER(last_name), 3, 1) = 'A';

-- 3
SELECT employee_id, last_name, department_id
FROM EMPLOYEES
WHERE LTRIM(RTRIM(INITCAP(first_name))) = 'Steven';

SELECT employee_id, last_name, department_id
FROM EMPLOYEES
WHERE TRIM(BOTH FROM INITCAP(first_name)) = 'Steven';

-- 4
SELECT employee_id "ID", last_name "Nume", LENGTH(last_name) "Lungimea numelui", INSTR(UPPER(last_name), 'A') "Prima aparitie a literei A"
FROM EMPLOYEES
WHERE LOWER(last_name) LIKE '%e';

-- 5
SELECT *
FROM EMPLOYEES
WHERE MOD(ROUND(sysdate - hire_date), 7) = 0;

-- 6
SELECT employee_id, last_name, salary, 
       ROUND(salary * 1.15, 2) "Salariu nou",
       ROUND((salary * 1.15) / 100, 2) "Numar sute"
FROM EMPLOYEES
WHERE MOD(salary, 1000) != 0;

-- 7
SELECT last_name "Nume angajat", RPAD(TO_CHAR(hire_date), 20) "Data angajarii"
FROM EMPLOYEES
WHERE commission_pct IS NOT NULL;

-- 8
SELECT TO_CHAR(sysdate + 30, 'MONTH DD YYYY MI SS') "Data de peste 30 de zile"
FROM DUAL;

-- 9
SELECT ROUND(TO_DATE('31-DEC-23') - sysdate) "Zile Pana La Sfarsitul Anului"
FROM DUAL;

-- 10
SELECT TO_CHAR(sysdate + 0.5, 'DD/MON HH24:MI:SS') 
FROM DUAL;

SELECT TO_CHAR(sysdate + 5 / 60 / 24, 'DD/MON HH24:MI:SS') 
FROM DUAL;

-- 11
SELECT CONCAT(last_name, ' ' || first_name), hire_date, 
       NEXT_DAY(ADD_MONTHS(hire_date, 6), 'Monday') "Negociere"
FROM EMPLOYEES;

-- 12
SELECT last_name, ROUND(MONTHS_BETWEEN(sysdate, hire_date)) "Luni lucrate"
FROM EMPLOYEES
ORDER BY "Luni lucrate" DESC;

-- 13
SELECT last_name, NVL(TO_CHAR(commission_pct), 'Fara comision') "Comision"
FROM EMPLOYEES;

SELECT last_name, DECODE(commission_pct, NULL, 'Fara comision', commission_pct) "Comision"
FROM EMPLOYEES;

-- 14
SELECT last_name, salary, commission_pct
FROM EMPLOYEES
WHERE salary + salary * NVL(commission_pct, 0) > 10000;

SELECT last_name, salary, commission_pct
FROM EMPLOYEES
WHERE NVL(salary + salary * commission_pct, salary) > 10000
ORDER BY 3 NULLS FIRST;

-- 15
SELECT last_name, job_id, salary, 
       CASE job_id WHEN 'IT_PROG' THEN salary * 1.1
                   WHEN 'ST_CLERK' THEN salary * 1.15
                   WHEN 'SA_REP' THEN salary * 1.2
                   ELSE salary
       END "Salariu renegociat"
FROM EMPLOYEES;

SELECT last_name, job_id, salary, 
       DECODE
       (
            job_id, 
            'IT_PROG', salary * 1.1,
            'ST_CLERK', salary * 1.15,
            'SA_REP', salary * 1.12,
            salary
       ) "Salariu renegociat"
FROM EMPLOYEES;

-- 16
SELECT employee_id, department_name
FROM EMPLOYEES e, DEPARTMENTS d
WHERE e.department_id = d.department_id (+);

SELECT employee_id, department_name
FROM EMPLOYEES e 
JOIN DEPARTMENTS d ON (e.department_id = d.department_id);

SELECT employee_id, department_name
FROM EMPLOYEES
JOIN DEPARTMENTS USING(department_id);

-- 17
SELECT job_id, job_title
FROM EMPLOYEES e
JOIN JOBS j USING(job_id)
WHERE department_id = 30;

-- 18
SELECT last_name, department_name, location_id
FROM EMPLOYEES e, DEPARTMENTS d
WHERE e.department_id = d.department_id 
      AND commission_pct IS NOT NULL;

-- 19
SELECT last_name, job_title, department_name
FROM DEPARTMENTS
JOIN EMPLOYEES USING(department_id)
JOIN JOBS USING(job_id)
JOIN LOCATIONS USING(location_id)
WHERE INITCAP(city) = 'Oxford';

-- 20
SELECT e.employee_id "Ang#", e.last_name "Angajat", m.employee_id "Manager", m.last_name "Mgr#" 
FROM EMPLOYEES e
JOIN EMPLOYEES m ON (e.manager_id = m.employee_id);

-- 21
SELECT e.employee_id "Ang#", e.last_name "Angajat", m.employee_id "Manager", m.last_name "Mgr#"
FROM EMPLOYEES e
LEFT JOIN EMPLOYEES m ON (e.manager_id = m.employee_id);

-- 22
SELECT e.last_name "Nume", e.department_id "Cod departament", col.last_name "Nume coleg" 
FROM EMPLOYEES e
JOIN EMPLOYEES col ON (e.department_id = col.department_id 
                       AND e.employee_id > col.employee_id);

-- 23
SELECT last_name, employee_id, job_title, department_name, salary
FROM DEPARTMENTS
RIGHT JOIN EMPLOYEES USING(department_id)
JOIN JOBS USING(job_id);

-- 24
SELECT e.last_name "NumeAng", e.hire_date "DataAng", 
       gates.last_name "NumeGates", gates.hire_date "DataGates"
FROM EMPLOYEES e, EMPLOYEES gates 
WHERE e.hire_date > gates.hire_date 
      AND INITCAP(gates.last_name) = 'Gates';

SELECT last_name "NumeAng", hire_date "DataAng"
FROM EMPLOYEES
WHERE hire_date > (
                        SELECT hire_date
                        FROM EMPLOYEES
                        WHERE INITCAP(last_name) = 'Gates'
                  );

-- 25
SELECT e.last_name "Angajat", e.hire_date "Data_ang",
       m.last_name "Manager", m.hire_date "Data_mgr"
FROM EMPLOYEES e
JOIN EMPLOYEES m ON (e.manager_id = m.employee_id 
                     AND e.hire_date < m.hire_date);
