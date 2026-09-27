/**
 *******************************************************************************
 * \file Schedule.cc
 *
 * \brief Implementation of class Schedule.
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

#include "Schedule.h"

/** Constructor.
 */
Schedule::Schedule(Task* T, unsigned int duration)
{ this->T = T;
  this->duration = duration;
  schedule = new bool[duration];

  // Initilaize all potential time steps with false
  for (unsigned int i=0; i<duration; i++)
  { schedule[i] = false;
  }
}


/** Copy constructor.
 */
Schedule::Schedule(const Schedule& s)
{ this->T = s.T;
  this->duration = s.duration;
  schedule = new bool(duration);
  for (unsigned int i=0; i<duration; i++)
  { schedule[i] = s.schedule[i];
  }
}

/** Assignment operator.
 */
Schedule& Schedule::operator= (const Schedule& s)
{ // Self assignment => nothing to do
  if (&s == this)
  { return *this;
  }
  this->T = s.T;
  this->duration = s.duration;
  schedule = new bool(duration);
  for (unsigned int i=0; i<duration; i++)
  { schedule[i] = s.schedule[i];
  }
  return *this;
}


std::ostream& operator<< (std::ostream& os, const Schedule& s)
{ unsigned int startTime;
  unsigned int endTime;

  bool foundBegin = false;

  std::cout << "Schedule of Task " << s.T->getName() << ": ";

  for (unsigned int i=0; i<s.duration; i++)
  { if (s.schedule[i] && !foundBegin)
    { foundBegin = true;
      startTime = i;
    }
    if (!s.schedule[i] && foundBegin)
    { endTime = i;
      foundBegin = false;

      std::cout << "[" << startTime;
      if (startTime != endTime)
      { std::cout << ", " << endTime << ") ";
      }
      else
      { std::cout << "] ";
      }
    }
    if (s.schedule[i] && i==s.duration-1)
    { endTime = i+1;
      std::cout << "[" << startTime;
      if (startTime != endTime)
      { std::cout << ", " << endTime;
      }
      std::cout << ") ";
    }
  }
  std::cout << std::endl;
  return os;
}

void Schedule::active(unsigned int startTime)
{ active(startTime, startTime);
}

void Schedule::active(unsigned int startTime, unsigned int endTime)
{ assert(startTime<duration);
  assert(endTime<duration);
  for (unsigned int i=startTime; i<=endTime; i++)
  { schedule[i] = true;
  }
}

void Schedule::reset()
{ for (unsigned int i=0; i<=duration; ++i)
  { schedule[i] = false;
  }
}

/** Destructor.
 */
Schedule::~Schedule()
{ delete[] schedule;
}

unsigned int Schedule::getDuration() const
{ return duration;
}

bool Schedule::isActive(unsigned int i) const
{ assert(i<duration);
  return schedule[i];
}

unsigned int Schedule::getBeginTime() const
{ for (unsigned int i=0; i<duration; i++)
  { if (schedule[i])
    { return (i);
    }
  }
  return 0;
}

unsigned int Schedule::getEndTime() const
{ for (unsigned int i=duration-1; i>0; i--)
  { if (schedule[i])
    { return (i+1);
    }
  }
  return 0;
}