// include the library code:
#include "Arduino.h"

// Display parameters
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <Adafruit_MCP23017.h>

// Ethernet parameters
#include <SPI.h>
#include <Ethernet.h>

// The shield uses the I2C SCL and SDA pins. On classic Arduinos
// this is Analog 4 and 5 so you can't use those for analogRead() anymore
// However, you can connect other I2C sensors to the I2C bus and share
// the I2C bus.
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// These #defines make it easy to set the backlight color
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

// Ethernet Information
byte mac[] =     { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[]  =     {192, 168, 101, 107 };
byte gateway[] = {192, 168, 101, 254 };
byte subnet[]  = {255, 255, 255, 0 };

// telnet defaults to port 23
EthernetServer server(23);
boolean gotAMessage = false; // whether or not you got a message from the client yet
int incomingByte = 0;

int pos = 0;

void setup()
{
  // setting pins 0 to 9 as outputs
  // pins 10-13 are used by the Ethernet Shield
  for(int  i= 0; i < 10; i++)  pinMode(i, OUTPUT);

  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setBacklight(WHITE);
}

void loop()
{
  // wait for a new client:
  EthernetClient client = server.available();

  // when the client sends the first byte, say hello:
  if (client)
  {
    if (!gotAMessage)
    {
      client.println("Welcome to Mordor!");
      gotAMessage = true;
    }

    if(pos < 16)
    {
      lcd.setCursor(pos, 0);
      pos++;
    }
    else
    {
      lcd.setCursor(0, 0);
      lcd.clear();
      pos = 0;
    }

    // read the bytes incoming from the client:
    char thisChar = client.read();

    if(thisChar == '/')
    {
      lcd.setCursor(0, 0);
      lcd.clear();
      pos = 0;
    }

    // echo the bytes back to the client:
    server.write(thisChar);
    // write the bytes to the lcd.
    lcd.write(thisChar);
    // print the bytes to serial.
    Serial.print(thisChar);
  }
}
