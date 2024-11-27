#include "Particle.h"

#include <cassert>
#include <cmath>
#include <iostream>

#include <cmath>  // for M_PI
#include <cstdlib> //for RAND_MAX

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

double Particle::GetPx() const { return fPx_; }
double Particle::GetPy() const { return fPy_; }
double Particle::GetPz() const { return fPz_; }

double Particle::GetMass() const {
  return fParticleType_[fIndex_]->GetParticleMass();
};

double Particle::GetEnergy() const {
  double Mass = GetMass();
  double momentum2 = fPx_ * fPx_ + fPy_ * fPy_ + fPz_ * fPz_;
  return std::sqrt(Mass * Mass + momentum2);
}

double Particle::GetInvMass(Particle& p) const {
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



int Particle::Decay2body(Particle &dau1,Particle &dau2) const {
  if(GetMass() == 0.0){
    printf("Decayment cannot be preformed if mass is zero\n");
    return 1;
  }
  
  double massMot = GetMass();
  double massDau1 = dau1.GetMass();
  double massDau2 = dau2.GetMass();

  if(fIndex_ > -1){ // add width effect

    // gaussian random numbers

    float x1, x2, w, y1;
    
    double invnum = 1./RAND_MAX;
    do {
      x1 = 2.0 * rand()*invnum - 1.0;
      x2 = 2.0 * rand()*invnum - 1.0;
      w = x1 * x1 + x2 * x2;
    } while ( w >= 1.0 );
    
    w = sqrt( (-2.0 * log( w ) ) / w );
    y1 = x1 * w;

    massMot += fParticleType_[fIndex_]->GetParticleWidth() * y1;

  }

  if(massMot < massDau1 + massDau2){
    printf("Decayment cannot be preformed because mass is too low in this channel\n");
    return 2;
  }
  
  double pout = sqrt((massMot*massMot - (massDau1+massDau2)*(massDau1+massDau2))*(massMot*massMot - (massDau1-massDau2)*(massDau1-massDau2)))/massMot*0.5;

  double norm = 2*M_PI/RAND_MAX;

  double phi = rand()*norm;
  double theta = rand()*norm*0.5 - M_PI/2.;
  dau1.SetP(pout*sin(theta)*cos(phi),pout*sin(theta)*sin(phi),pout*cos(theta));
  dau2.SetP(-pout*sin(theta)*cos(phi),-pout*sin(theta)*sin(phi),-pout*cos(theta));

  double energy = sqrt(fPx_*fPx_ + fPy_*fPy_ + fPz_*fPz_ + massMot*massMot);

  double bx = fPx_/energy;
  double by = fPy_/energy;
  double bz = fPz_/energy;

  dau1.Boost(bx,by,bz);
  dau2.Boost(bx,by,bz);

  return 0;
}
void Particle::Boost(double bx, double by, double bz)
{

  double energy = GetEnergy();

  //Boost this Lorentz vector
  double b2 = bx*bx + by*by + bz*bz;
  double gamma = 1.0 / sqrt(1.0 - b2);
  double bp = bx*fPx_ + by*fPy_ + bz*fPz_;
  double gamma2 = b2 > 0 ? (gamma - 1.0)/b2 : 0.0;

  fPx_ += gamma2*bp*bx + gamma*bx*energy;
  fPy_ += gamma2*bp*by + gamma*by*energy;
  fPz_ += gamma2*bp*bz + gamma*bz*energy;

}