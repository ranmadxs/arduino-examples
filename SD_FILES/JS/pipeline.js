$( document ).ready(function() {
	var id = 0;
	var LASER_ACTION = 100004;
	var ROVER_STOP 	= 100002;
	$("#command").change(function(){
		$(".params").removeAttr('disabled');
		if(this.value == LASER_ACTION){
			$("#p3").attr('disabled','disabled');
			$("#p4").attr('disabled','disabled');
			$("#p5").attr('disabled','disabled');
			$("#p6").attr('disabled','disabled');
			$("#p7").attr('disabled','disabled');
			$( ".p1" ).remove();
			var htmlP1 = '<input class="p1" type="radio" name="p1" id="p1_true" value="true" checked> True'+
						 '<input class="p1" type="radio" name="p1" id="p1_false" value="false" checked> False';
			$("#label_p1").after(htmlP1);			
		}
		if(this.value == ROVER_STOP){
			$("#p4").attr('disabled','disabled');
			$("#p5").attr('disabled','disabled');
			$("#p6").attr('disabled','disabled');
			$("#p7").attr('disabled','disabled');
			$( ".p1" ).remove();
			var htmlP1 = '<select name="p1" id="p1">'+
						 '</select>';
			$("#label_p1").after(htmlP1);			
		}		
	});
	$("#agregar").click(function(){
		id++;		
		var cmd = $("#command").val();
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
	});
	$("#ejecutar").click(function(){
		alert( "Click ejecutar" );
	});	
});