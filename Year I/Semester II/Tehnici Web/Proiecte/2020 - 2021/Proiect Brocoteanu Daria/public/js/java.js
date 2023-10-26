

function w3_open() {
    document.getElementById("mySidebar").style.display = "block";
    document.getElementById("myOverlay").style.display = "block";
}

function w3_close() {
    document.getElementById("mySidebar").style.display = "none";
    document.getElementById("myOverlay").style.display = "none";
}

// Modal Image Gallery
function onClick(element) {
    document.getElementById("img01").src = element.src;
    document.getElementById("modal01").style.display = "block";
    var captionText = document.getElementById("caption");
    captionText.innerHTML = element.alt;
}
// Tabbed Menu
function openMenu(evt, menuName) {
    var i, x, tablinks;
    x = document.getElementsByClassName("menu");
    for (i = 0; i < x.length; i++) {
        x[i].style.display = "none";
    }
    tablinks = document.getElementsByClassName("tablink");
    for (i = 0; i < x.length; i++) {
        tablinks[i].className = tablinks[i].className.replace(" daria-red", "");
    }
    document.getElementById(menuName).style.display = "block";
    evt.currentTarget.firstElementChild.className += " daria-red";
}
//document.getElementById("myLink").click();

function myFunctionDelete() {
    var myobj = document.getElementById("recom");
    myobj.remove();
}
// var slideIndex = 0;
// showSlides(slideIndex);

// // Next/previous controls
// function plusSlides(n) {
//     showSlides(slideIndex += n);
// }

// // Thumbnail image controls
// function currentSlide(n) {
//     showSlides(slideIndex = n);
// }

// function showSlides(n) {
//     var i;
//     var slides = document.getElementsByClassName("mySlides");
//     var dots = document.getElementsByClassName("dot");
//     if (n > slides.length) { slideIndex = 1 }
//     if (n < 1) { slideIndex = slides.length }
//     for (i = 0; i < slides.length; i++) {
//         slides[i].style.display = "none";
//     }
//     for (i = 0; i < dots.length; i++) {
//         dots[i].className = dots[i].className.replace(" active", "");
//     }
//     if(slideIndex>1){
//     slides[slideIndex-1].style.display = "block";
//     dots[slideIndex-1].className += " active";
    
// }

function validatedate(inputText) {
	var dateformat = /^(0?[1-9]|[12][0-9]|3[01])[\/\-](0?[1-9]|1[012])[\/\-]\d{4}$/;
	// Match the date format through regular expression
	if (inputText.value.match(dateformat)) {
		document.form.Date.focus();
		//Test which seperator is used '/' or '-'
		var opera1 = inputText.value.split('/');
		var opera2 = inputText.value.split('-');
		lopera1 = opera1.length;
		lopera2 = opera2.length;
		// Extract the string into month, date and year
		if (lopera1 > 1) {
			var pdate = inputText.value.split('/');
		}
		else if (lopera2 > 1) {
			var pdate = inputText.value.split('-');
		}
		var dd = parseInt(pdate[0]);
		var mm = parseInt(pdate[1]);
		var yy = parseInt(pdate[2]);
		// Create list of days of a month [assume there is no leap year by default]
		var ListofDays = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31];
		if (mm == 1 || mm > 2) {
			if (dd > ListofDays[mm - 1]) {
				alert('Invalid date format!');
				return false;
			}
		}
		if (mm == 2) {
			var lyear = false;
			if ((!(yy % 4) && yy % 100) || !(yy % 400)) {
				lyear = true;
			}
			if ((lyear == false) && (dd >= 29)) {
				alert('Invalid date format!');
				return false;
			}
			if ((lyear == true) && (dd > 29)) {
				alert('Invalid date format!');
				return false;
			}
		}
	}
	else {
		alert("Invalid date format!");
		document.form.Date.focus();
		return false;
	}
}
function setRandomColors() {
    let colors = ["magenta", "lawngreen", "cyan"];
    for (let el of Array.from(document.getElementsByClassName("random-color"))) {
        const randomIndex = Math.floor(Math.random() * colors.length);
        el.style.color = colors[randomIndex];
        colors.splice(randomIndex, 1);
    }
}