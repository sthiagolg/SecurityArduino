/*4x4 Matrix Keypad connected to Arduino
This code prints the key pressed on the keypad to the serial port*/

#include <Keypad.h>
#include <LiquidCrystal.h>

const byte numRows= 4; //number of rows on the keypad
const byte numCols= 4; //number of columns on the keypad

LiquidCrystal lcd(35, 33, 31, 29, 27, 25);

//keymap defines the key pressed according to the row and columns just as appears on the keypad
char keymap[numRows][numCols]= 
{
{'1', '2', '3', 'A'}, 
{'4', '5', '6', 'B'}, 
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};

//Code that shows the the keypad connections to the arduino terminals
byte rowPins[numRows] = {53,51,49,47}; //Rows 0 to 3
byte colPins[numCols]= {45,43,41,39}; //Columns 0 to 3

//initializes an instance of the Keypad class
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

int pirPin = 30; // Input for HC-S501

int pirValue; // Place to store read PIR Value

void(* resetFunc) (void) = 0; 

int validPass = 0;

char password[4] = {'2','3','3','3'};
char testPassword[4] = {'0','0','0','0'};

int index = 0;

int moving = 0;

int timeFlag = 0;

unsigned int startTime;
unsigned int finalTime;

int totalTime = 5000;

int alarm = 0;

int buzzer = 12;

void setup()
{
  //digitalWrite(resetPin, HIGH);
Serial.begin(9600);
lcd.begin(16, 2);
 
 pinMode(buzzer,OUTPUT);
 pinMode(pirPin, INPUT);
 Serial.print("Inicialisando...");
 //Serial.print(password[3]);
 delay(5000);
 lcd.print("  Alarm is ON");
}

//If key is pressed, this key is stored in 'keypressed' variable
//If key is not equal to 'NO_KEY', then this key is printed out
//if count=17, then count is reset back to 0 (this means no key is pressed during the whole keypad scan process
void loop()
{
  
 pirValue = digitalRead(pirPin);
 if (pirValue){
  moving=1;
  }
 
char keypressed = myKeypad.getKey();

startTime = millis();

while (!validPass && moving xor timeFlag or alarm){

  if (index==0){
      lcd.setCursor(0, 0); 
      lcd.print(" Password: ____ ");
      }
  if (index==1){
      lcd.setCursor(0, 0); 
      lcd.print(" Password: *___ ");
      }
  if (index==2){
      lcd.setCursor(0, 0); 
      lcd.print(" Password: **__ ");
      }
   if (index==3){
      lcd.setCursor(0, 0); 
      lcd.print(" Password: ***_ ");
      }
  if (index==4){
      lcd.setCursor(0, 0); 
      lcd.print(" Password: **** ");
      }

  finalTime = millis();

  if (!timeFlag){
  Serial.println( String((totalTime-(finalTime - startTime))/1000)+" seconds");
  lcd.setCursor(1, 4);

  
  lcd.print("  "+String((totalTime-(finalTime - startTime))/1000)+" seconds");
  }else{
    lcd.setCursor(1, 4);
    lcd.print("Atention!!! ");
    }

   
  if (finalTime - startTime> totalTime){
    Serial.println("time's over");
    timeFlag = 1;
    alarm = 1;
    }

    
  
  keypressed = myKeypad.getKey();
  //password.append(keypressed);
  if (keypressed){

    

    testPassword[index]=keypressed;
    index++;

    if(keypressed=='C'){
      index=0;
      }

    if (index==4){
      index=0;
      if(testPassword[0]==password[0]&&
      testPassword[1]==password[1]&&
      testPassword[2]==password[2]&&
      testPassword[3]==password[3]){
      Serial.println( "Good password!!!");
      validPass = 1;
      alarm = 0;
      lcd.setCursor(0, 0);
        lcd.print("     Alarm         ");
      lcd.setCursor(1, 4);
        lcd.print(" Deactivated");
      }else{
        
        Serial.println( "Bad password :(");
        }
    
    //validPass = 1;
    
      } 
    Serial.println("index:"+ String(index));
    Serial.println( keypressed);
    }
    if(alarm){
      Serial.println( "alarm is ringing inside!!");
      digitalWrite(buzzer,HIGH);
      
      }else{
        digitalWrite(buzzer,LOW);
        }

      
    
  }

if(alarm){
      Serial.println( "alarm is ringing!!");
      digitalWrite(buzzer,HIGH);
      }

if(keypressed=='D'){
  resetFunc();
}
//Serial.println("Nothing happens");

}
