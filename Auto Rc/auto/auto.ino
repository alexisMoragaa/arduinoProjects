#include <Servo.h>



int GRADOS = 0;
int vel = 0;

int ADELANTE = 2;
int ATRAS = 4;
int VELOCIDAD = 3;

int Y=0;
int X=0;

Servo servo;

void setup() {

  pinMode(VELOCIDAD, OUTPUT);
  pinMode(ADELANTE, OUTPUT);
  pinMode(ATRAS, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  Serial.begin(9600);
  servo.attach(6);
}

void loop() {

  X=analogRead(A0);
  Y=analogRead(A1);

  GRADOS = map(X, 1, 1021, 65, 125);
  vel = map(Y, 0, 1021, -255, 255);

  
  Serial.println(vel);

  if(vel > 15 ){
     analogWrite(VELOCIDAD, vel);
      digitalWrite(ATRAS, LOW);
      digitalWrite(ADELANTE, HIGH);
     
    }else if(vel < -15){
       analogWrite(VELOCIDAD, abs(vel));
       digitalWrite(ADELANTE, LOW);
       digitalWrite(ATRAS, HIGH);
    }else{
      analogWrite(VELOCIDAD, 0);
       digitalWrite(ADELANTE, LOW);
       digitalWrite(ATRAS, LOW);
      }

  servo.write(GRADOS);
  


 /* if(Serial.available() > 0){
    
   DATO =  Serial.readString();
  
    Serial.println(DATO);
   
    servo.write(DATO.toInt());
   delay(1000);
  }

 */
   
   

  

 /* delay(500);
  servo.write(110);

  delay(500);
  servo.write(center);

  delay(500);
  servo.write(50);

  delay(500);
  
*/
  
  
}
