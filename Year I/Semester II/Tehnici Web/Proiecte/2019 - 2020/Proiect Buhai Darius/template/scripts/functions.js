var ctrlIsPressed = false;

function generate_child_from_template(template, data){
    let outer_template = document.createElement("div");
    template.hidden = false;
    template.removeAttribute("id");
    outer_template.appendChild(template);
    for (const [key, value] of Object.entries(data))
        outer_template.innerHTML = outer_template.innerHTML.split("[["+key+"]]").join(value);
    return outer_template.childNodes[0];
}

function http_get(theUrl, callback, json_data = true) {
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.onreadystatechange = function() {
        if (xmlHttp.readyState === 4 && xmlHttp.status === 200){
            if(!json_data) callback(xmlHttp.responseText);
            else callback(JSON.parse(xmlHttp.responseText));
        }
    };
    xmlHttp.open("GET", theUrl, true); // true for asynchronous
    xmlHttp.setRequestHeader("accepts", "application/json");
    xmlHttp.send(null);
}

async function http_get_async(theUrl, json_data = true){
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("GET", theUrl, false); // true for asynchronous
    xmlHttp.setRequestHeader("accepts", "application/json");
    xmlHttp.send(null);
    if (xmlHttp.readyState === 4 && xmlHttp.status === 200){
        if(!json_data) return xmlHttp.responseText;
        else return JSON.parse(xmlHttp.responseText);
    }
}

function http_post(theUrl, data, callback, isFormData = false) {
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.onreadystatechange = function() {
        if (xmlHttp.readyState === 4 && xmlHttp.status === 200){
            callback(xmlHttp.responseText);
        }
    };
    xmlHttp.open("POST", theUrl);
    if(isFormData){
        var formData = new FormData();
        for(const [key, value] of Object.entries(data))
            formData.append(key, value);
        xmlHttp.send(formData);
    }else{
        xmlHttp.setRequestHeader("Content-Type", "application/json;charset=UTF-8");
        xmlHttp.send(JSON.stringify(data));
    }
}

function http_put(theUrl, data, callback, isFormData) {
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.onreadystatechange = function() {
        if (xmlHttp.readyState === 4 && xmlHttp.status === 200){
            callback(xmlHttp.responseText);
        }
    };
    xmlHttp.open("PUT", theUrl);
    if(isFormData){
        var formData = new FormData();
        for(const [key, value] of Object.entries(data))
            formData.append(key, value);
        xmlHttp.send(formData);
    }else{
        xmlHttp.setRequestHeader("Content-Type", "application/json;charset=UTF-8");
        xmlHttp.send(JSON.stringify(data));
    }
}

function http_delete(theUrl, callback) {
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.onreadystatechange = function() {
        if (xmlHttp.readyState == 4 && xmlHttp.status == 200){
            callback(xmlHttp.responseText);
        }
    };
    xmlHttp.open("DELETE", theUrl);
    xmlHttp.send();
}

function toggle_hide_by_class(className, hide = true){
    let el = document.getElementsByClassName(className);
    for(let i=0;i<el.length;i++)
        el[i].hidden= hide;
}

function changed_image(input_id, image_id){
    let file = document.getElementById(input_id).value;
    let img = document.getElementById(image_id);

    var tgt = file.target || window.event.srcElement, files = tgt.files;

    if (FileReader && files && files.length) {
        var fr = new FileReader();
        fr.onload = function () {
            img.src = fr.result;
        };
        fr.readAsDataURL(files[0]);
    }
}

function toggle_expand_navbar(){
    let nav = document.getElementById("navbar");
    if(nav.classList.contains("expanded")){
        nav.classList.remove("expanded");
        return;
    }
    nav.classList.add("expanded");
}

function open_page(link){
    console.log(link);
    location.href = link;
}

function key_up_action(){
    ctrlIsPressed = false;
}

function key_down_action(){
    var evtobj = window.event? event : e;
    if (evtobj.keyCode === 91 || evtobj.keyCode===17){
        ctrlIsPressed = true;
        apply_markup();
    }
}

function ctrl_click_action(call1, call2) {
    if(ctrlIsPressed) call1();
    else call2();
}

function open_link(link){
    window.location = link;
}

/** Animations **/
function strip_transition_blockers(){
    var el = document.getElementsByClassName("no-transition");
    for(var i=0;i<el.length;i++)
        el[i].classList.remove("no-transition");
}

function toggle_bill_view(hide = true){
    if(hide){
        document.getElementById("bill-view").classList.add("hide");
        document.getElementById("bill-overlay").classList.add("hide");
        setTimeout(function(){
            document.getElementById("bill-view").hidden = true;
            document.getElementById("bill-overlay").hidden = true;
        }, 300);
    }else{
        document.getElementById("bill-view").classList.remove("hide");
        document.getElementById("bill-overlay").classList.remove("hide");
        document.getElementById("bill-view").hidden = false;
        document.getElementById("bill-overlay").hidden = false;
    }
}

/** Modal actions **/
var opened_modal_id = "";

function show_generated_modal(modal_id, modal){
    opened_modal_id = modal_id;
    modal.id = modal_id;
    modal.hidden = false;
    document.getElementsByTagName("body")[0].appendChild(modal);
    document.getElementById("modal-overlay").hidden = false;
}

function show_modal(modal_id, modal_generator){
    let modal_template = document.getElementById(modal_id+"-template").cloneNode(true);
    if(modal_generator){
        modal_generator(modal_template, function(modal){
            show_generated_modal(modal_id, modal);
        });
    }else show_generated_modal(modal_id, modal_template);
}

function hide_modal(modal_id=null){
    if(modal_id==null) modal_id = opened_modal_id;
    document.getElementById(modal_id).classList.add("hide");
    document.getElementById("modal-overlay").classList.add("hide");
    setTimeout(function(){
        document.getElementById("modal-overlay").classList.remove("hide");
        document.getElementById(modal_id).remove();
        document.getElementById("modal-overlay").hidden = true;
    }, 300);
}