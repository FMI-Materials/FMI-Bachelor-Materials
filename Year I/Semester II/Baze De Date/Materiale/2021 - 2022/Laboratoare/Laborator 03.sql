port 1521 
host 193.226.51.37   host 193.226.51.46
sid o11g
grupa212 grupa212

--3.7. S? se afi?eze numele salaria?ilor ?i numele departamentelor în care lucreaz?. Se vor
--afi?a ?i salaria?ii care nu au asociat un departament. (left outer join, 2 variante).

select e.last_name, e.department_id, d.department_id, d.department_name
from employees e left join departments d on (e.department_id = d.department_id);

select e.last_name, e.department_id, d.department_id, d.department_name
from departments d right join employees e  on (e.department_id = d.department_id);

select e.last_name, e.department_id, d.department_id, d.department_name
from employees e, departments d 
where e.department_id = d.department_id(+);

9. S? se afi?eze numele departamentelor ?i numele salaria?ilor care lucreaz? în ele. Se
vor afi?a ?i departamentele care nu au salaria?i. (left outer join, 2 variante)

select e.last_name, e.department_id, d.department_id, d.department_name
from employees e right join departments d on (e.department_id = d.department_id);

select e.last_name, e.department_id, d.department_id, d.department_name
from departments d left join employees e  on (e.department_id = d.department_id);

select e.last_name, e.department_id, d.department_id, d.department_name
from employees e, departments d 
where e.department_id(+) = d.department_id;

select commission_pct, nvl(commission_pct, 0) 
from employees;

***
S? se afi?eze codul angajatului ?i numele acestuia, împreun? cu numele ?i codul
?efului s?u direct. Se vor eticheta coloanele Ang#, Angajat, Mgr#, Manager. 
Pentru ang care nu au manager direct se va afisa in loc de nume manager 'manager necunsocut';

select e.employee_id "Ang#", e.last_name "Angajat", 
   	   m.employee_id "Mgr#", nvl(m.last_name, 'manager necunoscut') "Manager"
from employees e, employees m
where e.manager_id = m.employee_id(+);

--
select e.employee_id "Ang#", nvl(e.last_name, 'nu are subordonati') "Angajat", 
   	   m.employee_id "Mgr#", m.last_name "Manager"
from employees e  right join  employees m
on e.manager_id = m.employee_id;

select e.employee_id "Ang#", e.last_name "Angajat", 
   	   m.employee_id "Mgr#", nvl(m.last_name, 'manager necunoscut') "Manager"
from employees e left join employees m 
      on e.manager_id = m.employee_id;


select e.last_name, e.department_id, d.department_id, d.department_name
from departments d full outer join employees e  on (e.department_id = d.department_id);


***
sa se afiseze pentru fiecare departament numele, numele managerului de departament
si titlul jobului managerului de departament.
pentru departamentele pentru care nu este cunoscut managerul se va afisa 'necunoscut';

select d.department_name, e.last_name, nvl(e.job_id, 'necunoscut')
from departments d  left join employees e  on (d.manager_id = e.employee_id)
                    left join jobs j on (e.job_id = j.job_id); 
                    

select d.department_name, e.last_name, nvl(e.job_id, 'necunoscut')
from departments d, employees e , jobs j 
where d.manager_id = e.employee_id(+)   and 
      e.job_id = j.job_id(+);                     
      

--decode case 
--2.16
16. S? se afi?eze numele, codul job-ului, salariul ?i o coloan? care s? arate salariul dup?
m?rire. Se presupune c? pentru IT_PROG are loc o m?rire de 20%, pentru SA_REP
cre?terea este de 25%, iar pentru SA_MAN are loc o m?rire de 35%. Pentru ceilal?i
angaja?i nu se acord? m?rire. S? se denumeasc? coloana "Salariu renegociat". 
                    


select last_name, job_id, salary, 
           case when job_id = 'IT_PROG' THEN salary * 1.20
                when job_id = 'SA_REP' THEN salary * 1.25
                when job_id = 'SA_MAN' THEN salary * 1.35
           else salary
           end "Salariu renegociat"           
from employees;

select last_name, job_id, salary, 
           case job_id when 'IT_PROG' THEN salary * 1.20
                       when 'SA_REP' THEN salary * 1.25
                       when 'SA_MAN' THEN salary * 1.35
           else salary
           end "Salariu renegociat"           
from employees;

select last_name, job_id, salary, 
           decode(job_id, 'IT_PROG',salary * 1.20,'SA_REP',salary * 1.25,
                          'SA_MAN', salary * 1.35,  salary)  "Salariu renegociat"           
from employees;


***sa se afiseze numele ang si codul tarii in care lucreaza
coloana tara va fi completata cu 'departament necunoscut' sau 'cod tara necunoscut'
sa se ordoneze angajatii in ordinea alfabetica a codurilor de tari,
execptie: angajatii din 'US' vor fi afisati primii in lista.
angajatii din aceeasi tara vor fi sortati alfabetic dupa nume

select e.last_name,
    decode(d.department_id, null, 'dep necunoscut',  
                nvl( l.country_id,  'cod tara necunsocut')) 
from employees e   left   join    departments d   on (e.department_id = d.department_id)
                   left   join    locations l    on (d.location_id = l.location_id) 
order by case when l.country_id = 'US' then 0 
              when l.country_id is not null then 1
              else 2 end , 
l.country_id , e.last_name
;

update locations set country_id = null where location_id = 1700;
commit;


select d.department_name, e.last_name, d.department_id, d.location_id, l.*
from departments d  right join employees e  on (d.manager_id = e.employee_id)
left join locations l on (d.location_id = l.location_id)
