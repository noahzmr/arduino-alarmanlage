#include <LiquidCrystal.h>

// Pin-Definitionen
const int rs = 2, en = 3, d4 = 13, d5 = 12, d6 = 11, d7 = 10, v0 = 9, a = 8, rw = 4;
const int buttonPin = A0; // Pin für den Button
const int touchPin = A1;  // Der Pin, an dem der Metal-Touch-Sensor angeschlossen ist
// Variablen zur Speicherung des aktuellen Zustands der Alarmanlage
bool alarmEnabled = false;
bool alarmTriggered = false;


// Initialisierung des LCD-Displays
LiquidCrystal lcd(rs, rw, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600); // Für den debug Modus
  pinMode(touchPin, INPUT);  // Setze den Pin als Eingang
  // Initialisierung des LCD-Displays
  lcd.begin(16, 2);

  // Konfiguration von Pin V0 als Ausgang
  pinMode(v0, OUTPUT);

  // Festlegen des Kontrastwerts auf 50%
  analogWrite(v0, 100);

  // Konfiguration von Pin A als PWM-Ausgang
  pinMode(a, OUTPUT);

  // Festlegen des PWM-Werts auf 50% (128 von 255)
  analogWrite(a, 128);


  // Konfiguration des Buttons als Eingang mit Pullup-Widerstand
  pinMode(buttonPin, INPUT_PULLUP);
  // Initialisierung der RGB-LED
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  setColor(0, 255, 0); // RGB-LED ausschalten

  // Ausgabe des Textes auf dem Display
  lcd.setCursor(0, 0);
  lcd.print("Alarmanlage");
  lcd.setCursor(0, 1);
  lcd.print("unscharf");
}

void loop() {
  waitForButtonDoublePress();
}


// Funktion zur Änderung der Farben der RGB-LED
void setColor(int red, int green, int blue) {
  analogWrite(5, red);
  analogWrite(6, green);
  analogWrite(7, blue);

}


void blinkRed() {
  int redValue = 255;
  int delayTime = 200;  // Anfangsverzögerungszeit von 200 Millisekunden

  unsigned long startTime = millis();
  int buttonCount = 0;
  unsigned long lastButtonPressTime = 0; // Zeitpunkt des letzten Tastendrucks
  unsigned long debounceDelay = 50; // Entprellzeit in Millisekunden

  while (millis() - startTime < 30000) {
    int buttonState = digitalRead(buttonPin);
    if (buttonState == LOW && (millis() - lastButtonPressTime) > debounceDelay) {
      lastButtonPressTime = millis();
      buttonCount++;
      if (buttonCount == 2) {
        Serial.println("Double Click!");
        setAlarmOff();
        break;
      }
    }

    setColor(redValue, 0, 0);
    delay(delayTime);
    setColor(0, 0, 0);
    delay(delayTime);

    // Die Verzögerungszeit nach 20 Sekunden ändern
    if (millis() - startTime >= 20000) {
      delayTime = 100;  // Verzögerungszeit auf 100 Millisekunden ändern
    }
  }

}



// Funktion zur Blinkfunktion der RGB-LED
void blinkRedBlue() {
  int redValue = 255;
  int blueValue = 255;
  Serial.println("Blink red and Blue");
  for (int i = 0; i < 10; i++) {
    setColor(redValue, 0, blueValue);
    delay(200);
    setColor(0, 0, 0);
    delay(200);
    setColor(0, 0, blueValue);
    delay(200);
    setColor(redValue, 0, 0);
    delay(200);
  }

  setColor(0, 0, 0); // RGB-Lampe ausschalten
}

void waitForButtonDoublePress() {

  int buttonCount = 0;        // Zähler für die Anzahl der Button-Klicks
  int buttonState = HIGH;     // aktueller Zustand des Buttons

  Serial.print("Wait for button up: ");
  while (digitalRead(buttonPin) != HIGH) {
    Serial.print(".");
    delay(50);
  }


  Serial.print("\nStart wait for Click: ");
  while (buttonCount < 2) {
    buttonState = digitalRead(buttonPin);
    // Überprüfen, ob der Button gedrückt wurde
    if (buttonState == HIGH) {
      Serial.print("~");
      while (digitalRead(buttonPin) != LOW) {
        if (alarmEnabled) {
          checkMotionSensor();
        }
        delay(50); // Entprellen
      }
      buttonCount++;
      delay(250); // Warten auf den nächsten Tastendruck
      Serial.print("+");
    }
    delay(50);

  }
  Serial.print("\n");

  if (buttonCount == 2) {
    Serial.print("Double Click!\n");
    if (!alarmEnabled) {
      blinkOrange();
    } else  {
      setAlarmOff();
    }
  }
  buttonCount = 0;
}

void setAlarmOn() {
  // Lampe auf Rot setzen
  setColor(255, 0, 0);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Alarmanlage");
  lcd.setCursor(0, 1);
  lcd.print("Scharf");
  Serial.print("setAlarmOn\n");
  alarmEnabled = true;
}

void setAlarmOff() {
  // Lampe auf Grün setzen
  setColor(0, 255, 0);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Alarmanlage");
  lcd.setCursor(0, 1);
  lcd.print("Unscharf");
  Serial.print("setAlarmOff\n");
  alarmEnabled = false;
  alarmTriggered = false;
}

void blinkOrange() {
  int delayTime = 200;  // Anfangsverzögerungszeit von 200 Millisekunden
  alarmEnabled = true;
  int buttonCount = 0;
  unsigned long lastButtonPressTime = 0; // Zeitpunkt des letzten Tastendrucks
  unsigned long debounceDelay = 50; // Entprellzeit in Millisekunden

  unsigned long startTime = millis();
  while (millis() - startTime < 30000) {
    int buttonState = digitalRead(buttonPin);
    if (buttonState == LOW && (millis() - lastButtonPressTime) > debounceDelay) {
      lastButtonPressTime = millis();
      buttonCount++;
      if (buttonCount == 2) {
        Serial.println("Double Click!");
        setAlarmOff();
        break;
      }
    }
    setColor(255, 128, 0);
    delay(delayTime);
    setColor(0, 0, 0);
    delay(delayTime);

    // Die Verzögerungszeit nach 20 Sekunden ändern
    if (millis() - startTime >= 20000) {
      delayTime = 100;  // Verzögerungszeit auf 100 Millisekunden ändern~
    }
  }
  if (alarmEnabled) {
    setAlarmOn();
  }

}


void checkMotionSensor() {

  int sensorValue = analogRead(touchPin);  // Lese den Sensorwert
  if (alarmEnabled) {
    Serial.print("\nStart wait for action: ");
    if (sensorValue < 1023) {
    } else {
      lcd.setCursor(0, 1);
      lcd.print("ausgelöst");
      if (alarmTriggered) {
        Serial.println("TRIGEERD THE ALERT");
        Serial.println(sensorValue);
        blinkRedBlue();  // Funktion blinkRedBlue() aufrufen
      } else {
        Serial.println("Countdown for shutdown");
        Serial.println(sensorValue);
        alarmTriggered = true;
        blinkRed();  // Funktion blinkRed() aufrufen
      }


      // Eine Verzögerung von 30 Sekunden
      unsigned long startTime = millis();
      while (millis() - startTime < 30000) {
        waitForButtonDoublePress();
      }

      if (alarmEnabled) {
        Serial.println("Still on!");
        alarmTriggered = true;
      } else {
        Serial.println(alarmTriggered);
        Serial.println(alarmEnabled);
      }

    }
  }
}
