#include <ESP8266WiFi.h>                 
#include <FirebaseArduino.h>   
#include <DHT.h>

#define FIREBASE_HOST "ENDEREÇO DO REALTIME DATABASE"      
#define FIREBASE_AUTH "CODIGO DE VERIFICACAO DO PROJETO"            
       
#define WIFI_SSID "NOME DA REDE"
#define WIFI_PASSWORD "SENHA DA REDE"  

#define DPIN 4        // Definindo o pino DHT sensor (GPIO) D2
#define DTYPE DHT22   // Usando o DHT22

DHT dht(DPIN, DTYPE);

void setup() {
  Serial.begin(115200);
  connectWiFi();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print("Humidity: ");  
  Serial.print(humidity);
  Serial.print("%  Temperature: ");  
  Serial.print(temperature);
  Serial.println("°C");

  pushData(humidity, temperature);

  delay(5000);
}

void connectWiFi() {
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("Connected, IP Address: ");
  Serial.println(WiFi.localIP());
}

void pushData(float humidity, float temperature) {
  Firebase.pushString("/DHT22/Humidity", String(humidity) + "%");
  Firebase.pushString("/DHT22/Temperature", String(temperature) + "°C");

  if (Firebase.failed()) {
    Serial.print("Pushing data to Firebase failed: ");
    Serial.println(Firebase.error()); 
  }
}
