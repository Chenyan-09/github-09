#include <WiFi.h>
#include <WebServer.h>
const char* ssid = "11111111";
const char* pwd = "147258369";
#define LED 2 
WebServer server(80);
int lx = 0; 
void root() {
  String h = "<html><body style='text-align:center;'>";
  h += "<h2>LED调光</h2>";
  h += "<input type='range' min=0 max=255 oninput='fetch(\"/d?v=\"+this.value)'>";
  h += "</body></html>";
  server.send(200, "text/html", h);
}
void dim() {
  if(server.hasArg("v")) {
    lx = server.arg("v").toInt();
    lx = constrain(lx, 0, 255); 
    analogWrite(LED, lx);
  }
  server.send(200);
}

void setup() {
  Serial.begin(115200);
  analogWrite(LED, 0);
  WiFi.begin(ssid, pwd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi连接成功！");
  Serial.print("访问地址：http://");
  Serial.println(WiFi.localIP());
  server.on("/", root);
  server.on("/d", dim);
  server.begin();
}

void loop() {
  server.handleClient();
}
