
typedef enum {
  MENU_OFF,  // set LED "OFF".
  MENU_ON,   // set LED "ON"
  ACTION_NONE,
  ACTION_LEFT, // blink LED "SLOW"
  ACTION_RIGHT,  // blink LED "FAST"
  ACTION_UP, // blink LED "SLOW"
  ACTION_DOWN,  // blink LED "FAST"
  ACTION_MENU // blink LED "SLOW"
  
} MyActions;

int mpd;
int mpds;
boolean verflag;
boolean horflag;

int numMenu = 0;
int countMenu = 3;
int dataMenu[3];

MyActions currentAction = MENU_OFF; // no action when starting
MyActions buttonAction = ACTION_NONE;

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

// setup code here, to run once:
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

  
  
  if (currentAction == MENU_OFF) {
    // Проверяем нажата ли кнопка меню
    if (buttonAction == ACTION_MENU) {
      //обнулили кнопку
      buttonAction = ACTION_NONE;
      //состояние переводим в меню пункт один
      currentAction = MENU_ON;
      numMenu = 0;
      
      //ввыводит надпись что мы в меню
      digitalWrite(13, HIGH);
      Serial.println("Main MENU");
      
      printMenuStatus();      
    }
    
  }
  else { 
    // Проверяем нажата ли кнопка меню
    if (buttonAction == ACTION_MENU) {
      //обнулили кнопку
      buttonAction = ACTION_NONE;
      //состояние переводим в меню пункт один
      currentAction = MENU_OFF;
      //ввыводит надпись что мы в меню
      digitalWrite(13, LOW);
      Serial.println("Main MENU Quit");     
    }
        
    if (buttonAction == ACTION_LEFT) {      
      //обнулили кнопку
      buttonAction = ACTION_NONE;
      //переключили указатель меню
      numMenu--;
      if (numMenu < 0) numMenu = 2;
      printMenuStatus();
    }

    if (buttonAction == ACTION_RIGHT) {
      buttonAction = ACTION_NONE;
      //переключили указатель меню
      numMenu++;
      if (numMenu > 2) numMenu = 0;
      printMenuStatus();
    }

    if (buttonAction == ACTION_UP) {
      buttonAction = ACTION_NONE;
      dataMenu[numMenu]++;
      printValueStatus();
    }

    if (buttonAction == ACTION_DOWN) {
      buttonAction = ACTION_NONE;
      dataMenu[numMenu]--;
      printValueStatus();
    }
    
  }
  
  
  // для антидребезга
  delay(10);


}


void printMenuStatus() {
  Serial.println((String) "Menu number: " + (numMenu + 1) + " ");
  if (numMenu == 0) {
    Serial.println((String) "Hyeta pervaya !!!!");
  }
  if (numMenu == 1) {
    Serial.println((String) "Pizda vtoraya !!!!");
  }
  if (numMenu == 2) {
    Serial.println((String) "Hren tretiy !!!!");
  }
  printValueStatus();
}

void printValueStatus() {
  Serial.println((String) "Value - " + dataMenu[numMenu]);
}



// ----- button 1 callback functions

// This function will be called when the button1 was pressed 1 time (and no 2. button press followed).
void click1() {
  Serial.println("Button 1 click."); 
  
} // click1


// This function will be called when the button1 was pressed 2 times in a short timeframe.
void doubleclick1() {
  Serial.println("Button 1 doubleclick.");
} // doubleclick1


// This function will be called once, when the button1 is pressed for a long time.
void longPress1() {
  Serial.println("Button 1 longPress");
  buttonAction = ACTION_MENU;
} // longPress1


// ... and the same for button 2:

void click2() {
  Serial.println("Button 2 click.");
  buttonAction = ACTION_LEFT;
} // click2


void doubleclick2() {
  Serial.println("Button 2 doubleclick.");
} // doubleclick2


// ... and the same for button 3:


void click3() {
  Serial.println("Button 3 click.");
  buttonAction = ACTION_RIGHT;
} // click3


// This function will be called when the button1 was pressed 2 times in a short timeframe.
void doubleclick3() {
  Serial.println("Button 3 doubleclick.");
} // doubleclick3


// ... and the same for button 4:


void click4() {
  Serial.println("Button 4 click.");
  buttonAction = ACTION_UP;
  
} // click4


void doubleclick4() {
  Serial.println("Button 4 doubleclick.");
} // doubleclick4



// ... and the same for button 5:


void click5() {
  Serial.println("Button 5 click.");
  buttonAction = ACTION_DOWN;
  
} // click5


// This function will be called when the button1 was pressed 2 times in a short timeframe.
void doubleclick5() {
  Serial.println("Button 5 doubleclick.");
} // doubleclick5



// End

