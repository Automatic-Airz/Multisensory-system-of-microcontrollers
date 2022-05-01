#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
// 红外温度传感器IC通信，SCL时钟信号接A5，SDA通信接A4

// A4A5 红外温度传感器IC通信
// AO-A0 DO-2 红外火焰传感器 
// A1 气压传感器
// AO-A3 DO-7 烟雾传感器
#define SmokeSensor_AO A3
#define SmokeSensor_DO 7
#define FireSensor_AO A0
#define FireSensor_DO 2
#define AlarmBuzzer 9



int pinRelay = 6; // 继电器控制引脚

unsigned int FireSensorValue = 0;
unsigned int SmokeSensorValue = 0;


const int QIYA_PIN = A1; // 电压采集接口
const float VCC =5000.0; // 模块供电电压，ADC参考电压为V
const float Voltage_100kpa =4500; // 标准大气压电压值mV  校准时需修改
const float Voltage_700kpa =5000 ; // 满量程输出电压值mV  需修改
const float Pressure_100kpa =100000; // 标准大气压pa
const float Pressure_700kpa =700000; // 满量程气压pa 

void setup() {
  pinMode(SmokeSensor_DO, INPUT);
  pinMode(FireSensor_DO, INPUT);
  pinMode(pinRelay, OUTPUT);
  pinMode(AlarmBuzzer, OUTPUT);
  Serial.begin(9600);
  mlx.begin();  
}

void Alarm(){
  long frequency = 500; // 蜂鸣器频率
  tone(AlarmBuzzer,frequency);
  delay(1000);
  noTone(AlarmBuzzer);
  delay(2000);
}

// the loop function runs over and over again until power down or reset
void loop() {
  // 火焰传感器信号处理
  FireSensorValue = analogRead(FireSensor_AO);
  Serial.print("FireSensor AD Value = ");
  Serial.println(FireSensorValue);
  // 烟雾传感器信号处理
  SmokeSensorValue = analogRead(SmokeSensor_AO);
  Serial.print("SmokeSensor AD Value = ");
  Serial.println(SmokeSensorValue);
  // 红外温度传感器信号处理
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF()); 
  Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");
  // 胎压传感器信号处理
  int P_ADC=analogRead(QIYA_PIN);
  float Pressure_V=P_ADC* VCC / 1024.0;
  Serial.println("Voltage: "+String(Pressure_V) +" V");
  float pressure = map(Pressure_V, Voltage_100kpa, Voltage_700kpa,Pressure_100kpa, Pressure_700kpa);
  Serial.println("Pressure: "+String(pressure) +" pa");

  Serial.println();
  
  // 决策
  if (digitalRead(FireSensor_DO) == LOW)
  {
    Serial.println("Alarm!Flame Detected!");
    digitalWrite(pinRelay, HIGH);
    Serial.println("The water pump is on!");
    Alarm();
    delay(10000);
    digitalWrite(pinRelay, LOW);

  }
  if (digitalRead(SmokeSensor_DO) == LOW)
  {
    Serial.println("Alarm!Smoke Detected!");
    digitalWrite(pinRelay, HIGH);
    Serial.println("The water pump is on!");
    Alarm();
    delay(10000);
    digitalWrite(pinRelay, LOW);

  }

  
  delay(2000);

}
