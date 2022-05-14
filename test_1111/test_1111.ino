#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();

#include <Wire.h>
#include <VL53L0X.h>
VL53L0X sensor;

#include"TFT_A.h" //จอภาพ

long elapsedTime = 0;
long nowTime = 0;

void setup() {
  Serial.begin(9600);
  tft.init();         //สั่งให้หน้าจอเริ่มทำงาน
  tft.setRotation(1); // หมุนหน้าจอ
  TFT_AA();//แสดงจอ
  
  Wire.begin();
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor.startContinuous();




  
}
/************************************setup**************************************************/
void loop() 
{tft.fillRect(0, 85, 480, 95, tft.color24to16(0xFFFFFF));//ปิดข้อความกลาง

 elapsedTime = millis();  //ใช้หน่วงเวลา
  //เริ่ม
  
  
  
  if (elapsedTime - nowTime > 1000) //ใช้หน่วงเวลา
  {//เริ่ม


    
  Serial.print(sensor.readRangeContinuousMillimeters());
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  Serial.println();
  tft.fillRect(200, 50, 80, 20, tft.color24to16(0x6699FF));
  tft.setTextColor(tft.color24to16(0xFF0066));//สีข้อความ
  tft.setTextSize(2.5);//ขนาดข้อความ
  tft.setCursor(200,50);
  tft.print(sensor.readRangeContinuousMillimeters());
  if (sensor.readRangeContinuousMillimeters() < 100){
    tft.setTextSize(3);
    tft.setTextColor(tft.color24to16(0xFF4500));
    tft.setTextSize(5);//ขนาดข้อความ
    tft.drawString("Be Careful", 100, 100);
    delay(300);


    
  }
  //จบ
  int a = millis() / 1000;  
  tft.fillRect(0, 0, 120, 25, tft.color24to16(0xFFFFFF));  
  tft.setTextColor(tft.color24to16(0xFF0066));//สีข้อความ
  tft.setTextSize(1);//ขนาดข้อความ
  tft.drawString("Time: ", 10, 10);//ข้อความ
  tft.setCursor(40, 10);
  tft.print(a);
  a++; 
  nowTime = elapsedTime;//ใช้หน่วงเวลา
    
  }

} 
