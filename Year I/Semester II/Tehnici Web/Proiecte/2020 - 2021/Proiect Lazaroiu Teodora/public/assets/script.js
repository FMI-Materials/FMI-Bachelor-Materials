/* clasa "responsive" este adaugata la navigatie cand utilizatorul apasa pe iconita */
function myFunction()
{
    var x = document.getElementById("myTopnav");
    if (x.className === "nav")
    {
        x.className = x.className + " responsive";
    } else
    {
        x.className = "nav";
    }
}

/* functie pentru tranzitia pozelor din galerie */

function fadeIn(el, time)
{
    el.style.opacity = 0;
    el.style.display = "block";
  
    var last = +new Date();
    var fade = function()
        {
        el.style.opacity = +el.style.opacity + (new Date() - last) / time;
        last = +new Date();
    
        if (+el.style.opacity < 1)
        {
            (window.requestAnimationFrame && requestAnimationFrame(fade)) || setTimeout(fade, 20)
        }
    };
  
    fade();
}

function formular()
{
    const addAnswer = (ev)=>
    {
        /* opreste programul din a da submit la formular */
        ev.preventDefault();

        let answer = {
                        name: document.getElementById('name').value,
                        email: document.getElementById('email').value,
                        suggestions: document.getElementById('suggestions').value
                    }

        document.forms[0].reset();
        
        /* salvam raspunsurile in local storage */

        if (localStorage.getItem('MyAnswers') === null)
        {
            localStorage.setItem('MyAnswers', JSON.stringify(answer));
        }
        else
        {
            answers = localStorage.getItem("MyAnswers");
            localStorage.setItem('MyAnswers', answers + ", " + JSON.stringify(answer));
        }

        alert("The form has been successfully submitted");
    }
    document.addEventListener('DOMContentLoaded', () =>
    {
        document.getElementById('submit').addEventListener('click', addAnswer);
    });
}

formular();

/* functie ce permite randomizarea pozelor din galerie */
function gallery()
{

    var arr = new Array(24).fill(0);
    var interval = 300;
    
    for (i = 1; i <= 16; i++)
    {
        do
        {
            var x = Math.floor(Math.random() * 24) + 1;
        }
        while (arr[x] != 0) arr[x] = 1;

        document.getElementById("img" + i).src = "/public/assets/images/img" + x + ".jpg";

        fadeIn(document.getElementById("img" + i), interval);

        if (i % 4 == 0) interval = interval + 300;

    }
    setTimeout(gallery, 5000);
}

/* cand se apasa enter va incepe jocul */
window.addEventListener ('keyup', (e) =>
{
    if (e.key == 'Enter') game();
});

function game()
{
    /* este preluat highscore-ul din local storage */
    var highscore = localStorage.getItem("highscore");

    document.getElementById("highscore").innerHTML = "Highscore: " + highscore;

    var jet = document.getElementById("jet");
    var board = document.getElementById("board");

    /* la inceperea jocului se schimba fundalul si este adaugata o animatie */
    board.style.animation = "scroll-background 5s linear infinite";

    jet.style.visibility = "visible";
    
    board.style.background = "url(/public/assets/images/galaxy.jpg)";

    window.addEventListener("keydown", (e) =>
    {
        var left = parseInt(window.getComputedStyle(jet).getPropertyValue("left"));
        
        /* pentru a muta nava la stanga */
        if (e.key == "ArrowLeft" && left > 0)
        {
            jet.style.left = left - 10 + "px";
        }

        /* pentru a muta nava la dreapta */
        else if (e.key == "ArrowRight" && left <= 440)
        {
            jet.style.left = left + 10 + "px";
        }

        /* pentru a trage in pietre */
        if (e.key == "ArrowUp" || e.key == " ")
        {
            var bullet = document.createElement("div");
            bullet.classList.add("bullets");

            var movebullet = setInterval(() =>
            {
                var rocks = document.getElementsByClassName("rocks");

                for (var i = 0; i < rocks.length; i++)
                {
                    var rock = rocks[i];

                    if (rock != undefined)
                    {
                        var rockbound = rock.getBoundingClientRect();
                        var bulletbound = bullet.getBoundingClientRect();

                        /* conditie pentru a verifica daca am lovit o piatra */
                        /* daca da, aceasta trebuie distrusa */

                        if (bulletbound.left >= rockbound.left &&
                            bulletbound.right <= rockbound.right &&
                            bulletbound.top <= rockbound.top &&
                            bulletbound.bottom <= rockbound.bottom)
                        {
                            rock.parentElement.removeChild(rock);
                            
                            /* daca am distrus o piatra se va distruge si bullet-ul */
                            bullet.style.display = "none";

                            /* se actualizeaza punctajul */

                            document.getElementById("points").innerHTML = parseInt(document.getElementById("points").innerHTML) + 1;

                            var points = parseInt(document.getElementById("points").innerHTML);

                            //localStorage.setItem("highscore", 0); // linia se va rula doar daca se doreste resetarea highscore-ului

                            if (highscore < points)
                            {
                                localStorage.setItem("highscore", points);

                                document.getElementById("highscore").innerHTML = "Highscore: " + points;
                            }
                        }
                    }
                }

                board.appendChild(bullet);
                var bulletbottom = parseInt(window.getComputedStyle(bullet).getPropertyValue("bottom"));

                /* elementele bullet nu vor iesi in afara board-ului */
                if (bulletbottom >= 500)
                {
                    clearInterval(movebullet);
                }

                bullet.style.left = left + 5 + "px"; //bullet should always be placed at the top of my jet..!
                bullet.style.bottom = bulletbottom + 3 + "px";
            },10);
        }
    });

    var generaterocks = setInterval(() =>
    {
        var rock = document.createElement("div");
        rock.classList.add("rocks");

        /* selectam elementul "rock" pentru a il genera in pozitii diferite */
        var rockleft = parseInt(window.getComputedStyle(rock).getPropertyValue("left"));
        
        /* se genereaza o valoare intre 0 si 430 (marimea spatiului de joc mai putin marimea pietrei) */
        rock.style.left = Math.floor(Math.random() * 430) + "px";

        board.appendChild(rock);

    }, 1700);

    var moverocks = setInterval(() =>
    {
        var rocks = document.getElementsByClassName("rocks");

        if (rocks != undefined)
        {
            /* vom face pietrele sa se miste in jos */
            for (var i = 0; i < rocks.length; i++)
            {
                var rock = rocks[i];
                var rocktop = parseInt(window.getComputedStyle(rock).getPropertyValue("top"));
                
                /* daca o piatra atinge marginea de jos, jocul s-a terminat */
                if (rocktop >= 455)
                {
                    alert("Game Over");
                    clearInterval(moverocks);
                    window.location.reload();
                }

                rock.style.top = rocktop + 25 + "px";
            }
        }
    }, 450);
}