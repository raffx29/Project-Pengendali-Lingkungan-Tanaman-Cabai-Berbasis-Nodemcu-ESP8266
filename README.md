# Project-Pengendali-Lingkungan-Tanaman-Cabai-Berbasis-Nodemcu-ESP8266
Project pengendali lingkungan tanaman cabai ini bertujuan untuk mengukur sirkulasi udara, memonitoring suhu, kelembaban dan intensitas cahaya yang membantu petani dengan bantuan aplikasi blynk pada smartphone.

## Komponen Yang Digunakan
**Mikrokontroler :**
* Nodemcu ESP8266

**Sensor :**
* DHT22
* LDR

**Output :**
* Relay 5V
* Lampu Pijar
* Fan DC

## Skematik Rangkaian Komponen
![Logo](https://github.com/raffx29/Project-Pengendali-Lingkungan-Tanaman-Cabai-Berbasis-Nodemcu-ESP8266/blob/fedd915a6f5ea8b3c35a751ad6a5a66cdadc6be5/Lib/1.jpg)

Pin yang digunakan komponen sensor dan output pada ESP32 yaitu :
| Komponen | Pin     |
| :-------- | :------- |
| `DHT22` | `D5` |
| `LDR` | `A0` |
| `Relay 1` | `D6` |
| `Relay 2` | `D7` |

## Program NodeMcu 8266
```c++
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
```
Tipe data sensor yang digunakan yaitu :
| Komponen | Tipe     |
| :-------- | :------- |
| `DHT22` | `float` |
| `LDR` | `int` |

## Tampilan Alat
Tampilan alat pada siang hari
![Logo](https://github.com/raffx29/Project-Pengendali-Lingkungan-Tanaman-Cabai-Berbasis-Nodemcu-ESP8266/blob/aa2689200c831728087c7c691350c3be4e9c6bfa/Lib/3.jpeg)
Tampilan alat pada malam hari
![Logo](https://github.com/raffx29/Project-Pengendali-Lingkungan-Tanaman-Cabai-Berbasis-Nodemcu-ESP8266/blob/aa2689200c831728087c7c691350c3be4e9c6bfa/Lib/2.jpeg)

## Interface Aplikasi
![Logo](https://github.com/raffx29/Project-Pengendali-Lingkungan-Tanaman-Cabai-Berbasis-Nodemcu-ESP8266/blob/7b81c6247d91de6e42df07be5bd6e621551083d2/Lib/4.jpg)
