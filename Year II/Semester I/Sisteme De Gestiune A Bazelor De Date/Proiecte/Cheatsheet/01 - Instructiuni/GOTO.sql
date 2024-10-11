/*
GOTO eticheta;
<<eticheta>>
*/

-- exemplu
DECLARE
    v_number NUMBER := 0;
BEGIN <<alpha>>
    LOOP
        v_number := v_number + 1;
        IF v_number > 10 THEN
            GOTO finish;
        END IF;
        DBMS_OUTPUT.PUT_LINE(v_number);
    END LOOP;
    <<finish>>
    NULL;
END <<alpha>>;