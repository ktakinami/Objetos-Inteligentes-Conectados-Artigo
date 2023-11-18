// OBJETOS INTELIGENTES CONECTADOS
// AULA 4 - APLICANDO CONHECIMENTO - PROJETO FINAL

//Configuração de Distancia Mínima em centimetros
const int distancia_sensor = 10; 

//Configurações de Portas do Arduino

//Sensor
const int TRIG = 3;
const int ECHO = 2;

//Demais componentes
const int ledGreen = 7;
const int ledRed = 8;
const int buzzer = 9;

// Variaveis para funcionamento do Buzzer
float seno;
int frequencia;

void setup() {
  Serial.begin(9600);
  
  // Configurações do Sensor
  pinMode(TRIG,OUTPUT);
  pinMode(ECHO,INPUT);
  
  // Configurações do LED
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);

  //Configurações do Buzzer
  pinMode(buzzer, OUTPUT); 
  
}

void loop() {
  int distancia = sensor_morcego(TRIG,ECHO);

    if(distancia <= distancia_sensor){
      Serial.print("WARNING: ");
      Serial.print(distancia);
      Serial.println("cm");
      digitalWrite(ledGreen, LOW);
      digitalWrite(ledRed, HIGH);
      tocaBuzzer();
    }
    else{
      Serial.print("FREE: ");
      Serial.print(distancia);
      Serial.println("cm");
      digitalWrite(ledGreen, HIGH);
      digitalWrite(ledRed, LOW);
      noTone(buzzer);
    }
  delay(100);
  
}

int sensor_morcego(int pinotrig,int pinoecho){
  digitalWrite(pinotrig,LOW);
  delayMicroseconds(2);
  digitalWrite(pinotrig,HIGH);
  delayMicroseconds(10);
  digitalWrite(pinotrig,LOW);

  return pulseIn(pinoecho,HIGH)/58;
}

//Função para execução do Alarme Sonoro
void tocaBuzzer(){
 for(int x=0;x<180;x++){
  seno=(sin(x*3.1416/180));
  frequencia = 2000+(int(seno*1000));
  tone(buzzer,frequencia);
  delay(2);
}

}

 
  /*** TENTATIVA DE INTEGRAÇÃO COM O PROTOCOLO MQTT

  #include "EspMQTTClient.h"
  #include "NewPing.h"

  EspMQTTClient client(
    "Wokwi-GUEST",          // SSID WiFi
    "",                     // Password WiFi
    "test.mosquitto.org",   // MQTT Broker
    "mqtt-wokwi",           // Client
    1883                    // MQTT port
  );

  // Configurações do Sensor Ultrassônico HC-SR04
  const int distancia_sensor = 1;
  const int TRIG = 3;
  const int ECHO = 2;
  NewPing sonar(TRIG, ECHO);

  // Demais componentes
  const int ledGreen = 7;
  const int ledRed = 8;
  const int buzzer = 9;

  // Funcionamento do Buzzer
  float seno;
  int frequencia;

  void setup() {
    Serial.begin(9600);

    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
    pinMode(ledGreen, OUTPUT);
    pinMode(ledRed, OUTPUT);
    pinMode(buzzer, OUTPUT);

    client.enableDebuggingMessages();
    client.enableHTTPWebUpdater();
    client.setInterval(10000);
  }

  void loop() {
    client.loop();

    int distancia = sonar.ping_cm();

    if (distancia <= distancia_sensor) {
      Serial.print("WARNING: ");
      Serial.print(distancia);
      Serial.println("cm");
      digitalWrite(ledGreen, LOW);
      digitalWrite(ledRed, HIGH);
      tocaBuzzer();

      // Publica a mensagem no tópico MQTT
      client.publish("eadMack/sensor", String(distancia).c_str());
    } else {
      Serial.print("FREE: ");
      Serial.print(distancia);
      Serial.println("cm");
      digitalWrite(ledGreen, HIGH);
      digitalWrite(ledRed, LOW);
      noTone(buzzer);
    }
    delay(200);
  }
  
***/
