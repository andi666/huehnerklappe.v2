/**************************************************************************
Huenerklappe, mit RTC (i2c) und LCD (i2c)
v2.2
14-OKT-2015 
andreas langkath , langkath@gmx.de
MIT license

youtube: https://youtu.be/BAS_Z18NrG4
code:		 https://github.com/andi666/huehnerklappe.v2
 

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
**************************************************************************/
#include "Wire.h"    //  *** Comes with Arduino IDE
#include "LiquidCrystal_I2C.h" // *** LCD Bibliothek
#include "RTClib.h"  // *** RTC-Bibliothek einbinden
#include "DS18S20.h" // *** temperatur-sensor Bibliothek

RTC_DS1307 RTC;      // *** RTC Modul

const int KlappePin = 2; // *** magnetschalter 

int LED_pin = 13;  // *** LED HERZSCHLAG
int LED_status = LOW;  // *** used to set the LED
long LED_setZeit = 0;  // *** will store last time LED was updated
long LED_interval = 1000;  // *** LED-HERZSCHALG-Intervall (milliseconds)
int alte_sekunde; 

int jetzt_monat;
int jetzt_tag;
int jetzt_stunde;
int jetzt_minute; 
int jetzt_sekunde;
  
#define MOTORRICHTUNG_A 10   // *** digital-Pin 8 (hoch)
#define MOTORRICHTUNG_B 9    // *** digital-Pin 9 (runter)
#define klappeaufzueingang 2 // *** analog-eingang a2
#define manuautoeingang 3    // *** analog-eingang a3
//#define klappenstatus 1      // *** analog-eingang a1

int zeit_auf = 9; // *** fuer zeitsteuerung
int zeit_zu = 22; // *** fuer zeitsteuerung
 

DS18S20_List ds18s20(7);     // *** Temperatursensor (pin D7)

int S1_klappeaufzu = 0;
uint8_t klappe = 0; // *** 0 = zu , 1 = auf dem weg, 2 = offen
uint8_t klappesoll = 2; // *** 2 = kein befehl, 0 = soll zu , 1 = soll auf
uint8_t motorrichtung = 1; // *** dient der Anzeige / motorrichtung = 0 (hoch) , motorrichtung = 1 (nix) , motorrichtung = 2 (runter) 
int automatik = 0;
int manuhand = 0;
int klappenstatus_eingelesen = 0; // analog-wert von den reed-relais (0..1024)
 
// *** eigene Sonder-Zeichen basteln *****************************************
 byte gradc[8] = { // eigenes grad C-zeichen
	B01100,
	B10100,
	B11000,
	B00011,
	B00100,
	B00100,
	B00100,
	B00011
};

byte herz[8] = {
  B00000,
  B01010,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000,
  B00000
};

byte klappe_unten[8] = { // *** eigenes Sonder-Zeichen erstellen (Klappe runter)
	B10001,
	B10001,
	B10001,
	B10001,
	B11111,
	B11111,
	B11111,
	B11111
};

byte klappe_oben[8] = { // *** eigenes Sonder-Zeichen erstellen (Klappe hoch)
	B11111,
	B11111,
	B11111,
	B11111,
	B10001,
	B10001,
	B10001,
	B10001
};

byte pfeilrunter[8] = { // *** eigenes Sonder-Zeichen erstellen (pfeil runter)
	B00000,
	B00100,
	B00100,
	B00100,
	B11111,
	B01110,
	B00100,
	B00000
};

byte pfeilhoch[8] = { // *** eigenes Sonder-Zeichen erstellen (pfeil hoch)
	B00000,
	B00100,
	B01110,
	B11111,
	B00100,
	B00100,
	B00100,
	B00000
};

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

// *** setup ********************************************************************************
void setup(void) {

  Wire.begin();// Initialisiere I2C 
  RTC.begin();// Initialisiere RTC
  
  pinMode(LED_pin, OUTPUT); // *** für LED HERZSCHLAG
  
  pinMode(MOTORRICHTUNG_A, OUTPUT); // setzt ‘pin’ als Ausgang 
  pinMode(MOTORRICHTUNG_B, OUTPUT); // setzt ‘pin’ als Ausgang 
  pinMode(KlappePin, INPUT); // *** magnetschalter
  
  lcd.begin(20,4);
  lcd.createChar(1, gradc);    // *** eigene Sonder-Zeichen aktivieren
  lcd.createChar(4, herz);  // *** eigene Sonder-Zeichen aktivieren
  lcd.createChar(5, klappe_unten);     // *** eigene Sonder-Zeichen aktivieren
  lcd.createChar(6, klappe_oben);     // *** eigene Sonder-Zeichen aktivieren
  lcd.createChar(7, pfeilrunter);    // *** eigene Sonder-Zeichen aktivieren
  lcd.createChar(8, pfeilhoch);    // *** eigene Sonder-Zeichen aktivieren
  
  
  
  Serial.begin(9600);
  lcd.setCursor(0, 0);
  
  // *** versionsnummer beim start anzeigen  
  lcd.setCursor(0,0);
  Serial.println("");
  Serial.println("");
  Serial.println("********************** ");
  lcd.print("* Huehnerklappe ");
  Serial.println("* Huehnerklappe "); 
  lcd.setCursor(0,1); 
  lcd.print("* v2.2 , 14-OKT-2015 "); 
  Serial.println("* v2.2 , 14-OKT-2015 ");
  lcd.setCursor(0,2); 
  lcd.print("* Andreas Langkath "); 
  Serial.println("* Andreas Langkath ");
  lcd.setCursor(0,3); 
  lcd.print("* info@langkath.de ");
  Serial.println("* info@langkath.de ");
  Serial.println("********************** ");
  delay(3000); // *** 3 sekunden warten
  lcd.clear();
  
  motor_stop(); // sicherheitshalber erst mal aus ...

}

