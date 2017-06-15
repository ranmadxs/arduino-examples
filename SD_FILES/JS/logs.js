var TIPO_CALL = "SERIAL";
var ipClient = "${clientIp}"; 
var ipClient = "192.168.100.103";
var init = 1;
var end = 4;

function actCmd(cmd, p1, p2, p3, p4, p5, p6, p7) { 
	p1 = p1 || 'None'; 
	p2 = p2 || 'None'; 
	p3 = p3 || 'None'; 
	p4 = p4 || 'None'; 
	p5 = p5 || 'None'; 
	p6 = p6 || 'None'; 
	p7 = p7 || 'None'; 
	
	var url ='http://'+ipClient+'/cmd?TIPO_CALL='+TIPO_CALL+'&COMMAND='+cmd+'&P1='+p1+'&P2='+p2+'&P3='+p3+'&P4='+p4+'&P5='+p5+'&P6='+p6+'&P7='+p7;
	alert(url);
	document.getElementById("iframeLogs").contentDocument.location.reload(true);
}

$( document ).ready(function() {
	$("#siguiente").click(function(){
		init = end;
		end = end + 4;
		actCmd('100005', init, end);		
	});
	$("#anterior").click(function(){
		end = init;
		init = init - 4;
		if (init < 1){
			init = 1;
			end = 4;
		}
		actCmd('100005', init, end);		
	});	
});