
enum {Bx0, Bx3, Bx5, Sf0,  Sf3, Sf5};
int layout[] = {Bx0, Bx3, Bx5, Sf5,  Sf3, Sf0};

#define BLACK 0
#define WHITE 1

boolean debug = 1;
int lineType =  BLACK;

#define FRONT 8
#define LEFT 4
#define RIGHT 6
#define BACK 2

// Mode eNum
enum {BEGIN, TEST, BLUETOOTH, LINE_FOLLOW, WHITE_SQUARE, OUTER_FLOOR, STORAGE_FLOOR, PROD_FLOOR, OUTER_FLOOR_B, STORAGE_FLOOR_B, PROD_FLOOR_B, END_GAME};

// EEPROM eNum
enum {eP, eI, eD, eMax, eBase, eDebug};

enum {CW, CCW};

//-------------------------------------------------------------------------------------------------------------- Pin Mapping

#define PIN_LED 13
#define BUTTON_1 5
//#define BUTTON_2 5

int buttonStatus = 1;

//-------------------------------------------------------------------------------------------------------------- IR Sensors Array

#define NUM_SENSORS 6
#define RIGHT_EDGE_READING 0
#define LEFT_EDGE_READING (NUM_SENSORS - 1) * 10
#define CENTER_EDGE_READING (NUM_SENSORS - 1) * 5

unsigned int sensor_values[NUM_SENSORS];

const unsigned int irPins[] = {A0, A1, A2, A3, A6, A7};
const unsigned int midPin = 18;

boolean allOut = 0;
boolean allIn = 0;
String irLineString = "000000";
int lastReading = CENTER_EDGE_READING;
int weight = 0, sum = 0, value = 0;
int leftEnd = 0, rightEnd = 0;
int reading[6];

//-------------------------------------------------------------------------------------------------------------- Line Following

float kP = 0, kD = 0, kI = 0;

int pos = CENTER_EDGE_READING;
int error = 0;
int lastError = 0;

// 11 12 10
#define rightMotor1 7
#define rightMotor2 8
#define rightMotorPWM 9

// 7 8 9
#define leftMotor1 11
#define leftMotor2 12
#define leftMotorPWM 10


int leftSpd = 0, rightSpd = 0;
const double slowFactor = 0.5;
const double speedFactor = 1;

int rightMotorSpeed = 0, leftMotorSpeed = 0;

int maxSpeed = 250;
int baseSpeed = 150;

int drift = 0;
int linePos = 0;



