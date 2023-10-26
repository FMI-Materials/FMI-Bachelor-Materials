SET SERVEROUTPUT ON;

--14
-- Definiți un pachet care să includă tipuri de date complexe și obiecte necesare pentru acțiuni integrate.

CREATE OR REPLACE PACKAGE proiect_bhd_2 AS
    -- Ex 6
    TYPE tablou_indexat IS TABLE OF Categorii%ROWTYPE INDEX BY PLS_INTEGER;

    -- Ex 7
    FUNCTION total_comenzi (v_cod_promotional Comenzi.cod_promotional%TYPE) RETURN NUMBER;
    
    TYPE t_detalii_promotie IS RECORD(
        cod_promotional Promotii.cod_promotional%TYPE,
        discount Promotii.discount%TYPE,
        descriere Promotii.descriere%TYPE
    );
    
    CURSOR c_promotii RETURN t_detalii_promotie;
        
    -- Ex 9
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
    
END proiect_bhd_2;
/
CREATE OR REPLACE PACKAGE BODY proiect_bhd_2 AS
    -- 7
    CURSOR c_promotii RETURN t_detalii_promotie IS
    select cod_promotional, discount, descriere
    from Promotii;
    
    -- 7
    FUNCTION total_comenzi
        (v_cod_promotional Comenzi.cod_promotional%TYPE)
    RETURN NUMBER IS
        v_total NUMBER;
    BEGIN
        select sum(p.pret * cp.cantitate) into v_total 
        from Comenzi c 
        join comanda_contine_produse cp on (c.id_comanda = cp.id_comanda)
        join Produse p on (p.id_produs = cp.id_produs)
        where c.cod_promotional = v_cod_promotional;
        RETURN v_total;
    END total_comenzi;
    
END proiect_bhd_2;

