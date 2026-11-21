int Vo = A0;
int V_led = 12;

const int SAMPLES = 10;  // 한 번 출력할 때 측정하는 횟수

void setup(){
  Serial.begin(9600);
  pinMode(V_led, OUTPUT);
  pinMode(Vo, INPUT);
}

// 센서에서 전압을 한 번 읽음 (LED 켜고 0.28ms 뒤 측정, 주기 10ms)
float readVoltage(){
  digitalWrite(V_led, LOW);
  delayMicroseconds(280);
  int Vo_value = analogRead(Vo);
  delayMicroseconds(40);
  digitalWrite(V_led, HIGH);
  delayMicroseconds(9680);

  return Vo_value * 5.0 / 1023.0;
}

void loop(){
  // 한 번만 재면 값이 너무 튀어서 여러 번 재서 평균
  float sum = 0;
  for (int i = 0; i < SAMPLES; i++) {
    sum += readVoltage();
  }
  float Voltage = sum / SAMPLES;

  float dustDensity = (Voltage - 0.5) / 0.005;

  // 공기가 깨끗하면 전압이 0.5V보다 낮아서 음수가 나옴
  if (dustDensity < 0) {
    dustDensity = 0;
  }

  Serial.print("dust=");
  Serial.println(dustDensity);

  delay(1000);
}
