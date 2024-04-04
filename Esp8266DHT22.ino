#include "DHT.h" //biblioteca do DHT11/DHT21/DHT22

#define DPIN 4        //Definindo o pino DHT sensor (GPIO) D2
#define DTYPE DHT22   // usando o DHT22

DHT dht(DPIN,DTYPE); //Juntando os pinos

void setup() { //Ligando a Engine
  Serial.begin(9600);
  dht.begin();
}

void loop() { //loob de input() Aqui tbm estará o método de conexão com o roteador para acesso via firebase
  delay(2000);
  
  float tc = dht.readTemperature(false);  //temperatura em C
  float tf = dht.readTemperature(true);   //temperatura em F
  float hu = dht.readHumidity();          //Humidade do ar

//Output do serial
  Serial.print("Temp: ");
  Serial.print(tc);
  Serial.print(" C, ");
  Serial.print(tf);
  Serial.print(" F, Hum: ");
  Serial.print(hu);
  Serial.println("%");
}