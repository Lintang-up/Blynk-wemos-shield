#define BLYNK_TEMPLATE_ID "TMPL6qXDOJW50"
#define BLYNK_TEMPLATE_NAME "Sensor Asap MQ"
#define BLYNK_AUTH_TOKEN "q2abhgNjkl-5T_qWy13y7nZAxPZvWBB_"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Ganti dengan kredensial Wi-Fi Anda
char ssid[] = "P1";
char pass[] = "69696969";

// Token autentikasi Blynk
char auth[] = BLYNK_AUTH_TOKEN;

// Pin sensor MQ135
#define MQ135_PIN A0 // Pin analog untuk MQ135

// Timer untuk pengiriman data ke Blynk
BlynkTimer timer;

void sendMQ135Data() {
  int sensorValue = analogRead(MQ135_PIN); // Membaca data dari sensor MQ135
  float voltage = sensorValue * (3.3 / 1023.0); // Konversi ke tegangan (V)

  Serial.print("MQ135 Raw Value: ");
  Serial.print(sensorValue);
  Serial.print(", Voltage: ");
  Serial.println(voltage);

  // Kirim data ke Blynk
  Blynk.virtualWrite(V0, sensorValue); // Kirim nilai analog ke Virtual Pin V0
  Blynk.virtualWrite(V1, voltage);    // Kirim tegangan ke Virtual Pin V1
}

void setup() {
  // Inisialisasi Serial Monitor
  Serial.begin(9600);
  
  // Hubungkan ke Blynk
  Blynk.begin(auth, ssid, pass);

  // Set timer untuk mengirim data setiap 1 detik
  timer.setInterval(1000L, sendMQ135Data);
}

void loop() {
  Blynk.run();
  timer.run();
}
