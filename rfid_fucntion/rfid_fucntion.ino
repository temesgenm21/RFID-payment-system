

#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

LiquidCrystal  lcd(15,0,16,17,18,19);

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);

String readCard;


void getCardUID() // to get the UID of Cards 
{
  // Getting ready for Reading PICCs
  if ( ! mfrc522.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {   //Since a PICC placed get Serial and continue
    return;
  }
  Serial.print(F("scanned card :"));
  readCard = "";
  for ( int i = 0; i < mfrc522.uid.size; i++) {  //
    readCard = readCard + String(mfrc522.uid.uidByte[i], HEX); // Conacatenate bytes of the card to get UID 
  }
  readCard.toUpperCase();
  mfrc522.PICC_HaltA(); // Stop reading
  lcd.clear();
  lcd.setCursor(0,0);// for checking
  lcd.print(readCard); 
  return;
}



void setup() {
  // put your setup code here, to run once:
 // Serial.begin(9600);
  lcd.begin(16,2);
 // while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
}

void loop() {
  // put your main code here, to run repeatedly:
analogWrite(14,120);
  getCardUID();


  //delay(1000);

}
