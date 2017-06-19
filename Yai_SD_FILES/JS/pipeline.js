var pipeline = [];
var TIPO_CALL = "SERIAL";
function getInputP(varp){
	var html = 	'<div class="tooltip" id="label_'+varp+'">| '+varp.toUpperCase()+': '+
				'<span class="tooltiptext" id="tooltiptext_'+varp+'">None</span></div>'+
				'<input class="input_text_small_2 params '+varp+
				'" type="text" id="'+varp+'" name="'+varp+
				'" placeholder="None" value="None">';
	return html;
}

function reconstruct(){	
	$( "#div_cmds").empty();
	for (i = 1; i <= 7; i++){		
		var html = getInputP("p"+i);
		$("#div_cmds").append(html);
	}
}

function constructSelectRoverType(varp){
	$( "."+varp ).remove();
	var html = '<select class="select_small_2 '+varp+'" id="'+varp+'" name="'+varp+'">'+
      '<option value="1001">ROVER_TYPE_2WD</option>'+
    '</select>';
	$("#label_"+varp).after(html);
}

function constructSelectServoType(varp){
	$( "."+varp ).remove();
	var html = '<select class="select_small_2 '+varp+'" id="'+varp+'" name="'+varp+'">'+
      '<option value="2001">SERVO_TYPE_SG90</option>'+
    '</select>';
	$("#label_"+varp).after(html);
}

function constructObstacleServoType(varp){
	$( "."+varp ).remove();
	var html = '<select class="select_small_2 '+varp+'" id="'+varp+'" name="'+varp+'">'+
      '<option value="3001">OBSTACLE_HC_SR04</option>'+
    '</select>';
	$("#label_"+varp).after(html);
}

function constructObstacleDirection(varp){
	$( "."+varp ).remove();
	var html = '<select class="select_small_2 '+varp+'" id="'+varp+'" name="'+varp+'">'+
      '<option value="30001">OBSTACLE_SENSOR_FRONT</option>'+
    '</select>';
	$("#label_"+varp).after(html);
}


function constructServoDirection(varp){
	$( "."+varp ).remove();
	var html = '<select class="select_small_2 '+varp+'" id="'+varp+'" name="'+varp+'">'+
      '<option value="20001">SERVO_DIRECTION_VERTICAL</option>'+
	  '<option value="20002">SERVO_DIRECTION_HORIZONTAL</option>'+
	  '<option value="20003">SERVO_DIRECTION_ALL</option>'+
    '</select>';
	$("#label_"+varp).after(html);
}

function constructServoMove(varp){
	$( "."+varp ).remove();
	var html = '<select class="select_small_2 '+varp+'" id="'+varp+'" name="'+varp+'">'+
      '<option value="21002">SERVO_CLOCKWISE</option>'+
	  '<option value="21001">SERVO_COUNTER_CLOCKWISE</option>'+
    '</select>';
	$("#label_"+varp).after(html);
}

function constructSelectRoverMoveType(varp){
	$( "."+varp ).remove();
	var html = '<select class="select_small_2 '+varp+'" id="'+varp+'" name="'+varp+'">'+
      '<option value="10001">ROVER_BODY_MOVE_TYPE_LEFT</option>'+
	  '<option value="10002">ROVER_BODY_MOVE_TYPE_RIGHT</option>'+
	  '<option value="10003">ROVER_BODY_MOVE_TYPE_FORWARD</option>'+
	  '<option value="10004">ROVER_BODY_MOVE_TYPE_BACK</option>'+
    '</select>';
	$("#label_"+varp).after(html);
}

function constructTrueFalse(varp){
	$( "."+varp ).remove();
	var html = '<input class="'+varp+'" type="radio" name="'+varp+'" id="'+varp+'_true" value="true" checked onchange=\'$("#'+varp+'").val("true");\'> T'+
			   '<input class="'+varp+'" type="radio" name="'+varp+'" id="'+varp+'_false" value="false" onchange=\'$("#'+varp+'").val("false");\'> F' + 
			   '<input type="hidden" class="'+varp+'" name="'+varp+'" id="'+varp+'" value="true"> ';
	$("#label_"+varp).after(html);	
}

$( document ).ready(function() {
	var id = 0;
	var LASER_ACTION = 100004;
	var ROVER_STOP 	= 100002;
	var ROVER_MOVE_MANUAL_BODY = 100001;
	var ROVER_SERIAL_CMD_GET_IP = 100003;
	var SERVO_ACTION_CONTINUOUS = 200001;
	var SERVO_ACTION_ANGLE = 200002;
	var SERVO_STOP = 200003;
	var OBSTACLE_READER = 300001;
	
	$("#command").change(function() {
		reconstruct();
		$(".params").removeAttr('disabled');
		if(this.value == LASER_ACTION){
			$("#tooltiptext_p1").html("Indica el estado del laser, true=activo, false=inactivo");
			$("#tooltiptext_p2").html("Tiempo en [ms] en ejecutar la acci\u00F3n del laser");
			$("#p3").attr('disabled','disabled');
			$("#p4").attr('disabled','disabled');
			$("#p5").attr('disabled','disabled');
			$("#p6").attr('disabled','disabled');
			$("#p7").attr('disabled','disabled');
			$("#p2").val(0);
			constructTrueFalse("p1");
		}
		if(this.value == ROVER_STOP){
			$("#tooltiptext_p1").html("Indica el tipo de rover, por ejemplo 2WD");
			$("#tooltiptext_p2").html("Tiempo en que se detiene en milisegundos, 0 se detiene inmediato");
			$("#tooltiptext_p3").html("Indica la distancia que recorre antes de detenerse");			
			$("#p4").attr('disabled','disabled');
			$("#p5").attr('disabled','disabled');
			$("#p6").attr('disabled','disabled');
			$("#p7").attr('disabled','disabled');				
			$("#p2").val(0);
			constructSelectRoverType("p1");								
		}		
		if(this.value == ROVER_MOVE_MANUAL_BODY){
			$("#tooltiptext_p1").html("Indica el tipo de rover, por ejemplo 2WD");
			$("#tooltiptext_p2").html("Delay en milisegundos, 0 inicia de inmediato");
			$("#tooltiptext_p3").html("Indica la distancia que recorre antes de detenerse");
			$("#tooltiptext_p4").html("Indica sentido del movimiento");
			$("#p2").val(0);
			$("#p5").attr('disabled','disabled');
			$("#p6").attr('disabled','disabled');
			$("#p7").attr('disabled','disabled');				
			constructSelectRoverType("p1");		
			constructSelectRoverMoveType("p4");			
		}	
		if(this.value == ROVER_SERIAL_CMD_GET_IP){
			$("#tooltiptext_p1").html("Si se encuentra en true devuelve la MAC");
			$("#p2").attr('disabled','disabled');
			$("#p3").attr('disabled','disabled');
			$("#p4").attr('disabled','disabled');
			$("#p5").attr('disabled','disabled');
			$("#p6").attr('disabled','disabled');
			$("#p7").attr('disabled','disabled');
			constructTrueFalse("p1");
		}		
		
		if(this.value == SERVO_ACTION_CONTINUOUS){
			$("#tooltiptext_p1").html("Indica el tipo de servo");
			$("#tooltiptext_p2").html("Tiempo en [ms] en ejecutar la acci\u00F3n del servo");
			$("#tooltiptext_p3").html("Indica el servo que ejecuta la acci\u00F3n");
			$("#tooltiptext_p4").html("Indica el sentido del movimiento del servo");
			$("#tooltiptext_p5").html("Grados que recorre el servo cada 15 [ms]");
			$("#p6").attr('disabled','disabled');
			$("#p7").attr('disabled','disabled');
			$("#p2").val(0);
			$("#p5").val(2);			
			constructSelectServoType("p1");
			constructServoDirection("p3");
			constructServoMove("p4");
		}		
		
		if(this.value == SERVO_ACTION_ANGLE){
			$("#tooltiptext_p1").html("Indica el tipo de servo");
			$("#tooltiptext_p2").html("Tiempo en [ms] en ejecutar la acci\u00F3n del servo");
			$("#tooltiptext_p3").html("Indica el servo que ejecuta la acci\u00F3n");
			$("#tooltiptext_p4").html("\u00C1ngulo que se mueve el servo");
			$("#p5").attr('disabled','disabled');
			$("#p6").attr('disabled','disabled');
			$("#p7").attr('disabled','disabled');
			$("#p2").val(0);
			$("#p4").val(90);			
			constructSelectServoType("p1");
			constructServoDirection("p3");
		}	
		
		if(this.value == SERVO_STOP){
			$("#tooltiptext_p1").html("Indica el tipo de servo");
			$("#tooltiptext_p2").html("Tiempo en [ms] en ejecutar la acci\u00F3n del servo");
			$("#tooltiptext_p3").html("Indica el servo que ejecuta la acci\u00F3n");
			$("#p4").attr('disabled','disabled');
			$("#p5").attr('disabled','disabled');
			$("#p6").attr('disabled','disabled');
			$("#p7").attr('disabled','disabled');
			$("#p2").val(0);
			constructSelectServoType("p1");
			constructServoDirection("p3");
		}	
		
		if(this.value == OBSTACLE_READER){
			$("#tooltiptext_p1").html("Indica el tipo de Sensor de Obst\u00E1culos");
			$("#tooltiptext_p2").html("Indica la orientaci\u00F3n del sensor");
			$("#p3").attr('disabled','disabled');
			$("#p4").attr('disabled','disabled');
			$("#p5").attr('disabled','disabled');
			$("#p6").attr('disabled','disabled');
			$("#p7").attr('disabled','disabled');
			constructObstacleServoType("p1");
			constructObstacleDirection("p2");
		}	
		
		
	});
	$("#agregar").click(function() {
		id++;		
		var cmd = $("#command").val();
		if(cmd > 0){
			var cmdTxt = $("#command option:selected").text();
			var p1 = $("#p1").val();
			var p2 = $("#p2").val();
			var p3 = $("#p3").val();
			var p4 = $("#p4").val();
			var p5 = $("#p5").val();
			var p6 = $("#p6").val();
			var p7 = $("#p7").val();
			var htmlTr = "<tr><td>"+id+"</td><td>"+cmdTxt+"</td><td>"+p1+"</td><td>"+p2+"</td><td>"+p3+"</td><td>"
						+p4+"</td><td>"+p5+"</td><td>"+p6+"</td><td>"+p7+"</td></tr>";
			$('#tablePipeline tr:last').after(htmlTr);
			pipeline.push(TIPO_CALL+","+$("#command option:selected").val()+","+p1+","+p2+","+p3+","+p4+","+p5+","+p6+","+p7);
		}
	});
	$("#ejecutar").click(function() {
		var data = new FormData();	
		for	(j = 0; j < pipeline.length; j++){
			data.append('cmd['+j+']', pipeline[j]);
		}

		var xhr = new XMLHttpRequest();
		xhr.open('POST', '../pipelineCmd', true);
		xhr.onload = function () {
			//console.log(this.responseText);
			alert(this.responseText);
		};
		xhr.send(data);		
	});	
});