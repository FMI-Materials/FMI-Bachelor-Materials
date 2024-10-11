--3

-- acest tip de variabila se numeste bind variable si este declarata folosind keyword-ul VARIABLE
-- iar accesul la ea se face prin :bindVariableName
-- putem sa o folosim pe post de variabila globala pt PL/SQL
VARIABLE g_mesaj VARCHAR2(50);
BEGIN
:g_mesaj := 'Invat PL/SQL';
END;
/
PRINT g_mesaj;

Exec :g_mesaj   := 'Invat PL/SQL 2';

PRINT g_mesaj;

-- View -> DBMS output

-- PUT deschide un buffer in care pot sa tot adaug caractere
-- si trebuie explicit sa folosesc .new_line cand am terminat propozitia
-- care pune la final  end of line marker
-- PUT_LINE pune automat eol marker
-- ambele le folosesc pentru debugging

BEGIN
dbms_output.put('A');
dbms_output.put('B');
dbms_output.put('C');
dbms_output.put('D');
dbms_output.new_line;
dbms_output.put('E');
dbms_output.put('F');
dbms_output.put_line('G');
END;
/

Begin
  dbms_output.put_line('A');
  dbms_output.put_line('B');
  dbms_output.put_line('C');
End;
/

--4
DECLARE
 v_dep departments.department_name%TYPE;
BEGIN
 SELECT department_name
 INTO v_dep
 FROM employees e, departments d
 WHERE e.department_id=d.department_id
 GROUP BY department_name
 HAVING COUNT(*) = (SELECT MAX(COUNT(*))
                     FROM employees
                    GROUP BY department_id);
 DBMS_OUTPUT.PUT_LINE('Departamentul '|| v_dep);
END;
/

-- daca am mai mult de doua linii primesc exceptia too_many_rows
-- pe care pot sa o ascund folosind un bloc de exceptii
-- de asemenea, daca pun conditia  COUNT(*) > MAX
-- primesc eroarea no_data_found

DECLARE
  v_dep departments.department_name%TYPE;
BEGIN
  SELECT department_name
  INTO   v_dep
  FROM   employees e, departments d
  WHERE  e.department_id=d.department_id 
  GROUP BY department_name
  HAVING COUNT(*) > (SELECT MAX(COUNT(*))
                     FROM   emp_prof
                     GROUP BY department_id);
  DBMS_OUTPUT.PUT_LINE('Departamentul '|| v_dep);
exception
    when too_many_rows then  
        DBMS_OUTPUT.PUT_LINE('Prea multe linii');
    when no_data_found then  
        DBMS_OUTPUT.PUT_LINE('Nici o linie');
END;
/

--5
VARIABLE rezultat VARCHAR2(35)
BEGIN
 SELECT department_name
 INTO :rezultat
FROM employees e, departments d
 WHERE e.department_id=d.department_id
 GROUP BY department_name
 HAVING COUNT(*) = (SELECT MAX(COUNT(*))
                     FROM employees
                    GROUP BY department_id);
 DBMS_OUTPUT.PUT_LINE('Departamentul '|| :rezultat);
END;
/
PRINT rezultat;

--6 tema

-- avem operatorii: IS NULL, LIKE, BETWEEN, IN , NOT, AND, OR, =, !=, <, >, <=, >=
-- pe care ii putem folosi in partea de conditions ale tuturor acestor instructiuni


--7
SET VERIFY OFF
DECLARE
 v_cod employees.employee_id%TYPE := &p_cod;
 v_bonus NUMBER(8);
 v_salariu_anual NUMBER(8);
BEGIN
 SELECT salary*12 INTO v_salariu_anual
 FROM employees 
 WHERE employee_id = v_cod;
 
 IF v_salariu_anual >= 200001
     THEN v_bonus := 20000;
     ELSIF v_salariu_anual BETWEEN 100001 AND 200000
     THEN v_bonus := 10000;
     ELSE v_bonus := 5000;
 END IF;
 
DBMS_OUTPUT.PUT_LINE('Bonusul este ' || v_bonus);
END;
/
SET VERIFY ON


SET VERIFY OFF
DECLARE
 v_cod employees.employee_id%TYPE := &p_cod;
 v_bonus NUMBER(8);
 v_salariu_anual NUMBER(8);
BEGIN
 SELECT salary*12 INTO v_salariu_anual
 FROM employees 
 WHERE employee_id = &p_cod;
 
 IF v_salariu_anual >= 200001
     THEN v_bonus := 20000;
     ELSIF v_salariu_anual BETWEEN 100001 AND 200000
     THEN v_bonus := 10000;
     ELSE v_bonus := 5000;
 END IF;
 
DBMS_OUTPUT.PUT_LINE('Bonusul este ' || v_bonus);
END;
/
SET VERIFY ON

--8

DECLARE
 v_cod employees.employee_id%TYPE:=&p_cod;
 v_bonus NUMBER(8);
 v_salariu_anual NUMBER(8);
BEGIN
 SELECT salary*12 INTO v_salariu_anual
 FROM employees 
 WHERE employee_id = v_cod;
 
 CASE 
     WHEN v_salariu_anual>=200001
        THEN v_bonus := 20000;
     WHEN v_salariu_anual BETWEEN 100001 AND 200000
        THEN v_bonus  := 10000;
     ELSE v_bonus := 5000;
 END CASE;
DBMS_OUTPUT.PUT_LINE('Bonusul este ' || v_bonus);
END;
/

--9

select employee_id, department_id, salary
from emp_prof
where employee_id = 200;

-- folosim define pentru a ne defini o variabila cu o anumita valoare
-- vizibila oriunde in sesiunea noastra

-- define simplu ne afiseaza toate variabilele noastre
-- same si cu variable simplu
-- cateva dintre variabile sunt define de sistem la startup
define;

-- daca folosim define si ii oferim si o valoare
-- when we want to reference said variable with  &
-- nu o sa mai apara prompt-ul pt user input

DEFINE p_cod_sal = 200
DEFINE p_cod_dept = 80
DEFINE p_procent =20

-- daca vrem sa stergem variabile folosim undefine
UNDEFINE p_cod_sal;
UNDEFINE p_cod_dept;
UNDEFINE p_procent;

-- in momentul in care compilatorul intalneste & si nu gaseste o valoare
-- deja pentru variabila de dupa &, apare prompt-ul

DECLARE
 v_cod_sal emp_prof.employee_id%TYPE:= &p_cod_sal;
 v_cod_dept emp_prof.department_id%TYPE:= &p_cod_dept;
 v_procent NUMBER(8):=&p_procent;

BEGIN
 UPDATE emp_prof
 SET department_id = v_cod_dept, 
 salary=salary + (salary* v_procent/100)
 WHERE employee_id= v_cod_sal;
 
 IF SQL%ROWCOUNT =0 THEN 
 DBMS_OUTPUT.PUT_LINE('Nu exista un angajat cu acest cod');
 ELSE DBMS_OUTPUT.PUT_LINE('Actualizare realizata');
 END IF;
END;
/
ROLLBACK;

-- mai exista si && care ii spune compilatorului sa stocheze prima valoarea
-- introdusa pana se incheie sesiunea
-- deci nu mai apare prompt-ul inca o data

DECLARE
 v_cod_sal emp_prof.employee_id%TYPE:= &&p_cod_sal;
 v_cod_dept emp_prof.department_id%TYPE:= &p_cod_dept;
 v_procent NUMBER(8):=&p_procent;

BEGIN
 UPDATE emp_prof
 SET department_id = v_cod_dept, 
 salary=salary + (salary* v_procent/100)
 WHERE employee_id =  &p_cod_sal;
 
 IF SQL%ROWCOUNT =0 THEN 
 DBMS_OUTPUT.PUT_LINE('Nu exista un angajat cu acest cod');
 ELSE DBMS_OUTPUT.PUT_LINE('Actualizare realizata');
 END IF;
END;
/

-- daca vreau sa ii afisez un mesaj custom utilizatorului atunci cand el introduce de la tastatura
-- avem comanda accept

ACCEPT v_mesaj PROMPT 'Introduceti mesajul dorit';

define;


--10

create table zile_prof
(id number, 
data date, 
nume_zi VARCHAR2(30));

DECLARE
 contor NUMBER(6) := 1;
 v_data DATE;
 maxim NUMBER(2) := LAST_DAY(SYSDATE)-SYSDATE;
BEGIN
 LOOP
     v_data := sysdate+contor;
     INSERT INTO zile_prof
     VALUES (contor,v_data,to_char(v_data,'Day'));
     contor := contor + 1;
     EXIT WHEN contor > maxim;
 END LOOP;
END;
/

select * from zile_prof;

rollback;


--11

-- daca avem o variabila de tip Boolean,
-- putem sa folosim pe post de conditia din while
-- direct variabila

/*
    ...
    v_check  BOOLEAN := true;
    ...
    while  v_check loop
        ...
    end loop;
    ...
*/

DECLARE
 contor NUMBER(6) := 1;
 v_data DATE;
 maxim NUMBER(2) := LAST_DAY(SYSDATE)-SYSDATE;

BEGIN
     WHILE contor <= maxim LOOP
         v_data := sysdate+contor;
         INSERT INTO zile_prof VALUES (contor,v_data,to_char(v_data,'Day'));
         contor := contor + 1;
     END LOOP;
END;
/

select * from zile_prof;

rollback;

--12

-- limita inferioara trebuie sa fie mai mica decat cea superioara
-- altfel for-ul nu se executa
-- requirement-ul e invers atunci cand avem REVERSE

DECLARE
 v_data DATE;
 maxim NUMBER(2) := LAST_DAY(SYSDATE)-SYSDATE;
BEGIN
 FOR contor IN 1..maxim LOOP
     v_data := sysdate+contor;
     INSERT INTO zile_prof VALUES (contor,v_data,to_char(v_data,'Day'));
 END LOOP;
END;
/

select * from zile_prof;

DELETE FROM zile_prof WHERE 1=1;

-- instructiune for in ordine inversa
-- cu contor-- de la maxim la 1

DECLARE
 v_data DATE;
 maxim NUMBER(2) := LAST_DAY(SYSDATE)-SYSDATE;
BEGIN
 FOR contor IN REVERSE 1..maxim LOOP
     v_data := sysdate+contor;
     INSERT INTO zile_prof
     VALUES (contor,v_data,to_char(v_data,'Day'));
 END LOOP;
END;
/

select * from zile_prof;


--13

--Varianta 1
DECLARE
 i POSITIVE := 1;
 max_loop CONSTANT POSITIVE := 10;
BEGIN
    LOOP
         i:=i+1;
         IF i>max_loop THEN
             DBMS_OUTPUT.PUT_LINE('in loop i=' || i);
             GOTO urmator;
         END IF;
    END LOOP;
i:=1;
<<urmator>> 
DBMS_OUTPUT.PUT_LINE('dupa loop i=' || i);
END;
/

-- pot sa ma folosesc de goto pentru a rula iar un set de comenzi
-- in stilul unui loop

DECLARE
   v_last_name  VARCHAR2(25);
   v_emp_id     NUMBER(6) := 100;
BEGIN
   <<restart>>
   SELECT last_name INTO v_last_name FROM employees 
          WHERE employee_id = v_emp_id;
   BEGIN
      DBMS_OUTPUT.PUT_LINE (v_last_name);
      v_emp_id := v_emp_id + 5;
      IF v_emp_id < 120 THEN
        GOTO restart;
      END IF;
   END;
END;
/


--Varianta 2
DECLARE
 i POSITIVE := 1;
 max_loop CONSTANT POSITIVE := 10;
BEGIN
 i:=1;
 LOOP
     i:=i+1;
     DBMS_OUTPUT.PUT_LINE('in loop i=' || i);
     EXIT WHEN i>max_loop;
 END LOOP;
 i:=1;
 DBMS_OUTPUT.PUT_LINE('dupa loop i=' || i);
END;
/

-- eticheta pt exit nume_etichete trebuie sa se refere la instructiunea loop
DECLARE
 i POSITIVE := 1;
 max_loop CONSTANT POSITIVE := 10;
BEGIN
 i:=1;
 <<urmator>>  LOOP
     i:=i+1;
     DBMS_OUTPUT.PUT_LINE('in loop i=' || i);
     EXIT urmator;
 END LOOP;

 i:=1;
 DBMS_OUTPUT.PUT_LINE('dupa loop i=' || i);
END;
/


-- EXERCITII

--1
-- nu ma leg de variabile  prin numele blocului.nume variabila
-- deci este vorba despre variabilele din scope-ul blocului in care  ma aflu

DECLARE
numar number(3):=100;
mesaj1 varchar2(255):='text 1';
mesaj2 varchar2(255):='text 2';
BEGIN
     DECLARE
         numar number(3):=1;
         mesaj1 varchar2(255):='text 2';
         mesaj2 varchar2(255):='text 3';
     BEGIN
         numar:=numar+1;
         mesaj2:=mesaj2||' adaugat in sub-bloc';
        DBMS_OUTPUT.PUT_LINE('numar subbloc ' || numar);
        DBMS_OUTPUT.PUT_LINE('mesaj1 subbloc ' || mesaj1);
        DBMS_OUTPUT.PUT_LINE('mesaj2 subbloc ' || mesaj2);
          
     END;
numar:=numar+1;
mesaj1:=mesaj1||' adaugat un blocul principal';
mesaj2:=mesaj2||' adaugat in blocul principal'; 

DBMS_OUTPUT.PUT_LINE('numar bloc ' || numar);
DBMS_OUTPUT.PUT_LINE('mesaj1 bloc ' || mesaj1);
DBMS_OUTPUT.PUT_LINE('mesaj2 bloc ' || mesaj2);
END;

--2

-- a) = 12 c)
select ziua, (select count(*) from rental where to_char(book_date,'dd.mm.yyyy') = to_char(ziua,'dd.mm.yyyy')) as nr
from  (select trunc(add_months(sysdate,-1),'month') + level-1 ziua
       from   dual
       connect by level<=extract (day from last_day(add_months(sysdate,-1))));
       
--b

create table octombrie_prof(id number, data date);

declare
d date := trunc(sysdate, 'mm');
n number := extract(day from last_day(sysdate));
begin
    for i IN 1..n LOOP
          insert into octombrie_prof
          values (i, d);
          d := d+1;
    END LOOP;
end;
/

select * from octombrie_prof;

-- b) partea cu SQL tema

-- 3 tema
-- pt variable de substitutie care trebuie sa fie string
-- punem '...' 
-- v_nume varchar2(20) := '&p_nume';

-- 4 tema
-- 5 tema


