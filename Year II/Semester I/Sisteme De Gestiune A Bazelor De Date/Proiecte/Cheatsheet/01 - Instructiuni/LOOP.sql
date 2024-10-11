/*
LOOP
    instructiuni;
    EXIT [WHEN expresie];
END LOOP;
*/

-- exemplu
DECLARE
    v_number NUMBER := 0;
BEGIN
    LOOP
        v_number := v_number + 1;
        EXIT WHEN v_number > 10;
        DBMS_OUTPUT.PUT_LINE(v_number);
    END LOOP;
END;