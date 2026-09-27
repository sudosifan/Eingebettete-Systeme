/** Creates scenario 3
 *  (Task scheduling with deadlines, cf. task sheet 12, task 3)
 */
list<Task*> createScenario3()
{ // Create empty task list
  list<Task*> TL;

  // Create new task T1 and add it to task list
  Task* T1 = new Task("T1", 3, 0, 16);      // name, exec time, release time, deadline
  TL.push_back(T1);

  Task* T2 = new Task("T2", 1, 2, 7);
  TL.push_back(T2);

  Task* T3 = new Task("T3", 6, 0, 8);
  TL.push_back(T3);

  Task* T4 = new Task("T4", 2, 8, 11);
  TL.push_back(T4);

  Task* T5 = new Task("T5", 3, 13, 18);
  TL.push_back(T5);

  return TL;
}
