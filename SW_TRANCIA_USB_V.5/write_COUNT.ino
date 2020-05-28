void WRITE_COUNT(unsigned long COUNT, int COUNT_EEPROM ){
  long COUNT_1;
  byte COUNT_1short;
  long COUNT_2;
  byte COUNT_2short;
  long COUNT_3;
  byte COUNT_3short;
  long COUNT_4;
  byte COUNT_4short;
  long COUNT_recomposed;

  COUNT_1 = COUNT >> 24;           // MOVE 24 TO THE RIGHT
  COUNT_1short = COUNT_1;           
 
  COUNT_2 = COUNT >> 16;           // MOVE 16 TO THE RIGHT
  COUNT_2short = COUNT_2;
  
  COUNT_3 = COUNT >> 8;            // MOVE 8 TO THE RIGHT
  COUNT_3short = COUNT_3;
  
  COUNT_4short = COUNT;


  EEPROM.write(COUNT_EEPROM, COUNT_1short);
  EEPROM.write(COUNT_EEPROM + 1, COUNT_2short);
  EEPROM.write(COUNT_EEPROM + 2, COUNT_3short);
  EEPROM.write(COUNT_EEPROM + 3, COUNT_4short);
}
