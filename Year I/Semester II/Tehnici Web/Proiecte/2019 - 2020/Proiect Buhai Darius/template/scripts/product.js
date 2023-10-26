/**
 * Generare pagina pe baza de template
 * Task 5 - P3
 * 2.5 pct
 */

async function get_product(callback = null){
    let product_id = window.location.search.replace("?id=","");
    http_get("/product/"+product_id, async function(data){
        var product_template = document.getElementById("product-details-template");
        var product_section = document.getElementById("product-section");
        product_section.innerHTML = "";

        let rating1 = await get_rating(product_id, 1);
        let rating2 = await get_rating(product_id, 2);
        let rating3 = await get_rating(product_id, 3);
        let ratingt = await get_rating(product_id);
        var description = data["description"];
        if(marked_products && marked_products.hasOwnProperty(product_id)){
            var new_description = description.slice(0,marked_products[product_id].from);
            new_description += "<mark>";
            new_description += description.slice(marked_products[product_id].from, marked_products[product_id].to);
            new_description += "</mark>";
            new_description += description.slice(marked_products[product_id].to, description.length);
            description = new_description;
        }
        let ingredients_list = "";
        let ingredients_arr = data["ingredients"].split(",");
        for(var i=0;i<ingredients_arr.length;i++)
            ingredients_list+="<li>"+ingredients_arr[i]+"</li>";
        var template_data = {
            title: data["name"],
            description: description,
            image: "images/"+data["image"],
            price: data["price"],
            category: data["category"],
            ingredients: ingredients_list,
            vegan: data["vegan"]?"DA":"NU",
            id: product_id
        };
        for(var i=1;i<=4;i++)
            for(var j=1;j<=5;j++){
                var v = 0;
                if(i===1) v = rating1;
                if(i===2) v = rating2;
                if(i===3) v = rating3;
                if(i===4) v = ratingt;
                template_data["rating_"+i+"_"+j] = (v>=j ? "active" : "");
            }
        let generated_product = generate_child_from_template(product_template.cloneNode(true), template_data);
        product_section.appendChild(generated_product);
        if(callback!==null)
            callback(data);
    });
}

function init_product_details(){
    page_type = "product";
    get_products_markup(false);
    get_product(function (product){
        selected_category = product["category"];
        get_products(function(){
            get_bill();
        });
    });
}

init_product_details();