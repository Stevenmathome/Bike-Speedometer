#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);  // initialize the LCD pins, use the pins on NANO to what the LCD guide said (pic in file folder)

volatile unsigned long lastturn;
volatile float SPEED;
volatile float DIST;
float w_length = 2.02; // give in meters (UPDATE THIS VALUE)
int epsilon = .1;
float last_speed = 0.0;
char mph[] = "MPH";
char nospd[] = "Not moving...yet!";

void setup() {
  attachInterrupt(0, sens, RISING);  // hall sensor interrupt
  pinMode(3, OUTPUT);                // D3 as power source (DOUBLE CHECK THIS IS CORRECT)
  digitalWrite(3, HIGH);             // writes the pin 3 to 5V
  pinMode(2, INPUT);                  // pin 2 is the hall sensor
  lcd.begin(16, 2);                 // LCD Columns and rows
  lcd.print("Welcome Back,");       // startup message
  lcd.setCursor(0, 1);
  lcd.print("RedBull Futurist"); 
  Serial.begin(9600); // send and receive at 9600 baud
}

void sens() {
  if (millis() - lastturn > 20) {    // simple noise cut filter (based on fact that you will not be ride your bike more than 120 km/h =)
    SPEED = w_length / ((float)(millis() - lastturn) / 1000) * 3.6 / 1.609;   // calculate speed, converts to mph
    lastturn = millis();                                              // remember time of last revolution

}
}

void loop() {

  if ((millis() - lastturn) > 4000) {       // if there is no signal more than 2 seconds  
    lcd.clear(); 
    lcd.setCursor(0, 0);                     // set cursor to top left
    lcd.print(nospd);
    
  }  else {
    lcd.clear();
    lcd.setCursor(0, 0);                     // set cursor to top left
    lcd.print(SPEED);
    lcd.setCursor(0, 4);                     // set cursor to top left
    lcd.print(mph);
    last_speed = SPEED;
    Serial.println(SPEED);
    delay(250);
    }
            
}