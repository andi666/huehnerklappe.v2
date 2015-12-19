/********************************************************************
temperatur auslesen und anzeigen (DS1820 sensor)
*********************************************************************/
void temperatur() {  

ds18s20.update(); 
 
  // *** temperatur anzeigen  
  
 
  
  lcd.setCursor(16, 1);
  
  if (ds18s20.get_temp(0) < 0){ // *** vorzeichen ***
    //lcd.print("");
  } else {
    lcd.print("+");
  }
  
  lcd.print(ds18s20.get_temp(0),0); // *** da nur ein sensor dran hängt, die '0' und '0' nachkommastellen
  
  lcd.setCursor(19, 1);
  lcd.write(1); // Sonderzeichen
  //lcd.print(" ");
  
  
  Serial.print(">[TEMP-SENSOR] "); 
  
  if (ds18s20.get_temp(0) < 0){ // *** vorzeichen ***
    //Serial.print("");
  } else {
    Serial.print("+");
  }
  
  Serial.print(ds18s20.get_temp(0),1); // *** da nur ein sensor dran hängt, die '0' + eine nachkommastellen 
  Serial.println("C");
 

}

