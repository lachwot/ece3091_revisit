int edge_det(int up) {
  //Takes in integer up, for detection logic when detector is facing upwards (depot)
  //Otherwise detection logic is facing down (cube)
  const int RISE = 30;
  const int DROP = 100;

  int voltage = 0;
  int detected = 0;

  claw_voltage = analogRead(analogClawEdgePin);
  depot_voltage = analogRead(analogDepotEdgePin);


  if (up) {
    //Detector facing upwards, baseline voltage is low -> surface will make voltage high
    if (depot_voltage > DEPOT_HEIGHT_VOLTAGE + RISE) {
      Serial.println("Edge detected");
      detected = 1;
    }
    else  {
      detected = 0;
      Serial.println("No Edge detected");
    }
  }
  else {
    //Detector facing down, baseline is high -> surface will make voltage low
    if (claw_voltage < CUBE_HEIGHT_VOLTAGE - DROP) {
      Serial.println("Edge detected");
      detected = 1;
    }
    else  {
      detected = 0;
      Serial.println("No Edge detected");
    }
  }

  return detected;
}
