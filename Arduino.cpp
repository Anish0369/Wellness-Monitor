#include <Wire.h>
#include <SoftwareSerial.h>
#include <PulseSensorPlayground.h>
#include <MPU6050.h>

MPU6050 mpu;
int data = 0;
const int PulseWire = 0;
int Threshold = 550;
PulseSensorPlayground pulseSensor;
int tempPin = A1;
unsigned long reminderTime = 0;
unsigned long reminderInterval = 30000;
unsigned long reminderInterval2 = 30000;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(ledPin, LOW);
  randomSeed(analogRead(0));
  pulseSensor.analogInput(PulseWire);
  pulseSensor.blinkOnPulse(LED);
  pulseSensor.setThreshold(Threshold);
  Wire.begin();
  mpu.initialize();
  Serial.println("MPU6050 initialization successful");
  Serial.begin(9600);
}

void loop() {
  data = Serial.read();
  delay(500);
  if (data > 0) {
    delay(1000);
    if (pulseSensor.sawStartOfBeat()) {
      int myBPM = pulseSensor.getBeatsPerMinute();
      Serial.println(" ♥ A HeartBeat Happened ! ");
      Serial.print("BPM: ");
      Serial.println(myBPM);
    }
    float tempC = analogRead(tempPin) * 0.48828125;
    float tempF = (tempC * 1.8) + 32 + 7;
    Serial.println("Temperature -" + String(tempF) + "F");
    int16_t ax, ay, az, gx, gy, gz;
    float AccY, AccZ, AccX, GyX, GyY, GyZ;
    float AccYPrev = 0;
    unsigned long previousMillis = 0;
    const long interval = 30000;
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    if (ay < -4500) {
      Serial.println("Emergency - fall detected");
    }
    if (tempF > 98.6 || heartRate < 60 || heartRate > 120) {
      Serial.println("Health status: Poor");
    } else {
      Serial.println("Health status: Good");
    }
    delay(2000);
    int16_t ax, ay, az, gx, gy, gz;
    float AccY, AccZ, AccX, GyX, GyY, GyZ;
    float AccYPrev = 0;
    unsigned long previousMillis = 0;
    const long interval = 10000;
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    if (ay < -4500) {
      Serial.println("Emergency - fall detected");
    }
    if (data != 49) {
      if (millis() - reminderTime > reminderInterval) {
        Serial.println("Reminder: Give medicine");
        reminderInterval = reminderInterval + 30000;
      }
      if (millis() - reminderTime > reminderInterval2) {
        Serial.println("Reminder: Drink water");
        Serial.println("Enter command");
        delay(500);
        data = Serial.read();
        Serial.println(data);
      }
    }
  }
}
