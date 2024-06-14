#include <ESP8266WiFi.h>

const char* ssid = "BLUIS";
const char* password = "chanceorchange1";
const int relayPin = 2;  // Chân GPIO để điều khiển relay
WiFiClient client;
void setup() {
  Serial.begin(115200); // This allows you to see ESP01 start data.
  Serial.println("\nESP 01 Starting WiFi test...");
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  pinMode(relayPin, OUTPUT);  // Thiết lập chân GPIO là OUTPUT
}


void loop() {
  if (!client.connected()) {
    if (client.connect("192.168.43.174", 80)) {  // Kết nối đến địa chỉ IP của ESP32 Server
      Serial.println("Connected to Server");
      //client.println("Hello from ESP01 Client");  // Gửi dữ liệu đến ESP32 Server
      client.println();
    }
  }

  while (client.available()) {
    String response = client.readStringUntil('\r');  // Đọc phản hồi từ ESP32 Server
    Serial.print("Response from Server: ");
    Serial.println(response);
    if (response == "ON")
    {
      digitalWrite(relayPin, HIGH);  // Bật relay
      delay(2000);  // Chờ 2 giây
    }
    else
    {
  digitalWrite(relayPin, LOW);  // Tắt relay
  delay(2000);  // Chờ 2 giây
    }
  }
}


  