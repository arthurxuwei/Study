'use strict';

/* Services */


// Demonstrate how to register services
// In this case it is a simple value service.
var arthurServices = angular.module('arthurService', ['ngResource']);
	
arthurServices.factory('User', ['$resource',
	function($resource) {
		return $resource('data/:name.json', {}, {
			query: {method:'GET', params:{name:'users'}, isArray:true}
		});
	}
]);
