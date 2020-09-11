void moistureControl()
{
  value1 = analogRead(moisture_pin1);
  //Serial.println(value1);  //uncomment it for calibration
  
  //In the serial monitor see the readings when soil is dry & when soil is completely wet
  value1 = map(value1, 550, 10, 0, 100);
  // 500 means sensor gives 500 when soil is dry. Change it according to your test
  // 10 means sensor gives 10 when soil is wet. Change it according to your test
  // map function will convert the value to percentage.

  value2 = analogRead(moisture_pin2);
  //Serial.println(value2);  //uncomment it for calibration
  
  value2 = map(value2, 550, 10, 0, 100);

  value3 = analogRead(moisture_pin3);
  //Serial.println(value3);  //uncomment it for calibration
  
  value3 = map(value3, 550, 10, 0, 100);
}
