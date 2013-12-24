'use strict';	

/* Controllers */
var arthurContollers = angular.module('arthurContollers', []);

arthurContollers.controller('login', ['$scope', '$location', 'User', function($scope, $location, User){
	$scope.error = '';
	
	$scope.signin = function(){
		$scope.error = "Login...";
		var users = User.query(function (res){
			console.log(res);
			var data = res[0];
			if (data.email === $scope.email && data.password === $scope.password) {
				$location.path('/loginsuccess');
			}
			$scope.email = '';
			$scope.password = '';
			$scope.error = 'password is wrong...';
		});	
	};
}]);

arthurContollers.controller('MyCtrl2', function(){

});

arthurContollers.controller('loginsuccess', function(){
});

