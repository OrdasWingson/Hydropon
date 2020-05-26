function getAddres(addres)
{
	addres=addres.substr(addres.indexOf("/")+2, addres.length);
	addres=addres.substr(0,addres.indexOf("/"));
	return addres;
}

function swap(addres) {

	$(document).load('http://'+ addres +'/level', function(lvlDt){
		var arrayOfStrings = lvlDt.split('?');
		$('#levelProc').text(arrayOfStrings[0]);
		$('.attendance-level').css('height',arrayOfStrings[0]);
		$('#Data').text(arrayOfStrings[1]);});
}



$(document).ready(function(){
	var addres = getAddres(location.href);
	swap(addres);

	
	var waterLevel //уровень влажности
	
	setInterval(() => {swap(addres);}, 5000);
		//$(arrButtID[i]).css('visibility','visible');
	
	
});
// 'http://'+ addres +'/level' 'http://127.0.0.1:8085/test.html'

				