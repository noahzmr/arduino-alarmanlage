eier
# Arduino Alarmanlage

## Code

### Variablen und Bibliotheken

```ino
#include <LiquidCrystal.h>

const int rs = 9, en = 7, d4 = 6, d5 = 5, d6 = 4, d7 = 3, v0 = 10, a = 2, rw = 8;
const int buttonPin = A0;
const int touchPin = A1;
bool alarmEnabled = false;
bool alarmTriggered = false;

LiquidCrystal lcd(rs, rw, en, d4, d5, d6, d7);
```

- Die Bibliothek `LiquidCrystal` wird für die Steuerung des LCD-Displays verwendet.
- Die konstanten Variablen `rs`, `en`, `d4`, `d5`, `d6`, `d7`, `v0`, `a` und `rw` werden verwendet, um die verwendeten Pins für das LCD und andere Komponenten festzulegen.
- `buttonPin` und `touchPin` definieren die Pins, an denen die Taster bzw. der Touch-Sensor angeschlossen sind.
- `alarmEnabled` und `alarmTriggered` sind boolesche Variablen, die den Status der Alarmanlage speichern.
- Das Objekt `lcd` wird erstellt, um die LiquidCrystal-Bibliothek zu verwenden.

### Setup-Funktion

Die setup()-Funktion wird einmal beim Start des Programms aufgerufen und initialisiert die erforderlichen Einstellungen:

```ino
void setup()
{
  Serial.begin(9600);
  pinMode(touchPin, INPUT);
  lcd.begin(16, 2);
  pinMode(v0, OUTPUT);
  analogWrite(v0, 100);
  pinMode(a, OUTPUT);
  analogWrite(a, 128);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  setColor(0, 255, 0);
  lcd.setCursor(0, 0);
  lcd.print("Alarmanlage");
  displayMsg("Unscharf");
}
```

- `Serial.begin(9600)` initialisiert die serielle Kommunikation mit einer Baudrate von 9600.
- `pinMode(touchPin, INPUT)` legt den Modus des Touch-Pins als Eingang fest.
- `lcd.begin(16, 2)` initialisiert das LCD-Display mit 16 Zeichen pro Zeile und 2 Zeilen.
- `pinMode(v0, OUTPUT)` und `analogWrite(v0, 100)` stellen den Ausgangsmodus und den Ausgangswert des Pins v0 ein.
- `pinMode(a, OUTPUT)` und `analogWrite(a, 128)` stellen den Ausgangsmodus und den Ausgangswert des Pins a ein.
- `pinMode(buttonPin, INPUT_PULLUP)` legt den Modus des Taster-Pins als Eingang mit Pull-Up-Widerstand fest.
- `pinMode(11, OUTPUT)`, `pinMode(10, OUTPUT)` und `pinMode(9, OUTPUT)` legen die Modi der Pins 11, 10 und 9 als Ausgang fest.
- `setColor(0, 255, 0)` ruft die Funktion `setColor()` auf und setzt die Farbe des RGB-LEDs auf Grün.
- `lcd.setCursor(0, 0)` positioniert den Cursor auf der ersten Zeile und ersten Spalte des LCD-Displays.
- `lcd.print("Alarmanlage")` gibt den Text "Alarmanlage" auf dem LCD-Display aus.
- `displayMsg("Unscharf")` ruft die Funktion `displayMsg()` auf, um die Nachricht "Unscharf" auf der zweiten Zeile des LCD-Displays und über die serielle Kommunikation anzuzeigen.

### Loop-Funktion

Die `loop()`-Funktion wird kontinuierlich ausgeführt, nachdem die setup()-Funktion abgeschlossen ist:

```ino
void loop()
{
  waitForButtonDoublePress();
}
```

Die `loop()`-Funktion ruft die Funktion `waitForButtonDoublePress()` auf. Diese Funktion wird verwendet, um auf einen doppelten Tastendruck zu warten und entsprechende Aktionen auszuführen.

### displayMsg-Funktion

Die `displayMsg()`-Funktion dient zum Anzeigen einer Nachricht auf dem LCD-Display und über die serielle Kommunikation:

```ino
void displayMsg(const char *msg)
{
  lcd.setCursor(0, 1);
  lcd.print(msg);
  Serial.println(msg);
  delay(50);
}
```

- `lcd.setCursor(0, 1)` positioniert den Cursor auf der zweiten Zeile und ersten Spalte des LCD-Displays.
- `lcd.print(msg)` gibt die übergebene Nachricht auf dem LCD-Display aus.
- `Serial.println(msg)` sendet die Nachricht über die serielle Kommunikation.
- `delay(50)` fügt eine kleine Verzögerung hinzu, um eine flüssige Anzeige zu gewährleisten.

### setColor-Funktion

Die `setColor()`-Funktion steuert die Farbe des RGB-LEDs:

```ino
void setColor(int red, int green, int blue)
{
  analogWrite(13, red);
  analogWrite(12, green);
  analogWrite(11, blue);
}
```

`analogWrite(pin, value)` setzt den angegebenen Pin auf den angegebenen PWM-Wert (Pulsweitenmodulation). Hierbei werden die Pins 13, 12 und 11 verwendet, um die rote, grüne und blaue Farbkomponente des RGB-LEDs zu steuern.

### blink-Funktion

Die `blink()`-Funktion steuert das Blinken des RGB-LEDs und enthält auch eine Funktionalität für einen doppelten Tastendruck:

### waitForButtonDoublePress-Funktion

Die `waitForButtonDoublePress()`-Funktion wartet auf einen doppelten Tastendruck und führt entsprechende Aktionen aus:

```ino
void waitForButtonDoublePress()
{
  int buttonCount = 0;
  int buttonState = HIGH;
  Serial.print("Wait for button up: ");
  while (digitalRead(buttonPin) != HIGH)
  {
    Serial.print(".");
    delay(50);
  }
  Serial.print("\nStart wait for Click: ");
  while (buttonCount < 2)
  {
    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH)
    {
      Serial.print("~");
      while (digitalRead(buttonPin) != LOW)
      {
        if (alarmEnabled)
        {
          metalConnection();
        }
        delay(50);
      }
      buttonCount++;
      delay(250);
      Serial.print("+");
    }
    delay(50);
  }
  Serial.print("\n");

  if (buttonCount == 2)
  {
    Serial.print("Double Click!\n");
    if (!alarmEnabled)
    {
      blink("orange");
    }
    else
    {
      setAlarmOff();
    }
  }
  buttonCount = 0;
}
```

Die Funktion überprüft den Status des Taster-Pins, um einen Tastendruck zu erfassen und auf einen doppelten Tastendruck zu warten.
Sobald ein doppelter Tastendruck erkannt wird, werden entsprechende Aktionen ausgeführt, z. B. das Aufrufen der `blink()`-Funktion oder das Deaktivieren des Alarms.

### setAlarmOn-Funktion

Die `setAlarmOn()`-Funktion aktiviert den Alarm:

```ino
void setAlarmOn()
{
  setColor(255, 0, 0);
  displayMsg("Aktiv");
  Serial.print("setAlarmOn\n");
  alarmEnabled = true;
}
```

Die Funktion ändert die Farbe des RGB-LEDs in Rot, zeigt die Nachricht "Aktiv" auf dem LCD-Display an und aktiviert den Alarm.

### setAlarmOff-Funktion

Die `setAlarmOff()`-Funktion deaktiviert den Alarm:

```ino
void setAlarmOff()
{
  setColor(0, 255, 0);
  displayMsg("Inaktiv");
  Serial.print("setAlarmOff\n");
  alarmEnabled = false;
  alarmTriggered = false;
}
```

- Die Funktion ändert die Farbe des RGB-LEDs in Grün, zeigt die Nachricht "Inaktiv" auf dem LCD-Display an, deaktiviert den Alarm und setzt den Alarmauslösestatus zurück.

### metalConnection-Funktion

Die `metalConnection()`-Funktion überwacht die Verbindung zu einem Metallsensor und löst bei Bedarf den Alarm aus:

```ino
void metalConnection()
{

  int sensorValue = analogRead(touchPin);
  if (alarmEnabled)
  {
    Serial.print("\nStart wait for action: ");
    if (sensorValue < 1023)
    {
    }
    else
    {
      displayMsg("ALARM");
      if (alarmTriggered)
      {
        Serial.println("TRIGEERD THE ALERT");
        Serial.println(sensorValue);
        blink("alert");
      }
      else
      {
        Serial.println("Countdown for shutdown");
        Serial.println(sensorValue);
        alarmTriggered = true;
        blink("red");
      }
      unsigned long startTime = millis();
      while (millis() - startTime < 30000)
      {
        waitForButtonDoublePress();
      }
    }
  }
}
```
