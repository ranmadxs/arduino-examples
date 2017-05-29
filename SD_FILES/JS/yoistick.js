var laserStatus = false;
var ipClient = "${clientIp}"; 
var ROVER_STOP = "${ROVER_STOP}";
var ROVER_MOVE_MANUAL_BODY = "${ROVER_MOVE_MANUAL_BODY}";
var LASER_ACTION = "${LASER_ACTION}";
var TIPO_CALL = "SERIAL";
function actCmd(cmd, p1, p2, p3, p4, p5, p6, p7) { 
	p1 = p1 || 'None'; 
	p2 = p2 || 'None'; 
	p3 = p3 || 'None'; 
	p4 = p4 || 'None'; 
	p5 = p5 || 'None'; 
	p6 = p6 || 'None'; 
	p7 = p7 || 'None'; 
    var xhttp = new XMLHttpRequest();
	xhttp.open('GET', 'http://'+ipClient+'/cmd?TIPO_CALL='+TIPO_CALL+'&COMMAND='+cmd+'&P1='+p1+'&P2='+p2+'&P3='+p3+'&P4='+p4+'&P5='+p5+'&P6='+p6+'&P7='+p7, false);
    xhttp.setRequestHeader('Content-type', 'text/html');
	xhttp.send();
}
function actionMove(move, roverType) { 
    var xhttp = new XMLHttpRequest();
	xhttp.open('GET', 'http://'+ipClient+'/cmd?TIPO_CALL='+TIPO_CALL+'&COMMAND='+ROVER_MOVE_MANUAL_BODY+'&P1='+roverType+'&P2=0&P3=0&P4='+move+'&P5=None&P6=None&P7=None', false);
    xhttp.setRequestHeader('Content-type', 'text/html');
	xhttp.send();
}
function actionStop(roverType) { 
    var xhttp = new XMLHttpRequest();
	xhttp.open('GET', 'http://'+ipClient+'/cmd?TIPO_CALL='+TIPO_CALL+'&COMMAND='+ROVER_STOP+'&P1='+roverType+'&P2=0&P3=0&P4=None&P5=None&P6=None&P7=None', false);
    xhttp.setRequestHeader('Content-type', 'text/html');
	xhttp.send();
}
function actionLaser() { 
    var xhttp = new XMLHttpRequest();
    if (laserStatus){
      laserStatus = false;
    }else{
      laserStatus = true;
    }
    xhttp.open('GET', 'http://'+ipClient+'/cmd?TIPO_CALL='+TIPO_CALL+'&COMMAND='+LASER_ACTION+'&P1='+laserStatus+'&P2=0&P3=None&P4=None&P5=None&P6=None&P7=None', false);
    xhttp.setRequestHeader('Content-type', 'text/html');
    xhttp.send();
}