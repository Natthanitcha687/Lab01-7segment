// กำหนดขา GPIO ของ ESP32 ที่เชื่อมต่อกับแต่ละ Segment
const int SEG_A = 18; // Segment A (Violet)
const int SEG_B = 5;  // Segment B (Blue)
const int SEG_C = 17; // Segment C (Green)
const int SEG_D = 16; // Segment D (Lime Green)
const int SEG_E = 4;  // Segment E (Yellow)
const int SEG_F = 0;  // Segment F (Orange)
const int SEG_G = 2;  // Segment G (Red)

// กำหนดขา GPIO ของ ESP32 ที่เชื่อมต่อกับขาควบคุมแต่ละหลัก (DIGITS)
// สำหรับ Common Cathode: LOW = เปิดหลัก (กระแสไหลลง GND ผ่านขาควบคุม)
const int DIGIT_1 = 21; // หลักที่ 1 (ซ้ายสุด)
const int DIGIT_2 = 19; // หลักที่ 2 (กลาง)
const int DIGIT_3 = 15; // หลักที่ 3 (ขวาสุด)

// Array ที่เก็บค่าสถานะของแต่ละ Segment สำหรับตัวเลข 0-9
// สำหรับ common cathode: HIGH = เปิด Segment, LOW = ปิด Segment
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
  // กำหนดขา Segment ทั้งหมดเป็น OUTPUT
  pinMode(SEG_A, OUTPUT);
  pinMode(SEG_B, OUTPUT);
  pinMode(SEG_C, OUTPUT);
  pinMode(SEG_D, OUTPUT);
  pinMode(SEG_E, OUTPUT);
  pinMode(SEG_F, OUTPUT);
  pinMode(SEG_G, OUTPUT);

  // กำหนดขา Digit Control ทั้งหมดเป็น OUTPUT
  pinMode(DIGIT_1, OUTPUT);
  pinMode(DIGIT_2, OUTPUT);
  pinMode(DIGIT_3, OUTPUT);

  // เริ่มต้นปิดทุกหลักก่อน (HIGH สำหรับ Common Cathode)
  digitalWrite(DIGIT_1, HIGH);
  digitalWrite(DIGIT_2, HIGH);
  digitalWrite(DIGIT_3, HIGH);
}

void loop() {
  // วนลูปนับจาก 0 ถึง 999
  for (int counter = 0; counter <= 999; counter++) {
    // แยกตัวเลขเป็นหลักร้อย, หลักสิบ, หลักหน่วย
    int hundreds = counter / 100;
    int tens = (counter % 100) / 10;
    int units = counter % 10;

    // Multiplexing เพื่อแสดงตัวเลข
    // จะแสดงแต่ละหลักสลับกันอย่างรวดเร็ว ทำให้ตาเรามองเห็นเป็นตัวเลขค้าง
    for (int i = 0; i < 50; i++) { // วน 50 รอบเพื่อความสว่างที่พอดี
      displayDigit(DIGIT_1, hundreds); // แสดงหลักร้อย
      delay(2);
      displayDigit(DIGIT_2, tens);     // แสดงหลักสิบ
      delay(2);
      displayDigit(DIGIT_3, units);    // แสดงหลักหน่วย
      delay(2);
    }
  }
}

// ฟังก์ชันสำหรับแสดงตัวเลขบน Segment และเปิดหลักที่ต้องการ
void displayDigit(int digitPin, int num) {
  // ปิดทุกหลักก่อนเพื่อป้องกัน Ghosting (ภาพซ้อน)
  digitalWrite(DIGIT_1, HIGH);
  digitalWrite(DIGIT_2, HIGH);
  digitalWrite(DIGIT_3, HIGH);

  // กำหนดค่าให้แต่ละ Segment ตามตัวเลขที่ต้องการแสดง
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

  // เปิดหลักที่ต้องการแสดง
  digitalWrite(digitPin, LOW); // LOW เพื่อเปิด Common Cathode
}
