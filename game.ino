void runG1P1() // Game 1 (memory) - player 1
{
  if(resetButton())
  {
    writeScoreG1(EEPROM_G1P1_SCORE,0);

    #if DEBUG
      Serial.println("Cleared!");
    #endif
  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(LANG_CLEARED);

    delay(1000);
    return false;
  }
  uint8_t best=readScoreG1(EEPROM_G1P1_SCORE);

  #if DEBUG
    Serial.println("Memory");
    Serial.print("The best result: ");
    Serial.println(best);
  #endif

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(LANG_GAME1_NAME);
  lcd.setCursor(0,1);
  lcd.print(LANG_THE_BEST);
  lcd.print(" ");
  lcd.print(best);

  randomSeed(millis());
  uint8_t sequence[GAME_MEMORY_SEQUENCE]={0};
  for(uint8_t i=0; i<GAME_MEMORY_SEQUENCE; i++)
  {
    sequence[i]=random(0,USED_BUTTON);
  }

  int16_t round=0;
  uint8_t score=0;
  while(round>-1 && round<GAME_MEMORY_SEQUENCE)
  {
    showSequenceG1P1(sequence, round);
    if(checkSequenceG1P1(sequence, round))
    {
      round++;
      score++;

      #if DEBUG
        Serial.print("Score: ");
        Serial.print(score);
        Serial.print("/");
        Serial.println(GAME_MEMORY_SEQUENCE);
      #endif

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(LANG_GAME1_NAME);
      lcd.setCursor(0,1);
      lcd.print(LANG_SCORE);
      lcd.print(" ");
      lcd.print(score);
    }
    else
    {
      round=-1;
    }
  }
  if(score>best)
  {
    writeScoreG1(EEPROM_G1P1_SCORE,score);

    #if DEBUG
      Serial.println("Game over! You win!");
    #endif

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(LANG_GAME_OVER);
    lcd.setCursor(0,1);
    lcd.print(LANG_GAME_OVER_WIN);
  }
  else
  {
    #if DEBUG
      Serial.print("Game over! Score: ");
      Serial.println(score);
    #endif

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(LANG_GAME_OVER);
    lcd.setCursor(0,1);
    lcd.print(LANG_SCORE);
    lcd.print(" ");
    lcd.print(score);
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

uint8_t readScoreG1(uint16_t address)
{
  return EEPROM.read(address);
}

void writeScoreG1(uint16_t address, uint8_t score)
{
  return EEPROM.write(address, score);
}
