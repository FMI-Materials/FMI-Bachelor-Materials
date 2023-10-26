cod_dezvoltator -> nume_dezvoltator

cod_proiect -> denumire_proiect, cod_sef_proiect, nume_sef_proiect, buget, data_inceput_priect, data_limita_proiect

cod_sef_proiect -> nume_sef_proiect

cod_task -> descriere_task, data_incepere_task, durata_zile


**Este deja in FN1**

* Participare(cod_dezvoltator#, nume_dezvoltator, cod_proiect#, denumire_proiect, cod_sef_proiect, nume_sef, proiect, buget, data_inceput_proiect, data_limita_proiect, cod_task#, descriere_task, data_incepere_task, durata_zile)

**FN2**

* Participare(cod_dezvoltator#, cod_proiect#, cod_task#)
* Dezvoltator(cod_dezvoltator#, nume_dezvoltator)
* Proiect(cod_proiect#, denumire_proiect, cod_sef_proiect, nume_sef, proiect, buget, data_inceput_proiect, data_limita_proiect)
* Task(cod_task#, descriere_task, data_incepere_task, durata_zile)

**FN3**

* Participare(cod_dezvoltator#, cod_proiect#, cod_task#)
* Dezvoltator(cod_dezvoltator#, nume_dezvoltator)
* SefProiect(cod_sef#, nume_sef)
* Proiect(cod_proiect#, denumire_proiect, cod_sef_proiect, proiect, buget, data_inceput_proiect, data_limita_proiect)
* Task(cod_task#, descriere_task, data_incepere_task, durata_zile)





**BOYCE_CODD?**

aplicatie  ----> |--| --> username 
persoana   ----> |--|       |
     ^----------------------|


(aplicatie#, username)
(username#, persoana)

persoana(cod_persoana#, cnp, data_nastere)




* 2

**A**

* Zbor -> ISA comercial
       -> ISA pasager
* Aeroport
* Avion
* Companie
* Angajat -> ISA pilot
          -> ISA insotitor
* Rezervare
* Pasager
* Echipaj

**B**

* Aeroport(aeroport_id#, nume, locatie)
* Zbor(zbor_id#, avion_id, echipaj_id, data, plecare_id, sosire_id, companie_id, tip)
* Avion(avion_id#, nume_avion)
* Companie(companie_id#, nume_companie)
* Angajat(angajat_id#, nume, companie_id, tip)
* Rezervare(id_rezervare#, id_pasager, id_zbor, loc)
* Pasager(id_pasager#, nume)
* Echipaj(id_echipaj#, nume_echipaj)
* EsteInEchipaj(echipaj_id#, angajat_id#)


**C**

* Aeroport(aeroport_id#, nume, locatie)
* Zbor(zbor_id#, avion_id@, echipaj_id@, data, plecare_id, sosire_id, companie_id@, tip)
* Avion(avion_id#, nume_avion)
* Companie(companie_id#, nume_companie)
* Angajat(angajat_id#, nume, companie_id@, tip)
* Rezervare(id_rezervare#, id_pasager@, id_zbor@, loc)
* Pasager(id_pasager#, nume)
* Echipaj(id_echipaj#, nume_echipaj)
* EsteInEchipaj(echipaj_id#@, angajat_id#@)


**D**

Z_2019 = SELECT(Zbor, an(data) = 2019)
Aeroport_Londra = SELECT(Aeroport, locatie='Londra')
Z = SEMI-JOIN(Z_2019, Aeroport_Londra,
        	aeroport_id = sosire_id)
R = JOIN(Rezervare, Z, zbor_id = id_zbor)
ANS = SEMI-JOIN(Pasager, R, id_pasager)

Nu este optim.
De exemplu, putem sa facem R = PROJECT(R, id_pasager).
Aeroport_Londra putea sa fie PROJECT(..., aeroport_id)








**ALT SUBIECT**

**1**

* Participare(cod_student#, nume_student, cod_profesor#, nume_profesor, cod_curs#, titlu_curs, an_universitar, semestru, zi_saptamana, sala, ora_incepere, durata) 

**DEPENDENTE**

1. cod_student -> nume_student
2. cod_profesor -> nume_profesor
3. cod_curs -> titlu_curs, an_universitar, semestru, zi_saptamana, sala, ora_incepere, durata
3. semestru -> an_universitar

**FN1**

* Participare(cod_student#, nume_student, cod_profesor#, nume_profesor, cod_curs#, titlu_curs, an_universitar, semestru, zi_saptamana, sala, ora_incepere, durata) 

**FN2**

* Participare(cod_student#, cod_profesor#, cod_curs#) 
* Student(cod_student#, nume_student)
* Profesor(cod_profesor#, nume_profesor)
* Curs(cod_curs#, titlu_curs, an_universitar, semestru, zi_saptamana, sala, ora_incepere, durata)

**FN3**

* Participare(cod_student#, cod_profesor#, cod_curs#) 
* Student(cod_student#, nume_student)
* Profesor(cod_profesor#, nume_profesor)
* Curs(cod_curs#, titlu_curs, zi_saptamana, sala, ora_incepere, durata)
* Semestru(semestru#, an_universitar)

ESTE IN BOYCE-CODD



*****************
**EX2** 

**a**

* Serviciu
* Incident
* Abonament
* Angajat -> ISA operator
	  -> ISA tehnician
* EchipaInterventie
* Client

**b**

* Serviciu(serviciu_id#, tip)
* serviciu_inclus(serviciu_id#, abonament_id#)
* Abonament(abonament_id#, data_lansare)
* abonament_achizitionat(abonament_id#, client_id#)
* Client(client_id#, nume)
* Incident(id_incident#, abonament_id, client_id, defectiune, id_echipa, operator_id, verdict)
* EchipaInterventie(id_echipa#, nume, locatie)
* Operator(angajat_id#, nume)
* Tehnician(angajat_id#, echipa_id#)

**c**

Mda idk

**d**

Internet = SELECT(serviciu, tip='internet')
IDCuInternet = JOIN(Internet, serviciu_inclus)
AbonamenteCuI = SEMI-JOIN(Abonament, IDCuInternet)
P = SELECT(AbonamenteCuI, data_lansare = 2020)
P2 = JOIN(P, Incident)
ANS = SEMI-JOIN(client, P2)























