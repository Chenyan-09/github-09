#define TOUCH_PIN  27  
#define LED_PIN    2  

bool ledState = false;
bool lastTouched = false;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.begin(115200);
}

void loop() {
  int val = touchRead(TOUCH_PIN);
  bool nowTouched = (val < 500);
  if (nowTouched && !lastTouched) {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
    Serial.print("LED: ");
    Serial.println(ledState ? "ON" : "OFF");
    delay(50);  
  }
  lastTouched = nowTouched;
}
