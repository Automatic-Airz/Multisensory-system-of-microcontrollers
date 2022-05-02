/******************************************************************************
Flex_Sensor_Example.ino
Create a voltage divider circuit combining a flex sensor with a 100k resistor.
As the resistance of the flex sensor increases (meaning it's being bent), the
voltage at A0 should decrease.
Development environment specifics:
Arduino 1.6.7
******************************************************************************/
//const int QIYA_PIN = A1; // 电压采集接口
const int QIYA_PIN = 34;
const float VCC =5000.0; // 模块供电电压，ADC参考电压为V
const float Voltage_100kpa =500; // 标准大气压电压值mV  校准时需修改
const float Voltage_700kpa =5000 ; // 满量程输出电压值mV  需修改
const float Pressure_100kpa =100000; // 标准大气压pa
const float Pressure_700kpa =700000 ; // 满量程气压pa 
void setup() 
{
  Serial.begin(9600);
  pinMode(QIYA_PIN, INPUT);
 }
void loop() 
{
  int P_ADC=analogRead(QIYA_PIN);
  float Pressure_V=P_ADC* VCC / 1024.0;
  Serial.println("Voltage: "+String(Pressure_V) +" V");
  float pressure = map(Pressure_V, Voltage_100kpa, Voltage_700kpa,Pressure_100kpa, Pressure_700kpa);
  Serial.println("Pressure: "+String(pressure) +" pa");
  Serial.println(); 

  delay(500);
  }
