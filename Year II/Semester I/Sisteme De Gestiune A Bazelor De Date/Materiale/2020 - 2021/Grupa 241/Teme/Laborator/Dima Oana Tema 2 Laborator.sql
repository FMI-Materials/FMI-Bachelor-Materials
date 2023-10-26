--Dima Oana Teodora 241 Tema 2 Laborator Deadline: 19 nov 2020
--ex2
--Defini?i un tip colec?ie denumit tip_orase_***
create type tip_orase_odi is varray (20) of varchar2(20);
/
--Crea?i tabelul excursie_***
create table excursie_odi
    (cod_excursie number(4), 
        denumire varchar2(20), 
        orase tip_orase_odi,
        status varchar2(20)
    );
/

--a. Insera?i 5 înregistr?ri în tabel.
insert into excursie_odi
values (1, 'Descopera Romania', tip_orase_odi('Bucuresti', 'Iasi', 'Cluj','Oradea'), 'disponibila');

insert into excursie_odi
values (2, 'Traditii si monumete', tip_orase_odi('Cluj','Oradea', 'Satu Mare'), 'anulata');

insert into excursie_odi
values (3, 'Promenada la Palate', tip_orase_odi('Iasi', 'Brasov','Sinaia'), 'disponibila');

insert into excursie_odi
values (4, 'Delta frumoasa',tip_orase_odi('Tulcea', 'Constanta'), 'anulata');

insert into excursie_odi
values (5, 'Litoralul romanesc',tip_orase_odi('Mamaia', 'Eforie', 'Mangalia','Vama Veche'), 'disponibila');

commit;
--b Actualiza?i coloana orase pentru o excursie specificat?: 
-- ad?uga?i un ora? nou în list?, ce va fi ultimul vizitat în excursia respectiv?;
/
declare 
    nume_ex excursie_odi.denumire%type := lower( '&denumire');
    oras_nou varchar(20):='&nume';
    o excursie_odi.orase%type;
    
begin

   select orase
   into o
   from excursie_odi
   where lower(denumire)=nume_ex;
   
   o.extend;
   o(o.last):=oras_nou;
   
   update excursie_odi
   set orase=o
   where lower(denumire)=nume_ex;
    
end;
/
commit;
/
--- ad?uga?i un ora? nou în list?, ce va fi al doilea ora? vizitat în excursia respectiv?;
/
declare 
    nume_ex excursie_odi.denumire%type := lower( '&denumire');
    oras_nou varchar(20):='&nume';
    o excursie_odi.orase%type;
    
begin

   select orase
   into o
   from excursie_odi
   where lower(denumire)=nume_ex;
   
   o.extend;
   for i in reverse 2..o.last-1 loop
    o(i+1):=o(i);
    end loop;
    o(2):=oras_nou;
   
   update excursie_odi
   set orase=o
   where lower(denumire)=nume_ex;
    
end;
/
select * from excursie_odi;
commit;
/
--inversa?i ordinea de vizitare a dou? dintre ora?e al c?ror nume este specificat;
/
declare 
    nume_ex excursie_odi.denumire%type := lower( '&denumire');
    oras_nou1 varchar(20):=lower('&nume1');
    oras_nou2 varchar(20):=lower('&nume2');
    aux varchar(20);
    poz1 binary_integer;
    poz2 binary_integer;
    o excursie_odi.orase%type;
    
begin

   select orase
   into o
   from excursie_odi
   where lower(denumire)=nume_ex;
   
   for i in o.first..o.last loop
    if lower(o(i))=oras_nou1 then poz1:=i;
    elsif lower(o(i))=oras_nou2 then poz2:=i;
    end if;
    end loop;
    
    aux:=o(poz1);
    o(poz1):=o(poz2);
    o(poz2):=aux;
    
   
   update excursie_odi
   set orase=o
   where lower(denumire)=nume_ex;
    
end;
/
select * from excursie_odi;
commit;
/
--elimina?i din list? un ora? al c?rui nume este specificat
/
declare 
    nume_ex excursie_odi.denumire%type := lower( '&denumire');
    oras_nou varchar(20):='&nume';
    o excursie_odi.orase%type;
    type tablou_indexat is table of varchar2(20) index by binary_integer;
    t tablou_indexat;
    
begin

   select orase
   into o
   from excursie_odi
   where lower(denumire)=nume_ex;
   
    --delete nu merge pe varray
   for i in o.last..o.first loop
    if lower(o(i))<>oras_nou then t(t.count+1):=o(i);
    end if;
    end loop;
    
   
   for i in 1..t.count loop
   o(i):=t(i);
   dbms_output.put_line(o(i));
   end loop;
   o.trim;
   
   update excursie_odi
   set orase=o
   where lower(denumire)=nume_ex;
    
end;
/
select * from excursie_odi;
rollback;
commit;
/
--ex 3. Rezolva?i problema anterioar? folosind un alt tip de colec?ie studiat.
create type tip_odi is table of varchar2(20);
/
--Crea?i tabelul excursie_***
create table excursie3_odi
    (cod_excursie number(4), 
        denumire varchar2(20),
        orase tip_odi,
        status varchar2(20)
    )
    nested table orase store as tip_o_odi;
/

--a. Insera?i 5 înregistr?ri în tabel.
insert into excursie3_odi
values (1, 'Descopera Romania', tip_odi('Bucuresti', 'Iasi', 'Cluj','Oradea'), 'disponibila');

insert into excursie3_odi
values (2, 'Traditii si monumete', tip_odi('Cluj','Oradea', 'Satu Mare'), 'anulata');

insert into excursie3_odi
values (3, 'Promenada la Palate', tip_odi('Iasi', 'Brasov','Sinaia'), 'disponibila');

insert into excursie3_odi
values (4, 'Delta frumoasa',tip_odi('Tulcea', 'Constanta'), 'anulata');

insert into excursie3_odi
values (5, 'Litoralul romanesc',tip_odi('Mamaia', 'Eforie', 'Mangalia','Vama Veche'), 'disponibila');

select * from excursie3_odi;
commit;
--b Actualiza?i coloana orase pentru o excursie specificat?: 
-- ad?uga?i un ora? nou în list?, ce va fi ultimul vizitat în excursia respectiv?;
/
declare 
    nume_ex excursie3_odi.denumire%type := lower( '&denumire');
    oras_nou varchar(20):='&nume';
    o excursie3_odi.orase%type;
    
begin

   select orase
   into o
   from excursie3_odi
   where lower(denumire)=nume_ex;
   
   o.extend;
   o(o.last):=oras_nou;
   
   update excursie3_odi
   set orase=o
   where lower(denumire)=nume_ex;
    
end;
/
select * from excursie3_odi;
commit;
/
--- ad?uga?i un ora? nou în list?, ce va fi al doilea ora? vizitat în excursia respectiv?;
/
declare 
    nume_ex excursie3_odi.denumire%type := lower( '&denumire');
    oras_nou varchar(20):='&nume';
    o excursie3_odi.orase%type;
    
begin

   select orase
   into o
   from excursie3_odi
   where lower(denumire)=nume_ex;
   
   o.extend;
   for i in reverse 2..o.last-1 loop
    o(i+1):=o(i);
    end loop;
    o(2):=oras_nou;
   
   update excursie3_odi
   set orase=o
   where lower(denumire)=nume_ex;
    
end;
/
select * from excursie3_odi;
commit;
/
--inversa?i ordinea de vizitare a dou? dintre ora?e al c?ror nume este specificat;
/
declare 
    nume_ex excursie3_odi.denumire%type := lower( '&denumire');
    oras_nou1 varchar(20):=lower('&nume1');
    oras_nou2 varchar(20):=lower('&nume2');
    aux varchar(20);
    poz1 binary_integer;
    poz2 binary_integer;
    o excursie3_odi.orase%type;
    
begin

   select orase
   into o
   from excursie3_odi
   where lower(denumire)=nume_ex;
   
   for i in o.first..o.last loop
    if lower(o(i))=oras_nou1 then poz1:=i;
    elsif lower(o(i))=oras_nou2 then poz2:=i;
    end if;
    end loop;
    
    aux:=o(poz1);
    o(poz1):=o(poz2);
    o(poz2):=aux;
    
   
   update excursie3_odi
   set orase=o
   where lower(denumire)=nume_ex;
    
end;
/
select * from excursie3_odi;
commit;
/
--elimina?i din list? un ora? al c?rui nume este specificat
/
declare 
    nume_ex excursie3_odi.denumire%type := lower( '&denumire');
    oras_nou varchar(20):='&nume';
    o excursie3_odi.orase%type;
    poz binary_integer;
    
begin

   select orase
   into o
   from excursie3_odi
   where lower(denumire)=nume_ex;
   

   for i in o.first..o.last loop
    if lower(o(i))=oras_nou then poz:=i;  
    end if;
    end loop;
    
   o.delete(poz);
  
   
   update excursie3_odi
   set orase=o
   where lower(denumire)=nume_ex;
    
end;
/
select * from excursie3_odi;
rollback;
commit;
/
