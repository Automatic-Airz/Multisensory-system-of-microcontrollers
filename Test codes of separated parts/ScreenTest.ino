/**********************************************************************
  程序名称/Program name     : words_display
  团队/Team                 : 太极创客团队 / Taichi-Maker (www.taichi-maker.com)
  作者/Author               : Dapenson
  日期/Date（YYYYMMDD）     : 2020/07/01
  程序目的/Purpose          :
  使用OLED0.96 IIC 12864显示文字
  -----------------------------------------------------------------------
  修订历史/Revision History
  日期/Date    作者/Author      参考号/Ref    修订说明/Revision Description
  -----------------------------------------------------------------------
  其它说明：
***********************************************************************/
 
// 引入IIC通讯所需的Wire库文件
// 教程参考http://www.taichi-maker.com/homepage/reference-index/arduino-library-index/wire-library/
#include <Wire.h>
 
// 引入驱动OLED0.96所需的库
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define SCREEN_WIDTH 128 // 设置OLED宽度,单位:像素
#define SCREEN_HEIGHT 64 // 设置OLED高度,单位:像素
 
// 自定义重置引脚,虽然教程未使用,但却是Adafruit_SSD1306库文件所必需的
#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
void setup()
{
  // 初始化Wire库
  //  Wire.begin();
 
  // 初始化OLED并设置其IIC地址为 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}
 
void loop()
{
  words_display();
  display.display();
}
 
void words_display()
{
  // 清除屏幕
  display.clearDisplay();
 
  // 设置字体颜色,白色可见
  display.setTextColor(WHITE);
 
  //设置字体大小
  display.setTextSize(1.5);
 
  //设置光标位置
  display.setCursor(0, 0);
  display.print("TaichiMaker");
 
  display.setCursor(0, 20);
  display.print("time: ");
  //打印自开发板重置以来的秒数：
  display.print(millis() / 1000);
  display.print(" s");
 
  display.setCursor(0, 40);
  display.print("Author: ");
  display.print("Dapenson");
}
 
