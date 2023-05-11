# Arduino Alarmanlage

<br />
<div align="center">
  <a href="https://github.com/noahzmr/react-chat">
    <img src="https://avatars.githubusercontent.com/u/65290559?v=4" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">Arduino Alarmanlage</h3>

  <p align="center">
    A little inspiration for people who want to start with Arduino!
    <br />
    <a href="https://github.com/noahzmr/react-chat"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://chat.noerkelit.online/">View Live Demo</a>
    ·
    <a href="https://github.com/noahzmr/react-chat/issues">Report Bug</a>
    ·
    <a href="https://github.com/noahzmr/react-chat/discussions">Request Feature</a>
  </p>
</div>

<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#introduction">Introduction</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li><a href="#code">Code</a>
        <ul>
            <li><a href="#setup-funktion">Setup-Funktion</a></li>
            <li><a href="#loop-funktion">Loop-Funktion</a></li>
            <li><a href="#displaymsg-funktion">displayMsg-Funktion</a></li>
            <li><a href="#setcolor-funktion">setColor-Funktion</a></li>
            <li><a href="#blink-funktion">blink-Funktion</a></li>
            <li><a href="#waitforbuttondoublepress-funktion">waitForButtonDoublePress-Funktion</a></li>
            <li><a href="#setalarmon-funktion">setAlarmOn-Funktion</a></li>
            <li><a href="#setalarmoff-funktion">setAlarmOff-Funktion</a></li>
            <li><a href="#metalconnection-funktion">metalConnection-Funktion</a></li>
        </ul>
    </li>
    <li><a href="architecture">Architecture</a>
        <ul>
            <li><a href="#verkabelung">Verkabelung</a></li>
            <li><a href="#elektronische-schaltkreis">Elektronische Schaltkreis</a></li>
        </ul>
    </li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#support">Support</a></li>
  </ol>
</details>

## Einleitung

Willkommen zur Dokumentation des spannenden Arduino-Raspberry Projekts, das sich rund um die Simulation einer Alarmanlage dreht. Diese innovative Projektidee wurde entwickelt, um Einsteigern einen faszinierenden Einblick in die aufregende Welt des Arduino zu ermöglichen. Hierbei verbinden wir die Leistungsfähigkeit des Arduino-Mikrocontrollers mit den vielfältigen Möglichkeiten des Raspberry Pi-Minicomputers, um eine interaktive und benutzerfreundliche Alarmanlage zu schaffen.

Dieses Projekt bietet Ihnen eine großartige Gelegenheit, Ihre Fähigkeiten in der Hardwareprogrammierung und -integration zu erweitern, indem Sie praktische Erfahrungen sammeln. Durch die Schritt-für-Schritt-Anleitung und die detaillierten Erklärungen werden Sie in die Lage versetzt, die Grundlagen der Arduino-Programmierung zu erlernen und Ihr Verständnis für elektronische Komponenten und ihre Zusammenspiel zu vertiefen.

Diese Alarmanlage-Simulation wird Ihnen helfen, das Potenzial des Arduino-Mikrocontrollers voll auszuschöpfen, indem Sie verschiedene Sensoren und Aktoren verwenden. Sie werden lernen, wie man Bewegungssensoren und Türkontakte einsetzt, um Eindringlinge zu erkennen, und wie man einen Alarm auslöst, um auf mögliche Sicherheitsverletzungen aufmerksam zu machen. Darüber hinaus werden Sie erfahren, wie man über den Raspberry Pi eine Benutzeroberfläche erstellt, um das System zu steuern und Benachrichtigungen zu empfangen.

Egal, ob Sie bereits Erfahrung mit Arduino und Raspberry Pi haben oder ob Sie neu in der Welt der Mikrocontroller und der Elektronik sind, dieses Projekt ist ein idealer Einstiegspunkt. Es bietet Ihnen die Möglichkeit, Ihre Kreativität einzusetzen, eigene Ideen einzubringen und Ihr Wissen kontinuierlich zu erweitern.

Also lassen Sie uns gemeinsam in diese faszinierende Welt eintauchen und entdecken, wie wir mit Arduino und Raspberry Pi eine beeindruckende Alarmanlage simulieren können!

### Built with

<div style='display: flex; flex-direction: row; justify-content: space-around; align-items: center;'>

[![Arduino](https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)](https://www.arduino.cc/)
[![Raspberry Pi](https://img.shields.io/badge/Raspberry%20Pi-A22846?style=for-the-badge&logo=Raspberry%20Pi&logoColor=white)](https://www.raspberrypi.org/)
[![Elegoo](https://img.shields.io/badge/Elegoo-0E68C2?style=for-the-badge&logo=elegoo&logoColor=white)](https://www.elegoo.com/)
[![Tinkercad](https://img.shields.io/badge/Tinkercad-222F29?style=for-the-badge&logo=tinkercad&logoColor=white)](https://www.tinkercad.com/)
[![Mermaid](https://img.shields.io/badge/Mermaid-003B6F?style=for-the-badge&logo=mermaid&logoColor=white)](https://mermaid-js.github.io/mermaid/)

</div>

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

## Architecture

### Verkabelung

![Verkabelung](/img/arduino.png)

### Elektronische Schaltkreis

<img src="img/electronic_circuit.svg" alt="electronic_circuit">

## Contact

<div style='display: flex; flex-direction: row; justify-content: space-around; align-items: center;'>

[![XING](https://img.shields.io/badge/xing-%23006567.svg?style=for-the-badge&logo=xing&logoColor=white)](https://www.xing.com/profile/NoahDanyael_Zeumer/)

[![LinkedIn](https://img.shields.io/badge/LinkedIn-%230077B5?style=for-the-badge&logo=LinkedIn&logoColor=%23FFFFFF)](https://www.linkedin.com/in/noah-zeumer-34b5081a5/?originalSubdomain=de)

[![IONOS Email](https://img.shields.io/badge/IONOS%20Email-004080?style=for-the-badge&logo=mail.ru&logoColor=white)](mailto:noah@noerkelit.online)

<a href='https://taag.co/GxxtAjXSpr1679622602xuDhbkVpDX' target="_blank"><img style="width: 100px;" alt='qr code medocino' src='img/qr.svg'/></a>

</div>

## Support

If you like this project and it helped you I would appreciate a little support!

<a href='https://www.buymeacoffee.com/noahdnylzmr' target="_blank"><img alt='buy me a coffee' src='https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png'/></a>
