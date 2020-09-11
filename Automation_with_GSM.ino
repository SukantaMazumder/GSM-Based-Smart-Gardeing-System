#include <SoftwareSerial.h>
SoftwareSerial SIM900(7, 8);

int moisture_pin1 = A0;  //defining analog pin for soil moisture sensor-1
int value1 = 0;

int moisture_pin2 = A1;  //defining analog pin for soil moisture sensor-2
int value2 = 0;

int moisture_pin3 = A2;  //defining analog pin for soil moisture sensor-3
int value3 = 0;

const int valve1  = 5; //relay 1 for solenoid valve 1
const int valve2  = 6; //relay 2 for solenoid valve 2
const int valve3  = 9; //relay 3 for solenoid valve 3
const int pump  = 4;

const int water_switch = 10;
const int led = 11;

String textMessage;

String valve1State = "LOW";
String valve2State = "LOW";
String valve3State = "LOW";
String pumpState = "LOW";

void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);

  pinMode(valve1, OUTPUT);
  pinMode(valve2, OUTPUT);
  pinMode(valve3, OUTPUT);
  pinMode(pump, OUTPUT);

  pinMode(led, OUTPUT);
  pinMode(water_switch, INPUT_PULLUP);

  digitalWrite(valve1, LOW);
  digitalWrite(valve2, LOW);
  digitalWrite(valve3, LOW);
  digitalWrite(pump, LOW);


  Serial.begin(19200);
  SIM900.begin(19200);

  // Give time to your GSM shield log on to network
  delay(20000);
  Serial.print("SIM900 ready...");

  // AT command to set SIM900 to SMS mode
  Serial.print("AT+CMGF=1\r");
  delay(100);

  // Set module to send SMS data to serial out upon receipt
  Serial.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);

}

void loop()
{
  if (digitalRead(water_switch) == LOW)
  {
    digitalWrite(led, LOW); //water level high
  }

  if (digitalRead(water_switch) == HIGH)
  {
    digitalWrite(led, HIGH); //water level low
    String message = "Water Level is LOW";
    sendSMS(message);
    textMessage = "";
  }


  moistureControl();
  if (Serial.available() > 0) {
    textMessage = Serial.readString();
    textMessage.toUpperCase();
    delay(10);
  }
  /////////////  valve & pump control ////////////////
  if (textMessage.indexOf("VALVE1ON") >= 0) {
    // Turn on valve1 & save current state
    digitalWrite(valve1, HIGH);
    valve1State = "on";
    textMessage = "";
  }

  if (textMessage.indexOf("VALVE1OFF") >= 0) {
    // Turn on valve1 & save current state
    digitalWrite(valve2, LOW);
    valve2State = "off";
    textMessage = "";
  }

  if (textMessage.indexOf("VALVE2ON") >= 0) {
    // Turn on valve2 & save current state
    digitalWrite(valve2, HIGH);
    valve2State = "on";
    textMessage = "";
  }

  if (textMessage.indexOf("VALVE2OFF") >= 0) {
    // Turn on valve1 & save current state
    digitalWrite(valve2, LOW);
    valve2State = "off";
    textMessage = "";
  }

  if (textMessage.indexOf("VALVE3ON") >= 0) {
    // Turn on valve3 & save current state
    digitalWrite(valve3, HIGH);
    valve3State = "on";
    textMessage = "";
  }

  if (textMessage.indexOf("VALVE3OFF") >= 0) {
    // Turn on valve3 & save current state
    digitalWrite(valve3, LOW);
    valve3State = "off";
    textMessage = "";
  }

  if (textMessage.indexOf("PUMPON") >= 0) {
    // Turn on pump & save current state
    digitalWrite(pump, HIGH);
    pumpState = "on";
    textMessage = "";
  }

  if (textMessage.indexOf("PUMPOFF") >= 0) {
    // Turn on pump & save current state
    digitalWrite(pump, LOW);
    pumpState = "off";
    textMessage = "";
  }
  ////////////////////////////////////////////////////////////

  if (textMessage.indexOf("STATE") >= 0) {
    //send soil moisture sensor state
    String message = ("Sensor 1: " + String(value1) + "%" + "Sensor 2: " + String(value2) + "%" +  "Sensor 3: " + String(value3) + "%");
    sendSMS(message);
    textMessage = "";
  }

  if (textMessage.indexOf("VALVE1STATE") >= 0) {
    //send valve 1 state
    String message = "Valve 1 is " + valve1State;
    sendSMS(message);
    textMessage = "";
  }

  if (textMessage.indexOf("VALVE2STATE") >= 0) {
    //send valve 2 state
    String message = "Valve 2 is " + valve2State;
    sendSMS(message);
    textMessage = "";
  }

  if (textMessage.indexOf("VALVE3STATE") >= 0) {
    //send valve 3 state
    String message = "Valve 3 is " + valve3State;
    sendSMS(message);
    textMessage = "";
  }

  if (textMessage.indexOf("PUMPSTATE") >= 0) {
    //send pump state
    String message = "Pump is " + pumpState;
    sendSMS(message);
    textMessage = "";
  }
}

// Function that sends SMS
void sendSMS(String message)
{
  // AT command to set SIM900 to SMS mode
  Serial.print("AT+CMGF=1\r");
  delay(100);

  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  Serial.println("AT + CMGS = \"+xxxxxxxxxxxxx\"");
  delay(100);
  // Send the SMS
  Serial.println(message);
  delay(100);

  // End AT command with a ^Z, ASCII code 26
  Serial.println((char)26);
  delay(100);
  Serial.println();
  // Give module time to send SMS
  delay(5000);
}
