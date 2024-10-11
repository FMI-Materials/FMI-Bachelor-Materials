SELECT DISTINCT employee_id
FROM WORKS_ON a
WHERE NOT EXISTS (
                    SELECT 'x'
                    FROM PROJECT p
                    WHERE budget = 10000
                    AND NOT EXISTS
                                    (
                                        SELECT 'x'
                                        FROM WORKS_ON b
                                        WHERE p.project_id = b.project_id
                                        AND b.employee_id = a.employee_id
                                    )
                 );

SELECT employee_id
FROM WORKS_ON
WHERE project_id IN (
                        SELECT project_id
                        FROM PROJECT
                        WHERE budget = 10000
                    )
GROUP BY employee_id
HAVING COUNT(project_id) = (
                                SELECT COUNT(*)
                                FROM project
                                WHERE budget = 10000
                           );

-- 1
SELECT * FROM PROJECT;
SELECT * FROM WORKS_ON;

SELECT employee_id
FROM WORKS_ON


-- 9
select employee_id
from works_on
where project_id IN (select project_id
                      from project
                      where project_manager = 102)--proiectele conduse de 102 -> p1 si p3


MINUS --eliminam angajatii care lucreaza la proiecte conduse de un alt manager
select employee_id
from works_on
where project_id NOT IN (select project_id
    from project
    where project_manager = 102);


-- 1
select sa.cod_asigurator, nume_societate, t.cod_timbru, nume, data_emitere, t.valoarefrom soc_asigurare sa join este_asigurat ea on (sa.cod_asigurator = ea.cod_asigurator)join timbru t on (ea.cod_timbru = t.cod_timbru)where to_char(data_emitere, 'yyyy') = 1990order by t.valoare;

-- 2
select sa.cod_asigurator, nume_societate, tara, cod_timbru,(select sum(valoare)from este_asigurat x join soc_asigurare y on(x.cod_asigurator = y.cod_asigurator)where sa.tara = y.tara) "Valoare totala"from soc_asigurare sa join este_asigurat ea on (sa.cod_asigurator = ea.cod_asigurator);

-- 3
select numefrom (select vanz.cod_vanzator, nume, count(cod_timbru)from vinde vin join vanzator vanz on (vin.cod_vanzator = vanz.cod_vanzator)group by vanz.cod_vanzator, numeorder by 3 desc)where rownum <= 2

-- 4
with valoare_totala as (select vanz.cod_vanzator, vanz.nume, sum(val_cumparare) sumafrom vinde vin join vanzator vanz on (vin.cod_vanzator = vanz.cod_vanzator)group by vanz.cod_vanzator, vanz.nume),vanzatori as (select nume, sumafrom valoare_totalawhere suma > (select round(avg(suma))from valoare_totala))select *from vanzatori;

-- 5
select cod_asiguratorfrom este_asiguratwhere cod_timbru IN (select cod_timbrufrom timbruwhere to_char(data_emitere, 'yyyy') = 1990)group by cod_asiguratorhaving count(cod_timbru) = (select count(cod_timbru)from timbruwhere to_char(data_emitere, 'yyyy') = 1990);

-- 6
select sum(t.valoare), count(t.cod_timbru)from timbru t join vinde v on (t.cod_timbru = v.cod_timbru)where val_pornire = val_cumparare and to_char(data_achizitie, 'yyyy') = 2020;

-- 7
create table valoare_totala(nume_timbru varchar2(30),nume_vanzator varchar2(30),numar_total_timbre number(5));

insert into valoare_totala (select t.nume, vanz.nume, (select count(*)from vindewhere cod_timbru = t.cod_timbru) "Timbre vandute"from timbru t join vinde vin on (t.cod_timbru = vin.cod_timbru)join vanzator vanz on (vin.cod_vanzator = vanz.cod_vanzator));select * from valoare_totala;