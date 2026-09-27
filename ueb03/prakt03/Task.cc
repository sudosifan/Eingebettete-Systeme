/**
 *******************************************************************************
 * \file Task.cc
 *
 * \brief Implementation of class Task.
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

/** Default constructor.
 *  Creates an 'empty' Task.
 */
Task::Task()
{ construct("", 0, 0, -1, 0);
}

/** Constructor.
 */
Task::Task(std::string name)
{ construct(name, 0, 0, -1, 0);
}

/** Constructor.
 */
Task::Task(std::string name, unsigned int execTime)
{ construct(name, execTime, 0, -1, 0);
}

/** Constructor.
 */
Task::Task(std::string name, unsigned int execTime, unsigned int releaseTime)
{ construct(name, execTime, releaseTime, -1, 0);
}

/** Constructor.
 */
Task::Task(std::string name, unsigned int execTime, unsigned int releaseTime, int deadline)
{ construct(name, execTime, releaseTime, deadline, 0);
}

/** Constructor.
 */
Task::Task(std::string name, unsigned int execTime, unsigned int releaseTime, int deadline, unsigned int period)
{ construct(name, execTime, releaseTime, deadline, period);
}

/** Copy constructor.
 */
Task::Task(const Task& T)
{ construct(T.name, T.execTime, T.releaseTime, T.deadline, T.period);
}

/** Assignment operator.
 */
Task& Task::operator= (const Task& T)
{ // Self assignment => nothing to do
  if (&T == this)
  { return *this;
  }
  construct(T.name, T.execTime, T.releaseTime, T.deadline, T.period);
  return *this;
}

std::ostream& operator<< (std::ostream& os, const Task& T)
{ os << T.name;
  return os;
}


/** Destructor.
 */
Task::~Task()
{
}

/** Helper function that is used by most constructors, which does the
 *  actual work.
 */
void Task::construct(std::string name, unsigned int execTime, unsigned int releaseTime, int deadline, unsigned int period)
{ this->name                 = name;
  this->execTime             = execTime;
  this->remainingExecTime    = execTime;
  this->releaseTime          = releaseTime;
  this->deadline             = deadline; // -1 = no deadline
  this->period               = period;   // 0 = no period
  priority                   = 0;
}


/** Overload the < operator.
 */
bool Task::operator< (const Task& Tr) const
{ return (priority < Tr.priority);
}


void Task::addSuccessor(Task* T)
{ // Check if task is already in list
  std::list<Task*>::const_iterator it = find(successorList.begin(), successorList.end(), T);
  if (it == successorList.end())
  { // if not, add it
    successorList.push_back(T);
    T->predecessorList.push_back(this);
  }
}

std::list<Task*> Task::getSuccessors() const
{ return successorList;
}

void Task::addPredecessor(Task* T)
{ // Check if task is already in list
  std::list<Task*>::const_iterator it = find(predecessorList.begin( ), predecessorList.end( ), T);
  if (it == predecessorList.end())
  { // if not, add it
    predecessorList.push_back(T);
    T->successorList.push_back(this);
  }
}

std::list<Task*> Task::getPredecessors() const
{ return predecessorList;
}

int Task::getPriority() const
{ return priority;
}

void Task::setPriority(int p)
{ priority = p;
}

std::string Task::getName() const
{ return name;
}

unsigned int Task::getExecutionTime() const
{ return execTime;
}

unsigned int Task::getRemainingExecutionTime() const
{ return remainingExecTime;
}

void Task::setRemainingExecutionTime(unsigned int t)
{ remainingExecTime = t;
}

unsigned int Task::getReleaseTime() const
{ return releaseTime;
}

void Task::setReleaseTime(unsigned int t)
{ releaseTime = t;
}

int Task::getDeadline() const
{ return deadline;
}

void Task::setDeadline(int d)
{ if (d <= -1)
  { deadline = -1;
  }
  else
  { deadline = d;
  }
}

unsigned int Task::getPeriod() const
{ return period;
}
