//SYnkroninen suoritus, menee rivi kerrallaan
var fs=require("fs");
var data=fs.readFileSync("input.txt");
console.log(data.toString());
console.log("Ohjelma loppui");