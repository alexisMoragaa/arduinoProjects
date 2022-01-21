#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

//Selecciona el pin digital que controlara la tira led, este debe ser un pin con pwm
#define PIN        6 

//Se establece el numero de pines que tiene la tira
#define NUMPIXELS 32 

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//Se establece el tiempo en milisegundos que tardara cada iteracion del loop
int DELAY = 26;

//Se establece una variable llamada acumulada que parte siendo el numero e leds de la tira
int acumulado = NUMPIXELS;

void setup() {

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

 Serial.begin(9600);
 pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
 
}



void loop() {
  //pixels.clear(); // Set all pixel colors to 'off'

   charger_efect();

}




void charger_efect(){

    //Recorremos la tira led
    for( int i = 0; i < NUMPIXELS; i++){

        //Por cada iteracion encendemos el led con el numero de la iteracion
        pixels.setPixelColor(i, pixels.Color(70, 0, 30));

        // si el numero de la iteracion  es menor al numero acumulado apagamos el pixel que esta justo atras del que acabamos de encender
         if(i < acumulado){
           pixels.setPixelColor(i-1, pixels.Color(0, 0, 0));
         }

     
        //Encendemos los leds
        pixels.show();

        //Si i es igual el numero de acumulados reducimos el numero de acumulado en 1 y reiniciamos la iteracion, ademas reducimos el tiempo de espera en 1 para aumentar la velocidad
        if(i == (acumulado-1) ){
            acumulado--; 
            Serial.print("Posicion: ");
            Serial.println(acumulado);
            if(DELAY > 3){
              DELAY--;     
             }
             //Imprimimos los valores para monitorearlos
            Serial.print("Espera: ");
            Serial.println(DELAY); 
          }
        //Esperamos el tiemop definido para la siguiente iteracion
        delay(DELAY);
      }


    if(acumulado == 0){
        acumulado = NUMPIXELS;
        DELAY = 22;
        Serial.println("RESETEAMOS ACUMULADO"); 
      }
  
  }
