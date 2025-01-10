#include <Time.h>
#include <TimeLib.h>



/*
  DS3231: Real-Time Clock. Simple example
  Read more: www.jarzebski.pl/arduino/komponenty/zegar-czasu-rzeczywistego-rtc-ds3231.html
  GIT: https://github.com/jarzebski/Arduino-DS3231
  Web: http://www.jarzebski.pl
  (c) 2014 by Korneliusz Jarzebski
*/

#include <Wire.h>
#include <DS3231.h>


DS3231 clock;
RTCDateTime dt;

//www.RobotLinking.com
//2015.5.7
// include the library code:
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

int led = 6;
int led2 = 7;
int butt_flag;
unsigned long last_press;
int mpd = 1;
int x = 0;
int H = 0;

int portion = 0;

void setup(){
  
  // Initialize DS3231
  Serial.println("Initialize DS3231");
  clock.begin();

  // Set sketch compiling time
  clock.setDateTime(__DATE__, __TIME__);



  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  lcd.clear();

  
  Serial.begin(9600);
  pinMode(7, INPUT_PULLUP);                                 // Конфигурируем вывод к которому подключён датчик, как вход
 // attachInterrupt(1, interrupt1, FALLING); 
//  attachInterrupt(1, interrupt2, RISING);

  butt_flag = 0;

  pinMode(led, OUTPUT); 
  digitalWrite(led, LOW);

  pinMode(led2, OUTPUT); 
  digitalWrite(led2, LOW);

  // Disarm alarms and clear alarms for this example, because alarms is battery backed.
  // Under normal conditions, the settings should be reset after power and restart microcontroller.
  clock.armAlarm1(false);
  clock.armAlarm2(false);

  clock.clearAlarm1();
  clock.clearAlarm2();

 
  // Manual (Year, Month, Day, Hour, Minute, Second)
  clock.setDateTime(2017, 1, 28, 5, 59, 50);
  //setTime(5,59,55,11,2,2018);
  time_t t = now();
  setTime(t);

  // Set Alarm - Every second.
  // DS3231_EVERY_SECOND is available only on Alarm1.
  // setAlarm1(Date or Day, Hour, Minute, Second, Mode, Armed = true)
  // clock.setAlarm1(0, 0, 0, 0, DS3231_EVERY_SECOND);

  // Set Alarm - Every full minute.
  // DS3231_EVERY_MINUTE is available only on Alarm2.
  // setAlarm2(Date or Day, Hour, Minute, Second, Mode, Armed = true)
  //clock.setAlarm2(0, 0, 0, 59, DS3231_MATCH_S);
  
  // Set Alarm1 - Every 20s in each minute
  // setAlarm1(Date or Day, Hour, Minute, Second, Mode, Armed = true)
  //clock.setAlarm1(0, 0, 0, 30, DS3231_MATCH_S, false);

  // Set Alarm2 - Every 01m in each hour
  // setAlarm2(Date or Day, Hour, Minute, Mode, Armed = true)
  //clock.setAlarm2(0, 0, 1, 0, DS3231_MATCH_M);

  // Set Alarm - Every 01m:25s in each hour
  // setAlarm1(Date or Day, Hour, Minute, Second, Mode, Armed = true)
   //clock.setAlarm1(0, 0, 55, 59, DS3231_MATCH_M_S);

  // Set Alarm - Every 01h:10m:30s in each day
  // setAlarm1(Date or Day, Hour, Minute, Second, Mode, Armed = true)
   clock.setAlarm1(0, 6, 0, 0, DS3231_MATCH_H_M_S);
  // clock.setAlarm2(0, 18, 0, 0, DS3231_MATCH_H_M_S);

     // Set Alarm - Every 01h:10m:30s in each day
  // setAlarm1(Date or Day, Hour, Minute, Second, Mode, Armed = true)
  // clock.setAlarm1(0, 12, 0, 0, DS3231_MATCH_H_M_S);

  // Set Alarm - 07h:00m:00s in 25th day in month
  // setAlarm1(Date or Day, Hour, Minute, Second, Mode, Armed = true)
  // clock.setAlarm1(25, 7, 0, 0, DS3231_MATCH_DT_H_M_S);

  // Set Alarm - 10h:45m:30s in every Friday (1 - Mon, 7 - Sun)
  // setAlarm1(Date or Day, Hour, Minute, Second, Mode, Armed = true)
  // clock.setAlarm1(5, 10, 40, 30, DS3231_MATCH_DY_H_M_S);
  
  // Check alarm settings
 /*   if (mpd == 1){
  x = 0;
  clock.setAlarm1(0, 6, 0, 0, DS3231_MATCH_H_M_S);
  }
else if (mpd == 2){
   x = 12;
  clock.setAlarm1(0, 6, 0, 0, DS3231_MATCH_H_M_S);
  clock.setAlarm2(0, 18, 0, 0, DS3231_MATCH_H_M_S);
}
else if (mpd == 3){
  x = 8;
  clock.setAlarm1(0, 6, 0, 0, DS3231_MATCH_H_M_S);
  clock.setAlarm2(0, 14, 0, 0, DS3231_MATCH_H_M_S);
  clock.setAlarm3(0, 22, 0, 0, DS3231_MATCH_H_M_S);
}
else if (mpd == 4){
  x = 6;
  clock.setAlarm1(0, 6, 0, 0, DS3231_MATCH_H_M_S);
  clock.setAlarm2(0, 12, 0, 0, DS3231_MATCH_H_M_S);
  clock.setAlarm3(0, 18, 0, 0, DS3231_MATCH_H_M_S);
  clock.setAlarm4(0, 0, 0, 0, DS3231_MATCH_H_M_S);
}
else if (mpd == 6){
  x = 4;
  clock.setAlarm1(0, 0, 0, 0, DS3231_MATCH_H_M_S);
  clock.setAlarm2(0, 4, 0, 0, DS3231_MATCH_H_M_S);
  clock.setAlarm3(0, 8, 0, 0, DS3231_MATCH_H_M_S);
  clock.setAlarm4(0, 12, 0, 0, DS3231_MATCH_H_M_S);
  clock.setAlarm5(0, 16, 0, 0, DS3231_MATCH_H_M_S);
  clock.setAlarm6(0, 18, 0, 0, DS3231_MATCH_H_M_S);
}
*/
  checkAlarms();
}


void checkAlarms()
{
  RTCAlarmTime a1;  

}

void loop(){
  
  int butt = digitalRead(0);
  int butt2 = 0;
  int portion = 2;
  dt = clock.getDateTime();

 // Serial.println(clock.dateFormat("d-m-Y H:i:s - l", dt));

  lcd.setCursor(0, 0); // set the cursor to column 15, line 0
  lcd.print("Data: ");// Print a message of "Temp: "to the LCD.
  lcd.print(clock.dateFormat("d.m.y",  dt));
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1); // set the cursor to column 15, line 1
  lcd.print("Time: ");
  lcd.print(clock.dateFormat("H:i:s",  dt));
  
  // Call isAlarm1(false) if you want clear alarm1 flag manualy by clearAlarm1();
  if (clock.isAlarm1())
  {
    lcd.clear();
  lcd.setCursor(0, 0); // set the cursor to column 15, line 0
  lcd.print("     Alarm:    ");// Print a message of "Temp: "to the LCD.
  lcd.setCursor(0, 1); // set the cursor to column 15, line 0


 //write(Uint8ToBcd(dt.Hour()))
uint8_t H = clock.dateFormat("H",  dt);
// if (clock.dateFormat("H",  dt) == 6) {
 lcd.print("  H:");
 lcd.print(H);
 lcd.print("  FUCK");
   while( portion > 0) {
    butt2 = 1;
    
    if( butt2 == 1 && butt_flag == 0) {
    butt_flag = 1;
    digitalWrite(led, HIGH);
    digitalWrite(led2, HIGH);
    Serial.println("RUN");
    Serial.println((String) "BUTTON= "+butt+" ");
    Serial.println((String) "FLAG= "+butt_flag+" ");
    delay(1000);
    }
   
    if( butt == 0 && butt_flag == 1) {
    Serial.println("RUN");
    Serial.println((String) "BUTTON= "+butt+" ");
    Serial.println((String) "FLAG= "+butt_flag+" ");
    delay(100);
          while (butt < 1){
      butt = digitalRead(0);
          }
    }
  
     if( butt == 1 && butt_flag == 1) {
    butt_flag = 0;
    Serial.println("RUN");
    Serial.println((String) "BUTTON= "+butt+" ");
    Serial.println((String) "FLAG= "+butt_flag+" ");
    delay(100);
          while (butt > 0){
      butt = digitalRead(0);
          }
     }
     
       if( butt == 0 && butt_flag == 0) {
      Serial.println("STOP");
      Serial.println((String) "BUTTON= "+butt+" ");
      Serial.println((String) "FLAG= "+butt_flag+" ");
      digitalWrite(led, LOW);
      digitalWrite(led2, LOW);
      delay(100);
       }



  
  portion = portion - 1;
  butt2 = 1;
   }
   delay(5000);
  lcd.clear();
   }

 
 // }

   dt = clock.getDateTime();

  // For leading zero look to DS3231_dateformat example


  delay(1000);
  
}

void portionperday(){


}

