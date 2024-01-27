#include <Keypad.h>
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
// bonjour 
const int rs = 8, en = 7, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int LDRPin = A0;

const byte ROWS = 4;
const byte COLS = 4;

bool ACompleted = false;
bool BCompleted = false;

int len;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
    
byte rowPins[ROWS] = {22, 23, 24, 25};
byte colPins[COLS] = {26, 27, 28, 29};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void resistorCubes(){
  if (ACompleted) {
    lcd.print("Already Solved!");
    lcd.setCursor(0, 1);
    lcd.print("Move onto B");
  }
  else {
    String code = "124";
    String full;
    char key = keypad.getKey();
    if (key) {
      String temp = String(key);
  
      full += temp;
      Serial.print(key); 
      lcd.print(key);
      Serial.print(full);
      
      if (full == code) {
        Serial.print("\nYAY");
        lcd.print(" Yay!!!!!");
      }
    
      len = full.length();
      if (len > 3) {
      full = "";
      Serial.print("\n");
      lcd.clear();
      }
    }
  }
  
}

void menu() {
  bool invalid = true;
  while (invalid) {
    lcd.print("A: Spinning Cubes");
    lcd.setCursor(0,1);
    lcd.print("B: Duck Throne");
    char key = keypad.getKey();
    if (key == "A") {
      invalid == false;
      resistorCubes();
    }
    else if (key == "B") {
      invalid == false;
      
    }
    else {
      lcd.print("Press A or B");
    }
  }
}

void setup() {
  pinMode(LDRPin, INPUT);
  pinMode(9, OUTPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  
  analogWrite(9, 90);

  
}

void loop() {
  
  int LDRStatus = analogRead(LDRPin);
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(LDRStatus);
  Serial.print(LDRStatus);
  delay(20);
  lcd.clear();
  
  

}
