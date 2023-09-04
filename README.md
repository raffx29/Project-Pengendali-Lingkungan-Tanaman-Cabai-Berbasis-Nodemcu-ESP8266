# Project-Pengendali-Lingkungan-Tanaman-Cabai-Berbasis-Nodemcu-ESP8266
Project pengendali lingkungan tanaman cabai ini bertujuan untuk mengukur sirkulasi udara, memonitoring suhu, kelembaban dan intensitas cahaya yang membantu petani tanpa harus memperhatikan lingkungan tanaman cabai.

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
![Logo]()

Pin yang digunakan komponen sensor dan output pada ESP32 yaitu :
| Komponen | Pin     |
| :-------- | :------- |
| `DHT22` | `32` |
| `LDR` | `34` |
| `Soil Moisture` | `35` |
| `Relay 1` | `5` |
| `Relay 2` | `17` |
| `LCD Nextion` | `0` |

## Program ESP32
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
| `Soil Moisture` | `float` |

## Interface Aplikasi
![Logo](https://github.com/raffx29/Project-Smart-Greenhouse/blob/7023ba70bec9769d1c439761c3b0e9c368770138/Lib/9.jpg)

## Program Aplikasi
![Logo](https://github.com/raffx29/Project-Smart-Greenhouse/blob/8dc61d599ebccf31e32524cc46457a2cb7a10615/Lib/6.jpg)
![Logo](https://github.com/raffx29/Project-Smart-Greenhouse/blob/8dc61d599ebccf31e32524cc46457a2cb7a10615/Lib/7.jpg)

## Database Google Firebase
![Logo](https://github.com/raffx29/Project-Smart-Greenhouse/blob/b63ba998d72723995becf825e132150ddcd37892/Lib/8.jpg)
