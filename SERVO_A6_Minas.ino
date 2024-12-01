#include <SPI.h>
#include <Ethernet2.h>

// Khai báo các thông số mạng
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177);
EthernetServer server(80);

// Khai báo chân điều khiển
const int pulsePin = 9;
const int dirPin = 8;
const int enablePin = 7;

int currentPulse = 0;

void setup() {
  // Khởi động Ethernet
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.begin(9600);

  // Cấu hình các chân đầu ra
  pinMode(pulsePin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enablePin, OUTPUT);

  // Kích hoạt Servo Drive
  digitalWrite(enablePin, HIGH);
}

void loop() {
  // Kiểm tra kết nối khách hàng
  EthernetClient client = server.available();
  if (client) {
    Serial.println("New client");
    boolean currentLineIsBlank = true;
    String request = "";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        request += c;

        if (c == '\n' && currentLineIsBlank) {
          // Phân tích yêu cầu và điều khiển servo
          if (request.indexOf("GET /servo/") >= 0) {
            int posIndex = request.indexOf("GET /servo/") + 11;
            String posString = request.substring(posIndex, request.indexOf(" ", posIndex));
            int pos = posString.toInt();
            moveServo(pos);
          } else if (request.indexOf("GET /increase") >= 0) {
            moveServo(currentPulse + 10);  // Tăng 10 xung
          } else if (request.indexOf("GET /decrease") >= 0) {
            moveServo(currentPulse - 10);  // Giảm 10 xung
          }

          // Phản hồi HTML
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<html><body>");
          client.println("<h1>Servo Control</h1>");
          client.println("<p>Current Pulse: " + String(currentPulse) + "</p>");
          client.println("<a href=\"/increase\"><button>Increase Pulse</button></a>");
          client.println("<a href=\"/decrease\"><button>Decrease Pulse</button></a>");
          client.println("</body></html>");

          break;
        }

        if (c == '\n') {
          currentLineIsBlank = true;
        } else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }

    delay(1);
    client.stop();
    Serial.println("Client disconnected");
  }
}

void moveServo(int position) {
  // Đặt hướng quay của động cơ
  if (position >= 0) {
    digitalWrite(dirPin, HIGH);
  } else {
    digitalWrite(dirPin, LOW);
    position = -position;
  }

  // Tạo xung để di chuyển servo
  for (int i = 0; i < position; i++) {
    digitalWrite(pulsePin, HIGH);
    delayMicroseconds(500);  // Điều chỉnh độ rộng xung nếu cần thiết
    digitalWrite(pulsePin, LOW);
    delayMicroseconds(500);  // Điều chỉnh khoảng cách giữa các xung nếu cần thiết
  }

  currentPulse = position;
}
