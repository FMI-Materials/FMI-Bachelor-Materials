-- LABORATOR 5

0. a) S? se afi?eze informa?ii despre angaja?ii al c?ror salariu dep??e?te valoarea medie a
salariilor colegilor s?i de departament.

SELECT last_name, salary, department_id
FROM employees e
WHERE salary > (SELECT AVG(salary)
                FROM employees
                WHERE department_id = e.department_id
                        AND employee_id!=e.employee_id
                );
 
 b) Analog cu cererea precedent?, afi?ându-se ?i numele departamentului ?i media salariilor
acestuia ?i num?rul de angaja?i.

--Solu?ia 1 (subcerere necorelat? în clauza FROM):

SELECT last_name, salary, e.department_id, department_name, sal_med, nr_sal
FROM employees e, departments d, (SELECT department_id, ROUND(AVG(salary)) sal_med,
                                 COUNT(*) nr_sal
                                 FROM employees
                                 GROUP BY department_id) ac
WHERE e.department_id = d.department_id
        AND d.department_id = ac.department_id
        AND salary > (SELECT AVG(salary)
                        FROM employees
                        WHERE department_id = e.department_id
                        );
 
 SELECT last_name, salary, e.department_id, department_name, sal_med, nr_sal
FROM employees e, departments d, (SELECT department_id, ROUND(AVG(salary)) sal_med,
                                 COUNT(*) nr_sal
                                 FROM employees
                                 GROUP BY department_id) ac
WHERE e.department_id = d.department_id
        AND d.department_id = ac.department_id
        AND salary > sal_med;
        
--Solu?ia 2 (subcerere corelat? în clauza SELECT):
 
SELECT last_name, salary, e. department_id, department_name,
 (SELECT AVG(salary)
 FROM employees
 WHERE department_id = e. department_id) “Salariu mediu”,
 (SELECT COUNT(*)
 FROM employees
 WHERE department_id = e. department_id) “Nr angajati”
FROM employees e join departments d on (e.department_id = d.department_id)
WHERE salary > (SELECT AVG(salary)
 FROM employees
 WHERE department_id = e.department_id);
 
1. S? se afi?eze numele ?i salariul angaja?ilor al c?ror salariu este mai mare decât salariile
medii din toate departamentele. Se cer 2 variante de rezolvare: cu operatorul ALL sau cu
func?ia MAX.

SELECT last_name, salary
FROM EMPLOYEES
WHERE salary>all (SELECT ROUND(AVG(SALARY)) 
                FROM employees
                GROUP BY department_id);
                
SELECT last_name, salary
FROM EMPLOYEES
WHERE salary>(SELECT ROUND(MAX(AVG(SALARY))) 
                FROM employees
                GROUP BY department_id);
                
2. Sa se afiseze numele si salariul celor mai prost platiti angajati din fiecare departament.

--Solu?ia 1 (cu sincronizare):
SELECT last_name, salary, department_id
FROM employees e
WHERE salary = (SELECT MIN(salary)
                FROM employees
                WHERE department_id = e.department_id);
 
--Solu?ia 2 (f?r? sincronizare):

SELECT last_name, salary, department_id
FROM employees
WHERE (department_id, salary) IN (SELECT department_id, MIN(salary)
                                FROM employees
                                 GROUP BY department_id);
 
--Solu?ia 3: Subcerere în clauza FROM 
 
 SELECT last_name, salary, e.department_id
FROM employees e JOIN (SELECT MIN(salary) sal, department_id
                        FROM employees
                        GROUP BY department_id) min_sal
                ON (e.department_id=min_sal.department_id)
WHERE e.salary = min_sal.sal;
 
 3. Sa se obtina numele salariatilor care lucreaza intr-un departament in care exista cel putin 1
angajat cu salariul egal cu salariul maxim din departamentul 30.

Obs: Deoarece nu este necesar ca instruc?iunea SELECT interioar? s? returneze o anumit?
valoare, se poate selecta o constant? (‘x’, ‘’, 1 etc.). De altfel, din punct de vedere al performan?ei,
selectarea unei constante asigur? mai mult? rapiditate decât selectarea unei coloane.

--IN

SELECT last_name, salary
FROM employees
WHERE department_id in (SELECT department_id
                        FROM employees
                        WHERE salary=(SELECT MAX(SALARY)
                                        FROM employees
                                        WHERE department_id=30)
                                AND department_id!=30        
                                        );
--EXISTS                                     
SELECT last_name, salary
FROM employees e
WHERE EXISTS (SELECT 1
            FROM employees
            WHERE e.department_id=department_id AND
            salary=(SELECT MAX(SALARY)
                    FROM employees
                    WHERE department_id=30)
                    AND department_id!=30
                    );


-- EX. 4 IMPORTANT!!! 
4. Sa se obtina numele primilor 3 angajati avand salariul maxim. Rezultatul se va afi?a în ordine
cresc?toare a salariilor.

--Solutia 1: subcerere sincronizat?
--numaram cate salarii sunt mai mari decat salariul de la linia la care a ajuns
select last_name, salary, rownum
from (select last_name, salary
      from employees
      order by salary desc
      ) e
where 3 > (select count(salary)
           from employees
           where salary > e.salary)
      and rownum <= 3;


--Solutia 2: vezi analiza top-n (mai jos)
--dorim sa afisam angajatii care au primele 3 cele mai mari salarii din firma

select last_name, salary, rownum
from employees
where rownum <= 3
order by salary desc;
-- aceasta varianta este GRESITA deoarece prima data se executa conditia din where
-- deci o sa ia primele 3 randuri gasite in tabel (in ordinea din tabel)
-- si la final o sa execute clauza group by 

-- varianta corecta - subcerere in from 
-- deoarece dorim sa ordonam descrescator inainte de a aplica conditia in where
select last_name, salary, rownum
from (select last_name, salary
      from employees
      order by salary desc
      )
where rownum <= 3;

5. S? se afi?eze codul, numele ?i prenumele angaja?ilor care au cel pu?in doi subalterni.

SELECT employee_id, last_name, first_name
FROM employees e
WHERE (SELECT COUNT(employee_id)
        FROM employees
        WHERE manager_id=e.employee_id)>=2;

6. S? se determine loca?iile în care se afl? cel pu?in un departament.


Obs: Ca alternativ? a lui EXISTS, poate fi utilizat operatorul IN. Scrie?i ?i aceast? variant? de
rezolvare.

--IN
SELECT location_id
FROM locations
WHERE location_id in (SELECT location_id
                    FROM departments);
--EXISTS
SELECT location_id
FROM locations l
WHERE EXISTS (SELECT 1
                FROM departments
                WHERE l.location_id=location_id
                );

7. S? se determine departamentele în care nu exist? nici un angajat.

SELECT department_id, department_name
FROM departments d -- department_id este PK ceea ce inseamna ca avem o lista unica de departamente
WHERE NOT EXISTS (SELECT 'x'
                FROM employees -- aici department_id este FK deci avem departamente in care lucreaza angajati
                WHERE department_id = d.department_id
                );
--> in final obtinem exact lista departamentelor in care nu exista angajati
--Obs: Acest exemplu poate fi rezolvat ?i printr-o subcerere necorelat?, utilizând operatorul NOT IN
--(vezi ?i laboratorul 3). Aten?ie la valorile NULL! Scrie?i ?i aceast? variant? de rezolvare.

--NOT IN
SELECT department_id, department_name
FROM departments d
WHERE department_id NOT IN (SELECT NVL(department_id, 0)
                            FROM employees
                            ); 
 --atunci cand utilizam not in trebuie sa eliminam sau sa inlocuim valorile null din subcerere
 
 --MINUS
 SELECT department_id
 FROM departments -- din lista tuturor departamentelor
 
 MINUS
 
 SELECT department_id
 FROM employees; -- departamentele care au angajati
 8. Utilizând clauza WITH, s? se scrie o cerere care afi?eaz? numele departamentelor ?i
valoarea total? a salariilor din cadrul acestora. Se vor considera departamentele a c?ror valoare
total? a salariilor este mai mare decât media valorilor totale ale salariilor tuturor angajatilor.

WITH val_dep AS (SELECT department_name, SUM(salary) AS total
                 FROM departments d join employees e ON (d.department_id = e.department_id)
                 GROUP BY department_name
                 ),
                 
val_medie AS (SELECT SUM(total)/COUNT(*) AS medie
                FROM val_dep)
                
SELECT *
FROM val_dep
WHERE total > (SELECT medie
                FROM val_medie)
ORDER BY department_name;

Tema: lab 5-> ex: 5, 9, 10, 11, 12, 14
Duminica 12.04 inclusiv

9. S? se afi?eze codul, prenumele, numele ?i data angaj?rii, pentru angajatii condusi de Steven
King care au cea mai mare vechime dintre subordonatii lui Steven King. Rezultatul nu va con?ine
angaja?ii din anul 1970.

10. S? se determine primii 10 cei mai bine pl?ti?i angaja?i.

SELECT employee_id, salary
FROM (SELECT employee_id, salary
        FROM employees
        ORDER BY 2 desc)
WHERE rownum<=10;

11. S? se afi?eze informa?ii despre departamente, în formatul urm?tor: „Departamentul
<department_name> este condus de {<manager_id> | nimeni} ?i {are num?rul de salaria?i <n> | nu
are salariati}“.

SELECT 'Departamentul '||department_name||' este condus de '||NVL(TO_CHAR(manager_id),'nimeni')||' si '||
CASE
WHEN (SELECT count(employee_id)
 FROM employees
 WHERE d.department_id = department_id) = 0
THEN 'nu are salariati'
ELSE 'are numarul de salariati ' || (SELECT count(employee_id)
 FROM employees
 WHERE d.department_id = department_id)
END Detalii
FROM departments d;

12. S? se afi?eze numele, prenumele angaja?ilor ?i lungimea numelui pentru înregistr?rile în
care aceasta este diferit? de lungimea prenumelui.

SELECT last_name, first_name, nullif(length(last_name),length(first_name)) Lungime
from employees;

14. S? se afi?eze:
a) suma salariilor, pentru job-urile care incep cu litera S;
b) media generala a salariilor, pentru job-ul avand salariul maxim;
c) salariul minim, pentru fiecare din celelalte job-uri.

SELECT job_id,
CASE
WHEN lower(job_id) like 's%' THEN
            (SELECT sum(salary)
            FROM employees
            WHERE job_id = j.job_id
            )
WHEN job_id = (SELECT job_id
                FROM employees
                WHERE salary = (SELECT max(salary)
                                FROM employees)
                ) THEN
                (SELECT round(avg(salary))
                FROM employees
                )
ELSE (SELECT min(salary)
    FROM employees
    WHERE job_id = j.job_id)
END joburi
FROM jobs j;
