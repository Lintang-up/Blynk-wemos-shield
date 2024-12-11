#define BLYNK_TEMPLATE_ID "TMPL64nM6ZX8j"
#define BLYNK_TEMPLATE_NAME "Ultrasonic"
#define BLYNK_AUTH_TOKEN "PdN3HlgOMixK8GIgyxGVjOPoZcIYufLz"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Ganti dengan kredensial Wi-Fi Anda
char ssid[] = "P1";
char pass[] = "69696969";

// Token autentikasi Blynk
char auth[] = BLYNK_AUTH_TOKEN;

const int TRIGPIN = D4;          
const int ECHOPIN = D3;
long timer;
int jarak;

// Timer untuk pengiriman data ke Blynk
BlynkTimer timers;

void sendUltraSonicData() {
  digitalWrite(TRIGPIN, LOW);                   
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);                  
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);                   

  timer = pulseIn(ECHOPIN, HIGH);
  jarak = timer/58;
  delay(1000);

  Serial.print("Jarak = ");
  Serial.print(jarak);
  Serial.print(" cm");
  Serial.println();

  // Kirim data ke Blynk
  Blynk.virtualWrite(V0, jarak); // Kirim Jarak ke Virtual Pin V0
}

void setup()
{
  Serial.begin(9600);
  // Pin Ultrasonic  
  pinMode(ECHOPIN, INPUT);
  pinMode(TRIGPIN, OUTPUT);
  // Hubungkan ke Blynk
  Blynk.begin(auth, ssid, pass);
  // Set timer untuk mengirim data setiap 1 detik
  timers.setInterval(1000L, sendUltraSonicData);
}

void loop(){
  Blynk.run();
  timers.run();
}
