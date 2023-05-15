#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN
const uint64_t pipe2 = 0xF0F0F0F066;
//
int TRIG = 5;      // trigger en pin 10
int ECO = 4;      // echo en pin 9
int LED = 3;      // LED en pin 3
int DURACION;
int DISTANCIA;

void setup() {
  //
  pinMode(TRIG, OUTPUT);  // trigger como salida
  pinMode(ECO, INPUT);    // echo como entrada
  pinMode(LED, OUTPUT);   // LED como salida
  //
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe2);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}
void loop() {

  digitalWrite(TRIG, HIGH);     // generacion del pulso a enviar
  delay(1);       // al pin conectado al trigger
  digitalWrite(TRIG, LOW);    // del sensor

  DURACION = pulseIn(ECO, HIGH);  // con funcion pulseIn se espera un pulso
  // alto en Echo
  DISTANCIA = DURACION / 58.2;    // distancia medida en centimetros
  Serial.println(DISTANCIA);    // envio de valor de distancia por monitor serial
  delay(500);       // demora entre datos
  radio.write(&DISTANCIA, sizeof(DISTANCIA));
  //Serial.println(radio.write(&DISTANCIA, sizeof(DISTANCIA)));
  delay(500);
  if (DISTANCIA <= 20 && DISTANCIA >= 0) { // si distancia entre 0 y 20 cms.
    digitalWrite(LED, HIGH);      // enciende LED
    delay(DISTANCIA * 10);      // demora proporcional a la distancia
    digitalWrite(LED, LOW);     // apaga LED
    //const char text[] = "kevin";
  }


}
