drop table works_on;
drop table project;

create table PROJECT(
	project_id number(4) primary key, 
	project_name varchar2(30), 
	budget number(6), 
	start_date date, 
	deadline date,
	delivery_date date,
	project_manager number(4) references employees(employee_id)); 

create table WORKS_ON(
	project_id number(4) references project(project_id),
	employee_id number(6) references employees(employee_id),
	start_date date, 
	end_date date,
	primary key(project_id, employee_id));
	
insert into project values (1, 'ALFA', 20000, '2-JAN-2006', '30-MAR-2006', '7-APR-2006', 102);
insert into project values (2, 'BETA', 10000, '5-MAY-2006', '15-JUL-2006', '15-JUL-2006', 103); 
insert into project values (3, 'GAMA', 10000, '11-DEC-2006', '15-JAN-2007', '17-JAN-2007', 102); 

insert into works_on values(1, 125, '1-FEB-2006', '7-APR-2006');
insert into works_on values(1, 136, '2-JAN-2006', '30-MAR-2006');
insert into works_on values(1, 140, '15-FEB-2006', '7-APR-2006');
insert into works_on values(2, 145, '6-MAY-2006', '15-JUL-2006');
insert into works_on values(2, 125, '6-MAY-2006', '15-JUL-2006');
insert into works_on values(2, 101, '6-MAY-2006', '15-JUL-2006');
insert into works_on values(2, 148, '14-MAY-2006', '10-JUL-2006');
insert into works_on values(2, 200, '6-MAY-2006', '15-JUL-2006');
insert into works_on values(3, 145, '15-DEC-2007', '15-JAN-2007');
insert into works_on values(3, 148, '14-DEC-2006', '17-JAN-2007');
insert into works_on values(3, 150, '14-DEC-2006', '17-JAN-2007');
insert into works_on values(3, 162, '20-DEC-2006', '17-JAN-2007');
insert into works_on values(3, 101, '20-DEC-2006', '17-JAN-2007');
insert into works_on values(3, 176, '20-DEC-2006', '17-JAN-2007');
insert into works_on values(3, 200, '20-DEC-2006', '17-JAN-2007');
insert into works_on values(3, 140, '15-DEC-2006', '7-JAN-2007');

commit;