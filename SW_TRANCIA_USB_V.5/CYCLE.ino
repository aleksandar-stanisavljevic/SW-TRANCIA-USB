void CYCLE() {
  
  DEBUG.println("IN THE CYCLE");
  
  STATE_ALARM = digitalRead (ALARM);
  DEBUG.print("STATE_ALARM = ");
  DEBUG.println(STATE_ALARM);

  delay(TIME_START);

  digitalWrite (DESTACO, 255);           // CLOSED DESTACO
  TIME_DOWNHILL_OLD = millis();
  TIME_DOWNHILL = 0;

  STATE_CIL_DESTACO = digitalRead (CIL_DESTACO);

  if (TEST_PROGRAM) {
    STATE_CIL_DESTACO = true;
  }

  while (STATE_CIL_DESTACO == false && STATE_ALARM == true && TIME_DOWNHILL <= TIME_DESTACO && START_CYCLE == true) {

    TIME_DOWNHILL = millis();
    TIME_DOWNHILL = TIME_DOWNHILL - TIME_DOWNHILL_OLD;

    STATE_CIL_DESTACO = digitalRead (CIL_DESTACO);
    STATE_ALARM = digitalRead (ALARM);
    
  }

  if (TIME_DOWNHILL >= TIME_DESTACO) {        // DESTACO PROBLEM

    PANEL.println ("#M1ANOMALY DESTACO");
    digitalWrite (DESTACO, 0);
    START_CYCLE = false;
    STATE_CIL_DESTACO = false;

    STATE_START_SX = digitalRead (START_SX);
    STATE_START_DX = digitalRead (START_DX);

    if (TEST_PROGRAM) {
      STATE_START_SX = true;
      STATE_START_DX = true;
    }

    while (STATE_START_SX == false || STATE_START_DX == false ) {         // TWO-HAND PUSH-BUTTON
      STATE_START_SX = digitalRead (START_SX);
      STATE_START_DX = digitalRead (START_DX);
    }
  }

  if (STATE_CIL_DESTACO == true) {
    DEBUG.println("DESTACO CLOSED CORRECTLY");
    PANEL.println ("#M1DESTACO OK!");
    if (TEST_PROGRAM)
      delay(1000);
  }
  
  if (STATE_ALARM == false) INTERRUPT_FUNCTION();
  
  STATE_ALARM = digitalRead (ALARM);
  DEBUG.print("STATE_ALARM AFTER DESTACO = ");
  DEBUG.println(STATE_ALARM);

  if (STATE_CIL_DESTACO == true && START_CYCLE == true && STATE_ALARM == true) {

    digitalWrite (DOWN_AIR, 255);

    TIME_DOWNHILL_OLD = millis();
    TIME_DOWNHILL = 0;

    PANEL.println ("#M1WARNING CYLINDER IN MOTION");

    if (TEST_PROGRAM)
      delay(1000);

    DEBUG.println("FIRST PART");

    STATE_CIL_DOWN = digitalRead (CIL_DOWN);

    if (TEST_PROGRAM) {
      STATE_CIL_DOWN = true;
    }

    while (STATE_CIL_DOWN == false && START_CYCLE == true && STATE_ALARM == true && TIME_DOWNHILL <= T_DOWNHILL_MAX1) {
      TIME_DOWNHILL = millis();
      TIME_DOWNHILL = TIME_DOWNHILL - TIME_DOWNHILL_OLD;
      STATE_CIL_DOWN = digitalRead (CIL_DOWN);
      STATE_ALARM = digitalRead (ALARM);

      if (TEST_PROGRAM)
        delay(1000);
    }

    if (TIME_DOWNHILL >= T_DOWNHILL_MAX1) {                // PROBLEM WITH CYLINDER
      PANEL.println ("#M1ANOMALY IN THE CYLINDER");
      digitalWrite (DOWN_AIR, 0);
      START_CYCLE = false;

      STATE_START_SX = digitalRead (START_SX);
      STATE_START_DX = digitalRead (START_DX);

      if (TEST_PROGRAM) {
        STATE_START_SX = true;
        STATE_START_DX = true;
      }

      while (STATE_START_SX == false || STATE_START_DX == false) {         // TWO-HAND PUSH-BUTTON
        STATE_START_SX = digitalRead (START_SX);
        STATE_START_DX = digitalRead (START_DX);
      }
    }
    
    if (STATE_ALARM == false) INTERRUPT_FUNCTION();

    if (STATE_CIL_DOWN == true) {
      PANEL.println ("#M1CYLINDER OK!");
      if (TEST_PROGRAM)
        delay(1000);
    }

    if (STATE_CIL_DOWN == true && START_CYCLE == true && STATE_ALARM == true) {

      digitalWrite (DOWN_OIL, 255);

      delay(T_BEFORE_UP);
      digitalWrite (DOWN_AIR, 0);  

      delay(T_DOWNHILL_OIL);

      digitalWrite (DOWN_OIL, 0);

    }

    STATE_CIL_UP = digitalRead (CIL_UP);
    TIME_CLIMB_OLD = millis();  
    TIME_CLIMB = 0;

    if (TEST_PROGRAM) {
      STATE_CIL_UP = true;
    }

    while (STATE_CIL_UP == false && START_CYCLE == true && STATE_ALARM == true && TIME_CLIMB <= T_CLIMB_MAX1) {
      TIME_CLIMB = millis();
      TIME_CLIMB = TIME_CLIMB - TIME_CLIMB_OLD;
      STATE_CIL_UP = digitalRead (CIL_UP);
      STATE_ALARM = digitalRead (ALARM);
      
      if (TEST_PROGRAM)
        delay(1000);
    }
    
    if (TIME_CLIMB >= T_CLIMB_MAX1) {                             // PROBLEM WITH CYLINDER
      PANEL.println ("#M1ANOMALY ON THE CYLINDER UP");
      START_CYCLE = false;

      STATE_START_SX = digitalRead (START_SX);
      STATE_START_DX = digitalRead (START_DX);

      if (TEST_PROGRAM) {
        STATE_START_SX = true;
        STATE_START_DX = true;
      }

      while (STATE_START_SX == false || STATE_START_DX == false ) {            // TWO-HAND PUSH-BUTTON
        STATE_START_SX = digitalRead (START_SX);
        STATE_START_DX = digitalRead (START_DX);
      }
    }
    
    if (STATE_ALARM == false) INTERRUPT_FUNCTION();

    if (STATE_CIL_UP == true && STATE_ALARM == true && START_CYCLE == true) {
      
      digitalWrite (DESTACO, 0);

      if (TEST_PROGRAM) {
        PANEL.println ("#M1PUNCHING OK");
        if (TEST_PROGRAM)
          delay(1000);
      }

      START_CYCLE = false;

      COUNTERS();  
      
      PAGEE_VIDEO(3);

      STATE_P_A = digitalRead (PART_A);   
      STATE_P_B = digitalRead (PART_B);  

      if (TEST_PROGRAM) {
        STATE_P_A = true;
        STATE_P_B = true;
        if (TEST_PROGRAM)
          delay(1000);
      }

      while (STATE_P_A == false || STATE_P_B == false) {
        STATE_P_A = digitalRead (PART_A);   
        STATE_P_B = digitalRead ( PART_B);  
        if (TEST_PROGRAM)
          delay(1000);
      }
      
      PAGEE_VIDEO(2);
    } 
  }

  if (START_CYCLE == false) {
        
    DEBUG.println("I took the START to fake");    
    digitalWrite (DOWN_AIR, 0);
    digitalWrite(DOWN_OIL, 0);
    digitalWrite (DESTACO, 0);
    
    DEBUG.print("STATE_ALARM = ");
    DEBUG.println(STATE_ALARM);
    
    delay(100);
  }
}
