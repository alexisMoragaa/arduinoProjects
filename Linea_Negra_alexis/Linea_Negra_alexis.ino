#include <OpenTB6612FNG.h>
#include <OpenLamborghino.h>

#define BOTON  5
#define BUZZER  13

int setpoint = 0;
int gyroSpeed = 120;
int base = 60;

float Kprop = 0.13;
float Kderiv = 0.4;
float Kinte = 0.1;
String s = "";
char c = 0;
boolean newline = false;
//Inicializamos las variables que usaremos para recibir los datos por el puerto serial


OpenLamborghino OpenLamborghino(BOTON, BUZZER);
OpenTB6612FNG OpenTB6612FNG(0);

void setup() {
  Serial.begin(9600);
  
  Serial.println("Presiona para iniciar la calibracion");
  OpenLamborghino.WaitBoton();
  Serial.print("P: "); Serial.print(Kprop); Serial.println();
  Serial.print("I: "); Serial.print(Kinte); Serial.println();
  Serial.print("D: "); Serial.print(Kderiv); Serial.println();
  Serial.print("V: "); Serial.print(base); Serial.println();
  Serial.print("G: "); Serial.print(gyroSpeed); Serial.println();
   
  Serial.println("Inicia la calibrazion");
  OpenLamborghino.calibracion();
  Serial.println("Finaliza la calibracion");
  OpenLamborghino.WaitBoton();
  Serial.println("Comenzamos");
  delay(1000);
   
}


void loop() {

  Serialin();

  int pos =  OpenLamborghino.LineaNegra();
  //int pos = 0;
  OpenLamborghino.PIDLambo(Kprop, Kderiv, Kinte);
  int Power = OpenLamborghino.PID(pos, setpoint, gyroSpeed);

  Serial.print("P: ");
  Serial.print(pos);
  Serial.print("    M-I: ");
  Serial.print(base - Power);
  Serial.print("    M-D: ");
  Serial.print(base + Power);

  Serial.println();
  
  digitalWrite(12, HIGH);
  OpenTB6612FNG.Motores(base - Power, base + Power );//motor izquierdo, motor derecho
 

}





  void Indicador(int numero){

    for(int i=0; i<numero; i++){
      digitalWrite(BUZZER, HIGH);
      delay(200);
      digitalWrite(BUZZER,LOW);
      delay(200);
    }
  }




void Serialin() {

  newline = false;
  while(Serial.available() > 0) {

    c = Serial.read();
    if( c == '\r')
      continue;
    else if(c == '\n'){
      newline = true;
      break;  
    }else
      s = s + c;
   }


  if(newline){
    Serial.println(s); Serial.println(); 

    if( s.substring(s.indexOf('p') +1).toFloat() > 0 ){
      Kprop = s.substring(s.indexOf('p') +1).toFloat();
      Indicador(1);
    }
    
    if( s.substring(s.indexOf('i') +1).toFloat() > 0 ){
      Kinte = s.substring(s.indexOf('i') +1).toFloat();
      Indicador(2);
    }
      
    if( s.substring(s.indexOf('d') +1).toFloat() > 0 ){
      Kderiv = s.substring(s.indexOf('d') +1).toFloat();
      Indicador(3);
    }


    if( s.substring(s.indexOf('v') +1).toFloat() > 0 ){
      base = s.substring(s.indexOf('v') +1).toFloat();
      Indicador(4);
    }

    if( s.substring(s.indexOf('gs') +1).toFloat() > 0 ){
      gyroSpeed = s.substring(s.indexOf('gs') +1).toFloat();
      Indicador(5);
    }
     
    Serial.println();
    Serial.print("P: "); Serial.print(Kprop); Serial.println();
    Serial.print("I: "); Serial.print(Kinte); Serial.println();
    Serial.print("D: "); Serial.print(Kderiv); Serial.println(); 
    Serial.print("V: "); Serial.print(base); Serial.println(); 
    Serial.print("GS: "); Serial.print(gyroSpeed); Serial.println(); Serial.println(); 


    s = "";
  }





 
}
