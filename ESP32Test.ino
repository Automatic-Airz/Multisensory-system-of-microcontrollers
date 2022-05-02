#include <Arduino.h>
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
//蓝牙事件回调函数
void Bluetooth_Event(esp_spp_cb_event_t event, esp_spp_cb_param_t *param);  
//从机HC-05 MAC地址
uint8_t address[6]={0x98,0xDA,0xC0,0x00,0x32,0x59}; 

void setup() {
    //ESP32_MASTER 蓝牙主机初始化 
    Serial.begin(9600);
    SerialBT.register_callback(Bluetooth_Event); 
    SerialBT.begin("ESP32_MASTER",true); 
    Serial.printf("Init Successful - Master\r\n");
    SerialBT.connect(address);
    Serial.printf("Connect Successful\r\n");

    //气压数据处理初始化

    
}

void loop()
{
    if(Master)
        SerialBT.write('A');
    
    delay(3000);
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
