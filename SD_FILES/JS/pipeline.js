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

function constructSelectType(varp){
	$( "."+varp ).remove();
	var html = '<select class="select_small_2 '+varp+'" id="p1" name="'+varp+'">'+
      '<option value="1001">ROVER_TYPE_2WD</option>'+
      '<option value="2001">SERVO_TYPE_SG90</option>'+
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
	$("#command").change(function(){
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
			constructTrueFalse("p1");
		}
		if(this.value == ROVER_STOP){
			$("#p4").attr('disabled','disabled');
			$("#p5").attr('disabled','disabled');
			$("#p6").attr('disabled','disabled');
			$("#p7").attr('disabled','disabled');				
			constructSelectType("p1");
									
		}		
	});
	$("#agregar").click(function(){
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
		}
	});
	$("#ejecutar").click(function(){
		alert( "Click ejecutar" );
	});	
});