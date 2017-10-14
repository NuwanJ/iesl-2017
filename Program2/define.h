
#define DEBUG 0

enum {RIGHT_SENSOR, FRONT_SENSOR, LEFT_SENSOR};
enum {COLOR_OPEN, COLOR_RED, COLOR_GREEN, COLOR_BLUE};

#define DELAY_BUZZER 200
#define DELAY_INDICATOR 100

#define PIN_PICK_COLLECT 4
#define PIN_SERVO_LIFT 5

#define PIN_8 8
#define PIN_BUZZER 9
#define PIN_10 10

#define PIN_RED 11
#define PIN_GREEN 12
#define PIN_BLUE 13

#define PIN_IR_1 14
#define PIN_IR_2 15
#define PIN_IR_3 16
#define PIN_IR_4 17

#define wire_address 8

byte lastMasterCommand = 0;

int irSensors[] = {0, 0, 0};

