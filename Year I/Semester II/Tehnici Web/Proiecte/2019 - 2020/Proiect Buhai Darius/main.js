const express = require('express');
const path = require('path');
const fs = require('fs');
const bodyParser = require("body-parser");

const app = express();
const port = process.env.PORT || 3000;

const password = "heavypassword";

app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());
app.use(bodyParser.raw());

const products = require("./modules/products");
const categories = require("./modules/categories");
const logger = require("./modules/logger");
const ratings = require("./modules/ratings");

const _template_dir = __dirname+"/template";
const _images_dir = __dirname+"/data/images";

/** Link static files */
/* Template */
link_folder(_template_dir+"/scripts");
link_folder(_template_dir+"/images", true);
link_folder(_template_dir+"/fontawesome", true, "/fontawesome/");
link_path(_template_dir+"/style.css");

/* Data */
link_folder(_images_dir, true, "/images/");

/** General links */
app.get('/', function(req, res){
    res.sendFile(_template_dir+"/index.html");
});

app.get('/product', function(req, res){
    res.sendFile(_template_dir+"/product.html");
    /** Log action */
    logger.prototype.post(req.ip,"a vizualizat produsul cu id-ul "+req.params.id);
});

/** Data getters and setters */
/** Categories */
app.get('/categories', function(req,res){
    res.send(categories.prototype.get());
});

/*app.get('/categories/:id', function(req,res){
    res.send(categories.prototype.get(req.params.id));
});*/

app.delete('/categories/:name/:password', function(req,res){
    if(req.params.password!==password){
        res.send("Invalid auth params");
        return;
    }
    res.send(categories.prototype.delete(req.params.name));
});

/** Ratings */

app.get('/ratings/:product_id', function(req,res){
    res.send('"'+ratings.prototype.get(req.params.product_id)+'"');
});

app.get('/ratings/:product_id/:criteria', function(req,res){
    res.send('"'+ratings.prototype.get_by_criteria(req.params.product_id, req.params.criteria)+'"');
});

app.post('/ratings', function(req,res){
    if(req.body.criteria==undefined){
        ratings.prototype.post(req.ip,req.body.product_id,1,req.body.value);
        ratings.prototype.post(req.ip,req.body.product_id,2,req.body.value);
        ratings.prototype.post(req.ip,req.body.product_id,3,req.body.value);
        /** Log action */
        logger.prototype.post(req.ip,"a adaugat un rating general pentru produsul cu id-ul "+req.body.product_ida);
    }else{
        ratings.prototype.post(req.ip,req.body.product_id,req.body.criteria,req.body.value);
        /** Log action */
        logger.prototype.post(req.ip,"a adaugat un rating pentru produsul cu id-ul "+req.body.product_id+" dupa criteriul "+req.body.criteria);
    }

    res.send("added rating");
});

/** Products */
app.get('/products', function(req,res){
    res.send(products.prototype.get());
});

app.get('/products/:category', function(req,res){
    res.send(products.prototype.get(req.params.category));
});

app.get('/product/:id', function(req,res){
    res.send(products.prototype.get(null, req.params.id));
    /** Log action */
    logger.prototype.post(req.ip,"a vizualizat produsul cu id-ul "+req.params.id);
});

app.put('/product/:id/:password', function(req,res){
    if(req.params.password!==password){
        res.send("Invalid auth params");
        /** Log action */
        logger.prototype.post(req.ip,"a incercat sa modifice produsele, dar cu date de autentificare gresite!");
        return;
    }
    products.prototype.put(req.params.id, req, res)
    /** Log action */
    logger.prototype.post(req.ip,"a modificat produsul cu id-ul "+req.params.id);
});

app.post('/products/:password', function(req,res){
    if(req.params.password!==password){
        res.send("Invalid auth params");
        /** Log action */
        logger.prototype.post(req.ip,"a incercat sa adauge un produs, dar cu date de autentificare gresite!");
        return;
    }
    products.prototype.post(req, res);
    /** Log action */
    logger.prototype.post(req.ip,"a adaugat un produs");
});

app.delete('/product/:id/:password', function(req,res){
    if(req.params.password!==password){
        res.send("Invalid auth params");
        /** Log action */
        logger.prototype.post(req.ip,"a incercat sa stearga un produs, dar cu date de autentificare gresite!");
        return;
    }
    res.send(products.prototype.delete(req.params.id));
    /** Log action */
    logger.prototype.post(req.ip,"a sters produsul cu id-ul "+req.params.id);
});

/** Logger */
app.get('/logger', function(req,res){
    if(req.header("accepts")==="application/json"){
        res.send(logger.prototype.get());
    }else{
        res.send(logger.prototype.get_string());
    }
});

/** Check password */
app.get('/check_auth/:password', function(req, res){
    let isCorrect = req.params.password===password;
    res.send(isCorrect);
});

/** 404 Error redirect */
app.use(function(req, res, next){
    if(req.headers.accept.indexOf("image/*")!==-1){
        res.sendFile(_images_dir+"/blank.png");
    }else{
        res.status(404);
        res.sendFile(_template_dir+"/404.html");
    }
});

/** Start local server */
app.listen(port);
console.log("Listening on port " + port);

/** Usefull functions */
function link_path(file_location, get_prefix = null){
    if(get_prefix==null){
        file_location.split("/").forEach(function(dir){
            get_prefix = dir;
        });
        get_prefix = "/"+get_prefix;
    }
    app.get(get_prefix, function(req, res){
       res.sendFile(path.join(file_location));
    });
}

function link_folder(dir, separate_directories = false, sub = "/", ignore_extension = [".html"]){
    fs.readdirSync(path.join(dir)).forEach(function(file) {
        get_prefix = (file.split('.')[0]==="index") ? "" : file;
        if(file.split('.').length===1){
            if(separate_directories) link_folder(dir+"/"+file, separate_directories, sub+file+"/");
            else link_folder(dir+"/"+file, separate_directories, sub);
            return;
        }
        link_path(dir+"/"+file, sub+get_prefix);
        for(var i=0;i<ignore_extension.length;i++)
            if(get_prefix.search(ignore_extension[i]))
                link_path(dir+"/"+file, sub+get_prefix.replace(ignore_extension[i], ""));
    });
}
