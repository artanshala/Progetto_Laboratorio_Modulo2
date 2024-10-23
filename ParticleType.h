
#ifndef PARTICLETYPE_HPP
#define PARTICLETYPE_HPP

class ParticleType {
 private:
  char* const fName_;
  double const fMass_;
  int const fCharge_;

 public:
  char GetParticleName() const;
  double GetParticleMass() const;
  int GetParticleCharge() const;
  virtual double GetParticleWidth() const;

  virtual void Print() const;
  ParticleType(char* fName, double fMass, int fCharge);


};
#endif