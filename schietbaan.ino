// PWM-uitgangen gekoppeld aan knoppen 1 t/m 6
const int pwmPins[6] = {A3, A2, A1, A0, A4, A5}; // PWM1 t/m PWM6
const int buttonPins[6] = {D2, D3, D4, D5, D6, D7}; // Knoppen 1 t/m 6

// Struct voor knipperstatus per kanaal
struct BlinkState {
  bool active = false;
  unsigned long startTime = 0;
  bool previousButtonState = HIGH;
};

BlinkState blinkStates[6];

const unsigned long blinkDuration = 5UL * 60UL * 1000UL; // 5 minuten in ms
const unsigned long blinkInterval = 1000UL;              // 1 seconde knipperen

// Voor synchroon knipperen
unsigned long lastToggleTime = 0;
bool toggleState = true; // begin op HIGH

void setup() {
  // PWM-uitgangen standaard HIGH (MOSFET aan)
  for (int i = 0; i < 6; i++) {
    pinMode(pwmPins[i], OUTPUT);
    digitalWrite(pwmPins[i], HIGH);
  }

  // Knoppen met interne pull-up
  for (int i = 0; i < 6; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}

void loop() {
  unsigned long currentMillis = millis();

  // Knoppen controleren
  for (int i = 0; i < 6; i++) {
    bool currentButton = digitalRead(buttonPins[i]) == LOW;
    bool previousButton = blinkStates[i].previousButtonState;

    if (currentButton && !previousButton) {
      // RISING EDGE – knop net ingedrukt
      if (blinkStates[i].active) {
        // Stop knipperen → uitgang blijft AAN
        blinkStates[i].active = false;
        digitalWrite(pwmPins[i], HIGH);
      } else {
        // Start knipperen
        blinkStates[i].active = true;
        blinkStates[i].startTime = currentMillis;
        digitalWrite(pwmPins[i], toggleState ? HIGH : LOW); // meteen mee knipperen
      }
    }

    blinkStates[i].previousButtonState = currentButton;
  }

  // Check of toggle nodig is
  if (currentMillis - lastToggleTime >= blinkInterval) {
    toggleState = !toggleState;
    lastToggleTime = currentMillis;

    // Zet alle actieve uitgangen in deze toggle-stand
    for (int i = 0; i < 6; i++) {
      if (blinkStates[i].active) {
        digitalWrite(pwmPins[i], toggleState ? HIGH : LOW);
      }
    }
  }

  // Controleer of knipperduur verlopen is
  for (int i = 0; i < 6; i++) {
    if (blinkStates[i].active &&
        (currentMillis - blinkStates[i].startTime >= blinkDuration)) {
      blinkStates[i].active = false;
      digitalWrite(pwmPins[i], HIGH); // terug naar continu aan
    }
  }
}

