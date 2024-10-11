--2 -b) tema
--3 tema

--4
--pt fiecare categorie afisati cate exemplare s-au imprumutat

select max(category), max(count(*))
from title t, rental r
where t.title_id = r.title_id
group by category;

select category, count(*), count( distinct title), count(r.copy_Id)
from title t, rental r
where t.title_id = r.title_id
group by category
having count(*) = (select max(count(*))
                    from title t, rental r
                    where t.title_id = r.title_id
                    group by category);
                    
--5
-- statusul este corect setat
select title_id, count(*)
from title_copy
where status = 'AVAILABLE'
group by title_id 
order by 1;

-- statusul nu este corect setat

select title_id, count(*)
from title_copy
where (copy_id, title_id)  not in (select copy_id, title_id
                                    from rental
                                    where act_ret_date is null)
group by title_id 
order by 1;


select title_id, count(*)
from (
        select copy_id, title_id
        from title_copy
        minus
        select copy_id, title_id
        from rental
        where act_ret_date is null   
    )
group by title_id 
order by 1;


--6

select title, copy_id, status as status_Setat,
case when (copy_id, a.title_id)  not in (select copy_id, title_id
                                        from rental
                                        where act_ret_date is null)
then 'AVAILABLE'
else 'RENTED'
end as status_Corect
from title_copy a, title b
where a.title_id = b.title_id;


--7
--a

select count(*)
from (
        select title, copy_id, status as status_Setat,
        case when (copy_id, a.title_id)  not in (select copy_id, title_id
                                                from rental
                                                where act_ret_date is null)
        then 'AVAILABLE'
        else 'RENTED'
        end as status_Corect
        from title_copy a, title b
        where a.title_id = b.title_id
    )
where status_Setat != status_Corect;

--b

create table title_copy_prof as
select * from title_copy;

update title_copy_prof a
set status = case when (copy_id, a.title_id) not in (select copy_id, title_id
                                                from rental
                                                where act_ret_date is null)
                then 'AVAILABLE'
                else 'RENTED'
                end
where status <> case when (copy_id, a.title_id) not in (select copy_id, title_id
                                                from rental
                                                where act_ret_date is null)
                then 'AVAILABLE'
                else 'RENTED'
                end;
commit;


--8
-- explicatii suplimentare la urmatorul laborator
select case when count(*) = 0 
            then 'DA'
            else 'NU'
        end raspuns
from(
    select res_date, member_id, title_id
    from reservation
    minus
    select book_date, member_id, title_id
    from rental
);

-- daca filmele au fost imprumutate la data rezervarii afisati da, altfel nu
select decode(count(*), 0, 'DA', 'NU')
from (select case when (res_date, title_id, member_id) in (select book_date,
                            title_id, member_id from rental)
        then 'DA'
        else 'NU'
        end info
        from reservation)
where info = 'NU';

--9

select m.member_id, t.title_id, m.first_name, m.last_name, t.title, count(*)
from member m, title t, rental r
where t.title_id = r.title_id
and m.member_id = r.member_id
group by m.member_id, t.title_id, m.first_name, m.last_name, t.title
order by 1,2;

-- aici am intrebam cum putem sa obtinem toate toate titlurile, inclusiv cele care nu au fost imprumutate
-- outer join-ul trebuie propagat, altfel liniile aduse in plus se pierd
-- si facem count doar pt titlurile din rental

select m.member_id, m.first_name, m.last_name,
       t.title_id, t.title, count(r.title_id)
from   member m, title t, rental r
where  t.title_id = r.title_id (+)
and    m.member_id(+) = r.member_id
group by m.member_id, m.first_name, m.last_name, t.title_id, t.title
order by 1,4;

--10 tema

--11
select copy_id, title_id, status
from title_copy
where (copy_id, title_id) 
IN (
        select r.copy_id, r.title_id
        from rental r
        group by r.copy_id, r.title_id
        having count(*)  = (select max(count(*))
                            from rental
                            where title_id = r.title_id
                             group by copy_id, title_id));


-- mai trebuia un join cu title copy
select title_id, copy_id, status
from title_copy
where (copy_id, title_id) 
IN (
        select c.copy_id, c.title_id
        from rental r, title_copy c
        where c.copy_id= r.copy_id
        and c.title_id = r.title_id
        group by c.copy_id, c.title_id
        having count(*)  = (select max(count(*))
                            from rental r, title_copy cr
                            where cr.copy_id= r.copy_id
                            and cr.title_id = r.title_id
                            and cr.title_id = c.title_id
                            group by cr.copy_id, cr.title_id))
order by 1;


-- vedeti ca se repeta query-ul, asa ca putem sa ne folosim de with

with exemplare as
    (select c.title_id, c.copy_id, max(status), count(*) nr
    from   title_copy c, rental r
    where  c.copy_id = r.copy_id
    and    c.title_id = r.title_id
    group by c.title_id, c.copy_id)
select *
from   exemplare ex
where  nr = (select max(nr)
             from exemplare
             where title_id = ex.title_id)
order by 1;

--12 tema

-- da, cerinta spune luna curenta si din aceasta cauza toate inregistrarile vor fi 0, daaar
-- putem sa testem cu luna trecuta, asa ca cererile vor fi doar pt luna trecuta

-- pentru a pune mana pe luna trecuta avem functia add_month(data, +-nr_de_luni)

--a 
-- aici scopul nu era sa punem de mana valorile 01-09-2021 si 02-09-2021
-- o metoda pentru a ajunge fara hardcoding la prima zi din luna era sa folosim trunc cu 'mm' pt luna

select trunc(add_months(sysdate,-1),'mm') 
from dual;

select (select count(*) from rental where  book_date = trunc(add_months(sysdate,-1),'mm')) zi_1,
       (select count(*) from   rental where  book_date = trunc(add_months(sysdate,-1),'mm')+1) zi_2 
from dual;

-- daca vrem sa afisam si alte detalii atunci putem sa facem cu 2 cereri separate
-- alaturate prin union

select trunc(add_months(sysdate,-1),'mm') ||' cu nr de imprumuturi: '||count(*) rent_per_day
from   rental 
where  book_date = trunc(add_months(sysdate,-1),'mm')
union 
select trunc(add_months(sysdate,-1),'mm')+1 ||' cu nr de imprumuturi: '||count(*) 
from   rental 
where  book_date = trunc(add_months(sysdate,-1),'mm')+1;

-- foarte multe variante de rezolvare aici


--b
-- trebuie sa ne uitam doar la zilele care exista in rental
-- si sa le filtram dupa luna si an
select book_date zi,count(*)
from   rental
where  to_char(book_date,'mm-yyyy')=to_char(add_months(sysdate,-1),'mm-yyyy')
group by book_date; 


--c
-- este o cerinta fab, care se rezolva cu cereri ierarhice, care permit intr-o anumita masura recursivitate
-- trebuia sa gasim o metoda prin care sa generam linii care sa contina toate zilele lunii 
-- pentru a putea compara usor cu book_date

SELECT sysdate, trunc((sysdate),'mm') prima_zi, last_day(sysdate) ultima_zi
FROM dual;

-- o metoda prin care putem sa generam siruri de numere este sa folosim pseudocoloana level
-- impreuna cu clauza connect by, pentru partea de recursivitate
-- level indica nivelul de nesting dintr-o ierarhie

-- un exemplu de cerere pe employees folosind level ar fi:
SELECT employee_id, last_name, manager_id, LEVEL
   FROM employees
   CONNECT BY PRIOR employee_id = manager_id;
   
 -- unde selectam fiecare subaltern al fiecarui angajat care este manager pentru cineva
 -- 100 este manager pt 101 si este la primul nivel din ierarhie pt ca 100 nu are manager
 -- 101 este manager pt 108 si este la al doilea nivel din ierarhie
 -- 108 este manager pt 5 angajati
 -- apoi revenim iar la nivelul 2 din ierarhie, pt ca 101 este manager-ul pt alti 4 angajati
 -- dintre care doar unul este manager pt cineva
 -- si ajungem iar la 100 si reluam procesul
 
 -- evident ierarhiile sunt complicate si mai exista clauze si operatori care pot fi folositi
 -- pentru a ajunge la rezultatul dorit
 -- daaar care sunt out of scope atm
 
 -- noi nu avem o ierarhie pentru cerinta noastra, asa ca vreau doar sa generez toate zilele din luna,
 -- adica last_day() nivele de nesting
 
select level
from  dual
connect by level <= extract (day from last_day(add_months(sysdate,-1)));

--daca dorim sa incepem de la un anumit numar

select level + 5, rownum
from dual
connect by level <= extract (day from last_day(add_months(sysdate,-1)));

-- deci, trebuie sa incepem de la prima zi din luna, si sa tot adaugam nivelul de nesting pt a ajunge la 
-- valorile cu care vom compara book_date

select trunc(add_months(sysdate,-1),'mm') + level-1 
       from   dual
       connect by level <= extract (day from last_day(add_months(sysdate,-1)));

-- asa ca.... taa daaa:       
select ziua, (select count(*) from rental where to_char(book_date,'dd.mm.yyyy') = to_char(ziua,'dd.mm.yyyy')) as nr
from  (select trunc(add_months(sysdate,-1),'month') + level-1 ziua
       from   dual
       connect by level<=extract (day from last_day(add_months(sysdate,-1))));
       
