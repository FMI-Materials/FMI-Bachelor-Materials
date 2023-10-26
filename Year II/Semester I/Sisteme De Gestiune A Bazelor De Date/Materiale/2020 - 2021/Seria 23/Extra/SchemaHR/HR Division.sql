create table work (employee_id number(6), start_work date, end_work date, project_id number(6) );

create table projects (project_id number(6), start_date date, end_date date,project_name varchar2(10) );

insert into projects values (1, to_date( '01-03-1998','dd-mm-yyyy') , to_date( '01-09-1998','dd-mm-yyyy'), 'P1');
insert into projects values (2, to_date( '10-02-1999','dd-mm-yyyy') , to_date( '10-05-1999','dd-mm-yyyy'), 'P2');
insert into projects values (3, to_date( '20-02-1999','dd-mm-yyyy') , to_date( '20-06-1999','dd-mm-yyyy'), 'P3');


insert into work values (201, to_date( '01-03-1998','dd-mm-yyyy') , to_date( '01-04-1998','dd-mm-yyyy'), 1);
insert into work values (202, to_date( '01-04-1998','dd-mm-yyyy') , to_date( '01-09-1998','dd-mm-yyyy'), 1);
insert into work values (114, to_date( '14-05-1998','dd-mm-yyyy') , to_date( '14-08-1998','dd-mm-yyyy'), 1);
insert into work values (201, to_date( '10-02-1999','dd-mm-yyyy') , to_date( '10-05-1999','dd-mm-yyyy'), 2);
insert into work values (202, to_date( '10-02-1999','dd-mm-yyyy') , to_date( '10-03-1999','dd-mm-yyyy'), 2);
insert into work values (112, to_date( '10-03-1999','dd-mm-yyyy') , to_date( '10-05-1999','dd-mm-yyyy'), 2);
insert into work values (201, to_date( '01-03-1999','dd-mm-yyyy') , to_date( '10-05-1999','dd-mm-yyyy'), 3);
insert into work values (112, to_date( '20-02-1999','dd-mm-yyyy') , to_date( '20-06-1999','dd-mm-yyyy'), 3);

insert into work values (206, to_date( '10-03-1999','dd-mm-yyyy') , to_date( '10-05-1999','dd-mm-yyyy'), 2);
insert into work values (206, to_date( '01-03-1999','dd-mm-yyyy') , to_date( '10-05-1999','dd-mm-yyyy'), 3);

insert into work values (205, to_date( '14-05-1998','dd-mm-yyyy') , to_date( '14-08-1998','dd-mm-yyyy'), 1);
insert into work values (205, to_date( '10-02-1999','dd-mm-yyyy') , to_date( '10-05-1999','dd-mm-yyyy'), 2);
commit;