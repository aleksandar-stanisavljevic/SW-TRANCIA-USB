void DATA_VIDEO(int page) {

  switch (page) {
    case 0 :
      
      // MIUPANEL - FIRST PAGE
      
      while (PAGE_0) {

        Msg = "";
        delay(50);
        while ((c = PANEL.read()) > '\n') Msg += (char) c;

        if (c == '\n')
        {
          if (Msg.equals("#B1P"))  {                   // NEXT
            PAGE_0 = false;
            PAGE_1 = true;
            PAGE_2 = false;
          }
        }
      }

      break;

    case 1 :
      
      // SELECT MODEL
      
      while (PAGE_1) {
        Msg = "";
        delay(50);
        while ((c = PANEL.read()) > '\n') Msg += (char) c;

        if (c == '\n')
        {
          if (Msg.equals("#BAP"))           // MODEL A
          { PAGE_1 = false;
            PAGE_2 = true;
            MOD_A = true;
            MOD_B = false;
            PAGEE_VIDEO(2);
          }

          if (Msg.equals("#BBP"))          // MODEL B
          { PAGE_1 = false;
            PAGE_2 = true;
            MOD_A = false;
            MOD_B = true;
            PAGEE_VIDEO(2);
          }
        }
      }

      break;

    case 2 :
     
      // MODEL A/B

      Msg = "";
      delay(50);

      while ((c = PANEL.read()) > '\n') Msg += (char) c;

      if (c == '\n')
      {
        if (Msg.equals("#BRP"))            // RETURN
        { PAGEE_VIDEO(1);
          PAGE_1 = true;
          PAGE_2 = false;
          MOD_A = false;
          MOD_B = false;
        }

        if (Msg.equals("#B2P"))           // RESET COUNTER
        { if (MOD_A)
          { PART_AA = READ_COUNT(PART_AA_EEPROM);
            WRITE_COUNT(0, PART_AA_EEPROM);
          }

          if (MOD_B)
          { PART_BB = READ_COUNT(PART_BB_EEPROM);
            WRITE_COUNT(0, PART_BB_EEPROM);
          }

          CONFORM = false;
          PAGEE_VIDEO(2);
          LOAD();         
        }
      }
      break;
  }
}
