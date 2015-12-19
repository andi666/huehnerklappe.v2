/*****************************************************************************
schalter für klappe >>> händisch <<< auf/zu
******************************************************************************/
void S1_abfragen() { 

    S1_klappeaufzu = analogRead(klappeaufzueingang); // *** read the value on analog input
 
    if (automatik == 0 ) { // *** nur ausführen, wenn auf >>> HAND <<< gestellt!
    
    // *** es ist auf >>> HAND <<< eingestellt  
        
        if (S1_klappeaufzu > 800) { // *** per hand-schalter: klappe soll auf(!)  
            
              if ( klappe == 1 ){; // *** 1 = offen/oben , 0 = zu/unterwegs 
                // NIX, da klappe bereits oben ist
                
              } else {
                
                //lcd.setCursor(16,3);
                //lcd.print(S1_klappeaufzu);
                
                klappesoll = 1;
                motor_hoch();
                Serial.println(">[HAND] Klappe hoch fahren! ");
            
              }
        }
        
        
        
        if (S1_klappeaufzu < 200) { // *** per hand-schalter: klappe soll runter(!)  
            
                //lcd.setCursor(16,3);
                //lcd.print(S1_klappeaufzu);
   
              //if ( klappe == 0 ){; // *** 1 = offen/oben , 0 = zu/unterwegs 
                // NIX, da klappe bereits zu ist
                
              //} else {
 
                klappesoll = 0; 
                motor_runter();
                Serial.println(">[HAND] Klappe runter fahren! ");
             // }
            
        }
       
        if (S1_klappeaufzu < 799) { // *** keine aktion , schalter-stellung nicht eindeutig  
           if (S1_klappeaufzu > 101) {
 
              klappesoll = 2;  
              motor_stop();
             
           }
         }
      
      
    } 
}

