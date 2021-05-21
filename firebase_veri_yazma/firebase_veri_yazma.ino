// Firebase Realtime Database e string ve int verisi yazma
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

const char *ssid = "COMPUTER";      // baglanilacak olan wifi aginin adi  
const char *password = "K1E2N3A4";      // baglanilacak olan wifi aginin sifresi
#define FIREBASE_HOST "absolute-advice-294714-default-rtdb.firebaseio.com"   // baglanilacak olan firebase host adresi
#define FIREBASE_AUTH "Fi7u8J1VwqBeV80C0eWvZXNOaFF7XFGF3iiTrS5s"  // baglanilacak olan firebase key
const char *sunucu = "bilgisayar.dpu.edu.tr"; //baglandigimiz host 
String yol = "";
String sifre= "";
int deger=0;
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
  WiFiClient istemci;
 if(!istemci.connect(sunucu, 80)) //sunucuya baglandigini kontrol etmek adina kosul ifadesi ekledik
 {
  Serial.println("sunucuya baglanilamadi");
  delay(500);
  return;
 }
 Serial.println("sunucuya baglanildi");
 
yol="GET /tr/index/sayfa/8997/bilisim-laboratuvari"; //baglanacagimiz hostun urlsi
yol+= " HTTP/1.1\r\n";
yol+="Host: ";
yol+=sunucu;
yol+="\r\n";
yol+="Connection:  close\r\n\r\n"; 


istemci.print(yol);
unsigned long simdiki_zaman = 0;
simdiki_zaman = millis();
while(!istemci.available())
{
  if(millis()-simdiki_zaman>3000)
  {
    istemci.stop();
    return;
  }
}

while (istemci.available())
{
  
  String line = istemci.readStringUntil('\r'); //bu kisim cekilen veriyi satır satır yazdırıyor
  //Serial.println(line);
  int varmi= line.indexOf("201813172015:"); //bu kismi yorum satirina alip ogr no sifre alindiktan sonra aciyoruz
  if(varmi!= -1)
  {
    sifre=line.substring(14,16); //okul no atlandi sadece sifre yazdirildi
    Serial.println("Şifre:"+sifre); //sifreyi yazdirdik
    
    deger=2*sifre+2066;
    
  }  
}
while(1)
{
  delay(100); 
}
  // set string value
  Firebase.setString("Mesaj", "Bizim icin buyuk bir adim");  // Mesaj etiketine Bizim icin buyuk bir adim yaz
  // handle error
  if (Firebase.failed()) {
      Serial.print("Hata kotu:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
  
  // set value
  Firebase.setInt("Sayi",deger);    // Sayi etiketine 42 yaz
  // handle error
  if (Firebase.failed()) {
      Serial.print("Hata kotu:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000); 
}
