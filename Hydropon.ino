#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h> 
#include <Ticker.h>    
#include <FS.h>
#include <ArduinoJson.h> 
#include <NTPClient2.h>
#include <WiFiUdp.h>
#include <cron.h>


String ssid = "Hubble"; //Сеть по умолчанию
String password = "scarletrose90"; //Пароль по умолчанию
String jsonConfig = "{}";//Переменная для обработки файла конфигурации
String jsonData = "{}"; //хранение данных о включении
String stateOf ="AP"; //какой режим включен
int sensorValue = 0; //глобальная переменная, съем данных с сенсора
//String dataOfStart[10]={"1","2","3","4","567890"}; //массив времени
String dataOfStart; //дата для передачи
int startViwe = 16; //d0 запуск датчика
int motorPin = 14; //пин подключения насоса
bool flagMotor = false; //флаг запуск насоса
bool flag = 0;
String dataString; //переменная для даты
Ticker ticker;
// Web интерфейс для устройства
ESP8266WebServer HTTP(80);
// Для файловой системы
File fsUploadFile;
//time
const long utcOffsetInSeconds = 3600*3;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ru.pool.ntp.org", utcOffsetInSeconds);
//---------------------------------------test---------------
//int count = 1;
//----------------------------------------------------------
//подключение к регулированию с помощью ШИМ
int ENA = 15; //считываем с датчика D8

//функция проверки уровня влажности
void checking()
{
  //Serial.println("Start");
  digitalWrite(startViwe, HIGH);
  myDelay(10);
  sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  int value =  rangeInt(sensorValue);
  //Serial.println(value);
   if(value < 20 )
   {
      //Serial.println("value < 20");
      startWater(0);
      flagMotor = true;
      dataOfStart = returnData();
      delay(10);
      //Serial.println(dataOfStart);
      saveData(dataOfStart);
   }
   else
   {
    //Serial.println("value >>>>> 20");
      if(flagMotor)
      {
        Serial.println("We are here");
        flagMotor = false;
        startWater(1);
      }
   }
   myDelay(10);
   
  /* if((count%5) == 0)
   {    
      flag = 1;
   }
   if((count%10) == 0)
   {     
     Serial.println("We are here");   
     flag = true;
   }
   Serial.println("Start2");
   count++;*/
   digitalWrite(startViwe, LOW);
}



void setup() {
  Serial.begin(9600);
  pinMode(startViwe, OUTPUT);
  pinMode(motorPin, OUTPUT);
  digitalWrite(motorPin, HIGH);
  FS_init();
  loadConfig();
  if(stateOf == "STA")
     WIFIinit();
  else
     StartAPMode();
  HTTP_init();
  timeClient.begin();
  if ( WiFi.status() == WL_CONNECTED)
  {
     timeNTP();
     //Serial.println(loadData());
     dataOfStart = loadData();
  }
  else
  {
     dataOfStart = "1989-09-17T03:00:20Z";
  }
  //ticker.attach(3,checking);
  cron.add(3000,checking);
}

int count = 0;

void loop() {
  HTTP.handleClient();
  cron.handleEvents();
  delay(10);
}
