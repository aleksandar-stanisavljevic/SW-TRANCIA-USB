void INTERRUPT_FUNCTION() {

  DEBUG.println("-----------------");
  DEBUG.println("INTERRUPT");
  DEBUG.println("-----------------");

  digitalWrite (DOWN_AIR, 0);
  digitalWrite(DOWN_OIL, 0);

  PAGEE_VIDEO(4);

  STATE_CIL_UP = digitalRead (CIL_UP);

  while (STATE_CIL_UP == false) STATE_CIL_UP = digitalRead (CIL_UP);
  
  PANEL.println("#M2REMOVE YOUR HANDS FROM BI-MANUAL <br> AND PRESS AGAIN");

  STATE_START_SX = digitalRead (START_SX);
  STATE_START_DX = digitalRead (START_DX);

  while (STATE_START_SX == false || STATE_START_DX == false ) {          // REMOVE YOUR HANDS FROM THE BUTTONS 
    STATE_START_SX = digitalRead (START_SX);
    STATE_START_DX = digitalRead (START_DX);
  }
  
  STATE_START_SX = digitalRead (START_SX);
  STATE_START_DX = digitalRead (START_DX);

  while (STATE_START_SX == true || STATE_START_DX == true ) {            // PRESSED THE BUTTONS AGAIN
    STATE_START_SX = digitalRead (START_SX);
    STATE_START_DX = digitalRead (START_DX);
  }
    
  digitalWrite (DESTACO, 0);
 
  STATE_CIL_DESTACO = digitalRead (CIL_DESTACO);
  
  while (STATE_CIL_DESTACO == true) STATE_CIL_DESTACO = digitalRead (CIL_DESTACO);
  
  delay(500);

  PANEL.println("#M2REMOVE YOUR HANDS FROM BI-MANUAL");

  STATE_START_SX = digitalRead (START_SX);
  STATE_START_DX = digitalRead (START_DX);

  if (TEST_PROGRAM) {
    STATE_START_SX = true;
    STATE_START_DX = true;
  }

  while (STATE_START_SX == false || STATE_START_DX == false) {               // BUTTONS PRESSED
    STATE_START_SX = digitalRead (START_SX);
    STATE_START_DX = digitalRead (START_DX);
  }
  
  STATE_ALARM = true;
  
  DEBUG.print("STATE_ALARM = ");
  DEBUG.println(STATE_ALARM);

  if (STATE_ALARM==true) {
    START_CYCLE = false;
    PAGE_3 = false;
    PAGE_2 = true;
    PAGE_1 = false;

    PAGEE_VIDEO(2);
    DEBUG.print("VERIFICATION START_CYCLE = ");
    DEBUG.println(START_CYCLE);
  }
  
  DEBUG.print("STATE_ALARM = ");
  DEBUG.println(STATE_ALARM);
}
