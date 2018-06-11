String formatMillis(unsigned long miliseconds)
{
  miliseconds = miliseconds / 1000;
  uint8_t s = miliseconds % 60;
  uint8_t m = (miliseconds / 60) % 60;
  uint8_t h = (miliseconds / 3600) % 24;

  String sh = String(h);
  if (h < 10)
  {
    sh = "0" + sh;
  }

  String sm = String(m);
  if (m < 10)
  {
    sm = "0" + sm;
  }

  String ss = String(s);
  if (s < 10)
  {
    ss = "0" + ss;
  }

  return sh + ":" + sm + ":" + ss;
}

String formatMillisWithMili(unsigned long miliseconds)
{
  unsigned int mili = miliseconds - (miliseconds / 1000 * 1000);
  miliseconds = miliseconds / 1000;
  uint8_t s = miliseconds % 60;
  uint8_t m = (miliseconds / 60) % 60;

  String sm = String(m);
  if (m < 10)
  {
    sm = "0" + sm;
  }

  String ss = String(s);
  if (s < 10)
  {
    ss = "0" + ss;
  }

  String smili = String(mili);

  return sm + ":" + ss + "," + smili;
}
