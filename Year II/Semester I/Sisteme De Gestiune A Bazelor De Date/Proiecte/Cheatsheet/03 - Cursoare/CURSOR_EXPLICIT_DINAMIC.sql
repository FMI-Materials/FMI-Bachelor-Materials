/*
TYPE nume IS REF CURSOR RETURN tip;
variabila nume;
*/

-- exemplu
DECLARE
    TYPE cursor_dinamic IS REF CURSOR RETURN joc_video%ROWTYPE;
    v_cursor cursor_dinamic;
    v_joc joc_video%ROWTYPE;
BEGIN
    OPEN v_cursor FOR
        SELECT *
        FROM joc_video;

    LOOP
        FETCH v_cursor INTO v_joc;
        EXIT WHEN v_cursor%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE(v_joc.nume);
    END LOOP;

    CLOSE v_cursor;
END;

-- poate fi folosit ca parametru de subprogram
CREATE OR REPLACE PROCEDURE test
(
    v_cursor SYS_REFCURSOR
)
IS
    v_joc joc_video%ROWTYPE;
BEGIN
    LOOP
        FETCH v_cursor INTO v_joc;
        EXIT WHEN v_cursor%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE(v_joc.nume);
    END LOOP;

    CLOSE v_cursor;
END;
/
DECLARE
    TYPE cursor_dinamic IS REF CURSOR RETURN joc_video%ROWTYPE;
    v_cursor cursor_dinamic;
BEGIN
    OPEN v_cursor FOR
        SELECT *
        FROM joc_video;

    test(v_cursor);
END;

-- poate fi folosit ca RETURN de functie
CREATE OR REPLACE FUNCTION test
(
    v_cod_utilizator utilizator.cod_utilizator%TYPE DEFAULT 1
) RETURN SYS_REFCURSOR
IS
    v_cursor SYS_REFCURSOR;
BEGIN
    OPEN v_cursor FOR
        SELECT *
        FROM joc_video;

    RETURN v_cursor;
END;
/
DECLARE
    v_cursor SYS_REFCURSOR := test();
    v_joc joc_video%ROWTYPE;
BEGIN
    LOOP
        FETCH v_cursor INTO v_joc;
        EXIT WHEN v_cursor%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE(v_joc.nume);
    END LOOP;

    CLOSE v_cursor;
END;

