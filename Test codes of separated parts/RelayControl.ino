int pinRelay = 6;

void setup() {
  Serial.begin(9600);
  pinMode(pinRelay, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pinRelay, HIGH);
  Serial.println("a");
  delay(500);

  digitalWrite(pinRelay, LOW);
  Serial.println("b");
  delay(800);
  
}
