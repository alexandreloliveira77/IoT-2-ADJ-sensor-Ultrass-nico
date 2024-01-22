#include <Ultrasonic.h>
#include <Wire.h>
#include <Servo.h>
const int echoPin = 6; //PINO DIGITAL UTILIZADO PELO HC-SR04 ECHO(RECEBE)
const int trigPin = 7; //PINO DIGITAL UTILIZADO PELO HC-SR04 TRIG(ENVIA)
#define SERVO 10
const int pinoBuzzer = 13; //PINO DIGITAL EM QUE O BUZZER ESTÁ CONECTADO
Servo myservo; 
Ultrasonic ultrasonic(trigPin,echoPin); //INICIALIZANDO OS PINOS
int pos, qte=0; 
int distancia; //CRIA UMA VARIÁVEL CHAMADA "distancia" DO TIPO INTEIRO
 
void setup(){
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(echoPin, INPUT); //DEFINE O PINO COMO ENTRADA (RECEBE)
  pinMode(trigPin, OUTPUT); //DEFINE O PINO COMO SAÍDA (ENVIA)
  pinMode(pinoBuzzer, OUTPUT); //DECLARA O PINO COMO SENDO SAÍDA
  myservo.attach(SERVO);
  myservo.write(180);
  Serial.begin(9600);
}

void loop(){
  hcsr04(); // FAZ A CHAMADA DO MÉTODO "hcsr04()"
  if(distancia <= 30){// SE A DISTÂNCIA ENTRE O OBJETO E O SENSOR ULTRASONICO FOR MENOR QUE 30CM, FAZ
    digitalWrite(8, 1);
    digitalWrite(9, 0);
    tone(pinoBuzzer,1500);//ACIONA O BUZZER
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15 ms for the servo to reach the position
    }
    delay(150);   
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15 ms for the servo to reach the position
    }
  }else{//SENÃO, FAZ
    noTone(pinoBuzzer);//BUZZER PERMANECE DESLIGADO
    digitalWrite(8, 0);
    digitalWrite(9, 1);
  }
  Serial.println(distancia); //ENVIA A DISTÂNCIA PELA PORTA SERIAL
  delay(1000); //AGUARDA 1 SEGUNDO
}

//MÉTODO RESPONSÁVEL POR CALCULAR A DISTÂNCIA
void hcsr04(){
  digitalWrite(trigPin, LOW); //SETA O PINO 6 COM UM PULSO BAIXO "LOW"
  delayMicroseconds(2); // DELAY DE 2 MICROSSEGUNDOS
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); //
  distancia = ultrasonic.read(CM); //
}
