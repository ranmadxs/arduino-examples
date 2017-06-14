var TIPO_CALL = "SERIAL";
var ipClient = "${clientIp}"; 
var ipClient = "192.168.0.23";
function actCmd(cmd, p1, p2, p3, p4, p5, p6, p7) { 
	p1 = p1 || 'None'; 
	p2 = p2 || 'None'; 
	p3 = p3 || 'None'; 
	p4 = p4 || 'None'; 
	p5 = p5 || 'None'; 
	p6 = p6 || 'None'; 
	p7 = p7 || 'None'; 
	alert("Enviando data v222");
	//$.get( 'http://'+ipClient+'/cmd', 		
	//	{ TIPO_CALL: TIPO_CALL, COMMAND: cmd, P1: p1, P2: p2, P3: p3, P4: p4, P5: p5, P6: p6, P7: p7 }, function( data ) {
	//	alert("Resultado del envio:::");
	//	alert(data);
	//} );	
	$.ajax({
		method: "GET",
		url: 'http://'+ipClient+'/cmd',
		data: { TIPO_CALL: TIPO_CALL, COMMAND: cmd, P1: p1, P2: p2, P3: p3, P4: p4, P5: p5, P6: p6, P7: p7 },
		dataType: "jsonp",
		success: function(result){
			alert("XDDDDD");
		}
	});
	
    //var xhttp = new XMLHttpRequest();
	//xhttp.open('GET', 'http://'+ipClient+'/cmd?TIPO_CALL='+TIPO_CALL+'&COMMAND='+cmd+'&P1='+p1+'&P2='+p2+'&P3='+p3+'&P4='+p4+'&P5='+p5+'&P6='+p6+'&P7='+p7, false);
    //xhttp.setRequestHeader('Content-type', 'text/html');
	//var result = xhttp.send();
	//alert("Result:");
	//alert(result);	
}

$( document ).ready(function() {
	setInterval(function(){ 
		//alert("Hello"); 
		actCmd("100005", 1, 12, true);
	}, 3000);
});