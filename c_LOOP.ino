void loop() {
  //Define variables
  const int clr_coords[3] = {0, 0, 0}; //Fixed Colour detection station coords
  const float homePoint[3] = {12.5, 0.0, 14.5};
  //Depot coords has {x,y,z}, 3x2 matrix for cube colour & size, 2 rows for left and right direction of depot
  const int depot_mat[2][3][2][3] = {{{{0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}}},
    {{{0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}}}};

  int finished = 0;
  int cube_colour = 0; //State for cube's colour, 0 = init, 1 = r, 2 = g, 3 = b
  int cube_size = 0; //State for cube's size, 0 = init, 1 = SML, 2 = LRG
  int cube_detected = 0;
  int cube_state[3][2] = {{1, 1}, {1, 1}, {1, 1}}; //If cube deposited, set val = 0, rows = rgb, col = Sml, Lrg
  int depot_dir = 0; //depot direction, 0 = init, 1 = left, 2 = right
  int depot_coords[3] = {0, 0, 0};

  //Calibrate (Edge det. -> Bench/Cube, Bench/Depot Edge), (Depot coords, Clr station)
  depot_dir = calibrate();

  float searchPoint[3];
  float pickupPoint[3];
  float homePoint[3] = {12.5, 0.0, 14.5};
  float baseAngle = 0 * (PI/180);

  while (~finished) {
    baseAngle = 0;
    searchPoint[0] = searchDistance*cos(baseAngle);
    searchPoint[1] = searchDistance*sin(baseAngle);
    searchPoint[2] = 0;

    search_algorithm();
        
    cube_size = pick_up();
    move_arm(homePoint);
    delay(20);
    move_arm(clr_coords);
    cube_colour = colour_det(); //Indicates which colour is detected in an array
    move_arm(homePoint);

    //Save specfic coords in a vector
    for (int k = 0; k < 3; k++) {
      depot_coords[k] = depot_mat[depot_dir - 1][cube_colour - 1][cube_size - 1][k];
    }

    move_arm(depot_coords);
    delay(20);
    clawServo.write(180) //release grip

    cube_state[cube_colour - 1][cube_size - 1] = 0; //Mark deposited cube as 0, indicating done with it

    //Any cube remaining in cube_state will reset cube_detected
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 2; j++) {
        if (cube_state[i][j] == 1) cube_detected = 0;
      }
    }

    //If cube detected NOT resetted, then finished will be set
    if (cube_detected) {
      finished = 1;
    }

    delay(200);
  }

  //Infinite loop that holds robot at homePoint if ALL cubes completed
  move_arm(homePoint);
  delay(5000);
}
