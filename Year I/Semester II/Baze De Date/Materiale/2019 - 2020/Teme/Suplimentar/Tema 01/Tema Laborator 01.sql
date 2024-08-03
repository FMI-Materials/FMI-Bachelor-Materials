--1
select cust_id, cust_name from customer_tbl where lower(cust_state) in ('in', 'oh', 'mi','il') or substr(lower(cust_name), 1, 1) in ('a', 'b') order by cust_name;
--2 a
select prod_id, prod_desc, cost from products_tbl where cost >= 1 and cost <= 12.50;
--2 b
select prod_id, prod_desc, cost from products_tbl where cost < 1 or cost > 12.50;
--3
select first_name|| '.' ||last_name||'@ittech.com' from employee_tbl;
--4
select first_name || ', ' || last_name as "NAME",
substr(emp_id, 1, 3) || '-' ||  substr(emp_id, 3, 2) || '-' || substr(emp_id, 5, 4) as "EMP_ID", 
'(' || substr(phone, 1, 3) || ')' ||  substr(phone, 3, 3) || '-' || substr(phone, 6, 4) as "PHONE"
from employee_tbl;
--5
select emp_id, date_hire from employee_pay_tbl;
--6
select e1.emp_id, e2.first_name, e2.last_name, e1.salary, e1.bonus from employee_pay_tbl e1 inner join employee_tbl e2 on (e1.emp_id = e2.emp_id);
--7
select c.cust_name, o.ord_num, o.ord_date from orders_tbl o inner join customer_tbl c on (c.cust_id = o.cust_id) where substr(lower(cust_state), 1, 1) = 'i';
--8
select o.ord_num, o.qty, e.last_name, e.first_name, e.city from orders_tbl o join employee_tbl e on (e.emp_id = o.sales_rep);
--9
select o.ord_num, o.qty, e.last_name, e.first_name, e.city from orders_tbl o full outer join employee_tbl e on (e.emp_id = o.sales_rep);
--10
select * from employee_tbl where middle_name is null;
--11
select nvl(salary, 0) + nvl(bonus, 0) as "SALARY" from employee_pay_tbl;
--12
--v1
select e.last_name, ep.salary, ep.position, 
case when lower(ep.position) = 'marketing' then (ep.salary * 1.1) 
when lower(ep.position) = 'salesman' then (ep.salary * 1.15)
else ep.salary end
as "Salariu modificat"
from employee_tbl e join employee_pay_tbl ep on (ep.emp_id = e.emp_id);

--v2
select e.last_name, ep.salary, ep.position, 
ep.salary * decode(lower(ep.position), 'marketing', 1.1, 'salesman', 1.15, 1) as "Salariu modificat"
from employee_tbl e, employee_pay_tbl ep where ep.emp_id = e.emp_id;

