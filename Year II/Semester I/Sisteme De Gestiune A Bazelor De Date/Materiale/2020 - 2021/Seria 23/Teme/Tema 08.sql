SET SERVEROUTPUT ON;
-- 1 a
CREATE OR REPLACE PACKAGE pachet1_bhd AS
    function min_salary(cod_departament employees.department_id%TYPE) return number;
    function get_manager_id(nume employees.first_name%TYPE, prenume employees.last_name%TYPE) return number;
    function get_department_id(nume departments.department_name%TYPE) return number;
    function get_job_id(nume jobs.job_title%TYPE) return number;
    PROCEDURE adauga_angajat(nume employees.first_name%TYPE, prenume employees.last_name%TYPE, telefon employees.phone_number%TYPE, email employees.email%TYPE);
END pachet1_bhd;
/
CREATE OR REPLACE PACKAGE BODY pachet1_bhd IS
    --
    function min_salary(cod_departament employees.department_id%TYPE)
        return number is 
        minim number;
    begin
        select min(salary) into minim from employees where department_id = cod_departament;
        return minim;
    end min_salary;
    --
    function get_manager_id(nume employees.first_name%TYPE, prenume employees.last_name%TYPE)
        return number is
        cod_manager number;
    begin
        select employee_id into cod_manager from employees where first_name = nume and last_name = prenume;
        return cod_manager;
    end get_manager_id;
    --
    function get_department_id(nume departments.department_name%TYPE) 
        return number is
        cod_departament number;
    begin
        return cod_departament;
    end get_department_id;
    --
    function get_job_id(nume jobs.job_title%TYPE) 
        return number is
        cod_job number;
    begin
        return cod_job;
    end get_job_id;
    --
    PROCEDURE adauga_angajat(nume employees.first_name%TYPE, prenume employees.last_name%TYPE, telefon employees.phone_number%TYPE, email employees.email%TYPE)
    IS
        data_angajare employees.hire_date%TYPE;
        salariu employees.salary%TYPE;
        cod_manager employees.employee_id%TYPE; 
        cod_departament employees.department_id%TYPE;
        cod_job jobs.job_title%TYPE;
    BEGIN
        cod_departament := get_department_id('Executive');
        salariu := min_salary(cod_departament);
        cod_manager := get_manager_id('Steven', 'King');
        cod_job := get_job_id('President');
        select CURRENT_DATE into data_angajare from dual;
        insert into employees 
        (first_name, last_name, email, phone_number, hire_date, job_id, salary, commission_pct, manager_id, department_id)
        values (nume, prenume, email, telefon, data_angajare,cod_job,salariu, 0,cod_manager,cod_departament);
    END adauga_angajat;
END pachet1_bhd;