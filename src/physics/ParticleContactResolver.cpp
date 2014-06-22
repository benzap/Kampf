#include "ParticleContactResolver.hpp"

ParticleContactResolver::ParticleContactResolver(unsigned int numIterations) :
    numIterations(numIterations) {
    
}

ParticleContactResolver::~ParticleContactResolver() {
    
}

void ParticleContactResolver::setIterations(unsigned int numIterations) {
    this->numIterations = numIterations;
}

void ParticleContactResolver::addParticleContact(ParticleContact particle) {
    contactList.push_back(particle);
}

void ParticleContactResolver::clearContacts() {
    contactList.clear();
}

void ParticleContactResolver::resolveContacts(timeType delta_ms) {
    iteration = 0;
    while(iteration < numIterations) {
	floatType max = KF_MAX_FLOAT;
	unsigned maxIndex = contactList.size();
	
	for(int i = 0; i < contactList.size(); i++) {
	    floatType sepVel = contactList[i].calculateSeparationVelocity();
	    if (sepVel < max && (sepVel < 0 || contactList[i].getPenetration() > 0)) {
		max = sepVel;
		maxIndex = i;
	    }
	}

	//if we have nothing else to resolve, end
	if (maxIndex == contactList.size()) {
	    break;
	}

	//resolve the biggest one found
	contactList[maxIndex].resolve(delta_ms);
	iteration++;
    }
}
