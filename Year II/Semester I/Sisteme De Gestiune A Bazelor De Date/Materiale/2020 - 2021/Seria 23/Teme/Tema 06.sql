SET SERVEROUTPUT ON;

-- 1
-- a
DECLARE 
    CURSOR c (job_curent jobs.job_id%TYPE) IS 
        SELECT e.last_name, e.first_name, e.salary
        FROM employees e, jobs j
        WHERE j.job_id = e.job_id and j.job_id = job_curent; 
    numar_joburi NUMBER;
    titlu_job jobs.job_title%TYPE;
    nume_angajat employees.first_name%TYPE;
    prenume_angajat employees.last_name%TYPE;
    salariu employees.salary%TYPE;
    TYPE tip_joburi IS TABLE OF jobs.job_id%TYPE;
    joburi tip_joburi := tip_joburi();
    counter NUMBER(5);
BEGIN
    select count(*) into numar_joburi from jobs;
    joburi.EXTEND(numar_joburi);
    select j.job_id bulk collect into joburi from jobs j;
    
    FOR i IN joburi.FIRST..joburi.LAST LOOP   
        SELECT job_title
        INTO titlu_job
        FROM jobs j
        WHERE j.job_id = joburi(i);
        DBMS_OUTPUT.put_line(titlu_job);
        counter := 0;
        
        OPEN c(joburi(i));
        LOOP
            FETCH c INTO nume_angajat, prenume_angajat, salariu;
            EXIT WHEN c%NOTFOUND;
            DBMS_OUTPUT.put_line(nume_angajat || ' ' || prenume_angajat || ' ' || salariu);
            counter := counter + 1;
        END LOOP;
        CLOSE c;
        IF counter = 0 THEN 
            DBMS_OUTPUT.put_line('Nu exista niciun angajat.');
        END IF;
        DBMS_OUTPUT.new_line();
    END LOOP;
END;
/
    
-- b
DECLARE 
    TYPE tip_joburi IS TABLE OF jobs.job_id%TYPE;
    CURSOR c (job_curent jobs.job_id%TYPE)IS 
        SELECT e.last_name l_name, e.first_name f_name, e.salary salary
        FROM employees e, jobs j
        WHERE j.job_id = e.job_id and
                j.job_id = job_curent;
                    numar_joburi NUMBER;
    titlu_job jobs.job_title%TYPE;
    nume_angajat employees.first_name%TYPE;
    prenume_angajat employees.last_name%TYPE;
    salariu employees.salary%TYPE;
    joburi tip_joburi := tip_joburi();
    counter NUMBER(5);
BEGIN
    select count(*) into numar_joburi from jobs;
    joburi.EXTEND(numar_joburi);
    select j.job_id bulk collect into joburi from jobs j;
    
    FOR i IN joburi.FIRST..joburi.LAST LOOP   
    
        SELECT job_title
        INTO titlu_job
        FROM jobs j
        WHERE j.job_id = joburi(i);
        DBMS_OUTPUT.put_line(titlu_job);
        counter := 0;
        
        FOR j IN c(joburi(i)) LOOP
            EXIT WHEN c%NOTFOUND;
            DBMS_OUTPUT.put_line(j.f_name || ' ' || j.l_name || ' ' || j.salary);
            counter := counter + 1;
        END LOOP;
        IF counter = 0 THEN 
            DBMS_OUTPUT.put_line('Nu exista niciun angajat.');
        END IF;
        DBMS_OUTPUT.new_line();
    END LOOP;
END;
/
    
-- c 
DECLARE 
    TYPE tip_joburi IS TABLE OF jobs.job_id%TYPE;
    CURSOR c (job_curent jobs.job_id%TYPE)IS 
        SELECT e.last_name l_name, e.first_name f_name, e.salary salary
        FROM employees e, jobs j
        WHERE j.job_id = e.job_id and
                j.job_id = job_curent;
    numar_joburi NUMBER;
    titlu_job jobs.job_title%TYPE;
    nume_angajat employees.first_name%TYPE;
    prenume_angajat employees.last_name%TYPE;
    salariu employees.salary%TYPE;
    joburi tip_joburi := tip_joburi();
    counter NUMBER(5);
BEGIN
    select count(*) into numar_joburi from jobs;
    joburi.EXTEND(numar_joburi);
    select j.job_id bulk collect into joburi from jobs j;
    
    FOR i IN joburi.FIRST..joburi.LAST LOOP   
    
        SELECT job_title
        INTO titlu_job
        FROM jobs j
        WHERE j.job_id = joburi(i);
        DBMS_OUTPUT.put_line(titlu_job);
        counter := 0;
        
        FOR j IN (SELECT e.last_name l_name, e.first_name f_name, e.salary salary
                    FROM employees e, jobs j
                    WHERE j.job_id = e.job_id and
                    j.job_id = joburi(i)) 
        LOOP
            DBMS_OUTPUT.put_line(j.f_name || ' ' || j.l_name || ' ' || j.salary);
            counter := counter + 1;
        END LOOP;
        IF counter = 0 THEN 
            DBMS_OUTPUT.put_line('Nu exista niciun angajat.');
        END IF;
        DBMS_OUTPUT.new_line();
    END LOOP;
END;
/


-- d
DECLARE 
    TYPE refcursor IS REF CURSOR;
    CURSOR c IS 
        SELECT j2.job_title, CURSOR
            (SELECT e.last_name, e.first_name, e.salary
            FROM employees e, jobs j
            WHERE j.job_id = e.job_id and
                    j.job_id = j2.job_id)
        FROM jobs j2;
    titlu_job jobs.job_title%TYPE;
    nume_angajat employees.first_name%TYPE;
    prenume_angajat employees.last_name%TYPE;
    salariu employees.salary%TYPE;
    titlu_job jobs.job_title%TYPE;
    referinta_cursor refcursor;
    counter NUMBER(5);
BEGIN
    OPEN c;
    LOOP
        FETCH c INTO titlu_job, referinta_cursor;
        EXIT WHEN c%NOTFOUND;
        DBMS_OUTPUT.put_line(titlu_job);
        LOOP 
            FETCH referinta_cursor INTO nume_angajat, prenume_angajat, salariu;
            EXIT WHEN referinta_cursor%NOTFOUND;
            DBMS_OUTPUT.put_line(nume_angajat || ' ' || prenume_angajat || ' ' || salariu);
        END LOOP;
        
        DBMS_OUTPUT.new_line();

    END LOOP;
    
END;
/


--2
DECLARE 
    TYPE tip_joburi IS TABLE OF jobs.job_id%TYPE;
    CURSOR c (job_curent jobs.job_id%TYPE)IS 
        SELECT e.last_name, e.first_name, e.salary
        FROM employees e, jobs j
        WHERE j.job_id = e.job_id and
                j.job_id = job_curent;
                    numar_joburi NUMBER;
    titlu_job jobs.job_title%TYPE;
    nume_angajat employees.first_name%TYPE;
    prenume_angajat employees.last_name%TYPE;
    salariu employees.salary%TYPE;
    joburi tip_joburi := tip_joburi();
    numar_salariati NUMBER(5);
    counter NUMBER(5);
    salariu_total_job NUMBER(8,2);
    salariu_mediu_job NUMBER(8,2);
    salariu_total NUMBER(10,2) := 0;
    salariu_mediu NUMBER(10,2) := 0;
    counter_total NUMBER(5) := 0;
BEGIN
    select count(*) into numar_joburi from jobs;
    joburi.EXTEND(numar_joburi);
    select j.job_id bulk collect into joburi from jobs j;
    
    FOR i IN joburi.FIRST..joburi.LAST LOOP   
    
        SELECT job_title
        INTO titlu_job
        FROM jobs j
        WHERE j.job_id = joburi(i);     
        counter := 0;
        salariu_total_job := 0;
        
        SELECT count(*)
        INTO numar_salariati
        FROM employees e, jobs j
        WHERE e.job_id = j.job_id and
            j.job_id = joburi(i);
        
        IF numar_salariati = 0 THEN
            DBMS_OUTPUT.put_line('Nu lucreaza niciun angajat pe postul de ' || titlu_job);
        ELSIF numar_salariati = 1 THEN
            DBMS_OUTPUT.put_line('Un angajat lucreaza ca ' || titlu_job);
        ELSIF numar_salariati < 20 THEN
            DBMS_OUTPUT.put_line(numar_salariati || ' angajati lucreaza ca ' || titlu_job);
        ELSE
            DBMS_OUTPUT.put_line(numar_salariati || ' de angajati lucreaza ca ' || titlu_job);
        END IF;
        
        OPEN c(joburi(i));
        LOOP
            FETCH c INTO nume_angajat, prenume_angajat, salariu;
            EXIT WHEN c%NOTFOUND;
            DBMS_OUTPUT.put_line(counter + 1 || ' ' || nume_angajat || ' ' || prenume_angajat || ' ' || salariu);
            counter := counter + 1;
            salariu_total_job := salariu_total_job + salariu;
            counter_total := counter_total + 1;
        END LOOP;
        CLOSE c;
        
        salariu_total := salariu_total + salariu_total_job;
        IF counter = 0 THEN 
            DBMS_OUTPUT.put_line('Nu exista niciun angajat.');
        ELSE
            salariu_mediu_job := salariu_total_job / counter;
            DBMS_OUTPUT.put_line('Salariul total al angajatilor este ' || salariu_total_job || ' iar cel mediu este ' || salariu_mediu_job);
        END IF;
        DBMS_OUTPUT.new_line();
    END LOOP;
    salariu_mediu := salariu_total / counter_total;
    DBMS_OUTPUT.put_line('Salariul total al tuturor angajatilor este ' || salariu_total || ' iar cel mediu este ' || salariu_mediu);
END;
/
    
    
--3
DECLARE 
    TYPE tip_joburi IS TABLE OF jobs.job_id%TYPE;
    CURSOR c (job_curent jobs.job_id%TYPE)IS 
        SELECT e.last_name, e.first_name, e.salary, e.commission_pct
        FROM employees e, jobs j
        WHERE j.job_id = e.job_id and
                j.job_id = job_curent;
                    numar_joburi NUMBER;
    titlu_job jobs.job_title%TYPE;
    nume_angajat employees.first_name%TYPE;
    prenume_angajat employees.last_name%TYPE;
    salariu employees.salary%TYPE;
    joburi tip_joburi := tip_joburi();
    numar_salariati NUMBER(5);
    counter NUMBER(5);
    salariu_total_job NUMBER(8,2);
    salariu_mediu_job NUMBER(8,2);
    salariu_total NUMBER(10,2) := 0;
    salariu_mediu NUMBER(10,2) := 0;
    counter_total NUMBER(5) := 0;
    procentaj_comision NUMBER(5) := 0;
    total_cu_comision NUMBER(10,2) := 0;
BEGIN
    select count(*) into numar_joburi from jobs;
    joburi.EXTEND(numar_joburi);
    select j.job_id bulk collect into joburi from jobs j;
    
    FOR i IN joburi.FIRST..joburi.LAST LOOP   
    
        SELECT job_title
        INTO titlu_job
        FROM jobs j
        WHERE j.job_id = joburi(i);     
        counter := 0;
        salariu_total_job := 0;
        
        SELECT count(*)
        INTO numar_salariati
        FROM employees e, jobs j
        WHERE e.job_id = j.job_id and
            j.job_id = joburi(i);
            
        SELECT SUM(salary) + SUM(salary*commission_pct)
        INTO total_cu_comision
        FROM EMPLOYEES;
        
        IF numar_salariati = 0 THEN
            DBMS_OUTPUT.put_line('Nu lucreaza niciun angajat pe postul de ' || titlu_job);
        ELSIF numar_salariati = 1 THEN
            DBMS_OUTPUT.put_line('Un angajat lucreaza ca ' || titlu_job);
        ELSIF numar_salariati < 20 THEN
            DBMS_OUTPUT.put_line(numar_salariati || ' angajati lucreaza ca ' || titlu_job);
        ELSE
            DBMS_OUTPUT.put_line(numar_salariati || ' de angajati lucreaza ca ' || titlu_job);
        END IF;
        
        OPEN c(joburi(i));
        LOOP
            FETCH c INTO nume_angajat, prenume_angajat, salariu, procentaj_comision;
            EXIT WHEN c%NOTFOUND;
            DBMS_OUTPUT.put_line(counter + 1 || ' ' || nume_angajat || ' ' || prenume_angajat || ' ' || 
            salariu || ' ' || 
            TO_CHAR(((salariu + (salariu * nvl(procentaj_comision, 0))) * 100 / total_cu_comision), '0.00'));
            
            counter := counter + 1;
            salariu_total_job := salariu_total_job + salariu;
            counter_total := counter_total + 1;
        END LOOP;
        CLOSE c;
        
        salariu_total := salariu_total + salariu_total_job;
        IF counter = 0 THEN 
            DBMS_OUTPUT.put_line('Nu exista niciun angajat.');
        ELSE
            salariu_mediu_job := salariu_total_job / counter;
            DBMS_OUTPUT.put_line('Salariul total al angajatilor este ' 
            || salariu_total_job || ' iar cel mediu este ' || salariu_mediu_job);
        END IF;
        DBMS_OUTPUT.new_line();
    END LOOP;
    salariu_mediu := salariu_total / counter_total;
    DBMS_OUTPUT.put_line('Salariul total al tuturor angajatilor este ' || salariu_total || ' iar cel mediu este ' || salariu_mediu);
END;
/
    

--4
DECLARE 
    TYPE tip_joburi IS TABLE OF jobs.job_id%TYPE;
    CURSOR c (job_curent jobs.job_id%TYPE)IS 
        SELECT e.last_name, e.first_name, e.salary, e.commission_pct
        FROM employees e, jobs j
        WHERE j.job_id = e.job_id and
                j.job_id = job_curent
        ORDER BY e.salary DESC; 
    numar_joburi NUMBER;
    titlu_job jobs.job_title%TYPE;
    nume_angajat employees.first_name%TYPE;
    prenume_angajat employees.last_name%TYPE;
    salariu employees.salary%TYPE;
    joburi tip_joburi := tip_joburi();
    numar_salariati NUMBER(5);
    counter NUMBER(5);
    salariu_total_job NUMBER(8,2);
    salariu_mediu_job NUMBER(8,2);
    salariu_total NUMBER(10,2) := 0;
    salariu_mediu NUMBER(10,2) := 0;
    counter_total NUMBER(5) := 0;
    procentaj_comision NUMBER(5) := 0;
    total_cu_comision NUMBER(10,2) := 0;
BEGIN  
    
    select count(*) into numar_joburi from jobs;
    joburi.EXTEND(numar_joburi);
    select j.job_id bulk collect into joburi from jobs j;
    
    FOR i IN joburi.FIRST..joburi.LAST LOOP   
        counter := 0;
        SELECT job_title
        INTO titlu_job
        FROM jobs j
        WHERE j.job_id = joburi(i); 
        
        SELECT count(*)
        INTO numar_salariati
        FROM employees e, jobs j
        WHERE e.job_id = j.job_id and
            j.job_id = joburi(i);

        IF numar_salariati < 5 THEN
            DBMS_OUTPUT.put_line('Lucreaza mai putin de 5 angajati ca  ' || titlu_job);
        ELSE
            DBMS_OUTPUT.put_line(titlu_job);
        END IF;
        
        OPEN c(joburi(i));
        LOOP
            FETCH c INTO nume_angajat, prenume_angajat, salariu, procentaj_comision;
            EXIT WHEN c%NOTFOUND or c%ROWCOUNT > 5;
            DBMS_OUTPUT.put_line(counter + 1 || ' ' || nume_angajat || ' ' || prenume_angajat || ' ' || salariu);
            counter := counter + 1;
        END LOOP;
        CLOSE c;
         
        DBMS_OUTPUT.new_line();
    END LOOP;
END;
/


--5
DECLARE 
    TYPE tip_joburi IS TABLE OF jobs.job_id%TYPE;
    CURSOR c (job_curent jobs.job_id%TYPE)IS 
        SELECT e.last_name, e.first_name, e.salary, e.commission_pct
        FROM employees e, jobs j
        WHERE j.job_id = e.job_id and
                j.job_id = job_curent
        ORDER BY e.salary DESC; 
    numar_joburi NUMBER;
    titlu_job jobs.job_title%TYPE;
    nume_angajat employees.first_name%TYPE;
    prenume_angajat employees.last_name%TYPE;
    salariu employees.salary%TYPE;
    joburi tip_joburi := tip_joburi();
    numar_salariati NUMBER(5);
    counter NUMBER(5);
    salariu_total_job NUMBER(8,2);
    salariu_mediu_job NUMBER(8,2);
    salariu_total NUMBER(10,2) := 0;
    salariu_mediu NUMBER(10,2) := 0;
    counter_total NUMBER(5) := 0;
    procentaj_comision NUMBER(5) := 0;
    total_cu_comision NUMBER(10,2) := 0;
    salariu_angajat employees.salary%TYPE;
BEGIN  
    
    select count(*) into numar_joburi from jobs;
    joburi.EXTEND(numar_joburi);
    select j.job_id bulk collect into joburi from jobs j;
    
    FOR i IN joburi.FIRST..joburi.LAST LOOP   
        salariu_angajat := 0;
        counter := 0;
        SELECT job_title
        INTO titlu_job
        FROM jobs j
        WHERE j.job_id = joburi(i); 
        
        SELECT count(*)
        INTO numar_salariati
        FROM employees e, jobs j
        WHERE e.job_id = j.job_id and
            j.job_id = joburi(i);

        IF numar_salariati < 5 THEN
            DBMS_OUTPUT.put_line('Lucreaza mai putin de 5 angajati ca  ' || titlu_job);
        ELSE
            DBMS_OUTPUT.put_line(titlu_job);
        END IF;
        
        OPEN c(joburi(i));
        LOOP
            FETCH c INTO nume_angajat, prenume_angajat, salariu, procentaj_comision;
            EXIT WHEN c%NOTFOUND or c%ROWCOUNT > 5;
            IF salariu_angajat = 0 or salariu <> salariu_angajat THEN
                salariu_angajat := salariu;
                counter := counter + 1;
            END IF;
            DBMS_OUTPUT.put_line(counter || ' ' || nume_angajat || ' ' || prenume_angajat || ' ' || salariu);
        END LOOP;
        CLOSE c;
         
        DBMS_OUTPUT.new_line();
    END LOOP;
END;
/