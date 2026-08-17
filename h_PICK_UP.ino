// PICKUP SEQUENCE
int pickup_sequence(float baseAngle, float startPoint[], float homePoint[], VarSpeedServo &baseServoIn, VarSpeedServo &armServoIn, VarSpeedServo &wristServoIn){
  // This function serves as the one to be called when we are picking up an object
  // INPUTS:
  // baseAngle: The angle of the base prior to being picked up.
  // A linear trajectory is generated between the start position and the pickup position
  // startPoint: The starting position of the arm
  // homePoint: returns to the home position after clasping the block

  //OUTPUT:
  // Outputs an integer that is the size of the block based on the analog feedback reading
  
  float distancePickup = 5.0;
  float numPoints = 100.0;
  float zOffset = 0.125;
  float endPoint[3];
  float analogReading;

  // baseAngle; //Making this trigonometrically correct

  // Maths for the end position
  endPoint[0] = startPoint[0] + distancePickup*cos(baseAngle);
  endPoint[1] = startPoint[1] + distancePickup*sin(baseAngle);
  endPoint[2] = startPoint[2]; // - zOffset*distancePickup; //This is so the arm remains on the table

  clawServo.write(90); //Half opening the gripper
  compute_trajectory(startPoint, endPoint, numPoints, baseServoIn, armServoIn, wristServoIn); // Moving towards the block
  delay(3000);
  clawServo.slowmove(180, 25); //Clasping on to the block
  delay(3000); //Pausing to ensure that the block is in the gripper
  //---------------
  //    Potentially read the analog servo in here
  analogReading = analogRead(analogFeedbackPin);
  for (int i = 0; i < 10; i ++){
    analogReading = (analogReading + analogRead(analogFeedbackPin))/2; //Taking an average
    Serial.println(analogRead(analogFeedbackPin));
  }
  Serial.print("Serial reading: ");
  Serial.println(analogReading);
  if (analogReading < 580){
    cubeSize = 1; //Depends on whatever the sizes end up being
    //This is the reading for a small cube
  }
  else cubeSize = 0; //This would be the large reading
  //---------------
  // cube 
  compute_trajectory(endPoint, homePoint, numPoints, baseServoIn, armServoIn, wristServoIn); // Moving back to the home postion
  delay(1000); //Handing over to the color detection code
  return cubeSize;
}
