void PRE_CYCLE()
{

  STATE_P_A = false;
  STATE_P_B = false;

  CONFORM = false;

  START_CYCLE = false;
  CONDITION_CYLINDER = false;
  
  STATE_PRE_CYCLE = false;

  STATE_P_A = digitalRead (PART_A);   
  STATE_P_B = digitalRead (PART_B); 

  if (TEST_PROGRAM) {
    DEBUG.print("STATE A = ");
    DEBUG.println(STATE_P_A);
    DEBUG.print("STATE B = ");
    DEBUG.println(STATE_P_B);
  }

  LOAD();

  if (CONFORM == true && PAGE_2 == true) {

    while (CONDITION_CYLINDER == false && PAGE_2 == true) {

      DEBUG.println("CYLINDER CONTROL");

      STATE_CIL_UP = digitalRead (CIL_UP);
      STATE_CIL_DOWN = digitalRead (CIL_DOWN);
      STATE_CIL_DESTACO = digitalRead (CIL_DESTACO);

      if (TEST_PROGRAM) {
        // STATE_AIR = true;
        STATE_CIL_UP = true;
        STATE_CIL_DOWN = false;
        STATE_CIL_DESTACO = false;
      }
   
      if (STATE_CIL_UP == true && STATE_CIL_DOWN == false && STATE_CIL_DESTACO == false ) {

        if (TEST_PROGRAM) {
          DEBUG.println("CYLINDER RISES - DESTACO IS OPEN: WAIT FOR START");
        }

        PANEL.println ("#M1PRESS BY-MANUAL TO START");
        CONDITION_CYLINDER = true;
      } 

      else {
        PANEL.println ("#M1CYLINDER NOT IN POSITION");
  
        if (TEST_PROGRAM) {
          DEBUG.print("STATE_CIL_UP = ");
          DEBUG.println(STATE_CIL_UP);
          DEBUG.print("STATE_CIL_DOWN = ");
          DEBUG.println(STATE_CIL_DOWN);
          DEBUG.print("STATE_CIL_DESTACO = ");
          DEBUG.println(STATE_CIL_DESTACO);
        }
      }

      DATA_VIDEO(2);
    } 
    
    STATE_ALARM = digitalRead (ALARM);
    DEBUG.print("STATE ALARM = ");
    DEBUG.println(STATE_ALARM);

    while (START_CYCLE == false && PAGE_2 == true) {
    
      STATE_START_SX = digitalRead (START_SX);
      STATE_START_DX = digitalRead (START_DX);

      if (TEST_PROGRAM) {
        STATE_START_SX = false;
        STATE_START_DX = false;
      }

      if (STATE_START_SX == false && STATE_START_DX == false ) {
        delay(T_AIR);

        STATE_AIR = digitalRead (AIR);

        if (TEST_PROGRAM) {
          STATE_AIR = true;
        }

        if (STATE_AIR) {
          START_CYCLE = true;
          STATE_PRE_CYCLE = true;
        }

        if (!STATE_AIR) PANEL.println ("#M1AIR NOT OK");
      } 

      DATA_VIDEO(2);

    } 
  } 
}
