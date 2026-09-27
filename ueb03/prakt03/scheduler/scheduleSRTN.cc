bool sortByRemainingExecutionTime(const Task* Tl, const Task* Tr)
{ return (true);  // Change this line!
}

void scheduleSRTN(list<Task*> scenario)
{ // ******************************************************************
  // * Create for all tasks in scenario an empty schedule
  // ******************************************************************
  map<Task*, Schedule*> taskSchedules;
  for (list<Task*>::const_iterator it = scenario.begin(); it != scenario.end(); ++it)
  { Task* T = *it;
    Schedule* S = new Schedule(T, SIMULATION_TIME);
    taskSchedules[T] = S;
  }


  // ******************************************************************
  // * Create an empty task queue
  // ******************************************************************
  list<Task*> TQ;


  // ******************************************************************
  // * Main simulation loop
  // ******************************************************************
  for (unsigned int cycle=0; cycle<SIMULATION_TIME; cycle++)
  { // Update the task queue since new tasks might have been released
    updateTaskQueue(TQ, scenario, cycle);


    // ****************************************************************
    // * Implementation of SRTN scheduler
    // ****************************************************************

    // Only if there are tasks in the queue, we have something to do
    if (!TQ.empty())
    { // Sort tasks according to their remaining execution times
      TQ.sort(sortByRemainingExecutionTime);

      // Get first task T
      list<Task*>::iterator it = TQ.begin();
      Task* T = *it;

      // Schedule task in this cycle
      Schedule* S = taskSchedules[T];
      S->active(cycle);

      // Get remaining execution time of task T 
      unsigned int d = T->getRemainingExecutionTime();
      if (d==1)
      { // The task has been totally executed and can be removed from the task queue
         TQ.erase(it);
      }
      else
      { // Decrement the remaining execution time by one cycle
        T->setRemainingExecutionTime(d-1);
      }
    }
  }
  printSchedule(taskSchedules);
  generateGantt(taskSchedules, "schedule.txt");

  computeResponseTimes(taskSchedules);
  computeWaitingTimes(taskSchedules);
}
