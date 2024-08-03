--enrollment
--course_section
--term
--course
--student
--faculty
--location

select * from enrollment;
select * from course_section;
select * from term;
select * from course;
select * from student;
select * from faculty;
select * from location;
--1
select s.s_last from student s where '(null)' not in (select grade from enrollment where s_id = s.s_id);

--2
select bldg_code from location 
where bldg_code not in 
(select bldg_code from location where loc_id not in (select distinct loc_id from course_section));

--3
select f.f_id, f.f_last from faculty f
where (select count(1) from student s where s.f_id = f.f_id and (select count(1) from enrollment where grade = 'A' and s_id = s.s_id)>0) > 0
and (select count(1) from course_section where f_id = f.f_id  and course_no = 'MIS 441') > 0;

--4
(select nume from (select f.f_last as nume from faculty f order by 
(select max((select count(s_id) from enrollment where c_sec_id = cs.c_sec_id)) from course_section cs where cs.f_id = f.f_id)) where rownum =1)
union
(select nume from (select f.f_last as nume from faculty f order by
(select max((select capacity from location where loc_id = cs.loc_id)) from course_section cs where cs.f_id = f.f_id)) where rownum = 1);

--5
select f.f_last as nume from faculty f where 
f.loc_id in (select loc_id from location where capacity = (select min(capacity) from location))
and f.f_id in (select f_id from course_section where max_enrl in 
(select min(max_enrl) from course_section where loc_id = (select loc_id from location where capacity = (select max(capacity) from location))));

--6
select round(avg(loc.capacity),2) as "Capacitatea salilor", round(avg(enrl.max_enrl),2) as "Numarul de locuri" from 
(select distinct l.loc_id, l.capacity from faculty f join course_section cs on (f.f_id=cs.f_id) join location l on (l.loc_id=cs.loc_id) where f.f_last = 'Marx') loc,
(select cs.max_enrl from student s join enrollment e on (s.s_id = e.s_id) join course_section cs on (e.c_sec_id=cs.c_sec_id) where s.s_last='Jones') enrl;

--7
select bldg_code as "Codul cladirii", round(avg(capacity), 2) as "Media capacitatilor" from location
where bldg_code in (select distinct l.bldg_code from course_section cs join course c using (course_no) join location l on (cs.loc_id=l.loc_id) where c.course_name like '%Systems%')
group by bldg_code;

--8 - care e problema 21 ?????
select bldg_code as "Codul cladirii", round(avg(capacity), 2) as "Media capacitatilor" from location
where bldg_code in (select distinct l.bldg_code from course_section cs join course c using (course_no) join location l on (cs.loc_id=l.loc_id) where c.course_name like '%Systems%')
group by bldg_code;

--9
select course_no, course_name from course where
(select count(*) from course where course_name like '%Java%')=0 or course_name like '%Java%'; 

--10
select c.course_name from course c where
decode((select count(1) from course_section cs join location l using(loc_id) where l.capacity=42 and cs.course_no = c.course_no), 0,0,1) +
decode((select count(1) from faculty f join course_section cs on (cs.f_id=f.f_id) join course c1 on (cs.course_no=c1.course_no) where f.f_last = 'Brown' and c1.course_no=c.course_no), 0, 0, 1) +
decode((select count(1) from student s join enrollment e on (e.s_id=s.s_id) join course_section cs on (cs.c_sec_id=e.c_sec_id) where s.s_last='Jones' and s.s_first='Tammy' and cs.course_no = c.course_no), 0,0,1) +
decode((select count(1) from course c1 where c1.course_name like '%Database%' and c1.course_no = c.course_no), 0,0,1) +
decode((select count(1) from course_section cs join term using (term_id) where extract(year from start_date) > 2007 and cs.course_no = c.course_no), 0,0,1) >= 3;

--11
select t.term_desc as "Denumire semestru", count(c.course_no) as "Numar de cursuri" from course_section cs join course c on (cs.course_no=c.course_no) join term t on (t.term_id=cs.term_id)
where c.course_name like '%Database%' group by t.term_desc;

--12




