#include <ESP8266WiFi.h>  
#include <ESP8266WebServer.h> 
#include <Ticker.h>    
#include <FS.h>
#include <ArduinoJson.h> 
#include <NTPClient2.h>
#include <WiFiUdp.h>



String ssid = "Hubble"; //Сеть по умолчанию
String password = "scarletrose90"; //Пароль по умолчанию
String jsonConfig = "{}";//Переменная для обработки файла конфигурации
String jsonData = "{}"; //хранение данных о включении
String stateOf ="AP"; //какой режим включен
int sensorValue = 0; //глобальная переменная, съем данных с сенсора
String dataOfStart[10]={"1","2","3","4","567890"};//{"0000000","44444441","000002","355555","47777","555555","6789"}; //массив времени
int startViwe = 16; //d0 запуск датчика
int motorPin = 14; //пин подключения насоса
bool flagMotor = false; //флаг запуск насоса
Ticker ticker;
// Web интерфейс для устройства
ESP8266WebServer HTTP(80);
// Для файловой системы
File fsUploadFile;
//time
const long utcOffsetInSeconds = 3600*3;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ru.pool.ntp.org", utcOffsetInSeconds);

//подключение к регулированию с помощью ШИМ
int ENA = 15; //считываем с датчика D8

void showArr()
{
   Serial.println("Array:");
  for(int i = 0; i < 10; i++)
  {
     Serial.println(dataOfStart[i]);
  }
}

//функция проверки уровня влажности
void checking()
{
  Serial.println("Start");
  digitalWrite(startViwe, HIGH);
  //delay(10);

   int sensorValue = analogRead(A0);
   int value =  rangeInt(sensorValue);
   if(value < 20 )
   {
      startWater(0);
      flagMotor= true;
   }
   else
   {
      if(flagMotor)
      {
        flagMotor = false;
        startWater(1);
      }
   }
   myDelay(10);
   digitalWrite(startViwe, LOW);
   timeNTP();
}



void setup() {
  Serial.begin(9600);
  pinMode(startViwe, OUTPUT);
  pinMode(motorPin, OUTPUT);
  digitalWrite(motorPin, LOW);
  showArr();
  FS_init();
  //saveDataArr();
  loadConfig();
  Serial.println("Data file going to load");
  loadData();
  showArr();
  if(stateOf == "STA")
     WIFIinit();
  else
     StartAPMode();
  HTTP_init();
  timeClient.begin();
  timeNTP();
  ticker.attach(3,checking);
}

void loop() {
  HTTP.handleClient();
  delay(10);
}
