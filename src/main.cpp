/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with M5Core2 sample source code
*                          配套  M5Core2 示例源代码
* Visit the website for more information：https://docs.m5stack.com/en/core/core2
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/core/core2
*
* describe：Button example.  按键示例
* date：2021/7/21
*******************************************************************************
*/
#include <M5Core2.h>
#include <GDTouchKeyboard.h>
#include "WiFi.h"

/* After M5Core2 is started or reset
  the program in the setUp () function will be run, and this part will only be run once.
  在 M5Core2 启动或者复位后，即会开始执行setup()函数中的程序，该部分只会执行一次。 */
void setup() {
  M5.begin(); 

  // M5.Lcd.setTextColor(YELLOW);  //Set the font color to yellow.  设置字体颜色为黄色
  // M5.Lcd.setTextSize(2);  //Set the font size.  设置字体大小为2
  // M5.Lcd.setCursor(65, 10); //Move the cursor position to (x, y).  移动光标位置到 (x, y)处
  // M5.Lcd.println("Button example"); //The screen prints the formatted string and wraps the line.  输出格式化字符串并换行
  // M5.Lcd.setCursor(3, 35);
  // M5.Lcd.println("Press button B for 700ms");
  // M5.Lcd.println("to clear screen.");
  // M5.Lcd.setTextColor(RED);
  // Serial.println("We finished the setup and welcome to the main program");

  M5.Lcd.setTextColor(WHITE);  
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(65, 10);
  M5.Lcd.println("Setup Wifi");

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

}

void strengthToColour(int strength)
{
  uint16_t colour;
  strength = abs(strength);
  if (strength <= 75 ) {colour = GREEN;}
  else if (strength <= 80) {colour = YELLOW;}
  else {colour = RED;}
  M5.Lcd.setTextColor(colour); 
}


/* After the program in setup() runs, it runs the program in loop()
The loop() function is an infinite loop in which the program runs repeatedly
在setup()函数中的程序执行完后，会接着执行loop()函数中的程序
loop()函数是一个死循环，其中的程序会不断的重复运行 */
void loop() {

  Serial.println("scan start");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) {
      M5.Lcd.println("no networks found");
  } else {
      M5.Lcd.print(n);
      M5.Lcd.println(" networks found");
      for (int i = 0; i < n; ++i) {
          // Print SSID and RSSI for each network found
          strengthToColour(WiFi.RSSI(i));
          M5.Lcd.print(i + 1);
          M5.Lcd.print(": ");
          M5.Lcd.println(WiFi.SSID(i));

          Serial.print(i + 1);
          Serial.print(": ");
          Serial.println(WiFi.SSID(i));
          Serial.print(" (");
          Serial.print(WiFi.RSSI(i));
          Serial.print(")");
          Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
          
      }
  }
  delay(10000);
  Serial.println("");

  String t = GDTK.run("test:",0xefe1);
  Serial.println(t);
  delay(1000);

  
  // M5.update(); //Read the press state of the key.  读取按键 A, B, C 的状态
  // if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(1000, 200)) {
  //   M5.Lcd.print('A');
  //   Serial.println("A");
  // } else if (M5.BtnB.wasReleased() || M5.BtnB.pressedFor(1000, 200)) {
  //   M5.Lcd.print('B');
  //   Serial.println("B");
  // } else if (M5.BtnC.wasReleased() || M5.BtnC.pressedFor(1000, 200)) {
  //   M5.Lcd.print('C');
  // } else if (M5.BtnB.wasReleasefor(700)) {
  //   M5.Lcd.clear(WHITE);  // Clear the screen and set white to the background color.  清空屏幕并将白色设置为底色
  //   M5.Lcd.setCursor(0, 0);
  // }
  
}

