//strict mode will change 'this' behavious.

"use strict";
var t = function() {
	return function(){
		console.log(this);
	}
}

t()();
