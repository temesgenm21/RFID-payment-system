#include <LiquidCrystal.h>

#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
#define CONTRAST 85

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'.', '0', '#', 'D'}
};

char data_char[10];
char data_float[10];
float data;

byte rowPins[ROWS] = {1, 2, 3, 4};
byte colPins[COLS] = {5, 6, 7, 8};

Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

LiquidCrystal lcd(15, 0, 16, 17, 18, 19);


void setup() {
  lcd.begin(16, 2);
  pinMode(0, OUTPUT);
  lcd.setCursor(0, 0);
}

void loop() {
 analogWrite(14, CONTRAST);
 
  data = keypad_input();

}



float keypad_input()
{
  static int count;
  static float data;
  char key = keypad.getKey();

  if (key) {
    if (key != '#' && key != 'A'  && key != 'B'  && key != 'C' && key != 'D' && count < 10)
    {
      data_char[count] = key;
      lcd.setCursor(count, 0);
      lcd.print(data_char[count]);
      count++;

    }
    else if (key == 'C') // clear all
    {
      lcd.clear();
      count = 0 ;
    }
    else if (key == 'B' && count != 0) // backspace
    {
      count--;
      lcd.clear();
      for (int i = 0; i < count; i++)
        lcd.print(data_char[i]);
    }
    else if ('#')  // to change char to float and return the value in float
    {

      data = atof(data_char);
//      lcd.clear();
//      lcd.setCursor(0,1);
//      dtostrf(data,7,2,data_float);  // changes float to string to display on lcd
//      lcd.print(data_float); we can use a buzzer instead as a confirmation 
      return data;
    }
//   other features 
//    else if ('A') // change to check balance mode 
//    else if ('D')  // return money mistakenly paid..... need password for confirmation 
  }
}
