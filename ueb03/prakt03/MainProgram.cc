/**
 *******************************************************************************
 * \file MainProgram.cc
 *
 * \brief Test program.
 *
 * \attention   Copyright (C) 2009-2010 by University of Erlangen-Nuremberg,
 *              Department of Hardware-Software-Co-Design, Germany.
 *              All rights reserved.
 *
 * \author Frank Hannig
 *
 * $Id:  $
 *
 *******************************************************************************
 */


#include "Task.h"
#include "Schedule.h"
#include "HelpFunctions.cc"
#include "scenarios/scenario1.cc"
#include "scenarios/scenario2.cc"
#include "scenarios/scenario3.cc"
#include "scenarios/scenario5.cc"
#include "scenarios/scenario6.cc"
#include "scenarios/scenario7.cc"

const unsigned int SIMULATION_TIME  = 81;


/** *******************************************************************
 * Computation of response times
 * ********************************************************************
 */
void computeResponseTimes(map<Task*, Schedule*> ts)
{
  for (map<Task*, Schedule*>::const_iterator it = ts.begin(); it != ts.end(); ++it)
  { Task* T = it->first;
    Schedule* S = it->second;

    // Calculate response time ta of task T
    // ...
    cout << "The response time of task " << T->getName() << " is " << "???" << endl;
  }
  cout << "The average response time is " << "???" << endl;
}

/** *******************************************************************
 * Computation of waiting times
 * ********************************************************************
 */
void computeWaitingTimes(map<Task*, Schedule*> ts)
{
  for (map<Task*, Schedule*>::const_iterator it = ts.begin(); it != ts.end(); ++it)
  { Task* T = it->first;
    Schedule* S = it->second;

    // Calculate waiting time tw of task T
    cout << "The waiting time of task " << T->getName() << " is " << "???" << endl;
  }
  cout << "The average waiting time is " << "???" << endl;
}

#include "scheduler/scheduleFCFS.cc"
#include "scheduler/scheduleSJF.cc"
#include "scheduler/scheduleSRTN.cc"
#include "scheduler/schedulePB.cc"
#include "scheduler/scheduleRR.cc"
#include "scheduler/scheduleEDD.cc"
#include "scheduler/scheduleEDF.cc"
#include "scheduler/scheduleEDFstar.cc"
#include "scheduler/scheduleDM.cc"



/** *******************************************************************
 *
 *  M A I N   P R O G R A M
 *
 * ********************************************************************
 */
int main(int argc, const char** argv)
{
#ifdef FCFS
#define PART1
#endif
#ifdef SJF
#define PART1
#endif
#ifdef SRTN
#define PART1
#endif
#ifdef PB
#define PART1
#endif
#ifdef RR
#define PART1
#endif

#ifdef EDD
#define PART2
#endif
#ifdef EDF1
#define PART2
#endif
#ifdef EDF2
#define PART2
#endif
#ifdef EDF_STAR
#define PART2
#endif

#ifdef EDF3
#define PART3
#endif
#ifdef DM
#define PART3
#endif

#ifdef PART1
  cout << "\n\n\33[1m***********************************************************************\n";
  cout <<     "***                                                                 ***\n";
  cout <<     "*** P A R T   I                                                     ***\n";
  cout <<     "***                                                                 ***\n";
  cout <<     "*** Task scheduling \33[1;4mwithout\33[0m\33[1m deadlines                               ***\n";
  cout <<     "***                                                                 ***\n";
  cout <<     "***********************************************************************\33[0m\n";
#endif

  list<Task*> scenario;
  string input;
#ifdef FCFS
  cout << "\n\n***********************************************************************\n";
  cout <<     "*** Scheduling strategy: First Come First Served (FCFS)             ***\n";
  cout <<     "***********************************************************************\n";
  scenario = createScenario1();
  scheduleFCFS(scenario);
  cout << "\nPress <return> to continue\n"; getline(cin, input);
#endif

#ifdef SJF
  cout << "\n\n***********************************************************************\n";
  cout <<     "*** Scheduling strategy: Shortest Job First (SJF)                   ***\n";
  cout <<     "***********************************************************************\n";
  scenario = createScenario1();
  scheduleSJF(scenario);
  cout << "\nPress <return> to continue\n"; getline(cin, input);
#endif

#ifdef SRTN
  cout << "\n\n***********************************************************************\n";
  cout <<     "*** Scheduling strategy: Shortest Remaining Time Next (SRTN)        ***\n";
  cout <<     "***********************************************************************\n";
  scenario = createScenario1();
  scheduleSRTN(scenario);
  cout << "\nPress <return> to continue\n"; getline(cin, input);
#endif

#ifdef PB
  cout << "\n\n***********************************************************************\n";
  cout <<     "*** Scheduling strategy: Priority-based (PB)                        ***\n";
  cout <<     "***********************************************************************\n";
  scenario = createScenario1();
  schedulePB(scenario);
  cout << "\nPress <return> to continue\n"; getline(cin, input);
#endif

#ifdef RR
  cout << "\n\n***********************************************************************\n";
  cout <<     "*** Scheduling strategy: Round-Robin (RR) with time quantum 5       ***\n";
  cout <<     "***********************************************************************\n";
  scenario = createScenario1();
  scheduleRR(scenario, 5);
  cout << "\nPress <return> to continue\n"; getline(cin, input);
  cout << "\n\n***********************************************************************\n";
  cout <<     "*** Scheduling strategy: Round-Robin (RR) with time quantum 3       ***\n";
  cout <<     "***********************************************************************\n";
  scenario = createScenario1();
  scheduleRR(scenario, 3);
  cout << "\nPress <return> to continue\n"; getline(cin, input);
  cout << "\n\n***********************************************************************\n";
  cout <<     "*** Scheduling strategy: Round-Robin (RR) with time quantum 2       ***\n";
  cout <<     "***********************************************************************\n";
  scenario = createScenario1();
  scheduleRR(scenario, 2);
  cout << "\nPress <return> to continue\n"; getline(cin, input);
  cout << "\n\n***********************************************************************\n";
  cout <<     "*** Scheduling strategy: Round-Robin (RR) with time quantum 1       ***\n";
  cout <<     "***********************************************************************\n";
  scenario = createScenario1();
  scheduleRR(scenario, 1);
  cout << "\nPress <return> to continue\n"; getline(cin, input);
#endif


#ifdef PART2
  cout << "\n\n\33[1m***********************************************************************\n";
  cout <<     "***                                                                 ***\n";
  cout <<     "*** P A R T   I I                                                   ***\n";
  cout <<     "***                                                                 ***\n";
  cout <<     "*** Task scheduling \33[1;4mwith\33[0m\33[1m deadlines                                  ***\n";
  cout <<     "***                                                                 ***\n";
  cout <<     "***********************************************************************\33[0m\n";
#endif

#ifdef EDD
  cout << "\n\n***********************************************************************\n";
  cout <<     "*** Scheduling strategy: Earliest Due Date (EDD)                    ***\n";
  cout <<     "***********************************************************************\n";
  scenario = createScenario2();
  scheduleEDD(scenario);
  cout << "\nPress <return> to continue\n"; getline(cin, input);
#endif

#ifdef EDF1
  cout << "\n\n***********************************************************************\n";
  cout <<     "*** Scheduling strategy: Earliest Deadline First (EDF)              ***\n";
  cout <<     "***********************************************************************\n";
  scenario = createScenario3();
  scheduleEDF(scenario);
  cout << "\nPress <return> to continue\n"; getline(cin, input);
#endif

#ifdef EDF2
  cout << "\n\n***********************************************************************\n";
  cout <<     "*** Scheduling strategy: Earliest Deadline First (EDF)              ***\n";
  cout <<     "***********************************************************************\n";
  scenario = createScenario5();
  scheduleEDF(scenario);
  cout << "\nPress <return> to continue\n"; getline(cin, input);
#endif

#ifdef EDF_STAR
  cout << "\n\n***********************************************************************\n";
  cout <<     "*** Scheduling strategy: Earliest Deadline First Star (EDF*)        ***\n";
  cout <<     "***********************************************************************\n";
  scenario = createScenario5();
  scheduleEDFstar(scenario);
  cout << "\nPress <return> to continue\n"; getline(cin, input);
#endif



#ifdef PART3
  cout << "\n\n\33[1m***********************************************************************\n";
  cout <<     "***                                                                 ***\n";
  cout <<     "*** P A R T   I I I                                                 ***\n";
  cout <<     "***                                                                 ***\n";
  cout <<     "*** Scheduling of \33[1;4mperiodic\33[0m\33[1m tasks                                    ***\n";
  cout <<     "***                                                                 ***\n";
  cout <<     "***********************************************************************\33[0m\n";
#endif

#ifdef EDF3
  cout << "\n\n***********************************************************************\n";
  cout <<     "*** Scheduling strategy: Earliest Deadline First (EDF)              ***\n";
  cout <<     "***********************************************************************\n";
  scenario = createScenario6();
  scheduleEDF(scenario);
  cout << "\nPress <return> to continue\n"; getline(cin, input);
#endif

#ifdef DM
  cout << "\n\n***********************************************************************\n";
  cout <<     "*** Scheduling strategy: Deadline-Monotonic (DM)                    ***\n";
  cout <<     "***********************************************************************\n";
  scenario = createScenario7();
  scheduleDM(scenario);
  cout << "\nPress <return> to continue\n"; getline(cin, input);
#endif

  return 0;
}
