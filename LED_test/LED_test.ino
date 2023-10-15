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
}

void slot(int in_red,int in_blue,int in_green){
  if (f_red == 0) {
    red = red + LED_RED_TIME;
    if (red >= 250) {
      f_red = 1;
    }
  }
  else {
    red = red - LED_RED_TIME;
    if (red <= 0) {
      f_red = 0;
    }
  }
  analogWrite(in_red, red);
delay(5);

  if (f_blue == 0) {
    blue = blue + LED_BLUE_TIME;
    if (blue >= 200) {
      f_blue = 1;
      blue=200;
    }
  }
  else {
    blue = blue - LED_BLUE_TIME;
    if (blue <= 0) {
      f_blue = 0;
      blue=0;
    }
  }
  analogWrite(in_blue, blue);
delay(3);

  if (f_green == 0) {
    green = green + LED_GREEN_TIME;
    if (green >= 200) {
      f_green = 1;
      green=200;
    }
  }
  else {
    green = green - LED_GREEN_TIME;
    if (green <= 0) {
      f_green = 0;
            green=0;
    }
  }
  analogWrite(in_green, green);
delay(1);
}

void blackout(){
    analogWrite(LED_L_RED,LOW);
    analogWrite(LED_L_BLUE,LOW);
    analogWrite(LED_L_GREEN,LOW);
    analogWrite(LED_M_RED,LOW);
    analogWrite(LED_M_BLUE,LOW);
    analogWrite(LED_M_GREEN,LOW);
    analogWrite(LED_R_RED,LOW);
    analogWrite(LED_R_BLUE,LOW);
    analogWrite(LED_R_GREEN,LOW);
}

// メインループ
void loop() {

  randomSeed(analogRead(0));
  int win_lose = random(10); 
  int RLLR = random(250); //before 120,250
  int RLLB = random(200); //before 120,200
  int RLLG = random(200); //before 120,200

  int RLMR = random(250); //before 120,250
  int RLMB = random(200); //before 120,200
  int RLMG = random(200); //before 120,200

  int RLRR = random(250); //before 120,250
  int RLRB = random(200); //before 120,200
  int RLRG = random(200); //before 120,200



  int timer = millis();
  if(timer < 3000) slot(LED_L_RED,LED_L_BLUE,LED_L_GREEN);
  else{
    analogWrite(LED_L_RED,RLLR);
    analogWrite(LED_L_BLUE,RLLB);
    analogWrite(LED_L_GREEN,RLLG);
  }

  if(timer < 6000) slot(LED_M_RED,LED_M_BLUE,LED_M_GREEN);
  else{
    if(win_lose < 4){
      analogWrite(LED_M_RED,RLMR);
      analogWrite(LED_M_BLUE,RLMB);
      analogWrite(LED_M_GREEN,RLMG);
    }
    else{
      analogWrite(LED_M_RED,RLLR);
      analogWrite(LED_M_BLUE,RLLB);
      analogWrite(LED_M_GREEN,RLLG);
    }
  }

  if(timer < 9000) slot(LED_R_RED,LED_R_BLUE,LED_R_GREEN);
  else{
    if(win_lose < 7){
      analogWrite(LED_R_RED,RLRR);
      analogWrite(LED_R_BLUE,RLRB);
      analogWrite(LED_R_GREEN,RLRG);
    }
    else{
      analogWrite(LED_R_RED,RLLR);
      analogWrite(LED_R_BLUE,RLLB);
      analogWrite(LED_R_GREEN,RLLG);
    }
  }

  if(timer > 11000){
    blackout();
  }
}


