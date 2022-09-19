#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>


// SCK  =>  13
// MISO =>  12
// MOSI =>  11
// CE   =>  9
// CSN  =>  10






RF24 radio(10, 9);   // nRF24L01 (CE, CSN)
const byte address[6] = "00001"; // Address

unsigned long lastReceiveTime = 0;
unsigned long currentTime = 0;

struct Data_Package {
  byte ch1;
  byte ch2_left_x;
  byte ch3_left_y;
  byte ch4_right_x;
  byte ch5_right_y;
  byte ch6;
  byte ch7;
  byte ch8;
  byte ch9;
  byte ch10;
  byte ch11;
  byte ch12;
  byte ch13;
  byte ch14;
};

Data_Package data;




Servo servo;

void setup() {
   Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening(); //  Set the module as receiver

  servo.attach(A7);
  resetData();

}




void loop() {

if (radio.available()) {
    radio.read(&data, sizeof(Data_Package)); // Read the whole data and store it into the 'data' structure
    lastReceiveTime = millis(); // At this moment we have received the data
  }
  // Check whether we keep receving data, or we have a connection between the two modules
  currentTime = millis();
  if ( currentTime - lastReceiveTime > 1000 ) { // If current time is more then 1 second since we have recived the last data, that means we have lost connection
    resetData(); // If connection is lost, reset the data. It prevents unwanted behavior, for example if a drone has a throttle up and we lose connection, it can keep flying unless we reset the values
  }
  
  // Print the data in the Serial Monitor
  Serial.print("CH1: ");
  Serial.print(data.ch1);
  
  Serial.print(" ||  L-X: ");
  Serial.print(data.ch2_left_x);
  Serial.print(" || L-Y: ");
  Serial.print(data.ch3_left_y);

  Serial.print(" || R-X: ");
  Serial.print(data.ch4_right_x);
  Serial.print(" || R-Y: ");
  Serial.print(data.ch5_right_y);

  
  Serial.println();



  int   GRADOS = map(data.ch4_right_x, 0, 255, 65, 125);
  servo.write(GRADOS);
}


void resetData() {
  // Reset the values when there is no radio connection - Set initial default values

  data.ch1 = 0;
  data.ch2_left_x = 127;
  data.ch3_left_y = 127;
  data.ch4_right_x = 127;
  data.ch5_right_y = 127;

}
