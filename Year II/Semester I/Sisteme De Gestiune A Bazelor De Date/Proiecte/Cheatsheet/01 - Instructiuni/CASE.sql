/* Varianta 1
CASE selector
    WHEN value1 THEN result1;
    WHEN value2 THEN result2;
    ...
    [ELSE result;]
END CASE;
*/

-- exemplu
DECLARE
    v_number NUMBER := 1;
BEGIN
    CASE v_number
        WHEN 1 THEN
            DBMS_OUTPUT.PUT_LINE('Unu');
        WHEN 2 THEN
            DBMS_OUTPUT.PUT_LINE('Doi');
        ELSE
            DBMS_OUTPUT.PUT_LINE('Alt numar');
    END CASE;
END;

/* Varianta 2
CASE
    WHEN selector = value1 THEN result1;
    WHEN selector = value2 THEN result2;
    ...
    [ELSE result;]
END CASE;
*/

-- exemplu
DECLARE
    v_number NUMBER := 1;
BEGIN
    CASE 
        WHEN v_number > 0 THEN
            DBMS_OUTPUT.PUT_LINE('Pozitiv');
        WHEN v_number < 0 THEN
            DBMS_OUTPUT.PUT_LINE('Negativ');
        ELSE
            DBMS_OUTPUT.PUT_LINE('Zero');
    END CASE;
END;