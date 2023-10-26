SET SERVEROUTPUT ON;
-- 1
DECLARE
    TYPE vector IS varray(5) OF emp_bhd.employee_id%type;
    coduri vector;
    salariu_vechi INTEGER;
    salariu_nou INTEGER;
BEGIN
    select employee_id bulk collect into coduri
    from (select employee_id from emp_bhd where commission_pct is null order by salary asc)
    where rownum <= 5;
    
    for i in 1..5 loop
        select salary into salariu_vechi from emp_bhd where employee_id = coduri(i);
        update emp_bhd set salary = salary * 1.05 where employee_id = coduri(i);
        select salary into salariu_nou from emp_bhd where employee_id = coduri(i);
        DBMS_OUTPUT.put_line('Salariu vechi: ' || salariu_vechi || ', Salariu nou: ' || salariu_nou);
    end loop;
    rollback;
END;

-- 2
drop table excursie_bhd;
drop type tip_orase_bhd;
create or replace type tip_orase_bhd as varray(5) of varchar2(20);
/
create table excursie_bhd (
    cod_excursie NUMBER(4) NOT NULL PRIMARY KEY,
    denumire VARCHAR2(20),
    orase tip_orase_bhd,
    status varchar(20)
);
--3
create table excursie_bhd (
    cod_excursie NUMBER(4) NOT NULL PRIMARY KEY,
    denumire VARCHAR2(20),
    status varchar(20)
);
create or replace type tip_orase_bhd is table of varchar2(20);
/
ALTER TABLE excursie_bhd
ADD (orase tip_orase_bhd)
NESTED TABLE orase STORE AS tabel_orase_bhd;
-- 3

DECLARE
    orase_curente excursie_bhd.orase%type;
    cod_excursie_specificat excursie_bhd.cod_excursie%type;
    oras_vizitat1 varchar2(20);
    oras_vizitat2 varchar2(20);
    id_oras_1 integer(5);
    id_oras_2 integer(5);
    aux varchar2(20);
    oras_specificat varchar2(20);
    pozitie_sters integer(5);
    numar_orase_vizitate integer(5);
    
    curr_orase excursie_bhd.orase%type;
    cod_excursie excursie_bhd.cod_excursie%type;
    nr_excursii NUMBER;
    TYPE vector IS varray(20) OF excursie_bhd.cod_excursie%type;
    excursii vector;
BEGIN
    delete from excursie_bhd;
    -- a
    for i in 1..5 loop
        insert into excursie_bhd (cod_excursie, denumire, orase, status) values (i, 'test '|| i, tip_orase_bhd('oras1', 'oras2'), 'disponibila');
    end loop;
    -- b
    cod_excursie_specificat := &cod_excursie;
    select orase into orase_curente from excursie_bhd where cod_excursie = cod_excursie_specificat;
    -- b1
    orase_curente.extend();
    orase_curente(orase_curente.count) := 'oras_nou';
    -- b2
    orase_curente.extend();
    for i in reverse 2..orase_curente.count loop
        orase_curente(i) := orase_curente(i-1);
    end loop;
    orase_curente(2) := 'oras_secundar';
    -- b3
    oras_vizitat1 := '&oras_vizitat1';
    oras_vizitat2 := '&oras_vizitat2';
    id_oras_1 := 1;
    id_oras_2 := 1;
    for i in 1..orase_curente.count loop
        if orase_curente(i) = oras_vizitat1 then
            id_oras_1 := i;
        end if;
        if orase_curente(i) = oras_vizitat2 then
            id_oras_2 := i;
        end if;
    end loop;
    aux := orase_curente(id_oras_1);
    orase_curente(id_oras_1) := orase_curente(id_oras_2);
    orase_curente(id_oras_2) := aux;
    -- b4
    oras_specificat := '&oras_specificat';
    for i in 1..orase_curente.count loop
        if orase_curente(i) = oras_specificat then 
            pozitie_sters := i;
        end if;
    end loop;
    for i in reverse pozitie_sters..orase_curente.count loop
        orase_curente(i) := orase_curente(i - 1);
    end loop;
    orase_curente.trim;
    -- then update
    update excursie_bhd set orase = orase_curente where cod_excursie = cod_excursie_specificat;
    -- c
    DBMS_OUTPUT.put_line('Numar orase: '|| orase_curente.count ||', orase: ');
    for i in 1..orase_curente.count loop
        DBMS_OUTPUT.put_line(orase_curente(i) || ', ');
    end loop;
    -- d
    select cod_excursie BULK COLLECT into excursii FROM excursie_bhd;
    for i in 1..excursii.count loop
        select orase into curr_orase
        from excursie_bhd
        where cod_excursie = excursii(i);
        DBMS_OUTPUT.put_line('Excursia ' || excursii(i) || ': ');
        for i in 1..curr_orase.count loop
            DBMS_OUTPUT.put_line(curr_orase(i) || ', ');
        end loop;
    end loop;
    -- e
    
END;
select * from excursie_bhd;


