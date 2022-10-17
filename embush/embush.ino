#define N 3
#define CH1 A0
#define CH2 A1
#define CH3 A2
int ch[N];

void setup(){
  Serial.begin(9600);
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
}
void loop(){  
  ch[0] = pulseIn(CH1, HIGH);
  ch[1] = pulseIn(CH2, HIGH);
  ch[2] = pulseIn(CH3, HIGH);


/*
 * pines 5 y 6 motor izquierdo
 * pin 10 velocidad motor izquierdo
 * 
 * pines 2 y 3 motor derecho
 * pin 9 velocidad motor derecho
*/

   int VELOCIDAD = map(ch[1], 998, 1977, -250, 250);// mapea la velocidad del canal 2
   int DIRECCION = map(ch[0], 993, 1962, 250, -250 );//mapea la direccion de canal 1
   int ARMA = map(ch[2], 995, 1965, 0, 250 ); //mapea la velocidad del arma desde el canal 3



    int motor_izquierdo = VELOCIDAD - DIRECCION;//establece la velocidad del motor izquierdo en funcion de la direccion
    int motor_derecho = VELOCIDAD + DIRECCION; //establece la velocidad del motor derecho en funcion de la direccion



  if(motor_izquierdo >= 10){//establece el sentido de giro del motor izquierdo
    digitalWrite(5, false);
    digitalWrite(6, true);
  }else{
    digitalWrite(5, true);
    digitalWrite(6, false);
    motor_izquierdo *= -1;//transforma los valores negativos a positivos
    if(motor_izquierdo <=10){
      motor_izquierdo = 0;
    }
  }


  if(motor_derecho >= 10){//establece el sentido de giro del motor derecho
    digitalWrite(2, false);
    digitalWrite(3, true);
  }else{
    digitalWrite(2, true);
    digitalWrite(3, false);
     motor_derecho *= -1;//transforma los valores negativos a positivos
    if(motor_derecho <=10){
      motor_derecho = 0;
    }
    
  }
  
  if(motor_izquierdo > 255){//establece la velocidad maxima de giro del motor izquierdo
    motor_izquierdo = 255;
  }

  if(motor_derecho > 255){//establece la velocidad maxima de giro del motor derecho
    motor_derecho = 255;
  }

  //escribe el pwm para la velocidad de los motores izquierdo y derecho
   analogWrite(10, motor_izquierdo);
   analogWrite(9, motor_derecho);



    //establece el sentido de giro y velocidad del motor del arma
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    analogWrite(11, ARMA);
    

   

  Serial.print("M-I: ");
  Serial.print(motor_izquierdo);
  
  Serial.print(" M-D:  ");
  Serial.print(motor_derecho);
  Serial.print(" / ");


  Serial.print(" ARMA:  ");
  Serial.print(ARMA);
  Serial.print(" / ");

  Serial.print(ch[0]);
  Serial.print(",");
  Serial.print(ch[1]);


  Serial.print(",");
  Serial.print(ch[2]);

  Serial.print(" / direccion: ");
  Serial.println(DIRECCION);

}
