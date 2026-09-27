/**
 *******************************************************************************
 * \file Schedule.h
 *
 * \brief Class definition: Schedule
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
#ifndef _SCHEDULE_H
#define _SCHEDULE_H

#include <iostream>
#include <string>
#include <vector>
#include <assert.h>

#include "Task.h"

class Schedule
{ protected:
    Task* T;
    unsigned int duration;
    bool* schedule;

  public:
    Schedule(Task*, unsigned int);
    Schedule(const Schedule&);
    Schedule& operator= (const Schedule&);
    friend std::ostream& operator<< (std::ostream&, const Schedule&);
    ~Schedule();

  public:
    void active(unsigned int);
    void active(unsigned int, unsigned int);
    unsigned int getDuration() const;
    bool isActive(unsigned int) const;
    void reset();
    unsigned int getBeginTime() const;
    unsigned int getEndTime() const;
};

#endif // _SCHEDULE_H
