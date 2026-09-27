#include <stdlib.h>
#include <fstream>
#include <map>
#include <list>

using namespace std;

void printSchedule(map<Task*, Schedule*> ts)
{ for (map<Task*, Schedule*>::const_iterator it = ts.begin(); it != ts.end(); ++it)
  { Schedule* S = it->second;
    cout << (*S);
  }
}

void resetSchedule(map<Task*, Schedule*> ts)
{ for (map<Task*, Schedule*>::const_iterator it = ts.begin(); it != ts.end(); ++it)
  { Schedule* S = it->second;
    S->reset();
  }
}

void generateGantt(map<Task*, Schedule*> ts, const char* filename)
{ //ostream& os = cout;
  ofstream os;
  os.open(filename);

  // Determine number of nodes, number continuous bars in the Gantt chart
  unsigned int numberOfNodes = 0;

  for (map<Task*, Schedule*>::const_iterator it = ts.begin(); it != ts.end(); ++it)
  { Schedule* S = it->second;
    unsigned int d = S->getDuration();
    bool state = false;
    // count all transistion from false to true
    for (unsigned int i=0; i<d; ++i)
    { if (!state && S->isActive(i))
      { // Found 0/1 transistion
        numberOfNodes++;
      }
      state = S->isActive(i);
    }
  }


  os << "NUMBER_OF_NODES { " << numberOfNodes << " }\n\n";


  os << "NODE_NAMES {\n";
  for (map<Task*, Schedule*>::const_iterator it = ts.begin(); it != ts.end(); ++it)
  { Task* T = it->first;
    Schedule* S = it->second;
    unsigned int d = S->getDuration();
    bool state = false;
    for (unsigned int i=0; i<d; ++i)
    { if (!state && S->isActive(i))
      { // Found 0/1 transistion
        os << T->getName() << endl;
      }
      state = S->isActive(i);
    }
  }
  os << "}\n\n";


  os << "NUMBER_OF_RESOURCES { " << ts.size() << " }\n\n";


  os << "RESOURCE_NAMES {\n";
  for (map<Task*, Schedule*>::const_iterator it = ts.begin(); it != ts.end(); ++it)
  { Task* T = it->first;
    os << T->getName() << endl;
  }
  os << "}\n\n";


  os << "RELEASE_TIMES {\n";
  for (map<Task*, Schedule*>::const_iterator it = ts.begin(); it != ts.end(); ++it)
  { Task* T = it->first;
    os << T->getReleaseTime() << endl;
  }
  os << "}\n\n";


  os << "DEADLINES {\n";
  for (map<Task*, Schedule*>::const_iterator it = ts.begin(); it != ts.end(); ++it)
  { Task* T = it->first;
    if (T->getPeriod()>0)
    { os << (T->getDeadline() % T->getPeriod()) << endl;
    }
    else
    { os << T->getDeadline() << endl;
    }
  }
  os << "}\n\n";


  os << "PERIODS {\n";
  for (map<Task*, Schedule*>::const_iterator it = ts.begin(); it != ts.end(); ++it)
  { Task* T = it->first;
    os << T->getPeriod() << endl;
  }
  os << "}\n\n";


  os << "RESOURCE_MAP {\n";
  unsigned int n = 1;
  for (map<Task*, Schedule*>::const_iterator it = ts.begin(); it != ts.end(); ++it)
  { Schedule* S = it->second;
    unsigned int d = S->getDuration();
    bool state = false;
    for (unsigned int i=0; i<d; ++i)
    { if (!state && S->isActive(i))
      { // Found 0/1 transistion
        os << n << endl;
      }
      state = S->isActive(i);
    }
    n++;
  }
  os << "}\n\n";


  os << "START_TIME {\n";
  for (map<Task*, Schedule*>::const_iterator it = ts.begin(); it != ts.end(); ++it)
  { Schedule* S = it->second;
    unsigned int d = S->getDuration();

    unsigned int startTime;

    bool foundBegin = false;
    for (unsigned int i=0; i<d; i++)
    { if (S->isActive(i) && !foundBegin)
      { foundBegin = true;
        startTime = i;
      }
      if (!S->isActive(i) && foundBegin)
      { foundBegin = false;
        os << startTime << endl;
      }
      if (S->isActive(i) && i==d-1)
      { os << startTime << endl;
      }
    }

  }
  os << "}\n\n";


  os << "END_TIME {\n";
  for (map<Task*, Schedule*>::const_iterator it = ts.begin(); it != ts.end(); ++it)
  { Schedule* S = it->second;
    unsigned int d = S->getDuration();

    unsigned int endTime;

    bool foundBegin = false;
    for (unsigned int i=0; i<d; i++)
    { if (S->isActive(i) && !foundBegin)
      { foundBegin = true;
      }
      if (!S->isActive(i) && foundBegin)
      { endTime = i;
        foundBegin = false;

        os << endTime << endl;
      }
      if (S->isActive(i) && i==d-1)
      { endTime = i;
        os << endTime << endl;
      }
    }

  }
  os << "}\n\n";

  os.close();
}

/** Updates a task queue TQ for a given scenario in dependence on the simulation
 *  time given by cycle c.
 */
void updateTaskQueue(list<Task*>& TQ, const list<Task*>& scenario, unsigned int c)
{
  // Iterate over entire scenario
  for (list<Task*>::const_iterator it = scenario.begin(); it != scenario.end(); ++it)
  { Task* T = *it;

    // If task T is released at cycle c, add it to the task queue
    unsigned int d = T->getDeadline();
    unsigned int p = T->getPeriod();
    if (p>0)
    { if (T->getReleaseTime()==(c%p))
      { T->setRemainingExecutionTime(T->getExecutionTime());
        if (c!=0) T->setDeadline(d+p);
        TQ.push_back(T);
      }
    }
    else
    { if (T->getReleaseTime()==c)
      { TQ.push_back(T);
      }
    }
  }
}
