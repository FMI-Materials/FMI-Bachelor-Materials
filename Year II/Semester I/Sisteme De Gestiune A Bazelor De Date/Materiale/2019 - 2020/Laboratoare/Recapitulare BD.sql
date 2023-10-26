--1. Sa se afiseze numele salariatilor si codul departamentelor pentru toti angajatii din departamentele 10 si 30 in ordine alfabetica a numelor.
SELECT first_name||' '||last_name full_name, department_id
FROM employees
WHERE department_id IN (10, 30)
ORDER BY 1;


--2. Care este data curenta? Afisati diferite formate ale acesteia.
SELECT sysdate
FROM dual;

SELECT TO_CHAR(sysdate, 'DAY MONTH YYYY HH24:MI:SS') data_curenta
FROM dual;


--3. Sa se afiseze numele si data angajarii pentru fiecare salariat care a fost angajat in 1987. 
-- Se cer 2 solutii: una in care se lucreaza cu formatul implicit al datei si alta prin care se formateaza data.
--Varianta 1
SELECT first_name, last_name, hire_date
FROM employees
WHERE hire_date LIKE '%87%';

--Varianta 2
SELECT first_name, last_name, hire_date
FROM employees
WHERE TO_CHAR(hire_date, 'YYYY') = '1987';


--4. Sa se afiseze numele si job-ul pentru toti angajatii care nu au manager.
SELECT first_name||' '||last_name full_name, job_id
FROM employees
WHERE manager_id IS NULL;


--5. Sa se afiseze numele, salariul si comisionul pentru toti salariasii care castiga comision. Sa se sorteze datele in ordine descrescatoare a salariilor si comisioanelor.
SELECT first_name, last_name, salary, commission_pct
FROM employees
WHERE commission_pct IS NOT NULL
ORDER BY salary DESC, commission_pct DESC;

--6. Eliminati clauza WHERE din cererea anterioara. Unde sunt plasate valorile NULL in ordinea descrescatoare?
-- Valorile NULL sunt plasate inaintea valorilor mai mari sau egale cu 0.

--7. Sa se listeze numele tuturor angajatilor care au a treia litera din nume ‘A’.
SELECT first_name||' '||last_name name
FROM employees
WHERE UPPER(first_name||' '||last_name) LIKE '__A%';


--8. Sa se listeze numele tuturor angajatilor care au 2 litere ‘L’ in nume si lucreaz? in departamentul 30 sau managerul lor este 102.
SELECT first_name, last_name
FROM employees
WHERE manager_id = 102 OR (UPPER(first_name||last_name) LIKE '%L%L%' AND department_id = 30);


--9. Sa se afiseze numele, job-ul si salariul pentru toti salariatii al caror job contine sirul “CLERK” sau “REP” si salariul nu este egal cu 1000, 2000 sau 3000.
SELECT DISTINCT first_name, last_name, salary
FROM employees JOIN jobs
    USING (job_id)
WHERE salary NOT IN (1000, 2000, 3000)
    AND UPPER(job_title) LIKE '%CLERK%' OR UPPER(job_title) LIKE'%REP%';
    
    
--10. Sa se afiseze numele salariatilor si numele departamentelor in care lucreaza. Se vor afisa si salariatii care nu au asociat un departament.
SELECT e.first_name||' '||e.last_name name, d.department_name
FROM employees e, departments d
WHERE e.department_id = d.department_id(+);

SELECT e.first_name||' '||e.last_name name, d.department_name
FROM employees e 
LEFT JOIN departments d ON e.department_id = d.department_id;


--11. Sa se afiseze numele departamentelor si numele salariatilor care lucreaza in ele. Se vor afisa si departamentele care nu au salariati.
SELECT d.department_name, e.first_name||' '||e.last_name name
FROM departments d
LEFT JOIN employees e ON d.department_id = e.department_id;

SELECT first_name, last_name, department_name
FROM employees e, departments d
WHERE e.department_id (+) = d.department_id;


--12 + 13. Sa se afiseze codul angajatului si numele acestuia, impreuna cu numele si codul sefului sau direct. 
-- Sa se modifice cererea astfel incat sa se afiseze toti angajatii, inclusiv cei care nu manager.
SELECT e.employee_id, e.last_name, manager_id, (SELECT last_name
                                                FROM employees
                                                WHERE employee_id = e.manager_id) manager
FROM employees e;


SELECT e.employee_id EMP#, e.first_name||' '||e.last_name "Employee", 
    m.employee_id MGR#, m.first_name||' '||m.last_name "Manager"
FROM employees e, employees m                                       -- SELF JOIN
WHERE e.manager_id = m.employee_id(+);


--14. Sa se obtina codurile departamentelor in care nu lucreaza nimeni.
--Varianta 1
SELECT department_id
FROM departments
MINUS
SELECT department_id
FROM employees;

--Varianta 2
SELECT department_id
FROM departments
WHERE department_id NOT IN (SELECT DISTINCT department_id
                            FROM employees
                            WHERE department_id IS NOT NULL)
ORDER BY department_id;


--Varianta 3
SELECT d.department_id
FROM departments d
WHERE NOT EXISTS ( SELECT 1
                   FROM employees
                   WHERE department_id = d.department_id);
                   
--Varianta 4
SELECT d.department_id
FROM departments d
WHERE (SELECT COUNT(*)
       FROM employees
       WHERE department_id = d.department_id) = 0;
       
       
--15. Sa se afiseze cel mai mare salariu, cel mai mic salariu, suma si media salariilor tuturor angajatilor.
SELECT MAX(salary) MAXIM, MIN(salary) MINIM, SUM(salary) TOTAL, ROUND(AVG(salary), 3) AVERAGE
FROM employees;


--16. Sa se afiseze minimul, maximul, suma si media salariilor pentru fiecare job
SELECT job_id, MAX(salary) MAXIM, MIN(salary) MINIM, SUM(salary) TOTAL, ROUND(AVG(salary), 3) AVERAGE
FROM employees
GROUP BY job_id;
                
                
--17. Sa se afiseze numarul de angajati pentru fiecare job.
SELECT e.job_id, 
CASE
    WHEN j.job_id NOT IN (SELECT DISTINCT job_id FROM employees) THEN 0
    ELSE COUNT(*)
END "Numar angajati"
FROM employees e
RIGHT JOIN jobs j ON e.job_id = j.job_id
GROUP BY e.job_id, j.job_id
ORDER BY 2 DESC;


--18. Scrieti o cerere pentru a se afisa numele departamentului, locatia, numarul de angaja?i si salariul mediu pentru angajatii din acel departament.
DESC locations;

SELECT d.department_name, l.street_address||', '||l.postal_code||', '||l.city||', '||l.state_province||', '||c.country_name ADDRESS,
    emp.num_emp, emp.average
FROM departments d, locations l, countries c,
    (SELECT department_id, COUNT(*) num_emp, ROUND(AVG(salary), 3) average
     FROM employees
     GROUP BY department_id) emp
WHERE d.department_id = emp.department_id
    AND d.location_id = l.location_id
    AND  l.country_id = c.country_id;


--19. Sa se afiseze codul si numele angajatilor care castiga mai mult decat salariul mediu din firma. Se va sorta rezultatul in ordine descrescatoare a salariilor.
SELECT e.employee_id, e.first_name||' '||e.last_name full_name
FROM employees e
WHERE e.salary > (SELECT TRUNC(AVG(salary), 2)
                  FROM employees)
ORDER BY e.salary;


--20. Care este salariul mediu minim al job-urilor existente? Salariul mediu al unui job va fi considerat drept media arirmetic? a salariilor celor care îl practic?.
SELECT MIN(AVG(salary))
FROM employees
GROUP BY job_id;

--21. Modifica?i exerci?iul anterior pentru a afi?a ?i id-ul jobului.
SELECT job_id, AVG(salary)
FROM employees 
JOIN jobs USING(job_id)
GROUP BY job_id, job_title
HAVING AVG(salary) = (SELECT MIN(AVG(salary))
                      FROM employees
                      GROUP BY job_id);

--22. Sa se afiseze codul, numele departamentului si numarul de angajati care lucreaza in acel departament pentru:
-- a) departamentele in care lucreaza mai putin de 4 angajati;
SELECT d.department_id, d.department_name, COUNT(e.employee_id)
FROM employees e, departments d
WHERE e.department_id(+) = d.department_id
GROUP BY d.department_id, d.department_name
HAVING COUNT(*) < 4
ORDER BY 3 DESC;

-- b) departamentul care are numarul maxim de angajati.
SELECT department_id, d.department_name, COUNT(e.employee_id)
FROM employees e JOIN departments d
    USING (department_id)
GROUP BY department_id, d.department_name
HAVING COUNT(*) = (SELECT MAX(COUNT(*))
                   FROM employees
                   GROUP BY department_id);
                   
--23. Sa se ob?ina numrul departamentelor care au cel putin 15 angaja?i.
SELECT COUNT(COUNT(department_id))
FROM employees 
GROUP BY department_id
HAVING COUNT(*) >= 15;

--24. Sa se afiseze salariatii care au fost angajati în aceea?i zi a lunii în care cei mai multi dintre salariati au fost angajati.
SELECT *
FROM employees
WHERE TO_CHAR(hire_date, 'DD') = ( SELECT TO_CHAR(hire_date, 'DD')
                                    FROM employees
                                    GROUP BY TO_CHAR(hire_date, 'DD')
                                    HAVING COUNT(employee_id) = (   SELECT MAX(COUNT(employee_id))
                                                                    FROM employees
                                                                    GROUP BY TO_CHAR(hire_date, 'DD') ) );


--25. Sa se afiseze numele si salariul celor mai prost platiti angajati din fiecare departament.
--Varianta 1 - subcerere nesincronizata in clauza WHERE
SELECT d.department_name, e.first_name||' '||e.last_name "Nume angajat", e.salary "Salariu"
FROM employees e JOIN departments d
    ON e.department_id = d.department_id
WHERE (d.department_id, e.salary) IN ( SELECT department_id, MIN(salary)
                                       FROM employees
                                       GROUP BY department_id);
                                    
--Varianta 2 - subcerere in clauza FROM
SELECT d.department_name, emp.full_name, emp.salary
FROM departments d, (SELECT first_name || ' ' || last_name AS full_name, salary, department_id
                     FROM employees 
                     WHERE (department_id, salary) IN (SELECT department_id, MIN(salary)
                                                       FROM employees
                                                       GROUP BY department_id)) emp
WHERE d.department_id = emp.department_id;

--26. Sa se detemine primii 10 cei mai bine platiti angajati.
--Varianta 1 
SELECT *
FROM (SELECT employee_id, first_name, last_name, MAX(salary)
      FROM employees
      GROUP BY employee_id, first_name, last_name
      ORDER BY 4 DESC)
WHERE ROWNUM < 11;

--Varianta 2 - Subcerere sincronizata in clauza WHERE
SELECT e.employee_id, e.first_name, e.last_name, e.salary
FROM employees e
WHERE 10 > (SELECT COUNT(*)
            FROM employees
            WHERE salary > e.salary)
ORDER BY e.salary DESC;


--27. Sa se afiseze codul, numele departamentului si suma salariilor pe departamente.
SELECT d.department_id, d.department_name, NVL(SUM(e.salary), 0) TOTAL
FROM departments d LEFT OUTER JOIN employees e
   ON d.department_id = e.department_id
GROUP BY d.department_id, d.department_name
ORDER BY 3 DESC;


--28. Sa se afiseze informatii despre angajatii al caror salariu depaseste valoarea medie a salariilor colegilor sai de departament.
with ssna as
 ( select department_id dep_id, sum(salary) suma, count(employee_id) nr
   from employees
   group by department_id
 )

 select e.employee_id, e.last_name, e.department_id
 from employees e join ssna s
 on e.department_id = s.dep_id
 where s.nr > 1 and e.salary > ((s.suma - e.salary) / (s.nr - 1))
 order by e.department_id;


SELECT *
FROM employees e
WHERE e.salary > (SELECT AVG(salary)
                  FROM employees
                  WHERE department_id = e.department_id
                      AND e.employee_id <> employee_id);