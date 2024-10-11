/*
WHILE condiţie LOOP
    instructiuni;
END LOOP;
*/

-- exemplu
DECLARE
    v_number NUMBER := 0;
BEGIN
    WHILE v_number < 10 LOOP
        v_number := v_number + 1;
        DBMS_OUTPUT.PUT_LINE(v_number);
    END LOOP;
END;