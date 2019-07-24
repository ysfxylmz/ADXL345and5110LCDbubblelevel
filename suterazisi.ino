#include <Wire.h>
#include <LCD5110_Basic.h>
LCD5110 myGLCD(8,9,10,11,12);
extern uint8_t koor[];
extern uint8_t SmallFont[];
int sifirla=7;
int buton=0;
int x1;
int y1;
int x2;
int y2;
int sx;
int sy;
int syk;
int sxk;

#define accel_module (0x53)
byte values[6];
char output[512];

void setup() {
  pinMode(sifirla,INPUT);
   myGLCD.InitLCD();
   myGLCD.setFont(SmallFont);
  myGLCD.setContrast(60);
  
  Wire.begin();
  Serial.begin(9600);
    Wire.beginTransmission(accel_module);
    Wire.write(0x2D);
    Wire.write(0);
    Wire.endTransmission();
      Wire.beginTransmission(accel_module);
    Wire.write(0x2D);
    Wire.write(16);
    Wire.endTransmission();
      Wire.beginTransmission(accel_module);
    Wire.write(0x2D);
    Wire.write(8);
    Wire.endTransmission();
  // put your setup code here, to run once:

}

void loop() {
  int xyzregister=0x32;
  int x, y, z;
  Wire.beginTransmission(accel_module);
  Wire.write(xyzregister);
  Wire.endTransmission();
  Wire.beginTransmission(accel_module);
  Wire.requestFrom(accel_module,6);
  int i=0;
  while(Wire.available()){
  (values[i])=Wire.read();
  i++;
    }
Wire.endTransmission();
  x=(((int)values[1]) << 8) | values[0];
y=(((int)values[3]) << 8) | values[2];
z=(((int)values[5]) << 8) | values[4];

//    ------------                                               -------------                         \\

x1=map(x,-270,270,-100,100);
y1=map(y,-270,270,-100,100);
x2=map(x1,-100,100,-100,100);
y2=map(-y1,-100,100,-50,50);


buton=digitalRead(sifirla);
  if (buton==HIGH){
  syk=y1;
  sxk=x1;
  sy=y2;
  sx=x2;
   }
   int a=x2+39-sx;
   if (a>=76) a=76;
   if (a<=0)  a=00;
   int b=y2+31-sy;
   if (b>=43) b=43;
   if (b<=10) b=10;
   int c=x1-sxk;
    if (c>=100) c=100;
   if (c<=-100) c=-100;
   int d=y1-syk;
    if (d>=100) d=100;
   if (d<=-100) d=-100;
   
  myGLCD.clrScr();
  myGLCD.drawBitmap(0, 0, koor, 84, 48);
  myGLCD.setFont(SmallFont);
  myGLCD.print("x:", LEFT, 0);
  //myGLCD.printNumI(a, LEFT,40);
 // myGLCD.print("", RIGHT,40);
  myGLCD.printNumI(c,20,0);
  myGLCD.printNumI(d, RIGHT,0);
  myGLCD.print("|y:",39,0);
  //myGLCD.printNumI(y, RIGHT,0);
  myGLCD.print("*", a,b) ;
  
  

  delay(250);
 

}
