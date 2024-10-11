/* local
TYPE nume IS VARRAY(dimensiune) OF tip;

-- are dimensiune fixa
*/

-- exemplu
DECLARE
    TYPE vector IS VARRAY(13) OF joc_video.nume%TYPE;
    v_jocuri vector := vector();
BEGIN
    SELECT nume
    BULK COLLECT INTO v_jocuri
    FROM joc_video;

    FOR i IN 1..v_jocuri.COUNT LOOP
        DBMS_OUTPUT.PUT_LINE(v_jocuri(i));
    END LOOP;
END;

/* global
CREATE OR REPLACE TYPE nume IS VARRAY(dimensiune) OF tip;
*/

-- exemplu
CREATE OR REPLACE TYPE vector IS VARRAY(13) OF VARCHAR2(128);
/
DECLARE
    v_jocuri vector := vector();
BEGIN
    SELECT nume
    BULK COLLECT INTO v_jocuri
    FROM joc_video;

    FOR i IN v_jocuri.FIRST..v_jocuri.LAST LOOP
        DBMS_OUTPUT.PUT_LINE(v_jocuri(i));
    END LOOP;
END;

-- poate fi folosit ca parametru de subprogram
CREATE OR REPLACE PROCEDURE test
(
    v_jocuri vector
)
IS
BEGIN
    FOR i IN v_jocuri.FIRST..v_jocuri.LAST LOOP
        DBMS_OUTPUT.PUT_LINE(v_jocuri(i));
    END LOOP;
END;
/
BEGIN
    test(vector('joc1', 'joc2', 'joc3'));
END;

-- poate fi folosit ca RETURN de functie
CREATE OR REPLACE FUNCTION test
(
    v_cod_utilizator utilizator.cod_utilizator%TYPE DEFAULT 1
) RETURN vector 
IS
    v_jocuri vector := vector();
BEGIN
    SELECT nume
    BULK COLLECT INTO v_jocuri
    FROM joc_video;

    RETURN v_jocuri;
END;
/
DECLARE
    v_jocuri vector := test();
BEGIN
    FOR i IN v_jocuri.FIRST..v_jocuri.LAST LOOP
        DBMS_OUTPUT.PUT_LINE(v_jocuri(i));
    END LOOP;
END;

-- poate fi folosit ca tip de coloana de tabel
CREATE TABLE exemplu
(
    jocuri vector
);
/
INSERT INTO exemplu
VALUES(vector('joc1', 'joc2', 'joc3'));
/
SELECT * from exemplu;
