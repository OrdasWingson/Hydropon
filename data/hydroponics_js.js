function getAddres(addres)
{
	addres=addres.substr(addres.indexOf("/")+2, addres.length);
	addres=addres.substr(0,addres.indexOf("/"));
	return addres;
}



$(document).ready(function(){
		

	var addres = getAddres(location.href);
	var waterLevel //уровень влажности
	
	setInterval(() => { $(document).load('http://'+ addres +'/level', function(lvl){ // 'http://'+ addres +'/level' 'http://127.0.0.1:8085/test.html'
	$('.attendance-level').css('height',lvl);});}, 5000);
		//$(arrButtID[i]).css('visibility','visible');
	
	
});


				