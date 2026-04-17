// ===============================
// 4x4x4 LED Cube - Layer Glow
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

// Turn OFF all layers
void turnOffLayers() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(layers[i], LOW);
  }
}

// Turn OFF all columns
void turnOffColumns() {
  for (int i = 0; i < 16; i++) {
    digitalWrite(columns[i], LOW);
  }
}

// Light full layer
void lightLayer(int layer) {

  for (int repeat = 0; repeat < 150; repeat++) {

    turnOffLayers();
    turnOffColumns();

    // Turn ON all columns
    for (int c = 0; c < 16; c++) {
      digitalWrite(columns[c], HIGH);
    }

    // Turn ON selected layer
    digitalWrite(layers[layer], HIGH);

    delayMicroseconds(2000);
  }
}

void setup() {
  for (int i = 0; i < 16; i++) pinMode(columns[i], OUTPUT);
  for (int i = 0; i < 4; i++) pinMode(layers[i], OUTPUT);
}

void loop() {

  // Move upward
  for (int l = 0; l < 4; l++) {
    lightLayer(l);
  }

  // Move downward
  for (int l = 2; l >= 1; l--) {
    lightLayer(l);
  }
}
