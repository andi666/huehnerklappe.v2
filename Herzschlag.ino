// *** LED HERZSCHLAG ******************************************
void LED_HERZSCHLAG() {
  unsigned long aktuelleZeit = millis();
  
  if( aktuelleZeit - LED_interval >= LED_setZeit ) { // *** es ist genügend Zeit vergangen, eine Änderung kann vorgenommen werden
   
        if ( LED_status == LOW) {
            LED_status = HIGH;
            lcd.setCursor(19,0);
            lcd.write(4);  // *** Sonderzeichen ausgeben
            
        } else {
            LED_status = LOW;
            lcd.setCursor(19,0);
            lcd.print(" "); 
            
        }
        digitalWrite(LED_pin, LED_status ); // set the LED with the ledState of the variable
        LED_setZeit = aktuelleZeit;
  }
}
