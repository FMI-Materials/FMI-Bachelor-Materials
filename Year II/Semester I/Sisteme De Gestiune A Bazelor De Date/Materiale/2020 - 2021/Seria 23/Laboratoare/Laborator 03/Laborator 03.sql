-- Ex 1
SET SERVEROUTPUT ON;
DECLARE
    numar   NUMBER(3) := 100;
    mesaj1  VARCHAR2(255) := 'text 1';
    mesaj2  VARCHAR2(255) := 'text 2';
BEGIN
    DECLARE
        numar   NUMBER(3) := 1;
        mesaj1  VARCHAR2(255) := 'text 2';
        mesaj2  VARCHAR2(255) := 'text 3';
    BEGIN
        numar := numar + 1;
        mesaj2 := mesaj2 || ' adaugat in sub-bloc';
        dbms_output.put_line(numar);
        dbms_output.put_line(mesaj1);
        dbms_output.put_line(mesaj2);
    END;

    numar := numar + 1;
    mesaj1 := mesaj1 || ' adaugat un blocul principal';
    mesaj2 := mesaj2 || ' adaugat in blocul principal';
    dbms_output.put_line(numar);
    dbms_output.put_line(mesaj1);
    dbms_output.put_line(mesaj2);
END;
-- a) 2
-- b) text 2
-- c) text 3 adaugat in sub-bloc
-- d) 101
-- e) text 1 adaugat un blocul principal
-- f) text 2 adaugat in blocul principal

-- Ex 2
-- a)
SELECT DT, (
    select count(*) 
    from rental where 
    extract(day from book_date) = extract(day from DT)
    and extract(month from book_date) = extract(month from DT))  as "Imprumuturi"
FROM(SELECT TRUNC (last_day(SYSDATE) - ROWNUM) dt
     FROM DUAL CONNECT BY ROWNUM < extract(day from last_day(sysdate))
     )
ORDER BY DT;
-- b)
create table octombrie_bhd(zi number(10), book_date date);
delete from octombrie_bhd;
SET SERVEROUTPUT ON;
DECLARE
    rentals NUMBER(3) := 0;
    d NUMBER(3) := extract(day from last_day(sysdate));
BEGIN
    FOR i IN 1..d LOOP
        select count(*) into rentals from rental 
        where extract(day from book_date) = i
        and extract(month from book_date) = extract(month from sysdate);
        --INSERT INTO octombrie_bhd VALUES (i , rentals);
        INSERT INTO octombrie_bhd VALUES (i, TO_DATE(i ||' 10'||' 2020', 'DD MM YYYY'));
    END LOOP;
END;
select * from octombrie_bhd;
select * from member;
-- Ex 3
DECLARE
    r NUMBER(3) := 0;
    name VARCHAR(101) := '&name';
BEGIN
    select count(title) into r
    from rental rr join member mm on (rr.member_id=mm.member_id) join title tt on (tt.title_id=rr.title_id) 
    where lower(last_name) like '%'||lower(name)||'%' or lower(first_name) like '%'||lower(name)||'%' 
    and rownum = 1;
    dbms_output.put_line(name || ': '||r);
END;
-- Ex 4
DECLARE
    r NUMBER(3) := 0;
    t NUMBER(3) := 0;
    pp NUMBER(3) := 0;
    name VARCHAR(101) := '&name';
BEGIN
    select count(title) into t
    from rental join title using (title_id);
    
    select count(title_id) into r
    from rental rr join member mm using (member_id)
    where lower(last_name) like '%' || lower(name) || '%' or lower(first_name) like '%' || lower(name) || '%' 
    and rownum = 1;
    
    dbms_output.put_line(name || ': '||r);
    
    pp := (r/t)*100;
    if pp > 75 then
        dbms_output.put_line('Categoria 1');
    elsif pp>50 then
        dbms_output.put_line('Categoria 2');
    elsif pp>25 then
        dbms_output.put_line('Categoria 3');
    else
        dbms_output.put_line('Categoria 4');
    end if;
END;
-- Ex 5
create table member_bhd as (select * from member);

ALTER TABLE member_bhd ADD CONSTRAINT PK_member_bhd PRIMARY KEY (member_id);

alter table member_bhd
add discount number;

SET VERIFY OFF
DECLARE
    cod_membru member_bhd.member_id%TYPE: = &cod;
    nr_titles_b number;
    nr_titles_t number;
BEGIN
    select count(*)
    into nr_titles_t
    from title;
    
    select count(distinct title_id)
    into nr_titles_b
    from rental r join member_bhd m using (member_id)
    group by member_id
    having member_id = cod_membru;
    
    CASE WHEN nr_titles_b * 100 / nr_titles_t >= 75 THEN 
            UPDATE member_bhd
            SET DISCOUNT = 10
            WHERE MEMBER_ID = cod_membru;
            COMMIT;
            DBMS_OUTPUT.PUT_LINE('1 rand modificat');
        WHEN nr_titles_b * 100 / nr_titles_t >= 50 THEN 
            UPDATE member_bhd
            SET DISCOUNT = 5
            WHERE MEMBER_ID = cod_membru;
            COMMIT;
            DBMS_OUTPUT.PUT_LINE('1 rand modificat');
        WHEN nr_titles_b * 100 / nr_titles_t >= 25 THEN
            UPDATE member_bhd
            SET DISCOUNT = 3
            WHERE MEMBER_ID = cod_membru;
            COMMIT;
            DBMS_OUTPUT.PUT_LINE('1 rand modificat');
        ELSE 
            DBMS_OUTPUT.PUT_LINE('Nicio modificare facuta');
    END CASE;        
EXCEPTION
    WHEN NO_DATA_FOUND THEN
    DBMS_OUTPUT.PUT_LINE('Nicio modificare facuta');
END;
/ 
SET VERIFY ON;

select * from member_bhd;
