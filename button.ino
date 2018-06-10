int8_t readButton()
{
  while (true)
  {
    for (uint8_t i = 0; i < USED_BUTTON; i++)
    {
      if (digitalRead(array_button[i]) == LOW)
      {
        while (digitalRead(array_button[i]) == LOW) // hack for push button delay
        {
        }
        delay(100);
        return i;
      }
    }
  }
  return -1;
}

bool resetButton()
{
  if (USED_BUTTON >= 4)
  {
    if (digitalRead(array_button[0]) == LOW && digitalRead(array_button[1]) == LOW && digitalRead(array_button[USED_BUTTON - 2]) == LOW && digitalRead(array_button[USED_BUTTON - 1]) == LOW)
    {
      return true;
    }
  }
  return false;
}

uint8_t cursorButton()
{
  uint8_t pushed=0;
  while(pushed!=5)
  {
    if(digitalRead(array_button[USED_BUTTON-5])==LOW)
    {
      while(digitalRead(array_button[USED_BUTTON-5])==LOW);
      pushed=1; // up
    }
    else if(digitalRead(array_button[USED_BUTTON-4])==LOW)
    {
      while(digitalRead(array_button[USED_BUTTON-4])==LOW);
      pushed=2; // down
    }
    else if(digitalRead(array_button[USED_BUTTON-3])==LOW)
    {
      while(digitalRead(array_button[USED_BUTTON-3])==LOW);
      pushed=3; // back
    }
    else if(digitalRead(array_button[USED_BUTTON-2])==LOW)
    {
      while(digitalRead(array_button[USED_BUTTON-2])==LOW);
      pushed=4; // forward
    }
    else if(digitalRead(array_button[USED_BUTTON-1])==LOW)
    {
      while(digitalRead(array_button[USED_BUTTON-1])==LOW);
      pushed=5; // enter
    }

//    bool up=digitalRead(array_button[USED_BUTTON-5]) ? 0 : 1;
//    bool down=digitalRead(array_button[USED_BUTTON-4]) ? 0 : 1;
//    bool back=digitalRead(array_button[USED_BUTTON-3]) ? 0 : 1;
//    bool forward=digitalRead(array_button[USED_BUTTON-2]) ? 0 : 1;
//    enter=digitalRead(array_button[USED_BUTTON-1]) ? 0 : 1;
  }
  return pushed;
}

void alfabet()
{
  char alphabet[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwyz";
  while(cursorButton()==5)
  {
    switch(cursorButton())
    {
    
    }
  }
}
