void ledOn(uint8_t led)
{
  digitalWrite(array_led[led], HIGH);
}

void ledOff(uint8_t led)
{
  digitalWrite(array_led[led], LOW);
}

void allLedOn()
{
  for (uint8_t i = 0; i < USED_BUTTON; i++)
  {
    digitalWrite(array_led[i], HIGH);
  }
}

void allLedOff()
{
  for (uint8_t i = 0; i < USED_BUTTON; i++)
  {
    digitalWrite(array_led[i], LOW);
  }
}

void ledCountDown()
{
  lcd.clear();
  lcd.setCursor(LANG_READY_PADDING, 1);
  lcd.print(LANG_READY);

  allLedOff();
  delay(500);
  allLedOn();
  delay(500);
  uint8_t middle = USED_BUTTON / 2;
  if ((USED_BUTTON % 2) > 0)
  {
    middle++;
  }
  for (uint8_t i = 0; i < middle; i++)
  {
    if ((i + 1) == middle)
    {
      lcd.clear();
      lcd.setCursor(LANG_START_PADDING, 1);
      lcd.print(LANG_START);
    }
    ledOff(i);
    ledOff(USED_BUTTON - 1 - i);
    delay(500);
    if ((i + 1) == middle)
    {
      delay(500);
    }
  }
}

void allLedBlink(uint8_t repeat, uint16_t time)
{
  for (uint8_t i = 0; i < repeat; i++)
  {
    allLedOn();
    delay(time);
    allLedOff();
    delay(time);
  }
}
