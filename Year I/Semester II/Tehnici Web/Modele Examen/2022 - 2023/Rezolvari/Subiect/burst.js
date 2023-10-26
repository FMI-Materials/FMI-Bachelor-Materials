function drawTable(nrows, ncols) 
{
    function popBubble(object)
    {
        if (object.src.endsWith("0.jpg"))
        {
            object.src = "Images/bubble1.jpg";
            let random = 1 + Math.floor(Math.random() * 3);
            let audio = document.createElement("audio");
            audio.src = "Audio/bubble" + random + ".mp3";
            audio.play();

            let x = Number(localStorage.getItem("count"));
            if (x) 
            {
                localStorage.setItem("count", x + 1);
            } 
            else 
            {
                localStorage.setItem("count", "1");
            }
            countElement.innerHTML = x + 1;
            return true;
        }
        return false;
    }

    function createBubble(row, column)
    {
        let bubble = document.createElement("img");
        bubble.src = "Images/bubble0.jpg";
        bubble.style.width = "60px";
        bubble.classList.add("r" + row);
        bubble.classList.add("c" + column);
        return bubble;
    }

    localStorage.clear();

    let countElement = document.getElementById("count");
    countElement.innerHTML = "0";

    let table = document.createElement("table");
    table.id = "table";
    for (let i = 0; i < nrows; ++i)
    {
        let row = document.createElement("tr");
        row.classList.add("row");
        for (let j = 0; j < ncols; ++j)
        {
            let bubble = createBubble(i, j);
            row.appendChild(bubble);

            bubble.addEventListener("click", () =>
            {
                popBubble(bubble);
            });
        }
        table.appendChild(row);
    }

    document.addEventListener("keydown", (event) => 
    {
        function reset()
        {
            let deletedRow = document.getElementsByClassName("row")[0];
            table.removeChild(deletedRow);

            let newRow = document.createElement("tr");
            for (let i = 0; i < 10; ++i)
            {
                let bubble = createBubble(5, i);
                newRow.appendChild(bubble);

                bubble.addEventListener("click", () =>
                {
                    popBubble(bubble);
                });

                table.appendChild(newRow);
            }
        }

        function hasPoppedBubble(row)
        {
            for (bubble of row.children)
            {
                if (bubble.src.endsWith("1.jpg"))
                {
                    return true;
                }
            }
            return false;
        }

        function getLastIndexWithPoppedBubble()
        {
            let count = 1;
            let index = 1;
            for (row of table.children)
            {
                if (hasPoppedBubble(row))
                {
                    index = count;
                }
                ++count;
            }
            return index;
        }

        if (event.key == "b")
        {
            let randomRow = Math.floor(Math.random() * 6);
            let randomCol = Math.floor(Math.random() * 10);
            let bubbleElement = document.getElementsByClassName("r" + randomRow + " c" + randomCol)[0];
            while (!popBubble(bubbleElement))
            {
                randomRow = Math.floor(Math.random() * 6);
                randomCol = Math.floor(Math.random() * 10);
                bubbleElement = document.getElementsByClassName("r" + randomRow + " c" + randomCol)[0];
            }
        }
        if (event.key == "r")
        {
            let counter = 0;
            let maxCounter = getLastIndexWithPoppedBubble();
            const intervalId = setInterval(() => 
            {
                reset();
                ++counter;
                if (counter === maxCounter) 
                {
                    clearInterval(intervalId);
                }
            }, 500);
        }
    });

    document.body.appendChild(table);
}

window.onload = () =>
{
    drawTable(6, 10);
};