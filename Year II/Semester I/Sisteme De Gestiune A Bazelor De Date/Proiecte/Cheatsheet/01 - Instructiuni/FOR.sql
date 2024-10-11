/*
FOR contor IN [REVERSE] limita_inferioara..limita_superioara LOOP
    instructiuni;
END LOOP;
*/

-- exemplu
DECLARE
    v_number NUMBER;
BEGIN
    FOR v_number IN REVERSE 1..10 LOOP
        DBMS_OUTPUT.PUT_LINE(v_number);
    END LOOP;
END;