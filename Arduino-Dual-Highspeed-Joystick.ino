/* 

  Arduino Dual Highspeed Joystick 
  This little code shows you how easy you can use a Pro Micro as a Dual Highspeed Joystick.
  Freely usable for all with the exception of military and other anti-social activities.
  Created 5.5.2018 by Marc-André Tragé
  
  Pinout for Arduino Pro Micro
  
  DISPALY Binding
  GND = GND
  5V  = 5V  (VCC)
  SDA = 2   (SDA)
  SCK = 3   (SCL)
    
  If you have any useful changes or improvements please let me know.
  (Not a wish (but a command)) have fun (NOW (and for the rest of your life))!

*/

#include <Keyboard.h>
#include <Mouse.h>

// OLED-Display
// #include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);


int Joystick_Button_left     =  10;
int Joystick_Button_right    =   9;
int Front_Button_left        =   5;
int Front_Button_right       =   4;
int Rear_Button_left         =  15;
int Rear_Button_right        =   8;
int Bottom_Button_left       =   7;
int Bottom_Button_right      =   6;
int Profil_Button            =  14;

int J1x, J1y, J2x, J2y;             // Joystick 1 & 2 xy-values
int Mouse_move_Delay         =  10; // Mouse move Delay 
int Mouse_speed              =   3; /* Mouse speed
                                       [1] = Slow Poke Rodriguez
                                       [3] = Normal
                                       [5] = Speedy Gonzales */

int NR_Mouse_speed_steps     =   5; // Number of profiles
int Selected_Mouse_speed     =   1; // Selected Profil value

// Button repaet or press 
bool Button_repaet_press     =   1; // 0 = Button repaet | 1 = Button press 
                          
// Button Delay a COUNTER without Delay(); AND interrupts();
int  Button_Delay            =    10; // Delay time for Button_repaet_press
bool Button_OK_Delay_ON_OFF  = false; // Used in Button_repaet_press for repeat selection and for press selection
int  Button_OK_Delay_Counter =     0; // Count value for Button_repaet_press
bool Button_01_Delay_ON_OFF  = false; // Used in Button_repaet_press for repeat selection and for press selection
int  Button_01_Delay_Counter =     0; // Count value for Button_repaet_press
bool Button_02_Delay_ON_OFF  = false; // Used in Button_repaet_press for repeat selection and for press selection
int  Button_02_Delay_Counter =     0; // Count value for Button_repaet_press
bool Button_03_Delay_ON_OFF  = false; // Used in Button_repaet_press for repeat selection and for press selection
int  Button_03_Delay_Counter =     0; // Count value for Button_repaet_press
bool Button_04_Delay_ON_OFF  = false; // Used in Button_repaet_press for repeat selection and for press selection
int  Button_04_Delay_Counter =     0; // Count value for Button_repaet_press
bool Button_05_Delay_ON_OFF  = false; // Used in Button_repaet_press for repeat selection and for press selection
int  Button_05_Delay_Counter =     0; // Count value for Button_repaet_press
bool Button_06_Delay_ON_OFF  = false; // Used in Button_repaet_press for repeat selection and for press selection
int  Button_06_Delay_Counter =     0; // Count value for Button_repaet_press
bool Button_07_Delay_ON_OFF  = false; // Used in Button_repaet_press for repeat selection and for press selection
int  Button_07_Delay_Counter =     0; // Count value for Button_repaet_press
bool Button_08_Delay_ON_OFF  = false; // Used in Button_repaet_press for repeat selection and for press selection
int  Button_08_Delay_Counter =     0; // Count value for Button_repaet_press

int Countdown_Display        = 200;   // Display Blanker Time
int Countdown_Display_CV     =   0;   // Display Blanker count value

const char profil[21][1]     = {"0",  // NAME
                                "d",  // Joystick 2 Text value X -3
                                "d",  // Joystick 2 Text value X -2
                                "d",  // Joystick 2 Text value X -1
                                "a",  // Joystick 2 Text value X +1
                                "a",  // Joystick 2 Text value X +2
                                "a",  // Joystick 2 Text value X +3
                                "s",  // Joystick 2 Text value Y +3
                                "s",  // Joystick 2 Text value Y +2
                                "s",  // Joystick 2 Text value Y +1
                                "w",  // Joystick 2 Text value Y -1
                                "w",  // Joystick 2 Text value Y -2
                                "w",  // Joystick 2 Text value Y -3
                                "1",  // Button value for Joystick_Button_left
                                "2",  // Button value for Joystick_Button_righ
                                "3",  // Button value for Front_Button_left
                                "4",  // Button value for Front_Button_right
                                "5",  // Button value for Rear_Button_left
                                "6",  // Button value for Rear_Button_right
                                "7",  // Button value for Bottom_Button_left
                                "8"}; // Button value for Bottom_Button_right
   
void setup(){
  Serial.begin(9600);
  pinMode(Joystick_Button_left,  INPUT_PULLUP);
  pinMode(Joystick_Button_right, INPUT_PULLUP);
  pinMode(Front_Button_left,     INPUT_PULLUP);
  pinMode(Front_Button_right,    INPUT_PULLUP);
  pinMode(Rear_Button_left,      INPUT_PULLUP);  
  pinMode(Rear_Button_right,     INPUT_PULLUP);
  pinMode(Bottom_Button_left,    INPUT_PULLUP);
  pinMode(Bottom_Button_right,   INPUT_PULLUP);
  pinMode(Profil_Button,         INPUT_PULLUP);
  delay(100); 
  Keyboard.begin();
  Mouse.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  delay(250);
  display.clearDisplay();
  display.display();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Mouse Speed ");
  display.setTextSize(2);
  display.println("1");
  display.display();
  delay(100);
  noInterrupts();   
}

void XY_value_J1x(int a){
  if(a >  1 && a <  10){J1x = 1;}
  if(a > 11 && a <  20){J1x = 2;}
  if(a > 21 && a <  35){J1x = 3;}
  if(a > 36 && a <  65){J1x = 4;}  // Center
  if(a > 66 && a <  80){J1x = 5;}
  if(a > 81 && a <  90){J1x = 6;}
  if(a > 91 && a < 100){J1x = 7;}
}

void XY_value_J1y(int a){
  if(a >  1 && a <  10){J1y = 1;}
  if(a > 11 && a <  20){J1y = 2;}
  if(a > 21 && a <  35){J1y = 3;}
  if(a > 36 && a <  65){J1y = 4;}  // Center
  if(a > 66 && a <  80){J1y = 5;}
  if(a > 81 && a <  90){J1y = 6;}
  if(a > 91 && a < 100){J1y = 7;}
}

void XY_value_J2x(int a){
  if(a >  1 && a <  10){J2x = 1;}
  if(a > 11 && a <  20){J2x = 2;}
  if(a > 21 && a <  35){J2x = 3;}
  if(a > 36 && a <  65){J2x = 4;}  // Center
  if(a > 66 && a <  80){J2x = 5;}
  if(a > 81 && a <  90){J2x = 6;}
  if(a > 91 && a < 100){J2x = 7;}
}

void XY_value_J2y(int a){
  if(a >  1 && a <  10){J2y = 1;}
  if(a > 11 && a <  20){J2y = 2;}
  if(a > 21 && a <  35){J2y = 3;}
  if(a > 36 && a <  65){J2y = 4;}  // Center
  if(a > 66 && a <  80){J2y = 5;}
  if(a > 81 && a <  90){J2y = 6;}
  if(a > 91 && a < 100){J2y = 7;
  }
}

void setJoy1x(int a){
  switch(a){              
    case 1:  Keyboard.press(profil[1][0]);
             break;
    case 2:  Keyboard.press(profil[2][0]);
             break;
    case 3:  Keyboard.press(profil[3][0]);
             break;
    case 4:  Keyboard.release(profil[1][0]);
             Keyboard.release(profil[2][0]);
             Keyboard.release(profil[3][0]);
             Keyboard.release(profil[4][0]);
             Keyboard.release(profil[5][0]);
             Keyboard.release(profil[6][0]);
             break;
    case 5:  Keyboard.press(profil[4][0]);
             break;
    case 6:  Keyboard.press(profil[5][0]);
             break;
    case 7:  Keyboard.press(profil[6][0]);
             break;
    default: break;
  }
}

void setJoy1y(int a){
  switch(a){
    case 1:  Keyboard.press(profil[7][0]);
             break;
    case 2:  Keyboard.press(profil[8][0]);
             break;
    case 3:  Keyboard.press(profil[9][0]);
             break;
    case 4:  Keyboard.release(profil[7][0]);
             Keyboard.release(profil[8][0]);
             Keyboard.release(profil[9][0]);
             Keyboard.release(profil[10][0]);
             Keyboard.release(profil[11][0]);
             Keyboard.release(profil[12][0]);
             break;
    case 5:  Keyboard.press(profil[10][0]);
             break;
    case 6:  Keyboard.press(profil[11][0]);
             break;
    case 7:  Keyboard.press(profil[12][0]);
             break;
    default: break;
  }
}

void setJoy2x(int a){
  int b = Mouse_speed * 2 * Selected_Mouse_speed;
  int c = Mouse_speed * 2 * Selected_Mouse_speed; 
  switch(a){
    case 1:  Mouse.move(0,-c,0);
             //delay(Mouse_move_Delay);
             break;
    case 2:  Mouse.move(0,-b,0);
             //delay(Mouse_move_Delay);
             break;
    case 3:  Mouse.move(0,-Mouse_speed,0);
             //delay(Mouse_move_Delay);
             break;
    case 4:  Mouse.move(0,0,0);
             //delay(Mouse_move_Delay);
             break;
    case 5:  Mouse.move(0,Mouse_speed,0);
             //delay(Mouse_move_Delay);
             break;
    case 6:  Mouse.move(0,b,0);
             //delay(Mouse_move_Delay);
             break;
    case 7:  Mouse.move(0,c,0);
             //delay(Mouse_move_Delay);
             break;
    default: //delay(Mouse_move_Delay);
             break;
  }
}

void setJoy2y(int a){
  int b = Mouse_speed * 2 * Selected_Mouse_speed;
  int c = Mouse_speed * 2 * Selected_Mouse_speed; 
  switch(a){
    case 1:  Mouse.move(-c,0,0);
             //delay(Mouse_move_Delay);
             break;
    case 2:  Mouse.move(-b,0,0);
             //delay(Mouse_move_Delay);
             break;
    case 3:  Mouse.move(-Mouse_speed,0,0);
             //delay(Mouse_move_Delay);
             break;
    case 4:  Mouse.move(0,0,0);
             //delay(Mouse_move_Delay);
             break;
    case 5:  Mouse.move(Mouse_speed,0,0);
             //delay(Mouse_move_Delay);
             break;
    case 6:  Mouse.move(b,0,0);
             //delay(Mouse_move_Delay);
             break;
    case 7:  Mouse.move(c,0,0);
             //delay(Mouse_move_Delay);
             break;
    default: //delay(Mouse_move_Delay);
             break;
  }
}

void loop(){
  int    Joy1_X = analogRead(A0);
  float  Joy1_X_value = (Joy1_X / 10.24) + 1;
  int    Joy1_X_value_GZ = (int)Joy1_X_value;  
  String Joy1_X_value_S = String(Joy1_X_value_GZ);
  XY_value_J1x(Joy1_X_value_S.toInt());
  Joy1_X_value_S = J1x;

  int    Joy1_Y = analogRead(A1);
  float  Joy1_Y_value = (Joy1_Y / 10.24) + 1;
  int    Joy1_Y_value_GZ = (int)Joy1_Y_value;
  String Joy1_Y_value_S = String(Joy1_Y_value_GZ);
  XY_value_J1y(Joy1_Y_value_S.toInt());
  Joy1_Y_value_S = J1y;

  int    Joy2_X = analogRead(A2);
  float  Joy2_X_value = (Joy2_X / 10.24) + 1;
  int    Joy2_X_value_GZ = (int)Joy2_X_value;
  String Joy2_X_value_S = String(Joy2_X_value_GZ);  
  XY_value_J2x(Joy2_X_value_S.toInt());
  Joy2_X_value_S = J2x;

  int    Joy2_Y = analogRead(A3);
  float  Joy2_Y_value = (Joy2_Y / 10.24) + 1;
  int    Joy2_Y_value_GZ = (int)Joy2_Y_value;
  String Joy2_Y_value_S = String(Joy2_Y_value_GZ);
  XY_value_J2y(Joy2_Y_value_S.toInt());
  Joy2_Y_value_S = J2y;

  // --- BEG - Button repaet
  if (Button_repaet_press==false){
    
    if(digitalRead(Joystick_Button_left) == LOW){
      if(Button_01_Delay_ON_OFF==false){
        Button_01_Delay_ON_OFF = true;
        Keyboard.println(profil[13][0]);
        }
      else{
        Button_01_Delay_Counter = Button_01_Delay_Counter+1;
        if(Button_01_Delay_Counter>Button_Delay){
          Button_01_Delay_Counter = 0;
          Button_01_Delay_ON_OFF  = false;
          }
        } 
      }

    if(digitalRead(Joystick_Button_right) == LOW){
      if(Button_02_Delay_ON_OFF==false){
        Button_02_Delay_ON_OFF = true;
        Keyboard.println(profil[14][0]);
        }
      else{
        Button_02_Delay_Counter = Button_02_Delay_Counter+1;
        if(Button_02_Delay_Counter>Button_Delay){
          Button_02_Delay_Counter = 0;
          Button_02_Delay_ON_OFF  = false;
          }
        } 
      }

    if(digitalRead(Front_Button_left) == LOW){
      if(Button_03_Delay_ON_OFF==false){
        Button_03_Delay_ON_OFF = true;
        Keyboard.println(profil[15][0]);
        }
      else{
        Button_03_Delay_Counter = Button_03_Delay_Counter+1;
        if(Button_03_Delay_Counter>Button_Delay){
          Button_03_Delay_Counter = 0;
          Button_03_Delay_ON_OFF  = false;
          }
        } 
      }

    if(digitalRead(Front_Button_right) == LOW){
      if(Button_04_Delay_ON_OFF==false){
        Button_04_Delay_ON_OFF = true;
        Keyboard.println(profil[16][0]);
        }
      else{
        Button_04_Delay_Counter = Button_04_Delay_Counter+1;
        if(Button_04_Delay_Counter>Button_Delay){
          Button_04_Delay_Counter = 0;
          Button_04_Delay_ON_OFF  = false;
          }
        } 
      }    

    if(digitalRead(Rear_Button_left) == LOW){
      if(Button_05_Delay_ON_OFF==false){
        Button_05_Delay_ON_OFF = true;
        Keyboard.println(profil[17][0]);
        }
      else{
        Button_05_Delay_Counter = Button_05_Delay_Counter+1;
        if(Button_05_Delay_Counter>Button_Delay){
          Button_05_Delay_Counter = 0;
          Button_05_Delay_ON_OFF  = false;
          }
        } 
      }    

    if(digitalRead(Rear_Button_right) == LOW){
      if(Button_06_Delay_ON_OFF==false){
        Button_06_Delay_ON_OFF = true;
        Keyboard.println(profil[18][0]);
        }
      else{
        Button_06_Delay_Counter = Button_06_Delay_Counter+1;
        if(Button_06_Delay_Counter>Button_Delay){
          Button_06_Delay_Counter = 0;
          Button_06_Delay_ON_OFF  = false;
          }
        } 
      }   

    if(digitalRead(Bottom_Button_left) == LOW){
      if(Button_07_Delay_ON_OFF==false){
        Button_07_Delay_ON_OFF = true;
        Keyboard.println(profil[19][0]);
        }
      else{
        Button_07_Delay_Counter = Button_07_Delay_Counter+1;
        if(Button_07_Delay_Counter>Button_Delay){
          Button_07_Delay_Counter = 0;
          Button_07_Delay_ON_OFF  = false;
          }
        } 
      }     

    if(digitalRead(Bottom_Button_right) == LOW){
      if(Button_08_Delay_ON_OFF==false){
        Button_08_Delay_ON_OFF = true;
        Keyboard.println(profil[20][0]);
        }
      else{
        Button_08_Delay_Counter = Button_08_Delay_Counter+1;
        if(Button_08_Delay_Counter>Button_Delay){
          Button_08_Delay_Counter = 0;
          Button_08_Delay_ON_OFF  = false;
          }
        } 
      }  
      
    }
  // --- END - Button repaet



  // --- BEG - Button press   
  else{
    
    if(digitalRead(Joystick_Button_left) == LOW){
      Button_01_Delay_ON_OFF=true;
      Keyboard.press(profil[13][0]);  
      }
    if(digitalRead(Joystick_Button_left) == HIGH && Button_01_Delay_ON_OFF==true){
      Button_01_Delay_ON_OFF=false;
      Keyboard.release(profil[13][0]);  
      }

    if(digitalRead(Joystick_Button_right) == LOW){
      Button_02_Delay_ON_OFF=true;
      Keyboard.press(profil[14][0]);  
      }
    if(digitalRead(Joystick_Button_right) == HIGH && Button_02_Delay_ON_OFF==true){
      Button_02_Delay_ON_OFF=false;
      Keyboard.release(profil[14][0]);  
      }

    if(digitalRead(Front_Button_left) == LOW){
      Button_03_Delay_ON_OFF=true;
      Keyboard.press(profil[15][0]);  
      }
    if(digitalRead(Front_Button_left) == HIGH && Button_03_Delay_ON_OFF==true){
      Button_03_Delay_ON_OFF=false;
      Keyboard.release(profil[15][0]);  
      }

    if(digitalRead(Front_Button_right) == LOW){
      Button_04_Delay_ON_OFF=true;
      Keyboard.press(profil[16][0]);  
      }
    if(digitalRead(Front_Button_right) == HIGH && Button_04_Delay_ON_OFF==true){
      Button_04_Delay_ON_OFF=false;
      Keyboard.release(profil[16][0]);  
      }

    if(digitalRead(Rear_Button_left) == LOW){
      Button_05_Delay_ON_OFF=true;
      Keyboard.press(profil[17][0]);  
      }
    if(digitalRead(Rear_Button_left) == HIGH && Button_05_Delay_ON_OFF==true){
      Button_05_Delay_ON_OFF=false;
      Keyboard.release(profil[17][0]);  
      }

    if(digitalRead(Rear_Button_right) == LOW){
      Button_06_Delay_ON_OFF=true;
      Keyboard.press(profil[18][0]);  
      }
    if(digitalRead(Rear_Button_right) == HIGH && Button_06_Delay_ON_OFF==true){
      Button_06_Delay_ON_OFF=false;
      Keyboard.release(profil[18][0]);  
      }

    if(digitalRead(Bottom_Button_left) == LOW){
      Button_07_Delay_ON_OFF=true;
      Keyboard.press(profil[19][0]);  
      }
    if(digitalRead(Bottom_Button_left) == HIGH && Button_07_Delay_ON_OFF==true){
      Button_07_Delay_ON_OFF=false;
      Keyboard.release(profil[19][0]);  
      }

    if(digitalRead(Bottom_Button_right) == LOW){
      Button_08_Delay_ON_OFF=true;
      Keyboard.press(profil[20][0]);  
      }
    if(digitalRead(Bottom_Button_right) == HIGH && Button_08_Delay_ON_OFF==true){
      Button_08_Delay_ON_OFF=false;
      Keyboard.release(profil[20][0]);  
      }      
    }   
  // --- END - Button press  

  // --- Menu set Mouse speed
  if(digitalRead(Profil_Button) == LOW){
    if(Button_OK_Delay_ON_OFF==false){
      Button_OK_Delay_ON_OFF = true;
        if(Selected_Mouse_speed > NR_Mouse_speed_steps-1){
         Selected_Mouse_speed=1;
         }
    else{
      Selected_Mouse_speed=Selected_Mouse_speed+1;
      }
    
    interrupts();
    display.clearDisplay();
    display.display();
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Mouse Speed ");
    display.setTextSize(2);
    display.println(Selected_Mouse_speed);
    display.display();
    delay(2500);
    if(digitalRead(Profil_Button) == LOW){return;}
      display.clearDisplay();
      display.display();
      }
    else{
      Button_OK_Delay_Counter = Button_OK_Delay_Counter+1;
      if(Button_OK_Delay_Counter>Button_Delay){
        Button_OK_Delay_Counter = 0;
        Button_OK_Delay_ON_OFF  = false;
        }
      } 
      noInterrupts();
    }
    
  // Send Joystick values
  setJoy1x(Joy1_X_value_S.toInt());
  setJoy1y(Joy1_Y_value_S.toInt());
  setJoy2x(Joy2_X_value_S.toInt());
  setJoy2y(Joy2_Y_value_S.toInt());
}
