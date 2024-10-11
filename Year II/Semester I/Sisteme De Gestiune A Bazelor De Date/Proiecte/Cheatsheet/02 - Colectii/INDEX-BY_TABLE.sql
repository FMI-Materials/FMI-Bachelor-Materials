/*
TYPE nume IS TABLE OF tip RETURN INDEX BY PLS_INTEGER/BINARY_INTEGER;

-- poate fi definit doar local
-- nu este initializat automat null
-- nu poate avea elemente de tip REF CURSOR
*/

-- exemplu
DECLARE
    TYPE tablou_indexat IS TABLE OF joc_video.nume%TYPE INDEX BY PLS_INTEGER;
    v_jocuri tablou_indexat;
BEGIN
    SELECT nume
    BULK COLLECT INTO v_jocuri
    FROM joc_video;

    FOR i IN v_jocuri.FIRST..v_jocuri.LAST LOOP
        DBMS_OUTPUT.PUT_LINE(v_jocuri(i));
    END LOOP;
END;