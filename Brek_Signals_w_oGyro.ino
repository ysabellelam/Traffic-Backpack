// Signals set
int LED_Left = 2;
int LED_Right = 4;
int Buttom_Left = 3;
int Buttom_Right = 5;
int R_value = 0;
int L_value = 0;

int gyro = 6;
int  gyro_value= 0 ;

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
  // Signals
  pinMode(LED_Left, OUTPUT);
  pinMode(LED_Right, OUTPUT);
  pinMode(Buttom_Left, INPUT);
  pinMode(Buttom_Right, INPUT);

  pinMode(gyro, INPUT);

  // Break
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(Matrix, OUTPUT);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
}

void loop() {

  Signals();
  Break();
  
}

void Signals(){

  R_value = digitalRead(Buttom_Right);
  L_value = digitalRead(Buttom_Left);
  gyro_value = digitalRead(gyro);


  if(R_value != 0) {
    while(gyro_value == 0){
      gyro_value = digitalRead(gyro);
  
      digitalWrite(LED_Right,HIGH);

      Break();
      digitalWrite(LED_Right,LOW);
      delay(100);
    }
  }
  
  if(L_value != 0) {
    while(gyro_value == 0){
      gyro_value = digitalRead(gyro);
  
      digitalWrite(LED_Left,HIGH);
      Break();
      digitalWrite(LED_Left,LOW);
      delay(100);
    }
  } 
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
  }
