// Import packages
const express = require("express");
const morgan = require("morgan");
const bodyParser = require("body-parser");
const cors = require("cors");
const uuid = require("uuid");

const fs = require("fs");

// Aplicatia
const app = express();

// Middleware
app.use(morgan("tiny"));
app.use(bodyParser.json());
app.use(cors());

function makeid(length = 8) {
    var result           = '';
    var characters       = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';
    var charactersLength = characters.length;
    for ( var i = 0; i < length; i++ ) {
        result += characters.charAt(Math.floor(Math.random() * charactersLength));
    }
    return result;
}

// Create
app.post("/dogs", (req, res) => {
    const dogsList = readJSONFile("db.json");
    newDog = {
        name: req.body.name,
        img: req.body.img,
        id: makeid(8)+"-"+makeid(4)+"-"+makeid(4)+"-"+makeid(4)+"-"+makeid(12)
    };
    dogsList.push(newDog);
    writeJSONFile(dogsList);
    res.send(newDog);
});

// Read One
app.get("/dogs/:id", (req, res) => {
    const dogsList = readJSONFile();
    var found = false;
    for(var i=0;i<dogsList.length;i++)
        if(dogsList[i].id == req.params.id){
            res.send(dogsList[i]);
            found = true;
            break;
        }
    if(!found)
        res.send("Not found");
});

// Read All
app.get("/dogs", (req, res) => {
    const dogsList = readJSONFile();
    res.send(dogsList);
});

// Update
app.put("/dogs/:id", (req, res) => {
    const dogsList = readJSONFile();
    var found = false;
    for(var i=0;i<dogsList.length;i++)
        if(dogsList[i].id == req.params.id){
            found = true;
            dogsList[i].name = req.body.name;
            dogsList[i].img = req.body.img;
            res.send(dogsList[i]);
            break;
        }
    writeJSONFile(dogsList);
    if(!found) res.send("Not found");
});

// Delete
app.delete("/dogs/:id", (req, res) => {
    const dogsList = readJSONFile();
    var found = false;
    for(var i=0;i<dogsList.length;i++)
        if(dogsList[i].id == req.params.id){
            dogsList.splice(i, 1);
            found = true;
            break;
        }
    writeJSONFile(dogsList);
    if(!found) res.send("Not found");
    else res.send("Deleted");
});

// Functia de citire din fisierul db.json
function readJSONFile() {
    return JSON.parse(fs.readFileSync("db.json"))["dogs"];
}

// Functia de scriere in fisierul db.json
function writeJSONFile(content) {
    fs.writeFileSync(
        "db.json",
        JSON.stringify({ dogs: content }),
        "utf8",
        err => {
            if (err) {
                console.log(err);
            }
        }
    );
}

// Pornim server-ul
app.listen("3000", () =>
    console.log("Server started at: http://localhost:3000")
);