// Nodemcu Raspbery Pi MQTT Broker ı na baglanıp temperature konusuna ABONE OLUYOR
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <MQTTClient.h>

const char *ssid = "************";      // baglanilacak olan wifi aginin adi  
const char *password = "********";      // baglanilacak olan wifi aginin sifresi

unsigned long lastMillis = 0;

MQTTClient mqtt_istemci;                // mqtt_istemci nesnesini olustur
WiFiClient wifi_istemci;                // wifi_istemci nesnesini olustur
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


  Serial.print("MQTT Broker'a baglaniyor...");
  // xxx.xxx.xxx.xxx bağlanılacak olan IP adresi girilmeli
  mqtt_istemci.begin("xxx.xxx.xxx.xxx", wifi_istemci); // mqtt broker a baglanma
  mqtt_istemci.onMessage(mesaj_geldi);                  // mqtt brokerdan msj gelince mesaj_geldi fonksiyonuna git
}
//************************************************************
void loop() 
{
  mqtt_istemci.loop();
  if(!mqtt_istemci.connected()) {
    baglan();
  }
}
//************************************************************
void baglan()
{
  Serial.print("Baglaniyor...");
  // mqtt_istemci.connect("subscriber adi","username","password");
  while (!mqtt_istemci.connect("nodemcu_hoca_sbc", "mosq_hoca", "12345678"))
  {
       Serial.print(".");
  }
  Serial.println("Projeye baglandi");
  
  mqtt_istemci.subscribe("temperature");     // temperature konusuna abone ol
}
//***********************************************************
void mesaj_geldi(String &konu, String &gelen_veri)  //mqtt broker dan veri geldi
{
  Serial.println(gelen_veri); 
}
