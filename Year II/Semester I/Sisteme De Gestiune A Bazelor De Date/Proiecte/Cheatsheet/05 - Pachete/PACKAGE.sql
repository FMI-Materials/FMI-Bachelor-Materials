/*
CREATE OR REPLACE PACKAGE nume AS
    -- declarare variabile
    -- declarare subprograme
END nume;

CREATE OR REPLACE PACKAGE BODY nume AS
    -- definire subprograme
END nume;
*/

-- exemplu
CREATE OR REPLACE PACKAGE test AS
    TYPE nume_complet IS RECORD
    (
        nume utilizator.nume%TYPE,
        prenume utilizator.prenume%TYPE
    );
    PROCEDURE afisare_nume(v_cod_utilizator utilizator.cod_utilizator%TYPE);
    FUNCTION afisare_nume_complet(v_cod_utilizator utilizator.cod_utilizator%TYPE) RETURN nume_complet;
END test;
/
CREATE OR REPLACE PACKAGE BODY test AS
    PROCEDURE afisare_nume(v_cod_utilizator utilizator.cod_utilizator%TYPE) IS
        v_nume utilizator.nume%TYPE;
        v_prenume utilizator.prenume%TYPE;
    BEGIN
        SELECT nume, prenume 
        INTO v_nume, v_prenume
        FROM utilizator
        WHERE cod_utilizator = v_cod_utilizator;
        DBMS_OUTPUT.PUT_LINE('Numele utilizatorului este: ' || v_nume || ' ' || v_prenume);
    END afisare_nume;

    FUNCTION afisare_nume_complet(v_cod_utilizator utilizator.cod_utilizator%TYPE) RETURN nume_complet IS
        v_nume_complet nume_complet;
    BEGIN
        SELECT nume, prenume INTO v_nume_complet
        FROM utilizator
        WHERE cod_utilizator = v_cod_utilizator;
        RETURN v_nume_complet;
    END afisare_nume_complet;
END test;
/
BEGIN
    test.afisare_nume(1);
    DBMS_OUTPUT.PUT_LINE('Numele utilizatorului este: ' || test.afisare_nume_complet(1).nume || ' ' || test.afisare_nume_complet(1).prenume);
END;