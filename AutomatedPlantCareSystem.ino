#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>  
#include <DHT.h>             
#include <Ultrasonic.h>    

#define MOISTURE_SENSOR_PIN A0
#define SERVO_PIN 9
#define DHT_PIN 7
#define TRIGGER_PIN 5
#define ECHO_PIN 6

#define SOIL_MOISTURE_THRESHOLD 500 
#define WATERING_DURATION 2000       
#define DHT_TYPE DHT22             

Servo waterServo;
Adafruit_SSD1306 display(4);  
DHT dht(DHT_PIN, DHT_TYPE);
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

void setup() {
  Serial.begin(9600);
  waterServo.attach(SERVO_PIN);

  dht.begin();
  display.begin(SSD1306_I2C_ADDRESS, 5, 4);
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int moistureLevel = analogRead(MOISTURE_SENSOR_PIN);
  float distance = ultrasonic.read();

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(temperature);
  display.print(" C");
  display.setCursor(0, 10);
  display.print("Humidity: ");
  display.print(humidity);
  display.print(" %");
  display.setCursor(0, 20);
  display.print("Moisture: ");
  display.print(moistureLevel);
  display.setCursor(0, 30);
  display.print("Distance: ");
  display.print(distance);
  display.print(" cm");
  display.display();

  if (moistureLevel < SOIL_MOISTURE_THRESHOLD) {
    waterPlant();
  }

  delay(5000); 

void waterPlant() {
  waterServo.write(180);  
  delay(WATERING_DURATION);
  waterServo.write(0);
}
