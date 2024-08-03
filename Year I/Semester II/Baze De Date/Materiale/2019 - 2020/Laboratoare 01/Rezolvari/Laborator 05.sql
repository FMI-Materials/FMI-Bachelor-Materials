-- LABORATOR 5

--Document lab 3

--VII. [Exercitii - subcereri necorelate]

10. Folosind subcereri, s? se afi?eze numele ?i data angaj?rii pentru salaria?ii care au
fost angaja?i dup? Gates.

SELECT last_name, hire_date
FROM employees
WHERE hire_date > (SELECT hire_date
                    FROM employees
                    WHERE INITCAP(last_name)='Gates'
                    -- subcerere care returneaza data angajarii lui Gates
                    );

11. Folosind subcereri, scrie?i o cerere pentru a afi?a numele ?i salariul pentru to?i
colegii (din acela?i departament) lui Gates. Se va exclude Gates.

Se poate înlocui operatorul IN cu = ???


-- subcerere care selecteaza departamentul lui Gates

SELECT department_id 
FROM employees
WHERE initcap(last_name)='Gates';

SELECT last_name, salary
FROM employees
WHERE department_id = (SELECT department_id 
                        FROM employees
                        WHERE initcap(last_name)='Gates'
                        )
        AND initcap(last_name)!='Gates';

-- Se va inlocui Gates cu King

SELECT last_name, salary
FROM employees
WHERE department_id IN (SELECT department_id 
                        FROM employees
                        WHERE initcap(last_name)='King'
                        )
        AND initcap(last_name)!='King';
        
Obs: operator poate fi:
• single-row operator (>, =, >=, <, <>, <=), care poate fi utilizat dac?
subcererea returneaz? o singur? linie;
• multiple-row operator (IN, ANY, ALL), care poate fi folosit dac? subcererea
returneaz? mai mult de o linie.
Operatorul NOT poate fi utilizat în combina?ie cu IN, ANY ?i ALL.
        
12. Folosind subcereri, s? se afi?eze numele ?i salariul angaja?ilor condu?i direct de
pre?edintele companiei (acesta este considerat angajatul care nu are manager).

SELECT last_name, salary
FROM employees
WHERE manager_id = (SELECT employee_id
                    FROM employees
                    WHERE manager_id is null
                    -- subcerere care determina pres. companiei
                    );



13. Scrie?i o cerere pentru a afi?a numele, codul departamentului ?i salariul
angaja?ilor al c?ror cod de departament ?i salariu coincid cu codul departamentului ?i
salariul unui angajat care câ?tig? comision.

SELECT last_name, department_id, salary
FROM employees
WHERE (department_id, salary) IN (SELECT department_id, salary
                                FROM employees
                                WHERE commission_pct is not null
                                -- codul departamentului ?i salariul unui angajat care câ?tig? comision
                                );

14. S? se afi?eze codul, numele ?i salariul tuturor angaja?ilor al c?ror salariu este mai
mare decât salariul mediu.

SELECT employee_id, last_name, salary
FROM employees
WHERE salary > (SELECT AVG(salary)
                FROM employees
                );

15. Scrieti o cerere pentru a afi?a angaja?ii care câ?tig? (salariul plus comision) mai mult
decât oricare func?ionar (job-ul con?ine ?irul “CLERK”). Sorta?i rezultatele dupa salariu,
în ordine descresc?toare.

-- subcerere pentru a selecta functionarii
SELECT salary+ NVL(salary*commission_pct, 0)
FROM employees
WHERE upper(job_id) LIKE '%CLERK%';

--cererea principala
SELECT *
FROM employees
WHERE salary+NVL(salary*commission_pct,0) > ALL (SELECT salary+ NVL(salary*commission_pct, 0)
                                        FROM employees
                                        WHERE upper(job_id) LIKE '%CLERK%'
                                        )
ORDER BY salary desc;
                                        
>ANY e suficient sa fie mai mare decat salariul unui singur functionar (mai mare ca minimul)
>ALL trebuie sa fie mai mare decat salariile tuturor functionarilor (mai mare ca maximul)

-- varianta 2

SELECT *
FROM employees
WHERE salary+NVL(commission_pct,0) > (SELECT max(salary+ NVL(salary*commission_pct, 0))
                                        FROM employees
                                        WHERE upper(job_id) LIKE '%CLERK%'
                                        )
ORDER BY salary desc;

16. Scrie?i o cerere pentru a afi?a numele angajatilor, numele departamentului ?i
salariul angaja?ilor care nu câ?tig? comision, dar al c?ror ?ef direct câ?tig? comision.

SELECT last_name, department_name, salary
FROM employees e JOIN departments d USING (department_id)
WHERE commission_pct is null and
e.manager_id IN (SELECT manager_id
                FROM employees
                WHERE commission_pct is not null
                );

17. S? se afi?eze numele angajatilor, departamentul, salariul ?i job-ul tuturor
angaja?ilor al c?ror salariu ?i comision coincid cu salariul ?i comisionul unui angajat din
Oxford.

SELECT last_name, department_id, salary, job_id, employee_id
FROM employees
WHERE (nvl(commission_pct, -1), salary) IN
                                            (SELECT nvl(commission_pct, -1), salary
                                            FROM employees e JOIN departments d ON (e.department_id = d.department_id)
                                                            JOIN locations l ON (l.location_id = d.location_id)
                                            WHERE initcap(l.city)='Oxford'
                                            );


18. S? se afi?eze numele angaja?ilor, codul departamentului ?i codul job-ului
salaria?ilor al c?ror departament se afl? în Toronto.

SELECT last_name, department_id, job_id
FROM employees
WHERE department_id = (SELECT department_id 
                        FROM departments where location_id = (SELECT location_id 
                                                            FROM locations 
                                                            WHERE initcap(city)='Toronto')
                    );

--Varianta 2

SELECT last_name, e.department_id, job_id
FROM employees e join departments d on(e.department_id=d.department_id)
                join locations l on (d.location_id=l.location_id)
WHERE l.city = 'Toronto';

-- LABORATOR 4

-- III. [Exerci?ii – func?ii grup ?i clauzele GROUP BY, HAVING]

1. a) Functiile grup includ valorile NULL in calcule?

b) Care este deosebirea dintre clauzele WHERE ?i HAVING?

2. S? se afi?eze cel mai mare salariu, cel mai mic salariu, suma ?i media salariilor
TUTUROR angaja?ilor. Eticheta?i coloanele Maxim, Minim, Suma, respectiv Media. Sa se
rotunjeasca media salariilor.

SELECT MAX(salary) Maxim, MIN(salary) Minim, SUM(salary) Suma, ROUND(AVG(salary)) Media
FROM employees;

3. S? se modifice problema 2 pentru a se afi?a minimul, maximul, suma ?i media
salariilor pentru FIECARE job.

SELECT job_id, MAX(salary) Maxim, MIN(salary) Minim, SUM(salary) Suma, ROUND(AVG(salary)) Media
FROM employees
GROUP BY job_id;

4. S? se afi?eze num?rul de angaja?i pentru FIECARE departament.

SELECT COUNT(employee_id), department_id
FROM employees
GROUP BY department_id;

-- daca exista departamente fara angajati, dorim sa afisam id-ul departamentului si 0 angajati

SELECT COUNT(e.employee_id), d.department_id
FROM employees e right join departments d on(e.department_id=d.department_id)
GROUP BY d.department_id;

SELECT count(distinct manager_id) "Nr. manageri"
FROM employees;


5. S? se determine num?rul de angaja?i care sunt ?efi. Etichetati coloana “Nr.
manageri”.

SELECT COUNT(distinct manager_id) "Nr. manageri"
FROM employees;

? De ce am folosit cuvântul cheie DISTINCT? Ce am fi ob?inut dac? îl omiteam?


6. S? se afi?eze diferen?a dintre cel mai mare si cel mai mic salariu. Etichetati
coloana “Diferenta”.

SELECT max(salary)-min(salary) Diferenta
FROM employees;

7. Scrie?i o cerere pentru a se afi?a numele departamentului, loca?ia, num?rul de
angaja?i ?i salariul mediu pentru angaja?ii din acel departament. Coloanele vor fi
etichetate corespunz?tor.

SELECT department_name "Nume departament", location_id "Locatie", COUNT(employee_id) Angajati, AVG(salary) Salariu
FROM employees e JOIN departments d ON (e.department_id=d.department_id)
GROUP BY department_name, location_id;


!!!Obs: În clauza GROUP BY se trec obligatoriu toate coloanele prezente în clauza
SELECT, care nu sunt argument al func?iilor grup (a se vedea ultima observa?ie de la
punctul I).

8. S? se afi?eze codul ?i numele angaja?ilor care au salariul mai mare decât salariul
mediu din firm?. Se va sorta rezultatul în ordine descresc?toare a salariilor.

SELECT employee_id, first_name, last_name
FROM employees
WHERE salary > (SELECT AVG(salary)
FROM employees)
ORDER BY salary DESC;

TEMA: Laborator 3 - ex: 18 + Laborator 4 - ex: 9 (0.5pct) --- primele 3 surse corecte 
        Laborator 4 - ex: 10, 12, 13, 14 - (bonus la final)
Deadline -> 28.03 (Sambata - inclusiv)

9. Pentru fiecare ?ef, s? se afi?eze codul s?u ?i salariul celui mai prost platit
subordonat. Se vor exclude cei pentru care codul managerului nu este cunoscut. De
asemenea, se vor exclude grupurile în care salariul minim este mai mic de 1000$.
Sorta?i rezultatul în ordine descresc?toare a salariilor.

SELECT manager_id, min(salary)
FROM employees
WHERE manager_id is not null 
GROUP BY manager_id
HAVING MIN(salary)>=1000
ORDER BY 2;

10. Pentru departamentele in care salariul maxim dep??e?te 3000$, s? se ob?in? codul,
numele acestor departamente ?i salariul maxim pe departament.

SELECT d.department_id, department_name, max(salary) "Salariu departament"
FROM departments d join employees e on (d.department_id=e.department_id)
GROUP BY d.department_id,department_name
HAVING max(salary)>3000;

11. Care este salariul mediu minim al job-urilor existente? Salariul mediu al unui job va
fi considerat drept media aritmetic? a salariilor celor care îl practic?.

SELECT MIN(AVG(salary))
FROM employees
GROUP BY job_id;

12. S? se afi?eze maximul salariilor medii pe departamente.

SELECT MAX(AVG(salary))
FROM employees
GROUP BY department_id;

13. Sa se obtina codul, titlul ?i salariul mediu al job-ului pentru care salariul mediu
este minim.

SELECT j.job_id, job_title, AVG(salary)
FROM jobs j join employees e ON (j.job_id=e.job_id)
GROUP BY j.job_id, job_title
HAVING AVG(salary)=(SELECT min(AVG(salary))
                    FROM employees
                    GROUP BY job_id
                    );

14. S? se afi?eze salariul mediu din firm? doar dac? acesta este mai mare decât 2500.
(clauza HAVING f?r? GROUP BY).;

SELECT AVG(salary)
FROM employees
HAVING AVG(salary)>2500;
