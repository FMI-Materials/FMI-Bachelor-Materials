window.onload = () =>
{
    draw();

    const canvas = document.getElementById("canvas");
    canvas.addEventListener("click", answer);

    const url = 'magic.json';
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

    function draw()
    {
        const canvas = document.getElementById("canvas");
        if (canvas.getContext)
        {
            const ctx = canvas.getContext("2d");
            ctx.fillStyle = "black";
            ctx.beginPath();
            ctx.arc(100, 100, 100, 0, 360);
            ctx.fill();

            ctx.fillStyle = "white";
            ctx.beginPath();
            ctx.arc(100, 100, 50, 0, 360);
            ctx.fill();

            ctx.fillStyle = "black";
            ctx.font = "70px sans-serif";
            ctx.fillText("8", 82, 125, 50); 
        }
    }

    function answer()
    {
        let max = possanswers.length;
        let ans = Math.floor(Math.random() * max);
        let color = "green";
        if (possanswers[ans].bool == "no")
        {
            color = "red";
        }
        else if (possanswers[ans].bool == "maybe")
        {
            color = "orange";
        }
        const canvas = document.getElementById("canvas");
        if (canvas.getContext)
        {
            const ctx = canvas.getContext("2d");
            ctx.fillStyle = "black";
            ctx.beginPath();
            ctx.arc(100, 100, 100, 0, 360);
            ctx.fill();

            ctx.fillStyle = color;
            ctx.beginPath();
            ctx.arc(100, 100, 50, 0, 360);
            ctx.fill();
        }

        let infoDiv = document.getElementById("info");
        infoDiv.innerHTML = possanswers[ans].text;
        infoDiv.style.color = color;
    }
}