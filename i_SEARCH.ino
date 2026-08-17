//SEARCH ALGORITHM:
void search_algorithm(int leftOrRight, float startPoint[], VarSpeedServo &baseServoIn, VarSpeedServo &armServoIn, VarSpeedServo &wristServoIn){
  int edgeDetected = 0;
  float startDistance = 6; // Absolute distance between the base of the robot and the closest blocks
  float endDistance = 18; //The furthest absolute distance that the robot will be searching

  //Search angle and distance
  int searchAngle = 90; // The starting angle of the search
  searchDistance = 6; // how far the end effector is from its home position, this is now global
  //float baseAngleIn;

  //Increments 
  float deltaAngle = 3; // delta Angle in degrees (negative as we are sweeping the y negative side
  float deltaDistance = 1; // delta distance in degrees (after it completes one full swing of the workspace)
  float numPoints = 100.0; // The number of points that make up the trajectory
  int angleIncrement; //used in the loops (this is here so it is not constatly initialized

  // Edge detection:
  int edgeDet = 0;


  float searchPoint[3];
  searchPoint[0] = startPoint[0];
  searchPoint[1] = startPoint[1];
  searchPoint[2] = 0;
  
  clawServo.write(0);
  
  float prevPoint[3]; //So that we can IK towards that point

  // int leftOrRight = 0;
  // Left = 1
  // Right = 2, this is now an input to the function
  // Must be passed into the function to prevent errors from occuring 

  
  ; // Searching to the left or right
  Serial.println("Starting search algorithm");

  // While the boxes have not been found yet
  for (int distanceIncrement = 0; distanceIncrement < 12; distanceIncrement ++){
    Serial.print("Distance: ");
    Serial.println(searchDistance);
    Serial.print("Angle: ");
    Serial.println(baseAngleIn);

    // Points for us to move forwards (it was the best way of doing it)
    prevPoint[0] = - searchDistance * cos(baseAngleIn*PI/180);
    prevPoint[1] = searchDistance * sin(baseAngleIn*PI/180);
    prevPoint[2] = 0;
    Serial.print("Starting point: (");
    Serial.print(prevPoint[0]);
    Serial.print(" , ");
    Serial.print(prevPoint[1]);
    Serial.print(" , ");
    Serial.print(prevPoint[2]);
    Serial.println(")");
    
    searchDistance = searchDistance + deltaDistance; 
    searchPoint[0] = - searchDistance * cos(baseAngleIn*PI/180);
    searchPoint[1] = searchDistance * sin(baseAngleIn*PI/180);
    searchPoint[2] = 0;
    Serial.print("Second point: (");
    Serial.print(searchPoint[0]);
    Serial.print(" , ");
    Serial.print(searchPoint[1]);
    Serial.print(" , ");
    Serial.print(searchPoint[2]);
    Serial.println(")");

    delay(1000);
    compute_trajectory(prevPoint, searchPoint, numPoints, baseServoIn, armServoIn, wristServoIn);
    delay(1000); // Moving the gripper forwards for the next sweep
    

    switch (leftOrRight){ //Rotating left
      case(1):
        for (angleIncrement = 0; angleIncrement < 30; angleIncrement ++){
          searchAngle = searchAngle + deltaAngle;
          baseAngleIn = 90 - searchAngle;
  
          Serial.print("Moving left, angle: ");
          Serial.println(baseAngleIn);
    
          baseServoIn.slowmove(searchAngle, 50); //Rotating the entire assembly (note that the other angles are not updated
          delay(20);
          // ----------------
          // Edge detection function
          // Break if an edge is detected, use the searchAngle as the argument for the pickup sequence
          // ----------------
          edgeDet = edge_det(REF_VOLTAGE);
          if (edgeDet == 1){
            baseAngleIn = 90.0 - searchAngle;
            Serial.print("Base angle: ");
            Serial.println(baseAngleIn);
            break;
          }
          delay(20);
        }
        // delay(500); 
        
        leftOrRight = 2;
        delay(500);
        break;
        
      case (2):// Rotating right
        for (angleIncrement = 0; angleIncrement < 30; angleIncrement ++){
          searchAngle = searchAngle - deltaAngle;
          baseAngleIn = 90 - searchAngle;
  
          Serial.print("Moving right, angle: ");
          Serial.println(baseAngleIn);
    
          baseServoIn.slowmove(searchAngle, 50); //Rotating the entire assembly (note that the other angles are not updated
          delay(20);
          // ----------------
          // Edge detection function
          // Break if an edge is detected, use the searchAngle as the argument for the pickup sequence
          // ----------------
          edgeDet = edge_det(REF_VOLTAGE);
          if (edgeDet == 1){
            baseAngleIn = 90.0 - searchAngle;
            Serial.print("Base angle: ");
            Serial.println(baseAngleIn);
            break;
          }
          delay(20);
        }
        leftOrRight = 1;
        delay(500);
        break;
    }  
    if (edgeDet == 1) break;
  }
}
