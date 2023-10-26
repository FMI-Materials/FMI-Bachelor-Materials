var persoana = {
    nume: "John",
    varsta: 50,
    calitati: ["ambitios", "fericit", "determinat"]
};

console.log(persoana.nume);
console.log("Varsta:", persoana.varsta);
console.log("Calitati:");
for(var i=0;i<persoana.calitati.length;i++)
    console.log(persoana.calitati[i]);
