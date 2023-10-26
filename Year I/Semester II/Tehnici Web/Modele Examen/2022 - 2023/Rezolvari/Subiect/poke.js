window.onload = () => {
    draw();

    let listElement = document.getElementById("list");
    listElement.style.visibility = "hidden";

    const canvas = document.getElementById("canvas");
    canvas.addEventListener("click", showPokemon);

    const url = "poke.json";
    var promise = fetch(url);
    let possanswers;

    promise.then((response) =>
    {
        if (!response.ok)
        {
            throw new Error(`HTTP error: ${response.status}`);
        }
        return response.text();
    })
    .then((text) =>
    {
        possanswers = JSON.parse(text);
    })
    .catch((err) =>
    {
        alert(err);
    });

    function draw() {
        const canvas = document.getElementById("canvas");
        if (canvas.getContext) 
        {
            const ctx = canvas.getContext("2d");

            ctx.fillStyle = "black";
            ctx.beginPath();
            ctx.arc(100, 100, 100, 0, 360);
            ctx.fill();

            ctx.fillStyle = "red"
            ctx.beginPath();
            ctx.arc(95, 95, 85, 1 * Math.PI, 0);
            ctx.fill();
            ctx.arc(105, 95, 85, 1 * Math.PI, 0);
            ctx.fill();

            ctx.fillStyle = "white"
            ctx.beginPath();
            ctx.arc(95, 105, 85, 0, 1 * Math.PI);
            ctx.fill();
            ctx.arc(105, 105, 85, 0, 1 * Math.PI);
            ctx.fill();

            ctx.fillStyle = "black";
            ctx.beginPath();
            ctx.arc(100, 100, 40, 0, 360);
            ctx.fill();

            ctx.fillStyle = "white";
            ctx.beginPath();
            ctx.arc(100, 100, 30, 0, 360);
            ctx.fill();
        }
    }

    function showPokemon()
    {
        let max = possanswers.length;
        let ans = Math.floor(Math.random() * max);
        let pokemonName = possanswers[ans].name;

        let x = Number(sessionStorage.getItem(pokemonName));
        if (x) 
        {
            sessionStorage.setItem(pokemonName, x + 1);
        } 
        else 
        {
            sessionStorage.setItem(pokemonName, "1");
        }
        let infoElement = document.getElementById("info");
        infoElement.innerHTML = pokemonName + ", I choose you! (" + (x + 1);
        if (x)
        {
            infoElement.innerHTML += " selections)";
        }
        else
        {
            infoElement.innerHTML += " selection)";
        }
        infoElement.style.marginTop = "20px";

        let imageElement = document.getElementsByTagName("img")[0];
        imageElement.src = possanswers[ans].image;
        imageElement.alt = pokemonName;
        imageElement.style.marginTop = "10px";
        imageElement.addEventListener("mouseover", () =>
        {
            let lines = document.getElementsByClassName("line");
            lines[0].innerHTML = "Level: " + possanswers[ans].level;
            lines[1].innerHTML = "Abilities: " + possanswers[ans].ability;
            listElement.style.visibility = "visible";
        });
        imageElement.addEventListener("mouseout", () =>
        {
            listElement.style.visibility = "hidden";
        });
    }
};