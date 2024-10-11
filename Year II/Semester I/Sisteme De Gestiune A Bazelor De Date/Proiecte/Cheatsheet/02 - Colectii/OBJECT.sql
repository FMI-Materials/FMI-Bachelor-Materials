/*
CREATE OR REPlACE TYPE nume AS OBJECT
(
    camp1 tip1,
    camp2 tip2,
    ...
);

-- Poate fi definit doar global
-- Nu poate avea camp de tip REF CURSOR
*/

-- exemplu
CREATE OR REPLACE TYPE pair AS OBJECT
(
    nume VARCHAR2(128),
    prenume VARCHAR2(128)
);

-- poate fi folosit ca parametru de subprogram
CREATE OR REPLACE PROCEDURE test
(
    v_pair pair
)
IS
BEGIN
    DBMS_OUTPUT.PUT_LINE(v_pair.nume || ' ' || v_pair.prenume);
END;
/
BEGIN
    test(pair('nume', 'prenume'));
END;

-- poate fi folosit ca RETURN de functie
CREATE OR REPLACE FUNCTION test
(
    v_cod_utilizator utilizator.cod_utilizator%TYPE DEFAULT 1
) RETURN pair 
IS
    v_pair pair := pair(NULL, NULL);
BEGIN
    SELECT pair(nume, prenume)
    INTO v_pair
    FROM utilizator
    WHERE cod_utilizator = v_cod_utilizator;

    RETURN v_pair;
END;
/
DECLARE
    v_pair pair := test();
BEGIN
    DBMS_OUTPUT.PUT_LINE(v_pair.nume || ' ' || v_pair.prenume);
END;
