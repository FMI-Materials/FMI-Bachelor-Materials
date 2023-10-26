var sessionExpired = setTimeout(function(){
    alert("Sesiune expirata");
}, 30*1000);

var dog = {

    movePixels: 10, // number of pixels
    delayMs: 50, // number of miliseconds
    dogTimer: null,

    dogWalk: function(){
        var img = document.getElementsByTagName("img")[0];
        var currentLeft = parseInt(img.style.left);
        img.style.left = currentLeft + dog.movePixels + "px";
        // reset image position to start
        if (currentLeft > window.innerWidth - img.width) {
            img.style.left = "0px";
        }
        document.getElementById("info").innerText = "Viteza: "+((1000 * dog.movePixels) / dog.delayMs)+"px/secunda";
    },

    // Call dogWalk function every 50 ms
    startDogWalk: function() {
        clearInterval(this.dogTimer);
        clearTimeout(sessionExpired);
        this.dogTimer = window.setInterval(this.dogWalk, this.delayMs);
        document.getElementById("start-button").disabled = true;
    },

    stopDogWalk: function(){
        clearTimeout(sessionExpired);
        clearInterval(this.dogTimer);
        document.getElementById("start-button").disabled = false;
    },

    goFaster: function(){
        clearTimeout(sessionExpired);
        this.movePixels += 10;
        this.startDogWalk();
    },

    resetSpeed: function(){
        clearTimeout(sessionExpired);
        dog.movePixels = 10;
        dog.startDogWalk();
    },


};

var rbutton = document.createElement("button");
rbutton.innerText = "Reset speed";
rbutton.id = "reset-button";
rbutton.onclick = dog.resetSpeed;
document.getElementsByTagName("body")[0].appendChild(rbutton);