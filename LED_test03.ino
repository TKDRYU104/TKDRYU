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


// 初期化
void setup() {

  // LEDのピンを出力に
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
  Serial.begin(9600);
}

void slot(int in_red, int in_blue, int in_green, LEDState &ledState){
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

   if (ledState.f_red == 0) {
    ledState.blue = ledState.blue + LED_BLUE_TIME;
    if (ledState.blue >= 200) {
      ledState.f_red = 1;
    }
  }
  else {
    ledState.blue = ledState.blue - LED_BLUE_TIME;
    if (ledState.blue <= 0) {
      ledState.f_red = 0;
    }
  }
  analogWrite(in_blue, ledState.blue);

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

// メインループ
void loop() {
  static int win_lose; 
  static int timer = 0;
  static bool leftLEDSet = false;
  static bool middleLEDSet = false;
  static bool rightLEDSet = false;
  static bool firstTime = true; 

  if(digitalRead(13) == LOW){
    if(firstTime) {
      win_lose = random(10);
      timer = millis();
      firstTime = false;
    }

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
      analogWrite(LED_L_RED,LOW);
      analogWrite(LED_L_BLUE,LOW);
      analogWrite(LED_L_GREEN,LOW);
      analogWrite(LED_M_RED,LOW);
      analogWrite(LED_M_BLUE,LOW);
      analogWrite(LED_M_GREEN,LOW);
      analogWrite(LED_R_RED,LOW);
      analogWrite(LED_R_BLUE,LOW);
      analogWrite(LED_R_GREEN,LOW);
      leftLEDSet = false; 
      middleLEDSet = false;
      rightLEDSet = false;
    }
    delay(10);
  }             
}

