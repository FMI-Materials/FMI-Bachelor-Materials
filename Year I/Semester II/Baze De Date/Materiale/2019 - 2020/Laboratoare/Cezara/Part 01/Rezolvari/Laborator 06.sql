-- LABORATOR 4

16. Sa se afiseze codul, numele departamentului si numarul de angajati care
lucreaza in acel departament pentru: 

a) departamentele in care lucreaza mai putin de 4 angajati;

SELECT e.department_id, d.department_name, COUNT(*)
FROM employees e JOIN departments d ON (d.department_id = e.department_id)
GROUP BY e.department_id, d.department_name
HAVING COUNT(*) < 4;

--afisam si departamentele care au 0 angajati
SELECT d.department_id, d.department_name, COUNT(employee_id)
FROM employees e right JOIN departments d ON (d.department_id = e.department_id)
GROUP BY d.department_id, d.department_name
HAVING COUNT(employee_id) < 4;


-- varianta 2 
SELECT e.department_id, d. department_name, COUNT(*)
FROM departments d JOIN employees e ON (d.department_id = e.department_id )
WHERE e.department_id IN (  SELECT department_id
                            FROM employees
                            GROUP BY department_id
                            HAVING COUNT(*) < 4
                          )
GROUP BY e.department_id, d.department_name;

-- not in cu null !!!!!!!!!!!!!!!!!!!
SELECT e.department_id, d. department_name, COUNT(*)
FROM departments d JOIN employees e ON (d.department_id = e.department_id )
WHERE e.department_id NOT IN (  SELECT nvl(department_id, 0)
                                FROM employees
                                GROUP BY department_id
                                HAVING COUNT(*) < 4
                              )
GROUP BY e.department_id, d.department_name;

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
-- daca avem NOT IN, iar subcererea returneaza si valori null atunci trebuie sa eliminam/inlocuim valorile null


b) departamentul care are numarul maxim de angajati.

SELECT d.department_id, d.department_name, COUNT(employee_id)
FROM employees e JOIN departments d ON (d.department_id = e.department_id)
GROUP BY d.department_id, d.department_name
HAVING count(employee_id) = (select max(count(employee_id))
                             from employees
                             group by department_id);

17. Sa se afiseze salariatii care au fost angajati în aceea?i zi a lunii în care cei mai
multi dintre salariati au fost angajati.

SELECT employee_id, TO_CHAR(hire_date,'DD') "Ziua angajarii din luna"
FROM employees
WHERE to_char(hire_date,'DD') =(
                        SELECT TO_CHAR(hire_date,'DD')
                        FROM employees
                        GROUP BY TO_CHAR(hire_date,'DD')
                        HAVING count(employee_id)=
                                (SELECT max(COUNT(employee_id)) -- 12 angajati
                                 FROM employees 
                                 GROUP BY TO_CHAR(hire_date,'DD')
                                 )
                        );

18. S? se ob?in? num?rul departamentelor care au cel pu?in 15 angaja?i.

SELECT COUNT(COUNT(department_id)) "Numar departamente"
FROM employees
GROUP BY department_id
HAVING COUNT(employee_id)>=15;

19. S? se ob?in? codul departamentelor ?i suma salariilor angaja?ilor care lucreaz? în
acestea, în ordine cresc?toare. Se consider? departamentele care au mai mult de
10 angaja?i ?i al c?ror cod este diferit de 30.

SELECT department_id, SUM(salary)
FROM employees
WHERE department_id != 30
GROUP BY department_id
HAVING COUNT(employee_id)>10
ORDER BY 2;

20. Care sunt angajatii care au mai avut cel putin doua joburi?

SELECT employee_id
FROM job_history
GROUP BY employee_id
HAVING count(employee_id)>=2;

21. S? se calculeze comisionul mediu din firm?, luând în considerare toate liniile din
tabel.
Obs: Func?iile grup ignor? valorile null. Prin urmare, instruc?iunea

SELECT AVG(commission_pct)
FROM employees; --0.2228...

va returna media valorilor pe baza liniilor din tabel pentru care exist? o valoare diferit?
de null. Astfel, reiese c? suma valorilor se împarte la num?rul de valori diferite de null.
Calculul mediei pe baza tuturor liniilor din tabel se poate realiza utilizând func?iile NVL,
NVL2 sau COALESCE:

SELECT AVG(NVL(commission_pct, 0))
FROM employees; --0.0728...

O alt? variant? este dat? de o cerere de forma:

SELECT SUM(commission_pct)/COUNT(*)
FROM employees;


-- IV. [Exerci?ii – DECODE]

22. Scrie?i o cerere pentru a afi?a job-ul, salariul total pentru job-ul respectiv pe
departamente si salariul total pentru job-ul respectiv pe departamentele 30, 50, 80.
Se vor eticheta coloanele corespunz?tor. Rezultatul va ap?rea sub forma de mai jos:
Job Dep30 Dep50 Dep80 Total
------------------------------------------------------------------------------
………….
...............
SELECT job_id,  SUM(DECODE(department_id, 30, salary)) Dep30,
                SUM(DECODE(department_id, 50, salary)) Dep50,
                SUM(DECODE(department_id, 80, salary)) Dep80,
                SUM(salary) Total
FROM employees
GROUP BY job_id;

Metoda 2: (cu subcereri corelate în clauza SELECT)

SELECT job_id, (SELECT SUM(salary)
                FROM employees
                WHERE department_id = 30
                AND job_id = e.job_id) Dep30,
                (SELECT SUM(salary)
                FROM employees
                WHERE department_id = 50
                AND job_id = e.job_id) Dep50,
                (SELECT SUM(salary)
                FROM employees
                WHERE department_id = 80
                AND job_id = e.job_id) Dep80,
                SUM(salary) Total
FROM employees e
GROUP BY job_id;


23. S? se creeze o cerere prin care s? se afi?eze num?rul total de angaja?i ?i, din
acest total, num?rul celor care au fost angaja?i în 1997, 1998, 1999 si 2000. Denumiti
capetele de tabel in mod corespunzator.

SELECT (SELECT COUNT(*) FROM employees) "Angajati total", 
                (SELECT COUNT(employee_id)
                FROM employees
                WHERE TO_CHAR(hire_date,'YYYY') = 1997) "1997",
                (SELECT COUNT(employee_id)
                FROM employees
                WHERE TO_CHAR(hire_date,'YYYY') = 1998) "1998",
                (SELECT COUNT(employee_id)
                FROM employees
                WHERE TO_CHAR(hire_date,'YYYY') = 1999) "1999",
                (SELECT COUNT(employee_id)
                FROM employees
                WHERE TO_CHAR(hire_date,'YYYY') = 2000) "2000"
FROM dual;

[Exerci?ii – subcereri în clauza FROM]

24. S? se afi?eze codul, numele departamentului ?i suma salariilor pe departamente.

-- varianta 1
SELECT d.department_id, department_name, sum(salary)
FROM departments d join employees e on (d.department_id = e.department_id)
GROUP by d.department_id, department_name;



--varianta 2
SELECT d.department_id, department_name, a.suma
FROM departments d, (SELECT department_id, SUM(salary) suma
                     FROM employees
                     GROUP BY department_id
                     ) a
WHERE d.department_id = a.department_id;


25. S? se afi?eze numele, salariul, codul departamentului si salariul mediu din
departamentul respectiv.

--subcerere in FROM 
select last_name, salary, department_id, SalMed
from employees join (select round(avg(salary)) SalMed, department_id
                     from employees
                     group by department_id
                     )
    using (department_id);
    
  
-- subcerere in select
select last_name, salary, department_id, (select round(avg(salary))
                                          from employees
                                          where e.department_id = department_id
                                          ) SalMediu
from employees e
where department_id is not null;

select last_name, salary, department_id
from employees;

