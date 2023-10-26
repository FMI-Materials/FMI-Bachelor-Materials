function calculate_square(){
    let v = document.getElementById("square-input").value;
    document.getElementById("solution").innerText = v*v;
}

function calculate_half(){
    let v = document.getElementById("half-input").value;
    document.getElementById("solution").innerText = v/2;
}

function calculate_percent(){
    let v1 = document.getElementById("percent1-input").value;
    let v2 = document.getElementById("percent2-input").value;
    document.getElementById("solution").innerText = v1/100 * v2;
}

function calculate_area(){
    let v = document.getElementById("area-input").value;
    document.getElementById("solution").innerText = v * v * 3.14;
}