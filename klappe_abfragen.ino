/***********************************************************************************************
status klappe abfragen , D2

*** 1 = offen/oben , 0 = zu/unterwegs
 
************************************************************************************************/
void Klappe_abfragen() {
 
   int KlappePinStatus = digitalRead(KlappePin); // *** HIGH/LOW
   
   if (KlappePinStatus == HIGH) {  
        klappe = 0; // *** 0 = zu/unterwegs  
   } else {
        klappe = 1; // *** 1 = offen/oben
   }
   
 
   /*klappenstatus_eingelesen = analogRead(klappenstatus); // *** read the value on analog input
 
   if (klappenstatus_eingelesen > 800) { // *** klappe ist offen !
           klappe = 2; // 0 = zu , 1 = auf dem weg, 2 = offen
   }
    
   if (klappenstatus_eingelesen < 799) { // *** klappe ist nicht oben ... (unterwegs?)
           klappe = 1; // 0 = zu , 1 = auf dem weg, 2 = offen
           if (klappenstatus_eingelesen < 100) { // *** klappe ist unten !
                   klappe = 0; // 0 = zu , 1 = auf dem weg, 2 = offen
           }
   }
   */
}

/***********************************************************************************************
status klappe anzeigen
************************************************************************************************/
void Klappe_anzeigen() {
   
  
  lcd.setCursor(0,3);
  lcd.print("Klappe: ");
  
                  
  if (klappe == 0) {
    // *** klappe ist unten / unterwegs
    lcd.write(5); // *** sonderzeichen - klappe unten
    lcd.print(" unten ");
    Serial.println(">[KLAPPE-STATUS] Klappe ist unten ");
  }
  /*
  if (klappe == 1) {
    // *** klappe ist unterwegs  
    lcd.print("?"); 
    lcd.print(" mitte");
    Serial.println(">[KLAPPE-STATUS] Klappe ist unterwegs ");
  }
  */
  if (klappe == 1) {
    // *** klappe ist oben  
    lcd.write(6); // *** sonderzeichen - klappe oben
    Serial.println(">[KLAPPE-STATUS] Klappe ist oben ");
    lcd.print(" offen ");
  }
}


