#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
/*
 * https://howtomechatronics.com/tutorials/arduino/arduino-wireless-communication-nrf24l01-tutorial/
 */
// RF pins
const byte RF_RX_pin = 9;
const byte RF_TX_pin = 10;

RF24 radio = RF24(RF_RX_pin, RF_TX_pin);
const uint16_t addr = 0xB00B;

// reading array
uint8_t incomingMsg[2];
uint8_t x_pos;
uint8_t y_pos;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(!Serial){}
  
  radio.begin();
  radio.openReadingPipe(1, addr);

}

void loop() {
  // put your main code here, to run repeatedly:
  radio.startListening();
  if (radio.available())
  {
    radio.read(&incomingMsg, sizeof(incomingMsg)); // how to handle incoming array?
  }

  if(incomingMsg[0] == 'X')
  {
    x_pos = incomingMsg[1];
    //Serial.print("X position: "); Serial.println(x_pos);
  }
  if(incomingMsg[0] == 'Y')
  {
    y_pos = incomingMsg[1];
    //Serial.print("Y position: "); Serial.println(y_pos);
  }
  
  Serial.print("X, Y: "); Serial.print(x_pos);
  Serial.print(", ");Serial.println(y_pos);

}
