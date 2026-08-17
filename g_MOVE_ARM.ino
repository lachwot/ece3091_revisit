void move_arm(float endEffectorPos[]) {
//Takes in a vector of end effector position, calcs the IK for the ArmAngle needed
//Use ArmAngle to move the arm to desired pos

  calc_IK(endEffectorPos[]);
  
  //WRITING TO SERVOS
  // control base
  baseServo.write(inputAngles[0]*(180/PI));
  delay(10);

  // control shoulder
  //shouler joint is inverted
  armServo.write(180 - inputAngles[1]*(180/PI));
  Serial.print(180 - inputAngles[1]*(180/PI));
  delay(10);

  // control elbow

  wristServo.write(150 - abs(inputAngles[2]*(180/PI)));
  delay(10);

  // control claw
  inputVal4 = analogRead(inputPin4);
  inputVal4 = map (inputVal4, 0, 1023, 40, 180);
  clawServo.write(inputVal4);
  //Serial.println(inputVal4);
  // clawServo.write(90); //Testing the mid position of the servos
  delay(10);
}

 void calc_IK(float endEffectorPos[])  {
  //Calculating the inverse kinematics of a point (for a set of angles)
  //Follows on from the maths done in the second assignment
  
  float x = endEffectorPos[0];
  float y = endEffectorPos[1];
  float z = endEffectorPos[2];
  
  //Keep the angles in radians for now
  float t1Inv = atan(y/x);
  
  float xx = sqrt(sq(x) + sq(y)) - L4;
  float zz = z - L1;
  
  float t3Inv = -acos((sq(xx) + sq(zz) - sq(L2) - sq(L3))/(2*L2*L3));
  float t2Inv = atan(zz/xx) - atan((L3*sin(t3Inv))/(L2+L3*cos(t3Inv)));
  
  //Converting the angles to degrees and returning
  inputAngles[0] = (180/PI)*t1Inv;
  inputAngles[1] = (180/PI)*t2Inv;
  inputAngles[2] = (180/PI)*t3Inv;
  
  }



//GENERATING A LINEAR TRAJECTORY OF POINTS
void compute_trajectory(float startPoint[], float endPoint[], float numPoints, VarSpeedServo &baseServoIn, VarSpeedServo &armServoIn, VarSpeedServo &wristServoIn){
  //Trajectory computing function. This sets the servos to the right angles during the movement from one object to another object
  //This trajectory is not as simple as setting the angles immediately, since this could lead to the robot "jerking" while mthe servos move
  //Thus, we must produce a smooth trajectory between the two points
  //The current solution is to produce intermediate steps for the robot to update its servos to.
  //The servo moving function will be the one called from within this function
  
  float intermediatePoint[3]; //Storing the 
  float intermediateAngle[3]; 
  for (int j = 0; j < 3; j++){
    intermediatePoint[j] = startPoint[j];
  }
  
  for (int i = 0; i < numPoints; i++){
    intermediatePoint[0] = startPoint[0] + ((i+1)/numPoints)*(endPoint[0] - startPoint[0]); // X
    intermediatePoint[1] = startPoint[1] + ((i+1)/numPoints)*(endPoint[1] - startPoint[1]); // Y
    intermediatePoint[2] = startPoint[2] + ((i+1)/numPoints)*(endPoint[2] - startPoint[2]); // Z
    
    //-------
    //Then set the servos, with a delay to make sure that they do not 
    calc_IK(intermediatePoint);
    servoWrite(inputAngles, baseServoIn, armServoIn, wristServoIn);
    delay(10);
    //--------

    /* Debugging print statements
    Serial.println(i);
    Serial.println(intermediatePoint[0]);
    Serial.println(intermediatePoint[1]);
    Serial.println(intermediatePoint[2]);
    Serial.println();
    */
  }
}
