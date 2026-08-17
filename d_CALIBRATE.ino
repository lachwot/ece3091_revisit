int calibrate() {
  //Calibrate edge detector
  const int depot_edge = {8, 8, 7};
  const int cube_height = {12.5,0,1};
  const int depot_height = {12.5,0,7};

  int depot_dir = 0; //depot direction, 0 = init, 1 = left, 2 = right
  bool pass = false;
  String str = "";

  //Wait to setup the light environment before calibration
  //pass is used to accept only a "y" from the user in order to move on as a safeguard
  move_arm(cube_height);
  Serial.println("Cube Calibration: Type y to confirm");

  while (!pass) {
    
    CUBE_HEIGHT_VOLTAGE = analogRead(analogClawEdgePin); //Edge Det. Voltage on a normal surface

    Serial.print("Cube height Voltage: ");
    Serial.println(CUBE_HEIGHT_VOLTAGE);

    if (Serial.available())
    {
      str = Serial.readString();
      if (str == "y") {
        pass = true;
        Serial.print("Cube height Voltage SAVED: ");
        Serial.println(CUBE_HEIGHT_VOLTAGE);
      }
    }
    delay(500);
  }

  pass = false;
  str = "";

  move_arm(depot_height);
  Serial.println("Depot calibration: Type y to confirm");

  while (!pass) {
    
    DEPOT_HEIGHT_VOLTAGE = analogRead(analogClawEdgePin); //Edge Det. Voltage on a normal surface

    Serial.print("Depot height Voltage: ");
    Serial.println(DEPOT_HEIGHT_VOLTAGE);

    if (Serial.available())
    {
      str = Serial.readString();
      if (str == "y") {
        pass = true;
        Serial.print("Depot height Voltage SAVED: ");
        Serial.println(DEPOT_HEIGHT_VOLTAGE);
      }
    }
    delay(500);
  }

  pass = false;
  str = "";

  //TO DO
  //Move arm to {8,8,7}, is depot there? if not its on the other side
  move_arm(depot_edge);
  delay(50);
  
  //if detected, fn returns 1, dir = 1 + 1 = 2 for depot on right side
  //if not detected, fn returns 0, dir = 1 for depot on left side
  depot_dir = edge_det(1) + 1;
  
  return depot_dir;
}
