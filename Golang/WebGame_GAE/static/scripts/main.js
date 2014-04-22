var d = new Date();
window.onload = function () {
	document.getElementById('clientTime').innerText = d.toUTCString();
}
