/*
nume EXCEPTION;
PRAGMA EXCEPTION_INIT(nume, cod_eroare);

cod_eroare = [-20001, -20002, -20003, ...]
*/

-- exemplu
DECLARE
    v_cod utilizator.cod_utilizator%TYPE := 15;
    v_nume utilizator.nume%TYPE;
    v_prenume utilizator.prenume%TYPE;
    v_count NUMBER;

    exception_no_user EXCEPTION;
    PRAGMA EXCEPTION_INIT(exception_no_user, -20001);
BEGIN
    SELECT COUNT(*)
    INTO v_count
    FROM utilizator
    WHERE cod_utilizator = v_cod;

    IF v_count = 0 THEN
        RAISE exception_no_user;
    END IF;

    SELECT nume, prenume 
    INTO v_nume, v_prenume
    FROM utilizator
    WHERE cod_utilizator = v_cod;
    DBMS_OUTPUT.PUT_LINE('Numele utilizatorului este: ' || v_nume || ' ' || v_prenume);
EXCEPTION
    WHEN exception_no_user THEN
        DBMS_OUTPUT.PUT_LINE('Nu exista utilizatorul cu codul ' || v_cod);
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('A aparut o eroare');
END;