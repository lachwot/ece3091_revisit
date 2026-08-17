//Setup fn for all components needed

void setup() {
//FK IK setup
baseServo.attach(9); // set pin 11 as base motor output
armServo.attach(6); // set pin 10 as shoulder motor output
wristServo.attach(5); // set pin 9 as elbow motor output
clawServo.attach(3); // set pin 6 as claw motor output
Serial.begin(9600);
Serial.flush();
  
//Edge detector setup
pinMode(analogEdgePin, INPUT);

//Colour detector setup
pinMode(analogColourPin, INPUT);
pinMode(redledPin, OUTPUT);
pinMode(greenledPin, OUTPUT);
pinMode(blueledPin, OUTPUT);
}
