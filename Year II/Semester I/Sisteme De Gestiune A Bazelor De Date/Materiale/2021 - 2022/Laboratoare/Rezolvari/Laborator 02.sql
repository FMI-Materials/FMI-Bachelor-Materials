DECLARE
 x NUMBER(1) := 5;
 y x%TYPE := NULL;
BEGIN
 IF x <> y THEN
 DBMS_OUTPUT.PUT_LINE ('valoare <> null este = true');
 ELSE
 DBMS_OUTPUT.PUT_LINE ('valoare <> null este != true');
 END IF;
 
 x := NULL;
 IF x = y THEN
 DBMS_OUTPUT.PUT_LINE ('null = null este = true');
 ELSE
 DBMS_OUTPUT.PUT_LINE ('null = null este != true');
 END IF;
END;
/

DECLARE
 x NUMBER(1) := 5;
 y x%TYPE := NULL;
BEGIN
 IF x <> y THEN
 DBMS_OUTPUT.PUT_LINE ('valoare <> null este = true');
 ELSE
 DBMS_OUTPUT.PUT_LINE ('valoare <> null este != true');
 END IF;
 
 x := NULL;
 IF x IS NULL AND  y IS NULL THEN
 DBMS_OUTPUT.PUT_LINE ('null = null este = true');
 ELSE
 DBMS_OUTPUT.PUT_LINE ('null = null este != true');
 END IF;
END;
/


--2

--a
DECLARE
 TYPE emp_record IS RECORD 
 (cod employees.employee_id%TYPE, 
 salariu employees.salary%TYPE, 
 job employees.job_id%TYPE);
 
 v_ang emp_record;
BEGIN
 v_ang.cod:=700;
 v_ang.salariu:= 9000;
 v_ang.job:='SA_MAN';
 DBMS_OUTPUT.PUT_LINE ('Angajatul cu codul '|| v_ang.cod || 
 ' si jobul ' || v_ang.job || ' are salariul ' || v_ang.salariu);
END;

--b
DECLARE
 TYPE emp_record IS RECORD 
 (cod employees.employee_id%TYPE, 
 salariu employees.salary%TYPE, 
 job employees.job_id%TYPE);
 
 v_ang emp_record;
BEGIN
SELECT employee_id, salary, job_id
INTO v_ang
FROM employees
WHERE employee_id = 101;
DBMS_OUTPUT.PUT_LINE ('Angajatul cu codul '|| v_ang.cod || 
 ' si jobul ' || v_ang.job || ' are salariul ' || v_ang.salariu);
END;
/

--c
DECLARE
 TYPE emp_record IS RECORD 
 (cod employees.employee_id%TYPE, 
 salariu employees.salary%TYPE, 
 job employees.job_id%TYPE);
 
 v_ang emp_record;
 BEGIN
    DELETE FROM emp_prof 
    WHERE employee_id=100
    RETURNING employee_id, salary, job_id INTO v_ang;
    DBMS_OUTPUT.PUT_LINE ('Angajatul cu codul '|| v_ang.cod || 
     ' si jobul ' || v_ang.job || ' are salariul ' || v_ang.salariu);
END;
/

select * from emp_prof 
    WHERE employee_id=100;
ROLLBACK;


DECLARE
 TYPE emp_record IS RECORD 
 (cod employees.employee_id%TYPE, 
 salariu employees.salary%TYPE, 
 job employees.job_id%TYPE);
 
 v_ang emp_record;
 BEGIN
  if v_ang.cod is null THEN
        DBMS_OUTPUT.PUT_LINE ('Codul este null');
    end if;
    
    DELETE FROM emp_prof 
    WHERE employee_id=10
    RETURNING employee_id, salary, job_id INTO v_ang;
    
--    if SQL%rowcount = 0 then
--        raise no_data_found;
--    end if;
    
    if v_ang.cod is null THEN
        DBMS_OUTPUT.PUT_LINE ('Codul este null');
    end if;
    
    DBMS_OUTPUT.PUT_LINE ('Angajatul cu codul '|| nvl(v_ang.cod, 0) || 
     ' si jobul ' || v_ang.job || ' are salariul ' || v_ang.salariu);
END;
/

DECLARE
 TYPE emp_record IS RECORD 
 (v_rowid rowid,
 cod employees.employee_id%TYPE, 
 salariu employees.salary%TYPE, 
 job employees.job_id%TYPE);
 
 v_ang emp_record;
 BEGIN
 
 insert into emp_prof
 values(500, 'Steven', 'King2', 'KING@GMAIL', null, to_date('17-11-87', 'DD-MM-YY'), 'AD_PRES2', 24000, null, null, 90)
 RETURNING rowid, employee_id, salary, job_id INTO v_ang;
 
  DBMS_OUTPUT.PUT_LINE ('Angajatul cu codul '|| nvl(v_ang.cod, 0) || 
     ' si jobul ' || v_ang.job || ' are salariul ' || v_ang.salariu || ' avand ROWID-ul ' || v_ang.v_rowid);
     
insert into emp_prof
select * from employees
where rownum <5;

if SQL%rowcount > 1 then
        raise too_many_rows;
end if;

    exception
    
    when others then
    DBMS_OUTPUT.PUT_LINE ('Alta eroare ' || SQLERRM);
END;
 
 select * from emp_prof
 where employee_id = 500;
 ROLLBACK;
 
 --3
 DECLARE
v_ang1 employees%ROWTYPE;
v_ang2 employees%ROWTYPE;
BEGIN
-- sterg angajat 100 si mentin in variabila linia stearsa
 DELETE FROM emp_prof 
 WHERE employee_id = 100
 RETURNING employee_id, first_name, last_name, email, phone_number,
 hire_date, job_id, salary, commission_pct, manager_id,
 department_id
 INTO v_ang1;
-- inserez in tabel linia stearsa
 INSERT INTO emp_prof
 VALUES v_ang1;
 
-- sterg angajat 101 
 DELETE FROM emp_prof 
 WHERE employee_id = 101;
 
 -- obtin datele din tabelul employees
 SELECT *
 INTO v_ang2
 FROM employees
 WHERE employee_id = 101;
-- inserez o linie oarecare in emp_prof
 INSERT INTO emp_prof
 VALUES(1000,'FN','LN','E',null,sysdate, 'AD_VP',1000, null,100,90);
-- modific linia adaugata anterior cu valorile variabilei v_ang2
 UPDATE emp_prof
 SET ROW = v_ang2
 WHERE employee_id = 1000;
END;

select * from  emp_prof 
 WHERE employee_id = 1000;
 
--4

DECLARE
 TYPE tablou_indexat IS TABLE OF NUMBER INDEX BY PLS_INTEGER;
 t tablou_indexat;
BEGIN
-- punctul a
 FOR i IN 1..10 LOOP
    t(i) := i;
 END LOOP;
 
 DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT ||' elemente: ');
 FOR i IN t.FIRST..t.LAST LOOP
 DBMS_OUTPUT.PUT(t(i) || ' '); 
 END LOOP;
 DBMS_OUTPUT.NEW_LINE;
 
 -- punctul b
 FOR i IN 1..10 LOOP
     IF i mod 2 = 1 THEN 
        t(i):= null;
     END IF;
 END LOOP;
 
 DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT ||' elemente: ');
FOR i IN t.FIRST..t.LAST LOOP
 DBMS_OUTPUT.PUT(nvl(t(i), 0) || ' '); 
 END LOOP;
 DBMS_OUTPUT.NEW_LINE;
 
 -- punctul c
 t.DELETE(t.first);
 t.DELETE(5,7);
 t.DELETE(t.last);
 DBMS_OUTPUT.PUT_LINE('Primul element are indicele ' || t.first ||
 ' si valoarea ' || nvl(t(t.first),0));
DBMS_OUTPUT.PUT_LINE('Ultimul element are indicele ' || t.last ||
 ' si valoarea ' || nvl(t(t.last),0));
 DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT ||' elemente: ');
 FOR i IN t.FIRST..t.LAST LOOP
 --DBMS_OUTPUT.PUT(nvl(t(i), 0)|| ' ');
    IF t.EXISTS(i) THEN 
        DBMS_OUTPUT.PUT(nvl(t(i), 0)|| ' '); 
    END IF;
 END LOOP;
 DBMS_OUTPUT.NEW_LINE;

-- punctul d
 t.delete;
 DBMS_OUTPUT.PUT_LINE('Tabloul are ' || t.COUNT ||' elemente.');
 END;
 
 --5
 DECLARE
 TYPE tablou_indexat IS TABLE OF emp_prof%ROWTYPE 
 INDEX BY BINARY_INTEGER;
 t tablou_indexat;
BEGIN
-- stergere din tabel si salvare in tablou 
 DELETE FROM emp_prof 
 WHERE ROWNUM <= 2
 RETURNING employee_id, first_name, last_name, email, phone_number,
 hire_date, job_id, salary, commission_pct, manager_id,
 department_id
 BULK COLLECT INTO t;
--afisare elemente tablou
 DBMS_OUTPUT.PUT_LINE (t(1).employee_id ||' ' || t(1).last_name);
 DBMS_OUTPUT.PUT_LINE (t(2).employee_id ||' ' || t(2).last_name);
--inserare cele 2 linii in tabel
 INSERT INTO emp_prof VALUES t(1);
 INSERT INTO emp_prof VALUES t(2);
 END;
 
 
 --6
 DECLARE
 TYPE tablou_imbricat IS TABLE OF NUMBER;
 t tablou_imbricat := tablou_imbricat();
BEGIN
-- punctul a
 FOR i IN 1..10 LOOP
     t.extend;
     --t(i):=i;
 END LOOP;
 DBMS_OUTPUT.PUT_LINE('Tabloul are ' || t.COUNT ||' elemente: ');
  FOR i IN 1..10 LOOP
     IF t.EXISTS(i) THEN 
        DBMS_OUTPUT.PUT(nvl(t(i), 0)|| ' '); 
     END IF;
 END LOOP;
 DBMS_OUTPUT.NEW_LINE;
 
  END;
 /
 
-- FOR i IN t.FIRST..t.LAST LOOP
--    DBMS_OUTPUT.PUT(t(i) || ' '); 
-- END LOOP;
-- DBMS_OUTPUT.NEW_LINE;
-- 
-- -- punctul b
-- FOR i IN 1..10 LOOP
--     IF i mod 2 = 1 THEN 
--        t(i) := null;
--     END IF;
-- END LOOP;
-- DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT ||' elemente: ');
-- FOR i IN t.FIRST..t.LAST LOOP
--    DBMS_OUTPUT.PUT(nvl(t(i), 0) || ' '); 
-- END LOOP;
-- DBMS_OUTPUT.NEW_LINE;
-- 
-- -- punctul c
-- t.DELETE(t.first);
-- t.DELETE(5,7);
-- t.DELETE(t.last);
-- DBMS_OUTPUT.PUT_LINE('Primul element are indicele ' || t.first ||
-- ' si valoarea ' || nvl(t(t.first),0));
-- DBMS_OUTPUT.PUT_LINE('Ultimul element are indicele ' || t.last ||
-- ' si valoarea ' || nvl(t(t.last),0));
-- DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT ||' elemente: ');
-- FOR i IN t.FIRST..t.LAST LOOP
--  --DBMS_OUTPUT.PUT_LINE('i=' || i);
--     IF t.EXISTS(i) THEN 
--        DBMS_OUTPUT.PUT(nvl(t(i), 0)|| ' '); 
--     END IF;
-- END LOOP;
-- DBMS_OUTPUT.NEW_LINE;
-- -- punctul d
-- t.delete;
-- DBMS_OUTPUT.PUT_LINE('Tabloul are ' || t.COUNT ||' elemente.');
-- IF t IS NULL THEN
--    DBMS_OUTPUT.PUT_LINE('Tabloul este null');
-- END IF;
 
 END;
 
 
 --7

DECLARE
    TYPE tablou_imbricat IS TABLE OF CHAR(1);
    t tablou_imbricat := tablou_imbricat('m', 'i', 'n', 'i', 'm');
    i INTEGER;
BEGIN
    i := t.FIRST;
    WHILE i <= t.LAST LOOP
     DBMS_OUTPUT.PUT(t(i));
     i := t.NEXT(i);
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
    
     i := t.LAST;
    WHILE i >= t.FIRST LOOP
     DBMS_OUTPUT.PUT(t(i));
     i := t.PRIOR(i);
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
     t.delete(2); 
     t.delete(4);
     
    i := t.FIRST;
    WHILE i <= t.LAST LOOP
     DBMS_OUTPUT.PUT(t(i));
     i := t.NEXT(i);
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
     i := t.LAST;
    WHILE i >= t.FIRST LOOP
     DBMS_OUTPUT.PUT(t(i));
     i := t.PRIOR(i);
    END LOOP;
    DBMS_OUTPUT.NEW_LINE;
END;
/

--8
DECLARE
 TYPE vector IS VARRAY(20) OF NUMBER;
 t vector := vector();
BEGIN
-- punctul a
 FOR i IN 1..10 LOOP
    t.extend; 
    t(i):=i;
 END LOOP;
 
 DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT ||' elemente: ');
 FOR i IN t.FIRST..t.LAST LOOP
    DBMS_OUTPUT.PUT(t(i) || ' '); 
 END LOOP;
 DBMS_OUTPUT.NEW_LINE;
-- punctul b
 FOR i IN 1..10 LOOP
     IF i mod 2 = 1 THEN 
        t(i) := null;
     END IF;
 END LOOP;
 DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT ||' elemente: ');
 FOR i IN t.FIRST..t.LAST LOOP
 DBMS_OUTPUT.PUT(nvl(t(i), 0) || ' '); 
 END LOOP;
 DBMS_OUTPUT.NEW_LINE;
-- punctul c
-- metodele DELETE(n), DELETE(m,n) nu sunt valabile pentru vectori!!! 
-- din vectori nu se pot sterge elemente individuale!!!

    t.TRIM(2);
     DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT ||' elemente: ');
 FOR i IN t.FIRST..t.LAST LOOP
 DBMS_OUTPUT.PUT(nvl(t(i), 0) || ' '); 
 END LOOP;
 DBMS_OUTPUT.NEW_LINE;
 
-- punctul d
 t.delete;
 DBMS_OUTPUT.PUT_LINE('Tabloul are ' || t.COUNT ||' elemente.');
 END;
 
 --9
 
CREATE OR REPLACE TYPE subordonati_prof AS VARRAY(10) OF NUMBER(4);
/

CREATE TABLE manageri_prof (
cod_mgr NUMBER(10),
 nume VARCHAR2(20),
 lista subordonati_prof);
 
DECLARE 
 v_sub subordonati_prof := subordonati_prof(100,200,300);
 v_lista manageri_prof.lista%TYPE;
BEGIN
-- INSERT INTO manageri_prof
-- VALUES (1, 'Mgr 1', v_sub);
-- 
-- INSERT INTO manageri_prof
-- VALUES (2, 'Mgr 2', null);
-- 
-- INSERT INTO manageri_prof
-- VALUES (3, 'Mgr 3', subordonati_prof(400,500));
 
INSERT INTO manageri_prof
 VALUES (4, 'Mgr 4', subordonati_prof());

 SELECT lista
 INTO v_lista
 FROM manageri_prof
 WHERE cod_mgr = 4;
 
 FOR j IN v_lista.FIRST..v_lista.LAST loop
    DBMS_OUTPUT.PUT_LINE (v_lista(j));
 END LOOP;
END;
/

SELECT * FROM manageri_prof;
DROP TABLE manageri_prof;
DROP TYPE subordonati_prof;


--10
CREATE TABLE emp_test_prof AS 
 SELECT employee_id, last_name 
    FROM employees
 WHERE ROWNUM <= 2;
 
CREATE OR REPLACE TYPE tip_telefon_prof IS TABLE OF VARCHAR(12);
/

ALTER TABLE emp_test_prof
ADD (telefon tip_telefon_prof) 
NESTED TABLE telefon STORE AS tabel_telefon_prof;

select * from SYS.dba_nested_tables;

INSERT INTO emp_test_prof
VALUES (500, 'XYZ', tip_telefon_prof('074XXX', '0213XXX', '037XXX'));

select * from emp_test_prof;

UPDATE emp_test_prof
SET telefon = tip_telefon_prof('073XXX', '0214XXX')
WHERE employee_id=198;


SELECT a.employee_id, b.*
FROM emp_test_prof a, TABLE (a.telefon) b;

SELECT a.employee_id, cardinality(a.telefon), b.*
FROM emp_test_prof a, TABLE (a.telefon)(+) b;

DROP TABLE emp_test_prof;
DROP TYPE tip_telefon_prof;

--11

DECLARE
 TYPE tip_cod IS VARRAY(5) OF NUMBER(3);
 coduri tip_cod := tip_cod(205,206); 
BEGIN
 FOR i IN coduri.FIRST..coduri.LAST LOOP
 DELETE FROM emp_prof
 WHERE employee_id = coduri (i);
 END LOOP;
END; 
/
SELECT employee_id FROM emp_prof;
ROLLBACK;
 
 DECLARE
 TYPE tip_cod IS VARRAY(20) OF NUMBER;
 coduri tip_cod := tip_cod(205,206);
BEGIN
 FORALL i IN coduri.FIRST..coduri.LAST
 DELETE FROM emp_prof
 WHERE employee_id = coduri (i);
END;
/
SELECT employee_id FROM emp_prof;
ROLLBACK;
 
 
 --1
 
 DECLARE
    TYPE t_ang IS VARRAY(5) OF emp_prof.employee_id%TYPE;
    TYPE t_sal IS VARRAY(5) OF emp_prof.salary%TYPE;
  v_ang t_ang := t_ang();
  v_sal t_sal := t_sal();
 BEGIN
    SELECT employee_id, salary
    BULK COLLECT INTO v_ang, v_sal
    FROM
    (SELECT *
        FROM emp_prof
    WHERE commission_pct IS NULL
    ORDER BY salary asc)
    WHERE ROWNUM <=5;
 
 FOR i IN v_ang.FIRST..v_ang.LAST LOOP
     DBMS_OUTPUT.PUT_LINE('Angajatul cu codul ' || v_ang(i) ||
     ' are salariu ' || v_sal(i));
 END LOOP;
 
 FORALL i IN v_ang.FIRST..v_ang.LAST
    UPDATE emp_prof
    SET salary = salary * 1.05
    WHERE employee_id = v_ang(i)
    RETURNING salary BULK COLLECT INTO v_sal;
    
 FOR i IN v_ang.FIRST..v_ang.LAST LOOP
     DBMS_OUTPUT.PUT_LINE('Angajatul cu codul ' || v_ang(i) ||
     ' are noul salariu ' || v_sal(i));
 END LOOP;
 END;
 /
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 