/*
CREATE OR REPLACE FUNCTION nume
(
    param1 tip1,
    param2 tip2,
    ...
) RETURN tip
IS
    declaratii;
BEGIN
    instructiuni;
END;
*/

-- exemplu
CREATE OR REPLACE FUNCTION test
(
    v_cod_utilizator utilizator.cod_utilizator%TYPE DEFAULT 1
) RETURN VARCHAR2
IS
    v_nume utilizator.nume%TYPE;
    v_prenume utilizator.prenume%TYPE;
BEGIN
    SELECT nume, prenume
    INTO v_nume, v_prenume
    FROM utilizator
    WHERE cod_utilizator = v_cod_utilizator;

    RETURN v_nume || ' ' || v_prenume;
END;
/
BEGIN
    DBMS_OUTPUT.PUT_LINE(test(1));
END;

-- functie cu parametru de tip OUT
CREATE OR REPLACE FUNCTION test
(
    v_cod_utilizator IN utilizator.cod_utilizator%TYPE,
    v_nume OUT utilizator.nume%TYPE,
    v_prenume OUT utilizator.prenume%TYPE
) RETURN VARCHAR2
IS
BEGIN
    SELECT nume, prenume
    INTO v_nume, v_prenume
    FROM utilizator
    WHERE cod_utilizator = v_cod_utilizator;

    RETURN v_nume || ' ' || v_prenume;
END;
/
DECLARE
    v_nume utilizator.nume%TYPE;
    v_prenume utilizator.prenume%TYPE;
BEGIN
    DBMS_OUTPUT.PUT_LINE(test(1, v_nume, v_prenume));
    DBMS_OUTPUT.PUT_LINE(v_nume || ' ' || v_prenume);
END;
