-- LABORATOR 6

desc projects;

desc works_on;

select * from projects;

select * from works_on;

Exemplu: S? se ob?in? codurile salaria?ilor ata?a?i tuturor proiectelor 
pentru care s-a alocat un buget egal cu 10000.

--Metoda 1 (utilizând de 2 ori NOT EXISTS):
SELECT DISTINCT employee_id
FROM works_on a
WHERE NOT EXISTS
    (SELECT 1
     FROM projects p
     WHERE budget = 10000
     AND NOT EXISTS
            (SELECT 'x'
             FROM works_on b
             WHERE p.project_id = b.project_id
             AND b.employee_id = a.employee_id
            )
    );
-- metoda 1 este identinca cu metoda 4

Exemplu: S? se ob?in? codurile salaria?ilor ata?a?i tuturor proiectelor 
pentru care s-a alocat un buget egal cu 10000.

select * from projects; -- lista tuturor proiectelor
-- observam ca p2 si p3 au buget egal cu 10k

select * from works_on; -- lista angajatilor care lucreaza la proiecte
-- observam ca angajatii 145, 148, 101, 200 lucreaza la TOATE proiectele cu buget de 10k

--Metoda 2 (simularea diviziunii cu ajutorul func?iei COUNT):
SELECT employee_id
FROM works_on  -- lista tuturor angajatilor care lucreaza la proiecte
WHERE project_id IN
            (SELECT project_id
             FROM projects
             WHERE budget = 10000 -- proiectele care au buget EGAL de 10k (p2 si p3)
            ) -- daca ne oprim cu solutia in acest punct obtinem angajatii care lucreaza atat la 
              -- toate proiectele cu buget egal cu 10k, cat si la o parte din proiectele
              -- cu buget egal cu 10k          
GROUP BY employee_id -- grupand putem numara pentru fiecare angajat proiectele cu buget de 10k la care lucreaza
HAVING COUNT(project_id)= (SELECT COUNT(*)
                           FROM projects
                           WHERE budget = 10000
                          ); -- si daca nr proiectelor la care lucreaza este egal cu nr proiectelor cu
                             -- buget egal cu 10k => ca ang lucreaza la TOATE proiectele care au buget
                             -- egal cu 10k si nu doar la o parte din ele



Exemplu: S? se ob?in? codurile salaria?ilor ata?a?i tuturor proiectelor 
pentru care s-a alocat un buget egal cu 10000.

select * from projects; -- lista tuturor proiectelor
-- observam ca p2 si p3 au buget egal cu 10k

select * from works_on; -- lista angajatilor care lucreaza la proiecte
-- observam ca angajatii 145, 148, 101, 200 lucreaza la TOATE proiectele cu buget de 10k

--Metoda 3 (operatorul MINUS):
SELECT employee_id
FROM works_on  -- lista tuturor angajatilor care lucreaza la proiecte

MINUS  -- dorim sa eliminam angajatii care lucreaza la proiecte cu buget DIFERIT de 10k
       -- sau pe cei care lucreaza doar la o parte din proiectele cu buget EGAL cu 10k
       -- in final dorim sa obtinem doar angajatii care lucreaza la TOATE proiectele cu buget de 10k

SELECT employee_id from
        ( SELECT employee_id, project_id
          FROM (SELECT DISTINCT employee_id FROM works_on) t1,
               (SELECT project_id FROM projects WHERE budget = 10000) t2
               
          MINUS
          
          SELECT employee_id, project_id FROM works_on -- (*)
        ) t3;
        
in baza de date avem (luam 2 exemple):
ang 148 care lucreaza la p2 si p3
ang 176 care lucreaza la p3 (*) - lista angajatilor care lucreaza la proiecte 

t1 - o lista de angajati care lucreaza la proiecte
t2 - lista proiectelor cu buget de 10k 
produsul cartezian t1 cu t2 - (luand elementele 148 si 176 ca exemplu)
   rezulta -> 148 - p2 / 148 - p3
              176 - p2 / 176 - p3
              etc (combinand toti angajatii cu proiectele cu buget de 10k)

-> din produsul cartezian se elimina (*) care reprezinta lista angajatilor care lucreaza la proiecte 
rezulta => un ang care lucreaza la toate proiectele cu buget de 10k o sa fie eliminat (ex: ang 148)
           176 ramane in lista deoarece el lucreaza doar la o parte din proiectele cu buget de 10k
           
Prin urmare in t3 ramane o lista cu angajatii care lucreaza la proiecte cu buget diferit de 10k
sau doar la o parte din proiectele cu buget egal cu 10k !!!!!!!!!
        
In final obtinem doar angajatii care lucreaza la TOATE proiectele cu buget de 10k        
        
        
--Metoda 4 (A include B => B\A = Ø):
SELECT DISTINCT employee_id
FROM works_on a  -- lista tuturor ang care lucreaza la proiecte
WHERE NOT EXISTS 
    (
        (SELECT project_id
         FROM projects p
         WHERE budget = 10000 -- proiectele cu buget egal cu 10k (p2 si p3)
         )
         
         MINUS -- din lista proiectelor cu buget de 10k elimin proiectele la care lucreaza ang curent
              -- atunci daca ang curent lucreaza la toate proiectele cu buget de 10k, in subcerere se obtine
              -- multimea vida
              -- daca ang lucreaza la o parte din proiectele cu buget de 10k sau la alte proiecte cu buget
              -- diferit de 10k, atunci angajatul respectiv o sa ramana in lista obtinuta in subcerere
         
        (SELECT p.project_id
         FROM projects p, works_on b
         WHERE p.project_id = b.project_id
         AND b.employee_id = a.employee_id -- lista proiectelor la care lucreaza angajatul CURENT (sincronizare)
        ) -- in subcerere raman ang care lucreaza la proiecte cu buget diferit de 10k sau 
          -- doar la o parte din proiectele cu buget de 10k
    );
-- in final se obtin ang care lucreaza la TOATE proiectele cu buget de 10k. 

Exerci?ii (DIVISION + alte cereri):

1. S? se listeze informa?ii despre angaja?ii care au lucrat în TOATE proiectele 
demarate în primele 6 luni ale anului 2006.

select * from projects;

select employee_id, last_name, first_name
from employees
where employee_id in (select employee_id
                      from works_on -- angajati care lucreaza la proiecte
                      where project_id in (select project_id
                                           from projects
                                           where start_date >= to_date('01-jan-06')
                                           and start_date <= to_date('30-jun-06') 
                                               -- lista proiectelor demarate in primele 6 luni(p1 si p2)
                                           )
                       -- daca ne oprim cu solutia in acest punct obtinem angajatii care lucreaza 
                       -- la toate proiectele demarate in primele 6 luni ale lui 2006
                       -- dar si pe cei care lucreaza doar la o parte din proiectele demarate in primele 6 luni din 2006
                      group by employee_id -- grupand putem numara pt fiecare angajat proiectele la care lucreaza
                      having count(project_id) = (select count(project_id)
                                                  from projects
                                                  where start_date >= to_date('01-jan-06')
                                                  and start_date <= to_date('30-jun-06') 
                                                 ) -- daca nr de proiecte este egal cu nr proiectelor demarate in primele
                                                 -- 6 luni din 2006 => ca ang lucreaza la TOATE proiectele acestea
                                                
                      );

2. S? se listeze informa?ii despre proiectele la care au participat to?i angaja?ii 
care au de?inut alte 2 posturi în firm?.

select *
from projects -- lista tuturor proiectelor
where project_id in (select project_id
                     from works_on -- proiecte la care lucreaza angajati
                     where employee_id in 
                                (select employee_id
                                 from job_history
                                 group by employee_id 
                                 having count(job_id) = 2
                                 ) --angaja?ii care au de?inut alte 2 posturi în firm? (101, 176, 200)
                    group by project_id -- grupand putem numara angajatii pentru fiecare proiect
                    having count(employee_id) = (select count(count(employee_id))
                                                 from job_history
                                                 group by employee_id 
                                                 having count(job_id) = 2
                                                 )
                                                 -- daca nr de ang care lucreaza la un proiecte este egal 
                                                 -- cu nr de angajati care au detinut alte doua posturi in firma
                                                 -- atunci inseamna ca la acel proiect au participat toti ang care 
                                                 -- au detinut alte doua posturi in firma
                     );   

3. S? se ob?in? num?rul de angaja?i care au avut cel pu?in trei job-uri, luându-se în considerare ?i job-ul curent.
-- inseamna cel putin doua joburi in trecut - in job_history
select count(count(employee_id)) NrAng
from job_history
group by employee_id 
having count(job_id) >= 2;

4. Pentru fiecare ?ar?, s? se afi?eze num?rul de angaja?i din cadrul acesteia.

select count(employee_id)
from employees join departments using (department_id)
               join locations using (location_id)
               right join countries using (country_id)
group by country_id;

Tema: laborator 6: ex: 5, 6, 7
Deadline: 25.04 (sambata inclusiv)

5. S? se listeze codurile angaja?ilor ?i codurile proiectelor pe care au lucrat. Listarea va cuprinde ?i angaja?ii care nu au lucrat pe nici un proiect.

SELECT e.employee_id, project_id
FROM employees e left join works_on w on (e.employee_id=w.employee_id);

6. S? se afi?eze angaja?ii care lucreaz? în acela?i departament cu cel pu?in un manager de proiect.

SELECT employee_id
FROM employees
WHERE department_id in(
                    SELECT department_id -- 60, 90
                    FROM employees JOIN projects ON (employee_id=project_manager)
                    GROUP BY department_id -- un angajat e managerul a doua proiecte
         )
        AND employee_id NOT IN( -- nu afisez si managerii de proiect(in acest caz lucreaza in departamente diferite)
                            SELECT project_manager -- 102, 103
                            FROM projects
                            GROUP BY project_manager -- 102 e managerul a doua proiecte
                            );

7. S? se afi?eze angaja?ii care nu lucreaz? în acela?i departament cu nici un manager de proiect.

SELECT employee_id, department_id
FROM employees
WHERE department_id NOT IN(
                    SELECT department_id 
                    FROM employees JOIN projects ON (employee_id=project_manager)
                    GROUP BY department_id -- un angajat e managerul a doua proiecte
         );

8. S? se determine departamentele având media salariilor mai mare decât un num?r dat.

