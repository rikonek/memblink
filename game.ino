void runG1P1()
{
  Serial.println("Start G1P1");

  uint8_t best=readScoreG1(EEPROM_G1P1_SCORE);
  Serial.print("The best: ");
  Serial.println(best);

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
    }
    else
    {
      round=-1;
      Serial.println("Game over!");
    }
  }
  Serial.print("Your score: ");
  Serial.println(score);
  if(score>best)
  {
    Serial.println("You win!");
    writeScoreG1(EEPROM_G1P1_SCORE,score);
  }
}

void showSequenceG1P1(const uint8_t *sequence, int16_t round)
{
  Serial.print("G1P1 - Show sequence: ");
  allLedOff();
  for(uint8_t i=0; i<(round+1); i++)
  {
    Serial.print(sequence[i]+1);
    ledOn(sequence[i]);
    delay(500);
    ledOff(sequence[i]);
    delay(500);
  }
  Serial.println("");
}

bool checkSequenceG1P1(const uint8_t *sequence, int16_t round)
{
  Serial.print("G1P1 - Check sequence: ");
  uint8_t position=0;
  int8_t user=-1;
  for(uint8_t i=0; i<round+1; i++)
  {
    user=readButton();
    Serial.print(user+1);
    if(user==sequence[i])
    {
      user=-1;
    }
    else
    {
      Serial.println(" mistake");
      return false;
    }
  }
  Serial.println("");
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
