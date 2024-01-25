// Exmaple of using the MQTT library for ESP32 
// Library by Joël Gähwiler
// https://github.com/256dpi/arduino-mqtt
// Modified by Arnan Sipitakiat

#define PCF8574_Address 0x20

#include <WiFi.h>
#include <MQTT.h>
#include <Adafruit_PCF8574.h>
#include <LCD_I2C.h>

LCD_I2C lcd(0x27,16,2);
int currentStep=0;
int currentMotor=0;
int stated = 0;

const int CIRCLE = 2048;
int pins[]={3,2,1,0};

const char ssid[] = "Goodl3oyZ";
const char pass[] = "1212312121";

const char mqtt_broker[]="test.mosquitto.org";
const char mqtt_topic[]="261215/group25";
const char mqtt_client_id[]="arduino_group_25_13213212"; // must change this string to a unique value
int MQTT_PORT=1883;

int counter=0;

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect(mqtt_client_id)) {  
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe(mqtt_topic);
  // client.unsubscribe("/hello");
}
Adafruit_PCF8574 pcf;
void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  if (!pcf.begin(PCF8574_Address, &Wire)) {
    Serial.println("Couldn't find PCF8574");
  }
  pcf.pinMode(pins[0], OUTPUT);
  pcf.pinMode(pins[1], OUTPUT);
  pcf.pinMode(pins[2], OUTPUT);
  pcf.pinMode(pins[3], OUTPUT);

  currentMotor=0;

  WiFi.begin(ssid, pass);

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported
  // by Arduino. You need to set the IP address directly.
  client.begin(mqtt_broker, MQTT_PORT, net);
  client.onMessage(messageReceived);

  connect();
  displayMessage("Idle");
}

void displayMessage(const String& a){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(a);
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
  if(payload == "A Step"){
    client.publish(mqtt_topic,"Move 1 step");
    displayMessage("Move 1 step");
    currentStep = 0;
    while(currentStep<CIRCLE/16){
      currentMotor = currentStep % 4;
      pcf.digitalWrite(pins[currentMotor],HIGH);
      delay(5);
      pcf.digitalWrite(pins[currentMotor],LOW);
      currentStep++;
    }
    // Serial.print("Current Step : ");
    // Serial.println(currentStep);
    displayMessage("Idle");
    client.publish(mqtt_topic,"Idle");
  }
  if(payload == "circle"){
    client.publish(mqtt_topic,"Move 1 circle");
    displayMessage("Move 1 circle");
    currentStep = 0;
    while(currentStep<CIRCLE){
      currentMotor = currentStep % 4;
      // Serial.println(currentMotor);
      pcf.digitalWrite(pins[currentMotor],HIGH);
      delay(5);
      pcf.digitalWrite(pins[currentMotor],LOW);
      currentStep++;
    }
    // Serial.print("Current Step : ");
    // Serial.println(currentStep);
    client.publish(mqtt_topic,"Idle");
    displayMessage("Idle");
  }
  // Note: Do not use the client in the callback to publish, subscribe or
  // unsubscribe as it may cause deadlocks when other things arrive while
  // sending and receiving acknowledgments. Instead, change a global variable,
  // or push to a queue and handle it in the loop after calling `client.loop()`.
}

void loop() {
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }
  // if(digitalRead(button)==HIGH&&stated==0){
  //   client.publish(mqtt_topic,"On");
  //   stated = 1;
  // }
  // if(digitalRead(button)==LOW&&stated==1){
  //   client.publish(mqtt_topic,"Off");
  //   stated = 0;
  // }
  
  // publish a message roughly every second.
  // not that we don't use delay() because we need to keep calling the client.loop()
  // to keep the connection alive
  /*if (millis() - lastMillis > 2000) {
    lastMillis = millis();
    client.publish(mqtt_topic, "Counter = " + String(counter++));
  }*/

}