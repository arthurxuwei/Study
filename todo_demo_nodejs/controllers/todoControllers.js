"use strict";

var config = require('../config');
var db = require('../dao/todoDao');

exports.index = function (req, res, next) {
	db.allTodos(function (err, todos){
		if (err) {
			return next(err);
		}
		res.render('index', {todos: todos});
	});
}

exports.new = function (req, res, next) {
	var title = req.body.title || '';
	title = title.trim();
	if (!title) {
		return res.render('error.html', {message: 'Need a title!'});
	}
	db.add(title, function (err, row){
		if (err) {
			return next(err);
		}
		res.redirect('/');
	});
}

exports.view = function (req, res, next) {
	res.redirect('/');
}

exports.edit = function (req, res, next) {
	var id = req.params.id;
	db.findTodoById(id, function (err, row){
		if (err) {
			return next(err);
		}
		if (!row) {
			return next();
		}
		res.render('todo/edit.html', {todo: row});
	});
}

exports.save = function (req, res, next) {
	var id = req.params.id;
	var title = req.body.title || '';
	title = title.trim();
	if (!title) {
		return res.render('error.html', {message: 'Need a title!'});
	}
	db.editTitle(id, title, function (err, row){
		if (err) {
			return next(err);
		}
		res.redirect('/');
	});
}

exports.delete = function (req, res, next) {
	var id = req.params.id;
	db.delete(id, function (err){
		if (err) {
			return next(err);
		}
		res.redirect('/');
	});
}

exports.finish = function (req, res, next) {
	var finished = req.query.status === 'yes' ? true : false;
	var id = req.params.id;
	db.editFinished(id, finished, function (err, result){
		if (err) {
			return next(err);
		}
		res.redirect("/");
	});
}
