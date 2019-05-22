#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <String.h>

RF24 radio = RF24(9,10);

const uint64_t rxAddr = 0xB00B1; //plus stop char

struct message{
  int num;
  char letter;
  bool TF;
  float decimal;
};

message Data;

void setup() {
  radio.begin();
  Serial.begin(9600);
  radio.printDetails();
  radio.openReadingPipe(1, rxAddr);
  radio.startListening();
  
}

void loop() {
  
  if (radio.available()){
      radio.read(&Data, sizeof(Data));

      Serial.print(Data.num);
      Serial.print(" ");
      Serial.print(Data.letter);
      Serial.print(" ");
      Serial.print(Data.TF);
      Serial.print(" ");
      Serial.println(Data.decimal);
  }
  //radio.stopListening();

}
