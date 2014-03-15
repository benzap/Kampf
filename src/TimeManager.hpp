#ifndef TIMEMANAGER__HPP
#define TIMEMANAGER__HPP
//DESCRIPTION
/*
  Holds timer events, ticks, tocks, clocks, etc
  
  Two use cases:

  1. Stores the current time using the 'tick' command, with 'tock'
  used to return the duration between the given 'tick' and
  'tock'. These are referred to as 'Inactive' timers.

  2. Stores a time which is the current time plus a given
  duration. The TimeSystem can then query the TimeManager for when
  these times are met, and produce messages within the Messenger. This
  allows timed events, etc. These are referred to as 'Active' timers.
 */

//CLASSES
class TimeManager;

//INCLUDES
#include <map>
#include <tuple>

#include <SDL2/SDL.h>

#include "KF_globals.hpp"
#include "KF_utilities.hpp"

//DEFINITIONS

//MACROS

//ENUMS

//TYPEDEFS a tuple containing the time stored, an identifier, and a
//boolean which is 'true' when it's an active timer.
typedef std::tuple<timeType, guidType, boolType> timeTuple;
typedef std::list<timeTuple> timeContainerType;

typedef std::vector<guidType> partialTimeContainer;

//FUNCTIONS

//Constant which tells tock(...) command to return a duration based on
//the very last tick command seen
const incrementType kUseLastGuid = "";
incrementType ticker_lastId = kUseLastGuid;

//calling this starts a timer, and returns a GUID used as an
//identifier
guidType tick();

//returns the duration for the given timer
timeType tock(guidType tickID = kUseLastGuid);

//BEGIN

class TimeManager {
private:
    TimeManager() {}
    TimeManager(TimeManager const&);
    void operator=(TimeManager const&);

    //holds a mapping of times at which 
    timeContainerType timeContainer;

public:
    static TimeManager* getInstance() {
	static TimeManager _instance = TimeManager();
	return &_instance;
    }
    
    //appends a time to the time manager, and returns a guidType
    //identifying it within the time manager. offset is a time offset in
    //milliseconds to the current time.
    guidType appendTime(timeType offset = 0);
    
    //extends the offset on the given timeGuid
    void extendTime(guidType timeGuid, timeType, duration);

    //checks if the given time exists
    boolType hasTime(guidType timeGuid);

    void removeTime(guidType timeGuid);

    timeType getTime(guidType timeGuid);
    
    const std::

};


#endif //END TIMEMANAGER__HPP
