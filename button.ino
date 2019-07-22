int8_t readButton()
{
  while (true)
  {
    for (uint8_t i = 0; i < USED_BUTTON; i++)
    {
      if (digitalRead(array_button[i]) == LOW)
      {
        while (digitalRead(array_button[i]) == LOW); // hack for push button delay
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
  uint8_t pushed = 0;
  while (pushed == 0)
  {
    if (digitalRead(array_button[BUTTON_UP]) == LOW)
    {
      while (digitalRead(array_button[BUTTON_UP]) == LOW);
      delay(100);
      pushed = 1; // up
    }
    else if (digitalRead(array_button[BUTTON_DOWN]) == LOW)
    {
      while (digitalRead(array_button[BUTTON_DOWN]) == LOW);
      delay(100);
      pushed = 2; // down
    }
    else if (digitalRead(array_button[BUTTON_BACK]) == LOW)
    {
      while (digitalRead(array_button[BUTTON_BACK]) == LOW);
      delay(100);
      pushed = 3; // back
    }
    else if (digitalRead(array_button[BUTTON_FORWARD]) == LOW)
    {
      while (digitalRead(array_button[BUTTON_FORWARD]) == LOW);
      delay(100);
      pushed = 4; // forward
    }
    else if (digitalRead(array_button[BUTTON_ENTER]) == LOW)
    {
      while (digitalRead(array_button[BUTTON_ENTER]) == LOW);
      delay(100);
      pushed = 5; // enter
    }

    //    bool up=digitalRead(array_button[USED_BUTTON-5]) ? 0 : 1;
    //    bool down=digitalRead(array_button[USED_BUTTON-4]) ? 0 : 1;
    //    bool back=digitalRead(array_button[USED_BUTTON-3]) ? 0 : 1;
    //    bool forward=digitalRead(array_button[USED_BUTTON-2]) ? 0 : 1;
    //    enter=digitalRead(array_button[USED_BUTTON-1]) ? 0 : 1;
  }
  return pushed;
}

void getPlayerName(char *player)
{
  char signs[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz "; // last must be a space
  int8_t signs_position = 0;
  int8_t player_position = 0;
  uint8_t button = 0;

  lcd.clear();
  lcd.setCursor(LANG_ENTER_YOUR_NAME_PADDING, 0);
  lcd.print(LANG_ENTER_YOUR_NAME);
  lcd.setCursor(0, 1);
  lcd.blink();

  while (button != 5)
  {
    lcd.print(signs[signs_position]);
    lcd.moveCursorLeft();
    player[player_position] = signs[signs_position];

    button = cursorButton();
    switch (button)
    {
    case 1:
      signs_position++;
      if (signs_position >= strlen(signs))
      {
        signs_position = 0;
      }
      break;

    case 2:
      signs_position--;
      if (signs_position < 0)
      {
        signs_position = strlen(signs) - 1;
      }
      break;

    case 3:
      lcd.print(signs[strlen(signs) - 1]);
      lcd.moveCursorLeft();
      if (player_position > 0)
      {
        lcd.moveCursorLeft();
      }

      player[player_position] = signs[strlen(signs) - 1];
      player_position--;
      if (player_position < 0)
      {
        player_position = 0;
      }
      signs_position = strlen(signs) - 1;
      break;

    case 4:
      lcd.moveCursorRight();
      player_position++;
      if (player_position >= SCORE_PLAYER_LENGTH_NAME)
      {
        player_position = SCORE_PLAYER_LENGTH_NAME - 1;
      }
      break;
    }
  }
  lcd.noBlink();
}
