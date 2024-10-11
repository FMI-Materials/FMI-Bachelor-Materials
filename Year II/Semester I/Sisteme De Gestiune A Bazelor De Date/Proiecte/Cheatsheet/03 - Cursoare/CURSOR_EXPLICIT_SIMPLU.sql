/*
CURSOR nume IS SELECT ... FROM tabel ...
variabila tabel%ROWTYPE

OPEN nume;
LOOP
    FETCH INTO variabila
    EXIT WHEN nume%NOTFOUND;
    ...
END LOOP;
CLOSE nume;
*/

-- exemplu
DECLARE
    CURSOR c_jocuri IS SELECT * FROM joc_video;
    v_joc joc_video%ROWTYPE;
BEGIN
    OPEN c_jocuri;
    LOOP
        FETCH c_jocuri INTO v_joc;
        EXIT WHEN c_jocuri%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE(v_joc.nume);
    END LOOP;
    CLOSE c_jocuri;
END;
