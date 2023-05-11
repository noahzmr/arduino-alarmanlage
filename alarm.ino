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
  lcd.setCursor(0, 0);
  lcd.print("Alarmanlage");
  displayMsg("Unscharf");
}

void loop()
{
  waitForButtonDoublePress();
}

void displayMsg(const char *msg)
{
  lcd.setCursor(0, 1);
  lcd.print(msg);
  Serial.println(msg);
  delay(50)
}

void setColor(int red, int green, int blue)
{
  analogWrite(5, red);
  analogWrite(6, green);
  analogWrite(7, blue);
}

void blink(const char *color)
{
  int redValue = 255;
  int blueValue = 255;
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
    if (color == "orange")
    {
      alarmEnabled = true;
      setColor(255, 128, 0);
    }
    else if (color == "red")
    {
      setColor(redValue, 0, 0);
    }
    else if (color == "alert")
    {
      setColor(redValue, 0, blueValue);
      delay(delayTime);
      setColor(0, 0, 0);
      delay(delayTime);
      setColor(0, 0, blueValue);
      delay(delayTime);
      setColor(redValue, 0, 0);
    }
    delay(delayTime);
    setColor(0, 0, 0);
    delay(delayTime);
    if (millis() - startTime >= 20000 && color != "alert")
    {
      delayTime = 100;
    }
  }
  if (alarmEnabled)
  {
    setAlarmOn();
  }
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
      blink("orange");
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
  displayMsg("Active");
  Serial.print("setAlarmOn\n");
  alarmEnabled = true;
}

void setAlarmOff()
{
  setColor(0, 255, 0);
  displayMsg("Unactive");
  Serial.print("setAlarmOff\n");
  alarmEnabled = false;
  alarmTriggered = false;
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
