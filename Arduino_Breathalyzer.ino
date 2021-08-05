    /////////////////////////////////////////////////////////////////
   //             Arduino Breathalyzer Project             v1.01  //
  //       Get the latest version of the code here:              //
 //      http://educ8s.tv/arduino-breathalyzer-project          //
/////////////////////////////////////////////////////////////////

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <dht.h>
dht DHT;

#define OLED_RESET 4
int TIME_UNTIL_WARMUP = 3;
unsigned long time;

#define DHT11_PIN 7

int analogPin = 0;
int val = 0;
int roundtemp = 0;
float temp = 0;
Adafruit_SSD1306 display(OLED_RESET);


void setup()   {                
 Wire.begin();

 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
 display.clearDisplay();
}

void loop() {  
  delay(1000);
  val = readAlcohol();
  printTitle();
  printWarming();
  int chk = DHT.read11(DHT11_PIN);
  
  time = millis()/1000;
  
  if(time<=TIME_UNTIL_WARMUP)
  {
    time = map(time, 0, TIME_UNTIL_WARMUP, 0, 100);
    display.drawRect(10, 25, 110, 5, WHITE); //Empty Bar
    display.fillRect(10, 25, time, 5,WHITE);
  }else
  {
     printTitle();
     printAlcohol(val);
     printAlcoholLevel(val);  
     dhtscreen();
  }
  display.display();

}


void printTitle()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(28,0);
  display.println("Alkometrs");
}

void printWarming()
{
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(12,8);
  display.println("Uzsildam");
}

void printAlcohol(int value)
{
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(30,8);
  display.println(val);
}

void dhtscreen()
{
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(80,9);
  display.print(round(DHT.temperature));
  display.print("C ");
  display.setCursor(80,15);
  display.print(DHT.humidity);
  display.print("%");
}

void printAlcoholLevel(int value)
{
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20,23);
  
  if(value<200)
  {
      display.println("Tu esi skaidrs.");
  }
  if (value>=200 && value<280)
  {
      display.println("Viens alins.");
  }
  if (value>=280 && value<350)
  {
      display.println("Norm sadzeries.");
  }
  if (value>=350 && value <450)
  {
      display.println("Diezgan pills!");
  }
  if(value>450)
  {
     display.println("Tu esi metams!!!");
  }
 }
 
 int readAlcohol()
 {
  int val = 0;
  int val1;
  int val2;
  int val3; 


  display.clearDisplay();
  val1 = analogRead(analogPin); 
  delay(10);
  val2 = analogRead(analogPin); 
  delay(10);
  val3 = analogRead(analogPin);
  
  val = (val1+val2+val3)/3;
  return val;
 }
