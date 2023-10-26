
function getCartValue(cart) {

    var total = 0;
    for (let [key, value] of Object.entries(cart)) {
        total+=value;
    }
    console.log(total.toFixed(2));
}

var blackFridayCart = {
    telefon: 350,
    consola: 250,
    televizor: 450,
    iepurasPlus: 10.60,
    cercei: 20.34,
    geanta: 22.36
};



// Output
getCartValue(blackFridayCart);