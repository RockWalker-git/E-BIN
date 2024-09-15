  

#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int rainPin = A0;

int thresholdValue = 700;
#include <Servo.h>
Servo servo1;
int initangle = 0;
const int trigPin = 7;
const int echoPin = 6;
const int buzzPin = 13;
const int LedRed = 10;

float duration;
float distanceCm;
int buttonStatus1 = 0;
// Setup the LiquidCrystal library with the pin numbers we have
// physically connected the module to.


int lastUpdate = 0;
int currentIndex = 0;


void setup() {
  Serial.begin(9600);
  servo1.attach(8);

  pinMode(rainPin, INPUT);
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
   Serial.begin(9600);
   pinMode(LedRed, OUTPUT);
    pinMode(buzzPin, OUTPUT);

}

void loop() {

 
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distanceCm = (duration*.0343)/2;

  Serial.print(distanceCm);
  Serial.print("cm");
  delay(100);
  if (distanceCm <= 6 )  {
    lcd.setCursor(0, 1);
    lcd.print("Filled");
    delay(60);
    digitalWrite(LedRed, HIGH);
    digitalWrite(buzzPin, HIGH);
    tone(buzzPin,0,350 );
    delay(60);
    digitalWrite(LedRed, LOW);
    digitalWrite(buzzPin, LOW);
    tone(buzzPin, 0, 350);
    
  }
  else
  {
    lcd.setCursor(0, 1);
    lcd.print("Not Filled");
    delay(60);
  }
  int time = millis();
  {
    // Move the cursor back to the first column of the first row.
    lcd.setCursor(0, 0);
  }
  // read the input on analog pin 0:
  int sensorValue = analogRead(rainPin);
  Serial.print(sensorValue);
  if (sensorValue < thresholdValue) {
    if (currentIndex == 0 || currentIndex == 2)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(" Wet Garbage");
    }

    Serial.println(" -Wet");
    servo1.write(15);
    delay(2000);
    servo1.write(90);
    delay(2000);
  }
  else {
    if (currentIndex == 0 || currentIndex == 2)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(" Garbage");
    }

    Serial.println(" - Dry");
    servo1.write(135);
    delay(2000);
    servo1.write(90);
    delay(2000);

  }

  if ((time  - lastUpdate) >= 800)


    // If we are writing "Drink all the..." or "Hack all the..."
    // then clear the screen and print the appropriate line.


    // Increment or reset the current index.
    if (currentIndex == 3)
    {
      currentIndex = 0;
    }
    else
    {
      currentIndex += 1;
    }

  // Update the time that we last refreshed the screen to track
  // when to update it again.
  lastUpdate = time;
  
}
