'use strict';

// Declare app level module which depends on filters, and services
angular.module('arthur', ['arthurContollers', 'arthur.filters', 'arthurService', 'arthurDirectives']).
  config(['$routeProvider', function($routeProvider) {
    $routeProvider.when('/login', {templateUrl: 'partials/login.html', controller: 'login'});
    $routeProvider.when('/register', {templateUrl: 'partials/register.html', controller: 'signin'});
	$routeProvider.when('/loginsuccess', {templateUrl: 'partials/loginsuccess.html', controller: 'loginsuccess'});
    $routeProvider.otherwise({redirectTo: '/login'});
  }]);
