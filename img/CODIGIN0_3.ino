//Programa : RFID - Controle de Acesso leitor RFID
//Autor : FILIPEFLOP
 
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
LiquidCrystal lcd(6, 7, 5, 4, 3, 2); 
 
char st[20];
int buzzer = 8; // declara o pino 10 como buzzer
 
void setup() 
{
  Serial.begin(9600);   // Inicia a serial
  SPI.begin();      // Inicia  SPI bus
  pinMode(buzzer, OUTPUT);
  mfrc522.PCD_Init();   // Inicia MFRC522
  Serial.println("");
  Serial.println();
  //Define o número de colunas e linhas do LCD:  
  lcd.begin(16, 2);  
  mensageminicial();
 
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
  //Mostra UID na serial
  Serial.print("UID da tag :");
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
 
  }
  Serial.println();
  Serial.print("Mensagem : ");
  conteudo.toUpperCase();
  if (conteudo.substring(1) == "E4 64 28 4F") //UID 1 - Chaveiro
  {
    Serial.println("Ola Vinicius");
    Serial.println();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Ola Vinicius");
    tone(buzzer,2000,100);
    lcd.setCursor(0,1);
    lcd.print("Presenca ok!");
    delay(1000);
    mensageminicial();
  }
  if (conteudo.substring(1) == "7C 3F B5 96") //UID 1 - Chaveiro
  {
    Serial.println("Ola Vinicius !");
    Serial.println();
    tone(buzzer, 700);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Ola William !");
    tone(buzzer,2000,100);
    lcd.setCursor(0,1);
    lcd.print("Presenca ok!!");
    delay(1000);
    mensageminicial();
  }
    if (conteudo.substring(1) == "FC 4F 90 52") //UID 1 - Chaveiro
  {
    Serial.println("Ola Vinicius !");
    Serial.println();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Ola Ulysses !");
    tone(buzzer,2000,100);
    lcd.setCursor(0,1);
    lcd.print("Presenca ok!!");
    delay(1000);
    mensageminicial();
  }
  if (conteudo.substring(1) == "3A 2A EF 56") //UID 2 - Cartao
  {
    Serial.println("Ola Whandersson !");
   
  Serial.println();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Ola Wanderson!");
    tone(buzzer,2000,100);
    lcd.setCursor(0,1);
    lcd.print("Presenca ok!!");
    delay(1000);
    mensageminicial();
  }
} 
 
void mensageminicial()
{
  lcd.clear();
  lcd.print(" Aproxime o seu");  
  lcd.setCursor(0,1);
  lcd.print("cartao do leitor");  
}
