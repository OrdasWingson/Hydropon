
void timeNTP()
{
  String formattedDate;
  String dayStamp;
  String timeStamp;
 
  //timeClient.update();
  /*formattedDate = timeClient.getEpochTime();
  Serial.println(formattedDate);
  Serial.println(timeClient.getFormattedTime());*/
  formattedDate = timeClient.getFormattedDate();
  Serial.println(formattedDate);
}

void myDelay(int interval)
{
  unsigned long previousMillis = millis();
  unsigned long currentMillis = millis();

  while ((currentMillis - previousMillis) < interval) {
    currentMillis = millis();}
}

String returnData()
{
   while(!timeClient.update()) 
   {
    timeClient.forceUpdate();
   }
   return timeClient.getFormattedDate();
}
