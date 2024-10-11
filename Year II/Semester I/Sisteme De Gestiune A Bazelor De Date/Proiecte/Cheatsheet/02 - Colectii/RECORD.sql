/*
TYPE nume IS RECORD
(
    camp1 tip1,
    camp2 tip2,
    ...
);

-- Poate fi definit doar local
-- Nu poate avea camp de tip REF CURSOR
*/

-- exemplu
DECLARE
    TYPE pair IS RECORD
    (
        nume utilizator.nume%TYPE,
        prenume utilizator.prenume%TYPE
    );
    v_pair pair;
BEGIN
    SELECT nume, prenume
    INTO v_pair
    FROM utilizator
    WHERE cod_utilizator = 1;
    DBMS_OUTPUT.PUT_LINE(v_pair.nume || ' ' || v_pair.prenume);
END;