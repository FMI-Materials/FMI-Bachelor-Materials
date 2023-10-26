# Laborator 5 - [JS] - Obiecte si functii

[JavaScript](https://ro.wikipedia.org/wiki/JavaScript) (JS) este unul dintre cele mai populare limbaje de programare din lume, fiind utilizat atat pe partea de client ([browser](https://en.wikipedia.org/wiki/Web_browser)) cat si pe partea de server ([NodeJs](https://nodejs.org/en/)).

## Exercitiul 5.1

Intr-un document HTML, link-uiti cate un fisier JavaScript pentru fiecare exercitiu de mai jos (_ex1.js_, _ex2.js_ etc.).

## Exercitiul 5.2

### Care sunt oamenii care v-au influentat viata?

- Creati un obiect care sa contina informatiile unei persoane ce v-a influentat viata. Obiectul trebuie sa contina: `nume` (string), `varsta` (number) si `calitati` (array of strings).
- Afisati in consola pe linii separate (cate un `console.log` pentru fiecare linie), informatiile persoanei, ca mai jos:

```JS
Gabriela Boboc
Varsta: 50
Calitati:
Empatica
Sincera
Iubitoare de animale
```

## Exercitiul 5.3

### E ca IMDB-ul, dar mult mai mic...

- Creati un obiect care sa contina informatiile unui film favorit. Obiectul trebuie sa includa `titlu` (string), `durata` (number) si `actori` (array of strings).
- Creati o functie care sa primeasca ca parametru obiectul de mai sus si sa printeze in consola informatiile filmului favorit, ca mai jos:

```bash
"La Moara cu noroc" a durat 130 minute. Actori: Constantin Codrescu, Olga Tudorache, Geo Barton"
```

## Exercitiul 5.4

### E Black Friday!

- Creati o functie care sa primeasca ca parametru obiectul corespunzator cosului de cumparaturi si sa returneze valoarea totala a acestuia, ca in exemplul de mai jos:

```JS
// Input
var blackFridayCart = {
  telefon: "350",
  consola: "250",
  televizor: "450",
  iepurasPlus: "10.60",
  cercei: "20.34",
  geanta: "22.36"
};

// Output
getCartValue(blackFridayCart); // 1103.3
```

## Exercitiul 5.5

### Map

- Implementati functia _[map](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array/map)_, astfel incat aceasta sa se comporte ca mai jos:

```JS
function multiplicator(element) {
    return 2 * element;
}

Array.prototype.myMap = function(callbackFunction) {
  let newArray = [];
  ...
  return newArray
}

[1,2,3].map(multiplicator); // [2,4,6]
[1,2,3].myMap(multiplicator); // [2,4,6]
```
