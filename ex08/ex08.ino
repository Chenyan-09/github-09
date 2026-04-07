#include <WiFi.h>
#include <WebServer.h>
const char* ssid = "11111111";
const char* pwd = "147258369";
#define TOUCH_PIN 14

WebServer server(80);
#define LED_PIN 2

bool isDefense = false;
bool isAlarm = false;
unsigned long alarmTime = 0;

void handleRoot() {
  String ds = isDefense ? "<span style='color:red;'>布防中</span>" : "<span style='color:green;'>撤防中</span>";
  String as = isAlarm ? "<span style='color:red;'>报警！</span>" : "<span style='color:green;'>正常</span>";

  String html = "<html><body style='text-align:center;margin-top:60px;'>";
  html += "<h2>ESP32 安防报警</h2>";
  html += "<p>状态：" + ds + "</p>";
  html += "<p>报警：" + as + "</p>";
  html += "<p><a href='/defense'><button style='padding:10px 20px;background:red;color:white;'>布防</button></a></p>";
  html += "<p><a href='/undefense'><button style='padding:10px 20px;background:green;color:white;'>撤防</button></a></p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void handleDefense() {
  isDefense = true;
  isAlarm = false;
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleUndefense() {
  isDefense = false;
  isAlarm = false;
  digitalWrite(LED_PIN, LOW); 
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  pinMode(TOUCH_PIN, INPUT);

  WiFi.begin(ssid, pwd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi已连接");
  Serial.println("IP: " + WiFi.localIP().toString());

  server.on("/", handleRoot);
  server.on("/defense", handleDefense);
  server.on("/undefense", handleUndefense);
  server.begin();
}

void loop() {
  server.handleClient();

  if (isDefense) {
    if (digitalRead(TOUCH_PIN) == LOW) { 
      isAlarm = true;
    } else {
      isAlarm = false;
    }
  } else {
    isAlarm = false;
    digitalWrite(LED_PIN, LOW);
  }

  if (isAlarm) {
    if (millis() - alarmTime > 300) {
      alarmTime = millis();
      static bool s = false;
      s = !s;
      digitalWrite(LED_PIN, s ? HIGH : LOW);
    }
  }
}
