--Dima Oana Teodora Tema 3 Lab 27 nov 2020
--ex1
--ciclu cursoare cu subcereri 
BEGIN
 FOR v_jobs IN (SELECT j.job_id, job_title, count (employee_id) nr
                FROM employees e right join jobs j on (e.job_id=j.job_id)
                group by j.job_id, job_title) LOOP
        DBMS_OUTPUT.PUT_LINE('-------------------------------------');
        DBMS_OUTPUT.PUT_LINE ('Jobul: '||v_jobs.job_title);
        
        --tratare caz
        if v_jobs.nr=0 then
        DBMS_OUTPUT.PUT_LINE ('Job fara angajati!');
        else
            FOR v_emp IN (SELECT last_name, salary
                          FROM employees
                          WHERE job_id = v_jobs.job_id) LOOP
                DBMS_OUTPUT.PUT_LINE (v_emp.last_name ||' are salariul :' || v_emp.salary);
            END LOOP;
        end if;
        
 END LOOP;
END;
/
--expresii cursor
DECLARE
 TYPE refcursor IS REF CURSOR;
 CURSOR c_jobs IS
    SELECT j.job_id, job_title, count (employee_id) ,CURSOR (SELECT last_name, salary
                                                                FROM employees ee
                                                                WHERE ee.job_id=j.job_id)
    FROM employees e right join jobs j on (e.job_id=j.job_id)
    group by j.job_id, job_title;
    
 job_titlu jobs.job_title%TYPE;
 nume employees.last_name%type;
 salariu employees.salary%type;
 id_job jobs.job_id%type;
 numar  number;
 
 v_cursor refcursor;
 
 
BEGIN
 OPEN c_jobs;
 
 LOOP
    FETCH c_jobs INTO id_job, job_titlu, numar,  v_cursor;
 EXIT WHEN c_jobs%NOTFOUND;
    DBMS_OUTPUT.PUT_LINE('-------------------------------------');
    DBMS_OUTPUT.PUT_LINE ('Jobul: '||job_titlu);
    
    LOOP
        FETCH v_cursor INTO nume, salariu;
    EXIT WHEN v_cursor%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE (nume||' are salariul :' || salariu);
    END LOOP;
    if numar=0 then DBMS_OUTPUT.PUT_LINE ('Job fara angajati!');
    end if;
 END LOOP;
 
 CLOSE c_jobs;
END;
/
--ciclu cursoare

DECLARE
 
 CURSOR c_job IS
    SELECT j.job_id id_job, job_title titlu , count (employee_id) numar
    FROM employees e right join jobs j on (e.job_id=j.job_id)
    group by j.job_id, job_title;
 cursor c_emp is
    SELECT last_name nume, salary salariu, job_id id_job
    FROM employees ;
    
  
BEGIN
 for j in c_job loop
    
    DBMS_OUTPUT.PUT_LINE('-------------------------------------');
    DBMS_OUTPUT.PUT_LINE ('Jobul: '||j.titlu);
  
    if j.numar=0 then DBMS_OUTPUT.PUT_LINE ('Job fara angajati!');
    else
        
        for e in c_emp loop
            if e.id_job=j.id_job then
            DBMS_OUTPUT.PUT_LINE (e.nume||' are salariul :' || e.salariu);
            end if;
        end loop;
       
    end if;
   
 END LOOP;
 
END;
/
--cursoare clasice
DECLARE
 titlu jobs.job_title%TYPE;
 nume employees.last_name%type;
 salariu employees.salary%type;
 id_job jobs.job_id%type;
 id_emp employees.job_id%type;
 numar  number;
 
 CURSOR c_job IS
    SELECT j.job_id , job_title  , count (employee_id) 
    FROM employees e right join jobs j on (e.job_id=j.job_id)
    group by j.job_id, job_title;
 cursor c_emp is
    SELECT last_name , salary , job_id 
    FROM employees ;
  
BEGIN
 open c_job;
 

 loop 
    fetch c_job into id_job, titlu, numar;
    exit when c_job%notfound;
    
    DBMS_OUTPUT.PUT_LINE('-------------------------------------');
    DBMS_OUTPUT.PUT_LINE ('Jobul: '||titlu);
  
    if numar=0 then DBMS_OUTPUT.PUT_LINE ('Job fara angajati!');
    else
        open c_emp;
        loop
            fetch c_emp into nume, salariu, id_emp;
            exit when c_emp%notfound;
            if id_job=id_emp then 
            DBMS_OUTPUT.PUT_LINE (nume||' are salariul :' || salariu);
            end if;
        end loop;
        close c_emp;
    end if;
   
 END LOOP;
 
 close c_job;

END;
/
        
          
