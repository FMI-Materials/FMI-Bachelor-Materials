select last_name || ' ' || first_name || ' castiga ' || salary || ' lunar dar doreste ' || salary*3 as "Salariu ideal" from employees;

select initcap(last_name), upper(first_name), length(first_name) from employees where substr(lower(first_name), 1, 1) = 'j' or substr(lower(first_name), 1, 1) = 'm' or substr(lower(first_name), 3, 1) = 'a' order by length(first_name);

select employee_id, first_name, department_name from employees inner join departments on departments.department_id = employees.department_id where ltrim(rtrim(lower(first_name))) = 'steven' ;

select employee_id, first_name, length(first_name), INSTR(lower(first_name), 'a') from employees where substr(lower(first_name), -1, 1) = 'e';

SELECT *
FROM employees
WHERE TO_CHAR(hire_date,'D') = TO_CHAR(sysdate,’D’);

select employee_id, first_name, salary, round(salary*1.15,2) as "Salariu nou", round((salary*1.15)/100, 2) as "Numar sute" from employees where mod(salary, 1000) != 0;

select first_name as "Nume angajat", RPAD(hire_date, 20) as "Data angajarii" from employees where commission_pct is not  NULL;

select TO_CHAR(sysdate+30, 'mm-dd-yy hh:mi:ss') from dual;

select to_date(concat('01-JAN-', (extract(YEAR from sysdate-1)+1)))-sysdate from dual;

select TO_CHAR(sysdate+(1/2), 'mm-dd-yy hh:mi:ss') from dual;
select TO_CHAR(sysdate+(1/1440)*5, 'mm-dd-yy hh:mi:ss') from dual;

select first_name || ' ' ||last_name, hire_date, NEXT_DAY(ADD_MONTHS(hire_date, 6), 'Monday') as "Negociere" from employees;

select first_name, round(months_between(sysdate, hire_date)) as "Luni lucrate" from employees order by months_between(sysdate, hire_date);
