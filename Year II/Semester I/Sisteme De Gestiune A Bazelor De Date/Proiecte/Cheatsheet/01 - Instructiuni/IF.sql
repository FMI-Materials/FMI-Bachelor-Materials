/*
IF expresie THEN
    instructiuni;
[ELSIF expresie THEN
    instructiuni;]
ELSE
    instructiuni;
END IF;
*/

-- exemplu
DECLARE
    v_number NUMBER;
BEGIN
    v_number := 1;
    IF v_number > 0 THEN
        DBMS_OUTPUT.PUT_LINE('Pozitiv');
    ELSIF v_number < 0 THEN
        DBMS_OUTPUT.PUT_LINE('Negativ');
    ELSE
        DBMS_OUTPUT.PUT_LINE('Zero');
    END IF;
END;