#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here


// Add your implementation of schedule() and other helper functions here



bool backTrack(
  const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    std::vector<size_t>& shiftsAssigned,
    size_t day,
    size_t slot
){

  if(day == avail.size()){
    return true;
  }

  if(slot == dailyNeed){
    return backTrack(avail,dailyNeed,maxShifts,sched,shiftsAssigned,day+1,0);
  }

  for(Worker_T worker = 0; worker < avail[0].size(); worker++){
    if(avail[day][worker] && shiftsAssigned[worker] < maxShifts &&
    find(sched[day].begin(), sched[day].end(), worker) == sched[day].end()){
      sched[day].push_back(worker);
      shiftsAssigned[worker]++;

      if (backTrack(avail, dailyNeed, maxShifts, sched, shiftsAssigned, day, slot + 1)) {
                return true;
            }
      sched[day].pop_back();
      shiftsAssigned[worker]--;
    }
  }

  return false;
}




bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    sched.resize(avail.size(), vector<Worker_T>());

    std::vector<size_t> shiftsAssigned(avail[0].size(),0);
    return backTrack(avail, dailyNeed, maxShifts, sched, shiftsAssigned,0,0);
}

