String loadData() {
  String tmp;
  // Открываем файл для чтения
  File dataFile = SPIFFS.open("/data.db", "r");
  if (!dataFile) {
  // если файл не найден  
  //  Создаем файл запиав в него даные по умолчанию
    dataFile.close();
    return "File not found.";
  }
  /*while(dataFile.available()){
    tmp = dataFile.readString();
  }*/
  tmp = dataFile.readString();
  dataFile.close();
  return tmp;
}



// Запись данных в файл 
/*bool saveDataArr() {
  //для избежания дублежа записи
  if(SPIFFS.exists("/data.db"))
  {
    SPIFFS.remove("/data.db");
  }
  
  File dataFile = SPIFFS.open("/data.db", "a");
  if (!dataFile) 
  {
    //Serial.println("Failed to open config file for writing");
    dataFile.close();
    return false;
  }
  
  for(int i = 0; i < 10; i++)
  {
    dataFile.print(dataOfStart[i]+"\n");
  }
  dataFile.close();
  return true;
}*/


bool saveData(String data) 
{
  File dataFile = SPIFFS.open("/data.db", "w");
  if (!dataFile) 
  {
    //Serial.println("Failed to open config file for writing");
    dataFile.close();
    return false;
  }
  dataFile.print(data);
  dataFile.close();
  return true;
}
