/** Creates scenario 5
 *  (Task scheduling with deadlines, cf. task sheet 12, task 5)
 */
list<Task*> createScenario5()
{ // Create empty task list
  list<Task*> TL;

  // Create new task T1 and add it to task list
  Task* A = new Task("A", 2, 0, 4);      // name, exec time, release time, deadline
  TL.push_back(A);

  Task* B = new Task("B", 2, 1, 10);
  TL.push_back(B);

  Task* C = new Task("C", 2, 1, 8);
  TL.push_back(C);

  Task* D = new Task("D", 2, 3, 6);
  TL.push_back(D);

  Task* E = new Task("E", 2, 7, 10);
  TL.push_back(E);

  Task* F = new Task("F", 2, 9, 12);
  TL.push_back(F);

  // Data dependencies
  // ...

  return TL;
}
