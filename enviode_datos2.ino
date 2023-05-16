#include <SPI.h>
#include <nRF24L01.h>
#include <ESP8266WiFi.h>
#include <RF24.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>


RF24 radio(2, 4); // CE, CSN
const uint64_t pipe1 = 0xF0F0F0F0AA;
const uint64_t pipe2 = 0xF0F0F0F066;
//const uint64_t pipe3 = 0xF0F0F0F033;
//.............................
const char* ssid = "KevinG";
const char* password = "123456789";

//String url = protocol + host + resource;
//..................

void setup() {
  Serial.begin(9600);
  //........................
  Serial.print("Receiver Started, ID: ");
  Serial.print("Conectando a  ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");
  //:::::::::::::::::::::::::::::::::
  radio.begin();
  radio.openReadingPipe(1, pipe1);
  radio.openReadingPipe(2, pipe2);
  //radio.openReadingPipe(3, pipe3);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}
// void loop() {
 // if (radio.available()) {
//    int datos;
  //  radio.read(&datos, sizeof(datos));
//    Serial.println(datos);
 //   delay(2000);
//  }
//}  
 


 
void loop()
{
     byte pipeNum = 0;
     //................
  if (radio.available(&pipeNum)) {
       int datos;
       radio.read(&datos, sizeof(datos));
       Serial.println(datos);
       //................
       Serial.print("Recibido del transmisor: ");
       Serial.println(pipeNum); // Se imprime el numero del transmisor que envio el dato
       delay(2000);
         

   
   

       HTTPClient http;   
       
       
       const String SERVER_ADDRESS = "http://lapaz.city/2/";

  String full_url = SERVER_ADDRESS + pipeNum+"/"+ datos +"/" ;
  
     // + "&another_value=" + another_value
      //String full_url = "http://lapaz.city/2/2" + "/save_data.php?value=" + value;
       
     http.begin(full_url);
     Serial.println("Making request to " + full_url);
       
   // http.begin("http://lapaz.city/2/2/datos/");        //Indicamos el destino
    //http.addHeader("Content-Type", "plain-text"); //Preparamos el header text/plain si solo vamos a enviar texto plano sin un paradigma llave:valor.

    int codigo_respuesta = http.GET();   //Enviamos el post pasándole, los datos que queremos enviar. (esta función nos devuelve un código que guardamos en un int)

    if(codigo_respuesta>0){
      Serial.println("Código HTTP ► " + String(codigo_respuesta));   //Print return code

      if(codigo_respuesta == 200){
        String cuerpo_respuesta = http.getString();
        Serial.println("El servidor respondió ▼ ");
        Serial.println(cuerpo_respuesta);

      }

    }else{

     Serial.print("Error enviando POST, código: ");
     Serial.println(codigo_respuesta);

    }

    http.end();  //libero recursos

  }else{

     Serial.println("Error en la conexión WIFI");

  }


  
  delay(3000);
  } 


//http.begin("http://lapaz.city/2/2/datos/");        //Indicamos el destino


  
 // String full_url = SERVER_ADDRESS + "/save_data.php?value=" + datos + "/" ;




  //String another_value = "This+is+another+value";
  
