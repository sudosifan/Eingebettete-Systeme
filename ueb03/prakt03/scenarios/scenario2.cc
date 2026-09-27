/** Creates scenario 2
 *  (Task scheduling with deadlines, cf. task sheet 12, task 1)
 */
list<Task*> createScenario2()
{ // Create empty task list
  list<Task*> TL;

  // Create new task T1 and add it to task list
  Task* T1 = new Task("T1", 4, 0, 9);      // name, exec time, release time, deadline
  TL.push_back(T1);

  // ...

  return TL;
}