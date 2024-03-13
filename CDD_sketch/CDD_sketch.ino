int distanceThreshold = 0;
int cm = 0;
int inches = 0;
int led1 = 2;
int led2 = 3;
int led3 = 4;
int buzzerPin = 5;

void setup()
{
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop()
{
  // Set distance threshold to activate LEDs and buzzer
  distanceThreshold = 350;

  // Measure the ping time in cm
  cm = 0.01723 * readUltrasonicDistance(7,6);

  // Convert to inches by dividing by 2.54
  inches = cm / 2.54;

  Serial.print(cm);
  Serial.print(" cm, ");
  Serial.print(inches);
  Serial.println(" inches");

  if (cm > distanceThreshold)
  {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    noTone(buzzerPin); // Turn off the buzzer if the object is beyond the threshold
  }
  else if (cm <= distanceThreshold && cm > distanceThreshold - 100)
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    tone(buzzerPin, 2000); // Lower frequency for farther distance
    delay(100); // Beep duration
    noTone(buzzerPin); // Turn off the buzzer
    delay(200); // Delay between beeps
  }
  else if (cm <= distanceThreshold - 100 && cm > distanceThreshold - 250)
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    tone(buzzerPin, 1500); // Slightly higher frequency
    delay(100); // Beep duration
    noTone(buzzerPin); // Turn off the buzzer
    delay(100); // Delay between beeps
  }
  else if (cm <= distanceThreshold - 250 && cm > distanceThreshold - 350)
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    tone(buzzerPin, 1000); // Highest frequency for closest distance
    delay(100); // Beep duration
    noTone(buzzerPin); // Turn off the buzzer
    delay(50); // Delay between beeps
  }
}

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);
  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Return the echoPin and return sound wave in microseconds
  return pulseIn(echoPin, HIGH);
}
