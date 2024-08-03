--Dima Oana Teodora 242 Tema 4 Lab Deadline: 3 dec 2020
--AM ALES: ciclu cursoare

--ex2

DECLARE
 
 CURSOR c_job IS
    SELECT j.job_id id_job, job_title titlu , count (employee_id) numar
    FROM employees e right join jobs j on (e.job_id=j.job_id)
    group by j.job_id, job_title;
    
 cursor c_emp is
    SELECT last_name nume, salary salariu, job_id id_job, nvl(commission_pct,0) comision
    FROM employees ;
    
    ord number:=0;
    total_salariu employees.salary%type:=0;
   
    nr number:=0;
    total_s employees.salary%type:=0;
    
  
BEGIN
 for j in c_job loop
    
    DBMS_OUTPUT.PUT_LINE('-------------------------------------');
    DBMS_OUTPUT.PUT_LINE ('Jobul: '||j.titlu);
  
    if j.numar=0 then DBMS_OUTPUT.PUT_LINE ('Job fara angajati!');
    else
        DBMS_OUTPUT.PUT_LINE ('Numarul de angajati este: '|| j.numar);
        total_salariu:=0;
        ord:=0;
        for e in c_emp loop
            if e.id_job=j.id_job then
            ord:=ord+1;
            total_salariu :=total_salariu+ e.salariu+e.comision*e.salariu;
            DBMS_OUTPUT.PUT_LINE (ord||' ' || e.nume||' are salariul :' || e.salariu);
            end if;
        end loop;
        DBMS_OUTPUT.PUT_LINE ('valoarea lunar? a veniturilor angaja?ilor: '||total_salariu);
        DBMS_OUTPUT.PUT_LINE ('valoarea medie a veniturilor angaja?ilor : '||round(total_salariu / j.numar,2) );
        nr:= nr+j.numar;
        total_s:=total_s+total_salariu;
        
       
    end if;
   
 END LOOP;
 DBMS_OUTPUT.PUT_LINE ('---------------------');
 DBMS_OUTPUT.PUT_LINE ('Nr total angajati : '||nr);
 DBMS_OUTPUT.PUT_LINE ('valoarea totala lunara a veniturilor angajatilor: '||total_s);
 DBMS_OUTPUT.PUT_LINE ('valoarea medie a veniturilor angaja?ilor: '||round(total_s/nr,2));
 
END;
/
----------------------------------
--ex3
DECLARE
 
 CURSOR c_job IS
    SELECT j.job_id id_job, job_title titlu , count (employee_id) numar
    FROM employees e right join jobs j on (e.job_id=j.job_id)
    group by j.job_id, job_title;
 cursor c_emp is
    SELECT last_name nume, salary salariu, job_id id_job, nvl(commission_pct,0) comision
    FROM employees ;
    
    ord number;
    total_salariu employees.salary%type:=0;
    nr number:=0;
    total_s employees.salary%type:=0;
    procent number;
   
  
BEGIN
 select sum(salary+ nvl(commission_pct,0)) 
    into total_s
    from employees;
    
 for j in c_job loop
    
    DBMS_OUTPUT.PUT_LINE('-------------------------------------');
    DBMS_OUTPUT.PUT_LINE ('Jobul: '||j.titlu);
  
    if j.numar=0 then DBMS_OUTPUT.PUT_LINE ('Job fara angajati!');
    else
        DBMS_OUTPUT.PUT_LINE ('Numarul de angajati este: '|| j.numar);
        total_salariu:=0;
        ord:=0;
        for e in c_emp loop
            if e.id_job=j.id_job then
            ord:=ord+1;
            total_salariu :=total_salariu+ e.salariu+e.comision*e.salariu;
            DBMS_OUTPUT.PUT(ord||' ' || e.nume||' are salariul :' || e.salariu);
            procent:= (e.salariu+e.comision*e.salariu)*100/total_S;
            DBMS_OUTPUT.PUT_LINE (' '|| 'si castiga ' || round(procent,2) || '% din salariul total');
            end if;
        end loop;
        DBMS_OUTPUT.PUT_LINE ('valoarea lunar? a veniturilor angaja?ilor: '||total_salariu);
        DBMS_OUTPUT.PUT_LINE ('valoarea medie a veniturilor angaja?ilor: '||round(total_salariu / j.numar,2) );
        nr:= nr+j.numar;
        
        
       
    end if;
   
 END LOOP;
 DBMS_OUTPUT.PUT_LINE ('---------------------');
 DBMS_OUTPUT.PUT_LINE ('Nr total angajati : '||nr);
 DBMS_OUTPUT.PUT_LINE ('valoarea total? lunar? a veniturilor angaja?ilor: '||total_s);
 DBMS_OUTPUT.PUT_LINE ('valoarea medie a veniturilor angaja?ilor: '||round(total_s/nr,2));
 
END;
/
--ex4
DECLARE
 
 CURSOR c_job IS
    SELECT j.job_id id_job, job_title titlu , count (employee_id) numar
    FROM employees e right join jobs j on (e.job_id=j.job_id)
    group by j.job_id, job_title;
 cursor c_emp is
    SELECT last_name nume, salary salariu, job_id id_job, nvl(commission_pct,0) comision
    FROM employees
    order by salary desc;
    
   
    total_salariu employees.salary%type:=0;
    nr number:=0;
    total_s employees.salary%type:=0;
    procent number;
    i number:=0;
   
  
BEGIN
 select sum(salary+ nvl(commission_pct,0)) 
    into total_s
    from employees;
 for j in c_job loop
    
    DBMS_OUTPUT.PUT_LINE('-------------------------------------');
    DBMS_OUTPUT.PUT_LINE ('Jobul: '||j.titlu);
  
    if j.numar=0 then DBMS_OUTPUT.PUT_LINE ('Job fara angajati!');
    else
        DBMS_OUTPUT.PUT_LINE ('Numarul de angajati este: '|| j.numar);
        if j.numar<5 then
        DBMS_OUTPUT.PUT_LINE ('Numarul de angajati este mai mic ca 5');
        end if;
        
        total_salariu:=0;
        i:=0;
        
        for e in c_emp loop
            if e.id_job=j.id_job then
            i:=i+1;
            total_salariu :=total_salariu+ e.salariu+e.comision*e.salariu;
                if i<=5 then
                DBMS_OUTPUT.PUT(i||' ' || e.nume||' are salariul :' || e.salariu);
                procent:= (e.salariu+e.comision*e.salariu)*100/total_S;
                DBMS_OUTPUT.PUT_LINE (' '|| 'si castiga ' || round(procent,2) || '% din salariul total');
                end if;
            end if;
           
        end loop;
        DBMS_OUTPUT.PUT_LINE ('valoarea lunar? a veniturilor angaja?ilor: '||total_salariu);
        DBMS_OUTPUT.PUT_LINE ('valoarea medie a veniturilor angaja?ilor : '||round(total_salariu / j.numar,2) );
        nr:= nr+j.numar;
        
    end if;
   
 END LOOP;
 DBMS_OUTPUT.PUT_LINE ('---------------------');
 DBMS_OUTPUT.PUT_LINE ('Nr total angajati : '||nr);
 DBMS_OUTPUT.PUT_LINE ('valoarea total? lunar? a veniturilor angaja?ilor: '||total_s);
 DBMS_OUTPUT.PUT_LINE ('valoarea medie a veniturilor angaja?ilor: '||round(total_s/nr,2));
 
END;
/
--ex5
DECLARE
 
 CURSOR c_job IS
    SELECT j.job_id id_job, job_title titlu , count (employee_id) numar
    FROM employees e right join jobs j on (e.job_id=j.job_id)
    group by j.job_id, job_title;
 cursor c_emp is
   
    SELECT last_name nume, salary salariu, job_id id_job, nvl(commission_pct,0) comision
    FROM employees;
    
    n number;
    type t is table of employees.salary%type ;
    tabel t;
    ord number;
    total_salariu employees.salary%type:=0;
    nr number:=0;
    total_s employees.salary%type:=0;
    procent number;
   
  
BEGIN
 select sum(salary+ nvl(commission_pct,0)) 
    into total_s
    from employees;
    
 for j in c_job loop
    
    DBMS_OUTPUT.PUT_LINE('-------------------------------------');
    DBMS_OUTPUT.PUT_LINE ('Jobul: '||j.titlu);
  
    if j.numar=0 then DBMS_OUTPUT.PUT_LINE ('Job fara angajati!');
    else
        DBMS_OUTPUT.PUT_LINE ('Numarul de angajati este: '|| j.numar);
        if j.numar<5 then
            n:=j.numar;
         else
            n:=5;
        end if;
        total_salariu:=0;
        ord:=0;
        select salary bulk collect 
        into tabel 
        from (select distinct salary
                from employees emp 
                where emp.job_id=j.id_job
                order by salary desc
                ) ee
        where n > (select count(distinct salary)
                    from employees emp 
                    where emp.job_id=j.id_job and  salary > ee.salary)
        and rownum <= n;
        
        for e in c_emp loop
            if e.id_job=j.id_job then
            
                total_salariu :=total_salariu+ e.salariu+e.comision*e.salariu;
            
                for i in tabel.first..tabel.last loop
                    if tabel(i)=e.salariu then
                        ord:=ord+1;
                        DBMS_OUTPUT.PUT(ord||' ' || e.nume||' are salariul :' || e.salariu);
                        procent:= (e.salariu+e.comision*e.salariu)*100/total_S;
                        DBMS_OUTPUT.PUT_LINE (' '|| 'si castiga ' || round(procent,2) || '% din salariul total');
                    end if;
                end loop;  
            end if;
            
        end loop;
        
        tabel.delete; 
        DBMS_OUTPUT.PUT_LINE ('valoarea lunar? a veniturilor angaja?ilor: '||total_salariu);
        DBMS_OUTPUT.PUT_LINE ('valoarea medie a veniturilor angaja?ilor: '||round(total_salariu / j.numar,2) );
        nr:= nr+j.numar;
       
end if;
   
 END LOOP;
 DBMS_OUTPUT.PUT_LINE ('---------------------');
 DBMS_OUTPUT.PUT_LINE ('Nr total angajati : '||nr);
 DBMS_OUTPUT.PUT_LINE ('valoarea total? lunar? a veniturilor angaja?ilor: '||total_s);
 DBMS_OUTPUT.PUT_LINE ('valoarea medie a veniturilor angaja?ilor: '||round(total_s/nr,2));
 
END;
/
--asa iau primele 5 salarii

select salary
from (select distinct salary
      from employees
      order by salary desc
      ) e
where 5 > (select count(distinct salary)
           from employees
           where  salary > e.salary)
      and rownum <= 5;
