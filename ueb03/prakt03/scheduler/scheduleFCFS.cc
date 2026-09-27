bool sortByReleaseTime(const Task* Tl, const Task* Tr)
{ return (Tl->getReleaseTime() < Tr->getReleaseTime());
}

void scheduleFCFS(list<Task*> scenario)
{ // ******************************************************************
  // * Create an empty schedule for all tasks in the scenario
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
  Task* T = NULL;
  list<Task*>::iterator it;
  for (unsigned int cycle=0; cycle<SIMULATION_TIME; cycle++)
  { // Update the task queue since new tasks might have been released
    updateTaskQueue(TQ, scenario, cycle);
    // Sort tasks according to their release times
    TQ.sort(sortByReleaseTime);

    // ****************************************************************
    // * Implementation of FCFS scheduler
    // ****************************************************************

    // Only if there are tasks in the queue or an active task,
    // we have something to do
    if ((!TQ.empty()) || (T!=NULL))
    { if (T == NULL)
      { // If there is no active task, dispatch the first task from the queue
        it = TQ.begin();
        T = *it;
      }

      // Schedule task in this cycle
      Schedule* S = taskSchedules[T];
      S->active(cycle);

      // Get remaining execution time of task T
      unsigned int d = T->getRemainingExecutionTime();
      if (d==1)
      { // The task has been totally executed and can be removed from the task queue
        TQ.erase(it);
        T = NULL;
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
