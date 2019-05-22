#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <String.h>

#define DEBUG 0

RF24 radio = RF24(9,10);
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

const uint64_t TxAddr = 0xB00B1;

struct message{
  int num;
  char letter;
  bool TF;
  float decimal;
};

message Data;

void setup() {
  radio.begin();
  accel.begin();
  pinMode(5, OUTPUT); //?
  accel.setRange(ADXL345_RANGE_16_G);
  
  
  radio.openWritingPipe(TxAddr);


  Data.num = 2;
  Data.letter = 'A';
  Data.TF = false;
  //Data.decimal = 3.14159;
  
  if(DEBUG)
  {
    Serial.begin(9600);
    Serial.println("Entering debug mode");
  }
  
}

void loop() {
  sensors_event_t event;
  accel.getEvent(&event);

  Data.decimal = event.acceleration.x;
  
  radio.stopListening();
  bool ok = radio.write(&Data, sizeof(Data));

  if (ok){digitalWrite(5, HIGH);}
  else{digitalWrite(5, LOW);}

}
