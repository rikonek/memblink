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
  for(uint8_t i=0; i<USED_BUTTON; i++)
  {
    digitalWrite(array_led[i], HIGH);
  }
}

void allLedOff()
{
  for(uint8_t i=0; i<USED_BUTTON; i++)
  {
    digitalWrite(array_led[i], LOW);
  }
}

void ledCountDown()
{
  allLedOff();
  delay(500);
  allLedOn();
  delay(500);
  uint8_t middle=USED_BUTTON/2;
  if( (USED_BUTTON%2)>0 )
  {
    middle++;
  }
  for(uint8_t i=0; i<middle; i++)
  {
    ledOff(i);
    ledOff(USED_BUTTON-1-i);
    delay(500);
  }
}

