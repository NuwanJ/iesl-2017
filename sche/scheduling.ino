



int reachT[]  = {20 , 10 , 20 , 50, 5, 10};
int reachTime[] = {0, 0, 0, 0 , 0 , 0};
int subPathTime = 5;


int schedule(int task1, int  task2, int task3) {

  int totalT = 0; // Time until first junction
  int p[] = {10 , 10 , 10};
  int q[] = {10 , 10 , 10};
  int task = 0;
  int taskTime[] = {0 , 0 , 0};
  int temp;
  int timeUntilFirstBox  = 0;
  int timeAfterLastBox = 0;

  // Calculate timespan
  reachTime[0] = reachT[0];
  for (int i = 1; i < 6; i++) {
    reachTime[i] =  reachTime[i - 1]  + reachT[i];
  }

  printArr("times", reachT, 6);
  printArr("reachTime", reachTime, 6);

  // Now take task 1 and calculate time taken _______________________________________________________________________________________________________________

  for (int i = 0; i < 6; i++) {
    if (p[task] == 10 && layout[i] == task1) {
      p[task] = i;            // Picking Junction
    } else if (layout[i] == task1 + 3) {
      q[task] = i;            // Dropping Junction
      break;
    }
  }

  // Now we have picking and dropping points. Now need to calculate driving time

  timeUntilFirstBox =  reachTime[p[task]] + subPathTime;           // Time until box path junction

  totalT += timeUntilFirstBox;
  Serial.print("Total: "); Serial.println(totalT);

  taskTime[task] = subPathTime + (reachTime[q[task]] - reachTime[p[task]]) + subPathTime; // Time between pick and drop

  if (debug) {

    Serial.println("Task0: ");
    Serial.print("H"); Serial.print(" -> "); Serial.print(p[task]); Serial.print(" | "); Serial.println(timeUntilFirstBox);
    Serial.println();
    Serial.println("Task1: ");
    Serial.print(p[task]); Serial.print(" -> "); Serial.print(q[task]); Serial.print(" | "); Serial.println(taskTime[task]);
  }
  totalT += taskTime[0];
  Serial.print("Total: "); Serial.println(totalT);

  // Now take task 2 and calculate time taken _______________________________________________________________________________________________________________

  task = 1;
  for (int i = 0; i < 6; i++) {
    if (p[task] == 10 && layout[i] == task2) {
      p[task] = i;            // Picking Junction
    } else if (layout[i] == task2 + 3) {
      q[task] = i;            // Dropping Junction
      break;
    }
  }

  // Now we have picking and dropping points. Now need to calculate driving time

  temp = subPathTime + (reachTime[q[task - 1]] - reachTime[p[task]]) + subPathTime; // Time before pick
  taskTime[task] += subPathTime + (reachTime[q[task]] - reachTime[p[task]]) + subPathTime;  // Time between pick(turn to subpath) and drop

  if (debug) {
    Serial.println();
    Serial.println("Task2: ");
    Serial.print(p[task]); Serial.print(" <- "); Serial.print(q[task - 1]); Serial.print(" | "); Serial.println(temp);
    Serial.print(p[task]); Serial.print(" -> "); Serial.print(q[task]); Serial.print(" | "); Serial.println(taskTime[task]);
  }
  totalT += taskTime[1] + temp;
  Serial.print("Total: "); Serial.println(totalT);


  // Now take task 3 and calculate time taken _______________________________________________________________________________________________________________
  task = 2;
  for (int i = 0; i < 6; i++) {
    if (p[task] == 10 && layout[i] == task3) {
      p[task] = i;            // Picking Junction
    } else if (layout[i] == task3 + 3) {
      q[task] = i;            // Dropping Junction
      break;
    }
  }

  // Now we have picking and dropping points. Now need to calculate driving time

  temp = subPathTime + (reachTime[q[task - 1]] - reachTime[p[task]]) + subPathTime; // Time before pick
  taskTime[task] += subPathTime + (reachTime[q[task]] - reachTime[p[task]]) + subPathTime;  // Time between pick(turn to subpath) and drop

  if (debug) {
    Serial.println();
    Serial.println("Task3: ");
    Serial.print(p[task]); Serial.print(" <- "); Serial.print(q[task - 1]); Serial.print(" | "); Serial.println(temp);
    Serial.print(p[task]); Serial.print(" -> "); Serial.print(q[task]); Serial.print(" | "); Serial.println(taskTime[task]);
  }
  totalT += taskTime[2] + temp;
  Serial.print("Total: "); Serial.println(totalT);

  timeAfterLastBox = reachTime[q[task]] + subPathTime;

  if (debug) {
    Serial.println();
    Serial.println("Task4: ");
    Serial.print("H"); Serial.print(" <- "); Serial.print(q[task]); Serial.print(" | "); Serial.println(timeAfterLastBox);
  }

  timeAfterLastBox = reachTime[q[task]] + subPathTime;
  totalT += timeAfterLastBox;
  Serial.print("Total: "); Serial.println(totalT);

  if (debug) {
    Serial.println();
    Serial.println("Summary: ");
    Serial.print("Total Time : "); Serial.println(totalT);

  }
  printArr("p: ", p, 3);
  printArr("q: ", q, 3);

  return totalT;
}




void printArr(String arrName, int* arr, int n) {
  Serial.print(">> ");
  Serial.print(arrName);
  Serial.print(" | ");

  for (int i = 0; i < n; i++) {
    Serial.print(arr[i]);
    Serial.print(" ");
  }
  Serial.println("");
}



