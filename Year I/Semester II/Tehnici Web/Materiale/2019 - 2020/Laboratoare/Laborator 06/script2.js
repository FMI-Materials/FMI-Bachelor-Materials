var filme = [
    {
        "titlu": "La Casa de Papel",
        "durata": 220,
        "actori": "John",
        "vizionat": true
    },
    {
        "titlu": "Into the storm",
        "durata": 180,
        "actori": "John",
        "vizionat": true
    }
];

let ul = document.createElement("ul");
for(var i=0;i<filme.length;i++){
    let li =  document.createElement("li");
    let p1 = document.createElement("p");
    p1.innerText = filme[i].titlu;
    li.appendChild(p1);
    let p2 = document.createElement("p");
    p2.innerText = "Durata: "+filme[i].durata;
    li.appendChild(p2);
    let p3 = document.createElement("p");
    p3.innerText = "Actori: "+filme[i].actori;
    li.appendChild(p3);
    let p4 = document.createElement("p");
    p4.innerText = "Vizionat: "+(filme[i].vizionat ? "Da" : "Nu");
    li.appendChild(p4);
    ul.appendChild(li);
}
document.getElementsByTagName("body")[0].appendChild(ul);