//Written by Ahmet Burkay KIRNIK
//TR_CapaFenLisesi
//Measure Angle with a MPU-6050(GY-521)

#include<Wire.h>

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int minVal=265;
int maxVal=402;

double x;
double y;
double z;


// Signals set
int LED_Left = 3;
int LED_Right = 5;
int Buttom_Left = 4;
int Buttom_Right = 6;
int R_value = 0;
int L_value = 0;


// Break set
int LED = 8;
int Matrix = 9;
int Trig = 10;
int Echo = 11;
long Time;
int DisCm;
int DisInch;
int BreakDis;


void setup() {

  // gyro
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);

  
  // Signals
  pinMode(LED_Left, OUTPUT);
  pinMode(LED_Right, OUTPUT);
  pinMode(Buttom_Left, INPUT);
  pinMode(Buttom_Right, INPUT);



  // Break
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(Matrix, OUTPUT);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
}

void loop() {


   R_value = digitalRead(Buttom_Right);
  L_value = digitalRead(Buttom_Left);


  // Gyro
     Gyro(x,y,z);
     print_gyro();

    
   if(R_value != 0) {
    
    while(y>=5 && y<=345){

      Gyro(x,y,z);
      print_gyro();
        
      digitalWrite(LED_Right,HIGH);

      Break();
      digitalWrite(LED_Right,LOW);
      delay(100);
      
      
    }
  }
  
  if(L_value != 0) {
    while(y>=5 && y<=345){

      Gyro(x,y,z);
      print_gyro();
  
      digitalWrite(LED_Left,HIGH);
      Break();
      digitalWrite(LED_Left,LOW);
      delay(100);
    }
  } 
  Break();
  
}

void Gyro(double &x, double &y, double &z){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  int xAng = map(AcX,minVal,maxVal,-90,90);
  int yAng = map(AcY,minVal,maxVal,-90,90);
  int zAng = map(AcZ,minVal,maxVal,-90,90);

     x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
     y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
     z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);

    delay(400);
}

void print_gyro() {
  Serial.print("AngleX= ");
   Serial.print(x);
  
   Serial.print("  AngleY= ");
   Serial.print(y);
  
   Serial.print("  AngleZ= ");
   Serial.println(z);
   Serial.println("-----------------------------------------");
}



void Break() {
  
digitalWrite(Trig, LOW);
delayMicroseconds(2);
digitalWrite(Trig, HIGH);
delayMicroseconds(10);
digitalWrite(Trig, LOW);
 
Time = pulseIn(Echo, HIGH);
  DisCm= (Time/2) / 29.1;
  DisInch = (Time/2) / 73.914;
 
BreakDis = DisInch;
if (BreakDis <= 1){
  digitalWrite(LED, HIGH);
  digitalWrite(Matrix, HIGH);
}
else{
  digitalWrite(LED, LOW);
  digitalWrite(Matrix, LOW);
}
  Serial.print("Distance Cm: ");
  Serial.print(DisCm);
  Serial.print("   DistanceInch: ");
  Serial.println(DisInch);
