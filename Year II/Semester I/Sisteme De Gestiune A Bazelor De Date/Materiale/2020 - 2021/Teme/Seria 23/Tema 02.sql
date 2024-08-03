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
