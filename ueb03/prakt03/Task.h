/**
 *******************************************************************************
 * \file Task.h
 *
 * \brief Class definition: Task
 *
 * \attention   Copyright (C) 2009-2010 by University of Erlangen-Nuremberg,
 *              Department of Hardware-Software-Co-Design, Germany.
 *              All rights reserved.
 *
 * \author Frank Hannig
 *
 * $Id:  $
 *
 ********************************************************************************
 */
#ifndef _TASK_H
#define _TASK_H

#include <iostream>
#include <string>
#include <list>
#include <algorithm>

class Task
{ protected:
    std::string name;
    unsigned int execTime;
    unsigned int remainingExecTime;
    unsigned int releaseTime;
    int deadline;
    unsigned int period;
    std::list<Task*> successorList;
    std::list<Task*> predecessorList;
    int priority;

  public:
    Task();
    Task(std::string name);
    Task(std::string name, unsigned int execTime);
    Task(std::string name, unsigned int execTime, unsigned int releaseTime);
    Task(std::string name, unsigned int execTime, unsigned int releaseTime, int deadline);
    Task(std::string name, unsigned int execTime, unsigned int releaseTime, int deadline, unsigned int period);
    Task(const Task&);
    Task& operator= (const Task&);
    bool operator< (const Task&) const;
    friend std::ostream& operator<< (std::ostream&, const Task&);
    ~Task();

  protected:
    void construct(std::string name, unsigned int execTime, unsigned int releaseTime, int deadline, unsigned int period);

  public:
    void addSuccessor(Task*);
    std::list<Task*> getSuccessors() const;
    void addPredecessor(Task*);
    std::list<Task*> getPredecessors() const;
    int getPriority() const;
    void setPriority(int);
    std::string getName() const;
    unsigned int getExecutionTime() const;
    unsigned int getRemainingExecutionTime() const;
    void setRemainingExecutionTime(unsigned int);
    unsigned int getReleaseTime() const;
    void setReleaseTime(unsigned int);
    int getDeadline() const;
    void setDeadline(int);
    unsigned int getPeriod() const;
};




#endif // _TASK_H
