https://sqlmaria.com/2017/08/08/using-dbms_xplan-display_cursor-to-examine-execution-plans/
https://docs.oracle.com/database/121/ARPLS/d_xplan.htm#ARPLS70136
https://www.oracle.com/technetwork/database/manageability/owp-sql-monitoring-128746.pdf

CREATE TABLE index_test ( 
    id INT,
    name VARCHAR(20) NOT NULL, 
    phone_number VARCHAR(20) 
);

CREATE TABLE index_test2 ( 
    id INT,
    name VARCHAR(20) NOT NULL, 
    phone_number VARCHAR(20) 
);

SELECT *
FROM USER_TABLES
WHERE lower(table_name) = 'index_test';

SELECT *
FROM USER_OBJECTS;

SELECT *
FROM USER_SOURCE;

CREATE OR REPLACE FUNCTION random_string
RETURN VARCHAR
IS
Random15CharacterString VARCHAR(15);
BEGIN
Random15CharacterString := 
   CHR(DBMS_RANDOM.VALUE()*25+97)||
   CHR(DBMS_RANDOM.VALUE()*25+97)||
   CHR(DBMS_RANDOM.VALUE()*25+97)||
   CHR(DBMS_RANDOM.VALUE()*25+97)||
   CHR(DBMS_RANDOM.VALUE()*25+97)||
   CHR(DBMS_RANDOM.VALUE()*25+97)||
   CHR(DBMS_RANDOM.VALUE()*25+97)||
   CHR(DBMS_RANDOM.VALUE()*25+97)||
   CHR(DBMS_RANDOM.VALUE()*25+97)||
   CHR(DBMS_RANDOM.VALUE()*25+97)||
   CHR(DBMS_RANDOM.VALUE()*25+97)||
   CHR(DBMS_RANDOM.VALUE()*25+97)||
   CHR(DBMS_RANDOM.VALUE()*25+97)||
   CHR(DBMS_RANDOM.VALUE()*25+97)||
   CHR(DBMS_RANDOM.VALUE()*25+97);
RETURN Random15CharacterString;
END;
/

SELECT CHR(DBMS_RANDOM.VALUE()*25+97)
FROM dual;

CREATE OR REPLACE PROCEDURE insert_test_function
IS 
    i integer := 1;
BEGIN
  WHILE i <= 100000 LOOP
        INSERT INTO index_test (id, name, phone_number ) 
        VALUES (i, random_string, LPAD(FLOOR(DBMS_RANDOM.VALUE() * 10000000000), 10, '0')) ;
        i := i + 1;
    END LOOP;
    COMMIT;
END;
/

SELECT LPAD(FLOOR(DBMS_RANDOM.VALUE() * 10000000000), 10, '0')
FROM DUAL;

EXECUTE insert_test_function()
/

SELECT * FROM index_test;

INSERT INTO index_test2
SELECT * FROM index_test;

SELECT * FROM index_test2;

DELETE FROM index_test2 where id=100001;

SELECT COUNT(*) 
FROM index_test2;

SELECT MAX(id) 
FROM index_test;

ALTER TABLE index_test 
ADD PRIMARY KEY(id);

SELECT num_rows         --NULL
FROM all_tables
WHERE lower(table_name) = 'index_test'; 

SELECT *
FROM index_test;

SELECT *
FROM index_test2;

SELECT * 
FROM index_test 
WHERE phone_number = '4717442113'; --tb modificata valoarea pt fiecare reexecutie a scriptului!

SELECT * 
FROM index_test2 
WHERE phone_number = '4717442113';

--VAR 1
EXPLAIN PLAN FOR 
    SELECT * 
    FROM index_test 
    WHERE phone_number = '4717442113';

SELECT plan_table_output 
FROM TABLE(DBMS_XPLAN.display('plan_table',NULL,'all'));

--VAR 2
EXPLAIN PLAN
SET STATEMENT_ID = 'info_index_test'
FOR SELECT * 
    FROM index_test 
    WHERE phone_number = '4717442113';
    
SELECT LPAD(' ',2*(LEVEL-1))||OPERATION operation, OPTIONS, OBJECT_NAME, POSITION, COST
FROM PLAN_TABLE
START WITH ID = 0 AND STATEMENT_ID = 'info_index_test'
CONNECT BY PRIOR ID = PARENT_ID AND STATEMENT_ID = 'info_index_test';

--VAR 3 se obtine cu tasta F10

INSERT INTO index_test (id, name, phone_number ) 
    VALUES (100002, random_string(), LPAD(FLOOR(DBMS_RANDOM.VALUE() * 10000000000), 10, '0'));

DELETE FROM index_test2;

INSERT INTO index_test2
SELECT * FROM index_test;

SELECT * FROM index_test WHERE phone_number = '4717442113';

CREATE INDEX idx1 ON index_test2 (phone_number);

EXPLAIN PLAN FOR 
    SELECT * 
    FROM index_test2 
    WHERE phone_number = '4717442113';

SELECT plan_table_output 
FROM TABLE(DBMS_XPLAN.display('plan_table',NULL,'all'));

EXPLAIN PLAN FOR 
    SELECT * 
    FROM index_test 
    WHERE phone_number = '4717442113';

SELECT plan_table_output 
FROM TABLE(DBMS_XPLAN.display('plan_table',NULL,'all'));
    
DELETE FROM index_test
WHERE id = 100002;

EXPLAIN PLAN FOR
    SELECT employee_id, last_name, salary, department_name, city
    FROM employees
    JOIN departments USING(department_id)
    JOIN locations USING(location_id)
    WHERE lower(city) LIKE 'oxford';
    
SELECT plan_table_output 
FROM TABLE(DBMS_XPLAN.display('plan_table',NULL,'all'));

CREATE TABLE dept_spr AS SELECT * FROM departments;
CREATE TABLE emp_spr AS SELECT * FROM employees;
CREATE TABLE loc_spr AS SELECT * FROM locations;

SELECT *
FROM USER_CONSTRAINTS
ORDER BY 4;
--WHERE UPPER(TABLE_NAME) LIKE '%_SPR';

SELECT *
FROM USER_INDEXES
ORDER BY 4;
--WHERE UPPER(TABLE_NAME) LIKE '%_SPR';

EXPLAIN PLAN FOR
    SELECT employee_id, last_name, salary, department_name, city
    FROM emp_spr
    JOIN dept_spr USING(department_id)
    JOIN loc_spr USING(location_id)
    WHERE lower(city) LIKE 'oxford';
    
SELECT plan_table_output 
FROM TABLE(DBMS_XPLAN.display('plan_table',NULL,'all'));

CREATE TABLE index_test3 ( 
    dep_id INT,
    dep_name VARCHAR(20) NOT NULL, 
    man_id INT
);

ALTER TABLE index_test3 
ADD FOREIGN KEY (man_id) REFERENCES index_test(id);

CREATE OR REPLACE PROCEDURE insert_test_function2
IS 
    i integer := 1;
BEGIN
  WHILE i <= 100000 LOOP
        INSERT INTO index_test3 (dep_id, dep_name, man_id ) 
        VALUES (i, random_string, i) ;
        i := i + 1;
    END LOOP;
    COMMIT;
END;
/

EXECUTE insert_test_function2()
/

EXPLAIN PLAN FOR
    SELECT *
    FROM index_test2
    JOIN index_test3 ON(dep_id = id)
    WHERE phone_number = '4717442113';
    
SELECT plan_table_output 
FROM TABLE(DBMS_XPLAN.display('plan_table',NULL,'all'));

CREATE TABLE index_test4
AS SELECT * FROM index_test3;

EXPLAIN PLAN FOR
    SELECT *
    FROM index_test
    JOIN index_test4 ON(dep_id = id)
    WHERE phone_number = '4717442113';
    
SELECT plan_table_output 
FROM TABLE(DBMS_XPLAN.display('plan_table',NULL,'all'));

DROP TABLE index_test4;
DROP TABLE index_test3;
DROP TABLE index_test2;
DROP TABLE index_test;

DROP TABLE emp_spr;
DROP TABLE loc_spr;
DROP TABLE dept_spr;

DROP PROCEDURE insert_test_function;
DROP PROCEDURE insert_test_function2;
DROP FUNCTION random_string;