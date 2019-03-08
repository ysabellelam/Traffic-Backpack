// Custom one-way communication with Bluetooth HM-10
// Receiving data in the form of a struct from transmitter
//
// Reads from the software UART and prints the received packet


// Library to make a Software UART
#include <SoftwareSerial.h>
#include <RGBmatrixPanel.h>
#define RX 13
#define TX 12

#define BAUDRATE 9600

#define CLK 11 // USE THIS ON ARDUINO MEGA
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);
 
SoftwareSerial BTSerial(RX, TX); // (RX, TX)

// Struct to hold the data we want to receive
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
  matrix.begin();
}
 
void loop() {
  // Receive data from the bluetooth
  bluetooth_receive();  
  delay(1);
  //check(pkt.a, pkt.b, pkt.c); 

  
}

// Function responsible for receiving data over bluetooth
void bluetooth_receive() {
  // Check the software serial buffer for data to read
  if(BTSerial.available() >= sizeof(Packet)) {
    // Read in the appropriate number of bytes to fit our Packet
    BTSerial.readBytes((byte *) & pkt,sizeof(Packet));
    
    // Print packet (debug)
    print_packet();
  }   
}

// Function to print packet data (debug)
void print_packet() {  
  Serial.print("RX: (a,b,c)=(");
  Serial.print(pkt.a); Serial.print(",");
  Serial.print(pkt.b); Serial.print(",");
  Serial.print(pkt.c); Serial.print(",");
  Serial.println(")");
}

void check(int a, int b, int c){
  if(a==1 && b==0){
    left();
  }
  else if(a==1 && b==1){
    leftstop();
  }
  else if(c==1 && b==0){
    right();
  }
  else if(c==1 && b==1){
    rightStop();
  }
  else if(a=0 && b==1 && c==0){
    stopNow();
  }
  else{
    biking(); 
  }
}


void left(){ //left only
  // draw left arrow (yellow)
while(true){
  matrix.fillRect(21, 11, 11, 10, matrix.Color333(7, 3, 0));
  delay(250);
  matrix.fillRect(15, 11, 11, 10, matrix.Color333(7, 3, 0));
  delay(250); 

  for (int i=0; i < 15; i++){
   matrix.drawLine(i, 15-i, i, 15+i, matrix.Color333(7, 3, 0));
    }

  delay(1000); 
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  delay(250); 
}
}

void leftstop(){ //left and slowing down
  // draw left arrow (yellow)
while(true){
  matrix.fillRect(21, 11, 11, 10, matrix.Color333(7, 3, 0));
  delay(250);
  matrix.fillRect(15, 11, 11, 10, matrix.Color333(7, 3, 0));
  delay(250); 

  for (int i=0; i < 15; i++){
   matrix.drawLine(i, 15-i, i, 15+i, matrix.Color333(7, 3, 0));
    }
  delay(500); 
  matrix.fillScreen(matrix.Color333(7, 0, 0));
  delay(1000); 
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  delay(250); 
}
}

void right(){ //right only
 while(true){
  matrix.fillRect(0, 11, 11, 10, matrix.Color333(7, 3, 0));
  delay(250); 
  matrix.fillRect(6, 11, 11, 10, matrix.Color333(7, 3, 0));
  delay(250);

  for (int i=0; i <= 15; i++){
   matrix.drawLine(16+i, 32-i, 16+i,i, matrix.Color333(7, 3, 0));
    }

  delay(1000); 
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  delay(250); 
}
}

void rightStop(){ //right and slowing down
 while(true){
  matrix.fillRect(0, 11, 11, 10, matrix.Color333(7, 3, 0));
  delay(250); 
  matrix.fillRect(6, 11, 11, 10, matrix.Color333(7, 3, 0));
  delay(250);

  for (int i=0; i <= 15; i++){
   matrix.drawLine(16+i, 32-i, 16+i,i, matrix.Color333(7, 3, 0));
    }
 delay(500); 
  matrix.fillScreen(matrix.Color333(7, 0, 0));
  delay(1000); 
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  delay(250); 
}
}
void stopNow(){ //stopping
  matrix.fillScreen(matrix.Color333(7, 0, 0)); 
  delay(1000); 
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  delay(500); 
   matrix.fillScreen(matrix.Color333(7, 0, 0)); 
  delay(1000); 
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  delay(500); 
}

void biking(){ //biking 
  matrix.fillScreen(matrix.Color333(7, 7, 0)); 
  delay(1000); 
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  delay(500); 
   matrix.fillScreen(matrix.Color333(7, 7, 0)); 
  delay(1000); 
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  delay(500); 
}
