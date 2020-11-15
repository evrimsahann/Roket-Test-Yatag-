#include "stdio.h"
#include "HX711.h"

#define C 420000.0                      // Load cell kalibrasyon değeri. Siz burada kendi değerinizi kendiniz bulacaksınız. Hiç yük yokken ekranda 0 görene kadar oynamanız lazım...
#define DT  6                          // Hx711'den çıkan DT kablosunun arduino üzerindeki yeri. Buradaki 6 sizin bağlantı yaptığınız yere göre değiştirilmesi lazım.
#define SCK  2                        // Hx711'den çıkan SCK kablosunun arduino üzerindeki yeri. Buradaki 2 sizin bağlantı yaptığınız yere göre değiştirilmesi lazım.

HX711 scale;

void setup() {

  Serial.begin(115200);               // Bu değerin, Seri Port ekranının sağ altında bulunan değerle aynı olması gerekiyor...
  Serial.println("EVR Mechanics");   // Yazılım başladığında Seri Port'a vereceği başlangıç yazısı. Bunu istediğinz birşey yapabilir veya satırı silerek komple kaldırabilirsiniz...
  scale.begin(DT, SCK);
  scale.set_scale(C);
  scale.tare(); 
  pinMode(8, OUTPUT);                  // Bu kısımda Led ve Buzzer'ın bağlı olduğu pini tanımlıyoruz. Buradaki 8 sizin bağlantı yaptığınız yere göre değiştirilmesi lazım.
}
void loop() {
  Serial.print("Kuvvet: ");
  Serial.print(scale.get_units(),5);      // Buradaki 5 ekrana çıkan değerin (.)dan sonraki basamak sayısı. Eğer çok detaylı sonuçlar istemiyorsanuz bunu 2 veya 3 olarak değiştirebilirsiniz.
  Serial.print(" kg");                   // Sonucun birim değeri..
  Serial.println();
  { 
  if (scale.get_units() < 0.01){           // Eğer değer 0.01kg'dan küçükse 2.5 saniyede bir ölçüm yapar ve her ölçümde aynı anda led ve buzzer sinyal verir.
  digitalWrite(8, HIGH);
  delay(100);
  digitalWrite(8, LOW);
  delay(2000);
  }
  else {
  digitalWrite(8, HIGH);                  // 0.01'den büyük ise 0.5(yarım) saniyede bir ölçüm yapar ve sinyalleride ona göre verir.
  delay(50);
  digitalWrite(8, LOW);
  delay(1);
}
  }
  delay (360);
}
