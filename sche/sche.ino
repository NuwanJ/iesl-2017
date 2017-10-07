#include "define.h";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  int t = 0;
  debug = 0;

  printArr("Layout", layout, 6);

  t = schedule(Bx0, Bx3, Bx5);
  Serial.print("0 -> 3 -> 5    :: "); Serial.println(t); Serial.println();

  t = schedule(Bx0, Bx5, Bx3);
  Serial.print("0 -> 5 -> 3    :: "); Serial.println(t); Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:

}
