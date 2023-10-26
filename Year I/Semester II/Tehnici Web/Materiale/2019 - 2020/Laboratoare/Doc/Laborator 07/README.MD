# Laborator 7 - [JS] - Evenimente

[Evenimentele](https://developer.mozilla.org/en-US/docs/Web/Events) in JavaScript sunt actiuni sau intamplari care sunt declansate de utilizator sau de browser.
Sunt multe tipuri de evenimente care sunt chemate, iar cateva dintre ele sunt:

- utilizatorul da click pe un element din pagina;
- utilizatorul pune cursorul pe un element din pagina;
- utilizatorul apasa o tasta de la tastatura;
- utilizatorul modifica marimea ferestrei browser-ului sau o inchide;
- un formular a fost trimis (submitted);
- pagina s-a terminat de incarcat;
- a aparut o eroare;

Programatorii Javascript obisnuiesc sa foloseasca des expresii precum: “event-loop”, “non-blocking”, “callback”, “asynchronous”, “single-threaded” si “concurrency”. Pentru a ne familiariza cu aceste notiuni, propun sa urmarim urmatorul video:
[Philip Roberts: What the heck is the event loop anyway? | JSConf EU 2014](https://www.youtube.com/watch?v=8aGhZQkoFbQ&t=420s).

## Exercitiul 7.1

### Povesti de calatorie

- Creati un document HTML (_calatorii.html_) cu template-ul de mai jos inclus in `<body>`:

```html
<h1>Povesti de calatorie</h1>

<ul>
  <li>Locuri vizitate: <input type="text" id="places" /></li>
  <li>Adjective: <input type="text" id="adjective" /></li>
  <li>Nume: <input type="text" id="person" /></li>
</ul>

<button id="story-button">Creaza povestea!</button>

<div id="story"></div>
```

- Creati un fisier JavaScript `script.js` si legati-l de documentul HTML folosind `<script>` la sfarsitul acestuia.
- Adaugati un _event listener_ butonului astfel incat de fiecare data cand este apasat functia `makeStory` sa fie apelata.
- In functia `makeStory` executati urmatoarele actiuni:

  - luati valorile din input-uri;
  - creati o poveste cu ajutorul lor (ex: "Diana a vizitat frumoasa Barcelona");
  - afisati povestea in tag-ul identificat prin id-ul _story_;

## Exercitiul 7.2

### Calculator

- Creati un document HTML (_calculator.html_) cu template-ul de mai jos inclus in `<body>`:

```html
<label
  >1. Ridicare la patrat:
  <input type="number" id="square-input" size="2" />
</label>
<button id="square-button">Calculeaza</button>
<br /><br />

<label
  >2. Jumatate din numar:
  <input type="number" id="half-input" size="2" />
</label>
<button id="half-button">Calculeaza</button>
<br /><br />

<label>
  3. Procent:
  <input type="number" id="percent1-input" size="2" />
</label>
<label>
  Numar:
  <input type="number" id="percent2-input" size="2" />
</label>
<button id="percent-button">Calculeaza</button>
<br /><br />

<label
  >4. Aria unui cerc cu raza:
  <input type="number" id="area-input" size="2" />
</label>
<button id="area-button">Calculeaza</button>
<br /><br />
<div id="solution"></div>
```

- Creati un fisier JavaScript `script.js` si legati-l de documentul HTML folosind `<script>` la sfarsitul acestuia.
- Adaugati evenimente pe butoane astfel incat de fiecare data cand sunt apasate sa cheme functiile de calcul.
- Creati functiile care returneaza rezultatele corecte pentru toate cazurile de mai sus.
- Afisati rezultatele calculelor in tag-ul identificat prin id-ul _solution_.

- Folositi evenimentul _keypress_ pe unul dintre input-uri astfel incat utilizatorul sa nu fie nevoit sa dea click pe buton.

## Exercitiul 7.3

### Catelus cu parul cret

- Creati un document HTML (_index.html_) cu template-ul de mai jos inclus in `<body>`:

```html
<div id="buttons">
  <button id="start-button">Start</button>
  <button id="speed-button">Go Faster!</button>
  <button id="stop-button">Stop</button>
</div>
<div id="info"></div>
<img
  style="position:absolute; left: 0px; top: 80px;"
  src="https://raw.githubusercontent.com/WebToLearn/laborator-tehnici-web/master/doc/laborator-7/dog.gif"
/>

<script>
  var movePixels = 10; // number of pixels
  var delayMs = 50; // number of miliseconds
  var dogTimer = null;

  // Move the image on screen with 10px
  function dogWalk() {
    var img = document.getElementsByTagName("img")[0];
    var currentLeft = parseInt(img.style.left);
    img.style.left = currentLeft + movePixels + "px";
    // reset image position to start
    if (currentLeft > window.innerWidth - img.width) {
      img.style.left = "0px";
    }
  }

  // Call dogWalk function every 50 ms
  function startDogWalk() {
    dogTimer = window.setInterval(dogWalk, delayMs);
  }
</script>
```

- Mutati script-ul din documentul HTML intr-un fisier separat.
- Adaugati un eveniment pe butonul _Start_ si creati functia pentru a porni miscarea catelului.
- Adaugati un eveniment pe butonul _Stop_ si creati functia pentru a opri miscarea catelului.
- Adaugati un eveniment pe butonul _Go Faster!_ si creati functia pentru a mari viteza de miscare a catelului.
- Afisati in tag-ul identificat prin id-ul _info_ viteza de miscare, calculata in pixeli pe secunda (Viteza: 300px/secunda).
- Creati dinamic butonul _Reset speed_ cu id-ul _reset-button_.
- Adaugati un eveniment pe butonul _Reset speed_ si creati functia pentru a reseta viteza.
- Simulati functionalitatea de expirare a sesiunii astfel incat dupa 30 secunde de inactivitate (nu a fost apasat niciun buton) sa fie afisata o alerta cu mesajul "Sesiune expirata". Folositi functia _setTimeout_.
- Dezactivati butonul _Start_ folosind atributul _disabled_ atunci cand catelul este in miscare;

## Exercitiul 7.4

### Catelus cu parul cret eXtreme

- Folositi _[Object literal pattern](https://addyosmani.com/resources/essentialjsdesignpatterns/book/#modulepatternjavascript)_ pentru a rescrie exerciutul anterior.
