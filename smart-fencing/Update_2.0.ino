/*
 *  Simple HTTP get webclient test
 */


#include <ESP8266WiFi.h>

const char* ssid     = "Nokia 3";
const char* password = "8144993311Aa@";
const char* host = "www.ksrctiot.intensebee.com";
String api     = "dyg1fhfnk3";
int inputPin = 13;   
int outputPin = 12;   
int inputPin1 = 15; // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int pirState1 = LOW; 
int val = 0; 
int val1 = 0; 
int valu = 0;
void setup() {
   pinMode(LED_BUILTIN, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);
  pinMode(inputPin1, INPUT);
  pinMode(outputPin, OUTPUT);
  Serial.begin(9600);
 
  delay(100);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
    WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;

void loop() {
  
val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(LED_BUILTIN, LOW);  // turn LED ON
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion 1 detected!");
      digitalWrite(outputPin,LOW);
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    digitalWrite(LED_BUILTIN, HIGH); // turn LED OFF
    if (pirState == HIGH){
      // we have just turned of
      Serial.println("Motion 1 ended!");
      digitalWrite(outputPin,HIGH);
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }

val1 = digitalRead(inputPin1);  // read input value
  if (val1 == HIGH) {            // check if the input is HIGH
    digitalWrite(LED_BUILTIN, LOW);  // turn LED ON
    if (pirState1 == LOW) {
      // we have just turned on
      Serial.println("Motion 2 detected!");
      // We only want to print on the output change, not state
      pirState1 = HIGH;
    }
  } else {
    digitalWrite(LED_BUILTIN, HIGH); // turn LED OFF
    if (pirState1 == HIGH){
      // we have just turned of
      Serial.println("Motion 2 ended!");
      // We only want to print on the output change, not state
      pirState1 = LOW;
    }
  }

++value;

  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  delay(1000);
  // We now create a URI for the request
String url = "/update.php?api="+api+"&field1="+val+"&field2="+val1+"&field3="+valu+"&field4="+value+"&field5="+value+"&field6="+value;
  //String url = "/sample/text.txt";
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(50);
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.println(line);
   delay(100);       
  }
  
  Serial.println();
  Serial.println("closing connection");
  delay(1000);
}











