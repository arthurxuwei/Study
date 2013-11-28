var object = 
{
	isA: function(aType) {
		var self = this;
		while(self) {
			if(self == aType)
				return true;
			self = self.Type;
		};
		return false;
	}
};

function Class(aBaseClass, aClassDefine) {
	function class_() {
		this.Type = aBaseClass;
		for(var member in aClassDefine)
			this[member] = aClassDefine[member];
	};
	class_.prototype = aBaseClass;
	return new class_();
};  

function New(aClass, aParams) {
	function new_() {
		this.Type = aClass;
		if(aClass.Create)
			aClass.Create.apply(this, aParams);
	};
	new_.prototype = aClass;
	return new new_();
};

var Person = Class(object, {
	Create: function(name, age) {
		this.name = name;
		this.age = age;
	},
	SayHello: function() {
		console.log("Hello, I'm " + this.name + ", " + this.age);
	}
});

var Employee = Class(Person, {
	Create: function(name, age, salary) {
		Person.Create.call(this, name, age);
		this.salary = salary;
	},
	ShowMeTheMoney: function() {
		console.log(this.name + "$: " + this.salary);
	}
});

var BillGates = New(Person, ["BillGates", 53]);
var SteveJobs = New(Employee, ["SteveJobs", 53, 1024]);

BillGates.SayHello();
SteveJobs.SayHello();
SteveJobs.ShowMeTheMoney();

var LittleBill = New(BillGates.Type, ["LittleBill", 6]);
LittleBill.SayHello();

console.log(BillGates.isA(Person));
console.log(BillGates.isA(Employee));

console.log(SteveJobs.isA(Person));
console.log(SteveJobs.isA(Employee));

console.log(Employee.isA(Person));
console.log(Person.isA(Employee));


