var dogs;

async function addEditEntity(){
    var name = document.getElementsByName("name")[0].value;
    var img = document.getElementsByName("img")[0].value;

    console.log(name, img);

    var idl = "";
    var action = "post";
    var id = document.getElementsByName("id")[0].value;

    console.log(id);
    if(id != ""){
        idl = "/"+id;
        action = "put";
    }

    var oReq = new XMLHttpRequest();
    oReq.onload = reqListener;
    oReq.onerror = reqError;
    await oReq.open(action, 'http://localhost:3000/dogs'+idl, false);
    await oReq.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    await oReq.send("img="+img+"&name="+name);

    location.reload();
}

function prepareEditEntity(id){
    document.getElementsByName("name")[0].value = dogs[id]["name"];
    document.getElementsByName("img")[0].value = dogs[id]["img"];
    document.getElementsByName("id")[0].value = dogs[id]["id"];
    document.getElementById("cancel_button").hidden = false;
    document.getElementById("add_button").innerText = "edit";
}

function cancelEditEntity(){
    document.getElementsByName("name")[0].value = "";
    document.getElementsByName("img")[0].value = "";
    document.getElementsByName("id")[0].value = "";
    document.getElementById("cancel_button").hidden = true;
    document.getElementById("add_button").innerText = "add";
}

async function deleteEntity(id){
    console.log(dogs[id]["id"]);
    var oReq = new XMLHttpRequest();
    oReq.onload = reqListener;
    oReq.onerror = reqError;
    await oReq.open('delete', 'http://localhost:3000/dogs/'+dogs[id]["id"], false);
    await oReq.send();

    location.reload();
}

function reqListener() {
    dogs = JSON.parse(this.responseText);

    var ul = document.createElement("ul");
    console.log(dogs);
    for(var i=0;i<dogs.length;i++){
        var li = document.createElement("li");
        var p = document.createElement("p");
        var edit = document.createElement("d");
        var del = document.createElement("d");
        del.innerHTML = "<button onclick='deleteEntity("+i+")'>delete</button>";
        edit.innerHTML = "<button onclick='prepareEditEntity("+i+")'>edit</button>";
        p.innerText = dogs[i]["name"];
        var img = document.createElement("img");
        img.src = dogs[i]["img"];
        p.appendChild(del);
        p.appendChild(edit);
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