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

// Helper Function to help schedule 
bool scheduleHelper( const AvailabilityMatrix& avail, const size_t dailyNeed,
    const size_t maxShifts, DailySchedule& sched, 
    std::vector<size_t>& workerShifts, size_t day, size_t slot );


// Add your implementation of schedule() and other helper functions here

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

    size_t n = avail.size(); // the number of days 
    size_t k = avail[0].size(); // the number of workers 

    // Clear and reinitialize the schedule with INVALID_IDs
    sched = DailySchedule(n, std::vector<Worker_T>(dailyNeed, INVALID_ID));

    // Track how many shifts each worker has worked
    std::vector<size_t> workerShifts(k, 0);

    // Call the recursive helper function starting at day 0, slot 0
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, workerShifts, 0, 0);

}

// Helper Function to help schedule 
bool scheduleHelper( const AvailabilityMatrix& avail, const size_t dailyNeed,
    const size_t maxShifts, DailySchedule& sched,
    std::vector<size_t>& workerShifts, size_t day, size_t slot )
{
    // Base case: all days have been scheduled
    if (day == sched.size()) {
      return true;
    }

    // Made to assign each worker to the current slot
    for (size_t worker = 0; worker < avail[0].size(); ++worker) {
      // Check if worker is available on the current day
      if (!avail[day][worker]) {
        continue;
      }
      // Check if worker hasn't exceeded max shifts
      if (workerShifts[worker] >= maxShifts) {
        continue;
      }
      // Check if worker is already assigned on this day
      if (find(sched[day].begin(), sched[day].end(), worker) != sched[day].end()) { 
        continue;
      }

      // Assign the worker to the current slot
      sched[day][slot] = worker;
      workerShifts[worker]++;

      // Recurse to the next slot or day
      bool result;
      if (slot + 1 == dailyNeed) {
        result = scheduleHelper(avail, dailyNeed, maxShifts, sched, workerShifts, day + 1, 0);
      } 
      else {
        result = scheduleHelper(avail, dailyNeed, maxShifts, sched, workerShifts, day, slot + 1);
      }

      if (result) {
        return true; // Found a valid schedule
      }

      // Backtrack
      sched[day][slot] = INVALID_ID;
      workerShifts[worker]--;
    }

    return false; // No valid assignment found
}

