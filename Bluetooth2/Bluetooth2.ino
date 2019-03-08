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
int LED_Left = 3;
int LED_Right = 5;
int Buttom_Left = 4;
int Buttom_Right = 6;
int R_value = 0;
int L_value = 0;
int stateRight; 
int stateLeft;



// Break set
int LED = 8;
int Matrix = 9;
int Trig = 10;
int Echo = 11;
long Time;
int DisCm;
int DisInch;
int BreakDis;


// Library to make a Software UART
#include <SoftwareSerial.h>

#define TX 2
#define RX 3
 
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
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(Matrix, OUTPUT);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  
}
 
void loop() {  
  // Transmit data via bluetooth
  bluetooth_transmit();  

  // Necessary forced delay, if we transmit too fast (no delay)
  //  the error rate increases
  delay(1);
}

// Function responsible for transmitting data over bluetooth
void bluetooth_transmit() {
  // Update data to be transmitted
  pkt.a = 1;
  pkt.b = 0;
  pkt.c = 0;
    
  // Write packet data to the bluetooth - and transmit
  BTSerial.write((byte *) & pkt,sizeof(Packet));

  // Print packet (debug)
  print_packet();
}

int left(){
  return stateLeft; 
}

int right(){
  return stateRight; 
}







// Function to print packet data (debug)
void print_packet() {  
  Serial.print("TX: (a,b,c,d)=(");
  Serial.print(pkt.a); Serial.print(",");
  Serial.print(pkt.b); Serial.print(",");
  Serial.print(pkt.c); Serial.print(",");  
  Serial.println(")");
}
