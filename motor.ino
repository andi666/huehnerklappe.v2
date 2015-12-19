// *** zeigt motor-richtung an ******************************************
void motorrichtung_anzeigen() {
    

    
    if (motorrichtung == 0){ // motorrichtung = 0 (hoch)  
      // *** klappe hoch
      lcd.setCursor(16,2);
      lcd.write(8); // *** sonderzeichen - pfeil hoch
      Serial.println(">[RICHTUNG] Klappe soll hoch ...");
    }
    
    if (motorrichtung == 1){ // motorrichtung =  1 (nix)  
      // *** klappe stop
      lcd.setCursor(16,2);
      lcd.print(" "); // *** pfeil rauf / runter weg machen !
      lcd.setCursor(16,3);
      lcd.print(" "); // *** pfeil rauf / runter weg machen !
      Serial.println(">[RICHTUNG] Klappe stop ...");
    }
    
    if (motorrichtung == 2){ // motorrichtung =  2 (runter) 
      // *** klappe runter
      lcd.setCursor(16,3);
      lcd.write(7); // *** sonderzeichen - pfeil runter
      Serial.println(">[RICHTUNG] Klappe soll runter ...");
    }

}

 

// *** klappe hoch *****************************************************
void motor_hoch() { 
    digitalWrite(MOTORRICHTUNG_A, HIGH); // motor richtung <-(High) / -> (LOW)  
    digitalWrite(MOTORRICHTUNG_B, LOW); // motor richtung <-(High) / -> (LOW)  
    motorrichtung = 0;
    Serial.println(">[MOTOR] hoch fahren! ");
}



// *** klappe runter (maximal 35 sekunde !) ****************************
void motor_runter() { 
    digitalWrite(MOTORRICHTUNG_A, LOW); // motor richtung <-(High) / -> (LOW)  
    digitalWrite(MOTORRICHTUNG_B, HIGH); // motor richtung <-(High) / -> (LOW)  
    motorrichtung = 2;
    Serial.println(">[MOTOR] runter fahren! ");
}



// *** motor stop! *****************************************************
void motor_stop() { 

    digitalWrite(MOTORRICHTUNG_A, LOW); // motor richtung <-(High) / -> (LOW)  
    digitalWrite(MOTORRICHTUNG_B, LOW); // motor richtung <-(High) / -> (LOW) 
    motorrichtung = 1;
    Serial.println(">[MOTOR] stop! ");
}

 
