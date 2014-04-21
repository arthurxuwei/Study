var person = require('./Test_this').getName;


function Person(name) {
	this.name = name;
};

Person.prototype.SayHello = function() {
	console.log("Hello, I'm " + this.name);
};

function Sex(sex) {
	this.sex = sex;
};

Sex.prototype.ShowSex = function() {
	console.log(this.sex);
};

function Employee(name, salary) {
	Person.call(this, name);
	this.salary = salary;
};

Employee.prototype = new Person();
//Employee.prototype = new Sex();

Employee.prototype.ShowMeTheMoney = function() {
	console.log(this.name + " $: " + this.salary);
};



var BillGates = new Person("BillGates");
BillGates.SayHello();

var SteveJobs = new Employee("SteveJobs", 1024);

SteveJobs.SayHello();
SteveJobs.ShowMeTheMoney();


