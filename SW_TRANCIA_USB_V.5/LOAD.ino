void LOAD() {
 while (CONFORM == false && PAGE_2 == true) {

    STATE_P_A = digitalRead (PART_A);   
    STATE_P_B = digitalRead (PART_B);  

    // ------------------------ SOFTWARE TESTING -------------------
    if (TEST_PROGRAM) {
      STATE_P_A = false;
      STATE_P_B = false;
    }

    // -------------------------- MODEL A --------------------------------

    if (MOD_A) {
      if (STATE_P_A == false && STATE_P_B == true)  {        // MODEL A SELECTED AND SENSOR "A" IS ACTIVE
        PANEL.println ("#M1PART CONFORM");
        CONFORM = true;
      }

      if (STATE_P_B == false)  {                              // MODEL A SELECTED, BUT SENSOR "B" IS ACTIVE
        PANEL.println ("#M1PART NOT CONFORM");
        CONFORM = false;
      }

      if (STATE_P_A == true && STATE_P_B == true)  {          // PART NOT SET
        CONFORM = false;
      }
    }

    // -------------------------- MODEL B --------------------------------

    if (MOD_B) {
      if (STATE_P_A == true && STATE_P_B == false) {         // MODEL B SELECTED AND SENSOR "B" IS ACTIVE
        PANEL.println ("#M1PART CONFORM");
        CONFORM = true;
      }

      if (STATE_P_A == false) {                              // MODEL B SELECTED, BUT SENSOR "A" IS ACTIVE
        PANEL.println ("#M1PART NOT CONFORM");
        CONFORM = false;
      }

      if (STATE_P_A == true && STATE_P_B == true)  {         // PART NOT SET
        CONFORM = false;
      }

    }
   
    DATA_VIDEO(2);
  }
}
