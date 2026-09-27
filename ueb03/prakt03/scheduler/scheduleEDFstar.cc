
bool topSortForward(const Task* Ta, const Task* Tb)
{ // if there exist a path from Ta to Tb return true otherwise false
  list<Task*> succs = Ta->getSuccessors();
  while (!succs.empty())
  { // Select one successor
    list<Task*>::iterator it = succs.begin();
    Task* T = *it;
    if (T == Tb)
    { return true;
    }
    else
    { // add successors of T also to successor list
      list<Task*> succsT = T->getSuccessors();
      // remove T from list
      succs.erase(it);
      succs.merge(succsT);
    }
  }
  return false;
}

bool topSortBackward(const Task* Ta, const Task* Tb)
{ // if there exist a path from Ta to Tb return true otherwise false
  // ...


  return false;
}

void scheduleEDFstar(list<Task*> scenario)
{ list<Task*> TQ = scenario;
  // ******************************************************************
  // * Create for all tasks in scenario an empty schedule
  // ******************************************************************
  map<Task*, Schedule*> taskSchedules;
  for (list<Task*>::const_iterator it = TQ.begin(); it != TQ.end(); ++it)
  { Task* T = *it;
    Schedule* S = new Schedule(T, SIMULATION_TIME);
    taskSchedules[T] = S;
  }

  // ******************************************************************
  // * Transform release times
  // ******************************************************************
  TQ.sort(topSortForward);
  for (list<Task*>::const_iterator it = TQ.begin(); it != TQ.end(); ++it)
  { Task* T = *it;
    list<Task*> preds = T->getPredecessors();
    if (preds.empty())
    { // nothing to do
      unsigned int tr = T->getReleaseTime();
      cout << "Release time of task " << T->getName() << ", tr=" << tr << " is transformed to tr*=" << tr << endl;
    }
    else
    { // Consider all predecessors
      unsigned int tmax = T->getReleaseTime();
      cout << "Release time of task " << T->getName() << ", tr=" << tmax << " is transformed to tr*=";
      for (list<Task*>::const_iterator it2 = preds.begin(); it2 != preds.end(); ++it2)
      { Task* Tin = *it2;
        unsigned int tc = Tin->getReleaseTime() + Tin->getExecutionTime();
        if (tc > tmax)
        { tmax = tc;
        }
      }
      // Update release time
      T->setReleaseTime(tmax);
      cout << tmax << endl;
    }
  }

  // ******************************************************************
  // * Transform deadlines
  // ******************************************************************
  TQ.sort(topSortBackward);
  for (list<Task*>::const_iterator it = TQ.begin(); it != TQ.end(); ++it)
  { Task* T = *it;
    list<Task*> succs = T->getSuccessors();

    // ...

  }




  // ******************************************************************
  // * Main simulation loop
  // ******************************************************************
  for (unsigned int cycle=0; cycle<SIMULATION_TIME; cycle++)
  {
    // ****************************************************************
    // * Implementation of EDF scheduler
    // ****************************************************************

    // Only if there are tasks in the queue, we have something to do
    if (!TQ.empty())
    { // Sort tasks according to their remaining execution times
      TQ.sort(sortByDeadline);

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
