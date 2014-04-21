$(document).ready(function() {
	$.ajax({
		url: 'http://16.187.93.8:3000/ajax',
		type: 'GET',
		success: function(data){
			var ret = jQuery.parseJSON(data);
			$('#lblResponse').html(ret.msg);
			console.log('Success:' + ret);
		},
		error: function(xhr, status, error) {
			$('#lblResponse').html('Error');
			console.log('Error' + error.message);
		}
	});
});