/*
CURSOR nume (parametru1, [parametru2, ...]) IS SELECT ... FROM tabel ...
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
    CURSOR c_jocuri (p_initiala VARCHAR2) IS SELECT * FROM joc_video WHERE nume LIKE p_initiala || '%';
    v_joc joc_video%ROWTYPE;
BEGIN
    OPEN c_jocuri('A');
    LOOP
        FETCH c_jocuri INTO v_joc;
        EXIT WHEN c_jocuri%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE(v_joc.nume);
    END LOOP;
    CLOSE c_jocuri;
END;

-- ciclu cursor
DECLARE
    CURSOR c_jocuri (p_initiala VARCHAR2) IS SELECT * FROM joc_video WHERE nume LIKE p_initiala || '%';
    v_joc joc_video%ROWTYPE;
BEGIN
    FOR v_joc IN c_jocuri('A') LOOP
        DBMS_OUTPUT.PUT_LINE(v_joc.nume);
    END LOOP;
END;