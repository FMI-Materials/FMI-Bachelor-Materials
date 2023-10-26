function get_bill(callback = null){
    try{
        if(window.localStorage.getItem("bill")!=null)
            bill = JSON.parse(window.localStorage.getItem('bill'));
    }catch (e) {
        bill = {};
    }
    var bill_item_template = document.getElementById("bill-item-template");
    var bill_template = document.getElementById("bill");
    bill_template.innerHTML = "";

    let size = 0;

    toggle_hide_by_class("add-bill-button", false);
    toggle_hide_by_class("added-bill-button");

    for (const [key, value] of Object.entries(bill)){
        size++;
        toggle_hide_by_class("add-bill-button-"+key);
        toggle_hide_by_class("added-bill-button-"+key, false);

        http_get("product/"+key, function(product){
            let bill_item = generate_child_from_template(bill_item_template.cloneNode(true), {
                name: product.name,
                image: "images/"+product.image,
                price: product.price,
                quantity: value,
                id: key
            });
            bill_template.appendChild(bill_item);
        });
    }

    if(size===0){
        document.getElementById("bill-button").disabled= true;
        document.getElementById("bill-button-count").innerText = "";
    }
    else {
        document.getElementById("bill-button").disabled= false;
        document.getElementById("bill-button-count").innerText = "("+size+")";
    }

    if(callback) callback();
}

function add_to_bill(product_id, qty = 1){
    try{
        if(window.localStorage.getItem("bill")!=null)
            bill = JSON.parse(window.localStorage.getItem('bill'));
    }catch (e) {
        bill = {};
    }
    console.log(bill);
    bill[product_id] = qty;

    window.localStorage.setItem("bill", JSON.stringify(bill));
    get_bill();
}

function remove_from_bill(product_id){
    try{
        if(window.localStorage.getItem("bill")!=null)
            bill = JSON.parse(window.localStorage.getItem('bill'));
    }catch (e) {
        bill = {};
    }
    delete bill[product_id];

    window.localStorage.setItem("bill", JSON.stringify(bill));
    get_bill();
}