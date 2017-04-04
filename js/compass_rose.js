Qt.include('qrc:/js/math.js');

var outer_radius = 0;
var offset_x = 0
var offset_y = 0;

var quadrants_name = ['N', 'NE', 'E', 'SE', 'S', 'SW', 'W', 'NW'];

var quadrants = []

function paint_compass_rose(canvas) {
    // console.info('paint_compass_rose');

    // X axis point to right
    // Y axis point to bottom
    // Positive rotation is clockwise

    var ctx = canvas.getContext('2d');
    ctx.reset();
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    var canvas_radius = Math.min(canvas.width, canvas.height) / 2;
    outer_radius = - canvas_radius; // invert y axis
    var inner_radius = 2 / 3 * outer_radius;

    // center frame
    offset_x = canvas.width / 2;
    offset_y = canvas.height / 2;
    ctx.translate(offset_x, offset_y);

    var i_angle  = 360 / 16;
    var p_outer = {x: 0, y: outer_radius}
    var p_inner = {x: 0, y: inner_radius}
    var p;

    ctx.beginPath();
    ctx.moveTo(0, outer_radius);
    for (var i = 1; i <= 8; i++) {
    	var j = 2 * i;
    	p = rotate_vector(p_inner, i_angle * (j - 1));
    	ctx.lineTo(p.x, p.y);
    	p = rotate_vector(p_outer, i_angle * j);
    	ctx.lineTo(p.x, p.y);
    }
    ctx.fillStyle = 'black';
    ctx.fill()

    // ctx.fillStyle = Qt.lighter('black', 1.5);
    ctx.fillStyle = 'gray';
    quadrants.forEach(function (quadrant) {
    	console.info(quadrant);
    	var j = quadrant * 2;
    	ctx.beginPath();
    	ctx.moveTo(0, 0);
    	p = rotate_vector(p_inner, i_angle * (j - 1));
    	ctx.lineTo(p.x, p.y);
    	p = rotate_vector(p_outer, i_angle * j);
    	ctx.lineTo(p.x, p.y);
    	p = rotate_vector(p_inner, i_angle * (j + 1));
    	ctx.lineTo(p.x, p.y);
    	ctx.lineTo(0, 0);
    	ctx.fill();
    });

    ctx.strokeStyle = 'white';
    ctx.lineWidth = 2;
    for (var i = 0; i < 8; i++) {
    	ctx.beginPath();
    	ctx.moveTo(0, 0);
    	p = rotate_vector(p_inner, i_angle * (2*i + 1));
    	ctx.lineTo(p.x, p.y);
    	ctx.stroke()
    }

    ctx.font =  (canvas_radius / 5).toFixed(0) + 'px sans-serif'; // roboto ?
    ctx.fillStyle = 'white';
    ctx.textAlign = 'center';
    ctx.textBaseline = 'middle';
    ctx.fillText("N", 0, inner_radius);
    ctx.fillText("S", 0, -inner_radius);
    ctx.fillText("E", -inner_radius, 0);
    ctx.fillText("W", inner_radius, 0);
}

function get_quadrant(mouse_x, mouse_y) {
    if (outer_radius) {
	mouse_x -= offset_x;
	mouse_y -= offset_y;
	mouse_y = - mouse_y;
	var angle = radians_to_degrees(Math.atan(mouse_x / mouse_y));
	if (mouse_x > 0) {
	    if (mouse_y < 0)
		angle =  180 + angle
	}
	else {
	    if (mouse_y < 0)
		angle =  180 + angle;
	    else
		angle =  360 + angle;
	}
	var i_angle  = 360 / 8;
	var quadrant = Math.floor((angle + i_angle / 2) /  i_angle);
	if (quadrant == 8)
	    quadrant = 0;
	console.info(mouse_x, mouse_y, angle, quadrant);
	return quadrant;
    } else
	return null;
}

function update_quadrant(quadrant) {
    var index = quadrants.indexOf(quadrant);
    if (index == -1) {
	// console.info('set', quadrant)
	quadrants.push(quadrant);
    } else {
	// console.info('unset', quadrant)
	quadrants.splice(index, 1);
    }
}

function get_state() {
    if (quadrants.length) {
	var state = [];
	quadrants.forEach(function (i) {
	    state.push(quadrants_name[i]);
	});
	return state;
    } else
	return null;
}

function set_state(state) {
    quadrants = [];
    state.forEach(function (value) {
	quadrants.push(quadrants_name.indexOf(value));
    });
}
