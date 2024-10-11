/*
DECLARE
    declaratii;
BEGIN
    instructiuni;
EXCEPTION
    WHEN ex1 THEN
        instructiuni;
    WHEN ex2 THEN
        instructiuni;
    ...
    WHEN OTHERS THEN
        instructiuni;
END;
*/

-- exemplu
DECLARE
    v_cod utilizator.cod_utilizator%TYPE := 15;
    v_nume utilizator.nume%TYPE;
    v_prenume utilizator.prenume%TYPE;
BEGIN
    SELECT nume, prenume 
    INTO v_nume, v_prenume
    FROM utilizator
    WHERE cod_utilizator = v_cod;
    DBMS_OUTPUT.PUT_LINE('Numele utilizatorului este: ' || v_nume || ' ' || v_prenume);
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('Nu exista utilizatorul cu codul ' || v_cod);
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('A aparut o eroare');
END;
