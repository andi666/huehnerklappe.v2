/*************************************************************************************

zeitgesteuert klappe auf/zu 

  1 = offen/oben , 0 = zu/unterwegs
 
Zeitsteuerung:
--------------------------------
Monat auf    zu
01    09:00  19:00
02    09:00  20:00
03    09:00  20:00
04    09:00  21:00
05    09:00  21:00
06    08:00  22:00
07    08:00  22:00
08    08:00  21:00
09    08:00  20:00
10    08:00  20:00
11    09:00  19:00
12    09:00  19:00

**************************************************************************************/
void Zeit_Aktion(DateTime datetime) { 


      
  // *** monat,stunde
  if(jetzt_monat == 1){     zeit_auf = 9;    zeit_zu = 19;}
  if(jetzt_monat == 2){     zeit_auf = 9;    zeit_zu = 20;}
  if(jetzt_monat == 3){     zeit_auf = 9;    zeit_zu = 20;}
  if(jetzt_monat == 4){     zeit_auf = 9;    zeit_zu = 21;}
  if(jetzt_monat == 5){     zeit_auf = 9;    zeit_zu = 21;}
  if(jetzt_monat == 6){     zeit_auf = 9;    zeit_zu = 22;}
  if(jetzt_monat == 7){     zeit_auf = 9;    zeit_zu = 22;}
  if(jetzt_monat == 8){     zeit_auf = 9;    zeit_zu = 21;}
  if(jetzt_monat == 9){     zeit_auf = 9;    zeit_zu = 20;}
  if(jetzt_monat == 10){    zeit_auf = 9;    zeit_zu = 20;}
  if(jetzt_monat == 11){    zeit_auf = 9;    zeit_zu = 19;}
  if(jetzt_monat == 12){    zeit_auf = 9;    zeit_zu = 19;}                

  lcd.setCursor(17, 2);
  lcd.write(8);  // *** Sonderzeichen ausgeben
  lcd.print(zeit_auf);
  lcd.setCursor(17, 3);
  lcd.write(7);  // *** Sonderzeichen ausgeben
  lcd.print(zeit_zu);
  
  if (automatik >= 1) { // *** automatik ist eingeschaltet, timer kann abgearbeitet werden
         
      // *** nach oben *** // *** ab xx uhr soll die klappe >auf< gehen ...   
      //if( jetzt_stunde == 15 && datetime.minute() == 58)  {  // *** DEBUG! *** 
      if( jetzt_stunde == zeit_auf && jetzt_minute == 0)  {   // *** ab minute '0' die aktion beginnen  
             
                  if(klappe == 0){  // *** 1 = offen/oben , 0 = zu/unterwegs
                        // klappe ist >auf dem weg< oder >offen<
                        Serial.println(">[Zeit-AKTION] Klappe soll hoch ");
                        motor_hoch(); // ... klappe auf!
                        
                  } else {

                        // ...nix machen , da klappe bereits >auf< ist
                        motor_stop();
                  }
  
        }
      

      
        // *** nach unten *** ab xx uhr soll die klappe >zu< gehen ...motor soll maximal xx sekunden 
        //if( jetzt_stunde == 18 && jetzt_minute == 21 )    {  // *** DEBUG! ***
        if( jetzt_stunde == zeit_zu && jetzt_minute == 0 && jetzt_sekunde <= 35)  {   // *** ab minute '0' die aktion beginnen , maximal 35 sekunden, dann aufhoeren  
  
             
                   
                     // klappe ist >unterwegs< oder >offen<
                       
                       //lcd.setCursor(14,2);
                       //lcd.print(jetzt_sekunde);
                       
                       if (jetzt_sekunde <= 35) {
                          Serial.println(">[Zeit-AKTION] Klappe soll runter ");
                          motor_runter(); // ... klappe zu fahren 
                       }  else {

                        // ...nix machen , da klappe bereits >zu< ist (sein sollte)
                        motor_stop();
                       }
                      
         
 
        }  
        
  } 
  
}

