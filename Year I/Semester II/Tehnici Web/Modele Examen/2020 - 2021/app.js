const express = require('express');
const app = express();

app.use('/post', express.urlencoded({ extended: true }));

carti = [{titlu:"c1", gen:"aventura", pagini:"200"}, {titlu:"c4", gen:"politist", pagini:"240"}, {titlu:"c5",
gen:"fantastic", pagini:"300"}, {titlu:"c2", gen:"fantastic", pagini:"450"}, {titlu:"c3", gen:"aventura",
pagini:"600"}]

app.get("/p4.html", function(req, res) {

  res.sendFile(__dirname + "/p4.html");
});

app.get("/", function(req, res) {

  res.sendFile(__dirname + "/p4.html");
});

app.post("/post", function(req, res) {
  let arr = [];
  console.log(req.body);
  for (let carte of carti) {
    if (req.body.gen == carte.gen) {
      if (carte.pagini > 250)
        arr.push(carte.titlu);
    }
  }
  if(arr.length!=0)
    res.send(arr);
  else
    res.send("Nu exista carti")
});

app.listen(7000, function() { console.log("Serverul a pornit"); });