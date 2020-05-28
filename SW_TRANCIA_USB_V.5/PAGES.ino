void PAGEE_VIDEO(int page)
{

  switch (page) {
    case 0 :
      
      // MIUPANEL - FIRST PAGE

      DEBUG.println(" PAGE 0");

      PANEL.print("$P:Dw!21B;{t%98,y80#05F_{m{%95,y10{T*12#FFFfb*5:IDT 16015MAC;}|>{B1%10,5r5!FFF,AAA#000^f*5:NEXT;}}");
      PANEL.print("_^{%95,y62Tfb*20#FFF:TRANCIA PORTAOGGETTI USB 330 MCA;}}}");
      PANEL.println("{%100,y20!21B,DEE{d5,0mI-11.1%27;}|>{d-5,0mI-10.0%9;}}");

      Msg = "";

      break;

    case 1 :

      // SELECT MODEL
      
      DEBUG.println(" PAGE 1 - MODEL SELECTION");

      PANEL.print("$P:Dw!21B;{t%98,y85#05F_{m{%95,y15{T*12#FFFfb*5:IDT 16015MAC;}}");
      PANEL.print("^{%95,y40Tfb#FFF:SELECT MODEL;");
      PANEL.print("_{d-2BA%20,15r5g0.15!FFF,AAA*15#FFFfb*5:BASE;|d10BB%30,15r5g0.15!FFF,AAA*15#FFFfb*5:ARMREST;}}_{%95,y40}}_");
      PANEL.println("{%100,y20!21B,DEE{d5,0mI-11.1%27;}|>{d-5,0mI-10.0%9;}}}");

      Msg = "";
      // "MODEL A" = BAP
      // "MODEL B" = BBP

      break;

    case 2 :
      
      // MODEL A
      
      if (MOD_A)
      {
        DEBUG.println(" PAGE 2 - MODEL A");

        TOT_A = READ_COUNT(TOT_A_EEPROM);
        PART_AA = READ_COUNT(PART_AA_EEPROM);

        PANEL.print("$P:Dw!21B;{t%98,y85#05F_{m{%95,y15{T*15#FFFfb*5:BASE;}|>{mI1.405%5;BR%10,5r5!FFF,AAA#000^f*5:RETURN;}}");
        PANEL.print("^{%95,y37tM1*13#FFFf-2p3b*5:LOAD PART;}");
        PANEL.print("<{T*12#FFFfb*5:TOTAL: ");
        PANEL.print(TOT_A);
        PANEL.print(";_T*12#FFFfb*5:PARTIAL: ");
        PANEL.print(PART_AA);
        PANEL.print(";}>{mI1.817%5;B2%20,5r5!FFF,AAA#000^f*5:RESET PARTIAL;}}");
        PANEL.println("{%100,y20!21B,DEE{d5,0mI-11.1%27;}|>{d-5,0mI-10.0%9;}}}");
        Msg = "";
        // "RETURN" =BRP
        // "RESET" = B2P
        // "SUBTRACT" = B1P
      }
      
      // MODEL B
      
      if (MOD_B)
      {
        DEBUG.println(" PAGE 3 - MODEL B");

        TOT_B = READ_COUNT(TOT_B_EEPROM);
        PART_BB = READ_COUNT(PART_BB_EEPROM);

        PANEL.print("$P:Dw!21B;{t%98,y85#05F_{m{%95,y15{T*15#FFFfb*5:ARMREST;}|>{mI1.405%5;BR%10,5r5!FFF,AAA#000^f*5:RETURN;}}");
        PANEL.print("^{%95,y37tM1*13#FFFf-2p3b*5:LOAD PART;}");
        PANEL.print("<{T*12#FFFfb*5:TOTAL: ");
        PANEL.print(TOT_B);
        PANEL.print(";_T*12#FFFfb*5:PARTIAL: ");
        PANEL.print(PART_BB);
        PANEL.print(";}>{mI1.817%5;B2%20,5r5!FFF,AAA#000^f*5:RESET PARTIAL;}}");
        PANEL.println("{%100,y20!21B,DEE{d5,0mI-11.1%27;}|>{d-5,0mI-10.0%9;}}}");
        Msg = "";
        // "RETURN" =BRP
        // "RESET" = B2P
        // "SUBTRACT" = B1P
      }
      break;

    case 3 :
      
      // RESTART A
     
      if (MOD_A)
      {
        PANEL.print("$P:Dw!0F0;{t%98,y80#0F0_{m{%95,y15{T*15#FFFfb*5:BASE;}}");
        PANEL.print("^{%95,y37tM1*13#FFFf-2p3b*5:REMOVE PART;}");
        PANEL.print("<{T*12#FFFfb*5:TOTAL: ");
        PANEL.print(TOT_A);
        PANEL.print(";_T*12#FFFfb*5:PARTIAL: ");
        PANEL.print(PART_AA);
        PANEL.print(";}}}");
        PANEL.println("{%100,y20!0F0,DEE{d5,0mI-11.1%27;}|>{d-5,0mI-10.0%9;}}");
        Msg = "";
      }
      
      // RESTART B
      
      if (MOD_B)
      {
        DEBUG.println(" PAGE RESTART CYCLE");
        PANEL.print("$P:Dw!0F0;{t%98,y80#0F0_{m{%95,y15{T*15#FFFfb*5:ARMREST;}}");
        PANEL.print("^{%95,y37tM1*13#FFFf-2p3b*5:REMOVE PART;}");
        PANEL.print("<{T*12#FFFfb*5:TOTAL: ");
        PANEL.print(TOT_B);
        PANEL.print(";_T*12#FFFfb*5:PARTIAL: ");
        PANEL.print(PART_BB);
        PANEL.print(";}}}");
        PANEL.println("{%100,y20!0F0,DEE{d5,0mI-11.1%27;}|>{d-5,0mI-10.0%9;}}");
        Msg = "";
      }
      break;

    // ALARM AND RESET PAGE UNTIL CYLINDER REPOSITIONING

    case (4):
      DEBUG.println(" ALARM ACTIVATED");

      PANEL.print("$P:Dw!A33;{t%98,y80#FFF");
      PANEL.print("^{//{-2p3T*10:ALARM - CYCLE INTERRUPT_FUNCTION;}/{M2*9:RESET SYSTEM <br>PRESS BY-MANUAL KEYS <br>WAIT THE CYLINDER IN UPPER POSITION;}}}");
      PANEL.println("{%100,y20!A33,C55<{d5,0mI-11.1%27;}|>{d-5,0mI-10.0%9;}}");

      break;
  }
}
