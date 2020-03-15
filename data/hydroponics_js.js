function getAddres(addres)
{
	addres=addres.substr(addres.indexOf("/")+2, addres.length);
	addres=addres.substr(0,addres.indexOf("/"));
	return addres;
}



$(document).ready(function(){
		

	var addres = getAddres(location.href);
	var waterLevel //уровень влажности
	
	$(document).load('http://'+ addres +'/level', function(lvl){
		alert(lvl);
		//$(arrButtID[i]).css('visibility','visible');
	});
	
});


				