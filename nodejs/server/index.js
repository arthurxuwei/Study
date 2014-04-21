var server = require("./server");
var router = require("./route");
var requestHandlers = require("./requestHandlers");

var handle = {}
handle["/"] = requestHandlers.start;
handle["/start"] = requestHandlers.start;
handle["/upload"] = requestHandlers.upload;
handle["/show"] = requestHandlers.show;

handle["/check"] = requestHandlers.check;
handle["/echo"] = requestHandlers.echo;
handle["/register"] = requestHandlers.register;

server.start(router.route, handle);
