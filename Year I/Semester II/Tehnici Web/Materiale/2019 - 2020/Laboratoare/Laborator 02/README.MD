# Laborator 2 - [CSS] - Introducere

CSS sau `Cascading Style Sheets` este limbajul descriptiv ce se foloseste pentru stilizarea documentului HTML (paginii web):

![CSS Rules](https://www.teaching-materials.org/css/img/cssrule.png)

```CSS
body {
  color: #333333;
}

nav {
  background-color: #ddd;
}

.container {
  margin: 0 auto;
}

.container .medium  {
  padding: 0 30px 25px 5px;
}

h1, h2, h3 {
  color: #000;
}

nav {
  background-color: #fff;
}
```

Iata cum adaugam stiluri paginilor web:

```HTML
<!-- Inline Style -->
<tag style="property: value;">
```

```HTML
<!-- Embedded Style -->
<head>
  <style type="text/css">
    selector { property: value; }
  </style>
</head>
```

```HTML
<!-- External Style Sheet -->
<head>
  <link rel="stylesheet" type="text/css" href="style.css" />
</head>
```

Pentru a invata mai usor proprietatile CSS putem folosi un [Cheat Sheet](css-cheat-sheet.pdf).

## Exercitiul 2.1

[CSS Diner](https://flukeout.github.io/) ne ajuta sa invatam selectorii CSS. Hai sa ne jucam!

## Exercitiul 2.2

Creati un document HTML (_cv.html_) cu markup-ul de mai jos si 2 fisiere CSS (_style.css_ si _resume-style.css_) care vor contine stilurile.

```HTML
<!DOCTYPE html>
<html lang="en">

<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <meta http-equiv="X-UA-Compatible" content="ie=edge">
  <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/normalize/7.0.0/normalize.min.css">
  <link rel="stylesheet" href="style.css">
  <link rel="stylesheet" href="resume-style.css">
  <title>Resume</title>
</head>

<body>
  <header class="header">
    <h1 class="title">SUNNY LUTHRA</h1>
    <h2 class="subtitle">Animator / Photographer</h2>
  </header>
  <nav class="menu">
    <a class="menu-item" href="index.html"><i class="fa fa-user"></i> About me</a>
    <a class="menu-item menu-item-active" href="resume.html"><i class="fa fa-file-text"></i> Resume</a>
    <a class="menu-item" href="portfolio.html"><i class="fa fa-heart"></i> Portfolio</a>
    <a class="menu-item" href="contact.html"><i class="fa fa-envelope"></i> Contact</a>
  </nav>
  <div class="resume-container">
    <main class="resume-content">
      <!-- Work Experience -->
      <section>
        <h2 class="resume-title">Work Experience</h2>
        <div class="resume-info">
          <h3 class="resume-subtitle">Freelance web designer</h3>
          <div class="resume-date">
            <time datetime="2009">2009</time> - <time datetime="2010">2010</time>
          </div>
        </div>
        <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aliquam sodales urna non odio egestas tempor. Nunc
          vel vehicula ante.</p>
        <hr>
        <div class="resume-info">
          <h3 class="resume-subtitle">Python Programmer</h3>
          <div class="resume-date">
            <time datetime="2010">2010</time> - <time datetime="2011">2011</time>
          </div>
        </div>
        <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aliquam sodales urna non odio egestas tempor. Nunc
          vel vehicula ante.</p>
        <hr>
        <div class="resume-info">
          <h3 class="resume-subtitle">Social Media Lunatic</h3>
          <div class="resume-date">
            <time datetime="2011">2011</time> - <time datetime="2012">2012</time>
          </div>
        </div>
        <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aliquam sodales urna non odio egestas tempor. Nunc
          vel vehicula ante.</p>
        <hr>
        <div class="resume-info">
          <h3 class="resume-subtitle">Being Awesome</h3>
          <div class="resume-date">
            <time datetime="2011">2011</time> - <time datetime="2019">2019</time>
          </div>
        </div>
        <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aliquam sodales urna non odio egestas tempor. Nunc
          vel vehicula ante.</p>
        <hr>
      </section>
      <!-- Education -->
      <section>
        <h2 class="resume-title">Education</h2>
        <div class="resume-info">
          <h3 class="resume-subtitle">NoUse School</h3>
          <div class="resume-date resume-date--green">
            <time datetime="2001">2001</time> - <time datetime="2002">2002</time>
          </div>
        </div>
        <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aliquam sodales urna non odio egestas tempor. Nunc
          vel vehicula ante.</p>
        <hr>
        <div class="resume-info">
          <h3 class="resume-subtitle">Super Useless College</h3>
          <div class="resume-date resume-date--green">
            <time datetime="2002">2002</time> - <time datetime="2008">2008</time>
          </div>
        </div>
        <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aliquam sodales urna non odio egestas tempor. Nunc
          vel vehicula ante.</p>
        <hr>
      </section>
    </main>
    <aside class="resume-aside">
      <h2 class="resume-title">Skills</h2>
      <h3 class="resume-subtitle">Software</h3>
      <ul class="skills">
        <li class="skills-item"><span class="skills-bg photoshop">Photoshop</span></li>
        <li class="skills-item"><span class="skills-bg ilustrator">Ilustrator</span></li>
        <li class="skills-item"><span class="skills-bg indesign">InDesign</span></li>
        <li class="skills-item"><span class="skills-bg xd">Xd</span></li>
        <li class="skills-item"><span class="skills-bg sketch">Sketch</span></li>
        <li class="skills-item"><span class="skills-bg office">Microsoft Office</span></li>
        <li class="skills-item"><span class="skills-bg linux">Linux</span></li>
      </ul>
      <h3 class="resume-subtitle">Design</h3>
      <ul class="skills">
        <li class="skills-item"><span class="skills-bg user">User</span></li>
        <li class="skills-item"><span class="skills-bg typography">Typography</span></li>
        <li class="skills-item"><span class="skills-bg web">Web Applications</span></li>
      </ul>
      <h3 class="resume-subtitle">Programming Language</h3>
      <ul class="skills">
        <li class="skills-item"><span class="skills-bg html">HTML/CSS</span></li>
        <li class="skills-item"><span class="skills-bg php">PHP/MySql</span></li>
        <li class="skills-item"><span class="skills-bg javascript">jQuery/JavaScript</span></li>
        <li class="skills-item"><span class="skills-bg ruby">Ruby</span></li>
        <li class="skills-item"><span class="skills-bg python">Python</span></li>
      </ul>
    </aside>
  </div>
</body>

</html>
```

Pentru inceput, adaugam urmatoarele stiluri in _style.css_:

```CSS
* {
    box-sizing: border-box;
}

html {
    font-family: 'Open Sans', sans-serif;
    color: #555;
}

body {
    background: url('https://raw.githubusercontent.com/WebToLearn/personal-page-css-workshop/master/img/background.jpg');
    background-repeat: no-repeat;
    background-attachment: fixed;
    background-position: center center;
    background-size: cover;
}

.header {
    margin-top: 30px;
}

.resume-container {
  background: white;
  width: 990px;
  margin: 0 auto 30px auto;
  padding: 30px 20px;
  border: 1px solid #f1f1f1;
  box-shadow: 0px 6px #c0392b;
  border-radius: 0px 0px 4px 4px;
  display: flex;
}

```

La finalul tuturor exercitiilor pagina trebuie sa arate asemanator cu imaginea de mai jos:

![Design website personal - resume](personal-website-resume.png)

## Exercitiul 2.3

Aplicati in pagina voastra fonturile `Open Sans` si `Lato`, folosind [Google Fonts](https://fonts.google.com/).

## Exercitiul 2.4

Stilizati titlul paginii astfel incat sa aiba urmatoarele proprietati:

- marginea sa fie `0`
- tipul fontului sa fie `Lato`
- marimea fontului sa fie de `38px`
- grosimea fontului sa fie `700`
- textul sa fie scris numai cu litere mari
- textul sa fie aliniat la centru

## Exercitiul 2.5

Stilizati subtitlul paginii astfel incat sa aiba urmatoarele proprietati:

- culoarea textului sa fie `#999`
- marginea de jos sa fie de `1em`
- tipul fontului sa fie `Lato`
- marimea fontului sa fie de `1.5em`
- distanta intre randuri sa fie de `1em`
- textul sa fie scris numai cu litere mari
- textul sa fie aliniat la centru

## Exercitiul 2.6

Stilizati meniul de navigare astfel incat sa aiba urmatoarele proprietati:

Containerul meniului:

- lungimea sa fie de `990px`
- marginile sa fie de `80px auto 0 auto`
- textul sa fie aliniat la centru

Optiunile din meniu:

- elementul sa fie de tip `inline-block`
- marginea din dreapta sa fie de `10px`
- marginea din stanga sa fie de `20px`
- padding-ul sa fie de `10px 40px 10px 40px`
- fundalul sa fie alb
- scoateti _text-decoration_
- grosimea fontului sa fie `bold`
- textul sa fie scris numai cu litere mari
- tipul fontului sa fie `Lato`
- marimea fontului sa fie de `14px`
- culoarea sa fie `#999`
- alinierea verticala sa fie la baza de jos

Optiune meniu activa:

- pozitia sa fie relativa
- elementul sa fie mai jos cu `1px` (_buttom_: `-1px`)
- culoarea sa fie `#c0392b`
- padding-ul sa fie de `15px 40px 15px 40px;`
- marginea de sus sa fie `0`

## Exercitiul 2.7

Stilizati tag-ul `<hr>` astfel incat sa aiba urmatoarele proprietati:

- marginea de sus si de jos sa fie de `25px`
- border-ul sa fie de `1px`, `solid` si sa aiba culoarea `#f1f1f1`

## Exercitiul 2.8

Stilizati sectiunea _Experienta profesionala_ si _Educatie_.

## Exercitiul 2.9

Stilizati sectiunea _Aptitudini_.
> Puteti imbunatati design-ul barii de aptitudini folosind `background` si `linear-gradient`, ca in exemplul urmator: 

```CSS
.skills-bg:before {
  content: "";
  position: absolute;
  top: 0;
  left: 0;
  bottom: 0;
  right: 0;
  background-image: linear-gradient(135deg,rgba(255,255,255,.15) 25%,transparent 25%,transparent 50%,rgba(255,255,255,.15) 50%,rgba(255,255,255,.15) 75%,transparent 75%,transparent); 
  background-size: 5rem 5rem;
  z-index: 1;
  border-top-right-radius: 8px;
  border-bottom-right-radius: 8px;
  border-top-left-radius: 20px;
  border-bottom-left-radius: 20px;
  overflow: hidden;
}
```
