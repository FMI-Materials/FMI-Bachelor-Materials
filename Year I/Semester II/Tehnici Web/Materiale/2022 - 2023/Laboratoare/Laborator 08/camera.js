function take_photo()
{
    const container = document.getElementById("container");
    const containerClone = container.cloneNode(true);
    containerClone.id = "container-clone";
    const audio = new Audio('screenshot.mp3');
    audio.play();
    const gallery = document.getElementById('gallery');
    gallery.insertBefore(containerClone, gallery.firstChild);
    if (gallery.children.length > 4) 
    {
        gallery.removeChild(gallery.lastChild);
    }
}

window.onload = function() 
{
    const img = document.querySelector("#vizor img");

    var x = -20;
    var y = -30;
    var maxX = 0;
    var maxY = 0;
    var minX = -1640;
    var minY = -1750;
    var scale = 1;

    document.addEventListener("keydown", (event) => 
    {
        if (event.key == "ArrowLeft" && x < maxX) 
        {
            x += Math.round(10 * scale);
        }
        else if (event.key == "ArrowUp" && y < maxY)
        {
            y += Math.round(10 * scale);
        }
        else if (event.key == "ArrowRight" && x > minX) 
        {
            x -= Math.round(10 * scale);
        }
        else if (event.key == "ArrowDown" && y > minY) 
        {
            y -= Math.round(10 * scale);
        }
        img.style.margin = y + "px 0 0 " + x + "px";
    });

    document.addEventListener("keydown", (event) => 
    {
        if (event.code === "Equal") 
        {
            if (scale < 2) 
            {
                scale += 0.05;
                maxX += 50;
                maxY += 50;
                minX -= 50;
                minY -= 50;
            }
        }
        else if (event.code === "Minus")
        {
            if (scale > 1) 
            {
                scale -= 0.05;
                maxX -= 50;
                maxY -= 50;
                minX += 50;
                minY += 50;
            }
        }
        img.style.transform = "scale(" + scale + ")";
        if (x > maxX) 
        {
            x = maxX;
        }
        else if (x < minX) 
        {
            x = minX;
        }
        if (y > maxY) 
        {
            y = maxY;
        }
        else if (y < minY) 
        {
            y = minY;
        }
        img.style.margin = y + "px 0 0 " + x + "px";
    });
    
    document.addEventListener("keydown", (event) =>
    {   
        if (event.key == "s") 
        {
            take_photo();
        }
        else if (event.key == "t") 
        {
            const countdown = document.createElement("div");
            countdown.style.color = "white";
            countdown.style.fontSize = "50px";
            countdown.style.position = "absolute";
            countdown.style.top = "50%";
            countdown.style.left = "50%";
            countdown.style.transform = "translate(-50%, -50%)";
            document.body.appendChild(countdown);
            let count = 5;
            function countdownFn() 
            {
                countdown.textContent = count;
                count--;
                if (count >= 0) 
                {   
                    setTimeout(countdownFn, 1000);
                } 
                else 
                {
                    document.body.removeChild(countdown);
                    take_photo();
                }
            }
            setTimeout(countdownFn, 0);
        }
        else if (event.key == 'b')
        {
            let counter = 0;
            const intervalId = setInterval(() => 
            {
                take_photo();
                counter++;
                if (counter === 4) 
                {
                  clearInterval(intervalId);
                }
            }, 500);
        }
    });
};
