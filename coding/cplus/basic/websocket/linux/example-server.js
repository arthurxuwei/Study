/*
  Prerequisites:

    1. Install node.js and npm
    2. npm install ws

  See also,

    http://einaros.github.com/ws/

  To run,

    node example-server.js
*/

"use strict"; // http://ejohn.org/blog/ecmascript-5-strict-mode-json-and-more/
var WebSocketServer = require('ws').Server;
var http = require('http');

function sleep(milliSeconds) {
    var startTime = new Date().getTime(); while(new Date().getTime() < startTime + milliSeconds);
}

var server = http.createServer();
var wss = new WebSocketServer({server: server, path: '/linux'});
wss.on('connection', function(ws) {
    console.log('/linux connected');
    ws.on('message', function(data, flags) {
        if (flags.binary) { return; }
        console.log('/linux >>> ' + data);
        if (data == 'goodbye') { ws.send('end'); }
        if (data == 'hello') { ws.send('world'); }
    });
    ws.on('close', function() {
      console.log('Connection closed!');
    });
    ws.on('error', function(e) {
    });
});

var wss2 = new WebSocketServer({server: server, path: '/windows'});
wss2.on('connection', function(ws) {
    console.log('/windows connected');
    ws.on('message', function(data, flags) {
        if (flags.binary) { return; }
        console.log('/windows >>> ' + data);
        if (data == 'goodbye') { for (var i = 0; i < 50; ++i){sleep(80); ws.send('end' + i);} }
    });
    ws.on('close', function() {
      console.log('Connection closed!');
    });
    ws.on('error', function(e) {
    });
});


server.listen(8126);
console.log('Listening on port 8126...');
