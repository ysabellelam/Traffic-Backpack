// Custom one-way communication with Bluetooth HM-10
// Transmitting data in the form of a struct to receiver
//
// Writes (hardcoded) data to the software UART 
//  and prints the transmitted packet

#include<Wire.h>

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int minVal=265;
int maxVal=402;

double x;
double y;
double z;

// Signals set
int LED_Left = 7;
int LED_Right = 5;
int Buttom_Left = 4;
int Buttom_Right = 6;
int R_value;
int L_value;
int previousR=LOW;
int previousL=LOW; 
int stateRight; 
int stateLeft;

// Break set
int LED = 8;
int Trig = 9;
int Echo = 10;
long Time;
double DisCm;
double DisInch;
double BreakDis;
int stopplease; 

// Library to make a Software UART
#include <SoftwareSerial.h>

#define TX 12
#define RX 13
 
SoftwareSerial BTSerial(RX, TX); // (RX, TX)

#define BAUDRATE 9600

// Struct to hold the data we want to transmit
struct Packet {
  int a;
  int b;
  int c;
} pkt; // Instantiate a Packet struct
 
void setup() {
  // Start Serial Monitor for feedback
  Serial.begin(BAUDRATE);

  // HM-10 virtual UART
  BTSerial.begin(BAUDRATE);  
  
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
  pinMode(LED, OUTPUT);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  
}
 
void loop() {   
  bluetooth_transmit();  
  delay(500); 
  // Necessary forced delay, if we transmit too fast (no delay)
  //  the error rate increases
  //stopNow(); 
}

// Function responsible for transmitting data over bluetooth
void bluetooth_transmit() {
  // Update data to be transmitted
  pkt.a = left();
  pkt.b = stopNow();
  pkt.c = right();
    
  // Write packet data to the bluetooth - and transmit
  BTSerial.write((byte *) & pkt,sizeof(Packet));

  // Print packet (debug)
  print_packet();
}

int left(){
  L_value = digitalRead(Buttom_Left);
  if(L_value == LOW && previousL == HIGH){
    if(stateLeft == 0){
      digitalWrite(LED_Left,HIGH);
      stateLeft = 1;
      digitalWrite(LED_Right,LOW);
      stateRight = 0; 
      delay(10);
    }
    else{
      digitalWrite(LED_Left,LOW);
      stateLeft = 0; 
    }
  }
  previousL = L_value;
  gyrocheck();
  return stateLeft; 
}


int right(){
  R_value = digitalRead(Buttom_Right);
  if(R_value == LOW && previousR== HIGH){
    if(stateRight == 0){
      digitalWrite(LED_Right,HIGH);
      stateRight = 1; 
      digitalWrite(LED_Left,LOW);
      stateLeft = 0; 
      delay(10); 
    }
    else{
    digitalWrite(LED_Right,LOW);
    stateRight = 0; 
    }
  }
  previousR = R_value; 
  gyrocheck();
  return stateRight; 
}

int stopNow() {
  breakfunction();
  if (BreakDis <= 5){
    digitalWrite(LED, HIGH);
    stopplease = 1; 
   }
  else{
    digitalWrite(LED, LOW);
    stopplease = 0; 
  }
  //breakprint();
  return stopplease; 
}

void breakfunction(){
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
 
  Time = pulseIn(Echo, HIGH);
  //DisCm= (Time/2) / 29.1;
  //DisInch = (Time/2) / 73.914;
  DisInch= Time*0.034/2;
  // Prints the distance on the Serial Monitor
  //Serial.print("Distance: ");
  //Serial.println(DisInch);
  BreakDis = DisInch;
}


void breakprint(){
  //Serial.print("Distance Cm: ");
  //Serial.print(DisCm);
  Serial.print("   DistanceInch: ");
  Serial.println(DisInch);  
}

void gyrocheck(){
  gyro();
  if(y>=10 && y<=340){
    digitalWrite(LED_Right,LOW);
    stateRight = 0; 
    digitalWrite(LED_Left,LOW);
    stateLeft = 0; 
  }
}


void gyro(){
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
  //print_gyro();
 
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


// Function to print packet data (debug)
void print_packet() {  
  Serial.print("TX: (a,b,c)=(");
  Serial.print(pkt.a); Serial.print(",");
  Serial.print(pkt.b); Serial.print(",");
  Serial.print(pkt.c);
  Serial.println(")");
}
