// drawrectangle.js

function main() {
	var canvas = document.getElementById("example");
	if (!canvas) {
		console.error("Failed to retrieve the canvas element");
		return;
	}

	var ctx = canvas.getContext('2d');

	ctx.fillStyle = 'rgba(0, 0, 255, 1.0)';
	ctx.fillRect(100, 10, 150, 150);

	setTimeout(function() {
		var canvas = document.getElementById("example");
		if (!canvas) {
			return;
		}

		var ctx = canvas.getContext('2d');
		ctx.clearRect(200, 10, 50, 50);

	}, 3000);
}
