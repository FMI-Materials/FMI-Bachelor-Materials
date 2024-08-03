select employee_id, (select first_name
                    from employees
                    where employee_id in (100)) nume
from employees;

SELECT employee_id, last_name,salary * 12 sal
FROM employees
where salary*12>70000
order by sal desc;

desc departments;
--3. S? se afi?eze numele salaria?ilor ?i codul departamentelor pentru
--toti angaja?ii din departamentele 10 ?i 30 în ordine alfabetic? a numelor.
SELECT last_name, department_id depart
from employees
where department_id IN (10, 30)
order by depart;


select last_name, hire_date, department_name
 from employees
 join departments using (department_id)
 where to_char(hire_date, 'yyyy') = 1987
 order by 1;
 
-- 
-- 11. S? se afiseze numele, job-ul si salariul pentru toti 
-- salariatii al caror job con?ine ?irul “CLERK” sau “REP”
-- ?i salariul nu este egal cu 1000, 2000 sau 3000. (operatorul NOT IN)
 
 
 select last_name, job_id, salary
 from employees
 where (upper(job_id) like upper('%cLERK%') or upper(job_id) like '%REP%') and salary not in (1000, 2000, 3000); --76
 
 
-- 12. S? se afi?eze numele salaria?ilor ?i numele departamentelor în care 
-- lucreaz?. Se vor afi?a ?i salaria?ii care nu au asociat un departament.

select last_name, department_name
 from employees e left join departments d using(department_id); --107

SELECT E.FIRST_NAME, E.LAST_NAME, D.DEPARTMENT_Name
FROM EMPLOYEES E, DEPARTMENTS D
WHERE E.DEPARTMENT_ID = D.DEPARTMENT_ID; --106

select count(*)
from employees;

SELECT E.FIRST_NAME, E.LAST_NAME, D.DEPARTMENT_Name
FROM EMPLOYEES E, DEPARTMENTS D
WHERE E.DEPARTMENT_ID = D.DEPARTMENT_ID(+);
--William	Gietz	Accounting
--Shelley	Higgins	Accounting
--Kimberely	Grant	null

--13. S? se afi?eze numele departamentelor ?i numele salaria?ilor care 
--lucreaz? în ele. Se vor afi?a ?i departamentele care nu au salaria?i.

select last_name, department_name
 from employees e right join departments d using(department_id);

--Higgins	Accounting
--Gietz	Accounting
--null	Treasury
--null	Corporate Tax

SELECT E.FIRST_NAME,  D.DEPARTMENT_Name
FROM EMPLOYEES E, DEPARTMENTS D
WHERE E.DEPARTMENT_ID(+) = D.DEPARTMENT_ID; --122


SELECT E.FIRST_NAME,  D.DEPARTMENT_Name
FROM EMPLOYEES E, DEPARTMENTS D
WHERE E.DEPARTMENT_ID(+) = D.DEPARTMENT_ID(+); --nu


SELECT E.FIRST_NAME,  D.DEPARTMENT_Name
FROM EMPLOYEES E, DEPARTMENTS D
WHERE E.DEPARTMENT_ID(+) = D.DEPARTMENT_ID
union 
SELECT E.FIRST_NAME,  D.DEPARTMENT_Name
FROM EMPLOYEES E, DEPARTMENTS D
WHERE E.DEPARTMENT_ID = D.DEPARTMENT_ID(+);  --117 (nu este bine)

SELECT E.EMPLOYEE_ID,E.FIRST_NAME,  D.DEPARTMENT_Name
FROM EMPLOYEES E, DEPARTMENTS D
WHERE E.DEPARTMENT_ID(+) = D.DEPARTMENT_ID
union
SELECT E.EMPLOYEE_ID, E.FIRST_NAME,  D.DEPARTMENT_Name
FROM EMPLOYEES E, DEPARTMENTS D
WHERE E.DEPARTMENT_ID = D.DEPARTMENT_ID(+); --123 corect

--14. S? se afi?eze codul angajatului ?i numele acestuia, împreun? cu numele ?i codul ?efului s?u direct.

Select e.EMPLOYEE_ID, e.LAST_NAME, man.employee_id, man.last_name
from employees e 
join employees man
on e.MANAGER_ID =man.EMPLOYEE_ID;


15. S? se modifice cererea anterioar? pentru a afi?a to?i salaria?ii, inclusiv cei care nu au ?ef.

Select e.EMPLOYEE_ID, e.LAST_NAME, man.employee_id, man.last_name
from employees e left
join employees man
on e.MANAGER_ID =man.EMPLOYEE_ID;

Select e.EMPLOYEE_ID, e.LAST_NAME,e.manager_id, (select man.last_name
                                                    from employees man
                                                     where man.EMPLOYEE_ID =  e.MANAGER_ID)
from employees e; --107





drop table member cascade constraints;
drop table title cascade constraints;
drop table title_copy cascade constraints;
drop table rental cascade constraints;
drop table reservation cascade constraints;
drop view title_avail;

SELECT 
SYS_CONTEXT('USERENV','NLS_TERRITORY') nls_territory,
SYS_CONTEXT('USERENV','NLS_DATE_FORMAT') nls_date_format,
SYS_CONTEXT('USERENV','NLS_DATE_LANGUAGE') nls_date_language,
SYS_CONTEXT('USERENV','NLS_SORT') nls_sort, 
SYS_CONTEXT('USERENV','LANGUAGE') language
FROM DUAL;

select sysdate from dual;

alter session set NLS_LANGUAGE='AMERICAN';
alter session set NLS_TERRITORY='AMERICA';
alter session set NLS_DATE_LANGUAGE='AMERICAN';



PROMPT Please wait while tables are created.

CREATE TABLE MEMBER(
 member_id    NUMBER (10) CONSTRAINT member_id_pk PRIMARY KEY,
 last_name    VARCHAR2(25) CONSTRAINT member_last_nn NOT NULL,
 first_name   VARCHAR2(25),
 address      VARCHAR2(100),
 city         VARCHAR2(30),
 phone        VARCHAR2(25),
 join_date    DATE DEFAULT SYSDATE CONSTRAINT join_date_nn NOT NULL)
;

CREATE TABLE TITLE(
 title_id     NUMBER(10) CONSTRAINT title_id_pk PRIMARY KEY,
 title  VARCHAR2(60) CONSTRAINT title_nn NOT NULL,
 description  VARCHAR2(400) CONSTRAINT title_desc_nn NOT NULL,
 rating       VARCHAR2(4)  CONSTRAINT title_rating_ck 
   CHECK (rating IN ('G','PG','R','NC17','NR')),
 category     VARCHAR2(20) DEFAULT 'DRAMA' 
   CONSTRAINT title_categ_ck 
   CHECK  (category IN ('DRAMA','COMEDY','ACTION','CHILD','SCIFI','DOCUMENTARY')),
 release_date DATE)
;

CREATE TABLE TITLE_COPY(
 copy_id      NUMBER(10),
 title_id     NUMBER(10)  CONSTRAINT copy_title_id_fk REFERENCES title(title_id),
 status       VARCHAR2(15) CONSTRAINT copy_status_nn NOT NULL
   CONSTRAINT copy_status_ck 
   CHECK (status IN ('AVAILABLE','DESTROYED','RENTED','RESERVED')),
   CONSTRAINT copy_title_id_pk  PRIMARY KEY(copy_id, title_id))
;

CREATE TABLE RENTAL(
 book_date    DATE DEFAULT SYSDATE,
 copy_id      NUMBER(10),
 member_id    NUMBER(10)   
   CONSTRAINT rental_mbr_id_fk REFERENCES member(member_id),
 title_id NUMBER(10),
 act_ret_date DATE,
 exp_ret_date DATE DEFAULT SYSDATE+2,
 CONSTRAINT rental_copy_title_id_fk FOREIGN KEY (copy_id, title_id)
     REFERENCES title_copy(copy_id,title_id), 
 CONSTRAINT rental_id_pk PRIMARY KEY  (book_date, copy_id, title_id, member_id))
;

CREATE TABLE RESERVATION(
 res_date     DATE,
 member_id    NUMBER(10) CONSTRAINT reservation_mbr_id_fk REFERENCES member(member_id),
 title_id     NUMBER(10) CONSTRAINT reservation_title_id_fk REFERENCES title(title_id),
 CONSTRAINT res_id_pk PRIMARY KEY  (res_date, member_id, title_id))
;

PROMPT TABLES CREATED.

SET ECHO ON
CREATE VIEW title_avail 
  AS
    SELECT t.title, c.copy_id, c.status, r.exp_ret_date
    FROM   title t, title_copy c, rental r
    WHERE  t.title_id = c.title_id
    AND	   c.copy_id = r.copy_id (+)
    AND	   c.title_id = r.title_id (+);

---------------------------------------------------------------------

INSERT INTO member VALUES
(101,'Velasquez','Carmen','283 King Street','Seattle','587-99-6666',TO_DATE('03-MAR-1990','DD-MON-YYYY'));  

select * from member;

INSERT INTO member VALUES
(102,'Ngao','LaDoris','5 Modrany','Bratislava','586-355-8882',TO_DATE('08-MAR-1990','DD-MON-YYYY')); 
  
INSERT INTO member VALUES
(103,'Nagayama','Midori','68 Via Centrale','Sao Paolo','254-852-5764',TO_DATE('17-JUN-1991','DD-MON-YYYY'));                

INSERT INTO member VALUES
(104,'Quick-To-See','Mark','6921 King Way','Lagos','63-559-777',TO_DATE('07-APR-1990','DD-MON-YYYY')); 
        
INSERT INTO member VALUES 
(105,'Ropeburn','Audry','86 Chu Street','Hong Kong','41-559-87',TO_DATE('04-MAR-1990','DD-MON-YYYY'));  
                                                                         
INSERT INTO member VALUES
(106,'Urguhart','Molly','3035 Laurier Blvd.','Quebec','418-542-9988',TO_DATE('18-JAN-1991','DD-MON-YYYY'));

INSERT INTO member VALUES 
(107,'Menchu','Roberta','Boulevard de Waterloo 41','Brussels','322-504-2228',TO_DATE('14-MAY-1990','DD-MON-YYYY'));

INSERT INTO member VALUES 
(108,'Biri','Ben','398 High St.','Columbus','614-455-9863',TO_DATE('07-APR-1990','DD-MON-YYYY'));

INSERT INTO member VALUES 
(109,'Catchpole','Antoinette','88 Alfred St.','Brisbane','616-399-1411',TO_DATE('09-FEB-1992','DD-MON-YYYY'));

select * from member;

---------------------------------------------------------------------
INSERT INTO TITLE 
(title_id, title, description, rating, category, release_date)
VALUES	(92, 'Willie and Christmas Too',  
  'All of Willie''s friends made a Christmas list for Santa, but Willie has yet 
   to create his own wish list.','G','CHILD',to_date('05-OCT-1995','DD-MON-YYYY'));

INSERT INTO TITLE 
(title_id, title, description, rating, category, release_date)
VALUES	(93, 'Alien Again','Another installment of science fiction 
  history. Can the heroine save the planet from the alien life 
  form?','R','SCIFI',to_date('19-MAY-1995','DD-MON-YYYY'));

INSERT INTO TITLE 
(title_id, title, description, rating, category, release_date)
VALUES (94, 'The Glob',
  'A meteor crashes near a small American town and unleashes carnivorous goo 
   in this classic.','NR','SCIFI',to_date('12-AUG-1995','DD-MON-YYYY'));

INSERT INTO TITLE 
(title_id, title, description, rating, category, release_date)
VALUES (95, 'My Day Off','With a little luck and a lot 
   of ingenuity, a teenager skips school for a day in NewYork.',
  'PG','COMEDY',to_date('12-JUL-1995','DD-MON-YYYY'));

INSERT INTO TITLE 
(title_id, title, description, rating, category, release_date)
VALUES	(96, 'Miracles on Ice',
   'A six-year-old has doubts about Santa Claus. But she discovers 
    that miracles really do exist.','PG','DRAMA',
    to_date('12-SEP-1995','DD-MON-YYYY'));

INSERT INTO TITLE 
(title_id, title, description, rating, category, release_date)
VALUES	(97, 'Soda Gang','After discovering a cached of 
   drugs, a young couple find themselves pitted against a vicious 
   gang.','NR','ACTION',to_date('01-JUN-1995','DD-MON-YYYY'));

INSERT INTO TITLE
(title_id, title, description, rating, category, release_date)
VALUES	(98, 'Interstellar Wars', 'Futuristic
	interstellar action movie.  Can the rebels save the humans from
	the evil Empire?', 'PG', 'SCIFI',to_date('07-JUL-1977','DD-MON-YYYY'));

select * from title;
COMMIT;
---------------------------------------------------------------------
INSERT INTO title_copy VALUES (1,92,'RENTED');
INSERT INTO title_copy VALUES (2,92,'AVAILABLE');
INSERT INTO title_copy VALUES (1,93,'AVAILABLE');
INSERT INTO title_copy VALUES (2,93,'AVAILABLE'); 
INSERT INTO title_copy VALUES (1,94,'AVAILABLE'); 
INSERT INTO title_copy VALUES (1,95,'AVAILABLE'); 
INSERT INTO title_copy VALUES (2,95,'RENTED'); 
INSERT INTO title_copy VALUES (3,95,'RENTED');
INSERT INTO title_copy VALUES (1,96,'AVAILABLE');
INSERT INTO title_copy VALUES (1,97,'AVAILABLE');
INSERT INTO title_copy VALUES (1,98,'RENTED');
INSERT INTO title_copy VALUES (2,98,'RENTED');
---------------------------------------------------------------------
COMMIT;

INSERT INTO reservation VALUES (sysdate-1,101,93);
INSERT INTO reservation VALUES (sysdate-2,106,98);

COMMIT;
---------------------------------------------------------------------
INSERT INTO rental VALUES (sysdate-1,2,101,93,null,sysdate+1);
INSERT INTO rental VALUES (sysdate-2,3,102,95,null,sysdate);
INSERT INTO rental VALUES (sysdate-3,1,101,98,null,sysdate-1);
INSERT INTO rental VALUES (sysdate-4,1,106,97,sysdate-2,sysdate-2);
INSERT INTO rental VALUES (sysdate-3,1,101,92,sysdate-2,sysdate-1);

INSERT INTO rental VALUES (sysdate-2,2,102,93,sysdate-1,sysdate-1);
INSERT INTO rental VALUES (sysdate-4,2,106,93,sysdate-2,sysdate-2);
INSERT INTO rental VALUES (sysdate-3,3,101,95,sysdate-2,sysdate);
INSERT INTO rental VALUES (sysdate-5,1,104,98,sysdate-3,sysdate-3);

INSERT INTO rental VALUES (sysdate-6,2,102,92,sysdate-4,sysdate-4);

INSERT INTO rental VALUES (sysdate-2,1,101,93,null,sysdate-1);
INSERT INTO rental VALUES (sysdate-4,1,104,93,sysdate-2,sysdate-2);
INSERT INTO rental VALUES (sysdate-3,2,103,95,null,sysdate);
INSERT INTO rental VALUES (sysdate-5,2,102,98,null,sysdate-1);

---------------------------------------------------------------------
COMMIT;

PROMPT ** Tables built and data loaded **

SET ECHO ON





Recap 2

4. Câte filme (titluri, respectiv exemplare) au fost împrumutate din cea mai cerut? categorie?

--Cate titluri au fost imprumutate pt fiecare categorie?


select count(*), category
from rental
join title using (title_id)
group by category;


select max(calc)
 from (select count(*) calc, category
       from rental
       join title using (title_id)
       group by category
 );


select max(count(*))
from rental
join title using (title_id)
group by category;

Select category,count(*), count(distinct t.title_id)
from title t, rental r
where t.title_id = r.Title_id
group by category
having count(*) = (select max(count(*))
                    from rental
                    join title using (title_id)
                    group by category
      );
select * from rental;
Select t.*, r.*
from title t, rental r
where t.title_id = r.Title_id
and upper(category) = 'SCIFI';

5. Câte exemplare din fiecare film sunt disponibile în prezent (considera?i 
c? statusul unui exemplar nu este setat, deci nu poate fi utilizat)?
select * from rental;

select title, count(*) exemplare
 from title
 join rental using (title_id)
 where act_ret_date is not null
 group by title;

select title, copy_id
from title_copy t, title l
where t.title_id= l.title_id
order by 1, 2;

select title, copy_id
from title_copy t, title l
where t.title_id= l.title_id
and (t.title_id, copy_id) not in ( Select title_id, copy_id
                                    from rental 
                                    where act_ret_date is null
                              );

select title, copy_id
from title_copy t, title l
where t.title_id= l.title_id
and (t.title_id, copy_id) not in ( Select title_id, copy_id
                                    from rental 
                                    where act_ret_date is null
                              );

select title, copy_id
from title_copy t, title l
where t.title_id= l.title_id
and (t.title_id, copy_id) not in ( Select title_id, copy_id
                                    from rental 
                                    where act_ret_date is null
                              );--6



select t.title_id, copy_id
from title_copy t, title l
where t.title_id= l.title_id
minus
Select title_id, copy_id
from rental 
where act_ret_date is null;
                            
select title, count(copy_id)
from title_copy t, title l
where t.title_id= l.title_id
and (t.title_id, copy_id) not in ( Select title_id, copy_id
                                    from rental 
                                    where act_ret_date is null
                              )
group by title;

--The Glob	1
--Soda Gang	1
--Willie and Christmas Too	2
--Miracles on Ice	1
--My Day Off	1

-- numele clientului/membru care a facut cele mai multe rezervari
 -- Cate rerevari a facut fiecare membru
 select member_id, count(title_id)
 from reservation
 group by member_id;

select * from reservation;
INSERT INTO reservation VALUES (sysdate-10,106,98);
commit;


 select m.member_id, count(title_id)
 from reservation r, member m
 where m.member_id = r.member_id(+)
 group by m.member_id;

select * from member;
select m.*, r.*
 from reservation r, member m
 where m.member_id = r.member_id(+)
 order by m.member_id;

 select m.member_id, count(title_id), m.last_name
 from reservation r, member m
 where m.member_id = r.member_id(+)
 group by m.member_id, m.last_name
 having count(title_id) =( select Max(count(title_id))
                           from reservation r, member m
                           where m.member_id = r.member_id(+)
                           group by m.member_id);
                           
 select m.member_id, count(title_id), max(m.last_name)
 from reservation r, member m
 where m.member_id = r.member_id(+)
 group by m.member_id
 having count(title_id) =( select Max(count(title_id))
                           from reservation r, member m
                           where m.member_id = r.member_id(+)
                           group by m.member_id);
                           
 9. De câte ori a împrumutat un membru (nume ?i prenume) fiecare film (titlu)?
 (includeti si persoanele care nu au imprumutat niciun film)
 
 /
 
 select m.last_name, m.first_name, r.title_id, count(r.title_id)
 from rental r right join member m on (r.member_id = m.member_id)
 group by m.last_name, m.first_name, r.title_id;
 
 
 SELECT m.first_name,m.last_name,t.title_id,count(t.title_id)

 FROM member m full join rental r on(m.member_id=r.member_id)

 full join title t on (r.title_id=t.title_id)

 GROUP BY m.first_name,m.last_name,t.title_id
 order by 1,3; --nu
 
 Select m.last_name, m.title, count(r.title_id)
  from (select member_id, last_name,title_id, title
      from member, title) m, 
      rental r
where m.member_id = r.member_id(+)
and m.title_id = r.title_id (+)
group by m.last_name, m.title
order by 1, 2;
 