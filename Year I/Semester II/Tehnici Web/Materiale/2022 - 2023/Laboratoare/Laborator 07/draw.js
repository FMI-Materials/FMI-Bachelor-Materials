function drawTable(nrows, ncols) 
{
    var container = document.getElementById("container");
    var table = document.createElement("table");
    table.id = "table";
    for (let i = 0; i < nrows; ++i)
    {
        var row = document.createElement("tr");
        for (let j = 0; j < ncols; ++j)
        {
            var cell = document.createElement("td");
            cell.classList.add("r" + i);
            cell.classList.add("c" + j);
            cell.style.border = "1px solid black";
            cell.style.width = "20px";
            cell.style.height = "20px";
            row.appendChild(cell);
        }
        table.appendChild(row);
    }
    container.appendChild(table);
}

function colorCol(column, color) 
{
    var c = document.getElementsByClassName("c" + column);
    for (let i = 0; i < c.length; ++i)
    {
        c[i].style.backgroundColor = color;
    }
}

function colorRow(row, color) 
{
    var r = document.getElementsByClassName("r" + row);
    for (let i = 0; i < r.length; ++i)
    {
        r[i].style.backgroundColor = color;
    }
}

function rainbow(target) 
{
    let colors = ["rgb(255, 0, 0)", "rgb(255, 154, 0)", "rgb(240, 240, 0)", "rgb(79, 220, 74)", "rgb(63, 218, 216)", "rgb(47, 201, 226)", "rgb(28, 127, 238)", "rgb(95, 21, 242)", "rgb(186, 12, 248)", "rgb(251, 7, 217)"];
    for (let i = 0; i < colors.length; ++i)
    {
        if (target == "row")
        {
            colorRow(3 * i, colors[i]);
            colorRow(3 * i + 1, colors[i]);
            colorRow(3 * i + 2, colors[i]);
        }
        else
        {
            colorCol(3 * i, colors[i]);
            colorCol(3 * i + 1, colors[i]);
            colorCol(3 * i + 2, colors[i]);
        }
    }
}

function getNthChild(element, n) 
{
    var children = element.children;
    if (children.length < n)
    {
        return null;
    }
    return children[n - 1];
}

function drawPixel(row, col, color) 
{
    document.querySelector(".r" + row + ".c" + col).style.backgroundColor = color;
}

function drawLine(r1, c1, r2, c2, color) 
{
    if (r1 == r2)
    {
        for (let i = c1; i <= c2; ++i)
        {
            drawPixel(r1, i, color);
        }
    }
    else if (c1 == c2)
    {
        for (let i = r1; i <= r2; ++i)
        {
            drawPixel(i, c1, color);
        }
    }
}

function drawRect(r1, c1, r2, c2, color)
{
    for (let i = r1; i <= r2; ++i)
    {
        drawLine(i, c1, i, c2, color);
    }
}

function drawPixelExt(row, col, color) 
{
    var table = document.getElementById("table");
    var rows = table.children;
    if (rows.length <= row)
    {
        for (let i = rows.length; i <= row; ++i)
        {
            var newRow = document.createElement("tr");
            for (let j = 0; j < table.children[0].children.length; ++j)
            {
                let newCell = document.createElement("td");
                newCell.classList.add("r" + i);
                newCell.classList.add("c" + j);
                newCell.style.border = "1px solid black";
                newCell.style.width = "20px";
                newCell.style.height = "20px";
                newRow.appendChild(newCell);
            }
            table.appendChild(newRow);
        }
    }
    for (let i = 0; i < rows.length; ++i)
    {
        var cells = rows[i].children;
        if (cells.length <= col)
        {
            for (let j = cells.length; j <= col; ++j)
            {
                let newCell = document.createElement("td");
                newCell.classList.add("r" + i);
                newCell.classList.add("c" + j);
                newCell.style.border = "1px solid black";
                newCell.style.width = "20px";
                newCell.style.height = "20px";
                rows[i].appendChild(newCell);
            }
        }
    }
    drawPixel(row, col, color);
}

function colorMixer(colorA, colorB, amount) {
    let cA = colorA * (1 - amount);
    let cB = colorB * (amount);
    return parseInt(cA + cB);
}

function drawPixelAmount(row, col, color, amount) 
{
    let cell = document.querySelector(".r" + row + ".c" + col);
    if (amount == 1)
    {
        cell.style.backgroundColor = color;
    }
    else if (amount != 0)
    {
        var oldColorArray = getComputedStyle(cell).backgroundColor.match(/\d+/g);
        var newColorArray = color.match(/\d+/g);
        var x = colorMixer(oldColorArray[0], newColorArray[0], amount);
        var y = colorMixer(oldColorArray[1], newColorArray[1], amount);
        var z = colorMixer(oldColorArray[2], newColorArray[2], amount);
        cell.style.backgroundColor = "rgb(" + x + ", " + y + ", " + z + ")";
    }
}

function delRow(row) 
{
    var table = document.getElementById("table");
    var rows = table.children;
    if (rows.length <= row)
    {
        return;
    }
    for (let i = row + 1; i < rows.length; ++i)
    {
        var cells = rows[i].children;
        for (let j = 0; j < cells.length; ++j)
        {
            cells[j].classList.remove("r" + i);
            cells[j].classList.add("r" + (i - 1));
        }
    }
    table.removeChild(rows[row]);
}

function delCol(col) 
{
    var table = document.getElementById("table");
    var rows = table.children;
    for (let i = 0; i < rows.length; ++i)
    {
        var cells = rows[i].children;
        if (cells.length <= col)
        {
            return;
        }
        for (let j = col + 1; j < cells.length; ++j)
        {
            cells[j].classList.remove("c" + j);
            cells[j].classList.add("c" + (j - 1));
        }
        rows[i].removeChild(cells[col]);
    }
}

function shiftRow(row, pos) 
{   
    var table = document.getElementById("table");
    var cells = table.children[row].children;
    for (let i = cells.length - 1; i > 0; --i)
    {
        var aux = cells[i].style.backgroundColor;
        cells[i].style.backgroundColor = cells[(i + pos) % cells.length].style.backgroundColor;
        cells[(i + pos) % cells.length].style.backgroundColor = aux;
    }
}

function jumble()
{
    var table = document.getElementById("table");
    var rows = table.children;
    for (let i = 0; i < rows.length; ++i)
    {
        var rand = Math.floor(Math.random() * rows.length);
        shiftRow(i, rand);
    }
}

function transpose() 
{   
    var table = document.getElementById("table");
    var rows = table.children;
    var newTable = document.createElement("table");
    newTable.id = "table";
    for (let i = 0; i < rows.length; ++i)
    {
        var newRow = document.createElement("tr");
        for (let j = 0; j < rows.length; ++j)
        {
            let newCell = document.createElement("td");
            newCell.classList.add("r" + i);
            newCell.classList.add("c" + j);
            newCell.style.border = "1px solid black";
            newCell.style.width = "20px";
            newCell.style.height = "20px";
            newRow.appendChild(newCell);
        }
        newTable.appendChild(newRow);
    }
    for (let i = 0; i < rows.length; ++i)
    {
        var cells = rows[i].children;
        for (let j = 0; j < cells.length; ++j)
        {
            var color = cells[j].style.backgroundColor;
            let newCell = newTable.querySelector(".r" + j + ".c" + i);
            newCell.style.backgroundColor = color;
        }
    }
    table.parentNode.replaceChild(newTable, table);
}


function flip(node) 
{
    const children = [];
    while (node.childNodes.length > 0) 
    {
        children.push(node.childNodes[0]);
        node.removeChild(node.childNodes[0]);
    }
    for (let i = children.length - 1; i >= 0; --i) 
    {
        node.appendChild(children[i]);
    }
}

function mirror() {
    /*
       15. Oglindiți pe orizontală tabla de desenat: luați jumătatea stângă a tablei, 
       aplicați-i o transformare flip și copiați-o în partea dreaptă a tablei.
    */
}

function smear(row, col, amount) {
    /*
       16. Întindeți culoarea unei celule de pe linia 'row' și coloana 'col' în celulele
       învecinate la dreapta, conform ponderii date de 'amount' (valoare între 0 și 1).
       Cu colorarea fiecărei celule la dreapta, valoarea ponderii se înjumătățește. 
       Hint: folosiți funcția 'drawPixelAmount'.
    */
}

window.addEventListener("load", 
    function() 
    {
        let colorPicker = document.querySelector("#color-picker");
        colorPicker.value = "#0000ff";
        colorPicker.addEventListener("change");
    },
    false);

window.onload = function() 
{
    const rows = 30;
    const cols = 30;
    drawTable(rows, cols);

    // Lab 8
    {   
        document.body.onclick = draw_pixel;
        function draw_pixel(event) 
        {
            var pos = event.target.classList;
            var x = pos[0].substring(1);
            var y = pos[1].substring(1);
            drawPixel(x, y, document.querySelector("#color-picker").value);
        }
        // when clicking the button rainbow, call function rainbow
        document.querySelector("#rainbow").onclick = rainbow;
        document.querySelector("#jumble").onclick = jumble;
        document.querySelector("#rotate").onclick = transpose;
        document.querySelector("#clear").onclick = function() 
        {
            document.querySelectorAll("td").forEach((el) => el.style.backgroundColor = "white");
        }
    }

    // Lab 7
    // {
    //     drawPixel(2, 1, "red");
    //     drawPixel(1, 1, "red");
    //     drawLine(2, 2, 4, 2, "green");
    //     drawRect(6, 6, 8, 8, "blue");
    //     var rand1 = Math.floor(Math.random() * 35), rand2 = Math.floor(Math.random() * 35);
    //     drawPixelExt(rand1, rand2, "orange");
    //     var rand3 = Math.random();
    //     drawPixelAmount(5, 0, "rgb(100, 100, 100)", rand3);
    //     if (rand3 <= 0.5)
    //     {
    //         delRow(6);
    //         delCol(6);
    //         drawPixel(6, 6, "red");
    //     }
    //     shiftRow(7, 2);
    //     flip(document.getElementById("table"));
    //     for (let i = 0; i < 30; ++i)
    //     {
    //         flip(document.getElementById("table").children[i]);
    //     }
    //     transpose();
    // }
};