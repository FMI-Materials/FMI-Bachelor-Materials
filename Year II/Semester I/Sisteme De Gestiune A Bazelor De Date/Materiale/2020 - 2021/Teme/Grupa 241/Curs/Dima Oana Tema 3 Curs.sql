--Dima Oana 241 Tema 3 Curs Dead 3 dec 2020
--exemplul 5.12
select * from emp_odi_copy;
select * from jobs;
--vreau sa le adaug comision de 33% angajatilor al 
--caror nume la jobului incepe cu litera a
SELECT employee_id
FROM emp_odi_copy
WHERE job_id IN (SELECT job_id
                 FROM jobs
                 WHERE upper(job_title) like 'A%');
/

DECLARE
 CURSOR c IS
    SELECT employee_id
    FROM emp_odi_copy
    WHERE job_id IN (SELECT job_id
                     FROM jobs
                     WHERE upper(job_title) like 'A%')
    FOR UPDATE OF commission_pct NOWAIT;
    --pentru intrebarea 3 nu va da nicio eroare si se va comporta la fel
    --FOR UPDATE NOWAIT ;
BEGIN

 FOR i IN c LOOP
 UPDATE emp_odi_copy
 SET commission_pct =0.33
 WHERE CURRENT OF c;

 END LOOP;
 -- permanentizare si eliberare blocari
 COMMIT;
 --Da, se poate modifica si o alta coloana decat cea aleasa in for update
 --exemplu aici
 FOR i IN c LOOP
 UPDATE emp_odi_copy
 SET first_name ='Nou'
 WHERE CURRENT OF c;
 END LOOP;
END;
/
rollback;
--Intrebari:
-- daca  pun commit in interiorul iterarii ce se intampla si de ce? 
-- Va da eroare "fetch out of sequence Do not issue a COMMIT inside a fetch loop for a cursor
--that has been opened FOR UPDATE." Deoarece bloc?rile implicate de clauza FOR UPDATE 
--vor fi eliberate de comanda COMMIT, nu este recomandat? utilizarea comenzii COMMIT în
--interiorul ciclului în care se fac înc?rc?ri de date. Orice FETCH executat
--dup? COMMIT va e?ua. N-ar fi dat eroare daca nu utilizam SELECT..FOR UPDATE

-- Pot modifica si o alta coloana decat cea aleasa in for update?
--Da , deoarece  În momentul deschiderii unui cursor FOR UPDATE, liniile din mul?imea
--activ?, determinat? de clauza SELECT, sunt blocate pentru opera?ii de
--scriere (reactualizare sau ?tergere)

--Ce se intampla daca la declararea cursorului nu mai speific nicio coloana la for update? 
--O sa se comporte la fel, nu va da nicio eroare 

--Exemplul 5.11 
--sesiune 1
SELECT * FROM emp_odi_copy
WHERE department_id=60 FOR UPDATE;
commit;--deblocare linii
--ruleaza si afiseaza angajatii din dep 60
--ii blocheaza pentru alti utilizatori (pt delete/update)
--rol: asa ne asiguram ca alti utilizatori nu modifica inaintea noastra datele

--sesiune 2
SELECT * FROM emp_odi_copy
WHERE department_id=60
FOR UPDATE NOWAIT; --nu a?teapt? deblocarea liniei si întoarce o eroare daca liniile sunt
                    --deja blocate de alta sesiune;

SELECT * FROM emp_odi_copy
WHERE department_id=60
FOR UPDATE WAIT 10;
--wait n arunda eroare la fel ca nowait doar ca acesta asteapta n secunde deblocarea liniilor

SELECT * FROM emp_odi_copy
WHERE department_id=60
FOR UPDATE SKIP LOCKED;
--nu afiseaza nimic deoarece skip locked sare peste liniile blocate

