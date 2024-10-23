#include <vector>

#include "ResonanceType.h"
class Particle {
 private:
  static const int fMaxNumParticleType_;
  static std::vector<ParticleType*> fParticleType_;
  // static  ParticleType* fParticleType_[fMaxNumParticleType_];
  static int fNParticleType_;
  static int FindParticle(char* fName);
  int fIndex_;
  double fPx_{0}, fPy_{0}, fPz_{0};

 public:
  Particle(char* fName, double fPx, double fPy, double fPz);
  int GetIndex();

  static void AddParticleType(char* fName, double fMass, int fcharge,
                              double fWidth);

  void SetIndex(int index);

  void SetIndex(char* name);

  double const GetPx();

  double const GetPy();

  double const GetPz();

  double const GetMass();

  double const GetEnergy();

  double const GetInvMass(Particle &p);

  void SetP (double fPx, double fPy, double fPz);

  static void PrintArray();

  void PrintParticle();




};