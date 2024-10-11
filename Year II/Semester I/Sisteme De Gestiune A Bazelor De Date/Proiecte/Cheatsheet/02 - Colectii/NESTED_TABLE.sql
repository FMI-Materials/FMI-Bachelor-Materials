/* local
TYPE nume IS TABLE OF tip;

-- este automat initializat cu NULL
-- nu poate avea elemente de tip REF CURSOR
*/

-- exemplu
DECLARE
    TYPE tablou_imbricat IS TABLE OF joc_video.nume%TYPE;
    v_jocuri tablou_imbricat := tablou_imbricat();
BEGIN
    SELECT nume
    BULK COLLECT INTO v_jocuri
    FROM joc_video;

    FOR i in 1..v_jocuri.COUNT LOOP
        DBMS_OUTPUT.PUT_LINE(v_jocuri(i));
    END LOOP;
END;

/* global
CREATE OR REPLACE TYPE tip AS TABLE OF tip;
*/

-- exemplu
CREATE OR REPLACE TYPE tablou_imbricat AS TABLE OF VARCHAR2(128);

-- poate fi folosit ca parametru de subprogram
CREATE OR REPLACE PROCEDURE test
(
    v_jocuri tablou_imbricat
)
IS
BEGIN
    FOR i in 1..v_jocuri.COUNT LOOP
        DBMS_OUTPUT.PUT_LINE(v_jocuri(i));
    END LOOP;
END;
/
BEGIN
    test(tablou_imbricat('joc1', 'joc2', 'joc3'));
END;

-- poate fi folosit ca RETURN de functie
CREATE OR REPLACE FUNCTION test
(
    v_cod_utilizator utilizator.cod_utilizator%TYPE DEFAULT 1
) RETURN tablou_imbricat 
IS
    v_jocuri tablou_imbricat := tablou_imbricat();
BEGIN
    SELECT nume
    BULK COLLECT INTO v_jocuri
    FROM joc_video;

    RETURN v_jocuri;
END;
/
DECLARE
    v_jocuri tablou_imbricat := test();
BEGIN
    FOR i in 1..v_jocuri.COUNT LOOP
        DBMS_OUTPUT.PUT_LINE(v_jocuri(i));
    END LOOP;
END;

-- poate fi folosit ca tip de coloana de tabel
CREATE TABLE exemplu
(
    jocuri tablou_imbricat
) NESTED TABLE jocuri STORE AS jocuri_tablou;
/
CREATE OR REPLACE PROCEDURE test
(
    v_cod_utilizator utilizator.cod_utilizator%TYPE DEFAULT 1
)
IS
    v_jocuri tablou_imbricat := tablou_imbricat();
BEGIN
    SELECT nume
    BULK COLLECT INTO v_jocuri
    FROM joc_video;

    INSERT INTO exemplu
    VALUES (v_jocuri);
END;
/
BEGIN
    test();
END;
/
SELECT t.*
FROM exemplu e, TABLE(e.jocuri) t;
