'use strict';	

/* Controllers */
var arthurConytollers = angular.module('arthurConytollers', []);

arthurConytollers.controller('login', function($scope, $http, $location){
	$scope.error = '';
	
	$scope.signin = function(){
		$scope.error = "Login...";
//		var email = $scope.email;
//		var password = $scope.password;
		$http.get('data/users.json').success(function(data) {
			var data = data[0];
			console.log(data.email);
			if (data.email === $scope.email && data.password === $scope.password) {
				$location.path('/loginsuccess');
			}
			$scope.email = '';
			$scope.password = '';
			$scope.error = 'password is wrong...';
		});	
	};
});

arthurConytollers.controller('MyCtrl2', function(){

});

arthurConytollers.controller('loginsuccess', function(){
});

