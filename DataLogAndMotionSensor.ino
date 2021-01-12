/*

  SD card datalogger

  This example shows how to log data using PIR motion sensor

  to an SD card using the SD library. Pin numbers reflect the default

  SPI pins for Arduino mega models

  The circuit:

   motion sensor on pin 22

   LED on pin 23

   SD card attached to SPI bus as follows:

 ** miso - pin 11

 ** mosi - pin 51

 ** sck - pin 52

 ** CS - pin 53

*/

#include <SPI.h>
#include <SD.h>

const int chipSelect = 53;
int ledPin = 23;                // choose the pin for the LED
int inputPin = 22;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
String motionStatus = "";               // variable for state of motion sensor

void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
 
  // Open serial communications and wait for port to open:

  Serial.begin(9600);

  // wait for Serial Monitor to connect. Needed for native USB port boards only:

  while (!Serial);

  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {

    Serial.println("initialization failed. Things to check:");

    Serial.println("1. is a card inserted?");

    Serial.println("2. is your wiring correct?");

    Serial.println("3. did you change the chipSelect pin to match your shield or module?");

    Serial.println("Note: press reset or reopen this serial monitor after fixing your issue!");

    while (true);

  }

  Serial.println("initialization done.");
}

void loop() {

  // make a string for assembling the data to log:

  String dataString = "";

  // read three sensors and append to the string:


  //MOTIONSENSOR  
  val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState == LOW) {
      // we have just turned on
      motionStatus = "Motion detected";
//      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH){
      // we have just turned of
      motionStatus = "No motion detected";
//      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
 //MOTIONSENSOR

    dataString += motionStatus;


  // open the file. note that only one file can be open at a time,

  // so you have to close this one before opening another.

  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:

  if (dataFile) {

    dataFile.println(dataString);

    dataFile.close();

    // print to the serial port too:

    Serial.println(dataString);

  }

  // if the file isn't open, pop up an error:

  else {

    Serial.println("error opening datalog.txt");

  }
}
