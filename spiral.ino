// ===============================
// 4x4x4 LED Cube - 3D Spiral Effect
// ===============================

// Column pins (same as your wiring)
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

// Light one voxel
void lightVoxel(int col, int layer) {
  for (int i = 0; i < 60; i++) {
    clearCube();
    digitalWrite(columns[col], HIGH);
    digitalWrite(layers[layer], HIGH);
    delayMicroseconds(2000);
  }
}

void setup() {
  for (int i = 0; i < 16; i++) pinMode(columns[i], OUTPUT);
  for (int i = 0; i < 4; i++) pinMode(layers[i], OUTPUT);
}

// Spiral path (around edges)
int spiralPath[12] = {
  0, 1, 2, 3,   // front row
  7, 11, 15,    // right side
  14, 13, 12,   // back row
  8, 4          // left side
};

void loop() {

  // Move spiral upward through layers
  for (int layer = 0; layer < 4; layer++) {
    for (int i = 0; i < 12; i++) {
      lightVoxel(spiralPath[i], layer);
    }
  }

  // Move spiral downward
  for (int layer = 2; layer >= 1; layer--) {
    for (int i = 0; i < 12; i++) {
      lightVoxel(spiralPath[i], layer);
    }
  }
}
