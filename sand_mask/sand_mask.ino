#include <Adafruit_NeoPixel.h>


#define LED_PIN  2
#define LARGO  5
#define BUTTON 3
#define V5  3

#define S1 6
#define S2 5
#define KEY 4

int old_state_key;
int old_state_s1;
int old_state_s2;
int brillo = 250;
int color = 1;

Adafruit_NeoPixel strip(LARGO, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  pinMode(V5, OUTPUT); 
  digitalWrite(V5,true);

  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(KEY, INPUT);
  
  Serial.begin(9600);

 
}

void loop() {
  // put your main code here, to run repeatedly:

  int state_key = digitalRead(KEY);
  int state_s1 = digitalRead(S1);
  int state_s2 = digitalRead(S2);


 

  if(state_key == 0 && old_state_key == 1){
    Serial.println("Apretamos el boton");
    set_color();
  }

  if(state_s1 == 0 && old_state_s1 == 1 && state_s2 == 1 && old_state_s2 == 1){
    Serial.println("Giramos a la derecha");
    set_brillo(10);
  }


   if(state_s2 == 0 && old_state_s2 == 1 && state_s1 == 1 && old_state_s1 == 1){
    Serial.println("Giramos a la izquierda");
    set_brillo(-10);
  }


   old_state_key = state_key;
   old_state_s1 = state_s1;
   old_state_s2 = state_s2;


  Serial.println(color);

  for(int i = 0; i< LARGO ; i++){

    if(color == 1){
      strip.setPixelColor(i,0,0,250); 
    }else if(color == 2){
       strip.setPixelColor(i,250,250,0); 
    }else if(color == 3){
       strip.setPixelColor(i,250,250,250); 
    }else if(color == 4){
      strip.setPixelColor(i,250,0,0); 
    }
    else if(color == 0){
      strip.setPixelColor(i,0,0,0); 
    }
    
  }

   strip.setBrightness(brillo);
   strip.show(); 
 delay(10);
}



//cambia el color con cada pulsasion, al superar el 4 restablece a 1
void set_color(){

  color = color +1;
  
  if(color > 4){
    color = 0;
  }
  
}




//Suma o resta brillo definiedo los limites minimos y maximos
int set_brillo(int power){
  brillo = brillo + power;

  if(brillo < 0){
    brillo = 0;
  }

  if(brillo > 250){
    brillo = 250;
  }  
}
