SET SERVEROUTPUT ON;
-- 1
CREATE TABLE info_bhd(
    ID          NUMBER(10, 2) PRIMARY KEY,
    utilizator  VARCHAR2(50),
    data        DATE,
    comanda     VARCHAR2(100),
    nr_linii    NUMBER,
    eroare      VARCHAR2(50));
/
-- 3
SET SERVEROUTPUT ON;
CREATE OR REPLACE FUNCTION find_employees_bhd (
    oras locations.city%TYPE
) RETURN NUMBER IS
    v_raspuns         NUMBER;
    v_error         VARCHAR2(100);
    v_utilizator  info_ari.utilizator%TYPE;
BEGIN
    SELECT user INTO v_utilizator FROM dual;

    IF oras IS NULL THEN
        INSERT INTO info_bhd VALUES (
            (
                SELECT
                    nvl(MAX(id), 0) + 1
                FROM
                    info_bhd
            ),
            v_utilizator,
            sysdate,
            NULL,
            0,
            'Oras null'
        );

        RETURN 0;
    END IF;

    SELECT COUNT(*)
    INTO v_raspuns
    FROM employees e
    JOIN departments d ON (e.department_id = d.department_id)
    JOIN locations l ON (l.location_id = d.location_id)
    WHERE
        (SELECT COUNT(*) FROM job_history WHERE employee_id = e.employee_id ) >= 1;
    IF v_raspuns = 0 THEN
        v_error := 'Niciun angajat gasit';
    END IF;
    INSERT INTO info_bhd VALUES (
        (
            SELECT
                nvl(MAX(id), 0) + 1
            FROM
                info_bhd
        ),
        v_utilizator,
        sysdate,
        NULL,
        0,
        v_error
    );

    RETURN v_raspuns;
END;