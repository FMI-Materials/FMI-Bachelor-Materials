alter session set NLS_LANGUAGE='AMERICAN';
alter session set NLS_TERRITORY='AMERICA';
alter session set NLS_DATE_LANGUAGE='AMERICAN';

SET SERVEROUTPUT ON

--Exemplul 6.1
CREATE OR REPLACE PROCEDURE proc_ex1
	(v_id IN produse.id_produs%TYPE, v_procent NUMBER)
AS
BEGIN
	UPDATE produse
	SET pret_unitar= pret_unitar*(1+v_procent)
	WHERE id_produs=v_id;
	DBMS_OUTPUT.PUT_LINE(SQL%ROWCOUNT||' linii actualizate');
	EXCEPTION
		WHEN NO_DATA_FOUND THEN
			RAISE_APPLICATION_ERROR(-20000,'Nu exista produsul');
END;
/

EXECUTE proc_ex1(1,0.5)

--------------
--Exemplul 6.2
CREATE OR REPLACE PROCEDURE proc_ex2
	(v_id IN produse.id_produs%TYPE, v_procent NUMBER)
AS
	exceptie EXCEPTION;
BEGIN
	UPDATE produse
	SET pret_unitar= pret_unitar*(1+v_procent)
	WHERE id_produs=v_id;
	IF SQL%NOTFOUND THEN
		RAISE exceptie;
	END IF;
	EXCEPTION
		WHEN exceptie THEN
			RAISE_APPLICATION_ERROR(-20000,'Nu exista produsul');
END;
/

EXECUTE proc_ex2(100,0.5)

--------------
--Exemplul 6.3

ALTER TABLE produse DISABLE ALL TRIGGERS;
EXECUTE proc_ex2(37,0.1)
ALTER TABLE produse ENABLE ALL TRIGGERS;

--------------
--Exemplul 6.4 - Tema

--Definiți un bloc PL/SQL în care procedura proc_ex2 este apelată pentru fiecare produs 
--din categoria "it" (nivel 1). Prețul acestor produse va fi micșorat cu 5%.

-------------
--Exemplul 6.5

DECLARE
	v_den categorii.denumire%TYPE:='&p_den';
	v_nivel categorii.nivel%TYPE:=&p_niv;
	v_parinte categorii.id_parinte%TYPE;
	PROCEDURE proc_ex5
		(id categorii.id_categorie%TYPE default 2000,
		 den categorii.denumire%TYPE,
		 nivel categorii.nivel%TYPE,
		 parinte categorii.id_parinte%TYPE)
	IS BEGIN
		INSERT INTO categorii(id_categorie,denumire,nivel,id_parinte)
		VALUES (id,den,nivel,parinte);
		DBMS_OUTPUT.PUT_LINE('Au fost inserate '||SQL%ROWCOUNT||' linii');
	END;
BEGIN
	v_parinte:=&p_parinte;
	proc_ex5(den=>v_den,nivel=>v_nivel, parinte=>v_parinte);
END;
/

--------------
--Exemplul 6.6
CREATE OR REPLACE PROCEDURE proc_ex6
	(p_id IN categorii.id_categorie%TYPE,
	 p_den OUT categorii.denumire%TYPE,
	 p_parinte OUT categorii.id_parinte%TYPE)
IS
BEGIN
	SELECT denumire, id_parinte
	INTO p_den, p_parinte
	FROM categorii
	WHERE id_categorie=p_id;
END;
/

DECLARE
	v_den categorii.denumire%TYPE;
	v_parinte categorii.id_parinte%TYPE;
BEGIN
	proc_ex6(3,v_den,v_parinte);
	DBMS_OUTPUT.PUT_LINE(v_den||' '||v_parinte);
END;
/

--------------
--Exemplul 6.7
CREATE OR REPLACE PROCEDURE proc_ex6
	(p_id IN OUT categorii.id_categorie%TYPE,
	 p_den OUT categorii.denumire%TYPE)
IS
BEGIN
	SELECT denumire, id_parinte
	INTO p_den, p_id
	FROM categorii
	WHERE id_categorie=p_id;
END;
/

DECLARE
	v_den categorii.denumire%TYPE;
	v_id categorii.id_parinte%TYPE:=3;
BEGIN
	proc_ex6(v_id,v_den);
	DBMS_OUTPUT.PUT_LINE(v_den||' '||v_id);
END;
/

--------------
--Exemplul 6.8
CREATE OR REPLACE FUNCTION func_ex8
	(p_id IN clienti.id_client%TYPE,
	 p_an NUMBER DEFAULT 2016)
	RETURN NUMBER
IS
	rezultat NUMBER;
BEGIN
	SELECT COUNT(DISTINCT id_produs)
	INTO rezultat
	FROM facturi f, facturi_contin_produse fp
	WHERE f.id_factura=fp.id_factura
	AND EXTRACT(YEAR FROM data)=p_an
	AND id_client=p_id;
	RETURN rezultat;
END;
/

--------------
--Exemplul 6.9
SELECT func_ex8(1,2016)
FROM DUAL;

--------------
--Exemplul 6.10
VARIABLE rezultat NUMBER
EXECUTE :rezultat:=func_ex8(1,2016);
PRINT rezultat

---------------
--Exemplul 6.11
BEGIN
	DBMS_OUTPUT.PUT_LINE(func_ex8(1,2016));
END;
/

---------------
--Exemplul 6.12
DECLARE
	n NUMBER :=func_ex8(p_id=>1);
BEGIN
	DBMS_OUTPUT.PUT_LINE(n);
END;
/

---------------
--Exemplul 6.13
VARIABLE rezultat NUMBER
CALL func_ex8(1,2016) INTO :rezultat;
PRINT rezultat

---------------
--Exemplul 6.14
CREATE OR REPLACE FUNCTION func_ex14(v_id NUMBER)
RETURN VARCHAR2
IS
	rez VARCHAR2(150):='';
BEGIN
	FOR i IN (SELECT denumire
			  FROM categorii
			  START WITH id_categorie=v_id
			  CONNECT BY PRIOR id_parinte=id_categorie)
	LOOP
		rez:=i.denumire||'/'||rez;
	END LOOP;
	RETURN rez;
END;
/

SELECT id_produs, denumire, func_ex14(id_categorie) AS arbore
FROM produse
WHERE ROWNUM<=10;

---------------
--Exemplul 6.15
DECLARE
	v_nr_trimestru NUMBER(10);
	v_nr_luna NUMBER(10);
	FUNCTION nr_produse
		(p_id produse.id_produs%TYPE,
		 p_luna NUMBER)
	RETURN NUMBER
	IS 
		rezultat NUMBER(10);
	BEGIN
		SELECT SUM(cantitate)
		INTO rezultat
		FROM facturi f, facturi_contin_produse fp
		WHERE f.id_factura=fp.id_factura
		AND fp.id_produs=p_id
		AND EXTRACT(MONTH FROM data)=p_luna;
		RETURN rezultat;
	END;
	FUNCTION nr_produse
		(p_id produse.id_produs%TYPE,
		 p_trimestru CHAR)
	RETURN NUMBER
	IS
		rezultat NUMBER(10);
	BEGIN
		SELECT SUM(cantitate)
		INTO rezultat
		FROM facturi f, facturi_contin_produse fp
		WHERE f.id_factura=fp.id_factura
		AND fp.id_produs=p_id
		AND TO_CHAR(data,'q')=p_trimestru;
		RETURN rezultat;
	END;
BEGIN
	v_nr_luna:=nr_produse(1,10);
	DBMS_OUTPUT.PUT_LINE('Nr produse vandute in luna aprilie:'||
		v_nr_luna);
	v_nr_trimestru:=nr_produse(1,'2');
	DBMS_OUTPUT.PUT_LINE('Nr produse vandute in trimestrul 2'||
		v_nr_trimestru);
END;
/

---------------
--Exemplul 6.16
CREATE OR REPLACE FUNCTION fibonacci(n NUMBER)
	RETURN NUMBER RESULT_CACHE
IS
BEGIN
	IF(n=0) OR (n=1) THEN
		RETURN 1;
	ELSE
		RETURN fibonacci(n-1)+fibonacci(n-2);
	END IF;
END;
/

SELECT fibonacci(50)
FROM dual;

---------------
--Exemplul 6.17
DECLARE
	PROCEDURE alfa 
	IS
	BEGIN
		beta('apel beta din alfa'); --apel incorect
	END;
	PROCEDURE beta (x VARCHAR2)
	IS
	BEGIN
		DBMS_OUTPUT.PUT_LINE(x);
	END;
BEGIN
	alfa;
END;
/

DECLARE
	PROCEDURE beta (x VARCHAR2)
	IS
	BEGIN
		DBMS_OUTPUT.PUT_LINE(x);
	END;
	PROCEDURE alfa 
	IS
	BEGIN
		beta('apel beta din alfa'); --apel corect
	END;
BEGIN
	alfa;
END;
/

DECLARE
		PROCEDURE beta (x VARCHAR2); --declarație forward
		PROCEDURE alfa 
		IS
		BEGIN
			beta('apel beta din alfa'); --apel corect
		END;
		PROCEDURE beta (x VARCHAR2)
		IS
		BEGIN
			DBMS_OUTPUT.PUT_LINE(x);
		END;
	BEGIN
		alfa;
	END;
/

---------------
--Exemplul 6.18
SELECT OBJECT_ID, OBJECT_NAME, OBJECT_TYPE, STATUS
FROM USER_OBJECTS
WHERE OBJECT_TYPE IN ('PROCEDURE','FUNCTION');

---------------
--Exemplul 6.19
CREATE OR REPLACE PROCEDURE proc_ex19
IS
BEGIN
	FOR i IN (SELECT OBJECT_TYPE, OBJECT_NAME
			  FROM USER_OBJECTS
			  WHERE STATUS='INVALID'
			  AND OBJECT_TYPE IN ('PROCEDURE','FUNCTION'))
	LOOP
	--recompileaza toate subprogramele invalide din schema curenta
	DBMS_DDL.ALTER_COMPILE(i.OBJECT_TYPE, USER, i.OBJECT_NAME);
	END LOOP;
END;
/

EXEC proc_ex19

---------------
--Exemplul 6.20
SELECT TEXT
FROM USER_SOURCE
WHERE NAME='FIBONACCI'
ORDER BY LINE;

---------------
--Exemplul 6.21
SELECT NAME, TYPE, REFERENCED_NAME, REFERENCED_TYPE
FROM USER_DEPENDENCIES
WHERE REFERENCED_TYPE IN
	('TYPE','TABLE','PROCEDURE','FUNCTION','VIEW')
	AND NAME NOT LIKE 'BIN%'
ORDER BY 1;

---------------
--Exemplul 6.22
--conectare ca administrator
EXECUTE DEPTREE_FILL('TABLE', 'CURS_PLSQL','FACTURI');
SELECT NESTED_LEVEL, TYPE, NAME
FROM DEPTREE
ORDER BY SEQ#;

SELECT *
FROM IDEPTREE;

---------------
--Exemplul 6.23
CREATE OR REPLACE FUNCTION calc (x IN REAL)
RETURN NUMBER
  AS LANGUAGE C 
  	 LIBRARY biblioteca 
  	 NAME C_CALC 
  	 PARAMETERS (x BY REFERENCES);
/

BEGIN
  calc(100);
END;
/

--------------------------