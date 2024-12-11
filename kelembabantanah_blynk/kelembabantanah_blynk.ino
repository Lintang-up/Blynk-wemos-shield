#define BLYNK_TEMPLATE_ID "TMPL6nf0mx1q5"
#define BLYNK_TEMPLATE_NAME "Kelembaban Tanah"
#define BLYNK_AUTH_TOKEN "_vh6VrlWud2R7jE4NziePJinO3o5XEz1"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Ganti dengan kredensial Wi-Fi Anda
char ssid[] = "P1";
char pass[] = "69696969";

// Token autentikasi Blynk
char auth[] = BLYNK_AUTH_TOKEN;

// Pin sensor kelembaban tanah
#define SOIL_SENSOR_PIN A0 // Pin analog untuk sensor kelembaban tanah

// Timer untuk pengiriman data ke Blynk
BlynkTimer timer;

void sendSoilMoistureData() {
  int sensorValue = analogRead(SOIL_SENSOR_PIN); // Membaca data dari sensor kelembaban tanah
  float percentage = map(sensorValue, 1023, 0, 0, 100); // Konversi nilai ke persentase (0-100%)
  
  // Pastikan nilai berada di rentang 0-100
  percentage = constrain(percentage, 0, 100);

  Serial.print("Soil Moisture Raw Value: ");
  Serial.print(sensorValue);
  Serial.print(", Percentage: ");
  Serial.print(percentage);
  Serial.println(" %");

  // Kirim data ke Blynk
  Blynk.virtualWrite(V0, sensorValue); // Kirim nilai mentah ke Virtual Pin V0
  Blynk.virtualWrite(V1, percentage); // Kirim kelembaban dalam persen ke Virtual Pin V1
}

void setup() {
  // Inisialisasi Serial Monitor
  Serial.begin(9600);
  
  // Hubungkan ke Blynk
  Blynk.begin(auth, ssid, pass);

  // Set timer untuk mengirim data setiap 1 detik
  timer.setInterval(1000L, sendSoilMoistureData);
}

void loop() {
  Blynk.run();
  timer.run();
}
