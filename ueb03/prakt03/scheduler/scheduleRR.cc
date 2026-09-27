bool sortByName(const Task* Tl, const Task* Tr)
{ return (Tl->getName() < Tr->getName());
}

void scheduleRR(list<Task*> scenario, unsigned int timeQuantum)
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
  Task* T = NULL;
  list<Task*>::iterator it = TQ.end();
  unsigned int counter = 0; // count since how long a task is active
  for (unsigned int cycle=0; cycle<SIMULATION_TIME; cycle++)
  { // Update the task queue since new tasks might have been released
    updateTaskQueue(TQ, scenario, cycle);
    // Sort tasks according to their release times
    TQ.sort(sortByName);


    // ****************************************************************
    // * Implementation of RR scheduler
    // ****************************************************************

    // Only if there are tasks in the queue or an active task,
    // we have something to do
    if ((!TQ.empty()) || (T!=NULL))
    { if (T == NULL)
      { // If there is no active task, dispatch the next one from the queue
        if (it == TQ.end())
        { it = TQ.begin();
        }
        T = *it;
      }

      // Schedule task in this cycle
      Schedule* S = taskSchedules[T];
      S->active(cycle);
      counter++;

      // Get remaining execution time of task T 
      unsigned int d = T->getRemainingExecutionTime();
      if (d==1)
      { // The task has been totally executed and can be removed from the task queue
         it = TQ.erase(it);
         T = NULL;
         counter = 0;
      }
      else
      { // Decrement the remaining execution time by one cycle
        T->setRemainingExecutionTime(d-1);
      }

      if (counter>=timeQuantum)
      { // stop currently running task
        T = NULL;
        counter = 0;
        // and select the next waiting one
        it++;
        if (it == TQ.end())
        { it = TQ.begin();
        }
      }
    }
  }
  printSchedule(taskSchedules);
  generateGantt(taskSchedules, "schedule.txt");

  computeResponseTimes(taskSchedules);
  computeWaitingTimes(taskSchedules);
}
