/*

*/

#include <TimerOne.h>

#define BUTTON  8

#define RIGHTF 11           //Motor derecho hacia adelante
#define RIGHTB 12           //Motor derecho hacia atrás
#define LEFTF   9           //Motor izquierdo hacia adelante
#define LEFTB  10           //Motor izquierdo hacia atrás

#define TRIGGER 3           //Distance
#define ECHO    2

#define SL_1   A1           //Sensor siguelinea adelante a la izq
#define SL_2   A2           //Sensor siguelinea adelante a la der
#define SL_3   A5           //Sensor siguelinea atrás a la izq
#define SL_4   A6           //Sensor siguelinea atrás a la der

bool buttonState = 0;       //Startup

int segundos = 0;           //Timer
int seg_anterior = 0;
void interruptForDist();

void moveFoward();          //Movement
void moveBackward();
void steerLeft();
void steerRight();
void pivotLeft();
void pivotRight();
void stopMotors();

bool getColor1();           //Colors
bool getColor2();
bool getColor3();
bool getColor4();

int getDistance();
float dist;

void setup() {
  Serial.begin(9600); 

  Timer1.initialize(500000);  //0.5 seg
  Timer1.attachInterrupt(interruptDist);
  noInterrupts();

  pinMode(RIGHTF, OUTPUT);
  pinMode(RIGHTB, OUTPUT);
  pinMode(LEFTF, OUTPUT);
  pinMode(LEFTB, OUTPUT);

  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(SL_1, INPUT);
  pinMode(SL_2, INPUT);
  pinMode(SL_3, INPUT);
  pinMode(SL_4, INPUT);

  pinMode(BUTTON, INPUT_PULLUP);
}

void loop() {
  if (buttonState == 0){    //Start up  button
    if (digitalRead(BUTTON)==0){
      delay (5000);
      buttonState = 1;
      interrupts();
    }
  }
  
  else{

  }
}

int getDistance() {         //Obtiene la distancia desde el sensor de proximidad
  delay(200);
  digitalWrite(TRIGGER, 1);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, 0);
  dist = pulseIn(ECHO, 1);
  dist = dist / 58;
  //Serial.print(dist);
  //Serial.println("cm");
  return dist;
}

bool getColor1() {          //Obtiene el color sobre el que está el sensor superior izquierdo
  int color1;
  color1 = analogRead(SL_1);
  if (color1 < 800) {
    return 1;       // Devuelve 1 si el color es Blanco
  } 
  else {
    return 0;       // Devuelve 0 si el color es Negro
  }
}

bool getColor2() {          //Obtiene el color sobre el que está el sensor inferior izquierdo
  int color2;
  color2 = analogRead(SL_2);
  if (color2 < 800) {
    return 1;       // Devuelve 1 si el color es Blanco
  } 
  else {
    return 0;       // Devuelve 0 si el color es Negro
  }
}

bool getColor3() {          //Obtiene el color sobre el que está el sensor superior derecho
  int color3;
  color3 = analogRead(SL_3);
  if (color3 < 800) {
    return 1;       // Devuelve 1 si el color es Blanco
  } 
  else {
    return 0;       // Devuelve 0 si el color es Negro
  }
}

bool getColor4() {          //Obtiene el color sobre el que está el sensor inferior derecho
  int color4;
  color4 = analogRead(SL_4);
  if (color4 < 800) {
    return 1;       // Devuelve 1 si el color es Blanco
  } 
  else {
    return 0;       // Devuelve 0 si el color es Negro
  }
}

void moveFoward() {         //Mueve el robot hacia adelante
  digitalWrite(RIGHTF, 1);
  digitalWrite(RIGHTB, 0);
  digitalWrite(LEFTF, 1);
  digitalWrite(LEFTB, 0);
}

void moveBackward() {       //Mueve el robot hacia antrás
  digitalWrite(RIGHTF, 0);
  digitalWrite(RIGHTB, 1);
  digitalWrite(LEFTF, 0);
  digitalWrite(LEFTB, 1);
}

void steerLeft() {          //Mueve el robot hacia la izquierda sobre si mismo
  digitalWrite(RIGHTF, 1);
  digitalWrite(RIGHTB, 0);
  digitalWrite(LEFTF, 0);
  digitalWrite(LEFTB, 1);
}

void steerRight() {         //Mueve el robot hacia la derecha sobre si mismo
  digitalWrite(RIGHTF, 0);
  digitalWrite(RIGHTB, 1);
  digitalWrite(LEFTF, 1);
  digitalWrite(LEFTB, 0);
}

void pivotLeft() {          //Mueve el robot hacia la izquierda sobre una rueda
  digitalWrite(RIGHTF, 0);
  digitalWrite(RIGHTB, 0);
  digitalWrite(LEFTF, 1);
  digitalWrite(LEFTB, 0);
}

void pivotRight() {         //Mueve el robot hacia la derecha sobre una rueda
  digitalWrite(RIGHTF, 1);
  digitalWrite(RIGHTB, 0);
  digitalWrite(LEFTF, 0);
  digitalWrite(LEFTB, 0);
}

void stopMotors() {         //Detiene los motores
  digitalWrite(RIGHTF, 0);
  digitalWrite(RIGHTB, 0);
  digitalWrite(LEFTF, 0);
  digitalWrite(LEFTB, 0);
}

void interruptForDist() {   //Interrupción para verificar distancia al oponente
  getDistance();
  if (getDistance()<30){
    moveFoward();
  }
}
