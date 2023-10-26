function reqListener() {
    var data = JSON.parse(this.responseText);

    var ul = document.createElement("ul");
    console.log(data);
    for(var i=0;i<data.length;i++){
        var li = document.createElement("li");
        var p = document.createElement("p");
        p.innerText = data[i]["name"];
        var img = document.createElement("img");
        img.src = data[i]["img"];
        li.appendChild(p);
        li.appendChild(img);
        ul.appendChild(li);
    }
    document.getElementsByTagName("body")[0].appendChild(ul);

}

function reqError(err) {
    console.log('Fetch Error :-S', err);
}

var oReq = new XMLHttpRequest();
oReq.onload = reqListener;
oReq.onerror = reqError;
oReq.open('get', 'http://localhost:3000/dogs', true);
oReq.send();