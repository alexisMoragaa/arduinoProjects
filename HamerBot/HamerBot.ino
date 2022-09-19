#include <PS2X_lib.h> //for v1.6
PS2X ps2x; // create PS2 Controller Class



int motor_derecha_1 = 2;
int motor_derecha_2 = 3;

int motor_izquierda_1 = 5;
int motor_izquierda_2 = 6;

int velocidad = 200;



int error = 0;
byte type = 0;
byte vibrate = 0;

void setup() {

  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(motor_derecha_1, OUTPUT);
  pinMode(motor_derecha_2, OUTPUT);
  pinMode(motor_izquierda_1, OUTPUT);
  pinMode(motor_izquierda_2, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  


   error = ps2x.config_gamepad(8,12,A0,13, true, false); //setup pins and settings: GamePad(clock,command, attention, data, Pressures?,Rumble?) check for error
   type = ps2x.readType();


  if(error == 0){
     Serial.println("Mando configurado");
  }else{
    reset();
    Serial.println("No funciona la wea");
  }
}

void loop() {
  
  ps2x.read_gamepad(); //read controller


  if(ps2x.Button(PSB_R2)){
    velocidad = 255;
  }else{
    velocidad = 200;
  } 
  
  
  if(ps2x.Button(PSB_PAD_UP)){
    front();
  }else if(ps2x.Button(PSB_PAD_DOWN)){
    back();
  }else if(ps2x.Button(PSB_PAD_LEFT)){
    left();
  }else if(ps2x.Button(PSB_PAD_RIGHT)){
    right();
  }else{
    reset();
  }

Serial.println(velocidad);
  
  // put your main code here, to run repeatedly:
delay(40);
}


void _speed(){
    analogWrite(9, velocidad);
    analogWrite(10, velocidad);
  }

void front(){
  digitalWrite(motor_derecha_1, false);
  digitalWrite(motor_derecha_2, true);

  digitalWrite(motor_izquierda_1, false);
  digitalWrite(motor_izquierda_2, true);

  _speed();
}


void back(){
  digitalWrite(motor_derecha_1, true);
  digitalWrite(motor_derecha_2, false);

  digitalWrite(motor_izquierda_1, true);
  digitalWrite(motor_izquierda_2, false);  
  _speed();
}




void left(){
  digitalWrite(motor_derecha_1, true);
  digitalWrite(motor_derecha_2, false);

  digitalWrite(motor_izquierda_1, false);
  digitalWrite(motor_izquierda_2, true);
  _speed();
}




void right(){
  digitalWrite(motor_derecha_1, false);
  digitalWrite(motor_derecha_2, true);

  digitalWrite(motor_izquierda_1, true);
  digitalWrite(motor_izquierda_2, false);
  _speed();
}



void reset(){
  digitalWrite(motor_derecha_1, false);
  digitalWrite(motor_derecha_2, false);

  digitalWrite(motor_izquierda_1, false);
  digitalWrite(motor_izquierda_2, false);
}
