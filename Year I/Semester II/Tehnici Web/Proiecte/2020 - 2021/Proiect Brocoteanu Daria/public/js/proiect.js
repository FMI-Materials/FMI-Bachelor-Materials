function setRandomColors() {
    let colors = ["red", "blue", "green"];
    for (let el of Array.from(document.getElementsByClassName("random-color"))) {
        const randomIndex = Math.floor(Math.random() * colors.length);
        el.style.setProperty("color", colors[randomIndex], "important")
        colors.splice(randomIndex, 1);
    }
}
window.onload = (event) => {
    var slideIndex = 1;
    showSlides(slideIndex);
};


// Next/previous controls
function plusSlides(n) {
  showSlides(slideIndex += n);
}

// Thumbnail image controls
function currentSlide(n) {
  showSlides(slideIndex = n);
}

function showSlides(n) {
  var i;
  var slides = document.getElementsByClassName("mySlides");
  var dots = document.getElementsByClassName("demo");
  //var captionText = document.getElementById("caption");
  if (n > slides.length) {slideIndex = 1}
  if (n < 1) {slideIndex = slides.length}
  for (i = 0; i < slides.length; i++) {
    slides[i].style.display = "none";
  }
  for (i = 0; i < dots.length; i++) {
    dots[i].className = dots[i].className.replace(" active", "");
  }
  if (slideIndex>=1)
    slides[slideIndex - 1].style.display = "block";
  if (slideIndex>=1)
    dots[slideIndex-1].className += " active";
//   if (slideIndex>=1)
//     captionText.innerHTML = dots[slideIndex-1].alt;
}

function loadDoc() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            let ratings = JSON.parse(this.responseText);
            let number = 0;
            var table = document.getElementById("ratingss");
            for (let rating of ratings) {
                ++ number;
                var div = document.createElement("div");
                // div.style.width = "400px";
                // div.style.height = "200px";
                var r = Math.floor(Math.random() * (255 - 0 + 1) + 0);
                var g = Math.floor(Math.random() * (255 - 0 + 1) + 0);
                var b = Math.floor(Math.random() * (255 - 0 + 1) + 0);
                // div.style.display = "table-cell";
                div.classList.add("rating-pe-bune");
                var rgbString = r + ", " + g + ", " + b;
                div.style.backgroundColor = 'rgb(' + rgbString + ')';
               // div.style.background = red;
                div.style.borderColor = "black";

                div.style.color = "white";
                div.innerHTML = "";
                
                
                let p = document.createElement('p');
                let p1 = document.createElement('p');
                let p2 = document.createElement('p');
                let p3 = document.createElement('p');
                var str = "Rating number: " + number + '\n';
                var str1 = str.bold();
                p3.innerHTML = str1;
                p.innerHTML = "Date: " + rating.Date + '\n';
                p1.innerHTML = "Name : " + rating.Name + "\n";
                p2.innerHTML = "Number of stars: " + rating.Rating + '\n';
                let p4 = document.createElement('p');
                p4.innerHTML = "\n";
                div.appendChild(p3);
                div.appendChild(p);
                div.appendChild(p1);
                div.appendChild(p2);
                document.getElementById("ratingss").appendChild(div);
        
            }
        }
    };
    xhttp.open("GET", "ratings", true);
    xhttp.send();
}
window.onload = loadDoc;