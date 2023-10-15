#include <Servo.h>      // Servoライブラリの読み込み
 
Servo myservo;          // Servoオブジェクトの宣言
const int SV_PIN = 7;   // サーボモーターをデジタルピン7に
 
void setup(){
 
  myservo.attach(SV_PIN);  // サーボの割当(パルス幅500~2400msに指定)
  
}
 
void loop(){
 
  myservo.write(10);    // サーボモーターを0度の位置まで動かす
  delay(1000);
 
  myservo.write(140);   // サーボモーターを90度の位置まで動かす
  delay(1000);

}
