#define BLYNK_TEMPLATE_ID " YOUR_TEMPLATE"
#define BLYNK_DEVICE_NAME "YOUR_DEVICE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_AUTH_TOKEN"
#define BLYNK_PRINT Serial
#include <.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "YOUR_SSID";
char pass[] = "YOUR_PASSWORD";

int ldr;             
#define relay1 D6 // relay module IN 1
#define relay2 D7 // relay module IN 2
void setup(){
Serial.begin(115200);
  dht.begin();
  Blynk.begin(auth, ssid, pass);
  pinMode(relay1, OUTPUT); // set relay1 for output Kipas
  pinMode(relay2, OUTPUT); // set relay2 for output Lampu
}

void loop()
{
  Blynk.run();
  sensorStarted(); 
}

void sensorStarted() {
  // TEMP
  byte hum = dht.readHumidity();     // temp and  are celsius and humidity readings
  byte temp = dht.readTemperature(); // from DHT/A

 Blynk.virtualWrite(V0, temp); //  Set Virtual Pin 0 (V0) frequency to in Blynk app
  Blynk.virtualWrite(V1, hum);  //  Set Virtual Pin 1 (V1)frequency to  in Blynk app
  Serial.print("Temperature  : ");
  Serial.println(temp);
  Serial.print("Humidity  : ");
  Serial.println(hum);

 //LDR
  ldr = analogRead(ldrSensors);
  Blynk.virtualWrite(V2, ldr); // Set Virtual Pin 2 (V2) frequency to  in Blynk app
  Serial.print("LDR Value : ");
  Serial.println(ldr); // print variable nilai

  if (temp > 21 && ldr > 500) {
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW);
    Serial.println("KIPAS ON LAMPU ON");
  } else if (temp < 21 && ldr > 500) {
digitalWrite(relay1, LOW);
    digitalWrite(relay2, HIGH);
    Serial.println("KIPAS OFF LAMPU ON");
  } else if (temp > 21 && ldr < 500) {
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, LOW);
    Serial.println("KIPAS ON LAMPU OFF");
  } else if (temp < 21 && ldr < 500) {
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);
    Serial.println("KIPAS OFF LAMPU OFF");
  } else if (temp > 255 && ldr > 1023) {
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);
Serial.println("Sensor Tidak Bekerja");
  }
}
