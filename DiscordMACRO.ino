#include <BleKeyboard.h>


BleKeyboard bleKeyboard("ESP32 Keyboard", "ESP32", 100);

#define BUTTON_PIN_DISCORD_MUTE 27  // Discord Mute
#define BUTTON_PIN_DISCORD_DEAFEN 26  // Discord Deafen
#define BUTTON_PIN_DISCORD_PTT 25 // Discord Push to Talk

const int debounceDelay = 250;

unsigned long lastDebounceDiscordMute = 0;
unsigned long lastDebounceDiscordDeafen = 0;
unsigned long lastDebounceDiscordPTT = 0;

bool lastButtonStateDiscordMute = HIGH;
bool lastButtonStateDiscordDeafen = HIGH;
bool lastButtonStateDiscordPTT = HIGH;


void setup() {
  
  Serial.begin(115200);

  bleKeyboard.begin();

  pinMode(BUTTON_PIN_DISCORD_MUTE, INPUT_PULLUP);
  pinMode(BUTTON_PIN_DISCORD_DEAFEN, INPUT_PULLUP);
  pinMode(BUTTON_PIN_DISCORD_PTT, INPUT_PULLUP);

  Serial.println("Waiting for Bluetooth connection...");
}

void loop() {
  
  if (bleKeyboard.isConnected()) {
    unsigned long currentTime = millis();

    bool buttonStateDiscordMute = digitalRead(BUTTON_PIN_DISCORD_MUTE);
    if (buttonStateDiscordMute == LOW && lastButtonStateDiscordMute == HIGH &&
      (currentTime - lastDebounceDiscordMute > debounceDelay)) {
      bleKeyboard.press(KEY_RIGHT_CTRL); 
      bleKeyboard.press(KEY_RIGHT_SHIFT); 
      bleKeyboard.press(KEY_F1);        
      delay(100);                     
      bleKeyboard.releaseAll();       
      lastDebounceDiscordMute = currentTime;
    }
    lastButtonStateDiscordMute = buttonStateDiscordMute;

    bool buttonStateDiscordDeafen = digitalRead(BUTTON_PIN_DISCORD_DEAFEN);
    if (buttonStateDiscordDeafen == LOW && lastButtonStateDiscordDeafen == HIGH && 
        (currentTime - lastDebounceDiscordDeafen > debounceDelay)) {
        bleKeyboard.press(KEY_RIGHT_CTRL); 
        bleKeyboard.press(KEY_RIGHT_SHIFT); 
        bleKeyboard.press(KEY_F2);
        delay(100);
        bleKeyboard.releaseAll();
        lastDebounceDiscordDeafen = currentTime;
      }
        lastButtonStateDiscordDeafen = buttonStateDiscordDeafen;

    bool buttonStateDiscordPTT = digitalRead(BUTTON_PIN_DISCORD_PTT);
    if (buttonStateDiscordPTT == LOW && lastButtonStateDiscordPTT == HIGH) {
    // Button is pressed
       bleKeyboard.press(KEY_RIGHT_CTRL);
       bleKeyboard.press(KEY_RIGHT_SHIFT);
       bleKeyboard.press(KEY_F3);
    } else if (buttonStateDiscordPTT == HIGH && lastButtonStateDiscordPTT == LOW) {
    // Button is released
    bleKeyboard.releaseAll();
    }
    lastButtonStateDiscordPTT = buttonStateDiscordPTT;

  }
   
}