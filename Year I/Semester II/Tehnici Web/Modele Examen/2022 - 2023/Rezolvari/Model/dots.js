window.onload = () => 
{
    localStorage.clear();
    document.body.addEventListener("keydown", keyDownListener);
    let print = document.createElement('div');
    print.setAttribute("id", "print");
    document.body.appendChild(print);
    let range = document.createElement('input');
    range.type = "range";
    range.id = "range";
    range.min = "20";
    range.max = "150";
    range.value = "20";
    document.body.appendChild(range);

    function keyDownListener(event) 
    {
        let thedot = document.createElement('div');
        thedot.style.borderRadius = "50%";
        thedot.style.display = "inline-block";
        thedot.style.position = "absolute";
        thedot.className = "dot";

        let w = window.innerWidth;
        let h = window.innerHeight;
        let posx = Math.floor(Math.random() * w);
        let posy = Math.floor(Math.random() * h);
        thedot.style.left = posx + "px";
        thedot.style.top = posy + "px";

        let size = document.getElementById("range").value;
        thedot.style.height = size + "px";
        thedot.style.width = size + "px";

        switch (event.key) 
        {
            case "r":
                thedot.style.backgroundColor = "red";
                break;
            case "g":
                thedot.style.backgroundColor = "green";
                break;
            case "b":
                thedot.style.backgroundColor = "#6495ED";
                break;
            case "y":
                thedot.style.backgroundColor = "yellow";
                break;
            default:
                return;
        }
        document.body.appendChild(thedot);
        let x = Number(localStorage.getItem("nodots"));
        if (x) 
        {
            localStorage.setItem("nodots", x + 1);
        } 
        else 
        {
            localStorage.setItem("nodots", "1");
        }
        document.getElementById("print").innerHTML = localStorage.getItem("nodots");

        function createNewDot()
        {
            let color = thedot.style.backgroundColor;
            let width = thedot.style.width;
            let height = thedot.style.height;

            let newDot = document.createElement('div');
            newDot.style.backgroundColor = color;
            newDot.style.width = width;
            newDot.style.height = height;
            newDot.style.borderRadius = "50%";
            newDot.style.display = "inline-block";
            newDot.style.position = "absolute";
            
            let w = window.innerWidth;
            let h = window.innerHeight;
            let posx = Math.floor(Math.random() * w);
            let posy = Math.floor(Math.random() * h);
            newDot.style.left = posx + "px";
            newDot.style.top = posy + "px";
            document.body.appendChild(newDot);
            let x = Number(localStorage.getItem("nodots"));
            if (x) 
            {
                localStorage.setItem("nodots", x + 1);
            } 
            else 
            {
                localStorage.setItem("nodots", "1");
            }
            document.getElementById("print").innerHTML = localStorage.getItem("nodots");
            newDot.addEventListener("click", createNewDot);
        }

        thedot.addEventListener("click", createNewDot);
    }
};