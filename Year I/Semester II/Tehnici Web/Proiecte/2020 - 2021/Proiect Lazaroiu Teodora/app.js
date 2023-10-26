const express = require("express");
const path = require("path");
const app = express();

app.get('/', function(req,res){
    res.render('pages/index');
})
app.get('/index', function(req,res){
    res.render('pages/index');
})
app.get('/game', function(req,res){
    res.render('pages/game');
})
app.get('/gallery', function(req,res){
    res.render('pages/gallery');
})
app.get('/form', function(req,res){
    res.render('pages/form');
})
app.get('/films3', function(req,res){
    res.render('pages/films3');
})
app.get('/films2', function(req,res){
    res.render('pages/films2');
})
app.get('/films1', function(req,res){
    res.render('pages/films1');
})
app.get('/actors', function(req,res){
    res.render('pages/actors');
})
app.get('/quiz', function(req,res){
    res.render('pages/quiz');
})
app.use('/public', express.static('public'));

app.get("*", function(req, res){
    res.sendFile(path.join(__dirname, '/404.html'));
})

app.set('view engine', 'ejs');

app.listen(8000, function(){
    console.log("Server running at http://localhost:8000/");
})