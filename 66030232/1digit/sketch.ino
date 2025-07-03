// กำหนดขา GPIO ของ ESP32 ที่เชื่อมต่อกับแต่ละ segment ของ 7-segment display
const int SEG_A = 18; // Segment A
const int SEG_B = 5;  // Segment B
const int SEG_C = 17; // Segment C
const int SEG_D = 16; // Segment D
const int SEG_E = 4;  // Segment E
const int SEG_F = 0;  // Segment F
const int SEG_G = 2;  // Segment G

// Array ที่เก็บค่าสถานะของแต่ละ segment สำหรับตัวเลข 0-9
// สำหรับ common cathode: HIGH = เปิด segment, LOW = ปิด segment
// จัดเรียงตาม A, B, C, D, E, F, G
const int numbers[10][7] = {
  // A  B  C  D  E  F  G
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

void setup() {
  // กำหนดขา GPIO ทั้งหมดเป็น OUTPUT
  pinMode(SEG_A, OUTPUT);
  pinMode(SEG_B, OUTPUT);
  pinMode(SEG_C, OUTPUT);
  pinMode(SEG_D, OUTPUT);
  pinMode(SEG_E, OUTPUT);
  pinMode(SEG_F, OUTPUT);
  pinMode(SEG_G, OUTPUT);
}

void loop() {
  // วนลูปแสดงตัวเลข 0-9
  for (int i = 0; i <= 9; i++) {
    displayNumber(i); // เรียกฟังก์ชันแสดงตัวเลข
    delay(1000);       // หน่วงเวลา 1 วินาที
  }
}

// ฟังก์ชันสำหรับแสดงตัวเลขบน 7-segment display
void displayNumber(int num) {
  // ตรวจสอบว่าตัวเลขอยู่ในช่วง 0-9
  if (num >= 0 && num <= 9) {
    digitalWrite(SEG_A, numbers[num][0]);
    digitalWrite(SEG_B, numbers[num][1]);
    digitalWrite(SEG_C, numbers[num][2]);
    digitalWrite(SEG_D, numbers[num][3]);
    digitalWrite(SEG_E, numbers[num][4]);
    digitalWrite(SEG_F, numbers[num][5]);
    digitalWrite(SEG_G, numbers[num][6]);
  }
}
