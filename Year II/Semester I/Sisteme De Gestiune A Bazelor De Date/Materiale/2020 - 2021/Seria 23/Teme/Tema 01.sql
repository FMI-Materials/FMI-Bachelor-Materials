
-- Ex: 22
--- Exemplu de eroare: Scriptul da eroare atunci cand tabelele ce trebuie sterse nu exista.
--- Rezolvare: Verificam daca exista sau nu tabelele la stergere, adaugand conditie inainte de drop table. 
--- Sintaxa MySql Similara: DROP TABLE IF EXISTS table_name;
-- Ex: 23
SET FEEDBACK OFF;
SPOOL insert_tabela.sql;
select 'insert into departments (department_id, department_name, location_id)
values(' || department_id || ', ' || department_name || ', ' || location_id || ');'
from departments;
SPOOL OFF;
SET FEEDBACK ON;

