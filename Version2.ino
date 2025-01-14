#include <BleKeyboard.h>

BleKeyboard bleKeyboard ("ESP32 Keyboard", "ESP32", 100);

// Discord Buttons
#define Mute 14  
#define Deafen 12 
#define PTT 13

// OBS Stream / Record / Virtual Camera
#define Stream 5
#define Record 18 
#define Virtual_Camera 4 

// OBS Camera Switch
#define Camera_1 16
#define Camera_2 17

// PC Volume Up and Down
#define Volume_Up 27
#define Volume_Down 26

const int debounceDelay = 50;
// Discord
unsigned long lastDebounceMute = 0;
unsigned long lastDebounceDeafen = 0;
unsigned long lastDebouncePTT = 0;
// OBS Stream / Record / Virtual Camera
unsigned long lastDebounceStream = 0;
unsigned long lastDebounceRecord = 0;
unsigned long lastDebounceVirtual = 0;
// OBS Camera Switch
unsigned long lastDebounceCam1 = 0;
unsigned long lastDebounceCam2 = 0;
// PC Volume Up and Down
unsigned long lastDebounceUp = 0;
unsigned long lastDebounceDown = 0;

// Discord
bool lastButtonStateMute = HIGH;
bool lastButtonStateDeafen = HIGH;
bool lastButtonStatePTT = HIGH;
// OBS Stream/ Record/ Virtual Camera
bool lastButtonStateStream = HIGH;
bool lastButtonStateRecord = HIGH;
bool lastButtonStateVirtual = HIGH;
// OBS Camera Switch
bool lastButtonStateCam1 = HIGH;
bool lastButtonStateCam2 = HIGH;
// PC Volume Up and Down
bool lastButtonStateUp = HIGH;
bool lastButtonStateDown = HIGH;

void setup() {
  Serial.begin(115200);
  bleKeyboard.begin();

  // Discord
  pinMode(Mute, INPUT_PULLUP);
  pinMode(Deafen, INPUT_PULLUP);
  pinMode(PTT, INPUT_PULLUP);
  // OBS Stream / Record / Virtual Camera
  pinMode(Stream, INPUT_PULLUP);
  pinMode(Record, INPUT_PULLUP);
  pinMode(Virtual_Camera, INPUT_PULLUP);
  // OBS Camera Switch
  pinMode(Camera_1, INPUT_PULLUP);
  pinMode(Camera_2, INPUT_PULLUP);
  // Volume Up and Down
  pinMode(Volume_Up, INPUT_PULLUP);
  pinMode(Volume_Down, INPUT_PULLUP);

  Serial.println("Bluetooth Ready");
}

void loop() {
  if (bleKeyboard.isConnected()){
    Serial.println("Connected");

    unsigned long currentTime = millis();

    // Discord Mute 
    bool buttonStateMute = digitalRead(Mute);
    if (buttonStateMute == LOW && lastButtonStateMute == HIGH && (currentTime - lastDebounceMute > debounceDelay)) {
      bleKeyboard.press(KEY_RIGHT_CTRL);
      bleKeyboard.press(KEY_RIGHT_SHIFT);
      bleKeyboard.press('1');
      delay(100);
      bleKeyboard.releaseAll();

      lastDebounceMute = currentTime;
    }
    lastButtonStateMute = buttonStateMute;

    // Discord Deafen
    bool buttonStateDeafen = digitalRead(Deafen);
    if (buttonStateDeafen == LOW && lastButtonStateDeafen == HIGH && (currentTime - lastDebounceDeafen > debounceDelay)) {
      bleKeyboard.press(KEY_RIGHT_CTRL);
      bleKeyboard.press(KEY_RIGHT_SHIFT);
      bleKeyboard.press('2');
      delay(100);
      bleKeyboard.releaseAll();

      lastDebounceDeafen = currentTime;
    }
    lastButtonStateDeafen = buttonStateDeafen;
    // Discord PTT  
    bool buttonStatePTT = digitalRead(PTT);
    if (buttonStatePTT == LOW && lastButtonStatePTT == HIGH && (currentTime - lastDebouncePTT > debounceDelay)) {
      bleKeyboard.press(KEY_RIGHT_CTRL);
      bleKeyboard.press(KEY_RIGHT_SHIFT);
      bleKeyboard.press('3');
      delay(100);
    } else if (buttonStatePTT == HIGH && lastButtonStatePTT == LOW) {
      bleKeyboard.releaseAll();
    }
    lastButtonStatePTT = buttonStatePTT;
  
    // OBS Stream
    bool buttonStateStream = digitalRead(Stream);
    if (buttonStateStream == LOW && lastButtonStateStream == HIGH && (currentTime - lastDebounceStream > debounceDelay)) {
    bleKeyboard.press(KEY_RIGHT_CTRL);
    bleKeyboard.press(KEY_RIGHT_SHIFT);
    bleKeyboard.press('4');
    delay(100);
    bleKeyboard.releaseAll();

      lastDebounceStream = currentTime;
    }
    lastButtonStateStream = buttonStateStream;

    // OBS Record
    bool buttonStateRecord = digitalRead(Record);
    if (buttonStateRecord == LOW && lastButtonStateRecord == HIGH && (currentTime - lastDebounceRecord > debounceDelay)) {
    bleKeyboard.press(KEY_RIGHT_CTRL);
    bleKeyboard.press(KEY_RIGHT_SHIFT);
    bleKeyboard.press('5');
    delay(100);
    bleKeyboard.releaseAll();

      lastDebounceRecord = currentTime;
    }
    lastButtonStateRecord = buttonStateRecord;

    // OBS Virtual Camera
    bool buttonStateVirtual = digitalRead(Virtual_Camera);
    if (buttonStateVirtual == LOW && lastButtonStateVirtual == HIGH && (currentTime - lastDebounceVirtual > debounceDelay)) {
    bleKeyboard.press(KEY_RIGHT_CTRL);
    bleKeyboard.press(KEY_RIGHT_SHIFT);
    bleKeyboard.press('6');
    delay(100);
    bleKeyboard.releaseAll();

      lastDebounceVirtual = currentTime;
    }
    lastButtonStateVirtual = buttonStateVirtual;

    // OBS Camera Switch 1
    bool buttonStateCam1 = digitalRead(Camera_1);
    if (buttonStateCam1 == LOW && lastButtonStateCam1 == HIGH && (currentTime - lastDebounceCam1 > debounceDelay)) {
    bleKeyboard.press(KEY_RIGHT_CTRL);
    bleKeyboard.press(KEY_RIGHT_SHIFT);
    bleKeyboard.press('7');
    delay(100);
    bleKeyboard.releaseAll();

      lastDebounceCam1 = currentTime;
    }
    lastButtonStateCam1 = buttonStateCam1;

    // OBS Camera Switch 2
    bool buttonStateCam2 = digitalRead(Camera_2);
    if (buttonStateCam2 == LOW && lastButtonStateCam2 == HIGH && (currentTime - lastDebounceCam2 > debounceDelay)) {
    bleKeyboard.press(KEY_RIGHT_CTRL);
    bleKeyboard.press(KEY_RIGHT_SHIFT);
    bleKeyboard.press('8');
    delay(100);
    bleKeyboard.releaseAll();

      lastDebounceCam2 = currentTime;
    }
    lastButtonStateCam2 = buttonStateCam1;

    // Volume Up 
    bool buttonStateUp = digitalRead(Volume_Up);
    if (buttonStateUp == LOW && lastButtonStateUp == HIGH && (currentTime - lastDebounceUp > debounceDelay)) {
    bleKeyboard.press(KEY_MEDIA_VOLUME_UP);
    } else if (buttonStateUp == HIGH && lastButtonStateUp == LOW) {
      bleKeyboard.releaseAll();
    }
    lastButtonStateUp = buttonStateUp;
    
    // Volume Down 
    bool buttonStateDown = digitalRead(Volume_Down);
    if (buttonStateDown == LOW && lastButtonStateDown == HIGH && (currentTime - lastDebounceDown > debounceDelay)) {
    bleKeyboard.press(KEY_MEDIA_VOLUME_DOWN);
    } else if (buttonStateDown == HIGH && lastButtonStateDown == LOW) {
      bleKeyboard.releaseAll();
    }
    lastButtonStateDown = buttonStateDown;
  }
}
