void HTTP_init(void) {
  HTTP.on("/level", sendLevel); 
  HTTP.on("/config", conf); //обработка конфигурации 
  HTTP.on("/mode", changeMode); //смена режима работы сервера  
  // Запускаем HTTP сервер
  HTTP.begin();

}

void sendLevel()
{
   digitalWrite(startViwe, HIGH);
   delay(10);
   int sensorValue = analogRead(A0);
   digitalWrite(startViwe, LOW);
   HTTP.send(200, "text/plain", range(sensorValue)+'%');
   
}




//конфигурация
void conf()
{
  //root
  HTTP.send(200, "application/json", jsonConfig);
}


//режим подключения
void changeMode()
{
  stateOf = HTTP.arg("mode");
  //Serial.println("mode - " + stateOf); 
  
  if(stateOf == "STA"){
    ssid = HTTP.arg("ssid");
    //Serial.println("ssid - " + ssid);
    password = HTTP.arg("pass");
    //Serial.println("password - " + password);
    WiFi.disconnect();
    Serial.println("DISCONECT");
    WIFIinit();
  }
  if(stateOf == "AP"){
    Serial.println("AP START");
     StartAPMode();
  }
   HTTP.send(200, "text/plain", "OK"); // AP/STA
  saveConfig();
 
}

// функция пересчета

String range(int x)
{
  int y = (-x+680)/4.8;
  if ( y < 0 ) y = 0;
  if ( y > 100) y = 100;
  return String(y); 
}
