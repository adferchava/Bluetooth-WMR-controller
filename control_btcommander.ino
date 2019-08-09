//Codigo para leer la trama de datos de la aplicacion joy bt commander
// el codigo lee una trama de datos ejemplo
//..200200..
// equivaente a la posición del joystick
// En arduino connectar el puerto bluetooth en el puerto RX2,TX2 Puerto2 Cruzados RX-TX TX-RX
// visualizar en puerto0, del serial monitor si se desea ver los datos de entrada de la applicacion.

#include <Servo.h>
#include <math.h>

Servo myservo;  // create servo object to control a servo

int d1 = 13; //in1 M1
int d2 = 12; //in2 M1
int i1 = 11; //in3 M1
int i2 = 10; //in4 M1
int d3 = 9; //in1 M2
int d4 = 8; //in2 M2
int i3 = 7; //in3 M2
int i4 = 6; //in4 M2
int d5 = 2; //in1 M3
int d6 = 3; //in2 M3
int i5 = 4; //in3 M3
int i6 = 5; //in4 M3


double x0 = 100;
double y0 = 100;
int dx=0, dy=0, rx=0, ry=0;
int pos, vel, rel, rel2;

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin
int val1;
int counter;
String dato1;
String dato2;
int num1;
int num2;
String cadena;
String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete


void setup() {
  // initialize serial:
   myservo.attach(9);  // crea un objet servo al pin 9
  Serial.begin(9600);  // se utiliza para visualizar los datos de entrada num1, num2 de lectura
  Serial2.begin(9600); // se utiliza para recibir el dato de trama (100,100) hasta (300,300) de la aplicacion joystick bluetooth commander
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(i1, OUTPUT);
  pinMode(i2, OUTPUT);
  pinMode(i3, OUTPUT);
  pinMode(i4, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);
  pinMode(i5, OUTPUT);
  pinMode(i6, OUTPUT);
  pinMode(d5, OUTPUT);
  pinMode(d6, OUTPUT);
    // reserve 200 bytes for the inputString:
  inputString.reserve(20);
  }

void loop() {
     // print the string when a newline arrives:
 if(stringComplete) {
    //Serial.println(inputString);
    //Serial.println(inputString.substring(0,3));
    //Serial.println(inputString.substring(3,6));
    dato1=inputString.substring(0,3);
    dato2=inputString.substring(3,6);
    num1=dato1.toInt();  // es necesario escalarlar los datos num1 y num2 para operar el servo y el motor DC para la salida PWM
    num2=dato2.toInt();
//    Serial.println(num1);
//    Serial.print('\n');
//    Serial.println(num2);
  val = num1;            // reads the value of the potentiometer (value between 100 and 300)
  val=val-100;
  if(val<0){val==0;}
  if(val>180){val==180;}

  val1 = num2;            // reads the value of the potentiometer (value between 100 and 300)
  val1=val1-100;
  if(val1<0){val1==0;}
  if(val1>180){val1==180;}
//     
//  //val = map(val, 200, 300, 0, 120);     // scale it to use it with the servo (value between 0 and 120)  
//  // clear the string:
    //Serial.print(val);
    //Serial.print(";");
    //Serial.println(val1);
inputString = "";
stringComplete = false;
//  
  if(val==100 && val1==100){ 
    //QUIETO
    analogWrite(i1, 0);     
    analogWrite(i2, 0); 
    analogWrite(d1, 0);  
    analogWrite(d2, 0);
    analogWrite(i3, 0);     
    analogWrite(i4, 0); 
    analogWrite(d3, 0);  
    analogWrite(d4, 0);
    analogWrite(i5, 0);     
    analogWrite(i6, 0); 
    analogWrite(d5, 0);  
    analogWrite(d6, 0);
//    Serial.print("QUIETO");
//    Serial.print('\n');
    }
    //DETERMINAR VELOCIDAD 
    rx = val-x0;
    dx = pow(rx,2);
    ry = val1-y0;
    dy = pow(ry,2);
    pos = dx + dy;
    vel = sqrt (pos); 
    if (vel>100){vel=100;}
//    Serial.print(vel);
//    Serial.print("\n");
    //PWM 0-255
    rel = (vel*255)/100;
    //rel2 = rel-50;// cmbio ultimo
    rel2 = rel;// cmbio ultimo
Serial.print(rel);
Serial.print(" ");
Serial.println(rel2);
    //ORIENTACION DELANTERA
    if(val1>100){
      if(val>80 && val<120){
        //ADELANTE
        analogWrite(i1, 0);     
        analogWrite(i2, rel); 
        analogWrite(d1, rel);  
        analogWrite(d2, 0);
        analogWrite(i3, 0);     
        analogWrite(i4, rel); 
        analogWrite(d3, 0);  
        analogWrite(d4, rel);
        analogWrite(i5, 0);     
        analogWrite(i6, rel); 
        analogWrite(d5, 0);  
        analogWrite(d6, rel);
//        Serial.print("adelante");
//        Serial.print('\n');
        }      
      if(val>120 && val<=200){
        //ZONA DERECHA 
        analogWrite(i1, 0);     
        analogWrite(i2, rel); 
        analogWrite(d1, 0);  
        analogWrite(d2, 0);
        analogWrite(i3, 0);     
        analogWrite(i4, rel); 
        analogWrite(d3, 0);  
        analogWrite(d4, 0);
        analogWrite(i5, 0);     
        analogWrite(i6, rel); 
        analogWrite(d5, 0);  
        analogWrite(d6, 0);
//        Serial.print("zona der");
//        Serial.print('\n');
        }
      if(val>=0 && val<80){
        //ZONA IZQUIERDA 
        analogWrite(i1, 0);     
        analogWrite(i2, 0); 
        analogWrite(d1, rel);  
        analogWrite(d2, 0);
        analogWrite(i3, 0);     
        analogWrite(i4, 0); 
        analogWrite(d3, 0);  
        analogWrite(d4, rel);
        analogWrite(i5, 0);     
        analogWrite(i6, 0); 
        analogWrite(d5, 0);  
        analogWrite(d6, rel);
//        Serial.print("zona izq");
//        Serial.print('\n');
        }
       }
    //ORIENTACION TRASERA
    if(val1<100){
      if(val>80 && val<120){
        //REVERSA
        analogWrite(i1, rel);     
        analogWrite(i2, 0); 
        analogWrite(d1, 0);  
        analogWrite(d2, rel);
        analogWrite(i3, rel);     
        analogWrite(i4, 0); 
        analogWrite(d3, rel);  
        analogWrite(d4, 0);
        analogWrite(i5, rel);     
        analogWrite(i6, 0); 
        analogWrite(d5, rel);  
        analogWrite(d6, 0);
//        Serial.print("reversa");
//        Serial.print('\n');
        }
      if(val>120 && val<=200){
        //ZONA DERECHA 
        analogWrite(i1, rel);     
        analogWrite(i2, 0); 
        analogWrite(d1, 0);  
        analogWrite(d2, 0);
        analogWrite(i3, rel);     
        analogWrite(i4, 0); 
        analogWrite(d3, 0);  
        analogWrite(d4, 0);
        analogWrite(i5, rel);     
        analogWrite(i6, 0); 
        analogWrite(d5, 0);  
        analogWrite(d6, 0);
//        Serial.print("zona atras der");
//        Serial.print('\n');
        }
      if(val>=0 && val<80){
        //ZONA IZQUIERDA 
        analogWrite(i1, 0);     
        analogWrite(i2, 0); 
        analogWrite(d1, 0);  
        analogWrite(d2, rel);
        analogWrite(i3, 0);     
        analogWrite(i4, 0); 
        analogWrite(d3, rel);  
        analogWrite(d4, 0);
        analogWrite(i5, 0);     
        analogWrite(i6, 0); 
        analogWrite(d5, rel);  
        analogWrite(d6, 0);
//        Serial.print("zona atras izq");
//        Serial.print('\n');
        }
       }
}
//else {
//  
// // myservo.write(val);                  // sets the servo position according to the scaled value
// // delay(15);                           // waits for the servo to get there
//}
}


void serialEvent2() {
   while (Serial2.available()) {
     // get the new byte:
    char inChar = (char) Serial2.read();
    // add it to the inputString:
    if (inChar>=48 && inChar<=57 ){
         inputString += inChar;
         counter++;
         if (counter>=6){stringComplete = true;
             counter=0;}
             cadena=inputString;
         }
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar<48){
      stringComplete = false;
      counter==0;
      }
  }
}
