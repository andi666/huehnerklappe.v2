// *** programm ********************************************************
void loop(void) {
  

  if (! RTC.isrunning()) {
    Serial.println("RTC laeuft nicht!");
    lcd.setCursor(0,1);
    lcd.print("RTC laeuft nicht!");
    
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
   
  
  DateTime now = RTC.now(); // *** aktuelle Zeit abrufen
  zeige_Datum(now);  // *** Datum und Uhrzeit ausgeben
 

 
    
  Klappe_abfragen();         // *** ist klappe zu oder offen ?
  S1_abfragen();             // *** schalter für klappe händisch auf/zu
  S2_abfragen();             // *** schalter für auto / hand - umschaltung
  Klappe_anzeigen();         // *** anzeigen, wo die klappe sich befindet
  motorrichtung_anzeigen();  // *** anzeigen, ob und in welche richtung sich die klappe sich bewegt
  LED_HERZSCHLAG();    // *** rufe unterprogramm auf
  temperatur();        // *** rufe unterprogramm auf
  Zeit_Aktion(now);       // *** rufe unterprogramm auf
  
 
}
// *** end loop *****************************************************************
 
 
