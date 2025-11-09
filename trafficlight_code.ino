#include <TM1637Display.h>

// TM1637 Display pins (A4 = DIO, A5 = CLK)
#define DIO A4
#define CLK A5
TM1637Display display(CLK, DIO);

// Sensors
#define EAST_SENSOR 2
#define WEST_SENSOR 3

// Signal 1 (East)
#define RED1     6
#define YELLOW1  7
#define GREEN1   8

// Signal 2 (West)
#define RED2     9
#define YELLOW2  10
#define GREEN2   11

// Segment patterns for letters (abcdefg)
// 0b0GFEDCBA
#define SEG_A  0b01110111
#define SEG_C  0b00111001
#define SEG_L  0b00111000
#define SEG_R  0b01010000
#define SEG_S  0b01101101
#define SEG_T  0b01111000
#define SEG_O  0b01111111
#define SEG_P  0b01110011
#define SEG_G  0b01111101

// --- Function Prototypes ---
void allOff();
void showMessage(String msg);
void showCountdown();
void blinkBothYellow(int cycles);
void handleSingleSide(int side);
void normalAlternation();

void setup() {
  pinMode(EAST_SENSOR, INPUT);
  pinMode(WEST_SENSOR, INPUT);

  pinMode(RED1, OUTPUT);
  pinMode(YELLOW1, OUTPUT);
  pinMode(GREEN1, OUTPUT);
  pinMode(RED2, OUTPUT);
  pinMode(YELLOW2, OUTPUT);
  pinMode(GREEN2, OUTPUT);

  Serial.begin(9600);
  display.setBrightness(7);
  display.clear();

  allOff();
}

void loop() {
  int east = digitalRead(EAST_SENSOR);
  int west = digitalRead(WEST_SENSOR);

  Serial.print("East: "); Serial.print(east == LOW ? "Vehicle" : "Clear");
  Serial.print(" | West: "); Serial.println(west == LOW ? "Vehicle" : "Clear");

  if (east == LOW && west == LOW) {
    Serial.println("Both sides vehicles → Blink Yellow both");
    showMessage("CA");
    blinkBothYellow(5);
  }
  else if (east == LOW && west == HIGH) {
    Serial.println("Vehicle only East side");
    handleSingleSide(1);
  }
  else if (west == LOW && east == HIGH) {
    Serial.println("Vehicle only West side");
    handleSingleSide(2);
  }
  else {
    Serial.println("No vehicles → Normal alternation (show only GO)");
    normalAlternation();
  }
}

// --- Turn all lights OFF ---
void allOff() {
  digitalWrite(RED1, LOW);
  digitalWrite(YELLOW1, LOW);
  digitalWrite(GREEN1, LOW);
  digitalWrite(RED2, LOW);
  digitalWrite(YELLOW2, LOW);
  digitalWrite(GREEN2, LOW);
}

// --- Display text on TM1637 ---
void showMessage(String msg) {
  display.clear();

  if (msg == "CA") {
    uint8_t data[] = { SEG_C, SEG_A, 0, 0 };
    display.setSegments(data);
  } 
  else if (msg == "STOP") {
    uint8_t data[] = { SEG_S, SEG_T, SEG_O, SEG_P };
    display.setSegments(data);
  } 
  else if (msg == "GO") {
    uint8_t data[] = { SEG_G, SEG_O, 0, 0 };
    display.setSegments(data);
  }
}

// --- Countdown 3 → 2 → 1 → GO ---
void showCountdown() {
  for (int i = 3; i >= 1; i--) {
    display.showNumberDec(i, false, 1, 1);  // centered
    delay(1000);
  }
  showMessage("GO");
}

// --- Blink both YELLOWs ---
void blinkBothYellow(int cycles) {
  for (int i = 0; i < cycles; i++) {
    allOff();
    digitalWrite(YELLOW1, HIGH);
    digitalWrite(YELLOW2, HIGH);
    delay(500);
    allOff();
    delay(500);
  }
}

// --- Handle single-side vehicle (STOP → Countdown → GO) ---
void handleSingleSide(int side) {
  allOff();
  if (side == 1) {
    // East vehicle waiting
    digitalWrite(RED1, HIGH);      // RED ON
    digitalWrite(GREEN2, HIGH);    // Opposite side GREEN
    showMessage("STOP");           // display STOP
    delay(3000);

    showCountdown();               // countdown appears while RED is still ON

    allOff();
    digitalWrite(GREEN1, HIGH);    // GREEN ON
    digitalWrite(RED2, HIGH);      // opposite RED
    showMessage("GO");
    delay(5000);
  } else {
    // West vehicle waiting
    digitalWrite(RED2, HIGH);      // RED ON
    digitalWrite(GREEN1, HIGH);    // Opposite side GREEN
    showMessage("STOP");
    delay(3000);

    showCountdown();               // countdown while RED

    allOff();
    digitalWrite(GREEN2, HIGH);
    digitalWrite(RED1, HIGH);
    showMessage("GO");
    delay(5000);
  }
  allOff();
}

// --- Normal alternation when no vehicles (show only GO) ---
void normalAlternation() {
  // Phase A
  allOff();
  digitalWrite(RED1, HIGH);
  digitalWrite(GREEN2, HIGH);
  showMessage("GO");   // always show GO
  delay(5000);

  // Yellow transition both
  allOff();
  digitalWrite(YELLOW1, HIGH);
  digitalWrite(YELLOW2, HIGH);
  delay(2000);

  // Phase B
  allOff();
  digitalWrite(GREEN1, HIGH);
  digitalWrite(RED2, HIGH);
  showMessage("GO");   // always show GO
  delay(5000);

  // Yellow transition again
  allOff();
  digitalWrite(YELLOW1, HIGH);
  digitalWrite(YELLOW2, HIGH);
  delay(2000);
}
