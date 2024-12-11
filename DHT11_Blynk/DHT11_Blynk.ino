#define BLYNK_TEMPLATE_ID "TMPL67ATTbEka"
#define BLYNK_TEMPLATE_NAME "DHT11"
#define BLYNK_AUTH_TOKEN "09tNVsV7kPQWzgs8GkRZTmcNAh3rUom2"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// Ganti dengan kredensial Wi-Fi Anda
char ssid[] = "P1";
char pass[] = "69696969";

// Token autentikasi Blynk
char auth[] = BLYNK_AUTH_TOKEN;

// Pin DHT dan tipe sensor
#define DHTPIN D1 // Pin data DHT11
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Timer untuk pengiriman data ke Blynk
BlynkTimer timer;

void sendDHTData() {
  float t = dht.readTemperature(); // Membaca suhu
  float h = dht.readHumidity();    // Membaca kelembapan

  // Cek apakah pembacaan valid
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Kirim data ke Blynk
  Blynk.virtualWrite(V0, t); // Kirim suhu ke Virtual Pin V0
  Blynk.virtualWrite(V1, h); // Kirim kelembapan ke Virtual Pin V1

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" °C, Humidity: ");
  Serial.print(h);
  Serial.println(" %");
}

void setup() {
  // Inisialisasi Serial Monitor
  Serial.begin(9600);
  
  // Inisialisasi DHT sensor
  dht.begin();

  // Hubungkan ke Blynk
  Blynk.begin(auth, ssid, pass);

  // Set timer untuk mengirim data setiap 1 detik
  timer.setInterval(1000L, sendDHTData);
}

void loop() {
  Blynk.run();
  timer.run();
}
