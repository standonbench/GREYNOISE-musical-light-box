int motorPin = 9;

void setup() {

 Serial.begin(9600);
 pinMode(motorPin, OUTPUT);
}
void loop() {

 int speed = map(analogRead(A0), 0, 1023, 0, 255); //map potentiometer to 0 to 255
 Serial.println(speed);
 
 analogWrite(motorPin, speed);
} 
