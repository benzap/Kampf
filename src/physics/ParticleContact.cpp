#include "ParticleContact.hpp"

ParticleContact::ParticleContact(Message msg) {
    //received message is assumed to be a COLLISION type, so we can
    //also assume that it has a 'penetration' key and a
    //'contactNormal' customData

    firstCollision = static_cast<CollisionComponent*> (msg.firstComponent);
    firstPhysics = firstCollision->getPhysicsRelation();
    
    if (secondCollision != nullptr) {
	secondCollision = static_cast<CollisionComponent*> (msg.secondComponent);
	secondPhysics = secondCollision->getPhysicsRelation();
    }

    floatType elasticityOne = firstPhysics->getElasticity();
    floatType elasticityTwo = (secondPhysics != nullptr) ? secondPhysics->getElasticity() : 1.0;

    restitution = elasticityOne * elasticityTwo;

    std::cout << "Collision Time: " << SDL_GetTicks() << std::endl;
    std::cout << "Restitution: " << restitution << std::endl;
    
    //get the penetration from the msg custom data
    auto customDataIter = msg.customData.find("penetration");
    if (customDataIter != msg.customData.end()) {
	penetration = customDataIter->second.get_float();
	if (penetration < 0) {
	    penetration = 0;
	}
    }
    else {
	std::cerr << "No provided penetration in collision message" << std::endl;
	penetration = 0;
    }

    std::cout << "Penetration: " << penetration << std::endl;
    
    //get the contact normal from the msg custom data
    customDataIter = msg.customData.find("contactNormal");
    if (customDataIter != msg.customData.end()) {
	contactNormal = Vector3(customDataIter->second.get_vector());
    }
    else {
	std::cerr << "No provided contact normal in collision message" << std::endl;
    }

}

ParticleContact::~ParticleContact() {

}

void ParticleContact::resolveVelocity(timeType delta_ms) {
    floatType separationVelocity = calculateSeparationVelocity();
    
    if (separationVelocity > 0) {
	return;
    }
    
    floatType newSeperationVelocity = -separationVelocity * restitution;
    floatType deltaVelocity = newSeperationVelocity - separationVelocity;

    //the impulse is affected by the mass of each particle
    floatType totalInverseMass = firstPhysics->getInverseMass();
    if (secondPhysics != nullptr) {
	totalInverseMass += secondPhysics->getInverseMass();
    }

    //objects with infinite mass aren't affected
    if (totalInverseMass <= 0) {
	return;
    }

    floatType impulse = deltaVelocity / totalInverseMass;
    const Vector3 impulsePerInverseMass = contactNormal * impulse;

    
    auto firstVelocity = firstPhysics->getVelocity();
    firstVelocity += impulsePerInverseMass;
    firstVelocity *= firstPhysics->getInverseMass();
    firstPhysics->setVelocity(firstVelocity);
    
    if (secondPhysics != nullptr) {
	auto secondVelocity = secondPhysics->getVelocity();
	secondVelocity += impulsePerInverseMass;
	secondVelocity *= secondPhysics->getInverseMass();
	secondPhysics->setVelocity(secondVelocity);
    }



}

void ParticleContact::resolveInterpenetration(timeType delta_ms) {
    if (penetration <= 0) {
	return;
    }

    floatType totalInverseMass = firstPhysics->getInverseMass();
    if (secondPhysics != nullptr) {
	totalInverseMass += secondPhysics->getInverseMass();
    }

    if (totalInverseMass <= 0) {
	return;
    }

    Vector3 movePerInverseMass = contactNormal * (penetration / totalInverseMass);
    Vector3 particleMovement[2];
    particleMovement[0] = movePerInverseMass * firstPhysics->getInverseMass();
    if (secondPhysics != nullptr) {
	particleMovement[1] = movePerInverseMass * -secondPhysics->getInverseMass();
    }
    else {
	particleMovement[1] = Vector3(0,0,0);
    }
    
    //penetration resolution
    auto firstPosition = firstPhysics->getPosition();
    firstPosition += particleMovement[0];
    firstPhysics->setPosition(firstPosition);

    if (secondPhysics != nullptr) {
	auto secondPosition = secondPhysics->getPosition();
	secondPosition += particleMovement[1];
	secondPhysics->setPosition(secondPosition);
    }

}

void ParticleContact::resolve(timeType delta_ms) {
    resolveVelocity(delta_ms);
    resolveInterpenetration(delta_ms);
}

floatType ParticleContact::calculateSeparationVelocity() const {
    Vector3 relativeVelocity = firstPhysics->getVelocity();
    if (secondPhysics != nullptr) {
	relativeVelocity -= secondPhysics->getVelocity();
    }
    return relativeVelocity * contactNormal;
}

floatType ParticleContact::getPenetration() const {
    return this->penetration;
}
