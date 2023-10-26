SET SERVEROUTPUT ON;
-- 13
-- Definiți un pachet care să conțină toate obiectele definite în cadrul proiectului.
CREATE OR REPLACE PACKAGE proiect_bhd AS
    PROCEDURE afisare_categorii_produs(v_id_produs Produse.id_produs%TYPE);
    PROCEDURE afisare_promotii;
    FUNCTION produse_comandate_in_judet (v_judet Adresa.judet%TYPE, v_data_din DATE, v_data_pana DATE) RETURN NUMBER;
    PROCEDURE afisare_comenzi (v_nume Utilizator.nume%TYPE, v_prenume Utilizator.prenume%TYPE);
END proiect_bhd;
/
CREATE OR REPLACE PACKAGE BODY proiect_bhd AS
    --6
    -- Definiți un subprogram stocat care să utilizeze un tip de colecție studiat. Apelați subprogramul.
    
    -- Pentru un produs dat (id_produs), salvati si afisati categoriile din care face parte

    PROCEDURE afisare_categorii_produs
        (v_id_produs Produse.id_produs%TYPE)
    AS
        TYPE tablou_indexat IS TABLE OF Categorii%ROWTYPE INDEX BY PLS_INTEGER;
        t tablou_indexat;
        v_categorie Categorii%ROWTYPE;
        v_id_categorie Categorii.id_categorie%TYPE;
        ind NUMBER;
    BEGIN
        ind := 0;
        select id_categorie into v_id_categorie from Produse where id_produs = v_id_produs;
        LOOP
            EXIT WHEN v_id_categorie is NULL;
            select id_categorie, id_parinte, denumire into v_categorie
            from Categorii where id_categorie = v_id_categorie;
            t(ind) := v_categorie;
            ind := ind + 1;
            v_id_categorie := v_categorie.id_parinte;
        END LOOP;
        DBMS_OUTPUT.PUT_LINE('Produsul cu id-ul '|| v_id_produs || ' apartine urmatoarelor categorii: ');
        DBMS_OUTPUT.PUT_LINE('');
        FOR i IN REVERSE t.FIRST..t.LAST LOOP
            DBMS_OUTPUT.PUT(t(i).denumire);
            IF i > 0 THEN
                DBMS_OUTPUT.PUT(' -> ');
            END IF;
        END LOOP;
        DBMS_OUTPUT.PUT_LINE('');
    END afisare_categorii_produs;
    
    --7
    -- Definiți un subprogram stocat care să utilizeze un tip de cursor studiat. Apelați subprogramul.

    -- Afisati pentru fiecare Promotie in parte: 
    -- codul promotional, discount-ul, numarul de comenzi pe care este aplicat si suma totala redusa.
    
    PROCEDURE afisare_promotii AS
        v_count_comenzi NUMBER;
        v_total_comenzi NUMBER;
        v_total_redus NUMBER;
        
        TYPE t_detalii_promotie IS RECORD(
            cod_promotional Promotii.cod_promotional%TYPE,
            discount Promotii.discount%TYPE,
            descriere Promotii.descriere%TYPE
        );
        detalii_promotie t_detalii_promotie;
        
        CURSOR c_promotii RETURN t_detalii_promotie IS
        select cod_promotional, discount, descriere
        from Promotii;
        
        CURSOR c_count_comenzi IS
        select count(id_comanda) from Comenzi
        where cod_promotional = detalii_promotie.cod_promotional;
    BEGIN
        DBMS_OUTPUT.PUT_LINE('Detalii coduri promotionale: ');
        DBMS_OUTPUT.PUT_LINE('');
        OPEN c_promotii;
        LOOP
            FETCH c_promotii INTO detalii_promotie;
            EXIT WHEN c_promotii%NOTFOUND;
            
            OPEN c_count_comenzi;
                FETCH c_count_comenzi INTO v_count_comenzi;
            CLOSE c_count_comenzi;
            
            DBMS_OUTPUT.PUT_LINE('Codul promotional ' || detalii_promotie.cod_promotional || ' are un discount de ' || detalii_promotie.discount || '%');
            
            IF v_count_comenzi = 0 THEN
                DBMS_OUTPUT.PUT_LINE('si nu este folosit in nicio comanda.');
            ELSE
                v_total_comenzi := total_comenzi(detalii_promotie.cod_promotional);
                v_total_redus := (detalii_promotie.discount / 100) * v_total_comenzi;
                DBMS_OUTPUT.PUT_LINE('si este folosit in ' || v_count_comenzi || ' comenzi, cu o reducere aplicata de ' || v_total_redus || ' lei.');
            END IF;
            DBMS_OUTPUT.PUT_LINE('');
            
        END LOOP;
        CLOSE c_promotii;
    END afisare_promotii;
    
    -- 8
    -- Definiți un subprogram stocat de tip funcție care să utilizeze 3 dintre tabelele definite. Tratați toate
    -- excepțiile care pot apărea. Apelați subprogramul astfel încât să evidențiați toate cazurile tratate.
    
    -- Creati o functie care sa returneze numarul de produse comandate dintr-un judet dat intr-un anumit interval de timp

    FUNCTION produse_comandate_in_judet
       (v_judet Adresa.judet%TYPE, v_data_din DATE, v_data_pana DATE)
    RETURN NUMBER IS
         v_id_adresa Adresa.id_adresa%TYPE;
         v_count NUMBER;
       BEGIN
         select id_adresa into v_id_adresa from Adresa
         where judet = v_judet;
         select count(p.id_produs) into v_count
         from Comenzi c 
         join comanda_contine_produse cp on (c.id_comanda=cp.id_comanda)
         join Produse p on (p.id_produs=cp.id_produs)
         where c.id_adresa = v_id_adresa and data >= v_data_din and data <= v_data_pana;
         RETURN v_count;
       EXCEPTION
         WHEN NO_DATA_FOUND THEN
            RAISE_APPLICATION_ERROR(-20000, 'Nu exista nicio adresa cu judetul dat');
         WHEN OTHERS THEN
           RAISE_APPLICATION_ERROR(-20002,'Alta eroare!');
    END produse_comandate_in_judet;
    
    -- 9
    -- Definiți un subprogram stocat de tip procedură care să utilizeze 5 dintre tabelele definite. Tratați toate
    -- excepțiile care pot apărea. Apelați subprogramul astfel încât să evidențiați toate cazurile tratate.
 
    -- Afisati toate comenzile cu adresa si totalul lor (aplicand codurile promotionale) facute de un utilizator dat (nume si prenume)
    
    PROCEDURE afisare_comenzi
        (v_nume Utilizator.nume%TYPE, v_prenume Utilizator.prenume%TYPE)
    IS
        v_id_utilizator Utilizator.id_utilizator%TYPE;
        
        v_total_comanda INT;
        
        v_discount Promotii.discount%TYPE;
        
        TYPE t_detalii_comanda IS RECORD(
            id_comanda INT,
            judet Adresa.judet%TYPE,
            oras Adresa.oras%TYPE,
            text_adresa Adresa.adresa%TYPE,
            cod_promotional Promotii.cod_promotional%TYPE
        );
        TYPE t_detalii_produs IS RECORD(
            pret Produse.pret%TYPE,
            cantitate comanda_contine_produse.cantitate%TYPE
        );
        detalii_comanda t_detalii_comanda;
        detalii_produs t_detalii_produs;
        
        CURSOR c_comanda RETURN t_detalii_comanda IS
        select c.id_comanda, a.judet, a.oras, a.adresa, c.cod_promotional
        from Comenzi c join Adresa a on (c.id_adresa=a.id_adresa)
        where c.id_utilizator = v_id_utilizator;
        
        CURSOR c_produs RETURN t_detalii_produs IS
        select p.pret, cp.cantitate from Produse p
        join comanda_contine_produse cp using(id_produs)
        where cp.id_comanda = detalii_comanda.id_comanda;
        
    BEGIN
        select id_utilizator into v_id_utilizator from Utilizator
        where lower(nume) like lower(v_nume) and lower(prenume) like lower(v_prenume);
        DBMS_OUTPUT.PUT_LINE('Istoric comenzi ' || v_nume || ' ' || v_prenume || ': ');
        DBMS_OUTPUT.PUT_LINE('');
        OPEN c_comanda;
            LOOP
                FETCH c_comanda INTO detalii_comanda;
                EXIT WHEN c_comanda%NOTFOUND;
                
                v_discount := 0;
                v_total_comanda := 0;
                
                OPEN c_produs;
                    LOOP
                        FETCH c_produs INTO detalii_produs;
                        EXIT WHEN c_produs%NOTFOUND;
                        v_total_comanda := v_total_comanda + detalii_produs.pret * detalii_produs.cantitate;
                    END LOOP;
                CLOSE c_produs;
                
                DBMS_OUTPUT.PUT_LINE('Comanda cu id-ul ' || detalii_comanda.id_comanda || ' din ' || detalii_comanda.judet || ', ' || detalii_comanda.oras || ', ' || detalii_comanda.text_adresa);
                
                IF detalii_comanda.cod_promotional IS NOT NULL THEN
                    select discount into v_discount from Promotii
                    where cod_promotional = detalii_comanda.cod_promotional;
                    v_total_comanda := v_total_comanda - v_discount / 100 * v_total_comanda;
                    DBMS_OUTPUT.PUT_LINE('are o valoare totala de ' || v_total_comanda || ' de lei, cu un discount de ' || v_discount || '% aplicat.');
                ELSE
                    DBMS_OUTPUT.PUT_LINE('are o valoare totala de ' || v_total_comanda || ' de lei, si nu are nicio promotie aplicata.');
                END IF;
                
            END LOOP;
        CLOSE c_comanda;
    EXCEPTION
        WHEN NO_DATA_FOUND THEN
          RAISE_APPLICATION_ERROR(-20000, 'Niciun utilizator gasit cu numele si prenumele dat!');
        WHEN TOO_MANY_ROWS THEN
          RAISE_APPLICATION_ERROR(-20001, 'Exista mai multi utilizatori cu numele dat');
        WHEN OTHERS THEN
          RAISE_APPLICATION_ERROR(-20002,'Alta eroare!');
    END afisare_comenzi;
    
END proiect_bhd;
/
-- Testare pachet
-- 6
execute proiect_bhd.afisare_categorii_produs(1);
-- 7
execute proiect_bhd.afisare_promotii();
-- 8
/
BEGIN
    -- Apel corect
    DBMS_OUTPUT.PUT_LINE('Produse comandate in Brasov din 01-11-2020 pana in 01-01-2021: ' || proiect_bhd.produse_comandate_in_judet('Brasov', TO_DATE('01-11-2020', 'dd-mm-yyyy'), TO_DATE('01-01-2021', 'dd-mm-yyyy')));
END;
/
BEGIN
    -- Exceptie: Judet inexistent
    DBMS_OUTPUT.PUT_LINE('Produse comandate in Transalpina din 01-11-2020 pana in 01-01-2021: ' || proiect_bhd.produse_comandate_in_judet('Transalpina', TO_DATE('01-11-2020', 'dd-mm-yyyy'), TO_DATE('01-01-2020', 'dd-mm-yyyy')));
END;
/
-- 9
-- Test cu cod promotional
execute proiect_bhd.afisare_comenzi('Darius', 'Buhai');
-- Test fara cod promotional
execute proiect_bhd.afisare_comenzi('George', 'Mihai');
-- Test nume inexistent
execute proiect_bhd.afisare_comenzi('Marcu', 'Ion');
-- Test mai multi utilizatori cu acelasi nume
execute proiect_bhd.afisare_comenzi('%', '%');

