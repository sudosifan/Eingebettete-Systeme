void scheduleEDF(list<Task*> scenario)
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
    // * Implementation of EDF scheduler
    // ****************************************************************

    // ...



    // ...
  }
  printSchedule(taskSchedules);
  generateGantt(taskSchedules, "schedule.txt");

  computeResponseTimes(taskSchedules);
  computeWaitingTimes(taskSchedules);
}
