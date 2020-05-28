int READ_COUNT(int COUNT_EEPROM){
  long COUNT_1;
  byte COUNT_1short;
  long COUNT_2;
  byte COUNT_2short;
  long COUNT_3;
  byte COUNT_3short;
  long COUNT_4;
  byte COUNT_4short;
  long COUNT_recomposed;
  unsigned long COUNT;

  COUNT_1short = EEPROM.read(COUNT_EEPROM);
  COUNT_2short = EEPROM.read(COUNT_EEPROM + 1);
  COUNT_3short = EEPROM.read(COUNT_EEPROM + 2);
  COUNT_4short = EEPROM.read(COUNT_EEPROM + 3 );

  COUNT_1 = COUNT_1short;
  COUNT_1 = COUNT_1 << 24;          // MOVE 24 TO THE LEFT
 
  COUNT_2 = COUNT_2short;
  COUNT_2 = COUNT_2 << 16;          // MOVE 16 TO THE LEFT
 
  COUNT_3 = COUNT_3short;
  COUNT_3 = COUNT_3 << 8;           // MOVE 8 TO THE LEFT
  
  COUNT_4 = COUNT_4short;

  COUNT_recomposed = COUNT_1 + COUNT_2 + COUNT_3 + COUNT_4;

  COUNT = COUNT_recomposed;

  return COUNT;
}
