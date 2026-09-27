/** Creates a scenario that defines the occurence of several tasks
 *  (Task scheduling without deadlines, cf. task sheet 11, task 1)
 */
list<Task*> createScenario1()
{ // Create empty task list
  list<Task*> TL;

  // Create new task T1 and add it to task list
  Task* T1 = new Task("T1", 20, 0);      // name, exec time, release time
  T1->setPriority(2);
  TL.push_back(T1);

  Task* T2 = new Task("T2", 5, 0);
  T2->setPriority(1);
  TL.push_back(T2);

  Task* T3 = new Task("T3", 10, 5);
  T3->setPriority(4);
  TL.push_back(T3);

  Task* T4 = new Task("T4", 5, 20);
  T4->setPriority(3);
  TL.push_back(T4);

  Task* T5 = new Task("T5", 20, 50);
  T5->setPriority(6);
  TL.push_back(T5);

  Task* T6 = new Task("T6", 5, 50);
  T6->setPriority(7);
  TL.push_back(T6);

  return TL;
}