#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

/* INCLUDES */
#include <cmath>
#include <ctime>
#include "kampf_general.hpp"
#include "Object.hpp"


/* CLASSES */
class Graphics;

/* ENUMERATIONS */
enum enumState {
  CREATING,
  NONACTIVE,
  ACTIVE,
  STOPPED,
  ANIMATING,
  DYING,
};

/* TYPEDEFS */
typedef double vecValue;
typedef clock_t clockValue;


/* DEFINITIONS */
#define NUM_TEMP_CLOCK_VALUES 2



/* START */
class Graphics: public Object {
private:
  //positioning
  vecValue position[3];
  vecValue direction[3];
  vecValue rotation[3];
  vecValue offset[3];

  //movement direction
  vecValue velocity[3];
  vecValue acceleration[3];

  //movement rotation
  vecValue ang_velocity[3];
  vecValue ang_acceleration[3];

  //State
  clockValue startTime;
  clockValue tempTime[NUM_TEMP_CLOCK_VALUES];
  clockValue endTime;
  enumState state;

protected:






public:
  
  Graphics();
  virtual ~Graphics();

  void printStatus();

  CALLBACK execute();

  //position
  CALLBACK setPosition(vecValue,vecValue, vecValue = HUGE_VAL);
  CALLBACK setDirection(vecValue,vecValue, vecValue = HUGE_VAL);
  CALLBACK setRotation(vecValue,vecValue, vecValue = HUGE_VAL);

  const vecValue* getPosition();
  const vecValue* getDirection();
  const vecValue* getRotation();

  //movement direction
  CALLBACK setVelocity(vecValue,vecValue, vecValue = HUGE_VAL);
  CALLBACK setAcceleration(vecValue,vecValue, vecValue = HUGE_VAL);

  const vecValue* getVelocity();
  const vecValue* getAcceleration();

  //movement direction
  CALLBACK setAngularVelocity(vecValue,vecValue,vecValue = HUGE_VAL);
  CALLBACK setAngularAcceleration(vecValue,vecValue,vecValue = HUGE_VAL);
  
  const vecValue* getAngularVelocity();
  const vecValue* getAngularAcceleration();

  //State
  CALLBACK setTempTime(unsigned short, clockValue = 0);
  CALLBACK setEndTime();

  const clockValue& getStartTime();
  const clockValue* getTempTime(unsigned short);
  const clockValue& getEndTime();

};


#endif //GRAPHICS_HPP
