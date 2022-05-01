int pinBuzzer = 9;

void setup() {
  // 将蜂鸣器引脚初始化为输出通道
  // initialize the pinBuzzer as an OUTPUT channel
  pinMode(pinBuzzer, OUTPUT);
}

void loop() {
  // choose a frequency for the pinBuzzer
  // 选择一个蜂鸣频率
  long frequency = 500;
  // output a signal of the frequency you choose on the pinBuzzer
  // 在蜂鸣器引脚通道输出选定频率
  tone(pinBuzzer, frequency);
  // the sound will last 1000 ms
  // 蜂鸣持续1000 ms
  delay(1000);
  // turn off the Buzzer for 2000 ms
  // 停止蜂鸣2000 ms
  noTone(pinBuzzer);
  delay(2000);
}
