this.firstname = "Tim";

function Person() {
	var secondname = "O";
	this.firstname1 = "Mike";
	this.getName = function () {
		var firstname2 = "Him";
		
		console.log(this);
		return function() {
			var firstname3 = "Fuck";
			console.log(firstname3);
			return secondname;
		};
	};
//	console.log(this);
}

console.log(this);

var person = new Person();
//var getName = person.getName().bind(this)();
Person.prototype.lastname = "123";

var getName = person.getName()();

console.log(person.lastname);
console.log(getName);
exports.getName = getName;
