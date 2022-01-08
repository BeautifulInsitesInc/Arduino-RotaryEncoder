// ButtonFever - Version: Latest 
#include <BfButton.h>
//Arduino code - Rotary Encoder w Push button

#include <BfButtonManager.h>

int btnPin=3; //GPIO #3 Push button on ecoder
int DT=4; //GPIO #4 on encoder (outbut B)
int CLK=5; //GPIO #5-CLK on encoder (Output A)
BfButton btn(BfButton::STANDALONE_DIGITAL, btnPin, true, LOW);

int counter = 0;
int angle = 0;
int aState;
int aLastState;

//Button press handling function
void pressHandler (BfButton *btn, BfButton::press_pattern_t pattern) {
  switch (pattern) {
    case BfButton::SINGLE_PRESS:
      Serial.println("Single push");
      break;
      
    case BfButton::DOUBLE_PRESS:
      Serial.println("Double Push");
      break;
    case BfButton::LONG_PRESS:
      Serial.println("Long push");
      break;
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println(angle);
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);
  aLastState = digitalRead(CLK);
  
  //Button settings
  btn.onPress(pressHandler)
  .onDoublePress(pressHandler) // default timeout)
  .onPressFor(pressHandler, 1000); // custom time out for 1 second))
}

void loop() {
  // put main code here to run repeatedly:
  
  //Wait for the button press to execute commads
  btn.read();
  
  aState = digitalRead(CLK);
  
  //Enncoder rotation tracking
  if (aState != aLastState) {
    if (digitalRead(DT) != aState) {
      counter ++;
      angle ++;
    }
    else {
      counter--;
      angle --;
    }
    if (counter >=100) {
      counter =100;
    }
    if (counter <=-100 ) {
      counter =-100;
    }
    Serial.println(counter);
  }
  aLastState = aState;
}
