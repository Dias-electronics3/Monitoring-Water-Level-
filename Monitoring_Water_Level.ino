#include <LiquidCrystal_I2C.h>
#include <Wire.h>

long jarak, waktu; // Inisialisasi UltraSonik

#define Rec 9
#define Trans 10

#define Kosong 8
#define Setengah 6
#define Penuh 5

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define  maxJarak 400   

void setup() {

  pinMode(Rec, INPUT); // Terima
  pinMode(Trans, OUTPUT); // Kirim
  // Indikator
  pinMode(Penuh, OUTPUT);
  pinMode(Setengah, OUTPUT);
  pinMode(Kosong, OUTPUT);

  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {

  // Syarat Awal Ultrasonik
  digitalWrite(Trans, 0);
  delayMicroseconds(2);
  digitalWrite(Trans, 1);
  delayMicroseconds(10);
  digitalWrite(Trans, 0);

  // Panjang Bar Animasi Pada LCD
  int panjangBar = map(jarak, maxJarak, 0, 0, 16);
  // Pengukuran Jarak Menjadi CM
  waktu = pulseIn(Rec, 1);
  jarak = (waktu * 0.034) / 2;

  // Pembatas
  if (jarak > maxJarak) jarak = maxJarak;
  if (jarak < 0) jarak = 0;

  // BARIS 2
  lcd.setCursor(0, 1);
  for (int i = 0; i < 16; i++) {
    lcd.print(" ");
  }

  lcd.setCursor(0, 1);
  for (int i = 16; i > panjangBar; i--) {
    lcd.print((char)255);
  }

    // BARIS 1
  lcd.setCursor(4, 0);

  if (jarak < 150) {
    lcd.print(" KOSONG ");
    digitalWrite(Kosong, 1);
    delay(500);
    digitalWrite(Kosong, 0);
    digitalWrite(Penuh, 0);
    digitalWrite(Setengah, 0);
  } 
  else if (jarak >= 151 && jarak <= 300) {
    lcd.print("SETENGAH");
    digitalWrite(Penuh, 0);    
    digitalWrite(Kosong, 0);
    digitalWrite(Setengah, 1);
  } 
  else {
    lcd.print(" PENUH  ");
    digitalWrite(Penuh, 1);    
    digitalWrite(Kosong, 0);
    digitalWrite(Setengah, 0);
  }

  Serial.println(String("JARAK AIR : ") + jarak + String("CM"));
  delay(500);
}
