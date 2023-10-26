const fs = require("fs");
const formidable = require('formidable');

const categories = require("./categories");

class Products {

    get(category = null, id = null) {
        let data = JSON.parse(fs.readFileSync("data/products.json"));
        if(id!=null) return data[id];
        if(category===null) return data;
        var products = [];
        for(var i=0;i<data.length;i++)
            if(data[i].category===category){
                data[i].id = i;
                products.push(data[i]);
            }
        return products;
    }

    delete(id){
        let products = this.get();
        if(products.length>id){
            let current_category = products[id].category;

            delete products[id];
            products.splice(id, 1);
            fs.writeFileSync("data/products.json", JSON.stringify(products));

            let exists = false;
            for(var i=0;i<products.length;i++)
                if(products[i].category===current_category)
                    exists = true;
            if(!exists)
                categories.prototype.delete(current_category);

        }
        return products;
    }

    post(req, res){
        var products = this.get();
        var form = new formidable.IncomingForm();

        form.parse(req, function (err, fields, files) {

            if(files.hasOwnProperty("image")){
                var oldpath = files.image.path;
                var newpath = 'data/images/' + files.image.name;
                fs.rename(oldpath, newpath, function (err) {
                    if (err) console.log(err);
                });
            }

            var new_product = {};
            if(fields.hasOwnProperty("name")) new_product.name = fields.name;
            if(fields.hasOwnProperty("description")) new_product.description = fields.description;
            if(fields.hasOwnProperty("price")) new_product.price = fields.price;
            if(fields.hasOwnProperty("category")) new_product.category = fields.category;
            if(files.hasOwnProperty("image")) new_product.image = files.image.name;
            if(fields.hasOwnProperty("ingredients")) new_product.ingredients = fields.ingredients;
            if(fields.hasOwnProperty("vegan")) new_product.vegan = fields.vegan;

            if(!categories.prototype.get().includes(new_product.category)){
                console.log("adding new");
                categories.prototype.post(new_product.category);
            }

            products.push(new_product);
            fs.writeFileSync("data/products.json", JSON.stringify(products));

            res.send(new_product);
        });
    }

    put(id, req, res){

        let products = this.get();
        var form = new formidable.IncomingForm();

        form.parse(req, function (err, fields, files) {

            if(files.hasOwnProperty("image") && files.image!=null){
                var oldpath = files.image.path;
                var newpath = 'data/images/' + files.image.name;
                fs.rename(oldpath, newpath, function (err) {
                    if (err) console.log(err);
                });
            }

            var new_product = {};
            if(fields.hasOwnProperty("name")) products[id].name = fields.name;
            if(fields.hasOwnProperty("description")) products[id].description = fields.description;
            if(fields.hasOwnProperty("price")) products[id].price = fields.price;
            if(fields.hasOwnProperty("category")) products[id].category = fields.category;
            if(fields.hasOwnProperty("ingredients")) products[id].ingredients = fields.ingredients;
            if(fields.hasOwnProperty("vegan")) products[id].vegan = fields.vegan;
            if(files.hasOwnProperty("image") && files.image!=null) products[id].image = files.image.name;

            if(!categories.prototype.get().includes(products[id].category)){
                categories.prototype.post(products[id].category);
            }

            fs.writeFileSync("data/products.json", JSON.stringify(products));

            res.send(products[id]);
        });
    }

}

module.exports = Products;