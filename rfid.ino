/*
 * 
 * All the resources for this project: http://randomnerdtutorials.com/
 * Modified by Rui Santos & Mekel Ilyasa
 * 
 * Created by FILIPEFLOP
 * 
 */
 
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
 
#define SS_PIN 10
#define RST_PIN 9
#define BUZZ_PIN 8
#define RED_PIN 2
#define GREEN_PIN 5
MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo servo;
 
void setup() 
{
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  servo.attach(7);
  servo.write(90);
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  pinMode(BUZZ_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  digitalWrite(RED_PIN, HIGH);
}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "04 84 83 6A 80 61 80")
  {
    Serial.println("Authorized access");
    Serial.println();
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
    tone(BUZZ_PIN, 1000, 200);
    servo.write(0);
    delay(2000);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(RED_PIN, HIGH);
    servo.write(90);
  }
 
 else   {
    Serial.println(" Access denied");
    tone(BUZZ_PIN, 1000, 200);
    delay(3000);
  }
}
