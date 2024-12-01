1. Phần cứng cần thiết
Arduino (Uno, Nano, hoặc Mega)
Module Ethernet W5500
MINAS A6 Series AC Servo Motor và Servo Drive
Nguồn cung cấp phù hợp
Dây nối
2. Kết nối phần cứng
Kết nối module Ethernet W5500 với Arduino như trước.
Kết nối các chân điều khiển của MINAS A6 Servo Drive với Arduino:
Pulse (PUL+): kết nối với chân PWM trên Arduino (ví dụ: chân 9)
Direction (DIR+): kết nối với chân điều khiển chiều (ví dụ: chân 8)
Enable (ENA+): kết nối với chân điều khiển bật/tắt (ví dụ: chân 7)
Các chân PUL-, DIR-, và ENA- nối với GND của Arduino.
3. Sử dụng
Nạp chương trình vào Arduino.
Kết nối Arduino và module Ethernet vào mạng của bạn.
Truy cập vào địa chỉ IP của Arduino từ trình duyệt web (ví dụ: http://192.168.1.177).
Sử dụng các nút "Increase Pulse" và "Decrease Pulse" trên trang web để điều khiển số xung.