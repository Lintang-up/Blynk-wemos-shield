#define BLYNK_TEMPLATE_ID "TMPL6aXUtsn3Y"
#define BLYNK_TEMPLATE_NAME "Ir"
#define BLYNK_AUTH_TOKEN "m0tLKF7K_teRmSyGfcwoKb2nWsnrRYiM"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Ganti dengan kredensial Wi-Fi Anda
char ssid[] = "P1";
char pass[] = "69696969";

// Token autentikasi Blynk
char auth[] = BLYNK_AUTH_TOKEN;
int val = 0 ;  

// Timer untuk pengiriman data ke Blynk
BlynkTimer timer;

void sendDHTData() {
  val = digitalRead(5); // IR Sensor output pin connected to D1  
  Serial.println(val);  // see the value in serial m0nitor in Arduino IDE  

  // Kirim data ke Blynk
  Blynk.virtualWrite(V0, val); // Kirim Ir ke Virtual Pin V0
}

void setup() {
  // Inisialisasi Serial Monitor
  Serial.begin(9600);
  
  // Hubungkan ke Blynk
  Blynk.begin(auth, ssid, pass);

  // Set timer untuk mengirim data setiap 1 detik
  timer.setInterval(1000L, sendDHTData);
}

void loop() {
  Blynk.run();
  timer.run();
}
