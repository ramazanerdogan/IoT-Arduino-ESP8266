// Firebase Realtime Database e DHT11 den okuduğumuz sıcaklık verisini yazma
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <dht11.h>  // dht11 kütüphanesini ekliyoruz.
#define DHT11PIN D1 // DHT11PIN olarak Dijital 1'yi belirliyoruz.

dht11 DHT11;        // DHT11 nesnesini olusturuyoruz
//********************************************************
const char *ssid = "************";      // baglanilacak olan wifi aginin adi  
const char *password = "*********";      // baglanilacak olan wifi aginin sifresi
#define FIREBASE_HOST "*****************************"   // baglanilacak olan firebase host adresi
#define FIREBASE_AUTH "*****************************"  // baglanilacak olan firebase key
//************************************************************
void setup() {
  Serial.begin(9600);                   //seri portu baslat
  delay(1500);                          // 1500 ms = 1.5sn
  Serial.println("Wifi agına baglanıyor");
  
  WiFi.mode(WIFI_STA);                  // istasyon modunda çalış
  WiFi.begin(ssid, password);           // SSID si yukarıda belirtilmiş olan wifi a bağlan
  
  while (WiFi.status() != WL_CONNECTED) // baglanti kuruldu mu?
  {                                     // kurulmadiysa kurulana kaddar 
    delay(500);                         // 500 ms bekle
    Serial.print(".");                  // ekrana . koy    
  }
  
  Serial.println("");
  Serial.println("Wifi erisim noktasina baglanildi");

  Serial.print("Alinan IP adresi: ");
  Serial.println(WiFi.localIP());       // wifi agindan alinan IP adresini yazdir.

  Serial.println("Connecting Firebase Realtime Database");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
//************************************************************
void loop() 
{
  DHT11.read(DHT11PIN);   // sensoru oku
  Serial.println((float)DHT11.temperature, 2);
  Firebase.setFloat("Sicaklik", (float)DHT11.temperature);  // Sicaklik etiketine okudugun degeri yaz
  // handle error
  if (Firebase.failed()) {
      Serial.print("Hata kotu:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(3000); 
}
