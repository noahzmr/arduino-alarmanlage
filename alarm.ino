#include <LiquidCrystal.h>

const int rs = 2, en = 3, d4 = 13, d5 = 12, d6 = 11, d7 = 10, v0 = 9, a = 8, rw = 4;
const int buttonPin = A0;
const int touchPin = A1;
bool alarmEnabled = false;
bool alarmTriggered = false;

LiquidCrystal lcd(rs, rw, en, d4, d5, d6, d7);

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

  displayMsg("unscharf");
}

void loop()
{
  waitForButtonDoublePress();
}

void displayMsg(const char* msg) {
  setColor(255, 0, 0);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Alarmanlage");
  lcd.setCursor(0, 1);
  lcd.print(msg);
  Serial.println(msg);
}


void setColor(int red, int green, int blue)
{
  analogWrite(5, red);
  analogWrite(6, green);
  analogWrite(7, blue);
}

void blinkRed()
{
  int redValue = 255;
  int delayTime = 200;
  unsigned long startTime = millis();
  int buttonCount = 0;
  unsigned long lastButtonPressTime = 0;
  unsigned long debounceDelay = 50;
  while (millis() - startTime < 30000)
  {
    int buttonState = digitalRead(buttonPin);
    if (buttonState == LOW && (millis() - lastButtonPressTime) > debounceDelay)
    {
      lastButtonPressTime = millis();
      buttonCount++;
      if (buttonCount == 2)
      {
        Serial.println("Double Click!");
        setAlarmOff();
        break;
      }
    }
    setColor(redValue, 0, 0);
    delay(delayTime);
    setColor(0, 0, 0);
    delay(delayTime);
    if (millis() - startTime >= 20000)
    {
      delayTime = 100;
    }
  }
}

void blinkRedBlue()
{
  int redValue = 255;
  int blueValue = 255;
  Serial.println("Blink red and Blue");
  for (int i = 0; i < 10; i++)
  {
    setColor(redValue, 0, blueValue);
    delay(200);
    setColor(0, 0, 0);
    delay(200);
    setColor(0, 0, blueValue);
    delay(200);
    setColor(redValue, 0, 0);
    delay(200);
  }
  setColor(0, 0, 0);
}

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
          checkMotionSensor();
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
      blinkOrange();
    }
    else
    {
      setAlarmOff();
    }
  }
  buttonCount = 0;
}

void setAlarmOn()
{
  setColor(255, 0, 0);
  displayMsg("Scharf");
  Serial.print("setAlarmOn\n");
  alarmEnabled = true;
}

void setAlarmOff()
{
  setColor(0, 255, 0);
  displayMsg("Unscharf");
  Serial.print("setAlarmOff\n");
  alarmEnabled = false;
  alarmTriggered = false;
}

void blinkOrange()
{
  int delayTime = 200;
  alarmEnabled = true;
  int buttonCount = 0;
  unsigned long lastButtonPressTime = 0;
  unsigned long debounceDelay = 50;

  unsigned long startTime = millis();
  while (millis() - startTime < 30000)
  {
    int buttonState = digitalRead(buttonPin);
    if (buttonState == LOW && (millis() - lastButtonPressTime) > debounceDelay)
    {
      lastButtonPressTime = millis();
      buttonCount++;
      if (buttonCount == 2)
      {
        Serial.println("Double Click!");
        setAlarmOff();
        break;
      }
    }
    setColor(255, 128, 0);
    delay(delayTime);
    setColor(0, 0, 0);
    delay(delayTime);
    if (millis() - startTime >= 20000)
    {
      delayTime = 100;
    }
  }
  if (alarmEnabled)
  {
    setAlarmOn();
  }
}

void checkMotionSensor()
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
      displayMsg("ausgelöst");
      if (alarmTriggered)
      {
        Serial.println("TRIGEERD THE ALERT");
        Serial.println(sensorValue);
        blinkRedBlue();
      }
      else
      {
        Serial.println("Countdown for shutdown");
        Serial.println(sensorValue);
        alarmTriggered = true;
        blinkRed();
      }
      unsigned long startTime = millis();
      while (millis() - startTime < 30000)
      {
        waitForButtonDoublePress();
      }

      if (alarmEnabled)
      {
        Serial.println("Still on!");
        alarmTriggered = true;
      }
      else
      {
        Serial.println(alarmTriggered);
        Serial.println(alarmEnabled);
      }
    }
  }
}
