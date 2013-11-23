var http = require("http");
var url = require("url");

function start(route, handle) {
	function onRequest(request, response) {
		var pathname = url.parse(request.url).pathname;
		console.log("request "+ pathname +" handling...");
		
		route(handle, pathname, response, request);		
	}

	http.createServer(onRequest).listen('8889', '16.187.94.230');
	console.log("Server has Started.");
}

exports.start = start;
