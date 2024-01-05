#include <Keypad.h>
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 8, en = 7, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const byte ROWS = 3;
const byte COLS = 3;
String str1 = "124";
String str3;
int len;

char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'}
};
    
byte rowPins[ROWS] = {22, 23, 24};
byte colPins[COLS] = {25, 26, 27};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  pinMode(9, OUTPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
  analogWrite(9, 90);

  
}

void loop() {
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  //lcd.print(millis() / 1000);
  
  char key = keypad.getKey();

  if (key) {
    String str2 = String(key);

    str3 += str2;
    Serial.print(key); 
    lcd.print(key);
    //Serial.print(str3);
    
    if (str3 == str1) {
      Serial.print("\nYAY");
      lcd.print(" Yay");
      //servo_A1.attach(A1, 500, 2500);
      //servo_A0.write(90);
      //servo_A1.write(90);
      delay(10);
    }
  
    len = str3.length();
    if (len > 3) {
    str3 = "";
    Serial.print("\n");
    lcd.clear();
    }
 }
}
