----Puteti sa testati exemplele prezentate la curs folosind userul seria25 cu parola oracle creat pe serverul extern.
-- user: seria25
-- passw: oracle
-- hostname: 193.226.51.37
-- sid: o11g

SET SERVEROUTPUT ON
--------------
--Exemplul 3.1
SELECT POWER(3,2) FROM dual;

BEGIN
	DBMS_OUTPUT.PUT_LINE(POWER(3,2));
END;
/

BEGIN
	DBMS_OUTPUT.PUT_LINE(3**2);
END;
/

--------------
--Exemplul 3.2

DECLARE
nume_utilizator VARCHAR2(30);
data_creare_cont DATE DEFAULT SYSDATE;
numar_credite NUMBER(4) NOT NULL:=1000;
limita_inferioara_credite CONSTANT NUMBER:=100;
limita_superioara_credite NUMBER:=5000;
este_valid BOOLEAN:=TRUE;
BEGIN
	NULL;
END;
/

DECLARE
/*declarație corecta*/
i INTEGER;
j INTEGER;
BEGIN
	NULL;
END;
/

--------------
--Exemplul 3.3
DECLARE
	v_principal VARCHAR2(50);
BEGIN
v_principal:='variabila din blocul respectiv';
	DECLARE
		v_secundar VARCHAR2(50):='variabila din blocul secundar';
	BEGIN
		DBMS_OUTPUT.PUT_LINE('<<Bloc Secundar>>');
		DBMS_OUTPUT.PUT_LINE('Folosesc '||'v_principal');
		DBMS_OUTPUT.PUT_LINE('Folosesc '||'v_secundar');
		v_secundar:='Modific '||v_secundar;
		v_principal:='Modific '||v_principal;
		DBMS_OUTPUT.PUT_LINE(v_secundar);
		DBMS_OUTPUT.PUT_LINE(v_principal);
	END;
DBMS_OUTPUT.PUT_LINE('<<Bloc Principal>>');
--DBMS_OUTPUT.PUT_LINE(v_secundar);
DBMS_OUTPUT.PUT_LINE(v_principal);
END;
/

--------------
--Exemplul 3.4

BEGIN
	DBMS_OUTPUT.PUT_LINE('SGBD');
END;
/

DECLARE
	v_data DATE:=SYSDATE;
BEGIN
	DBMS_OUTPUT.PUT_LINE(v_data);
END;
/

DECLARE
	x NUMBER:=&p_x;
	y NUMBER:=&p_y;
BEGIN
	DBMS_OUTPUT.PUT_LINE(x/y);
EXCEPTION
	WHEN ZERO_DIVIDE THEN
		DBMS_OUTPUT.PUT_LINE('Nu poti sa imparti la 0!');
	WHEN OTHERS THEN
		DBMS_OUTPUT.PUT_LINE('Alta eroare!');
END;
/

--------------
--Exemplul 3.5

DECLARE
	v_clasificare clasific_clienti.clasificare%TYPE;
	v_categorie clasific_clienti.id_categorie%TYPE;
	v_client clasific_clienti.id_client%TYPE:=&p_client;
BEGIN
	SELECT clasificare, id_categorie
	INTO v_clasificare, v_categorie
	FROM clasific_clienti
	WHERE id_client=v_client;
	DBMS_OUTPUT.PUT_LINE(v_categorie||' '||v_clasificare);
EXCEPTION
	WHEN NO_DATA_FOUND THEN
	DBMS_OUTPUT.PUT_LINE('Nici o linie!');
	WHEN TOO_MANY_ROWS THEN
	DBMS_OUTPUT.PUT_LINE('Mai multe linii');
	WHEN OTHERS THEN
	DBMS_OUTPUT.PUT_LINE('Alta eroare!');
END;
/

--------------
--Exemplul 3.6

VARIABLE h_clasificare VARCHAR2
VARIABLE h_categorie NUMBER
BEGIN
	SELECT clasificare, id_categorie
	INTO :h_clasificare, :h_categorie
	FROM clasific_clienti
	WHERE id_client=82;
EXCEPTION
	WHEN NO_DATA_FOUND THEN
	DBMS_OUTPUT.PUT_LINE('Clientul nu exista!');
	WHEN OTHERS THEN
	DBMS_OUTPUT.PUT_LINE('Alta eroare!');
END;
/

PRINT h_clasificare
PRINT h_categorie

--------------
--Exemplul 3.7

BEGIN
	DELETE FROM clasific_clienti WHERE id_client=209;

	INSERT INTO clasific_clienti VALUES (209,2,1,null);

	UPDATE clasific_clienti
	SET clasificare='D'
	WHERE id_client=209;

	COMMIT;
END;
/

--------------
--Exemplul 3.8

SET SERVEROUTPUT ON

DECLARE
	v_categorie NUMBER;
	v_produse NUMBER;
	v_clasificare CHAR(1); 
BEGIN
	DELETE FROM clasific_clienti WHERE id_client=209
	RETURNING id_categorie, nr_produse, clasificare
	INTO v_categorie,v_produse,v_clasificare;

	INSERT INTO clasific_clienti
	VALUES (209,v_produse,v_clasificare,v_categorie);

	UPDATE clasific_clienti
	SET clasificare =v_clasificare
	WHERE id_client = 209;
	COMMIT;
END;
/

---------------
--Exemplul 3.9

DECLARE
	x NUMBER(2) NOT NULL;
BEGIN
	x:=2;
	DBMS_OUTPUT.PUT_LINE(x);
END;
/

DECLARE
	x NUMBER(2) NOT NULL:=2;
BEGIN
	DBMS_OUTPUT.PUT_LINE(x);
END;
/

---------------
--Exemplul 3.10

DECLARE
	v_nr NATURAL;
	v_clasificare CHAR(1):=UPPER('&p_clasificare');
BEGIN
	SELECT COUNT(*) INTO v_nr
	FROM clasific_clienti
	WHERE clasificare=v_clasificare;

	IF v_nr=0 THEN
		DBMS_OUTPUT.PUT_LINE('Nu exista clienti de tipul '|| v_clasificare);
	ELSE
		DBMS_OUTPUT.PUT_LINE('Exista '|| v_nr ||'clienti de tipul '|| v_clasificare);
	END IF;
END;
/

---------------
--Exemplul 3.11

DECLARE
	v_nr NATURAL;
	v_clasificare CHAR(1):=UPPER('&p_clasificare');
BEGIN
	SELECT COUNT(*) INTO v_nr
	FROM clasific_clienti
	WHERE clasificare=v_clasificare
	AND id_categorie=1;

	IF v_nr=0 THEN
		DBMS_OUTPUT.PUT_LINE('Nu exista clienti de tipul '|| v_clasificare);
	ELSE
		IF v_nr=1 THEN
			DBMS_OUTPUT.PUT_LINE('Exista 1 client de tipul '|| v_clasificare);
		ELSE
			DBMS_OUTPUT.PUT_LINE('Exista '|| v_nr || ' clienti de tipul '|| v_clasificare);
		END IF;
	END IF;
END;
/
---------------
--Exemplul 3.12

DECLARE
	v_nr NATURAL;
	v_clas CHAR(1):=UPPER('&p_clasificare');
BEGIN
	SELECT COUNT(*) INTO v_nr
	FROM clasific_clienti
	WHERE clasificare=v_clas
	AND id_categorie=1;

	IF v_nr=0 THEN
		DBMS_OUTPUT.PUT_LINE('Nu exista clienti de tipul '|| v_clas);
	ELSIF v_nr=1 THEN
		DBMS_OUTPUT.PUT_LINE('Exista 1 client de tipul '||v_clas);
	ELSE
		DBMS_OUTPUT.PUT_LINE('Exista '||v_nr||' clienti de tipul '||v_clas);
	END IF;
END;
/

---------------
--Exemplul 3.13

DECLARE
	v_nr NATURAL;
	v_clasificare CHAR(1):=UPPER('&p_clasificare');
BEGIN
	SELECT COUNT(*) INTO v_nr
	FROM clasific_clienti
	WHERE clasificare=v_clasificare
	AND id_categorie=1;

	CASE v_nr
		WHEN 0 THEN
			DBMS_OUTPUT.PUT_LINE('Nu exista clienti de tipul '|| v_clasificare);
		WHEN 1 THEN
			DBMS_OUTPUT.PUT_LINE('Exista 1 client de tipul '|| v_clasificare);
		ELSE
			DBMS_OUTPUT.PUT_LINE('Exista '|| v_nr || ' clienti de tipul '|| v_clasificare);
	END CASE;
END;
/

---------------
--Exemplul 3.14

DECLARE
	v_nr NATURAL;
	v_clas CHAR(1):=UPPER('&p_clasificare');
BEGIN
	SELECT COUNT(*) INTO v_nr
	FROM clasific_clienti
	WHERE clasificare=v_clas
	AND id_categorie=1;

	CASE
		WHEN v_nr=0 THEN
			DBMS_OUTPUT.PUT_LINE('Nu exista clienti de tipul '||v_clas);
		WHEN v_nr=1 THEN
			DBMS_OUTPUT.PUT_LINE('Exista 1 client de tipul '||v_clas);
		ELSE
			DBMS_OUTPUT.PUT_LINE('Exista '||v_nr||' clienti de tipul '||v_clas);
	END CASE;
END;
/

-------------
Exemplul 3.15

UNDEFINE p_clasificare
SELECT
	CASE 
    	WHEN COUNT(*)=0 THEN
			'Nu exista clienti de tipul '||UPPER('&&p_clasificare')
		WHEN COUNT(*)=1 THEN
			'Exista 1 client de tipul '||UPPER('&&p_clasificare')
		ELSE
			'Exista '||COUNT(*)||' clienti de tipul '||UPPER('&&p_clasificare')
	END "INFO_CLIENTI"
FROM clasific_clienti
WHERE clasificare=UPPER('&p_clasificare')
AND id_categorie=1;

--sau

UNDEFINE p_clasificare
SELECT
	CASE COUNT(*)
		WHEN 0 THEN
			'Nu exista clienti de tipul '||UPPER('&&p_clasificare')
		WHEN 1 THEN
			'Exista 1 client de tipul '||UPPER('&&p_clasificare')
		ELSE
			'Exista '||COUNT(*)||' clienti de tipul '||UPPER('&&p_clasificare')
	END "INFO_CLIENTI"
FROM clasific_clienti
WHERE clasificare=UPPER('&p_clasificare')
AND id_categorie=1;

---------------
--Exemplul 3.16

UNDEFINE p_clasificare
DECLARE
	v_nr NATURAL;
	v_clasificare CHAR(1):=UPPER('&p_clasificare');
	mesaj VARCHAR2(100);
BEGIN
	SELECT COUNT(*) INTO v_nr
	FROM clasific_clienti
	WHERE clasificare=v_clasificare
	AND id_categorie=1;

	mesaj:=CASE
			WHEN v_nr=0 THEN
				'Nu exista clienti de tipul '||v_clasificare
			WHEN v_nr=1 THEN
				'Exista 1 client de tipul '||v_clasificare
			ELSE
				'Exista '||v_nr||' clienti de tipul '||v_clasificare
			END;
	DBMS_OUTPUT.PUT_LINE(mesaj);
END;
/

-------------
Exemplul 3.17

DECLARE
	cod_ascii NUMBER:=ASCII('A');
BEGIN
	LOOP
		DBMS_OUTPUT.PUT(CHR(cod_ascii) || ' ');
		cod_ascii:=cod_ascii+1;
	-- EXIT;  
	EXIT WHEN cod_ascii > ASCII('E');
	/* IF cod_ascii > ASCII('E') THEN EXIT;
	    END IF; 
	*/
	END LOOP;
	DBMS_OUTPUT.NEW_LINE;
	DBMS_OUTPUT.PUT_LINE('Iesire cand am ajuns la ' || CHR(cod_ascii));
END;
/

-------------
Exemplul 3.18

DECLARE
	i NATURAL :=1;
BEGIN
	LOOP
		DBMS_OUTPUT.PUT(i**2||' ');
		i:=i+1;
		EXIT WHEN i>10;
	END LOOP;
	DBMS_OUTPUT.NEW_LINE;
	DBMS_OUTPUT.PUT_LINE('Iesire cand i= '||i);
END;
/

DECLARE
	i NATURAL :=1;
BEGIN
	LOOP
		DBMS_OUTPUT.PUT(i**2||' ');
		i:=i+1;
		IF i<=5 THEN CONTINUE;
			--controlul este preluat de urmatoarea iteratie
		END IF;
		DBMS_OUTPUT.NEW_LINE;
		EXIT WHEN i>10;
	END LOOP;
	DBMS_OUTPUT.PUT_LINE('Iesire cand i= '||i);
END;
/

DECLARE
	i NATURAL :=1;
BEGIN
	LOOP
		DBMS_OUTPUT.PUT(i**2||' ');
		i:=i+1;
		CONTINUE WHEN i<=5;
		--controlul este preluat de urmatoarea iteratie
		DBMS_OUTPUT.NEW_LINE;
		EXIT WHEN i>10;
	END LOOP;
	DBMS_OUTPUT.PUT_LINE('Iesire cand i= '||i);
END;
/

-------------
Exemplul 3.19

DECLARE
	i NATURAL:=1;
BEGIN
	WHILE i<=10 LOOP
		DBMS_OUTPUT.PUT(i**2 || ' ' );
		i:=i+1;
	END LOOP;
	DBMS_OUTPUT.NEW_LINE;
	DBMS_OUTPUT.PUT_LINE('Iesire cand i= ' || i);
END;
/

DECLARE
i NATURAL:=1;
BEGIN
	WHILE i<=10 LOOP
		DBMS_OUTPUT.PUT(i**2 || ' ');
		i:=i+1;
		CONTINUE WHEN i<=5;
	DBMS_OUTPUT.NEW_LINE;
	END LOOP;
	DBMS_OUTPUT.PUT_LINE('Iesire cand i= ' || i);
END;
/

-------------
Exemplul 3.20

BEGIN
	FOR i IN 1..10 LOOP
		DBMS_OUTPUT.PUT(i**2 || ' ');
	END LOOP;
	DBMS_OUTPUT.NEW_LINE;
END;
/

BEGIN
	FOR i IN REVERSE 1..10 LOOP
		DBMS_OUTPUT.PUT(i**2 || ' ');
	END LOOP;
	DBMS_OUTPUT.NEW_LINE;
END;
/

BEGIN
	FOR i IN REVERSE 1..10 LOOP
		DBMS_OUTPUT.PUT(i**2 || ' ');
		CONTINUE WHEN i<=5;
		DBMS_OUTPUT.NEW_LINE;
	END LOOP;
	DBMS_OUTPUT.NEW_LINE;
END;
/

-------------
Exemplul 3.21

DECLARE
	x NUMBER(2) NOT NULL :=2;
BEGIN
	NULL;
END;
/

-------------
Exemplul 3.22

DECLARE
	v_clasificare clasific_clienti.clasificare%TYPE;
	v_categorie clasific_clienti.id_categorie%TYPE;
	v_client clasific_clienti.id_client%TYPE :=978;
BEGIN
	SELECT clasificare, id_categorie
	INTO v_clasificare, v_categorie
	FROM clasific_clienti
	WHERE id_client=v_client;
	DBMS_OUTPUT.PUT_LINE(v_categorie||' '||v_clasificare);
EXCEPTION
	WHEN NO_DATA_FOUND THEN
		--DBMS_OUTPUT.PUT_LINE('Nici o linie!');
		NULL;
	WHEN TOO_MANY_ROWS THEN
		DBMS_OUTPUT.PUT_LINE('Mai multe linii!');
	WHEN OTHERS THEN
		DBMS_OUTPUT.PUT_LINE('Alta eroare!');
END;
/

-------------
Exemplul 3.23

DECLARE
	i INT(1);
BEGIN
	FOR i IN 1..5 LOOP
		IF i=3 THEN
			GOTO eticheta;
		ELSE
		DBMS_OUTPUT.PUT_LINE('i='||i);
		END IF;
	END LOOP;
	<<eticheta>>
	--instructiunea NULL nu este necesara
	DBMS_OUTPUT.PUT_LINE('STOP cand i='||i);
END;
/

DECLARE
	j INT(1);
BEGIN
	FOR i IN 1..5 LOOP
		j:=i;
		IF i=3 THEN
			GOTO eticheta;
		ELSE
			DBMS_OUTPUT.PUT_LINE('i='||i);
		END IF;
	END LOOP;
	<<eticheta>>
	-- instructiunea NULL nu este necesara
	DBMS_OUTPUT.PUT_LINE('STOP cand i='||j);
END;
/

DECLARE
	j INT(1);
BEGIN
	FOR i IN 1..5 LOOP
		IF i=3 THEN
			DBMS_OUTPUT.PUT_LINE('STOP cand i='||i);
			GOTO eticheta;
		ELSE
			DBMS_OUTPUT.PUT_LINE('i='||i);
		END IF;
	END LOOP;
	<<eticheta>>
	-- instructiunea NULL este necesara
	NULL;
END;
/

BEGIN
	FOR i IN 1..5 LOOP
		IF i=3 THEN
			NULL;
		ELSE
			DBMS_OUTPUT.PUT_LINE('i='||i);
		END IF;
	END LOOP;
END;
/


------------------------------------------------------