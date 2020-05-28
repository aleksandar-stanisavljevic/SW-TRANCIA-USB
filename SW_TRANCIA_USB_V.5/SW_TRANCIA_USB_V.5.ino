/*
   project SIGIT - USB V5 SLICE HOLDER - 03/27/17

   order 16015

   features
   A- Short piece (1 sensor)
   B- Long piece (2 sensors)

   Automatic destaco
   Cycle start from two-hand push-button panel
   Production counters, with the possibility of decreasing by waste piece
   INTERRUPT_FUNCTIONs from safety barriers with panel process reactivation

   CAUTION!!!! THE OUTPUTS ARE CONNECTED ON ANALOG PINS, SO TO ACTIVATE THEM, YOU MUST WRITE THE VALUE 255 AND NOT "HIGH",
                 AND TO DEACTIVATE YOU WRITE 0 AND NOT "LOW" !!
 */

//------------- CONDITION FOR TESTING THE SOFTWARE ----------//

boolean TEST_PROGRAM = false; // TESTING THE OFF-LINE SOFTWARE
boolean CLEARING = false; // RESET THE EEPROM

//------------- CONDITION FOR TESTING THE SOFTWARE ----------//

#define  DEBUG  Serial         // DEBUG VIDEO ARDUINO
#define  PANEL  Serial1      // DISPLAY CONNECTED TO SERIAL 1
#include <EEPROM.h>

//------------- PANEL DATA ACQUISITION VARIABLES ------//

String Msg = "";
int c;

//------------- INPUT ALARM ------//

byte ALARM = 2;         //I0.5 

//------------- CYLINDER READING SENSORS INPUT ------//

byte CIL_UP = A0;       //I0.7
byte CIL_DOWN = 3;      //I0.6
byte CIL_DESTACO = A1;  //I0.8
byte AIR = 25;          //I0.3

//------------- PART SENSOR INPUT ------//

byte PART_A = A2; //I0.10
byte PART_B = A3; //I0.9

//------------- BIMANUAL ------//
byte START_SX = A5; //I0.12
byte START_DX = A4; //I0.11

//------------- SOLENOID VALVES OUTPUT ------//
byte DOWN_AIR = 6;    //Q0.7
byte DOWN_OIL = 5;    //Q0.6
byte DESTACO = 4;     //Q0.5
byte RESET = 40;      //Q0.4

//--------- TIMES -----------------//
int TIME_DESTACO = 1500; // TIME BEFORE CLOSING DESTACO
int TIME_START = 300; // TIME BEFORE THE PISTON STARTS
int T_DOWNHILL_MAX1 = 3000; // DESCENT TIME
int T_CLIMB_MAX1 = 4000; // CLIMBING TIME
int T_DOWNHILL_OIL = 500; // DESCENT TIME (OIL)
int TIME_RESET = 1000;
int T_BEFORE_UP = 0; // TIME BEFORE STARTING THE CYLINDER
int T_AIR = 500; // AIR TIME

//--------- PAGES -----------------//
boolean PAGE_0 = false;
boolean PAGE_1 = false;
boolean PAGE_2 = false;
boolean PAGE_3 = false;

boolean MOD_A = false;
boolean MOD_B = false;

boolean STATE_ALARM = true;

 boolean STATE_CIL_UP = false;  // LIFTED CYLINDER
 boolean STATE_CIL_DOWN = false;// END OF STROKE CYLINDER
 boolean STATE_CIL_DESTACO = false; // DESTACO CLOSED
 boolean STATE_AIR = false; // AIR PRESSURE

 boolean STATE_START_SX = false;
 boolean STATE_START_DX = false;

 boolean STATE_P_A = false;
 boolean STATE_P_B = false;

 boolean CONFORM = false;  // CONFORMING PART

boolean START_CYCLE = false; // CYCLE STARTING SIGNAL

 boolean CONDITION_CYLINDER = false; // STATE OF CYLINDER
 
 boolean STATE_PRE_CYCLE = false;

//------------- TIMES ------//

unsigned long TIME_DOWNHILL_OLD;
unsigned long TIME_CLIMB_OLD;
unsigned long TIME_DOWNHILL;
unsigned long TIME_CLIMB;

//------------- COUNTERS ------//
long TOT_A;
long TOT_B;
long PART_AA;
long PART_BB;

byte TOT_A_EEPROM = 10;
byte TOT_B_EEPROM = 20;
byte PART_AA_EEPROM = 30;
byte PART_BB_EEPROM = 40;


void setup() {

  //------------- BEGIN DEBUG ------//

  DEBUG.begin(9600);
  delay(1000);
  DEBUG.println("Showing //DEBUG");

  //------------- BEGIN PANEL ------//

  PANEL.begin(57600);
  delay(3000);
  PANEL.println("\n$PING 200");

  //------------- SETUP INPUT ----------//

  pinMode (CIL_UP, INPUT);
  pinMode (CIL_DOWN, INPUT);
  pinMode (CIL_DESTACO, INPUT);
  pinMode (AIR, INPUT);
  pinMode (PART_A, INPUT);
  pinMode (PART_B, INPUT);
  pinMode (START_SX, INPUT);
  pinMode (START_DX, INPUT);

  //------------- SETUP OUTPUT ----------//
  pinMode( DOWN_AIR, OUTPUT);
  pinMode( DOWN_OIL, OUTPUT);
  pinMode( DESTACO, OUTPUT);

  pinMode(RESET, OUTPUT);

  digitalWrite (DOWN_AIR, 0);
  digitalWrite(DOWN_AIR, 0);
  digitalWrite (DESTACO, 0);
  digitalWrite (RESET, 0);

  //------------- RESET EEPROM ----------//

  if (CLEARING) {
    TOT_A = 0;
    TOT_B = 0;
    PART_AA = 0;
    PART_BB = 0;

    WRITE_COUNT(TOT_A, TOT_A_EEPROM);
    WRITE_COUNT(TOT_B, TOT_B_EEPROM);
    WRITE_COUNT(PART_AA, PART_AA_EEPROM);
    WRITE_COUNT(PART_BB, PART_BB_EEPROM);
  }
  
  //---------------- START PANEL HOME PAGE --------//
  PAGE_0 = true;
  PAGEE_VIDEO(0);  
  
  DATA_VIDEO(0);

  PAGEE_VIDEO(1); 
}

void loop()
{
  if (PAGE_1 == true)  DATA_VIDEO(1); // PANEL DATA READING - SELECT MODEL

  if (PAGE_2 == true) {

    PRE_CYCLE();

    if (START_CYCLE == true && STATE_PRE_CYCLE == true) CYCLE();

  }
}
