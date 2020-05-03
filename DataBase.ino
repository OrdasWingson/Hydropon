bool loadData() {
  // Открываем файл для чтения
  File dataFile = SPIFFS.open("/data.db", "r");
  if (!dataFile) {
  // если файл не найден  
  //  Создаем файл запиав в него даные по умолчанию
    saveDataArr();
    dataFile.close();
    return false;
  }
  // Проверяем размер файла, будем использовать файл размером меньше 1024 байта
  size_t size = dataFile.size();
  if (size > 1024) {
    Serial.println("Data file size is too large");
    dataFile.close();
    return false;
  }

// загружаем файл конфигурации в глобальную переменную
  char symb;
  for(int i = 0; i < 10; i++)
  { 
    dataOfStart[i]=""; //очищаем
    symb = char(dataFile.read());   
    while(symb != '\n')
    {
      dataOfStart[i] += symb;
      symb = char(dataFile.read());
    }
    
    
  }
  /*while(file.available()){
    Serial.write(dataFile.read());*/
  dataFile.close();
}



// Запись данных в файл 
bool saveDataArr() {
  //для избежания дублежа записи
  if(SPIFFS.exists("/data.db"))
  {
    SPIFFS.remove("/data.db");
  }
  
  File dataFile = SPIFFS.open("/data.db", "a");
  if (!dataFile) {
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
}


bool saveData() {
  File dataFile = SPIFFS.open("/data.db", "a");
  if (!dataFile) {
    //Serial.println("Failed to open config file for writing");
    dataFile.close();
    return false;
  }
  
  size_t size = dataFile.size();
  if (size > 101) {
    dataFile.close();
    SPIFFS.remove("/data.db");
    dataFile = SPIFFS.open("/data.db", "a");
    Serial.println("Data file size is too large");
  }
  
  for(int i = 0; i < 10; i++)
  {
    dataFile.print(dataOfStart[i]+"\n");
  }
  dataFile.close();
  return true;
}
