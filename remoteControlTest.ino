#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
/*
 * https://howtomechatronics.com/tutorials/arduino/arduino-wireless-communication-nrf24l01-tutorial/
 */
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


// joystick pins
const byte x_pos_pin = A0;
const byte y_pos_pin = A1;
const byte joy_button_pin = 2;
const byte joystick[] = {x_pos_pin, y_pos_pin, joy_button_pin};

// RF pins
const byte RF_TX_pin = 9;
const byte RF_RX_pin = 10; // probabaly not what these are

RF24 radio = RF24(7,8);
const uint16_t addr = 0xB00B;

uint8_t x_pos[2] = {'X', 0};
uint8_t y_pos[2] = {'Y', 0};

void setup()
{
  for (int i=0; i<sizeof(joystick); i++)
  {
    pinMode(joystick[i], INPUT); // input pullup?
  }
 
  Serial.begin(115200);
  while(!Serial){}

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) 
  {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.display();
  display.clearDisplay();
  display.setTextSize(2); // by page
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0); // (LR, UD) goes by page (8 pixels)
  

  radio.begin();
  radio.stopListening();
  radio.openWritingPipe(addr);

}

void loop()
{
  // read joystick
  x_pos[1] = analogRead(x_pos_pin);
  y_pos[1] = analogRead(y_pos_pin);
 
  Serial.print("X position: "); Serial.println(x_pos[1]);
  Serial.print("Y position: "); Serial.println(y_pos[1]);

  display.clearDisplay();
  display.setTextSize(2);
  
  display.setCursor(0, 0);
  display.write("X, Y");
  
  display.setCursor(0, 16);
  display.println(x_pos[1]);

  display.setCursor(0, 32);
  display.println(y_pos[1]);
  
  display.display();
  display.setCursor(0, 0);
  //display.setTextSize(2);
  radio.write(&x_pos, sizeof(x_pos)); // maybe sin-cos this bitch for vectors
  radio.write(&y_pos, sizeof(y_pos));
 
  // later on, send over RF
 
  delay(50); // not forever, just to see serial print
}
