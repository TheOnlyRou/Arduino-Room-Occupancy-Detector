#include <LiquidCrystal.h>

#define lcd_col 20
#define lcd_row 4

LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);
int room_1;
int room_2;
int room_3;
String state;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(lcd_col,lcd_row);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Rooms");
  lcd.setCursor(0,1);
  lcd.print("Occupancy");
  delay(2000);
  lcd.clear();
  Serial.begin(38400); // Default communication rate of the Bluetooth module

}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){ // Checks whether data is comming from the serial port
  state = Serial.read(); // Reads the data from the serial port
  char * token = strtok(state.c_str(),",");
  switch((int)token[0]){
    case 1:
    room_1 = (int)token[1];
    break;
    case 2:
    room_2 = (int)token[1];
    break;
    case 3:
    room_3 = (int)token[1];
    break;
    default:
    break;
  }
  
  //------Printing On LCD----//
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Room Occupancy:");
  lcd.setCursor(0,1);
  lcd.print("Room 1 --> ");
  lcd.setCursor(13,1);
  lcd.print(room_1);
  lcd.setCursor(0,2);
  lcd.print("Room 2 --> ");
  lcd.setCursor(13,2);
  lcd.print(room_2);
  lcd.print("Room 3 --> ");
  lcd.setCursor(13,3);
  lcd.print(room_3);

  
  }
  }
