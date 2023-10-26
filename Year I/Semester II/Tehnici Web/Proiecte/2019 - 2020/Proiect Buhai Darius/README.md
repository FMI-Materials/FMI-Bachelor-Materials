# Waitee

## Proiect TW
### Link: https://waiteeapp.herokuapp.com/
### Tema: Construiti o aplicatie web care respecte criteriile de acceptanta si cerintele de mai jos. Tematica site-ului este la libera alegere.

## Cerinte suplimentare:
  - [x] **II.1** Varsta utilizator. Va exista in pagina, la inceput, un singur input in care un utilizator isi poate trece data nasterii sub forma zi#luna#an (de exemplu 20#03#2001). La click pe un buton se va afisa imediat sub input varsta utilizatoului in ani, luni si zile, ore minute secunde ( de exemplu: 19 ani 3 luni si 4 zile, 12 ore 15 minute 4 secunde).  Afisajul varstei se va actualiza la fiecare secunda.
  - [x] **IV.2** (Site comercial, Node) Posibilitatea de a da un rating unor produse. Ratingul s-ar face in felul urmator. Utilizatorul are 3 criterii pentru care da note de la 1 la N (de exemplu N=5). Pentru fiecare produs, pentru fiecare criteriu se afiseaza ratingul mediu (media notelor primite de la fiecare utilizator, pentru fiecare criteriu), cat si media generala - media tuturor notelor indiferent de criterii. De exemplu, pentru un utilizator care a dat notele N1,N2,N3 pe cele 3 criterii si un utilizator cu notele N4,N5,N6 pe cele 3 criterii, media total ar fi (N1+N2+N3+N4+N5+N6)/6 dar media pe fiecare criteriu ar fi (N1+N4)/2, (N2+N5)/2, (N3+N6)/2). Un utilizator nu poate da doua ratinguri.
  - [x] **IV.4** Posibilitatea de a marca portiuni din text (asa cum se face cu markerul pe un text tiparit) si salvarea acelor marcaje in localStorage pentru a le gasi in aceeasi forma la reintrarea in pagina. Zonele marcate ar aparea cu o culoare de background si de text diferita. Marcajul se face selectand textul (pentru simplitate se va marca doar text care nu contine alte taguri, precum elemente b, i, a, etc) si apoi apasand o combinatie de taste care sa salveze textul ca fiind marcat (se va inlocui bucata de text cu un element de tip <mark> avand contintul egal cu cel al textului selectat). Indicatii: la mouseup, sau keyup se verifica daca e vreun text selectat cu window.getSelection() si document.selection.createRange().text. Mai multe informatii utile la: https://javascript.info/selection-range
  - [x] **V.3**  Generarea de pagini pe baza unui template incarcand datele dintr-un json/xml/tabel din baza de date. De exemplu requestul ar fi de forma /pagina?id=nr, unde nr e id-ul produsului(din json) si ar contine datele acelui produs. Nu se vor scrie fisiere separate pentru fiecare produs, ci se va face un template cu campuri completate prin program, pe baza id-ului din query string cu datele din JSON. Campurile trebuie sa contina: un titlu, o descriere de minim 2 paragrafe, o imagine, o enumerare de elemente (de exemplu cuvinte cheie care descriu produsul), un camp numeric, unul boolean, una sau mai multe trimiteri catre id-urile altor produse (aceste trimiteri se vor afisa sub forma de linkuri catre paginile acelor produse). Trebuie sa existe minim 10 astfel de produse in fisierul de date.
  - [x] **V.4** (Node) Sa se realizeze operatia de logging (memorarea intr-un fisier in format ales de studenti a actiunilor importante (in special de modificare a datelor din site) facute de utilizatori (trebuie minim 4 tipuri de actiuni: de exemplu vizualizare, adaugare, stergere, modificare). Intr-un camp al fisierului de log ar trebui memorate: numele utilizatorului, data si ora la care s-a petrecut actiunea, informatii despre actiune (de exemplu, "[10/02/2020, 08:34:25] ]utilizatorul ion.popescu a sters produsul 2345 din baza de date.")

### Criterii de acceptanta:

- [x] aplicatia sa fie Single Page Application
- [x] codul sursa (nearhivat) al proiectului trebuie sa fie salvat pe GitHub
- [x] nu puteti folosi librarii, framework-uri CSS sau JavaScript (cum ar fi jQuery, Bootstrap, Angular, React, etc) pentru realizarea frontend-ului
***Atentie! Orice proiect care nu respecta criteriile de acceptanta este evaluat la 0 puncte.***

## Frontend (maxim 17 puncte)
### HTML si CSS (maxim 8 puncte)
- [x] Fisiere separate pentru HTML si CSS (0.5 puncte)
- [x] In interiorul documentelor HTML, sa se foloseasca minim 4 taguri semantice (1 punct)
- [x] Stilurile CSS sa fie definite folosind clase direct pe elementele care trebuie stilizate (minim 80% din selectori) (0.5 punct)
- [x] Layout-ul sa fie impartit in minim 2 coloane si sa fie realizat cu Flexbox si/sau CSS grid (2 puncte)
- [x] Site-ul sa fie responsive, respectand rezolutiile urmatoarelor dispozitive folosind media queries: (4 puncte)
  - telefon mobil - latime mai mica 768px
  - tableta - latime intre 768px si 1280px
  - desktop - latime mai mare de 1280px
### Javascript (maxim 9 puncte)
- [x] Fisier separat JavaScript (0.5 puncte)
- [x] Manipularea DOM-ului (crearea, editarea si stergerea elementelor/nodurilor HTML) (3 puncte)
- [x] Folosirea evenimentelor JavaScript declansate de mouse/tastatura (1 punct)
- [x] Utilizarea AJAX (GET, POST, PUT, DELETE) (4 puncte)
- [x] Folosirea localStorage (0.5 puncte)
### Backend API (maxim 8 puncte)
- [x] Creare server Backend (2 puncte)
- [x] CRUD API (Create, Read, Update si Delete) pentru a servi Frontend-ului (6 puncte)

### Punctaj subiectiv (maxim 5 puncte)
***Ne vom imagina ca aplicatia trebuie prezentata unui client, care va aprecia, de exemplu:***

- calitatea sustinerii prezentarii proiectului
- designul (sa arate placut si ingrijit)
- utilitatea (sa rezolve probleme reale)
- stabilitatea (sa NU contina defecte evidente)
- complexitatea (sa aiba mai multe ecrane, layout-ul sa fie mai complex etc.)

### Requirements:
 - node.js
 - express
 - path
 - fs
 - body-parser
 - formidable
 - moment
