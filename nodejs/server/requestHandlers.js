var querystring = require("querystring"),
	fs = require("fs"),
	formidable = require("formidable");

function start(response, postData) {
	console.log("Requset handler 'start' was called.");
	
	var body = '<html>' +
	  '<head>' +
	  '<meta http-equiv="Content-Type" content="text/html; ' +
	  'charset=UTF-8" />' +
	  '</head>' +
	  '<body>' +
	  '<form action="/upload" enctype="multipart/form-data" method="post">' +
	  '<input type="file" name="upload">' +
	  '<input type="submit" value="upload" />' +
	  '</form>' +
	  '</body>' +
	  '</html>';

	response.writeHead(200, {"Content-Type":"text/html"});
	response.write(body);
	response.end();
}

function upload(response, request) {
	console.log("Requset handler 'upload' was called.");
	
	var form = new formidable.IncomingForm();
	console.log("about to pares");
	form.parse(request, function(error, fields, files){
		console.log("parsing done");
		fs.renameSync(files.upload.path, "/home/arthur/Downloads/1.jpg");
		response.writeHead(200, {"Content-Type":"text/html"});
		response.write("received image:<br/>");
		response.write("<img src='/show' />");
		response.end();
	});
	
}

function show(response, request) {
	console.log("Requset handler 'show' was called.");
	fs.readFile("/home/arthur/Downloads/1.jpg", "binary", function(error, file){
		if(error){
			response.writeHead(500, {"Content-Type":"text/plain"});
			response.write(error + "\n");
			response.end();
		} else {
			response.writeHead(200, {"Content-Type":"image/jpg"});
			response.write(file, "binary");
			response.end();
		}
	});
}

function check(response, request) {
	console.log("Requset handler 'check' was called.");
	var json = "Ok";
	
	response.writeHead(200, {"Content-Type":"text/json"});
	response.write(json);
	response.end();
}

function echo(response, request) {
	console.log("Requset handler 'echo' was called.");
	if (request.method == 'POST') {
		var body = '';
		request.on('data', function (data) {
			body += data;
		});
		request.on('end', function(){
//			var POST = querystring.parse(body);
			console.log(body);
		});
	}
	var json = "Ok";
	response.writeHead(200, {"Content-Type":"text/json"});
	response.write(json);
	response.end();
}

function register(response, request) {
	console.log("Requset handler 'register' was called.");
	if (request.method == 'POST') {
		var body = '';
		request.on('data', function (data) {
			body += data;
		});
		request.on('end', function(){
			console.log(body);
		});
	}
	var json = "{" +
    			"\"hpmsRegistrationId\": \"2bf5997d-27f0-4fd1-adf4-98f5aa5daac0\"" +
				"}";
	response.writeHead(200, {"Content-Type":"text/json"});
	response.write(json);
	response.end();
}

exports.start = start;
exports.upload = upload;
exports.show = show;

exports.check = check;
exports.echo = echo;
exports.register = register;
