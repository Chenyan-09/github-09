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
int sosxu[] = {0,2,0,2,0,2, 1,2,1,2,1,2, 0,2,0,2,0,2, 3};
int x = 0;         // 当前序列位置

void setup() {
  // 初始化三个引脚为输出模式
  pinMode(ledPin_R, OUTPUT);
  pinMode(ledPin_G, OUTPUT);
  pinMode(ledPin_Y, OUTPUT);
  // 初始状态全部熄灭
  digitalWrite(ledPin_R, LOW);
  digitalWrite(ledPin_G, LOW);
  digitalWrite(ledPin_Y, LOW);
}
void loop() {
  long currentMillis = millis();
  long duration;
  switch(sosxu[x]) {
    case 0: // 短闪（亮）
      duration = a;
      led = HIGH;
      break;
    case 1: // 长闪（亮）
      duration = b;
      led = HIGH;
      break;
    case 2: // 字符间隔（灭）
      duration = c;
      led = LOW;
      break;
    case 3: // 单词间隔（灭，长停顿）
      duration = d;
      led = LOW;
      break;
  }
  if (currentMillis - previousMillis >= duration) {
    previousMillis = currentMillis;
    digitalWrite(ledPin_R, led);
    digitalWrite(ledPin_G, led);
    digitalWrite(ledPin_Y, led);
    x++;
    if (x >= sizeof(sosxu)/sizeof(sosxu[0])) {
      x = 0; // 回到序列开头，循环SOS
    }
  }
}
