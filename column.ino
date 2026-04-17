// ===============================
// 4x4x4 LED Cube - Column Glow
// ===============================

// Column pins
int columns[16] = {
  2, 4, 5, 18,
  19, 21, 22, 23,
  13, 12, 14, 27,
  26, 25, 33, 32
};

// Layer pins
int layers[4] = {
  15,   // Layer 1
  16,   // Layer 2 (RX2)
  17,   // Layer 3 (TX2)
  1     // Layer 4 (TX0)
};

// Turn OFF everything
void clearCube() {
  for (int i = 0; i < 16; i++) digitalWrite(columns[i], LOW);
  for (int i = 0; i < 4; i++) digitalWrite(layers[i], LOW);
}

// Light one full column
void lightColumn(int col) {

  // Repeat for persistence (multiplexing)
  for (int repeat = 0; repeat < 100; repeat++) {

    for (int l = 0; l < 4; l++) {

      clearCube();

      digitalWrite(columns[col], HIGH);
      digitalWrite(layers[l], HIGH);

      delayMicroseconds(2000);
    }
  }
}

void setup() {
  for (int i = 0; i < 16; i++) pinMode(columns[i], OUTPUT);
  for (int i = 0; i < 4; i++) pinMode(layers[i], OUTPUT);
}

void loop() {

  // Scan all columns
  for (int c = 0; c < 16; c++) {
    lightColumn(c);
  }
}
