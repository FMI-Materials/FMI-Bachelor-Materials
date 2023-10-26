const options = ["Autobot", "Daimons", "Deep Ones", "Experiment", "Goa'uld", "Hutt", "Jawa", "Kryptonian", "Mandalorians", "Martian", "Protoss", "Rodian", "Romulan", "Tleilaxu", "Vogon", "Wookie", "Xenu", "Yeti", "Zerg"];

window.onload = function() {
    let dropdown = document.getElementById("rasa");
    for (let i = 0; i < options.length; i++) {
        let option = document.createElement("option");
        option.value = options[i];
        option.text = options[i];
        dropdown.appendChild(option);
    }


    const credit = document.getElementById("credit").value;
    const creditValue = document.getElementById("credit-value");
    creditValue.innerHTML = credit;

    document.getElementById("credit").oninput = (event) =>
    {
        const credit = event.target.value;
        const creditValue = document.getElementById("credit-value");
        creditValue.innerHTML = credit;
    };
};