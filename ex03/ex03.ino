const int ledPin_R = 26; 
const int ledPin_G = 25;  
const int ledPin_Y = 32;  
int led = LOW;
long previousMillis = 0;
const long a = 200;    
const long b = 600;   
const long c = 200;     
const long d = 1500; 
// SOS 序列：点=0，划=1，间隔=2，长停顿=3
int sosxu[19] = {0,2,0,2,0,2, 1,2,1,2,1,2, 0,2,0,2,0,2, 3};
int x = 0;         // 当前序列位置

void setup() {
  pinMode(ledPin_R, OUTPUT);
  pinMode(ledPin_G, OUTPUT);
  pinMode(ledPin_Y, OUTPUT);
  digitalWrite(ledPin_R, LOW);
  digitalWrite(ledPin_G, LOW);
  digitalWrite(ledPin_Y, LOW);
}
void loop() {
  long currentMillis = millis();
  long t;//持续时间
  switch(sosxu[x]) {
    case 0: // 短闪（亮）
      t = a;
      led = HIGH;
      break;
    case 1: // 长闪（亮）
      t = b;
      led = HIGH;
      break;
    case 2: // 字符间隔（灭）
      t = c;
      led = LOW;
      break;
    case 3: // 单词间隔（灭，长停顿）
      t = d;
      led = LOW;
      break;
  }
  if (currentMillis - previousMillis >= t) {
    previousMillis = currentMillis;
    digitalWrite(ledPin_R, led);
    digitalWrite(ledPin_G, led);
    digitalWrite(ledPin_Y, led);
    x++;
    if (x >= 19) {
      x = 0; // 回到序列开头，循环SOS
    }
  }
}
