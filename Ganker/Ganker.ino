#include <PS2X_lib.h> //Añade libreria para control ps2//for v1.6
#include <Wire.h> // Añade libreria para comunicacion i2c
#include <Adafruit_PWMServoDriver.h> // Añade la libreria para manejar los servos con el driver pca9685

PS2X ps2x; //Inicializa la clase ps2x para el manejo con control ps2

//Inicia variables para el driver pca9685
Adafruit_PWMServoDriver servos = Adafruit_PWMServoDriver(0x40);// establece la direccion de la placa  que manejara los servos
unsigned int pos0=172; // ancho de pulso en cuentas para pocicion 0°
unsigned int pos180=565; // ancho de pulso en cuentas para la pocicion 180°
//Finaliza variables  para el driver pca9685

int error = 0;
byte type = 0;
int velocidad = 0;
int direccion  = 0;


void setup() {
  Serial.begin(9600);

  servos.begin();  
  servos.setPWMFreq(60); //Frecuecia PWM de 60Hz o T=16,66ms

  initController();//Ejecuta la funcion que inicializa la conexion con el control ps2
  

}



void loop() {

  ps2x.read_gamepad(); //Realiza una lectura de los datos enviados por el control
  
    velocidad = map(ps2x.Analog(PSS_LY), 255,0, -255,255);
    Serial.print("Velocidad ");
    Serial.println(velocidad, DEC);
    
    Serial.print(" Direccion ");
    direccion = map(ps2x.Analog(PSS_RX), 255, 0, 55, 135);
    Serial.println(direccion, DEC);



    setServo(15, 90);//Establece el servo numero 15 en 90 grados

delay(20);

}



/*setServo()
 * Establece la posicion de un servo
 * @n_servo numero del servo que controlara
 * @grados Grado exactp em el que posicionara el servo 
*/
void setServo(uint8_t n_servo, int grados){
  int value = map(grados, 0, 180, pos0, pos180);//Establece el tiempo en milisegundos correspondiente al grado de movimiento seleccionado 
  servos.setPWM(n_servo, 0, value);//Setea el valor en grados que tendra el servo en cuestion
  
}




/*initController()
 * Inicializa la conexion con el control ps2
*/
void initController(){
   error = ps2x.config_gamepad(8,12,A0,13, true, false); //setup pins and settings: GamePad(clock,command, attention, data, Pressures?,Rumble?) check for error
  if(error == 0){
     Serial.println("Found Controller, configured successful");
     Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Go to www.billporter.info for updates and to report bugs.");
   }
     
    else if(error == 1)
     Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
    else if(error == 2)
     Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
    else if(error == 3)
     Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
     
     type = ps2x.readType(); 
       switch(type) {
         case 0:
          Serial.println("Unknown Controller type");
         break;
         case 1:
          Serial.println("DualShock Controller Found");
         break;
         case 2:
           Serial.println("GuitarHero Controller Found");
         break;
       } 
}
