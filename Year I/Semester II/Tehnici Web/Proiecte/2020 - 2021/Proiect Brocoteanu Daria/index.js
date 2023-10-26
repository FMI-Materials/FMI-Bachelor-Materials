const express = require('express')
const path = require('path')
const fs = require('fs')
const app = express()
const port = 3000
app.use(express.static(path.join(__dirname, "public")));
app.use(express.urlencoded());

app.get('/', (req, res) => {
    res.sendFile("proiect.html", { root: __dirname });
})

app.get('/about', (req, res) => {
    res.sendFile("about.html", { root: __dirname });
})

app.get('/photos', (req, res) => {
    res.sendFile("photos.html", { root: __dirname });
})

app.get('/contact', (req, res) => {
    res.sendFile("contact.html", { root: __dirname });
})

app.get('/menu', (req, res) => {
    res.sendFile("menu.html", { root: __dirname });
})

app.post('/rating', (req, res) => {
    let str = fs.readFileSync('ratings.json').toString().trim();
    let ratings = !str ? [] : JSON.parse(str);
    ratings.push(req.body);

    fs.writeFileSync('ratings.json', JSON.stringify(ratings));
    res.redirect('/contact');

})

app.get('/ratings', (req, res) => {
    res.sendFile("ratings.json", { root: __dirname });
})


app.listen(port, () => {
    console.log(`Example app listening at http://localhost:${port}`)
})