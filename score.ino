theScore readScore()
{
    theScore data;
    EEPROM.get(EEPROM_START, data);
    return data;
}

void writeScore(theScore data)
{
    EEPROM.put(EEPROM_START, data);
}

theBest readGameScore(uint8_t game_number)
{
    theScore s = readScore();
    return s.game[game_number];
}

void writeGameScore(uint8_t game_number, theBest data)
{
    theScore s = readScore();
    s.game[game_number] = data;
    writeScore(s);
}
