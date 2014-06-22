#ifndef PARTICLECONTACTRESOLVER__HPP
#define PARTICLECONTACTRESOLVER__HPP
//DESCRIPTION
/*
  Includes functionality for resolving several particle contacts together
*/

//CLASSES
class ParticleContactResolver;

//INCLUDES

#include <vector>
#include <algorithm>

#if defined(KF_WIN)

#include "../KF_globals.hpp"
#include "../KF_utilities.hpp"
#include "../KF_math.hpp"

#else

#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "KF_math.hpp"

#endif

#include "ParticleContact.hpp"

//DEFINITIONS

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class ParticleContactResolver {
private:
    unsigned int numIterations;
    unsigned int iteration = 0;

    std::vector<ParticleContact> contactList;
public:
    ParticleContactResolver(unsigned int numIterations);
    virtual ~ParticleContactResolver();

    void setIterations(unsigned int numIterations);
    void addParticleContact(ParticleContact particle);
    void clearContacts();
    void resolveContacts(timeType delta_ms);
};

#endif //END PARTICLECONTACTRESOLVER__HPP
