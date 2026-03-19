// 定义板载LED引脚，避免使用"魔法数字"
#define LED_PIN 2
#define LED_PIN_R 26
#define LED_PIN_G 25
#define LED_PIN_Y 32
void setup() {
  // 初始化串口通信
  Serial.begin(115200);
  // 初始化板载LED引脚为输出模式
  pinMode(LED_PIN, OUTPUT); 
  pinMode(LED_PIN_R, OUTPUT); 
   pinMode(LED_PIN_G, OUTPUT);
    pinMode(LED_PIN_Y, OUTPUT);
}

void loop() {
  Serial.println("Hello ESP32!");
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(LED_PIN_R, HIGH);
  digitalWrite(LED_PIN_G, HIGH);
  digitalWrite(LED_PIN_Y, HIGH);// 点亮LED
  delay(500);                   // 等待1秒
  digitalWrite(LED_PIN, LOW); 
  digitalWrite(LED_PIN_R, LOW);
  digitalWrite(LED_PIN_G, LOW);
  digitalWrite(LED_PIN_Y, LOW);// 熄灭LED
  delay(500);              // 等待1秒
}
