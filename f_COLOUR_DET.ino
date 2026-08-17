int colour_det() {
//Cycle through flashing RGB, compare and accept the highest value
//Highest value is the true voltage level for that cube

//Initialise temp storage for the voltage readings
int cube_clr = 0; //State for cube's colour, 0 = init, 1 = r, 2 = g, 3 = b
int rgb_val[3] = {0,0,0}; //Corresponds to voltage readings for r,g,b light
int larger = 0;
int cube_voltage = 0;

//Flash red, wait and record to temp value
digitalWrite(redledPin,HIGH);
delay(500);
rgb_val[0] = analogRead(analogLDRPin);
digitalWrite(redledPin,LOW);

//Flash green, wait and record to temp value
digitalWrite(greenledPin,HIGH);
delay(500);
rgb_val[1] = analogRead(analogLDRPin);
digitalWrite(greenledPin,LOW);

//Flash blue, wait and record to temp value
digitalWrite(blueledPin,HIGH);
delay(500);
rgb_val[2] = analogRead(analogLDRPin);
digitalWrite(blueledPin,LOW);

//max returns the larger of the two values
larger = max(rgb_val[0], rgb_val[1]);
cube_voltage = max(larger, rgb_val[2]);


//Find out the colour based on which light value was the highest
if (cube_voltage == rgb_val[0]) { 
  //Red detected
  cube_clr = 1;
  Serial.println("Cube RED detected.");
}
else if (cube_voltage == rgb_val[1]) {
  //Green detected
  cube_clr = 2;
  Serial.println("Cube GREEN detected.");
}
else {
  //Blue detected = 11
  cube_clr = 3;
  Serial.println("Cube BLUE detected.");
}

delay(500);

return cube_clr;
}
