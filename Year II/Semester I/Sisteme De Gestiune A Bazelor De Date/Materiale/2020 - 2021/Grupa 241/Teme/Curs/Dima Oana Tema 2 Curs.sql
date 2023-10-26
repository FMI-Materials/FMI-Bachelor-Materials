--Tema2 CURS Dima Oana-Teodora 241 10 Nov 2020
create table emp_odi_copy as select * from employees;
select * from emp_odi_copy;

/
declare
    type tablou_indexat is table of emp_odi_copy%rowtype INDEX BY binary_integer;
    t tablou_indexat;
    marime number(5);
    
begin
    select count(*)
    into marime
    from emp_odi_copy
    where commission_pct is not null;
    
   DELETE FROM emp_odi_copy
    WHERE commission_pct is not null
    RETURNING employee_id, first_name, last_name, email, phone_number,
     hire_date, job_id, salary, commission_pct, manager_id,
    department_id
    BULK COLLECT INTO t;

    
    for i in 1..marime loop
      DBMS_OUTPUT.PUT_LINE (t(i).employee_id || ' ' || t(i).last_name|| ' ' || t(i).first_name || ' ' || t(i).email|| ' ' || 
      t(i).phone_number|| ' ' || t(i).hire_date || ' '||  t(i).job_id || ' ' || t(i).salary || ' ' || t(i).commission_pct || 
      ' ' || t(i).manager_id|| ' ' || t(i).department_id); 
      end loop;
end;
/
rollback;
/       
