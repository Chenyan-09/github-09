#define TOUCH_PIN 27 
#define LED_PIN   2    
const int freq = 5000;
const int res = 8;
int speedLevel = 1;   
bool lastTouched = false;
void setup() {
  Serial.begin(115200);
  ledcAttach(LED_PIN, freq, res); 
}
void loop() {
  int val = touchRead(TOUCH_PIN);
  bool nowTouched = (val < 700);
  if (nowTouched && !lastTouched) {
    speedLevel = (speedLevel % 3) + 1; 
    Serial.print("当前档位: ");
    Serial.println(speedLevel);
    delay(50); 
  }
  lastTouched = nowTouched;
  int step;
  if (speedLevel == 1) step = 1;   
  else if (speedLevel == 2) step = 10; 
  else step = 20; 
  for (int duty = 0; duty <= 255; duty += step) {
    ledcWrite(LED_PIN, duty);
    delay(10);
  }
  for (int duty = 255; duty >= 0; duty -= step) {
    ledcWrite(LED_PIN, duty);
    delay(10);
  }
}
