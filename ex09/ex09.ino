#include <WiFi.h>
#include <WebServer.h>

const char* ssid     = "11111111";
const char* password = "147258369";

#define TOUCH_PIN 14  // 触摸引脚：GPIO4

WebServer server(80);

// 读取触摸值
String getTouch() {
  int value = touchRead(TOUCH_PIN);
  return String(value);
}

// 主页面（无刷新实时显示）
void handleRoot() {
  String html = R"HTML(
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>触摸实时仪表</title>
<style>
body{text-align:center;font-size:26px;margin-top:60px;background:#111;color:#0f0;}
.number{font-size:60px;font-weight:bold;color:#0ff;}
</style>
</head>
<body>
<h2>ESP32 触摸实时监测</h2>
<div class="number" id="val">--</div>

<script>
function update() {
  fetch("/get").then(res=>res.text()).then(t=>{
    document.getElementById("val").innerText = t;
  });
}
setInterval(update, 100); // 每100ms刷新一次，不闪屏
</script>
</body>
</html>
)HTML";
  server.send(200, "text/html", html);
}

// 返回触摸数据接口
void handleGet() {
  server.send(200, "text/plain", getTouch());
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  server.on("/", handleRoot);
  server.on("/get", handleGet);
  server.begin();
}

void loop() {
  server.handleClient();
}
