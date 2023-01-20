#include <PS2X_lib.h> //for v1.6
PS2X ps2x; // create PS2 Controller Class
#include <Servo.h>

int error = 0;
byte type = 0;

int velocidad = 0;
int direccion  = 0;


void setup() {
 Serial.begin(9600);

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
     
     //Serial.print(ps2x.Analog(1), HEX);
     
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

void loop() {
  
    velocidad = map(ps2x.Analog(PSS_LY), 255,0, -255,255);
    Serial.println(velocidad, DEC);

    direccion = map(ps2x.Analog(PSS_RX), 255, 0, 55, 135);
    Serial.println(velocidad, DEC);





}
