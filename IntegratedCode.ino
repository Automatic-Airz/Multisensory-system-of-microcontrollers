#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
// 红外温度传感器IC通信，SCL时钟信号接A5，SDA通信接A4
// 红外火焰传感器 AO-A0 DO-2
// 烟雾传感器 AO-A3 DO-7
// 继电器控制引脚 6
#define SmokeSensor_AO A3
#define SmokeSensor_DO 7
#define FireSensor_AO A0
#define FireSensor_DO 2
#define AlarmBuzzer 9
#define pinRelay 6
unsigned int FireSensorValue = 0;
unsigned int SmokeSensorValue = 0;

// OLED Screen 相关定义
#define SCREEN_WIDTH 128 // 设置OLED宽度,单位:像素
#define SCREEN_HEIGHT 64 // 设置OLED高度,单位:像素
#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 

void Alarm(){
  long frequency = 500; // 蜂鸣器频率
  tone(AlarmBuzzer,frequency);
  delay(1000);
  noTone(AlarmBuzzer);
  delay(2000);
}

void setup() {
    Serial.begin(9600);

    pinMode(SmokeSensor_DO, INPUT);
    pinMode(FireSensor_DO, INPUT);
    pinMode(pinRelay, OUTPUT);
    pinMode(AlarmBuzzer, OUTPUT);
    mlx.begin();  
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
    // 火焰传感器信号处理
    FireSensorValue = analogRead(FireSensor_AO);
    Serial.print("FireSensor AO Value = ");
    Serial.println(FireSensorValue);
    // 烟雾传感器信号处理
    SmokeSensorValue = analogRead(SmokeSensor_AO);
    Serial.print("SmokeSensor AO Value = ");
    Serial.println(SmokeSensorValue);
    // 红外温度传感器信号处理
    int tempC=mlx.readObjectTempC();

    int pressure= 0;

    while(Serial.available()>0)
    {
        pressure=Serial.parseInt();
        // Serial.println(p);
    }

    // 决策
    int Flag = 0;
    string notice;

    if (digitalRead(FireSensor_DO) == LOW) Flag ++;
    if (digitalRead(SmokeSensor_DO) == LOW) Flag +=2;
    if (tempC>100) Flag +=3;

    switch (Flag)
    {
    case 1:
        notice="Attention! Fire detected!"
        words_display(pressure,tempC,notice);
        display.display();
        Alarm();
        break;
    case 2:        
        notice="Attention! Smoke detected!"
        words_display(pressure,tempC,notice);
        display.display();
        Alarm();
        break;
    case 3:
        notice="Warning! Fire and smoke detected!"
        words_display(pressure,tempC,notice);
        display.display();
        Alarm();
        break;
    case 6:
        digitalWrite(pinRelay, HIGH);
        notice="Danger! Fire and smoke detected! The water pump is switched on!"
        words_display(pressure,tempC,notice);
        display.display();
        Alarm();
        delay(10000);
        digitalWrite(pinRelay, LOW);
        break; 
    default:
        notice="System works well!"
        words_display(pressure,tempC,notice);
        display.display();
        break;
    }
    // 若无事发生，间隔1s刷新一次数据
    delay(1000);
}

void words_display(int pressure, int temperature, string notice)
{
    // 清除屏幕
    display.clearDisplay();
    // 设置字体颜色,白色可见
    display.setTextColor(WHITE);
    //设置字体大小
    display.setTextSize(1.5);
    
    //设置光标位置
    display.setCursor(0, 0);
    display.print("Pressure: %d",pressure);
    
    display.setCursor(0, 10);
    display.print("Temperature: %d °C",temperature);
    
    display.setCursor(0, 20);
    display.print("%s",notice);
}