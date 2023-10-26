const fs = require("fs");

class Ratings {

    get(product_id) {
        let ratings = JSON.parse(fs.readFileSync("data/ratings.json"));
        if(ratings[product_id]==null) return 0;
        var tot = 0, nr = 0;
        for(const [criteria, values] of Object.entries(ratings[product_id]))
            for(const [ip, rating] of Object.entries(values)){
                tot+=rating;
                nr++;
            }
        if(nr===0) return 0;
        return Math.round(tot/nr);
    }

    get_by_criteria(product_id, criteria) {
        let ratings = JSON.parse(fs.readFileSync("data/ratings.json"));
        if(ratings[product_id]==null) return 0;
        if(ratings[product_id][criteria]==null) return 0;
        var tot = 0, nr = 0;
        for(const [ip, rating] of Object.entries(ratings[product_id][criteria])){
            tot+=rating;
            nr++;
        }
        if(nr===0) return 0;
        return Math.round(tot/nr);
    }

    /// post and update
    post(ip, product_id, criteria, value) {
        var ratings = JSON.parse(fs.readFileSync("data/ratings.json"));
        if(ratings[product_id]==null) ratings[product_id] = new Object();
        if(ratings[product_id][criteria]==null) ratings[product_id][criteria] = new Object();
        var found = false;
        ratings[product_id][criteria][ip]=value;
        fs.writeFileSync("data/ratings.json", JSON.stringify(ratings));
        return ratings;
    }
}

module.exports = Ratings;