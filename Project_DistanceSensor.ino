//**Project Distance**//
//**Objectives:**//
//**1.Use Ultrasonic Sensor to Detect Distance**//
//**2.If Obstacle is within 60mm,Turn NeoPixel Strip Red**//
//**3.If Obstacle is more than 60mm, Activate Rainbow. Upon Button Press Change to individual color**//

//**Include Adafruit NeoPixel Library**//
#include <Adafruit_NeoPixel.h>

//**Define Trig and Echo Pins**//
#define echoPin 2
#define trigPin 4
#define PushButton 6

//**Define Led Pin and Number of NeoPixels**//
#define LED_PIN     7
#define LED_COUNT  8

//**Define Variables for distance and duration for Ultrasonic**//
long duration;
int distance;

//**Define Button State**//
int ButtonState;

//**Declare our NeoPixel strip object**//
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
//**Initialize Serial Monitor at a baud rate of 9600**//
  Serial.begin(9600);
//**Initialize NeoPixel strip object**//
  strip.begin(); 
//**Turn OFF All Pixels**//          
  strip.show();
//**Set Brightness to 50 due to Low Current**//              
  strip.setBrightness(200);
//**Declare Push Button as Input**//
  pinMode(PushButton,INPUT_PULLUP);   
}

void loop() {
//**Call CheckPath to get Ultrasonic Sensor Reading**//
  CheckPath();
}

void CheckPath() {
  //**Clears the trigPin condition**//
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  //**Sets the trigPin HIGH (ACTIVE) for 10 microseconds**//
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  //**Reads the echoPin, returns the sound wave travel time in microseconds**//
  duration = pulseIn(echoPin, HIGH);
  //**Calculating the distance**//
  //**Speed of sound wave divided by 2(back&forth)**//
  distance = duration * 0.034 / 2;
  //**Displays the distance on the Serial Monitor**//
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  //**If Distance is Less than equal to 2 turn neopixel red**//
    if (distance <= 6) {
      RedWarning();
    }
    if (distance > 6){
      RainbowEffect();
    }
}

void RedWarning(){
//**Set ButtonState to 0**//
  ButtonState = 0;
//**RGB(255,0,0) is RED**//  
  colorWipe(strip.Color(255,   0,   0), 0);
}

void RainbowEffect(){
//**Check For Button Pushes and Set Appropriate Color according to ButtonState**//
//**Break out of the loop if button is Pressed**//
  Serial.print(ButtonState);
  if(digitalRead(PushButton)==LOW && ButtonState==3){
    //RainbowEffect();
    ButtonState = 0;
    delay(500);
  }
  if(digitalRead(PushButton)==LOW && ButtonState==2){
    ShowYellow();
    delay(2000);
    ButtonState = ButtonState + 1;
  }
  if(digitalRead(PushButton)==LOW && ButtonState==1){
    ShowGreen();
    delay(2000);
    ButtonState = ButtonState + 1;
  }
  if(digitalRead(PushButton)==LOW && ButtonState==0){
    ShowBlue();
    delay(2000);
    ButtonState = ButtonState + 1;
  }
  if(ButtonState == 0){
    for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
      for(int i=0; i<strip.numPixels(); i++) { 
        int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
        strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
      }
      strip.show();
      delay(1);
    }
  }
}


void colorWipe(uint32_t color, int wait) {
//**Set Color of Each Pixel with assigned delay**//
  for(int i=0; i<strip.numPixels(); i++) { 
    strip.setPixelColor(i, color);         
    strip.show();                          
    delay(wait);                           
  }
}

void ShowGreen(){
  //**RGB(0,255,0) is Green**//  
  colorWipe(strip.Color(0,   255,   0), 0);
}

void ShowBlue(){
  //**RGB(0,0,255) is Blue**//  
  colorWipe(strip.Color(0,   0,   255), 0);
}

void ShowYellow(){
  //**RGB(255,255,0) is Yellow**//  
  colorWipe(strip.Color(255,   255,   0), 0);
}
