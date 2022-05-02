#include <Arduino.h>
#include "BluetoothSerial.h"

// 气压模拟信号采集 相关定义
// 校准项 标准大气压、满量程输出电压值mV VoltageDetector代码烧进去，打开串口监视器可以看到电压
//----------------------------------------------------------------
const float Voltage_100kpa =500; 
const float Voltage_700kpa =3300 ; 
//----------------------------------------------------------------
// 电压采集引脚
const int Pressure_PIN = 34;
// 模块供电电压
const float VCC =3300; 
const float Pressure_100kpa =100000; 
const float Pressure_700kpa =700000 ; 

// 蓝牙通信部分 相关定义
// 实例化蓝牙串口
BluetoothSerial SerialBT;
// 蓝牙事件回调函数
void Bluetooth_Event(esp_spp_cb_event_t event, esp_spp_cb_param_t *param);  
// 从机HC-05 MAC地址
uint8_t address[6]={0x98,0xDA,0xC0,0x00,0x32,0x59}; 

void setup() {
    // ESP32_MASTER 蓝牙主机初始化 
    Serial.begin(9600);
    SerialBT.register_callback(Bluetooth_Event); 
    SerialBT.begin("ESP32_MASTER",true); 
    Serial.printf("Init Successful - Master\r\n");
    SerialBT.connect(address);
    Serial.printf("Connect Successful\r\n");

    // 气压数据处理初始化
    Serial.begin(9600);
    pinMode(Pressure_PIN, INPUT);
    
}

void loop()
{
    // 气压数据线性拟合
    int P_ADC=analogRead(Pressure_PIN);
    float Pressure_V=P_ADC* VCC / 1024.0;
    float pressure = map(Pressure_V, Voltage_100kpa, Voltage_700kpa,Pressure_100kpa, Pressure_700kpa);
    
    // 蓝牙数据传输
    SerialBT.write("Voltage: "+String(Pressure_V) +" V");
    SerialBT.write("Pressure: "+String(pressure) +" pa");

    delay(5000);
}

void Bluetooth_Event(esp_spp_cb_event_t event, esp_spp_cb_param_t *param)  //蓝牙事件回调函数
{
    if(event == ESP_SPP_OPEN_EVT || event == ESP_SPP_SRV_OPEN_EVT) //蓝牙连接成功标志 
    {                                                              //蓝牙主机和从机模式对应的标志不同，前面的是主机模式的，后面是从机模式
        Serial.write("connection successful!\r\n");
    }
    else if(event == ESP_SPP_CLOSE_EVT)     //蓝牙断开连接标志
    {
        Serial.write("disconnect successful!\r\n");
    }
    else if(event == ESP_SPP_DATA_IND_EVT)  //数据接收标志
    {
        while(SerialBT.available())
        {
            Serial.write(SerialBT.read());
        }
        Serial.write("  receive complete! \r\n");
    }
    else if(event == ESP_SPP_WRITE_EVT)     //数据发送标志
    {
        Serial.write("  send complete! \r\n");
    }
}
