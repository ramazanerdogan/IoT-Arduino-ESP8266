//Firebase'den veri okuma
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <MQTTClient.h>
#include <FirebaseArduino.h>

const char *ssid = "";      // baglanilacak olan wifi aginin adi  
const char *password = "";      // baglanilacak olan wifi aginin sifresi
#define FIREBASE_HOST ""
#define FIREBASE_AUTH "" //gizli anahtar
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

  Serial.println("Connecting Firebase Realtime Databese");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
               
}
//************************************************************
void loop() 
{
  Serial.print("Okunan sicaklik degeri: ");
  Serial.println(Firebase.getFloat("Sicaklik: "));
  delay(5000);
  
}
