#include <DHT.h>
#define T1Pin 6
#define DHTTYPE DHT22       //DHT 21  (AM2301)
DHT sensor(T1Pin, DHTTYPE);   //Initialize DHT sensor for normal 16mhz Arduino



#define T1HIGH 78
#define T1LOW 74

//relay pinouts
#define T1Relay 9

int state_s1 = 0;

float temp = 0;


void setup() {
  sensor.begin();
  pinMode(T1Relay, OUTPUT);
  digitalWrite(T1Relay, LOW);
  
  }



void SM_s1() {  //temp state machine

  switch (state_s1) {
    case 0:  //cool and check
      digitalWrite(T1Relay, HIGH);
      temp = sensor.readTemperature() *9/5 + 32;
      Serial.println("Temp: ");
      Serial.println(temp);
      Serial.println("State  :");
      Serial.println(state_s1);
      delay(10000);
      if (temp < T1LOW) {
        state_s1 = 1;
      }
    break;



    case 1:  //heat
      digitalWrite(T1Relay, LOW);
      Serial.println("Temp: ");
      temp = sensor.readTemperature() * 9/5 +32;
      Serial.println(temp);
      Serial.println("State  :");
      Serial.println(state_s1);
      delay(10000);
      if (temp > T1HIGH) {
        state_s1 = 0;
      }
    break;
    
  }
  
}

void loop() {
  
//  int chk = sensor.read(T1Pin);
  
  SM_s1();  //run
//  delay(2000);


}
