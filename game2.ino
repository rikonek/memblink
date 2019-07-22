bool runG2() // Game 2 (reflex) - player 1
{
    if (resetButton())
    {
        theBest data;
        data.time=0b11111111111111111111111111111111;
        clearGameScore(NO_GAME_2, data);
        return false;
    }

    theBest best = readGameScore(NO_GAME_2);

#if DEBUG
    Serial.println("Reflex");
    Serial.print("The best time: ");
    Serial.print(formatMillisWithMili(best.time));
    Serial.print(", player: ");
    Serial.println(best.player);
#endif

    lcd.clear();
    lcd.setCursor(LANG_GAME2_NAME_PADDING, 0);
    lcd.print(LANG_GAME2_NAME);
    lcd.setCursor(LANG_THE_BEST_TIME_PADDING, 2);
    lcd.print(LANG_THE_BEST_TIME);
    lcd.print(": ");
    lcd.print(formatMillisWithMili(best.time));
    lcd.setCursor(LANG_THE_BEST_PLAYER_PADDING, 3);
    lcd.print(LANG_THE_BEST_PLAYER);
    lcd.print(": ");
    lcd.print(best.player);

    allLedOff();
    randomSeed(millis());
    unsigned long time_sum = 0;
    unsigned long time_start = 0;
    unsigned long time_stop = 0;
    uint8_t sequence;
    int8_t user = -1;
    for (uint8_t i = 0; i < GAME_REFLEX_SEQUENCE; i++)
    {
        sequence = random(0, USED_BUTTON);
        ledOn(sequence);
        time_start = millis();
        while (user != sequence)
        {
            user = readButton();
        }
        time_stop = millis();
        time_sum = time_sum + time_stop - time_start;
        ledOff(sequence);

#if DEBUG
        Serial.print(i+1);
        Serial.print(". ");
        Serial.println(formatMillisWithMili(time_stop - time_start));
#endif

        lcd.clear();
        lcd.setCursor(LANG_GAME2_NAME_PADDING, 0);
        lcd.print(LANG_GAME2_NAME);
        lcd.setCursor(LANG_SCORE_TIME_PADDING, 3);
        lcd.print(LANG_SCORE_TIME);
        lcd.print(": ");
        lcd.print(formatMillisWithMili(time_stop - time_start));

        if ((i + 1) < GAME_REFLEX_SEQUENCE)
        {
            delay(random(500, 5000));
        }
    }
    time_sum = time_sum / GAME_REFLEX_SEQUENCE;

    if (time_sum < best.time)
    {
#if DEBUG
        Serial.print("Game over! You win! Your time: ");
        Serial.println(formatMillisWithMili(time_sum));
#endif

        lcd.clear();
        lcd.setCursor(LANG_GAME_OVER_PADDING, 0);
        lcd.print(LANG_GAME_OVER);
        lcd.setCursor(LANG_GAME_OVER_WIN_PADDING, 2);
        lcd.print(LANG_GAME_OVER_WIN);

        theBest data;
        data.score = 0;
        data.time = time_sum;
        writeGameScore(NO_GAME_2, data);
        allLedBlink(3, 400);
        delay(4200);
        getPlayerName(data.player);
        writeGameScore(NO_GAME_2, data);
    }
    else
    {
#if DEBUG
        Serial.print("Game over! Time: ");
        Serial.println(formatMillisWithMili(time_sum));
#endif

        lcd.clear();
        lcd.setCursor(LANG_GAME_OVER_PADDING, 0);
        lcd.print(LANG_GAME_OVER);
        lcd.setCursor(LANG_SCORE_TIME_PADDING, 3);
        lcd.print(LANG_SCORE_TIME);
        lcd.print(": ");
        lcd.print(formatMillisWithMili(time_sum));
        allLedBlink(2, 100);
        delay(4800);
    }
}
