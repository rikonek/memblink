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
