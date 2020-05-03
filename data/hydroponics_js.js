function getAddres(addres)
{
	addres=addres.substr(addres.indexOf("/")+2, addres.length);
	addres=addres.substr(0,addres.indexOf("/"));
	return addres;
}

function swap(addres) {


  var data = new Date().toLocaleDateString(); // 19.12.2019
  var time = new Date().toLocaleTimeString(); // 11:02:48
	$(document).load('http://'+ addres +'/level?data='+data+'&time='+time, function(lvl){ 
		$('.attendance-level').css('height',lvl);});
}



$(document).ready(function(){
	var addres = getAddres(location.href);
	swap(addres);

	
	var waterLevel //уровень влажности
	
	setInterval(() => {swap(addres);}, 5000);
		//$(arrButtID[i]).css('visibility','visible');
	
	
});
// 'http://'+ addres +'/level' 'http://127.0.0.1:8085/test.html'

				