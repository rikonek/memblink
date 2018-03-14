int8_t readButton()
{
  while(true)
  {
    for(uint8_t i=0; i<USED_BUTTON; i++)
    {
      if(digitalRead(array_button[i])==LOW)
      {
        while(digitalRead(array_button[i])==LOW); // hack for push button delay
        delay(100);
        return i;
      }
    }
  }
  return -1;
}

bool resetButton()
{
  if(USED_BUTTON>=4)
  {
    if(digitalRead(array_button[0])==LOW && digitalRead(array_button[1])==LOW && digitalRead(array_button[USED_BUTTON-2])==LOW && digitalRead(array_button[USED_BUTTON-1])==LOW)
    {
      return true;
    }
  }
  return false;
}

