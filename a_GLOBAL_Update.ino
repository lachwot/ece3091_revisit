//Declare global vars

//FK IK global vars
  // Forward kinematics programmer
  #include "VarSpeedServo.h"

  // servo motors
  VarSpeedServo baseServo;
  VarSpeedServo armServo;
  VarSpeedServo wristServo;
  VarSpeedServo clawServo;
  
  //Forwards kinematics
  float jointAngles[3];
  float inputAngles[3]; //To be used in the FK calculations
  float endEffectorPos[3];
  float L1 = 6.5;
  float L2 = 8;
  float L3 = 8;
  float L4 = 4.5;

  // set input pins
  int inputPin1 = A0;// set A0 as base pot input
  int inputPin2 = A1;// set A1 as shoulder joint pot input
  int inputPin3 = A2;// set A2 as elbow joint pot input
  int inputPin4 = A3; // set A3 as claw pot input
  int potInterrupt = 10;

  // input values from pots
  int inputVal1;
  int inputVal2;
  int inputVal3;
  int inputVal4;

  //Potentiometer position saving
  int storeValBase = 90;
  int storeValArm = 90;
  int storeValWrist = 90;

  //Servo calibration
  int armMax = 120;
  int armMin = 0;
  int wristMax = 180;
  int wristMin = 50;

  //End effector calibration
  int xmax = 22;
  int xmin = 0;
  int ymax = 22;
  int ymin = 0;
  int zmax = 14.5;
  int zmin = 0; // Touching the table
  //there are also some dependent relationships between some of the z and x/y coordinates (0,0,0 is not possible for example)

  //Setting the servos up globally so that they can be used by the interrupt function

//Edge detector global vars
  const int analogClawEdgePin = A5;
  const int analogDepotEdgePin = A2;
  int CUBE_HEIGHT_VOLTAGE = 0; //Infrared baseline reading at cube height 
  int DEPOT_HEIGHT_VOLTAGE = 0; //Infrared baseline reading at depot height 

//Colour detection global vars
  const int analogLDRPin = A4;
  const int redledPin = 2;
  const int greenledPin = 4;
  const int blueledPin = 7; 

//Size detection global vars
  const int analogClawFB = A3;
