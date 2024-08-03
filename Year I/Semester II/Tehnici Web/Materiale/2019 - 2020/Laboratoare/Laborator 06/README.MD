# Laborator 6 - [JS] - DOM

DOM ([Document Object Model](https://developer.mozilla.org/en-US/docs/Web/API/Document_Object_Model/Introduction)) este o interfata de programare (API) a aplicatiilor care trateaza un document HTML, XHTML sau XML ca o structura de arbore in care fiecare nod este un obiect reprezentand o parte a documentului. Obiectele pot fi manipulate in mod programat, cu ajutorul [functiilor DOM](https://www.impressivewebs.com/10-essential-dom-methods-techniques-for-practical-javascript/), iar eventualele schimbari vizibile aparute in urma executarii lor pot fi reflectate in afisarea documentului.

## Exercitiul 6.1

### Hack Google

- Deschideti [google.com](https://www.google.com) in Chrome sau Firefox si afisati consola.
- Gasiti logo-ul Google si stocati-l intr-o variabila.
- Modificati sursa imaginii (url-ul) astfel incat sa apara logo-ul de la Yahoo. Puteti cauta url-ul logo-ului de la Yahoo intr-un motor de cautare.
- Gasiti butonul de search Google si stocati-l intr-o variabila.
- Modificati textul buttonului astfel incat sa scrie Yahoo.

## Exercitiul 6.2

### Toate site-urile ar trebui sa aiba o sectiune "Despre noi"

- Creati un document HTML (_aboutme.html_) cu template-ul de mai jos inclus in `<body>`:

```html
<h1>About Me</h1>
<ul>
  <li>Nickname: <span id="nickname"></span></li>
  <li>Favorites: <span id="favorites"></span></li>
  <li>Hometown: <span id="hometown"></span></li>
</ul>
```

- Creati un fisier JavaScript `script.js` si legati-l de documentul HTML folosind `<script>` la sfarsitul acestuia.
- Schimbati stilul din `<body>` astfel incat sa avem font-family: _Arial, sans-serif_.
- Inlocuiti ficare `<span>` (_nickname, favorites, hometown_) cu informatiile voastre.
- Iterati prin fiecare `<li>` si adaugati clasa _list-item_.
- Creati un fisier CSS (conectati-l la document) cu stilurile necesare clasei _list-item_ pentru a avea un text rosu.
- Creati un nou element `<img>` cu atributul `src` catre o imagine cu voi. Adaugati acel element in pagina.

## Exercitiul 6.3

### My IMDB

- Creati un document HTML (_filme.html_) cu titlul "Filmele mele favorite:", folosind tag-ul `<h1>`.
- Creati un fisier JavaScript `script.js` si legati-l de documentul HTML folosind `<script>` la sfarsitul acestuia.
- Creati un vector cu obiecte care sa contina informatiile filmelor favorite. Obiectul trebuie sa includa _titlu_ (string), _durata_ (number), _actori_ (array of strings) si o propietate de tip boolean care sa indice daca filmul a fost vizualizat sau nu.
- Iterati prin vector si creati dinamic (folosind `document.createElement`) in pagina elemente `<p>` care sa contina titlul filmului.

### Bonus

- Folositi `<ul>` si `<li>` pentru a afisa filmele, alaturi de celelalte informatii despre acestea.
- Adaugati in fiecare obiect din vector o proprietate reprezentand imaginea filmului si reflectati schimbarea in pagina.
- Adaugati proprietati CSS care sa diferentieze filmele vizualizate de cele nevizualizate din lista.
