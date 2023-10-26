
document.getElementsByTagName("body")[0].style.fontFamily = "Arial, sans-serif";

document.getElementById("nickname").innerText = "Darius";
document.getElementById("favorites").innerText = "Coding, Food, Tennis";
document.getElementById("hometown").innerText = "Galati";

let li = document.getElementsByTagName("li");
for(var i=0;i<li.length;++i)
    li[i].setAttribute("class", "list-item");

let img = document.createElement("img");
img.src = "https://www.descoperativocatia.ro/img/darius.jpg";
document.getElementsByTagName("body")[0].appendChild(img);