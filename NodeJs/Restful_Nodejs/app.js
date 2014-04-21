var express = require('express')
	,http = require('http');

var app = express();

app.engine('html', require('ejs').renderFile);

app.set('port', process.env.PORT || 3000);
app.use(express.favicon());
app.use(express.logger('dev'));
app.use(express.bodyParser());
app.use(express.methodOverride());
app.use(app.router);
app.set('views', __dirname + '/views');
app.set('view engine', 'ejs');
app.use(express.static(__dirname + '/public'));

if ('development' == app.get('env')) {
	app.use(express.errorHandler());
}

app.get('/', function(req, res, next){
	res.render('index.html',{});
});
app.get('/ajax', function(req, res, next){
	res.send('{"msg":"123"}');
});

http.createServer(app).listen(app.get('port'), function(){
	console.log('Server start on port: ' + app.get('port'));
});