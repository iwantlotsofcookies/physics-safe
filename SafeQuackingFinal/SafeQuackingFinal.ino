#include <Wire.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
// bonjour 
const int rs = 35, en = 34, d4 = 33, d5 = 32, d6 = 31, d7 = 30;
const int LDRPin = A0;
const int pwmLCD = 2;
const byte ROWS = 4;
const byte COLS = 4;
int slaveAddress = 48;

Servo myServo;

bool ACompleted = false; //set to false after testing
bool BCompleted = false; //set to false after testing
bool completed = false; // set to false after testing

String code = "434";
String code2 = "221";
String code3 = "114";

const int CLK = 51;
const int DT = 52;
//  const int SW = 4


int counter = 0;
int currentStateCLK;
int lastStateCLK;
String currentDir ="";
unsigned long lastButtonPress = 0;

const int LEDPIN = 13;
  // Pin 13: Arduino has an LED connected on pin 13
  // Pin 11: Teensy 2.0 has the LED on pin 11
  // Pin  6: Teensy++ 2.0 has the LED on pin 6
  // Pin 13: Teensy 3.0 has the LED on pin 13

const int SENSORPIN = 53;
int sensorState = 0, lastState=0; // variable for reading the pushbutton status

int len;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


char keys[ROWS][COLS] = {
  {'D','C','A','B'},
  {'#','9','3','6'},
  {'0','8','2','5'},
  {'*','7','1','4'}
};
    
byte rowPins[ROWS] = {22, 29, 24, 25};
byte colPins[COLS] = {26, 27, 28, 23};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);





void resistorCubes() {
  bool Aloop = true;

  if (ACompleted) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Already Solved!");
    lcd.setCursor(0, 1);
    lcd.print("Move onto B");
    delay(3000);
  }
  
  else {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Solving:");
    lcd.setCursor(0,1);
    lcd.print("Circuit Spins");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Face numbers:");
    lcd.setCursor(0,1);
    String full = ""; // what does this do?
    
    while (Aloop) {
//      String code = "124";
      
      char key = keypad.getKey();
      if (key) {
        String keyPressed = String(key);
//        Serial.print(full);

        
        if (keyPressed == "#") {
          Serial.println(code);
          Serial.println(full);
          

          if (full == code or full == code2 or full == code3) {
            Serial.print("\nYAY");
            lcd.clear();
            lcd.print("Circuit Spins");
            lcd.setCursor(0,1);
            Wire.beginTransmission( slaveAddress ); // transmit to device #9

            Wire.write(1); // sends x

            Wire.endTransmission(); // stop transmitting
            lcd.print("Completed!");
            ACompleted = true;
            delay(3000);
            return;
          }

          else {
            lcd.clear();
            lcd.print("Wrong!");
            delay(3000);
            full = "";
            Serial.print("\n");
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Face numbers:");
            lcd.setCursor(0,1);
          }
        }
      
        else if (keyPressed == "*") {
          // String Clength = full.length() - 1;
          // full[Clength] = '\0';
          full = "";
          Serial.print("\n");
          lcd.clear();
          Aloop = false;
          return;
        }
        else {
          full += keyPressed;
//          Serial.print(keyPressed); 
//          lcd.clear();
//          lcd.print(full);
          lcd.print(keyPressed);
        }

        len = full.length();
        if (len > 5) {
          full = "";
          Serial.print("\n");
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Face numbers:");
          lcd.setCursor(0,1);
        }
      }
    }
  }
  
}

//void resistorCubesCheck2() {
//  if (ACompleted) {
//    lcd.setCursor(0, 0);
//    lcd.print("Already Solved!");
//    lcd.setCursor(0, 1);
//    lcd.print("Move onto B");
//  }
//}

void tensegrityCheck() {
  bool Bloop = true;

  if (BCompleted) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Already Solved!");
    lcd.setCursor(0, 1);
    lcd.print("Move onto A");
    delay(3000);
  }
  else {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Solving:");
    lcd.setCursor(0,1);
    lcd.print("Star Gazing");
    delay(3000);
    lcd.clear();
    lcd.print("Press # to check");
    lcd.setCursor(0,1);

    while (Bloop) {

      char key = keypad.getKey();
      
      if (key) {
        String keyPressed = String(key);
    
        // full += temp;
        // Serial.print(key); 
        // lcd.print(key);
        // Serial.print(full);
        
        int LDRStatus = analogRead(LDRPin);
        Serial.print(LDRStatus);
        if ((keyPressed == "#") && (LDRStatus <= 250)) {
          lcd.clear();
          lcd.print("Checking...");
          delay(1000);
            
            sensorState = digitalRead(SENSORPIN);
            Serial.print(sensorState);
            if (sensorState == 0) {
//              Serial.println("Unbroken");
              lcd.clear();
              lcd.print("Star Gazing");
              lcd.setCursor(0,1);
              Wire.beginTransmission( slaveAddress ); // transmit to device #9

              Wire.write(1); // sends x

              Wire.endTransmission(); // stop transmitting
              lcd.print("Completed!");
              BCompleted = true;
              delay(3000);
              return;
              
            } else{
              lcd.clear();
              lcd.print("Queen didn't");
              lcd.setCursor(0,1);
              lcd.print("reach her star");
              delay(3000);
            }
        } else if (keyPressed == "*") {
          return;
         
        } else{

            lcd.clear();
            lcd.print("Checking...");
            delay(3000);
            lcd.clear();
            lcd.print("Close the Door");
            delay(3000);
            
          }
          
          
    
        
        
        
        
      }else{
    lcd.clear();
    lcd.print("Press # to check");
    lcd.setCursor(0,1);
      }
    }
  
  }

}

void rotaryEncoder() {

//  pinMode(SW, INPUT_PULLUP);

    currentStateCLK = digitalRead(CLK);

  // If last and current state of CLK are different, then pulse occurred
  // React to only 1 state change to avoid double count
    if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){
  
      // If the DT state is different than the CLK state then
      // the encoder is rotating CCW so decrement
      Serial.println(digitalRead(DT));
      Serial.println(currentStateCLK);
      if (digitalRead(DT) != currentStateCLK) {

        counter --;
        currentDir ="CCW";
      }
//      } else {
//        // Encoder is rotating CW so increment
//        counter ++;
//        currentDir ="CW";
//      }
  
      Serial.print("Direction: ");
      Serial.print(currentDir);
      Serial.print(" | Counter: ");
      Serial.println(counter);
    }
    lastStateCLK = currentStateCLK;
    delay(1);
  if (counter > 10 or counter < -10) {

    // Remember last CLK state
    lastStateCLK = currentStateCLK;
    lcd.clear();
    lcd.print("WHOOO!");
    Wire.beginTransmission( slaveAddress ); // transmit to device #9

    Wire.write(1); // sends x

    Wire.endTransmission(); // stop transmitting
    completed = true;
    myServo.write(90);
    return;
  }
}

void reset() {
  while (completed) {

      char key = keypad.getKey();
      
      if (key) {
        String keyPressed = String(key);
        if ((keyPressed == "#")) {
          setup();
          counter = 0;
          currentDir ="";
          lastButtonPress = 0;
          ACompleted = false; 
          BCompleted = false; 
          completed = false; 
          
        }
      }
  }
}

void setup() {
// servo
  myServo.attach(50);
  myServo.write(0);
// LDR
  pinMode(LDRPin, INPUT);
//  LCD
  pinMode(pwmLCD, OUTPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  analogWrite(pwmLCD, 90);
//  IR Sensor
  // initialize the LED pin as an output:
//  pinMode(LEDPIN, OUTPUT);      
  // initialize the sensor pin as an input:
  pinMode(SENSORPIN, INPUT);     
  digitalWrite(SENSORPIN, HIGH); // turn on the pullup
  
//  rotary encoder


  pinMode(CLK,INPUT);
  pinMode(DT,INPUT);
  
  Serial.begin(9600);
  Wire.begin();
}


void loop() {
  digitalWrite(LEDPIN, LOW); 
  bool invalid = true;
  


  if (ACompleted and BCompleted and !completed) {
    lcd.clear();
    lcd.print("Uh Oh - Error:");
    lcd.setCursor(0,1);
    lcd.print("920");
    rotaryEncoder();
  } else if (completed){
    lcd.print("Finished!");
    reset();
    
  } else{
      lcd.setCursor(0, 0);
      lcd.print("A: Circuit Spins");
      lcd.setCursor(0,1);
      lcd.print("B: Star Gazing");
  }
  char key = keypad.getKey();
  if (key) {
    lcd.clear();
    String keyPressed = String(key);
    Serial.print(keyPressed);
    if (keyPressed == "A") {
      Serial.print("pressed key A");
      resistorCubes();
    }
    else if (keyPressed == "B") {
      Serial.print("pressed key B");
      tensegrityCheck(); 
    }
    else {
      lcd.clear();
      lcd.print("Press A or B");
      delay(3000);
     }
   }
}
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(0, 1);
  // print the number of seconds since reset:

  // lcd.print(LDRStatus);
  // Serial.print(LDRStatus);
  // delay(20);
  // lcd.clear();
  
  
