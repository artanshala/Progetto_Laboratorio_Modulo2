#include "Particle.h"

#include <cassert>
#include <cmath>
#include <iostream>

int const Particle::fMaxNumParticleType_ = 10;
std::vector<ParticleType*> Particle::fParticleType_;
int Particle::fNParticleType_;

Particle::Particle(char* fName, double fPx, double fPy, double fPz)
    : fPx_(fPx), fPy_(fPy), fPz_(fPz) {
  if (FindParticle(fName) == 11) {
    std::cout << "No correspondence found!\n";
  } else {
    fIndex_ = FindParticle(fName);
  }
};

int Particle::FindParticle(char* fName) {
  for (int i = 0; i < fMaxNumParticleType_; i++) {
    char particleName = fParticleType_[i]->GetParticleName();
    if (particleName == *fName) {
      return i;
    }
  }
  return 11;
}

int Particle::GetIndex() { return fIndex_; }

void Particle::AddParticleType(char* fName, double fMass, int fCharge,
                               double fWidth) {
  if (fWidth == 0) {
    ParticleType* particle_ptr = new ParticleType{fName, fMass, fCharge};
    assert(fParticleType_.size() < 11 && FindParticle(fName) == 11);
    fParticleType_.push_back(particle_ptr);
  } else {
    ParticleType* resonace_ptr =
        new ResonanceType{fName, fMass, fCharge, fWidth};
    assert(fParticleType_.size() < 11 && FindParticle(fName) == 11);
    fParticleType_.push_back(resonace_ptr);
  }
}

void Particle::SetIndex(int index) {
  if (index >= 0 && index < static_cast<int>(fParticleType_.size())) {
    fIndex_ = index;
  } else {
    std::cout << "Indice non valido!" << std::endl;
  }
}

void Particle::SetIndex(char* name) {
  int index = FindParticle(name);
  if (index != 11) {
    fIndex_ = index;
  } else {
    std::cout << "Tipo di particella\"" << name << "\" non trovato!"
              << std::endl;
  }
}

void Particle::PrintArray() {
  for (int i = 0; i < fParticleType_.size(); ++i) {
    fParticleType_[i]->Print();
  }
}

void Particle::PrintParticle() {
  std::cout << "Indice Particella:" << GetIndex() << "\nNome Particella: "
            << fParticleType_[fIndex_]->GetParticleName() << std::endl;
  std::cout << "Impulso: Px=" << GetPx() << ", Py=" << GetPy()
            << ", Pz=" << GetPz() << std::endl;
}

double const Particle::GetPx() { return fPx_; }
double const Particle::GetPy() { return fPy_; }
double const Particle::GetPz() { return fPz_; }

double const Particle::GetMass() {
  return fParticleType_[fIndex_]->GetParticleMass();
};

double const Particle::GetEnergy() {
  double Mass = GetMass();
  double momentum2 = fPx_ * fPx_ + fPy_ * fPy_ + fPz_ * fPz_;
  return std::sqrt(Mass * Mass + momentum2);
}

double const Particle::GetInvMass(Particle& p) {
  double e12 = GetEnergy() + p.GetEnergy();
  double Px12 = GetPx() + p.GetPx();
  double Py12 = GetPy() + p.GetPy();
  double Pz12 = GetPz() + p.GetPz();
  double InvMass = std::sqrt((e12) * (e12) + (Px12) * (Px12) + (Py12) * (Py12) +
                             (Pz12) * (Pz12));
  return InvMass;
}

void Particle::SetP(double fPx, double fPy, double fPz) {
  fPx_ = fPx;
  fPy_ = fPy;
  fPz_ = fPz;
}

