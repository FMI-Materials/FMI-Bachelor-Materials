const fs = require("fs");

class Categories {

    get() {
        let data = JSON.parse(fs.readFileSync("data/categories.json"));
        return data;
    }

    post(name) {
        let data = this.get();
        data.push(name);
        fs.writeFileSync("data/categories.json", JSON.stringify(data));
        return data;
    }

    delete(name){
        console.log("Deleting: "+name);
        let data = this.get();
        data.splice(data.indexOf(name), 1);
        fs.writeFileSync("data/categories.json", JSON.stringify(data));
        return data;
    }
}

module.exports = Categories;