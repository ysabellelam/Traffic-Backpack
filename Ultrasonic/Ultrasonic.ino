const int trigger = 9;
const int echo = 10;

long duration; 
long distance; 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
}

void loop() {
  digitalWrite(trigger, LOW);
  delayMicroseconds(2); // Sets the trigPin on HIGH state for 10 micro seconds 
  digitalWrite(trigger, HIGH); delayMicroseconds(10); digitalWrite(trigger, LOW); 
  duration = pulseIn(echo, HIGH);
  distance= duration*0.034/2; 
  Serial.print("Distance: "); 
  Serial.println(distance); 

}
