void runG1P1() // Game 1 (memory) - player 1
{
  if(resetButton())
  {
    theBest data;
    writeGameScore(NO_GAME_1, data);

    #if DEBUG
      Serial.println("Cleared!");
    #endif
  
    lcd.clear();
    lcd.setCursor(LANG_CLEARED_PADDING,1);
    lcd.print(LANG_CLEARED);

    delay(1000);
    return false;
  }

  theBest best=readGameScore(NO_GAME_1);

  #if DEBUG
    Serial.println("Memory");
    Serial.print("The best result: ");
    Serial.print(best.score);
    Serial.print(", time: ");
    Serial.println(formatMillis(best.time));
  #endif

  lcd.clear();
  lcd.setCursor(LANG_GAME1_NAME_PADDING,0);
  lcd.print(LANG_GAME1_NAME);
  lcd.setCursor(LANG_THE_BEST_PADDING,2);
  lcd.print(LANG_THE_BEST);
  lcd.print(": ");
  lcd.print(best.score);
  lcd.setCursor(LANG_THE_BEST_TIME_PADDING,3);
  lcd.print(LANG_THE_BEST_TIME);
  lcd.print(": ");
  lcd.print(formatMillis(best.time));

  randomSeed(millis());
  uint8_t sequence[GAME_MEMORY_SEQUENCE]={0};
  for(uint8_t i=0; i<GAME_MEMORY_SEQUENCE; i++)
  {
    sequence[i]=random(0,USED_BUTTON);
  }

  unsigned long time_start=millis();
  unsigned long time_diff=0b11111111111111111111111111111111;
  int16_t round=0;
  uint8_t score=0;
  while(round>-1 && round<GAME_MEMORY_SEQUENCE)
  {
    showSequenceG1P1(sequence, round);
    if(checkSequenceG1P1(sequence, round))
    {
      time_diff=millis()-time_start;
      round++;
      score++;

      #if DEBUG
        Serial.print("Score: ");
        Serial.print(score);
        Serial.print("/");
        Serial.print(GAME_MEMORY_SEQUENCE);
        Serial.print(", time: ");
        Serial.println(formatMillis(time_diff));
      #endif

      lcd.clear();
      lcd.setCursor(LANG_GAME1_NAME_PADDING,0);
      lcd.print(LANG_GAME1_NAME);
      lcd.setCursor(LANG_SCORE_PADDING,2);
      lcd.print(LANG_SCORE);
      lcd.print(": ");
      lcd.print(score);
      lcd.setCursor(LANG_SCORE_TIME_PADDING,3);
      lcd.print(LANG_SCORE_TIME);
      lcd.print(": ");
      lcd.print(formatMillis(time_diff));
    }
    else
    {
      round=-1;
    }
  }
  if(score>best.score || (score==best.score && time_diff<best.time))
  {
    theBest data;
    data.score=score;
    data.time=time_diff;
//    data.player=
    writeGameScore(NO_GAME_1, data);

    #if DEBUG
      Serial.println("Game over! You win!");
    #endif

    lcd.clear();
    lcd.setCursor(LANG_GAME_OVER_PADDING,0);
    lcd.print(LANG_GAME_OVER);
    lcd.setCursor(LANG_GAME_OVER_WIN_PADDING,2);
    lcd.print(LANG_GAME_OVER_WIN);
  }
  else
  {
    #if DEBUG
      Serial.print("Game over! Score: ");
      Serial.print(score);
      if(score > 0)
      {
        Serial.print(", time: ");
        Serial.println(formatMillis(time_diff));
      }
      else
      {
        Serial.println("");
      }
    #endif

    lcd.clear();
    lcd.setCursor(LANG_GAME_OVER_PADDING,0);
    lcd.print(LANG_GAME_OVER);
    lcd.setCursor(LANG_SCORE_PADDING,2);
    lcd.print(LANG_SCORE);
    lcd.print(": ");
    lcd.print(score);
    if(score > 0)
    {
      lcd.setCursor(LANG_SCORE_TIME_PADDING,3);
      lcd.print(LANG_SCORE_TIME);
      lcd.print(": ");
      lcd.print(formatMillis(time_diff));
    }
  }
  if(round>-1)
  {
    allLedBlink(2,400);
    delay(4200);
  }
  else // mistake
  {
    allLedBlink(2,100);
    delay(4800);
  }
}

void showSequenceG1P1(const uint8_t *sequence, int16_t round)
{
  #if DEBUG
    Serial.print("Displayed sequence: ");
  #endif

  allLedOff();
  for(uint8_t i=0; i<(round+1); i++)
  {
    #if DEBUG
      Serial.print(sequence[i]+1);
    #endif

    ledOn(sequence[i]);
    delay(500);
    ledOff(sequence[i]);
    delay(500);
  }
  #if DEBUG
    Serial.println("");
  #endif
}

bool checkSequenceG1P1(const uint8_t *sequence, int16_t round)
{
  #if DEBUG
    Serial.print("Entered sequence:   ");
  #endif

  uint8_t position=0;
  int8_t user=-1;
  for(uint8_t i=0; i<round+1; i++)
  {
    user=readButton();

    #if DEBUG
      Serial.print(user+1);
    #endif

    if(user==sequence[i])
    {
      user=-1;
    }
    else
    {
      #if DEBUG
        Serial.println(" <-- mistake");
      #endif

      return false;
    }
  }
  #if DEBUG
    Serial.println("");
  #endif

  return true;
}

theBest readData(uint16_t address)
{
  theBest data;
  EEPROM.get(address, data);
  return data;
}

void writeData(uint16_t address, theBest data)
{
  EEPROM.put(address, data);
}
