#include <Servo.h>      // Servoライブラリの読み込み
#define LED_L_RED 2            //赤LED 左　PIN番号
#define LED_L_BLUE 3           //青LED 左　PIN番号
#define LED_L_GREEN 4          //緑LED 左　PIN番号
#define LED_M_RED 5            //赤LED 中　PIN番号
#define LED_M_BLUE 6           //青LED 中　PIN番号
#define LED_M_GREEN 7          //緑LED 中　PIN番号
#define LED_R_RED 8            //赤LED 右　PIN番号
#define LED_R_BLUE 9           //青LED 右　PIN番号
#define LED_R_GREEN 10         //緑LED 右　PIN番号
#define LED_RED_TIME 5        //赤LED 周期
#define LED_BLUE_TIME 6       //青LED 周期
#define LED_GREEN_TIME 7      //緑LED 周期    

 
Servo openservo; // Servoオブジェクトの宣言
Servo switchservo;
const int OPEN_SV_PIN = 12;  
const int SWITCH_SV_PIN = 11;
const int DIN_PIN = 13;

int red = 0, blue = 0, green = 0;
int f_red = 0, f_blue = 0, f_green = 0;

struct LEDState { 
  int red;
  int blue;
  int green;
  int f_red;
  int f_blue;
  int f_green;
};

LEDState leftLED = {0, 0, 0, 0, 0, 0};
LEDState middleLED = {0, 0, 0, 0, 0, 0};
LEDState rightLED = {0, 0, 0, 0, 0, 0};

void setup(){
 
  openservo.attach(OPEN_SV_PIN, 500, 1250);
  switchservo.attach(SWITCH_SV_PIN);
  pinMode( DIN_PIN, INPUT_PULLUP );
  Serial.begin(9600);

  pinMode(LED_L_RED, OUTPUT);
  pinMode(LED_L_BLUE, OUTPUT);
  pinMode(LED_L_GREEN, OUTPUT);
  pinMode(LED_M_RED, OUTPUT);
  pinMode(LED_M_BLUE, OUTPUT);
  pinMode(LED_M_GREEN, OUTPUT);
  pinMode(LED_R_RED, OUTPUT);
  pinMode(LED_R_BLUE, OUTPUT);
  pinMode(LED_R_GREEN, OUTPUT);

  randomSeed(analogRead(0));
  
}

void blackout(){
    analogWrite(LED_L_RED,0);
    analogWrite(LED_L_BLUE,0);
    analogWrite(LED_L_GREEN,0);
    analogWrite(LED_M_RED,0);
    analogWrite(LED_M_BLUE,0);
    analogWrite(LED_M_GREEN,0);
    analogWrite(LED_R_RED,0);
    analogWrite(LED_R_BLUE,0);
    analogWrite(LED_R_GREEN,0);
}

void open_roof() {
  openservo.write(0); 
  Serial.println("opened");
}

void switch_on() {
  switchservo.write(140); // before 140
  delay(1000);
  

  switchservo.write(10);
  delay(1000);
  
  openservo.write(40);   
  //delay(3000);
  Serial.println("closed");

}


void slot(int in_red, int in_blue, int in_green, LEDState &ledState) {
  // RED
  if (ledState.f_red == 0) {
    ledState.red = ledState.red + LED_RED_TIME;
    if (ledState.red >= 250) {
      ledState.f_red = 1;
    }
  }
  else {
    ledState.red = ledState.red - LED_RED_TIME;
    if (ledState.red <= 0) {
      ledState.f_red = 0;
    }
  }
  analogWrite(in_red, ledState.red);

  // BLUE
  if (ledState.f_blue == 0) { 
    ledState.blue = ledState.blue + LED_BLUE_TIME;
    if (ledState.blue >= 200) {
      ledState.f_blue = 1;  
    }
  }
  else {
    ledState.blue = ledState.blue - LED_BLUE_TIME;
    if (ledState.blue <= 0) {
      ledState.f_blue = 0; 
    }
  }
  analogWrite(in_blue, ledState.blue);

  // GREEN
  if (ledState.f_green == 0) {
    ledState.green = ledState.green + LED_GREEN_TIME;
    if (ledState.green >= 200) {
      ledState.f_green = 1;
    }
  }
  else {
    ledState.green = ledState.green - LED_GREEN_TIME;
    if (ledState.green <= 0) {
      ledState.f_green = 0;
    }
  }
  analogWrite(in_green, ledState.green);
}


void loop(){
  static int win_lose; 
  static int timer;
  static bool leftLEDSet = false;
  static bool middleLEDSet = false;
  static bool rightLEDSet = false;
  static bool firstTime = true; 


  int value = digitalRead(DIN_PIN);
  if (value == 0) {
    if(firstTime) {
      win_lose = random(10); // ここで初期化
      timer = millis();
      firstTime = false;
      openservo.write(40);
      switchservo.write(10);
    }

    //Serial.print(win_lose);
    Serial.println("");
    // デバッグ用。モータの角度取得
    Serial.print(openservo.read());
    Serial.println("");
    Serial.println(millis() - timer);
    Serial.println("");

    // ここで屋根を開ける動作
    open_roof();

    // 各LEDの動作
    if(millis() - timer < 3000) {
      slot(LED_L_RED,LED_L_BLUE,LED_L_GREEN, leftLED);
    }
    else if(!leftLEDSet){
      analogWrite(LED_L_RED,0);
      analogWrite(LED_L_BLUE,0);
      analogWrite(LED_L_GREEN,200);
      leftLEDSet = true;
    }

    if(millis() - timer < 6000) {
      slot(LED_M_RED,LED_M_BLUE,LED_M_GREEN, middleLED);
    }
    else if (!middleLEDSet) {
      if(win_lose < 4) {
        analogWrite(LED_M_RED,250);
        analogWrite(LED_M_BLUE,0);
        analogWrite(LED_M_GREEN,0);
      }
      else {
        analogWrite(LED_M_RED,0);
        analogWrite(LED_M_BLUE,0);
        analogWrite(LED_M_GREEN,200);
      }
      middleLEDSet = true;
    }

    if(millis() - timer < 9000) {
      slot(LED_R_RED,LED_R_BLUE,LED_R_GREEN, rightLED);
    }
    else if (!rightLEDSet) {
      if(win_lose < 7) {
        analogWrite(LED_R_RED,250);
        analogWrite(LED_R_BLUE,0);
        analogWrite(LED_R_GREEN,0);
      }
      else {
        analogWrite(LED_R_RED,0);
        analogWrite(LED_R_BLUE,0);
        analogWrite(LED_R_GREEN,200);
      }
      rightLEDSet = true;
    }

    if(millis() - timer > 11000){
      switch_on();
      blackout();
      firstTime = true; 
      leftLEDSet = false; 
      middleLEDSet = false;
      rightLEDSet = false;
    }
  }
  
}

