var TIPO_CALL = "SERIAL";
var ipClient = "${clientIp}"; 
//var ipClient = "192.168.0.23";
var START_LOG = 1;
var END_LOG = 20;
var delta = 20;
var init;
var end;


function actCmd(cmd, p1, p2, p3, p4, p5, p6, p7) { 
	p1 = p1 || 'None'; 
	p2 = p2 || 'None'; 
	p3 = p3 || 'None'; 
	p4 = p4 || 'None'; 
	p5 = p5 || 'None'; 
	p6 = p6 || 'None'; 
	p7 = p7 || 'None'; 
	
	var url ='http://'+ipClient+'/cmd?TIPO_CALL='+TIPO_CALL+'&COMMAND='+cmd+'&P1='+p1+'&P2='+p2+'&P3='+p3+'&P4='+p4+'&P5='+p5+'&P6='+p6+'&P7='+p7;
	$('#iframeLogs').attr("src", url);
}

$( document ).ready(function() {
	init = START_LOG;
	end = END_LOG;
	
	$("#siguiente").click(function(){
		init = end;
		end = end + delta;
		actCmd('100005', init, end);		
	});
	$("#anterior").click(function(){
		end = init;
		init = init - delta;
		if (init < 1){
			init = START_LOG;
			end = END_LOG;
		}
		actCmd('100005', init, end);		
	});	
});