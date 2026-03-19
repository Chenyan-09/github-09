// 定义LED引脚
const int ledPin = 26;  
const int ledPin_G = 25; 
const int ledPin_Y = 32; 

// 设置PWM属性
const int freq = 5000;          // 频率 5000Hz
const int resolution = 8;       // 分辨率 8位 (0-255)

void setup() {
  Serial.begin(115200);
  ledcAttach(ledPin, freq, resolution);
    ledcAttach(ledPin_G, freq, resolution);
       ledcAttach(ledPin_Y, freq, resolution);
}

void loop() {
  // 逐渐变亮
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   

    ledcWrite(ledPin, dutyCycle);  
      ledcWrite(ledPin_G, 255-dutyCycle);
        ledcWrite(ledPin_Y, dutyCycle); 
    delay(100);
  }

  // 逐渐变暗
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    ledcWrite(ledPin, dutyCycle);  
      ledcWrite(ledPin_G, 255-dutyCycle);
        ledcWrite(ledPin_Y, dutyCycle); 
    delay(100);
  }
  
  Serial.println("Breathing cycle completed");
}
