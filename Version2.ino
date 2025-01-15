#include <BleKeyboard.h>

BleKeyboard bleKeyboard("ESP32 Keyboard", "ESP32", 100);

#define NUM_BUTTONS 10

// Button Pins
int buttonPins[NUM_BUTTONS] = {
  14, 12, 13, 5, 18, 4, 16, 17, 27, 26
};

// Corresponding Actions
const char* actions[NUM_BUTTONS] = {
  "Ctrl+Shift+1",  // Mute
  "Ctrl+Shift+2",  // Deafen
  "Ctrl+Shift+3",  // PTT (Hold/Release)
  "Ctrl+Shift+4",  // Stream
  "Ctrl+Shift+5",  // Record
  "Ctrl+Shift+6",  // Virtual Camera
  "Ctrl+Shift+7",  // Camera 1
  "Ctrl+Shift+8",  // Camera 2
  "VolumeUp",      // Volume Up
  "VolumeDown"     // Volume Down
};

unsigned long debounceTimers[NUM_BUTTONS] = {0};
bool lastStates[NUM_BUTTONS] = {HIGH};

const int debounceDelay = 50;

void setup() {
  Serial.begin(115200);
  bleKeyboard.begin();

  // Initialize button pins
  for (int i = 0; i < NUM_BUTTONS; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  Serial.println("Bluetooth Ready");
}

void loop() {
  if (bleKeyboard.isConnected()) {
    unsigned long currentTime = millis();

    for (int i = 0; i < NUM_BUTTONS; i++) {
      bool currentState = digitalRead(buttonPins[i]);

      if (currentState == LOW && lastStates[i] == HIGH && (currentTime - debounceTimers[i] > debounceDelay)) {
        handleAction(i);
        debounceTimers[i] = currentTime;
      } else if (currentState == HIGH && lastStates[i] == LOW) {
        if (strcmp(actions[i], "Ctrl+Shift+3") == 0) {
          // Release PTT (Push-to-Talk) keys
          bleKeyboard.releaseAll();
        }
        if (actions[i] == "VolumeUp" || actions[i] == "VolumeDown") {
          bleKeyboard.releaseAll();
        }
      }

      lastStates[i] = currentState;
    }
  }
}

void handleAction(int index) {
  if (strcmp(actions[index], "VolumeUp") == 0) {
    bleKeyboard.press(KEY_MEDIA_VOLUME_UP);
  } else if (strcmp(actions[index], "VolumeDown") == 0) {
    bleKeyboard.press(KEY_MEDIA_VOLUME_DOWN);
  } else {
    // Parse custom actions (e.g., Ctrl+Shift+X)
    if (strstr(actions[index], "Ctrl")) bleKeyboard.press(KEY_RIGHT_CTRL);
    if (strstr(actions[index], "Shift")) bleKeyboard.press(KEY_RIGHT_SHIFT);
    char key = actions[index][strlen(actions[index]) - 1];
    bleKeyboard.press(key);
    delay(100);
    bleKeyboard.releaseAll();
  }
}
