#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char *ssid = "xxxxxxxxxxxxx";    // baglanilacak olan wifi aginin adi  
const char *password = "xxxxxxxxx";    // baglanilacak olan wifi aginin sifresi

const char *sunucu = "maker.ifttt.com";         // maker.ifttt.com sitesine baglanilacak
String yol="";
//************************************************************
void setup() {
  Serial.begin(9600);         //seri portu baslat
  pinMode(D7, INPUT);       // D7 pinini giris yap
  delay(1500);                // 1500 ms = 1.5sn
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
  Serial.println(WiFi.localIP());      // wifi agindan alinan IP adresini yazdir.
}
//************************************************************
void loop() 
{
 // if(digitalRead(D7)==LOW)    // D7 pull-up yapilmis buton var, butona basıldı mi?
  {
    //String path="/******************************"; path eklenecek
    String path="/trigger/sicaklik/with/key/dL2jbGWjXwP-G7i8dtckWMTz80mgL3iuElSf7ANZePW";      
    WiFiClient istemci;                   // istemci nesnesini olustur
    if (!istemci.connect(sunucu, 80))     // isemci nesnesi sunucuya 80 portundan baglandi mi?
    {
      Serial.println("Sunucuya baglanamadi");
      delay(500);
      return;                              // loop un basina git
    }     
  
    // sunucuya baglandi, http protokolunu olustur, sayfayi istemek icin                     
    yol="GET ";
    yol+=path;
    yol+= " HTTP/1.1\r\n";
    yol+="Host: ";
    yol+=sunucu;
    yol+="\r\n";
    yol+="Connection: close\r\n\r\n";
  
    istemci.print(yol);                   // sayfa istegini gonder
    //*************** 3sn lik istemci kontrolu*****************
    unsigned long simdiki_zaman = 0;
    simdiki_zaman = millis();             // millis fonksiyonu o anki zamanı aldı simdiki_zaman değişkenine atadı. örneğin simdiki_zaman=4000
    
    while(!istemci.available())           // istemciye bilgi gelmemis mi?
    {                                     // gelmemis bekleme
        if(millis()-simdiki_zaman>3000)   // örneğin yeniden o anki zamanı al. 4001-4000=1>3000?
        { 
          istemci.stop();                 // örneğin yeniden o anki zamanı al. 7001-4000=3001>3000. 3 sn doldu
          return;                         // istemci durduruldu loop basina don
        }
    }
    //********************************************************
    while (istemci.available())           // istemciye bilgi gelmis mi?
    {
      String line = istemci.readStringUntil('\r');  // gelen veriyi satır satır oku
      Serial.println(line);             // okudugunu seri porttan gonder
    }
    delay(10000);
    Serial.println("............................");
  }
}
