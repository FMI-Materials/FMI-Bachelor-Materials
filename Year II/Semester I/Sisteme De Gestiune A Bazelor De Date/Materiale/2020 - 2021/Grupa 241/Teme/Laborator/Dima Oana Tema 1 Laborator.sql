--Tema 1 Dima Oana-Teodora grupa 241
-- Deadline miercuri 21 octombrie 2020

--10. De câte ori a împrumutat un membru (nume ?i prenume)
--fiecare exemplar (cod) al unui film (titlu)?

with tabel as (select member_id, title_id , copy_id 
                from member, title_copy)--product
select m.last_name Nume, m.first_name Prenume,
        t.title Titlu, tb.copy_id Cod_copie, count(r.copy_id) Numar--ignora null =>
from tabel tb, member m, rental r, title t   --=> pune 0 unde nu a imprumutat
where tb.member_id = r.member_id(+) --join
    and tb.title_id = r.title_id (+)
    and m.member_id=tb.member_id
    and t.title_id=tb.title_id
group by m.last_name, m.first_name, t.title, tb.copy_id
order by 1;

--11. Ob?ine?i statusul celui mai des împrumutat 
--exemplar al fiec?rui film (titlu).
select distinct status, title
from title_copy tc join title t on (tc.title_id=t.title_id)
where (tc.title_id, tc.copy_id) in(select title_id, copy_id
                                from rental
                                group by title_id, copy_id
                                having count(*)=(select max(count(*))
                                                        from rental
                                                        group by title_id, copy_id
                                                        )
                                );
