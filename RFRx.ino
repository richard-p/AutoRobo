/*
 * This is the pass-through code. 
 * Vehicle will immediately start Tx so this starts by listening.
 */
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <String.h>

RF24 radio = RF24(9,10);

const uint64_t Addr[2] = {0xB00B1, 0xB00B2}; //plus stop char

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

incomingMessage Data;
outgoingMessage Update;

void setup() {
  radio.begin();
  Serial.begin(9600);
  radio.openReadingPipe(1, Addr[0]);
  radio.openWritingPipe(Addr[1]);

  radio.startListening();

  Data.DIR = true;
  
}

void loop() {
  
  if (Data.DIR)
  {
    if (radio.available()){
      radio.read(&Data, sizeof(Data));

      if (Data.DIR)
      {
        Serial.print(Data.num);
        Serial.print(" ");
        Serial.print(Data.letter);
        Serial.print(" ");
        Serial.print(Data.DIR);
        Serial.print(" ");
        Serial.println(Data.decimal);
      }
    }

    Data.DIR = false;
    
  }

  else
  {
    radio.stopListening();

    Update.num++;

    Data.DIR = true;

    radio.write(&Update, sizeof(Update));
    
  }
 
}
