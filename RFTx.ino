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

const uint64_t Addr[2] = {0xB00B1, 0xB00B2};

struct incomingMessage{
  int num;
  char letter;
  bool DIR;
  float decimal;
};

struct outgoingMessage{
  int num;
  char letter;
  bool DIR;
  float decimal;
};

outgoingMessage Data;
incomingMessage Update;

void setup() {
  radio.begin();
  accel.begin();
  pinMode(5, OUTPUT); //?
  accel.setRange(ADXL345_RANGE_16_G);
  
  
  radio.openWritingPipe(Addr[0]);
  radio.openReadingPipe(1, Addr[1]);

  radio.stopListening();

  Data.num = 2;
  Data.letter = 'A';
  Data.DIR = true;
    
  if(DEBUG)
  {
    Serial.begin(9600);
    Serial.println("Entering debug mode");
  }
  
}

void loop() {

  if (Data.DIR)
  {
    sensors_event_t event;
    accel.getEvent(&event);

    Data.decimal = event.acceleration.x;

    Data.DIR = false;
    
    radio.write(&Data, sizeof(Data));

  }

  else
  {
    radio.startListening();
    if (radio.available())
    {
      radio.read(&Update, sizeof(Update));
    }

    Serial.print(Update.num);
    Serial.print(" ");
    Serial.print(Update.letter);
    Serial.print(" ");
    Serial.print(Update.DIR);
    Serial.print(" ");
    Serial.println(Update.decimal);

    Data.DIR = true;
    radio.stopListening();

  }
  
}
