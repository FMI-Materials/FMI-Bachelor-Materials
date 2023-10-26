SELECT * from employees;

--8. S? se creeze o cerere pentru a afi?a numele angajatului ?i num?rul departamentului
--pentru angajatul având codul 104.

SELECT last_name, department_id
FROM employees
WHERE employee_id=104;

--9. S? se modifice cererea de la problema 7 pentru a afi?a numele ?i salariul angaja?ilor
--al c?ror salariu nu se afl? în intervalul [1500, 2850].

SELECT last_name, salary
FROM employees
WHERE salary NOT BETWEEN 1500 and 2850;

--10. S? se afi?eze numele, job-ul ?i data la care au început lucrul salaria?ii angaja?i între 20
--Februarie 1987 ?i 1 Mai 1989. Rezultatul va fi ordonat cresc?tor dup? data de început.

SELECT last_name, job_id, hire_date
FROM employees
WHERE hire_date BETWEEN '20-FEB-1987' AND '1-MAY-1989'
ORDER BY hire_date;

--Din laboratorul 1
-- 11
-- varianta 1
SELECT last_name, department_id
FROM employees
WHERE department_id IN (10, 30)
ORDER BY last_name;

--varianta 2
SELECT last_name, department_id
FROM employees
WHERE department_id IN (10, 30)
ORDER BY 1;
--varianta 3
SELECT last_name NUME, department_id
FROM employees
WHERE department_id IN (10, 30)
ORDER BY last_name NUME;

--varianta 4
SELECT last_name, department_id
FROM employees
WHERE department_id IN (10, 30)
ORDER BY last_name ASC;

--12. S? se modifice cererea de la problema 11 pentru a lista numele ?i salariile angajatilor
--care câ?tig? mai mult de 1500 ?i lucreaz? în departamentul 10 sau 30. Se vor eticheta
--coloanele drept Angajat si Salariu lunar.

SELECT last_name Angajat, salary "Salariu lunar"
FROM employees
WHERE department_id IN (10, 30) and salary>1500
ORDER BY last_name ASC;

--12 cu negatie
SELECT last_name Angajat, salary "Salariu lunar"
FROM employees
WHERE department_id NOT IN (10, 30) and salary>1500
ORDER BY last_name;

--13 Care este data curent?? Afi?a?i diferite formate ale acesteia.

SELECT SYSDATE
FROM employees; --afiseaza data de nr_angajatilor ori

desc dual; --o singura coloana

select 4+6
from dual;

select * from dual;

SELECT SYSDATE "Data curenta"
FROM dual;

--------------------------------------- CONVERSII
TO_CHAR(data, format) -- transforma in char

TO_NUMBER -- transforma in numar

TO_DATE -- transforma in data

----------------------------------------

TO_CHAR(data, format)

select to_char(sysdate, 'day-mon-year hh12 mi ss sssss d dd ddd') Data_Formatata
from dual;

14. S? se afi?eze numele ?i data angaj?rii pentru fiecare salariat care a fost angajat în
1987. Se cer 2 solu?ii: una în care se lucreaz? cu formatul implicit al datei ?i alta prin
care se formateaz? data.
--Varianta1:
SELECT last_name, hire_date
FROM employees
WHERE hire_date LIKE ('%87'); -- parantezele sunt optionale
-- sa contina X => %X% -> ABCXVBGF
-- sa inceapa cu X => X% -> XABBSFX 
-- sa se sfarseasca cu X => %X -> SOFEWDJDX
--Varianta 2:
SELECT last_name, hire_date
FROM employees
WHERE TO_CHAR(hire_date, 'YYYY')='1987';

desc employees;

15. S? se afi?eze numele ?i job-ul pentru to?i angaja?ii care nu au manager.

SELECT last_name, job_id
FROM employees
WHERE manager_id is NULL; -- nu se foloseste egalitatea

16. S? se afi?eze numele, salariul ?i comisionul pentru toti salaria?ii care câ?tig? comision.
S? se sorteze datele în ordine descresc?toare a salariilor ?i comisioanelor.
SELECT last_name, salary, commission_pct
FROM employees
 WHERE commission_pct is NOT NULL
 ORDER BY salary DESC, commission_pct DESC; --ordoneaza dupa salariu, daca sunt egale, atunci le ordoneaza descrescator dupa comision
 
 17. Elimina?i clauza WHERE din cererea anterioar?. Unde sunt plasate valorile NULL în
ordinea descresc?toare?

SELECT last_name, salary, commission_pct
FROM employees
-- WHERE commission_pct is not null
 ORDER BY salary DESC, commission_pct DESC; --pune NULL la final, daca erau ordonate crescator, NULL era pus la inceput

18. S? se listeze numele tuturor angajatilor care au a treia liter? din nume ‘A’.
Obs: Pentru compararea ?irurilor de caractere, împreun? cu operatorul LIKE se utilizeaz?
caracterele wildcard:
? % - reprezentând orice ?ir de caractere, inclusiv ?irul vid;
? _ (underscore) – reprezentând un singur caracter ?i numai unul.

SELECT last_name
FROM employees
WHERE upper(last_name) LIKE ('__A%');

SELECT last_name
FROM employees
WHERE lower(last_name) LIKE ('__a%');

SELECT last_name
FROM employees
WHERE initcap(last_name) LIKE ('__a%'); -- prima litera mare, restul mici

19. S? se listeze numele tuturor angajatilor care au cel putin 2 litere ‘L’ in nume ?i
lucreaz? în departamentul 30 sau managerul lor este 102.

SELECT last_name
FROM employees
WHERE (upper(last_name) LIKE ('%L%L%') and department_id=30) or manager_id=102; --and se executa mereu inainte de sau si fara paranteze

SELECT last_name, department_id, manager_id
FROM employees
WHERE last_name LIKE ('%l%l%');

20. S? se afiseze numele, job-ul si salariul pentru toti salariatii al caror job con?ine ?irul
“CLERK” sau “REP” ?i salariul nu este egal cu 1000, 2000 sau 3000 $. (operatorul NOT IN).

SELECT last_name, job_id, salary
FROM employees
WHERE (job_id LIKE '%CLERK%' or job_id LIKE '%REP%') and salary not in (1000, 2000, 3000);

-- LABORATOR 2

SELECT ABS(TO_NUMBER ('-125.789',999.999))
FROM dual;

SELECT RPAD (LOWER('InfO'), 11)
FROM dual;

SELECT ADD_MONTHS('06-MAR-2020', 12)
FROM dual;

1. Scrie?i o cerere care are urm?torul rezultat pentru fiecare angajat:
<prenume angajat> <nume angajat> castiga <salariu> lunar dar doreste <salariu de 3 ori
mai mare>. Etichetati coloana “Salariu ideal”. Pentru concatenare, utiliza?i atât func?ia
CONCAT cât ?i operatorul “||”.

SELECT CONCAT(first_name, last_name) ||' castiga '|| salary
|| ' lunar, dar doreste '||3*salary "Salariu ideal"
FROM employees;

2. Scrie?i o cerere prin care s? se afi?eze prenumele salariatului cu prima litera majuscul?
?i toate celelalte litere minuscule, numele acestuia cu majuscule ?i lungimea
numelui, pentru angaja?ii al c?ror nume începe cu J sau M sau care au a treia liter? din
nume A. Rezultatul va fi ordonat descresc?tor dup? lungimea numelui. Se vor eticheta
coloanele corespunz?tor. Se cer 2 solu?ii (cu operatorul LIKE ?i func?ia SUBSTR).

--LIKE

SELECT initcap(first_name) Prenume, upper(last_name) Nume,length(last_name) Lungime
FROM employees
WHERE upper(last_name) LIKE 'J%' or upper(last_name) LIKE 'M%' or upper(last_name) LIKE '__A%'
ORDER BY length(last_name) DESC;

--SUBSTR

SELECT initcap(first_name) Prenume, upper(last_name) Nume,length(last_name) Lungime
FROM employees
WHERE upper(last_name) LIKE 'J%' or upper(last_name) LIKE 'M%' or substr(upper(last_name), 3, 1) = 'A';

4. S? se afi?eze pentru to?i angaja?ii al c?ror nume se termin? cu litera 'e', codul, numele,
lungimea numelui ?i pozi?ia din nume în care apare prima data litera 'A'. Utiliza?i alias-uri
corespunz?toare pentru coloane. 

SELECT employee_id, last_name, length(last_name), instr(upper(last_name), 'A', 1, 1) PozitieLitera
FROM employees
WHERE substr(last_name, -1)='e';

SELECT ROUND(TO_DATE('17-06-1987','dd-mm-yyyy') - sysdate)
from dual;


-- TEMA EXERCITIUL 5

5. S? se afi?eze detalii despre salaria?ii care au lucrat un num?r întreg de s?pt?mâni pân?
la data curent?.
Obs: Solu?ia necesit? rotunjirea diferen?ei celor dou? date calendaristice. De ce este necesar
acest lucru?

SELECT last_name
FROM employees
WHERE MOD(ROUND(SYSDATE - hire_date), 7) = 0;

--LABORATORUL 3(la facultate), ex din lab 2

6. S? se afi?eze codul salariatului, numele, salariul, salariul m?rit cu 15%, exprimat cu
dou? zecimale ?i num?rul de sute al salariului nou rotunjit la 2 zecimale. Eticheta?i
ultimele dou? coloane “Salariu nou”, respectiv “Numar sute”. Se vor lua în considerare
salaria?ii al c?ror salariu nu este divizibil cu 1000.

SELECT employee_id, last_name, salary, round(salary*1.15, 2) "Salariu nou", round(salary*1.15/100, 2) "Numar sute"
FROM employees
WHERE MOD(salary, 1000) != 0;  /* diferit => != sau <> sau ^= */

7. S? se listeze numele ?i data angaj?rii salaria?ilor care câ?tig? comision. S? se
eticheteze coloanele „Nume angajat”, „Data angajarii”. Utiliza?i func?ia RPAD pentru a
determina ca data angaj?rii s? aib? lungimea de 20 de caractere.

SELECT last_name "Nume Angajat", RPAD(hire_date, 20, 'X') "Data angajarii"
FROM employees
WHERE commission_pct is not NULL;

8. S? se afi?eze data (numele lunii, ziua, anul, ora, minutul si secunda) de peste 30 zile.

SELECT TO_CHAR(SYSDATE+30, 'MONTH/DD/YYYY HH24:MI:SS') Data
FROM DUAL;

9. Sa se afiseze numarul de zile ramase pana la sfarsitul anului.

SELECT ROUND(TO_DATE('31/12/2020','DD/MM/YYYY')-sysdate)
FROM dual;

10. a) S? se afi?eze data de peste 12 ore.

SELECT TO_CHAR(SYSDATE+12/24, 'DD/MM HH24:MI:SS') Data
FROM DUAL;

b) S? se afi?eze data de peste 5 minute
Obs: Cât reprezint? 5 minute dintr-o zi?

1h... 60m
x.... 5m -> x=5/60 in raport cu ora

in raport cu ziua -> (5/60)/24

SELECT TO_CHAR(SYSDATE+5/60/24, 'DD/MM HH24:MI:SS') Data
FROM DUAL;

/* Exercitiile 11, 12 rezolva */

11. S? se afi?eze numele ?i prenumele angajatului (într-o singur? coloan?), data angaj?rii ?i
data negocierii salariului, care este prima zi de Luni dup? 6 luni de serviciu. Eticheta?i
aceast? coloan? “Negociere”.

SELECT concat(last_name, first_name), hire_date,
NEXT_DAY(ADD_MONTHS(hire_date, 6), 'monday') "Negociere"
FROM employees;

12. Pentru fiecare angajat s? se afi?eze numele ?i num?rul de luni de la data angaj?rii.
Eticheta?i coloana “Luni lucrate”. S? se ordoneze rezultatul dup? num?rul de luni lucrate.
Se va rotunji num?rul de luni la cel mai apropiat num?r întreg.

SELECT last_name, months_between(sysdate, hire_date) "Luni lucrate"
FROM employees
ORDER BY "Luni lucrate";

Sau:
…
ORDER BY “Luni lucrate”;
Sau
…
ORDER BY 2;

!!!13. S? se afi?eze numele angaja?ilor ?i comisionul. Dac? un angajat nu câ?tig? comision, s?
se scrie “Fara comision”. Eticheta?i coloana “Comision”.

SELECT last_name, NVL(TO_CHAR(commission_pct), 'Fara comision') Comision
FROM employees;

!!!14.

SELECT last_name, salary, commission_pct
FROM employees
WHERE salary + salary * nvl(commission_pct, 0) > 10000;

14. S? se listeze numele, salariul ?i comisionul tuturor angaja?ilor al c?ror venit lunar
(salariu + valoare comision) dep??e?te 10.000;

SELECT last_name, salary, commission_pct
FROM employees
WHERE salary + salary * nvl(commission_pct, 0) > 10000;

SELECT 10 + 10 * NULL
from dual; -> null

select 10 + NULL
from dual; -> null

15. S? se afi?eze numele, codul functiei, salariul ?i o coloana care s? arate salariul dup?
m?rire. Se ?tie c? pentru IT_PROG are loc o m?rire de 10%, pentru ST_CLERK 15%, iar
pentru SA_REP o m?rire de 20%. Pentru ceilalti angajati nu se acord? m?rire. S? se
denumeasc? coloana "Salariu renegociat"

SELECT last_name, job_id, salary,
        DECODE(job_id,
        'IT_PROG', salary*1.1,
        'ST_CLERK', salary*1.15,
        'SA_REP', salary*1.2,
        salary) "Salariu renegociat"
FROM employees;

-- Sau

SELECT last_name, job_id, salary,
        CASE job_id WHEN 'IT_PROG' THEN salary* 1.1
                    WHEN 'ST_CLERK' THEN salary* 1.15
                    WHEN 'SA_REP' THEN salary* 1.2
        ELSE salary
        END "Salariu renegociat"
FROM employees;

-- JOIN

select * from departments;

select * from employees;

16. S? se afi?eze codul angajatilor ?i numele departamentului pentru to?i angaja?ii.
I. Condi?ia de Join este scris? în clauza WHERE a instruc?iunii SELECT

select employee_id, department_name
from employees e, departments d; --> produs cartezian

select employee_id, department_name
from employees e, departments d
where e.department_id = d.department_id;

De ce afiseaza 106 in loc de 107???

select last_name, employee_id, job_id
from employees
where department_id is null; --> Grant 178 nu are departament

--> In employees_id este cheie externa, deci poate fi null
--> De aceea avem un angajat care nu are departament

Exista simbolul (+) care se pune in dreptul coloanei (din conditia de join)
unde se afla deficit de informatie

-- Vrem sa afisam si angajatii care nu au departament

select employee_id, department_name
from employees e, departments d
where e.department_id = d.department_id (+);

-- Vrem sa afisam si departamentele care nu au angajati

select employee_id, department_name
from employees e, departments d
where e.department_id (+) = d.department_id;

-- ALIAS-ul

select employee_id, department_name, d.department_id
from employees, departments d
where employees.department_id = d.department_id;

II. Condi?ia de Join este scris? în FROM

Utiliz?m ON:
select employee_id, department_name
from employees e join departments d on (e.department_id = d.department_id);

Utiliz?m USING – atunci când avem coloane cu acela?i nume:
select employee_id,department_name
from employees e join departments d using(department_id);


17. S? se listeze codurile ?i denumirile job-urilor care exist? în departamentul 30.

SELECT j.job_id, job_title
FROM jobs j, employees e
WHERE department_id = 30 and j.job_id = e.job_id;

18. S? se afi?eze numele angajatului, numele departamentului ?i id-ul loca?iei pentru to?i
angaja?ii care câ?tig? comision.

SELECT last_name, department_name, location_id
FROM employees e, departments d
WHERE e.department_id = d.department_id AND commission_pct is not null;

19. S? se afi?eze numele, titlul job-ului ?i denumirea departamentului pentru to?i angaja?ii
care lucreaz? în Oxford.

SELECT last_name, job_title, department_name
FROM employees e, jobs j, departments d, locations l
WHERE e.job_id=j.job_id and
        e.department_id = d.department_id and
        d.location_id = l.location_id and 
        initcap(l.city) = 'Oxford'; -- nu merge
        
20. S? se afi?eze codul angajatului ?i numele acestuia, împreun? cu numele ?i codul
?efului s?u direct. Se vor eticheta coloanele Ang#, Angajat, Mgr#, Manager.

SELECT ang.employee_id Ang#, ang.last_name Angajat, sef.employee_id Mgr#,
sef.last_name Manager
FROM employees ang, employees sef
WHERE ang.manager_id = sef.employee_id;

SELECT * from employees;

21. S? se modifice cererea anterioar? pentru a afi?a to?i salaria?ii, inclusiv cei care nu au ?ef.

SELECT ang.employee_id Ang#, ang.last_name Angajat, sef.employee_id Mgr#,
sef.last_name Manager
FROM employees ang, employees sef
WHERE ang.manager_id = sef.employee_id (+);

22. Scrie?i o cerere care afi?eaz? numele angajatului, codul departamentului în care
acesta lucreaz? ?i numele colegilor s?i de departament. Se vor eticheta coloanele
corespunz?tor.

SELECT ang.last_name, ang.department_id, coleg.last_name
FROM employees ang, employees coleg
WHERE ang.department_id=coleg.department_id and ang.employee_id < coleg.employee_id;

--- TEMA 23, 25

23. Crea?i o cerere prin care s? se afi?eze numele angajatilor, codul job-ului, titlul job-ului,
numele departamentului ?i salariul angaja?ilor. Se vor include ?i angaja?ii al c?ror
departament nu este cunoscut.

SELECT last_name, e.job_id, job_title, department_name, salary
FROM jobs j, employees e, departments d
WHERE d.department_id (+)=e.department_id and j.job_id=e.job_id;


SELECT last_name, job_id, department_id, salary
FROM employees;

24. S? se afi?eze numele ?i data angaj?rii pentru salaria?ii care au fost angaja?i dup? Gates.

select ang.last_name, ang.hire_date, gates.last_name, gates.hire_date
FROM employees ang, employees gates
WHERE ang.hire_date > gates.hire_date AND initcap(gates.last_name)='Gates';

25. S? se afi?eze numele salariatului ?i data angaj?rii împreun? cu numele ?i data angaj?rii
?efului direct pentru salaria?ii care au fost angaja?i înaintea ?efilor lor. Se vor eticheta
coloanele Angajat, Data_ang, Manager si Data_mgr.

SELECT ang.last_name Angajat, ang.hire_date Data_ang, m.last_name Manager, m.hire_date Data_mgr
FROM employees ang, employees m
WHERE ang.manager_id = m.employee_id AND ang.hire_date < m.hire_date;

--- Laborator 3

SELECT last_name, salary, grade_level, lowest_sal, highest_sal
FROM employees, job_grades
WHERE salary BETWEEN lowest_sal AND highest_sal;

SELECT *
FROM job_grades;

SELECT last_name, department_id, department_name 
FROM employees 
NATURAL JOIN departments; --returneaza 32 de rezultate pentru ca au si manager id si department id comune

SELECT last_name, e.job_id, job_title
FROM employees e, jobs j
WHERE e.job_id = j.job_id;

-- JOIN

SELECT last_name, department_name, location_id
FROM employees e, departments d
WHERE e.department_id=d.department_id;

--USING SQL 3
SELECT last_name, department_name, location_id
FROM employees JOIN departments USING (department_id);

-- ON
SELECT last_name, department_name, location_id
FROM employees e JOIN departments d ON (e.department_id=d.department_id);

--dorim sa afisam si angajatii fara departament

SELECT last_name, department_name, location_id
FROM employees e, departments d
WHERE e.department_id=d.department_id (+);

--dorim sa afisam TOTI angajatii, chiar daca au sau nu departament

SELECT last_name, department_name, location_id
FROM employees e LEFT JOIN departments d ON (e.department_id=d.department_id);

--dorim sa afisam TOTATE departamentele, chiar daca au sau nu angajati

SELECT last_name, department_name, location_id
FROM employees e RIGHT JOIN departments d ON (e.department_id=d.department_id);

--dorim sa afisam TOTATE departamentele, chiar daca au sau nu angajati
--dorim sa afisam TOTI angajatii, chiar daca au sau nu departament
-- plus intersectia, elementele comune
SELECT last_name, department_name, location_id
FROM employees e FULL JOIN departments d ON (e.department_id=d.department_id);


1. Scrie?i o cerere pentru a se afisa numele, luna (în litere) ?i anul angaj?rii pentru to?i
salaria?ii din acelasi departament cu Gates, al c?ror nume con?ine litera “a”. Se va
exclude Gates.

SELECT ang.last_name, TO_CHAR(ang.hire_date, 'month-yyyy'), gates.last_name
FROM employees ang join employees gates ON (ang.department_id=gates.department_id)
WHERE initcap(gates.last_name) = 'Gates' and lower(ang.last_name) like '%a%'
    and initcap(ang.last_name) != 'Gates';

2. S? se afi?eze codul ?i numele angaja?ilor care lucreaz? în acela?i departament cu
cel pu?in un angajat al c?rui nume con?ine litera “t”. Se vor afi?a, de asemenea, codul ?i
numele departamentului respectiv. Rezultatul va fi ordonat alfabetic dup? nume.

SELECT distinct e1.employee_id, e1.last_name, d.department_id, d.department_name
FROM employees e1 join employees e2 ON (e1.department_id=e2.department_id)
                join departments d on (e1.department_id=d.department_id)
WHERE lower(e2.last_name) like '%t%'
ORDER by e1.last_name;

3. S? se afi?eze numele, salariul, titlul job-ului, ora?ul ?i ?ara în care lucreaz?
angaja?ii condu?i direct de King.

SELECT e.last_name, e.salary, j.job_title, city, country_name, k.last_name
FROM employees e join employees k on(e.manager_id=k.employee_id)
                join jobs j on(e.job_id=j.job_id)
                join departments d on(e.department_id=d.department_id)
                join locations l on(l.location_id=d.location_id)
                join countries c on(l.country_id=c.country_id)
WHERE lower(k.last_name) like 'king';
    


4. S? se afi?eze codul departamentului, numele departamentului, numele ?i job-ul
tuturor angaja?ilor din departamentele al c?ror nume con?ine ?irul ‘ti’. De asemenea, se
va lista salariul angaja?ilor, în formatul “$99,999.00”. Rezultatul se va ordona alfabetic
dup? numele departamentului, ?i în cadrul acestuia, dup? numele angaja?ilor.

SELECT d.department_id, department_name, job_id, last_name, to_char(salary,'$99,999.00')
FROM employees e JOIN departments d ON (e.department_id = d.department_id)
WHERE lower(department_name) like '%ti%'
ORDER BY d.department_name, e.last_name;


5. Cum se poate implementa full outer join?

Obs: Full outer join se poate realiza fie prin reuniunea rezultatelor lui right outer join
?i left outer join, fie utilizând sintaxa specific? standardului SQL3.

-- varianta 1 cu join

--dorim sa afisam TOTATE departamentele, chiar daca au sau nu angajati
--dorim sa afisam TOTI angajatii, chiar daca au sau nu departament
-- plus intersectia, elementele comune
SELECT distinct last_name, department_name, location_id
FROM employees e FULL JOIN departments d ON (e.department_id=d.department_id); -- 123 de rezultate fara distinct



-- varianta 2 operatori pe multimi

SELECT last_name, department_name, location_id
FROM employees e LEFT JOIN departments d ON (e.department_id=d.department_id)

UNION -- elementele comune si necomune luate o singura data                 -- 121 de rezultate, face si ordonare

SELECT last_name, department_name, location_id
FROM employees e RIGHT JOIN departments d ON (e.department_id=d.department_id);


6. Se cer codurile departamentelor al c?ror nume con?ine ?irul “re” sau în care
lucreaz? angaja?i având codul job-ului “SA_REP”.
Cum este ordonat rezultatul?

-- cu JOIN

SELECT distinct d.department_id
FROM departments d full join employees e on (d.department_id=e.department_id)
WHERE lower(d.department_name) like '%re%' or upper(e.job_id) LIKE '%SA_REP%';


-- operatori pe multimi

SELECT department_id
FROM departments
WHERE lower(department_name) like '%re%' -- 40, 70, 120, 140, 150, 250, 260

UNION                              -- 40, 70, 80, 120, 140, 150, 250,

SELECT department_id
FROM employees
WHERE upper(job_id) LIKE '%SA_REP%'; -- 80 si NULL



7. Ce se întâmpl? dac? înlocuim UNION cu UNION ALL în comanda precedent??





Obs(la 8): Operatorii pe mul?imi pot fi utiliza?i în subcereri. Coloanele care apar în clauza
WHERE a interog?rii trebuie s? corespund?, ca num?r ?i tip de date, celor din clauza SeELECT a subcererii
8. S? se ob?in? codurile departamentelor în care nu lucreaza nimeni (nu este introdus
nici un salariat în tabelul employees). Se cer dou? solu?ii.



-- varianta 1 cu JOIN
-- dorim sa afisam departamente fara angajati

SELECT d.department_id 
FROM employees e right join departments d on(e.department_id=d.department_id)
WHERE e.department_id is null;

-- varianta 2

SELECT department_id "Cod departament"
FROM departments        -- din lista tuturor departamentelor(lista unica, department_id e cheie primara) 
MINUS                   -- eliminam
SELECT department_id
FROM employees;         -- departamentele in care lucreaza angajati (department_id e cheie externa)

-> departamentele fara angajati

-- varianta 3








Utilizând subcereri:
SELECT department_id
FROM departments
WHERE department_id NOT IN (SELECT DISTINCT NVL(department_id,0)
FROM employees);
? În a doua variant?, de ce este nevoie de utilizarea func?iei NVL?