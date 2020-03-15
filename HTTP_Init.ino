void HTTP_init(void) {
  HTTP.on("/level", sendLevel);  
  // Запускаем HTTP сервер
  HTTP.begin();

}

void sendLevel()
{
   int sensorValue = analogRead(A0);
   Serial.println(sensorValue); 
   String value = String(sensorValue);
   Serial.print("string ");
   Serial.println(value); 
   HTTP.send(200, "text/plain", value);
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
