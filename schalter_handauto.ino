/****************************************************************************
schalter für auto / hand - umschaltung 
*****************************************************************************/
void  S2_abfragen() {
 
       	manuhand = analogRead(manuautoeingang); // *** read the value on analog input
 
        if (manuhand > 800) {
            automatik = 0;  // *** S2 steht auf 'hand'
            lcd.setCursor(0,2);
            //lcd.print(manuhand);
            lcd.print("Modus: hand");
            Serial.println(">[BETRIEB] hand");
  
        } else {
          
            automatik = 1; // *** S2 steht auf 'auto'
            lcd.setCursor(0,2);
            //lcd.print(manuhand);
            lcd.print("Modus: auto");
            Serial.println(">[BETRIEB] auto");  
        }
        
}
  
