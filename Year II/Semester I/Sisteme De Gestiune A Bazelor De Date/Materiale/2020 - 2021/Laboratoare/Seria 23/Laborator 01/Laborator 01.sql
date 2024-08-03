--
select count(*) from employees;
select count(commission_pct) from employees;
--9
create table emp_bhd as select * from employees;
--10
select * from employees;
--11
comment on table emp_bhd is 'Informatii despre angajati';
--12
select * from user_tab_comments;
select * from user_tab_comments where table_name = upper('emp_bhd');
--13
select sysdate from dual;
alter session set nls_date_format = 'DD-MM-YYYY HH24:MI:SS';
--14
SELECT EXTRACT(YEAR FROM SYSDATE)
FROM dual;
--15
select extract(DAY FROM SYSDATE), extract(MONTH FROM SYSDATE) FROM dual;
--16
select table_name from user_tables where table_name like 'EMP_%';
--17
SET FEEDBACK OFF;
SET PAGESIZE 1;
SPOOL sterg_tabele.sql;
select 'drop table ' || table_name || ';'
from user_tables where table_name like 'EMP_%';
SPOOL OFF;
SET FEEDBACK ON;
--22
--- Exemplu de eroare: Scriptul da eroare atunci cand tabelele ce trebuie sterse nu exista.
--- Rezolvare: Verificam daca exista sau nu tabelele la stergere, adaugand conditie inainte de drop table. 
--- Sintaxa MySql Similara: DROP TABLE IF EXISTS table_name;
--23
SET FEEDBACK OFF;
SPOOL insert_tabela.sql;
select 'insert into departments (department_id, department_name, location_id)
values(' || department_id || ', ' || department_name || ', ' || location_id || ');'
from departments;
SPOOL OFF;
SET FEEDBACK ON;
