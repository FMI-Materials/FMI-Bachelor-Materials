--4
SELECT * FROM (SELECT COUNT(distinct t.title_id) "Titluri", COUNT(*) "Exemplare" 
     FROM title_copy tc JOIN rental r ON (tc.copy_id = r.copy_id and tc.title_id = r.title_id) 
         JOIN title t ON (t.title_id = tc.title_id) 
     GROUP BY t.category 
     ORDER BY COUNT(*) DESC) 
WHERE rownum = 1; 
--5
select title as "Titlu", count(status) as "Valabile" 
from title_copy join title using(title_id) where status = 'AVAILABLE' 
group by title;
--6
select t.title, tc.copy_id, status, case 
  when (t.title_id, tc.copy_id) not in (select title_id, copy_id from rental where act_ret_date is null) 
    then 'AVAILABLE' 
  else 'RENTED' 
end "status corect" 
from title t, title_copy tc where t.title_id = tc.title_id; 
--7 a
select count(*) "Numar eronate"
from (select t.title, tc.copy_id, status, case  
  when (t.title_id, tc.copy_id) not in (select title_id, copy_id from rental where act_ret_date is null)  
    then 'AVAILABLE'  
  else 'RENTED'  
end "status corect"  
from title t, title_copy tc where t.title_id = tc.title_id) 
where status != "status corect"; 
--7 b
create table title_copy_bhd as select * from title_copy;
update title_copy_bhd set status = (case when (title_id, copy_id) not in (select title_id, copy_id from rental where act_ret_date is null)  
    then 'AVAILABLE'  
  else 'RENTED' end);
select * from title_copy_bhd;
--8
select 
    case when 
        (select count(*) 
        from rental r 
        join reservation rr on (r.member_id=rr.member_id and r.title_id=rr.title_id)
        where book_date != res_date)>0
    then 'NU' 
    else 'DA' 
    end "Au fost toti corecti?"
from dual;
-- Tema SGBD Buhai Darius
--9
select m.last_name "Prenume", m.first_name "Nume", t.title "Titlu Film", count(t.title_id) "Imprumutari"
from member m
join rental r on (r.member_id = m.member_id)
join title_copy c on (c.copy_id=r.copy_id and c.title_id=r.title_id)
join title t on (t.title_id=c.title_id)
group by t.title_id, t.title, m.last_name, m.first_name
order by m.last_name, m.first_name;
--10
select m.last_name "Prenume", m.first_name "Nume",r.copy_id "Cod", t.title "Titlu Film", count(t.title_id) "Imprumutari"
from member m
join rental r on (r.member_id = m.member_id)
join title_copy c on (c.copy_id=r.copy_id and c.title_id=r.title_id)
join title t on (t.title_id=c.title_id)
group by t.title_id, t.title, m.last_name, m.first_name, r.copy_id
order by m.last_name, m.first_name;
--11
select title as "Titlu", tc.status as "Status" 
from title_copy tc join title t on (t.title_id=tc.title_id)
where tc.copy_id = ( select copy_id 
                     from  (select tc.copy_id 
                            from rental r join title_copy tc on (r.copy_id=tc.copy_id)
                            group by tc.copy_id 
                            order by count(tc.copy_id) desc)
                    where rownum = 1);
--12
--a
SELECT DT, (
    select count(*) 
    from rental where 
    extract(day from book_date) = extract(day from DT)
    and extract(month from book_date) = extract(month from DT))  as "Imprumuturi"
FROM(SELECT TRUNC (last_day(add_months(SYSDATE, -1)) + ROWNUM) dt
     FROM DUAL CONNECT BY ROWNUM < 3
     )
ORDER BY DT;
--b
select book_date, count(*) as "Imprumuturi"
from rental 
where extract(month from book_date) = extract(month from sysdate) 
group by book_date 
order by book_date asc;
--c
SELECT DT, (
    select count(*) 
    from rental where 
    extract(day from book_date) = extract(day from DT)
    and extract(month from book_date) = extract(month from DT))  as "Imprumuturi"
FROM(SELECT TRUNC (last_day(SYSDATE) - ROWNUM) dt
     FROM DUAL CONNECT BY ROWNUM < extract(day from last_day(sysdate))
     )
ORDER BY DT;




