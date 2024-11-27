#include <vector>
#include <cmath>
#include "ResonanceType.h"

#ifndef PARTICLE_H
#define PARTICLE_H

class Particle
{
private:
  static const int fMaxNumParticleType_;
  static std::vector<ParticleType *> fParticleType_;
  static int fNParticleType_;
  static int FindParticle(char *fName);
  int fIndex_;
  double fPx_{0}, fPy_{0}, fPz_{0};
  void Boost(double bx, double by, double bz);

public:
  Particle();
  Particle(char *fName, double fPx, double fPy, double fPz);
  int GetIndex();

  static void AddParticleType(char *fName, double fMass, int fcharge,
                              double fWidth);

  void SetIndex(int index);

  void SetIndex(char *name);

  double GetPx() const;

  double GetPy() const;

  double GetPz() const;

  double GetMass() const;

  double GetEnergy() const;

  double GetInvMass(Particle &p) const;

  void SetP(double fPx, double fPy, double fPz);

  static void PrintArray();

  void PrintParticle();

  int Decay2body(Particle &dau1, Particle &dau2) const;
};

#endif