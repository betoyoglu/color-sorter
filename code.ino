//SDA pin: A4 pinine
//SCL pin: A5 pinine
//GND pin: Gnd pinine
//VIN pin: 5V pinine
//başlamak için seri port ekranına 8 yazarak gönder butonuna basınız.
//Durdurmak için seri port ekranına 8 yazarak gönder butonuna basınız.
//ÜST MOTOR
#include <Servo.h>
#include "Wire.h"
#include "Adafruit_TCS34725.h"
 
Servo ust_servo;
Servo alt_servo;
int renk = 0;
int data, durum = false;
 
const int KPos=90;
const int TPos=130;
const int SPos=110;
const int YPos=50;
const int MPos=70;
//const int GrPos=30;
const int Renksiz=90;

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);




void setup() {
Serial.begin(9600);
Serial.println("başlamak için seri port ekranına 8 yazarak gönder butonuna basınız.");
Serial.println("Durdurmak için seri port ekranına 9 yazarak gönder butonuna basınız.");
if (tcs.begin()) {
} else {
 
while (1); // Dur!
}
 
ust_servo.attach(9);
alt_servo.attach(8);
 
ust_servo.write(75);
alt_servo.write(90);
//alt_servo.writeMicroseconds(1300); //turn left

delay(10);
}
void loop() {
 
data = Serial.read();
delay(10);
if ( data == '8')
{
durum = true;
 
}
 
/*if ( data =='9')
{
durum = false;
}*/
 
if ( durum == true)
{
makine_baslat();
}
if ( durum == false)
{
makine_durdur();
}




uint16_t renksiz, kirmizi,yesil,mavi;
  float ortRenk, k,y,m;
  delay(100);
  tcs.getRawData(&kirmizi,&yesil,&mavi,&renksiz);
  ortRenk=(kirmizi+yesil+mavi)/3;
  k=kirmizi/ortRenk;
  y=yesil/ortRenk;
  m=mavi/ortRenk;
 Serial.print("Renksiz: "); Serial.println(renksiz);
 Serial.print("Kirmzi: "); Serial.println(k);
 Serial.print("Yesil: "); Serial.println(y);
 Serial.print("Mavi: "); Serial.println(m);
 

if((k>1.4)&&(y<0.5)&&(m<0.5)){
  Serial.println("Kirmizi ");
  alt_servo.write(KPos);
  }
else if((k<0.95)&&(y>1.15)&&(m<1.1)){//0.87 1.17 1                             0.94 1.09 1
  Serial.println("Yesil ");
  alt_servo.write(YPos);
  }
  else if((k<0.85)&&(y<1.15)&&(m>1)){// 0.75 1.09 1.18
  Serial.println("Mavi ");
  alt_servo.write(MPos);
  }
  else if((k>1.1)&&(y>1.1)&&(m<0.7)){
  Serial.println("Sari ");
  alt_servo.write(SPos);
  }
  else if((k>1.6)&&(y>0.6)&&(m<0.7)){
  Serial.println("Turuncu");
  alt_servo.write(TPos);
  }
  /*else if((k>1.1)&&(y>1.1)&&(m<0.7)){
  Serial.println("Gri");
  alt_servo.write(GrPos);
  }*/
   else {
  Serial.println("Renksiz");
  alt_servo.write(Renksiz);
  }
}
 
void makine_baslat()
{
delay(500);
for(int i = 75; i > 33; i--) {
ust_servo.write(i);
delay(5);
}
delay(1000);
 
renk = renk_oku();
Serial.print("renk: ");
Serial.print(renk);
delay(50);
switch (renk) {
//case 1:
//alt_servo.write(30);
 
//Serial.println("Kırmızı");
//break;
case 2:
alt_servo.write(YPos);
Serial.println("Yesil");
break;
case 3:
alt_servo.write(MPos);
Serial.println("Mavi");
break;
case 4:
alt_servo.write(SPos);
Serial.println("Sari");
break;
case 5:
alt_servo.write(TPos);
Serial.println("Turuncu");
break;
//case 6:
//alt_servo.write(150);
//Serial.println("Gri");
//break;
default:
Serial.println(0);
break;
}
delay(300);
 
 
for(int i = 28; i > 0; i--) {
ust_servo.write(i);
delay(5);
}
delay(200);
 
for(int i = 0; i < 76; i++) {
ust_servo.write(i);
delay(5);
}
renk=0;
}
 
void makine_durdur()
{
ust_servo.write(ust_servo.read());
alt_servo.write(alt_servo.read());
}
 
// renk okuma fonksiyonu
int renk_oku() {
uint16_t clearcol, red, green, blue;
float average, k, y, m;
tcs.getRawData(&red, &green, &blue, &clearcol);
 
average = (red+green+blue)/3;
k = red/average;
y = green/average;
m = blue/average;
Serial.print("Renksiz: "); Serial.println(clearcol);
 Serial.print("Kirmzi: "); Serial.println(k);
 Serial.print("Yesil: "); Serial.println(y);
 Serial.print("Mavi: "); Serial.println(m); 
delay(50);
 
if((k>1.8)&&(y<0.75)&&(m<0.48)){
  Serial.println("Kirmizi ");
renk = 1;

}
if((k<0.95)&&(y>1.15)&&(m<1.1)){
  Serial.println("Yesil ");
renk = 2;
 
}
if((k<0.85)&&(y<1.15)&&(m>1)){
  Serial.println("Mavi ");
renk = 3;
 
}

if((k>1.1)&&(y>1.1)&&(m<0.7)){
  Serial.println("Sari ");
renk = 4;
 
}
if((k>1.6)&&(y>0.6)&&(m<0.7)){
  Serial.println("Turuncu");
renk = 5;
 
}
/*if((k>1.2)&&(y>1.13)&&(m<0.68)){
  Serial.println("Gri");
renk = 6;
 
}*/
return renk;
}
