#define LED_PIN 2
#define LED_PIN_R 26
#define LED_PIN_G 25
#define LED_PIN_Y 32
long preMillis = 0;
const long t = 1000;
int leds = LOW;
void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT); 
  pinMode(LED_PIN_R, OUTPUT); 
   pinMode(LED_PIN_G, OUTPUT);
    pinMode(LED_PIN_Y, OUTPUT);
}
void loop() 
{
  long currentMillis = millis(); 
  if (currentMillis - preMillis >= t) {
    preMillis = currentMillis; 
    leds = !leds;          
    digitalWrite(LED_PIN, leds);
    digitalWrite(LED_PIN_R, leds);
    digitalWrite(LED_PIN_G, leds);
    digitalWrite(LED_PIN_Y, leds);
    Serial.println(leds);
  }
}
