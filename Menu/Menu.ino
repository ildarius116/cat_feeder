
typedef enum {
  MENU_OFF,  // set LED "OFF".
  MENU_ON,   // set LED "ON"
  ACTION_LEFT, // blink LED "SLOW"
  ACTION_RIGHT,  // blink LED "FAST"
  ACTION_UP, // blink LED "SLOW"
  ACTION_DOWN,  // blink LED "FAST"
  ACTION_CONFIRM // blink LED "SLOW"
  
} 
MyActions;

int mpd;
int mpds;
boolean verflag;
boolean horflag;


MyActions nextAction = MENU_OFF; // no action when starting

#include "OneButton.h"

// Setup a new OneButton on pin A0.  
OneButton button1(A0, true);
// Setup a new OneButton on pin A1.  
OneButton button2(A1, true);
// Setup a new OneButton on pin A2.  
OneButton button3(A2, true);
// Setup a new OneButton on pin A3.  
OneButton button4(A3, true);
// Setup a new OneButton on pin A4.  
OneButton button5(A4, true);

// setup code to run once:
void setup() {

  mpd = 0;
  mpds = 0;
  verflag = 0;
  horflag = 0;
  
  // Setup the Serial port. see http://arduino.cc/en/Serial/IfSerial
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("Starting TwoButtons...");

  // link the button 1 functions.
  button1.attachClick(click1);
  button1.attachDoubleClick(doubleclick1);
  button1.attachLongPressStart(longPress1);


  // link the button 2 functions.
  button2.attachClick(click2);
  button2.attachDoubleClick(doubleclick2);


    // link the button 3 functions.
  button3.attachClick(click3);
  button3.attachDoubleClick(doubleclick3);


      // link the button 4 functions.
  button4.attachClick(click4);
  button4.attachDoubleClick(doubleclick4);


      // link the button 5 functions.
  button5.attachClick(click5);
  button5.attachDoubleClick(doubleclick5);




  // You may have to modify the next 2 lines if using another pin than A1
  PCICR |= (1 << PCIE1);    // This enables Pin Change Interrupt 1 that covers the Analog input pins or Port C.
  PCMSK1 |= (1 << PCINT9);  // This enables the interrupt for pin 1 of Port C: This is A1.
} // setup



// The Interrupt Service Routine for Pin Change Interrupt 1
// This routine will only be called on any signal change on A1: exactly where we need to check.
ISR(PCINT1_vect) {
  // keep watching the push button:
  button1.tick(); // just call tick() to check the state.
}



// main code here, to run repeatedly: 
void loop() {
  unsigned long now = millis();
  
  // keep watching the push buttons:
  button1.tick();
  button2.tick();
  button3.tick();
  button4.tick();
  button5.tick();

  // You can implement other code in here or just wait a while 
 // Serial.print(".");
  delay(10);

 // You can implement other code in here or just wait a while 

  if (nextAction == MENU_OFF) {
    // do nothing.
    digitalWrite(13, LOW);
    Serial.println("Main MENU Quit");
  }
    else if (nextAction == MENU_ON) {
    // turn LED on
    digitalWrite(13, HIGH);
    Serial.println("Main MENU");
    delay(10);

  while (nextAction == MENU_ON) {
     button1.tick();
     button2.tick();
     button3.tick();
     if (nextAction == ACTION_RIGHT) {
    Serial.println((String) "MENU: Meals per Day: "+mpd+" ");
      while (nextAction == ACTION_RIGHT) {
     button1.tick();
     button2.tick();
       if (nextAction == ACTION_CONFIRM) {
         Serial.println("Choose: Meals per Day:   ");
         Serial.println((String) "Choose: Meals per Day: "+mpd+" ");
         while (nextAction == ACTION_CONFIRM) {
         button1.tick();
         button4.tick();
         button5.tick();
             if (nextAction == ACTION_UP) {
             mpds = mpd;   
             mpds++;
             verflag = 1;
             Serial.println("Meals per Day:   ");
             Serial.println((String) "Confirm Meals per Day: "+mpds+" ?");
             delay(500);
                while (nextAction == ACTION_UP || ACTION_DOWN) {
                button1.tick();
                button4.tick();
                button5.tick();
                if (nextAction == ACTION_UP && verflag == 0) {
                mpds++;
                verflag = 1;
                Serial.println("Meals per Day:   ");
                Serial.println((String) "Confirm Meals per Day: "+mpds+" ?");
                delay(500);
                }
                if (nextAction == ACTION_DOWN && verflag == 0) {
                mpds--;
                verflag = 1;
                Serial.println("Meals per Day:   ");
                Serial.println((String) "Confirm Meals per Day: "+mpds+" ?");
                delay(500);
                }
                if (nextAction == ACTION_CONFIRM) {
                mpd = mpds;
                Serial.println((String) "Meals per Day: "+mpds+" Confirmed");
                nextAction == MENU_ON;
                }
                if (nextAction == MENU_ON) {
                mpds = mpd; 
                Serial.println((String) "Meals per Day: "+mpds+" Canceled");
                
                }
                }
             }
             if (nextAction == ACTION_DOWN) {
             mpds = mpd;   
             mpds--;
             Serial.println("Meals per Day:   ");
             Serial.println((String) "Meals per Day: "+mpds+" ");
             delay(500);
                while (nextAction == ACTION_UP || ACTION_DOWN) {
                button1.tick();
                button4.tick();
                button5.tick();
                if (nextAction == ACTION_UP && verflag == 0) {
                mpds++;
                verflag = 1;
                Serial.println("Meals per Day:   ");
                Serial.println((String) "Meals per Day: "+mpds+" ");
                delay(500);
                }
                if (nextAction == ACTION_DOWN && verflag == 0) {
                mpds--;
                verflag = 1;
                Serial.println("Meals per Day:   ");
                Serial.println((String) "Meals per Day: "+mpds+" ");
                delay(500);
                }
                if (nextAction == ACTION_CONFIRM) {
                mpd = mpds;
                Serial.println((String) "Meals per Day: "+mpds+" ");
                nextAction == MENU_ON;
                
                }
                if (nextAction == MENU_ON) {
                mpds = mpd;
                Serial.println((String) "Meals per Day: "+mpds+" ");
                
                }
                }
             }
              



              
               } 
                }
               }
     }
              
   }
  }
}






// ----- button 1 callback functions

// This function will be called when the button1 was pressed 1 time (and no 2. button press followed).
void click1() {
  Serial.println("Button 1 click.");
  nextAction = ACTION_CONFIRM;
} // click1


// This function will be called when the button1 was pressed 2 times in a short timeframe.
void doubleclick1() {
  Serial.println("Button 1 doubleclick.");
} // doubleclick1


// This function will be called once, when the button1 is pressed for a long time.
void longPress1() {
  Serial.println("Button 1 longPress");
    if (nextAction == MENU_ON)
    nextAction = MENU_OFF;
    else
    nextAction = MENU_ON;
} // longPress1


// ... and the same for button 2:

void click2() {
  Serial.println("Button 2 click.");
  nextAction = ACTION_LEFT;
} // click2


void doubleclick2() {
  Serial.println("Button 2 doubleclick.");
} // doubleclick2


// ... and the same for button 3:


void click3() {
  Serial.println("Button 3 click.");
  nextAction = ACTION_RIGHT;
} // click3


// This function will be called when the button1 was pressed 2 times in a short timeframe.
void doubleclick3() {
  Serial.println("Button 3 doubleclick.");
} // doubleclick3


// ... and the same for button 4:


void click4() {
  Serial.println("Button 4 click.");
  nextAction = ACTION_UP;
  if (verflag == 1)
    verflag = 0;
    
} // click4


void doubleclick4() {
  Serial.println("Button 4 doubleclick.");
} // doubleclick4



// ... and the same for button 5:


void click5() {
  Serial.println("Button 5 click.");
  nextAction = ACTION_DOWN;
  if (verflag == 1)
    verflag = 0;
} // click5


// This function will be called when the button1 was pressed 2 times in a short timeframe.
void doubleclick5() {
  Serial.println("Button 5 doubleclick.");
} // doubleclick5



// End

