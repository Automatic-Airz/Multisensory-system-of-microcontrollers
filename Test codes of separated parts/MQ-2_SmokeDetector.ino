/*
   MQ-2烟雾传感器的使用
*/
#include <Arduino.h>

#define Sensor_AO A3
#define Sensor_DO 7

//#define Sensor_AO A0
//#define Sensor_DO 2

unsigned int sensorValue = 0;

void setup()
{
  pinMode(Sensor_AO, INPUT);
  pinMode(Sensor_DO, INPUT);
  Serial.begin(9600);
}

void loop()
{
  sensorValue = analogRead(Sensor_AO);
  Serial.print("Sensor AD Value = ");
  Serial.println(sensorValue);

  if (digitalRead(Sensor_DO) == LOW)
  {
    Serial.println("Alarm!");
  }
  delay(1000);
}

// 相同的代码也可以用于火焰传感器，同时接收AO和DO
// 火焰传感器 AO值一般为1023，台灯灯光贴脸，可以触发报警，AO值到个位数
