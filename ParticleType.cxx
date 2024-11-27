#include "ParticleType.h"

#include <iostream>

ParticleType::ParticleType(char* const fName, double const fMass,
                           int const fCharge)
    : fName_(fName), fMass_(fMass), fCharge_(fCharge) {};

char ParticleType::GetParticleName() const { return *fName_; }
double ParticleType::GetParticleMass() const { return fMass_; }
int ParticleType::GetParticleCharge() const { return fCharge_; }
double ParticleType::GetParticleWidth() const { return 0.;}

void ParticleType::Print() const {
  std::cout << "Particle: " << *fName_ << "\nMass: " << fMass_
            << "\nCharge: " << fCharge_ << '\n';
}