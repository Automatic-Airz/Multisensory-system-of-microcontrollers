// 电压测量显示代码

const int Detect_PIN = A1; // 模拟电压输入接口
const float VCC = 5000.0;
void setup() {
  Serial.begin(9600);
  pinMode(Detect_PIN, INPUT);
}

void loop() {
  int ADC;
  ADC=analogRead(Detect_PIN);
  float Voltage = ADC* VCC / 1024.0;
  Serial.println("The voltage is "+String(Voltage)+"V");
  Serial.println();

  delay(1000);
}
