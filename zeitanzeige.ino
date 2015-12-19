// *** interne uhr ausgeben ************************************************** 
void zeige_Datum(DateTime datetime){
 

  lcd.setCursor(0,0);
  // Wochentag, Tag.Monat.Jahr
  lcd.print(get_day_of_week(datetime.dayOfWeek()));
  lcd.print(", ");
  if(datetime.day()<10)lcd.print(0);
  lcd.print(datetime.day(),DEC);
  lcd.print(".");
  if(datetime.month()<10)lcd.print(0);
  lcd.print(datetime.month(),DEC);
  lcd.print(".");
  lcd.print(datetime.year(),DEC);
  
  lcd.setCursor(0,1);
  // Stunde:Minute:Sekunde
  if(datetime.hour()<10)lcd.print(0);
  lcd.print(datetime.hour(),DEC);
  lcd.print(":");
  if(datetime.minute()<10)lcd.print(0);
  lcd.print(datetime.minute(),DEC);
  lcd.print(":");
  if(datetime.second()<10)lcd.print(0);
  lcd.print(datetime.second(),DEC);
  lcd.print(" Uhr");

  jetzt_monat = (int)datetime.month() ; // *** wandele uint8_t {aka unsigned char} to dec
  jetzt_tag = (int)datetime.day() ; // *** wandele uint8_t {aka unsigned char} to dec
  jetzt_stunde = (int)datetime.hour() ; // *** wandele uint8_t {aka unsigned char} to dec
  jetzt_minute = (int)datetime.minute() ; // *** wandele uint8_t {aka unsigned char} to dec
  jetzt_sekunde = (int)datetime.second() ; // *** wandele uint8_t {aka unsigned char} to dec
}




