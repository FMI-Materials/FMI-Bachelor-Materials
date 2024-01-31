SET SERVEROUTPUT ON

--------------
--Exemplul 9.1

DECLARE
	x NUMBER(2):=&p_x;
	y NUMBER(2):=&p_y;
BEGIN
	DBMS_OUTPUT.PUT_LINE(x/y);
	DBMS_OUTPUT.PUT_LINE(x);
	DBMS_OUTPUT.PUT_LINE(y);
EXCEPTION
	WHEN ZERO_DIVIDE THEN
		DBMS_OUTPUT.PUT_LINE('Codul erorii: '||SQLCODE);
		DBMS_OUTPUT.PUT_LINE('Mesajul erorii: '||SQLERRM);
END;
/

--------------
--Exemplul 9.2

DECLARE
	v_nr NUMBER:=&p_nr;
	v_den categorii.denumire%TYPE;
BEGIN
	SELECT denumire INTO v_den
	FROM categorii 
	WHERE id_categorie in (SELECT id_categorie
					  FROM produse 
					  GROUP BY id_categorie
					  HAVING COUNT(*)=v_nr);
	DBMS_OUTPUT.PUT_LINE('Categoria gasita: '||v_den);
EXCEPTION
	WHEN NO_DATA_FOUND THEN
		DBMS_OUTPUT.PUT_LINE('Nu exista categorii cu numarul specificat de produse');
	WHEN TOO_MANY_ROWS THEN
		DBMS_OUTPUT.PUT_LINE('Exista mai multe categorii cu numarul specificat de produse');
	WHEN OTHERS THEN
		DBMS_OUTPUT.PUT_LINE('Codul erorii: '||SQLCODE);
		DBMS_OUTPUT.PUT_LINE('Mesajul erorii: '||SQLERRM);
END;
/

--------------
--Exemplul 9.3

DECLARE
	x NUMBER(2):=&p_x;
	y NUMBER(2):=&p_y;
BEGIN
	IF x<0 OR y<0 THEN
		--declansare explicita
			RAISE INVALID_NUMBER;
	END IF;
	--declansare explicita cand y=0
	DBMS_OUTPUT.PUT_LINE(TO_CHAR(x/y,'999.99.99'));
EXCEPTION
	WHEN ZERO_DIVIDE THEN
		DBMS_OUTPUT.PUT_LINE('Impartirea la 0 nu este permisa');
	WHEN INVALID_NUMBER THEN
		--declansare implicita
		DBMS_OUTPUT.PUT_LINE('Nu sunt permise valori negative');
	WHEN OTHERS THEN
		--declansare implicita
		DBMS_OUTPUT.PUT_LINE('Codul erorii '||SQLCODE);
		DBMS_OUTPUT.PUT_LINE('Mesajul erorii '||SQLERRM);
END;
/

--------------
--Exemplul 9.4

DECLARE
	exista_produse EXCEPTION;
	PRAGMA EXCEPTION_INIT(exista_produse,-2292);
	v_denumire categorii.denumire%TYPE:='&p_denumire';
BEGIN
	DELETE FROM categorii WHERE denumire=v_denumire;
	IF SQL%NOTFOUND THEN
		RAISE NO_DATA_FOUND; --cand nu am select, trebuie sa lansez eu NO_DATA_FOUND
	END IF;
EXCEPTION
	WHEN exista_produse THEN
		DBMS_OUTPUT.PUT_LINE('Nu puteti sterge categoria '||v_denumire||' deoarece contine produse');
	WHEN NO_DATA_FOUND THEN
		DBMS_OUTPUT.PUT_LINE('Ati introdus date eronate');
END;
/

--incalcarea constrangerii de cheie externa determina eroarea cu codul -2292

--------------
--Exemplul 9.5

DECLARE
	exceptie EXCEPTION;
	cantitate_totala NUMBER;
	v_id produse.id_produs%TYPE;
	v_denumire produse.denumire%TYPE:='&p_denumire';
BEGIN
	SELECT id_produs 
	INTO v_id
	FROM produse
	WHERE denumire=v_denumire;

	SELECT SUM(cantitate)
	INTO cantitate_totala
	FROM facturi_contin_produse
	WHERE id_produs=v_id;

	IF cantitate_totala IS NULL THEN
		RAISE exceptie;
	END IF;

	DBMS_OUTPUT.PUT_LINE('Produs '||v_denumire||' - Numar bucati vandute= '||cantitate_totala);
EXCEPTION
	WHEN TOO_MANY_ROWS THEN
		DBMS_OUTPUT.PUT_LINE('Exista mai multe produse cu aceeasi denumire!');

	WHEN NO_DATA_FOUND THEN
		DBMS_OUTPUT.PUT_LINE('Nu exista produsul cu denumirea specificata!');
	WHEN exceptie THEN 
		DBMS_OUTPUT.PUT_LINE('Produsul nu are vanzari inregistrate');
	WHEN OTHERS THEN
		DBMS_OUTPUT.PUT_LINE('Alta eroare');
	END;
/

--Televizor - nr bucati vandute = 0
--Bicicleta - nr bucati vandute = 0
--Tricou - produsul nu are vanzari inregistrate


--Exemplul 9.6
--------------

CREATE OR REPLACE TRIGGER trig
  BEFORE UPDATE OF serie ON case
  FOR EACH ROW
  WHEN (NEW.serie <> OLD.serie)
BEGIN
  RAISE_APPLICATION_ERROR (-20145, 'Nu puteti modifica seria casei fiscale!');
END;
/

--blocul urmator detecteaza si trateaza eroarea
DECLARE
  -- declarare exceptie
  exceptie  EXCEPTION;
  -- asociere un nume codului de eroare folosit in trigger
  PRAGMA EXCEPTION_INIT(exceptie,-20145);
  BEGIN
  -- lansare comanda declasatoare
  UPDATE case
  SET  serie = serie||'0';
EXCEPTION
  -- tratare exceptie
  WHEN exceptie THEN
    -- se afiseaza mesajul erorii specificat in trigger in procedura RAISE_APPLICATION_ERROR
    DBMS_OUTPUT.PUT_LINE(SQLERRM);
END; 
/

--Exemplul 9.7
--------------

DECLARE
  v_den  produse.denumire%TYPE;
  v_id   produse.id_produs%TYPE := &p_id;
BEGIN
  SELECT denumire
  INTO   v_den
  FROM   produse
  WHERE  id_produs = v_id;
  <<eticheta>>
  DBMS_OUTPUT.PUT_LINE('Denumirea produsului este '||v_den);
EXCEPTION
  WHEN NO_DATA_FOUND THEN v_den := ' ';
    GOTO eticheta; --salt ilegal in blocul curent
END;
/

--Exemplul 9.8
--------------
BEGIN
  DECLARE
    nr_produse   NUMBER(10) := ' ';
          -- este generata eroarea VALUE_ERROR
  BEGIN
    SELECT  COUNT (DISTINCT id_produs)
    INTO    nr_produse
    FROM    facturi_contin_produse;
  EXCEPTION
    WHEN VALUE_ERROR THEN
      -- eroarea nu este captata si tratata in blocul intern
     DBMS_OUTPUT.PUT_LINE('Eroare bloc intern: ' || SQLERRM);
  END;
EXCEPTION
  WHEN VALUE_ERROR THEN
      -- eroarea este captata si tratata in blocul extern
   DBMS_OUTPUT.PUT_LINE('Eroare bloc extern: ' || SQLERRM );
END;
/

--Exemplul 9.9
--------------

DECLARE
	B EXCEPTION;
BEGIN
	BEGIN
		DBMS_OUTPUT.PUT_LINE('test');
  END;
  DECLARE
		A EXCEPTION;
	BEGIN
    RAISE A; -- este generata exceptia A
  	EXCEPTION
    	WHEN A THEN
      		RAISE B; -- este generata exceptia B
    	WHEN B THEN 
    		DBMS_OUTPUT.PUT_LINE('EXCEPTIA B BLOC INTERIOR');
     		/* exceptia este propagata spre blocul exterior
      		cu toate ca exista aici un handler pentru ea */
  	END;
EXCEPTION
  	WHEN B THEN 
  		DBMS_OUTPUT.PUT_LINE('EXCEPTIA B BLOC EXTERIOR');
  	--exceptia B este tratata in blocul exterior
END;
/

BEGIN
	DECLARE
		B EXCEPTION;
	BEGIN
  		DECLARE
			A EXCEPTION;
		BEGIN
    		RAISE A; -- este generata exceptia A
  		EXCEPTION
    		WHEN A THEN
      			RAISE B; -- este generata exceptia B
    		WHEN B THEN 
    			DBMS_OUTPUT.PUT_LINE('EXCEPTIA B BLOC INTERIOR');
     			/* exceptia este propagata spre blocul exterior
      			cu toate ca exista aici un handler pentru ea */
  		END;
	EXCEPTION
  		WHEN B THEN DBMS_OUTPUT.PUT_LINE('EXCEPTIA B BLOC EXTERIOR');
  		--exceptia B este tratata in blocul exterior
	END;
	BEGIN
		DBMS_OUTPUT.PUT_LINE('test');
	END;
END;
/

<<bloc1>>
BEGIN
  <<bloc2>>
	DECLARE
		B EXCEPTION;
	BEGIN
      <<bloc3>>
  		DECLARE
			A EXCEPTION;
      BEGIN
    		RAISE A; -- este generata exceptia A
  		EXCEPTION
    		WHEN A THEN
      			RAISE B; -- este generata exceptia B
    		WHEN B THEN 
    			DBMS_OUTPUT.PUT_LINE('EXCEPTIA B BLOC INTERIOR');
     			/* exceptia este propagata spre blocul exterior
      			cu toate ca exista aici un handler pentru ea */
      END bloc3;
	EXCEPTION
  		WHEN B THEN DBMS_OUTPUT.PUT_LINE('EXCEPTIA B BLOC EXTERIOR');
  		--exceptia B este tratata in blocul exterior
	END bloc2;
  <<bloc4>>
	BEGIN
		DBMS_OUTPUT.PUT_LINE('test');
	END bloc4;
END bloc1;
/

-----------------------
